#include "pch.h"
#include "framework.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

extern "C"
{
	long __stdcall step(long int1, long int2)
	{
		long intatSt = pow(int1, int2);
		return intatSt;
	}
	long __stdcall iabs(long aint)
	{
		return abs(aint);
	}

	void __stdcall _ConsoleWriteInt(long number) {

		std::cout << number << std::endl;
		return;
	}
	
	void __stdcall output(const char* buffer) {
		setlocale(0, "");
		if (buffer == NULL) {
			std::cout << "NULL\n";
			return;
		}
		std::cout << buffer << std::endl;
		return;
	}
	/*void __stdcall _ConsoleWriteHex(long number) {
		std::cout << "0x" << std::hex << std::uppercase << number << std::endl;
		return;
	}*/

	
};
