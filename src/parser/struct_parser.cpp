/*
 * struct_parser.cpp
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
#include "clang/Tooling/CommonOptionsParser.h"
// Declares llvm::cl::extrahelp.
#include "llvm/Support/CommandLine.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>
#include <regex>
#include <cstdint>
#include <cassert>

#include "parser/common_parser.h"
#include "parser/struct_parser.h"
#include "data/struct_model.h"
#include <cassert>

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
std::vector<struct_model> *global_struct_collection = nullptr;
std::regex filter;

//
// ######################################################### LIBTOOLING VISITOR
//

/** This class Visits each parts of the AST.
EnmVisitor::VisitNamedDecl selects the appropriate code elements (enums).

Here we find/identify all enums in the source code and select the
appropriate ones (based on the regexp filter).
*/
class StructVisitor
  : public RecursiveASTVisitor<StructVisitor> {
public:
	explicit StructVisitor(ASTContext *Context)
		: m_Context(Context),
		  m_last_noname_Declaration(nullptr) {
	}

    bool is_template(CXXRecordDecl *prec) {
        return (nullptr != prec->getDescribedClassTemplate());
    }

    std::string get_template_type(NamedDecl *p) {
        switch(p->getKind()) {
        case clang::Decl::Kind::TemplateTypeParm:
            {
                //cout << "   -> TMPL: " << p->getDeclKindName() << endl;
                //cout << "            class " << p->getNameAsString() << endl;
                return "class";
            }
            break;
        case clang::Decl::Kind::NonTypeTemplateParm:
            {
                //cout << "   -> TMPL: " << p->getDeclKindName() << endl;
                NonTypeTemplateParmDecl* d = &dynamic_cast<NonTypeTemplateParmDecl&>(*p);
                //cout << "            " << d->getType().getAsString() << " " << p->getNameAsString() << endl;
                return d->getType().getAsString();
            }
            break;
        default:
            cerr << "not yet implemented... " << p->getDeclKindName() << endl;
            exit(1);
        }
    }

    std::string get_template_name(NamedDecl *p) {
        return p->getNameAsString();
    }

	void process_struct(const std::string fullname, clang::NamedDecl *Declaration, std::string sourcefile)
	{
		if (std::regex_match (fullname, filter )) {
			//std::cout << "struct " << fullname << " ..." << std::endl;
			CXXRecordDecl *myrec = &dynamic_cast<CXXRecordDecl&>(*Declaration);

            string newname = "";
            string templateCode = "";

            // analyze if type is templated
            if (is_template(myrec)) {
                string templateCodeTemp = "";
                TemplateDecl* templateDecl = myrec->getDescribedClassTemplate();
                assert(templateDecl!=nullptr);

                string tmpl="<";
                TemplateParameterList *tp = templateDecl->getTemplateParameters();
                for(NamedDecl *p: *tp) {
                    //cout << "  TMPL " << get_template_type(p) << " " << get_template_name(p) << endl;
                    if (tmpl.size()>1) tmpl = tmpl+",";
                    tmpl = tmpl+"TMPL_"+get_template_name(p);
                    if (templateCodeTemp.size()>0) templateCodeTemp = templateCodeTemp+", ";
                    templateCodeTemp = templateCodeTemp+get_template_type(p)+" TMPL_"+get_template_name(p);
                }
                tmpl = tmpl+">";
                newname = "template "+myrec->getNameAsString()+tmpl;
                //newname = myrec->getNameAsString()+tmpl;
                templateCode = templateCodeTemp;
            }
            else {
                newname = myrec->getNameAsString();
            }

            // analyze type and type parents
            DeclContext *context = myrec->getDeclContext();
            while(context!=nullptr) {
                // find the decl
                if (context->getDeclKind() == clang::Decl::Kind::CXXRecord)
                {
                    //CXXRecordDecl *prec = &dynamic_cast<CXXRecordDecl&>(*context);
                    CXXRecordDecl *prec = &dynamic_cast<CXXRecordDecl&>(*CXXRecordDecl::castFromDeclContext(context));
                    //cout << "  > PARENT REC "<< prec->getNameAsString() << endl;
                    if (is_template(prec)) {
                        string templateCodeTemp = "";
                        TemplateDecl* templateDecl = prec->getDescribedClassTemplate();
                        assert(templateDecl!=nullptr);

                        string tmpl="<";
                        TemplateParameterList *tp = templateDecl->getTemplateParameters();
                        for(NamedDecl *p: *tp) {
                            //cout << "  TMPL " << get_template_type(p) << " " << get_template_name(p) << endl;
                            if (tmpl.size()>1) tmpl = tmpl+",";
                            tmpl = tmpl+"TMPL_"+get_template_name(p);
                            if (templateCodeTemp.size()>0) templateCodeTemp = templateCodeTemp+", ";
                            templateCodeTemp = templateCodeTemp+get_template_type(p)+" TMPL_"+get_template_name(p);
                        }
                        tmpl = tmpl+">";
                        newname = "template "+prec->getNameAsString()+tmpl+"::"+newname;
                        //newname = prec->getNameAsString()+tmpl+"::"+newname;
                        if (templateCode.size()>0) templateCode = templateCodeTemp+", "+templateCode;
                        else templateCode = templateCodeTemp;
                    }
                    else {
                        newname = prec->getNameAsString()+"::"+newname;
                    }
                }
                else if (context->getDeclKind() == clang::Decl::Kind::Namespace)
                {
                    NamespaceDecl *pns = NamespaceDecl::castFromDeclContext(context);
                    //cout << "  > PARENT NS  "<< pns->getNameAsString() << endl;
                    newname = pns->getNameAsString()+"::"+newname;
                }
                else
                {
                    // ignore
                }
                //cout << "  > PARENT "<< context->getDeclKindName() << endl;
                context = context->getParent();
            }

            //cout << "NEW NAME: " << newname << endl;
            struct_model mymodel(newname);
            mymodel.fullname_without_template=fullname;
            if (templateCode.size()>0) {
                mymodel.template_declaration=templateCode;
                mymodel.is_a_template=true;
            }
            else {
                mymodel.is_a_template=false;
            }

			for (auto d: myrec->decls()) {
				if (d->getKind()==clang::Decl::Kind::Field) {
					FieldDecl *myfield = &dynamic_cast<FieldDecl&>(*d);
					std::string field_name = myfield->getName();
					//std::cout << " -- " << field_name << std::endl;
					mymodel.attribute_names.push_back(field_name);
				}
				else {
					// nothing
				}
			}

            global_struct_collection->push_back(mymodel);
		}
	}

	bool VisitNamedDecl(clang::NamedDecl *Declaration) {
		switch(Declaration->getKind()) {
		case clang::Decl::Kind::CXXRecord: //RecordDecl
			if (Declaration->getNameAsString().length()>0)
			{
				//cout << "NAMED " << Declaration->getDeclKindName() << "," << Declaration->getQualifiedNameAsString() << " ... " << Declaration->getNameAsString() << endl;
				SourceManager &sman = Declaration->getASTContext().getSourceManager();
				process_struct(Declaration->getQualifiedNameAsString(), Declaration, Declaration->getLocStart().printToString(sman));
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
				process_struct(Declaration->getQualifiedNameAsString(), m_last_noname_Declaration, m_last_noname_Declaration->getLocStart().printToString(sman));
			}
			else
			{
				//cout << "NONAME " << Declaration->getDeclKindName() << " ... " << Declaration->getNameAsString() << endl;
			}
			m_last_noname_Declaration = nullptr;
			break;
		case clang::Decl::Kind::Field:
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
 * This class calls/uses the StructVisitor.
 */
class StructConsumer : public clang::ASTConsumer {
public:
  explicit StructConsumer(ASTContext *Context)
    : Visitor(Context) {
	  //cout << "StructConsumer()" << endl;
  }

  virtual void HandleTranslationUnit(clang::ASTContext &Context) {
	  //cout << "HandleTranslationUnit()" << endl;
	  Visitor.TraverseDecl(Context.getTranslationUnitDecl());
  }
private:
  StructVisitor Visitor;
};

/** The action executed on the code.
 * This class calls/uses the StructConsumer.
 */
class StructAction : public clang::ASTFrontendAction {
public:
  virtual clang::ASTConsumer* CreateASTConsumer(clang::CompilerInstance &Compiler, llvm::StringRef InFile) {
	  //cout << "CreateASTConsumer" << endl;
	  return new StructConsumer(&Compiler.getASTContext());
  }
};

} // anon namespace

namespace parser {

int struct_parser(int argc,
				const char **argv,
				const data::file_model& myfile,
				std::vector<data::struct_model> &mystructs) {
	int ret = EXIT_SUCCESS;
	using namespace parser::clangstuff;

	global_struct_collection = &mystructs;
	try
	{
		filter = std::regex(myfile.regexp_filter);

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
		ret |= Tool.run(newFrontendActionFactory<StructAction>().get());
	}
	catch(std::exception& ex) {
		cerr << ex.what() << endl;
		return EXIT_FAILURE;
	}
	global_struct_collection = nullptr;
	return ret;
}

} // namespace
