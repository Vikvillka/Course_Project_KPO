#pragma once

#include "pch.h"
#include "LT.h"
#include "IT.h"
#include "Error.h"
#include "Log.h"

namespace SA {
	class SemanticAnalyzer {
	private:
		LT::LexTable lextable;
		IT::IdTable idtable;
		void CheckReturn();
		void ParmsOfFunc();
		void ParmsOfStandFunc();
		void Types();
		void FuncReturn();
		void CorrectAmountOfParms();
		void ParmsOfBiFunc();
	public:
		void Start(const Log::LOG& log);
		SemanticAnalyzer(LT::LexTable lextable, IT::IdTable idtable);
	};
}
