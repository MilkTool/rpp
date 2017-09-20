/*
 * enum_parser.cpp
 *
 *  Created on: Jun 19, 2015
 *      Author: goto40
 */

//
// #################################################################   INCLUDES
//
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/Tooling.h"
// Declares llvm::cl::extrahelp.
#include "llvm/Support/CommandLine.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>
#include <regex>

#include "parser/enum_parser.h"
#include "parser/common_parser.h"
#include "data/enum_model.h"

using namespace std;
using namespace clang;
using namespace clang::tooling;
using namespace llvm;
using namespace data;

//
// ################################################################### GLOBALS
//

namespace {

/** variable to hold a vector of parsed enums */
std::vector<enum_model> *global_enum_collection = nullptr;
std::regex filter;

//
// ######################################################### LIBTOOLING VISITOR
//

/** This class Visits each parts of the AST.
EnmVisitor::VisitNamedDecl selects the appropriate code elements (enums).

Here we find/identify all enums in the source code and select the
appropriate ones (based on the regexp filter).
*/
class EnumVisitor
  : public RecursiveASTVisitor<EnumVisitor> {
public:
	explicit EnumVisitor(ASTContext *Context)
		: m_Context(Context),
		  m_last_noname_Declaration(nullptr) {
	}

	void process_enum(const std::string fullname, clang::NamedDecl *Declaration, std::string sourcefile)
	{
		if (std::regex_match (fullname, filter )) {
			EnumDecl *myenum = &dynamic_cast<EnumDecl&>(*Declaration);
			std::string int_type_name = myenum->getIntegerType().getAsString();
			//std::cout << "enum " << fullname << " : " << int_type_name << std::endl;
			enum_model mymodel(fullname, int_type_name);
			mymodel.sourcefile = sourcefile;
			for (auto d: myenum->decls()) {
				if (d->getKind()==clang::Decl::Kind::EnumConstant) {
					EnumConstantDecl *myconst = &dynamic_cast<EnumConstantDecl&>(*d);
					std::string const_name = myconst->getName();
					//std::cout << " -- " << const_name << std::endl;
					mymodel.value_names.push_back(const_name);
				}
				else {
					// nothing
				}
			}
			if (mymodel.value_names.size()>1) // do not use enums with one entry
			{
				if (std::none_of(global_enum_collection->begin(), global_enum_collection->end(), [&](const enum_model &m){ return m.fullname.compare(mymodel.fullname)==0; }) )
				{
					global_enum_collection->push_back(mymodel);
				}
				else
				{
					//std::cout << mymodel.fullname << " already stored" << std::endl;
				}
			}
		}
	}

	bool VisitNamedDecl(clang::NamedDecl *Declaration) {
		switch(Declaration->getKind()) {
		case clang::Decl::Kind::Enum:
			if (Declaration->getNameAsString().length()>0)
			{
				//cout << "NAMED " << Declaration->getDeclKindName() << " ... " << Declaration->getNameAsString() << endl;
				SourceManager &sman = Declaration->getASTContext().getSourceManager();
				process_enum(Declaration->getQualifiedNameAsString(), Declaration, Declaration->getLocStart().printToString(sman));
				m_last_noname_Declaration = nullptr;
			}
			else
			{
				//cout << "NONAME " << Declaration->getDeclKindName() << " ... " << Declaration->getNameAsString() << endl;
				m_last_noname_Declaration = Declaration;
			}
			break;
		case clang::Decl::Kind::Typedef:
		case clang::Decl::Kind::TypeAlias:
			if (m_last_noname_Declaration!=nullptr)
			{
				//cout << "NAMED (referenced) " << Declaration->getDeclKindName() << " ... " << Declaration->getNameAsString() << endl;
				SourceManager &sman = Declaration->getASTContext().getSourceManager();
				process_enum(Declaration->getQualifiedNameAsString(), m_last_noname_Declaration, m_last_noname_Declaration->getLocStart().printToString(sman));
			}
			else
			{
				//cout << "NONAME " << Declaration->getDeclKindName() << " ... " << Declaration->getNameAsString() << endl;
			}
			m_last_noname_Declaration = nullptr;
			break;
		case clang::Decl::Kind::EnumConstant:
			break;
		default:
			m_last_noname_Declaration = nullptr;
			//cout << "YYY " << Declaration->getDeclKindName() << " ... " << Declaration->getNameAsString() << endl;
			// nothing
			break;
		}
		return true;
	}

private:
  ASTContext *m_Context;
  clang::NamedDecl *m_last_noname_Declaration;
};

//
// ######################################################### LIBTOOLING VISITOR
//

/** The consumer consumes a part of the AST (Abstract syntax tree; code).
 * This class calls/uses the EnumVisitor.
 */
class EnumConsumer : public clang::ASTConsumer {
public:
  explicit EnumConsumer(ASTContext *Context)
    : Visitor(Context) {
	  //cout << "EnumConsumer()" << endl;
  }

  virtual void HandleTranslationUnit(clang::ASTContext &Context) {
	  //cout << "HandleTranslationUnit()" << endl;
	  Visitor.TraverseDecl(Context.getTranslationUnitDecl());
  }
private:
  EnumVisitor Visitor;
};

/** The action executed on the code.
 * This class calls/uses the EnumConsumer.
 */
class EnumAction : public clang::ASTFrontendAction {
public:
  virtual std::unique_ptr<ASTConsumer> CreateASTConsumer(clang::CompilerInstance &Compiler, llvm::StringRef InFile) {
	  //cout << "CreateASTConsumer" << endl;
	  return std::unique_ptr<ASTConsumer>(new EnumConsumer(&Compiler.getASTContext()));
  }
};
} // anon. namespace

namespace parser {

int enum_parser(int argc,
				const char **argv,
				const data::file_model& myfile,
				std::vector<data::enum_model> &myenums) {

	int ret = EXIT_SUCCESS;
	using namespace parser::clangstuff;

	try
	{
		// make enum model and filter globally availabe in this file
		global_enum_collection = &myenums;
		filter = std::regex(myfile.regexp_filter);

		// determine input files
		std::vector<std::string> files;
		if (useDBFiles.getValue())
		{
			files = OptionsParser->getCompilations().getAllFiles();
		}
		else
		{
			files = OptionsParser->getSourcePathList();
		}
		ClangTool Tool(OptionsParser->getCompilations(),files);
		//ret |= Tool.run(newFrontendActionFactory(&Finder).get());
		ret |= Tool.run(newFrontendActionFactory<EnumAction>().get());
	}
	catch(std::exception& ex) {
		cerr << ex.what() << endl;
		return EXIT_FAILURE;
	}
	global_enum_collection = nullptr;
	return ret;
}

} // namespace
