#include <cstdint>
#include <stdarg.h>

namespace global {

enum : uint32_t  {pi=1,ba=2};

namespace plain {
enum plainA { a1=0xF0,a2,a3 };
enum class plainB { b1,b2,b3 };
enum class plainC : char { c1='x',c2,c3 };
enum class plainD : uint8_t { d1=0x32U,d2,d3 };
}

namespace mytest_with_typedef {
typedef enum { a1=0xF0,a2,a3 } typedefA;
typedef int OTHERSTUFF_1;
}

namespace mytest_with_using {
using usingA = enum { a1=0xF0,a2,a3 };
}
} // endof namespace global


namespace mytest_xmacro {
/** A X-macro based enum
    (example from http://www.drdobbs.com/cpp/the-x-macro/228700289)
*/
#define COLORS \
    X(red) \
    X(blue) \
    X(green)
#define X(a) a,
enum Color { COLORS };
#undef X
#define X(a) #a,
static const char *ColorStrings[] = { COLORS };
#undef X
}
//! [defining an enum]
namespace mytest {
  enum class oknotok : bool {ok=true, not_ok=false};
}
//! [defining an enum]
