#ifndef _DEBUG_PRINTF_H_
#define _DEBUG_PRINTF_H_
#include <windows.h>
#include <stdio.h>
inline void DebugPrintf(LPCSTR pFormat, ...)
{
#if defined(_DEBUG) || defined(DEBUG)
	va_list argp;
	char strBuf[256];
	va_start(argp, pFormat);
	vsprintf_s(strBuf, 256, pFormat, argp);
	va_end(argp);
	OutputDebugStringA(strBuf);
#endif
}

#endif	//_DEBUG_PRINTF_H_