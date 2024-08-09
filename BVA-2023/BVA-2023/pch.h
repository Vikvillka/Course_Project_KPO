#pragma once

#define _CRT_SECURE_NO_WARNINGS

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#define _CRT_SECURE_NO_WARNINGS

#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>
#include "stdarg.h"
#include <sstream>
