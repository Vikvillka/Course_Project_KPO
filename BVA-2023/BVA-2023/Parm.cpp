#include "pch.h"
#include "Error.h"
#include "Parm.h"

wchar_t* findSubstr(int argc, _TCHAR* argv[], wchar_t(&destination)[PARM_MAX_SIZE], const wchar_t* key) 
{
	wchar_t* substr = nullptr;
	for (int i = 1; i < argc; ++i) 
	{
		substr = wcsstr(argv[i], key);
		if (substr) {
			wcscpy_s(destination, substr + wcslen(key));
			break;
		}
	}
	return substr;
}

bool findAdditionalKey(int argc, _TCHAR* argv[], const wchar_t* key) 
{
	wchar_t* substr = nullptr;
	for (int i = 1; i < argc; ++i) {
		substr = wcsstr(argv[i], key);
		if (substr)
			return true;
	}
	return false;
}

Parm::PARM Parm::getparm(int argc, _TCHAR* argv[]) 
{
	PARM p;
	wchar_t* inParm = nullptr;

	[argc, argv]() 
	{
		if (argc <= 1)
			throw ERROR_THROW(100);

		for (int i = 1; i < argc; ++i) 
		{
			if (wcslen(argv[i]) > PARM_MAX_SIZE)
				throw ERROR_THROW(104);
			if (wcsstr(argv[i], PARM_IN))
				return;
		}

		throw ERROR_THROW(100);
	}();

	inParm = findSubstr(argc, argv, p.in, PARM_IN);

	if (!findSubstr(argc, argv, p.out, PARM_OUT)) 
	{
		wcscpy_s(p.out, inParm + wcslen(PARM_IN));
		wcscat_s(p.out, PARM_OUT_DEFAULT_EXT);
	}

	if (!findSubstr(argc, argv, p.log, PARM_LOG)) 
	{
		wcscpy_s(p.log, inParm + wcslen(PARM_IN));
		wcscat_s(p.log, PARM_LOG_DEFAULT_EXT);
	}

	findAdditionalKey(argc, argv, PARM_LEX) ? p.lex = true : p.lex = false;
	findAdditionalKey(argc, argv, PARM_ID) ? p.id = true : p.id = false;

	return p;
}