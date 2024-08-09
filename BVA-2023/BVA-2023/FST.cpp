#include "pch.h"
#include "Error.h"
#include "FST.h"
#include "In.h"

#pragma region "Графв"
FST::RELATION::RELATION(char c, short ns)
	: symbol(c), nnode(ns)
{ }

FST::NODE::NODE()
	: n_relation(0), relations(NULL)
{ }

FST::NODE::NODE(short n, RELATION rel, ...)
	: n_relation(n)
{
	RELATION* p = &rel;
	relations = DBG_NEW RELATION[n];

	for (short i = 0; i < n; ++i)
		relations[i] = p[i];
}

FST::FST::FST(short ns, char symbol, NODE n, ...)
	: symbol(symbol), position(-1), nstates(ns)
{
	nodes = DBG_NEW NODE[ns];
	NODE* p = &n;

	for (int i = 0; i < ns; ++i)
		nodes[i] = p[i];

	rstates = DBG_NEW short[nstates];
	memset(rstates, 0xff, sizeof(short) * nstates);
	rstates[0] = 0;
}

FST::FST::~FST() 
{
	for (int i = 0; i < nstates; ++i) 
	{
		delete nodes[i].relations;
		nodes[i].relations = nullptr;
	}

	delete[] nodes;
	nodes = nullptr;

	delete[] rstates;
	rstates = nullptr;
}

bool step(FST::FST& fst, short*& rstates, std::string str) 
{
	bool rc = false;

	std::swap(rstates, fst.rstates);
	for (short i = 0; i < fst.nstates; ++i)
		if (rstates[i] == fst.position)
			for (short j = 0; j < fst.nodes[i].n_relation; ++j)
				if (fst.nodes[i].relations[j].symbol == (unsigned char)str[fst.position]) 
				{
					fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
					rc = true;
				}

	return rc;
}

bool FST::execute(FST& fst, std::string str) 
{
	short* rstates = DBG_NEW short[fst.nstates];
	short lstring = (short)str.size();
	bool rc = true;

	memset(rstates, 0xff, sizeof(short) * fst.nstates);

	fst.position = -1;
	*fst.rstates = 0;

	for (short i = 0; i < lstring && rc; ++i) 
	{
		fst.position++;
		rc = step(fst, rstates, str);
	}
	delete[] rstates;

	return rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc;
}

std::string _string(int n) 
{
	char buf[40];
	sprintf_s(buf, n < 10 ? "0%d" : "%d", n);
	return buf;
}

#pragma endregion

