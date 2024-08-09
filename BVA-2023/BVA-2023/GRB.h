#pragma once
#include "Error.h"

typedef short GRBALPHABET;		// символы алфавита грамматики терминалы > 0, нетерминалы < 0

namespace GRB
{
	struct Rule		// правило в грамматике Грейбах
	{
		GRBALPHABET nn;		// нетерминал (левый символ правила) < 0
		int iderror;		// идентификатор диагностического сообщени¤
		short size;			// количество цепочек - правых частей правила
		struct Chain		// цепочка (правая часть правила)
		{
			short size;
			std::vector<GRBALPHABET> nt;
			Chain() : size(0), nt(0) { };
			Chain(
				short psize,			// количество символов в цепочке 
				GRBALPHABET s, ...		// символы (терминал или нетерминал)
			);
			std::string getCChain();	// получить правую сторону правила
			static GRBALPHABET T(char t) { return GRBALPHABET(t); };    // терминал
			static GRBALPHABET N(char n) { return -GRBALPHABET(n); };   // нетерминал
			static bool isT(GRBALPHABET s) { return s > 0; };			// терминал?
			static bool isN(GRBALPHABET s) { return !isT(s); };			 // нетерминал?
			static char alphabet_to_char(GRBALPHABET s) { return isT(s) ? char(s) : char(-s); };
		};
		std::vector<Chain> chains;	 // массив цепочек - правых частей правила 
		Rule();
		Rule(GRBALPHABET pnn, int iderror, short psize, Chain c, ...);
		std::string getCRule(short nchain);
		short getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j);
	};
	struct Greibach		// грамматика Грейбах
	{
		short size;					// количество правил
		GRBALPHABET startN;			// стартовый символ
		GRBALPHABET stbottomT;		// дно стека
		std::vector<Rule> rules;
		Greibach() : size(0), startN(0), stbottomT(0), rules(0) { };
		Greibach(GRBALPHABET pstartN, GRBALPHABET pstbootomT, short psize, Rule r, ...);
		short getRule(GRBALPHABET pnn, Rule& prule);	// получить правило, возвращающа¤ номер правила или -1
		Rule getRule(short n);		// получить правило по номеру
		static Greibach initGreibach();
	};
	Greibach getGreibach();		// получить грамматику
};

