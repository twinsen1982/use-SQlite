#ifndef _SETDEBUGNEW_H_
#define _SETDEBUGNEW_H_

#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif

#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

#endif