void FST::Recognize(std::vector<std::pair<int, std::string>> lexems, std::ostream* logfile, LT::LexTable& lextable, IT::IdTable& idtable) {
#pragma region "Переменные"
	std::string temp_prefix = "", current_prefix = "";
	IT::IDDATATYPE iddatatype = IT::IDDATATYPE::INT;
	IT::IDTYPE idtype = IT::IDTYPE::L;
	FST fst_arr[] = { FST_INTEGER, FST_MAIN , FST_PRINT , FST_RETURN , FST_DECLARE , FST_CHAR , FST_FUNCTION ,
		FST_LEFT_BRACKET , FST_RIGHT_BRACKET , FST_LEFT_BRACE , FST_RIGHT_BRACE , FST_PLUS , FST_MINUS , FST_MULTI ,
		FST_AND, FST_OR, FST_INVERSE, FST_COMMA, FST_SEMICOLON, FST_EQUALLY, FST_NUMBERS, FST_NUMBERS16, FST_LEFTSQUARE, FST_RIGHTSQUARE,
		FST_IF, FST_ELSE, FST_HIGHER, FST_LOWER, FST_ID, FST_STRING_LITERAL };
	int size = sizeof(fst_arr) / sizeof(FST), it_id = -1, currentLiteral = 0;
	bool param = false, _main = false, libFunc = false;
#pragma endregion

#pragma region "Разбор лексем"
	for (size_t i = 0; i < lexems.size(); i++)
	{
		for (int j = 0; j < size; j++) {
			if (execute(fst_arr[j], lexems[i].second))
			{
				if (fst_arr[j].symbol == LEX_SEMICOLON)
					libFunc = false;
				if (lextable.table[lextable.size - 1].lexema == LEX_MAIN && fst_arr[j].symbol != LEX_RIGHTBRACE)
					throw ERROR_THROW(126);
#pragma region "Определение префикса"
				if (fst_arr[j].symbol == LEX_MAIN && !current_prefix.empty())
					throw ERROR_THROW(124);
				if (fst_arr[j].symbol == LEX_FUNCTION || fst_arr[j].symbol == LEX_MAIN)
				{
					if (current_prefix.empty())
						if (fst_arr[j].symbol == LEX_MAIN) 
						{
							if (_main == true)
								throw ERROR_THROW(125);
							_main = true;
							current_prefix = lexems[i].second;
						}
						else
							current_prefix = lexems[i + 1].second;
					else {
						temp_prefix = current_prefix;
						current_prefix = lexems[i + 1].second;
					}
					param = true;
				}

				if (fst_arr[j].symbol == LEX_RIGHTHESIS) 
				{
					if (!temp_prefix.empty())
						current_prefix = temp_prefix;
					else
						temp_prefix.clear();
					param = false;
				}
				else if (fst_arr[j].symbol == LEX_BRACELET) 
				{
					current_prefix.clear();
					temp_prefix.clear();
				}
#pragma endregion


#pragma region "Определение IDDATATYPE"
				int delt = 0;
				int hexToDec = 0;
				/*if (fst_arr[j].symbol == LEX_LITERAL)*/
					/*IT::is_digit(lexems[i].second) ? iddatatype = IT::IDDATATYPE::INT : iddatatype = IT::IDDATATYPE::CH;*/
				if (fst_arr[j].symbol == LEX_LITERAL) { 
					if (lexems[i].second.substr(0, 2) == "0x") {
						lexems[i].second.erase(0, 2); 
						iddatatype = IT::IDDATATYPE::INT; 
						idtype = IT::IDTYPE::L;
						long long hexToDec = std::stoll(lexems[i].second, nullptr, 16);
						long long intValue = static_cast<long long>(hexToDec);
						if (intValue >= std::numeric_limits<int>::min() && intValue <= std::numeric_limits<int>::max() && hexToDec == static_cast<long long>(intValue)) {
							lexems[i].second = std::to_string(intValue);
							iddatatype = IT::IDDATATYPE::INT;
						}
						else {
							throw ERROR_THROW(117);
						}
					}
					else if (IT::is_digit(lexems[i].second)) {
							double test = std::stod(lexems[i].second);
							int intValue = static_cast<int>(test);
							if (intValue >= std::numeric_limits<int>::min() && intValue <= std::numeric_limits<int>::max() && test == static_cast<double>(intValue)) {
								lexems[i].second = std::to_string(intValue);
								iddatatype = IT::IDDATATYPE::INT;
							}
							else {
								throw ERROR_THROW(117);
							}	
					}
					else if (lexems[i - 5].second == CHAR) {
							if(lexems[i].second.size() !=3){
								throw ERROR_THROW(706);
							}
							else iddatatype = IT::IDDATATYPE::CH;
					}
					else {
						iddatatype = IT::IDDATATYPE::STR;
						if (lexems[i].second.size() > 150) {
							
							throw ERROR_THROW(132);
						}
					}
				}
				else if ((fst_arr[j].symbol == LEX_ID) && lextable.size >= 2) 
				{
					if (lextable.table[lextable.size - 1].lexema == LEX_FUNCTION)
						delt = 2;
					else if (lextable.table[lextable.size - 1].lexema == LEX_INTEGER)
						delt = 1;
					if (lexems[i - delt].second == INTEGER)
						iddatatype = IT::IDDATATYPE::INT;
					else if (lexems[i - delt].second == INTEGER) {
						iddatatype = IT::IDDATATYPE::INT;
					}	
					else if (lexems[i - delt].second == CHAR)
						iddatatype = IT::IDDATATYPE::CH;
				}
#pragma endregion

#pragma region "Заполнение таблиц"

				it_id = IT::IsId(idtable, lexems[i].second.c_str(), current_prefix.c_str());

#pragma region "Запись идентификаторов"
				if (fst_arr[j].symbol == LEX_ID) 
				{
					if (it_id == TI_NULLIDX)
						if (lextable.size >= 2 && lextable.table[lextable.size - 2].lexema == LEX_DECLARE &&
							lextable.table[lextable.size - 1].lexema == LEX_DATATYPE) 
						{
							IT::Add(idtable, { lextable.size, lexems[i].second.c_str(), current_prefix.c_str(), "", iddatatype, IT::IDTYPE::V, lexems[i].second });
						}
						else if (lextable.size >= 1 && lextable.table[lextable.size - 1].lexema == LEX_FUNCTION) 
						{
							IT::Add(idtable, { lextable.size, lexems[i].second.c_str(), "", "", iddatatype, IT::IDTYPE::F, lexems[i].second });
						}
						else if (lextable.size >= 1 && lextable.table[lextable.size - 1].lexema == LEX_DATATYPE && param) 
						{
							IT::Add(idtable, { lextable.size, lexems[i].second.c_str(), current_prefix.c_str(), "", iddatatype, IT::IDTYPE::P, lexems[i].second });
						}
						else {
							*logfile << lexems[i].second << " - " << lexems[i].first << " ---> ";
							throw ERROR_THROW(128);
						}
					else if (lextable.size >= 2 && lextable.table[lextable.size - 2].lexema == LEX_DECLARE ||
						lextable.size >= 1 && lextable.table[lextable.size - 1].lexema == LEX_FUNCTION) 
					{
						*logfile << lexems[i].second << " - " << lexems[i].first << " ---> ";
						throw ERROR_THROW(129);
					}
				}
#pragma endregion

#pragma region "Запись литералов"
				if ((fst_arr[j].symbol == LEX_LITERAL || fst_arr[j].symbol == LEX_MAIN) && it_id == TI_NULLIDX) 
				{
					if (fst_arr[j].symbol == LEX_LITERAL) 
					{
						it_id = IT::LiteralRepeat(idtable, lexems[i].second);
						if (it_id == TI_NULLIDX)
							IT::Add(idtable, { lextable.size, "", "", std::to_string(currentLiteral++).c_str(), iddatatype, IT::IDTYPE::L, lexems[i].second });
					}
					else if (fst_arr[j].symbol == LEX_MAIN)
						IT::Add(idtable, { lextable.size, lexems[i].second.c_str(), "", "", IT::IDDATATYPE::INT, IT::IDTYPE::F, lexems[i].second });
				}
#pragma endregion

#pragma region "Запись в таблицу лексем"
				if (fst_arr[j].symbol != LEX_LITERAL)
					it_id = IT::IsId(idtable, lexems[i].second.c_str(), current_prefix.c_str());
				else
					it_id = IT::LiteralRepeat(idtable, lexems[i].second);
				LT::Add(lextable, { fst_arr[j].symbol, lexems[i].first, it_id });
#pragma endregion

#pragma endregion

				break;
			}
			else if (j == size - 1 && !libFunc) {
				*logfile << lexems[i].second << " - ";
				throw ERROR_THROW(115);
			}
		}
	}
	if (_main == false)
		throw ERROR_THROW(124);

#pragma endregion
}