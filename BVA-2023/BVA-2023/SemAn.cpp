#include "pch.h"
#include "SemAn.h"

SA::SemanticAnalyzer::SemanticAnalyzer(LT::LexTable lextable, IT::IdTable idtable)
{
	this->lextable = lextable;
	this->idtable = idtable;
}

void SA::SemanticAnalyzer::Start(const Log::LOG& log)
{
	CheckReturn();
	//ParmsOfFunc();
	ParmsOfBiFunc();
	ParmsOfStandFunc();
	CorrectAmountOfParms();
	Types();
	FuncReturn();
	*log.stream << "-------------------------------------------------------------------------------------\n";
	*log.stream << "—емантический анализ выполнен без ошибок\n";
}

void SA::SemanticAnalyzer::CheckReturn()
{
	bool main = false;
	for (int i = 0; i < lextable.size; i++)
		if (lextable.table[i].lexema == LEX_RETURN)
		{
			if (main)
			{
				if ((lextable.table[i + 1].lexema == LEX_ID || lextable.table[i + 1].lexema == LEX_LITERAL)
					&& idtable.table[lextable.table[i + 1].idxTI].iddatatype != IT::IDDATATYPE::INT)
					throw ERROR_THROW_SEM(708, lextable.table[i].sn);
			}
			else if (lextable.table[i + 1].lexema == LEX_ID)
			{
				if (idtable.table[lextable.table[i + 1].idxTI].idtype == IT::IDTYPE::F)
					throw ERROR_THROW_SEM(700, lextable.table[i].sn);
			}
		}
		else if (lextable.table[i].lexema == LEX_MAIN)
			main = true;
}

