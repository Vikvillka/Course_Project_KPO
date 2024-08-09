#include "LT.h"
#include "IT.h"

namespace PN {
	void PolishNotation(LT::LexTable& lextable, IT::IdTable& idtable);
	bool Convertation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable);
	void fix_lextable(LT::LexTable& lextable, const std::string& str, size_t length, size_t pos, const std::vector<int>& ids);
	int get_priority(char lexem);
	bool find_elem(std::stack<char> stack, size_t size, char elem);
}

