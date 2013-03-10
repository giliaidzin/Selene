// Utils
#ifndef SE_UTILS_H
#define SE_UTILS_H

#include <assert.h>

#ifndef NULL
#define NULL 0
#endif // NULL

#ifdef _DEBUG

#define SAFE_DELETE(x); if (x != NULL) {delete x; x = NULL;}
#define SAFE_DELETE_ARRAY(x); if (x != NULL) {delete [] x; x = NULL;}

#define ASSERT(x, ...); assert(x);

#else

#define SAFE_DELETE(x); delete x
#define SAFE_DELETE_ARRAY(x); delete [] x

#define ASSERT(x, ...);

#endif // _DEBUG

#endif // SE_UTILS_H