void SA::SemanticAnalyzer::ParmsOfFunc()
{
	char buf[ID_MAXSIZE];
	int par = 0, funcpar = 0;
	for (int i = 0; i < lextable.size; i++)
		if (lextable.table[i].lexema == LEX_EQUAL)
		{
			while (lextable.table[i].lexema == LEX_SEMICOLON)
			{
				i++;
				if (lextable.table[i].lexema == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F)
				{
					strcpy(buf, idtable.table[lextable.table[i].idxTI].id);
					for (int j = 0; j < i; j++)
						if (lextable.table[j].lexema == LEX_ID && lextable.table[j - 2].lexema == LEX_FUNCTION
							&& !strcmp(buf, idtable.table[lextable.table[j].idxTI].id))
						{
							j++;
							for (j; lextable.table[j].lexema != LEX_RIGHTHESIS; j++)
								if (lextable.table[j].lexema == LEX_ID)
								{
									funcpar++;
									i += 2;
									if (idtable.table[lextable.table[j].idxTI].iddatatype == IT::IDDATATYPE::INT)
									{
										if (idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::L
											&& idtable.table[lextable.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
											par++;
										if (lextable.table[i].lexema == LEX_ID && idtable.table[lextable.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
											par++;
									}
									if (idtable.table[lextable.table[j].idxTI].iddatatype == IT::IDDATATYPE::STR)
									{
										if (idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::L
											&& idtable.table[lextable.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
											par++;
										if (lextable.table[i].lexema == LEX_ID)
											if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
												par++;
									}
								}
							if (funcpar != par || lextable.table[i + 2].lexema != LEX_SEMICOLON)
								throw ERROR_THROW_SEM(701, lextable.table[i].sn);
						}
				}
			}
		}
}

void SA::SemanticAnalyzer::ParmsOfStandFunc()
{
	for (int i = 0; i < lextable.size; i++)
		switch (lextable.table[i].lexema) {
		case LEX_PRINT: {
			if (lextable.table[i + 1].lexema != LEX_ID && lextable.table[i + 1].lexema != LEX_LITERAL)
				throw ERROR_THROW_SEM(704, lextable.table[i].sn);
			break;
		}

	}
}

void SA::SemanticAnalyzer::ParmsOfBiFunc()
{
	int parmprimecount = 0;
	int parmseccount = 0;
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == LEX_EQUAL)
		{
			while (lextable.table[i].lexema != LEX_SEMICOLON)
			{
				i++;
				if (lextable.table[i].lexema == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F)
				{
					std::string buf = idtable.table[lextable.table[i].idxTI].id;
					std::vector<IT::IDDATATYPE> parmtypes;

					while (lextable.table[i].lexema != LEX_RIGHTHESIS)
					{
						i++;
						if (lextable.table[i].lexema == LEX_ID || lextable.table[i].lexema == LEX_LITERAL)
						{
							parmtypes.push_back(idtable.table[lextable.table[i].idxTI].iddatatype);
							parmprimecount++;
						}

						if (parmprimecount > 4)
							throw ERROR_THROW_SEM(705, lextable.table[i].sn);
					}
					for (int j = 0, k = 0; j < i; j++)
					{

						if (lextable.table[j].lexema == LEX_ID || idtable.table[lextable.table[j].idxTI].idtype == IT::IDTYPE::F)
						{
							if (buf == idtable.table[lextable.table[j].idxTI].id)
							{
								while (lextable.table[j].lexema != LEX_RIGHTHESIS)
								{
									j++;
									if (lextable.table[j].lexema == LEX_ID)
									{
										parmseccount++;
										if (parmseccount > 4)
											throw ERROR_THROW_SEM(705, lextable.table[j].sn);

										if (parmtypes.size() <= k || idtable.table[lextable.table[j].idxTI].iddatatype != parmtypes[k])
										{
											throw ERROR_THROW_SEM(701, lextable.table[i].sn); // was 708
										}
										k++;
										//parmseccount++;
									}
								}
								break;
							}
						}
					}
				}
				if (parmprimecount != parmseccount)
					throw ERROR_THROW_SEM(701, lextable.table[i].sn);
				parmprimecount = 0;
				parmseccount = 0;
			}
		}
	}
}

void SA::SemanticAnalyzer::Types()
{
	IT::IDDATATYPE datatype;
	bool isFuncParm = false;
	for (int i = 0; i < lextable.size; i++) {
		if (lextable.table[i].lexema == LEX_EQUAL)
		{
			datatype = idtable.table[lextable.table[i - 1].idxTI].iddatatype;
			while (lextable.table[i].lexema != LEX_SEMICOLON)
			{
				i++;
				switch (lextable.table[i].lexema)
				{
				case LEX_ID:
				{
					if (idtable.table[lextable.table[i].idxTI].iddatatype != datatype)
						throw ERROR_THROW_SEM(706, lextable.table[i].sn);
					if (idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F)
						while (lextable.table[i].lexema != LEX_RIGHTHESIS)
							i++;
					break;
				}
				case LEX_LITERAL:
				{
					if ((idtable.table[lextable.table[i].idxTI].iddatatype != datatype) && (datatype == IT::IDDATATYPE::INT))
						throw ERROR_THROW_SEM(706, lextable.table[i].sn);
					else if (idtable.table[lextable.table[i].idxTI].iddatatype == datatype && datatype == IT::IDDATATYPE::STR)
						if (idtable.table[lextable.table[i].idxTI].value.vch.len == 0)
							throw ERROR_THROW_SEM(710, lextable.table[i].sn);
					break;
				}
				}
			}
		}
	}
}

void SA::SemanticAnalyzer::FuncReturn()
{
	for (int i = 0; i < lextable.size; i++)
		if (lextable.table[i].lexema == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F
			&& lextable.table[i - 1].lexema == LEX_FUNCTION && lextable.table[i - 3].lexema != LEX_DECLARE)
		{
			IT::IDDATATYPE iddatatype = idtable.table[lextable.table[i].idxTI].iddatatype;
			while (lextable.table[i].lexema != LEX_RETURN)
				i++;
			if (idtable.table[lextable.table[i + 1].idxTI].iddatatype != iddatatype)
				throw ERROR_THROW_SEM(707, lextable.table[i].sn);
		}
}

void SA::SemanticAnalyzer::CorrectAmountOfParms()
{
	std::string buf;
	buf.reserve(ID_MAXSIZE);
	for (int i = 0; i < lextable.size; i++)
		if (lextable.table[i].lexema == LEX_EQUAL)
		{

			int parms = 0, funcparms = 0;

			while (lextable.table[i].lexema != LEX_SEMICOLON)
			{
				i++;
				if (lextable.table[i].lexema == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F)
				{
					buf = idtable.table[lextable.table[i].idxTI].id;
					int mainLine = i;
					std::vector<IT::IDDATATYPE> types;
					while (lextable.table[i].lexema != LEX_RIGHTHESIS)
					{
						i++;
						if (lextable.table[i].lexema == LEX_ID || lextable.table[i].lexema == LEX_LITERAL)
						{
							parms++;
							types.push_back(idtable.table[lextable.table[i].idxTI].iddatatype);
						}

						if (parms > 4)
							throw ERROR_THROW_SEM(705, lextable.table[i].sn);
					}
					for (int j = 0; j < i; j++)
						if (lextable.table[j].lexema == LEX_ID && idtable.table[lextable.table[j].idxTI].idtype == IT::IDTYPE::F
							&& buf == idtable.table[lextable.table[j].idxTI].id)
						{
							j++;
							int k;
							for (j, k = 0; lextable.table[j].lexema != LEX_RIGHTHESIS; j++)
								if (lextable.table[j].lexema == LEX_ID)
								{
									if (types.size() <= k || idtable.table[lextable.table[j].idxTI].iddatatype != types[k])
										throw ERROR_THROW_SEM(705, lextable.table[mainLine].sn);
									funcparms++;
									k++;
								}
	
							if (funcparms > 4)
								throw ERROR_THROW_SEM(705, lextable.table[j].sn);

							break;
						}
				}
			}
			if (funcparms != parms)
				throw ERROR_THROW_SEM(701, lextable.table[i].sn);
		}
}
