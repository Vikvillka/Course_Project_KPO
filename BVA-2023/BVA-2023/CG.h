#pragma once
#include "pch.h"
#include "LT.h"
#include "It.h"
#include "Log.h"

namespace CG
{
	class Generator
	{
	private:
		LT::LexTable lextable;
		IT::IdTable idtable;
		std::ofstream out;
		void Head();
		void Constants();
		void Data();
		void Code();

	public:
		Generator(LT::LexTable lexT, IT::IdTable idT, wchar_t out[PARM_MAX_SIZE]);
		void Start(const Log::LOG& log);
	};
}
