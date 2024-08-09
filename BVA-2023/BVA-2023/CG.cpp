#include "CG.h"

CG::Generator::Generator(LT::LexTable lexT, IT::IdTable idT, wchar_t outfile[PARM_MAX_SIZE])
{
	lextable = lexT;
	idtable = idT;
	out = std::ofstream(outfile);
}

void CG::Generator::Start(const Log::LOG& log)
{
	Head();
	Constants();
	Data();
	Code();
	*log.stream << "-------------------------------------------------------------------------------------\n";
	*log.stream << "Код успешно сгенерирован\n";
	*log.stream << "-------------------------------------------------------------------------------------\n";
}

void CG::Generator::Head()
{
	out << ".586\n";
	out << ".model flat, stdcall\n";
	out << "includelib libucrt.lib\n";
	out << "includelib kernel32.lib\n";
	out << "includelib ../Debug/BVA_Lib.lib\n";
	out << "ExitProcess PROTO : DWORD\n";
	out << "_ConsoleWriteInt	PROTO : SDWORD\n";
	out << "_ConsoleWriteHex	PROTO : SDWORD\n";
	out << "iabs PROTO      :	  SDWORD\n";
	out << "step PROTO    :   SDWORD,\t : SDWORD\n";
	out << "output PROTO       :   SDWORD\n\n";
	out << "\n.stack 4096\n";
}

void CG::Generator::Constants()
{
	out << ".const\n";
	for (int i = 0; i < idtable.size; i++)
		if (idtable.table[i].idtype == IT::IDTYPE::L)
		{
			out << "\t" << idtable.table[i].literalID;
			if (idtable.table[i].iddatatype == IT::IDDATATYPE::CH || idtable.table[i].iddatatype == IT::IDDATATYPE::STR)
				out << " BYTE " << idtable.table[i].value.vch.str << ", 0";
			if (idtable.table[i].iddatatype == IT::IDDATATYPE::INT)
				out << " SDWORD " << std::setw(0) << std::setfill('0') << idtable.table[i].value.vint;
			out << '\n';
		}
}

void CG::Generator::Data()
{
	std::vector<char> operators = { LEX_MINUS, LEX_PLUS, LEX_STAR, LEX_AND, LEX_INVERSE, LEX_OR };
	out << ".data\n";
	for (int i = 0; i < idtable.size; i++)
		if (idtable.table[i].idtype == IT::IDTYPE::V) {
			out << '\t';
			out << idtable.table[i].scope << idtable.table[i].id;
			out << "\t\t\tSDWORD 0\n";
		}
}

void CG::Generator::Code()
{
	out << "\n.code\n";
	int indOfFunc = -1;
	int indOflex = -1;
	bool func = false;
	bool main = false;

	std::stack<std::string> if_marks;
	const std::string if_mark_template = "skip_if_";
	int if_mark_count = 0;

	for (int i = 0; i < lextable.size; i++)
	{
		switch (lextable.table[i].lexema)
		{
		case LEX_FUNCTION:
		{
			if (func || main)
				break;
			indOfFunc = i + 1;
			out << idtable.table[lextable.table[indOfFunc].idxTI].id << " PROC ";
			func = true;
			int backup = i;
			while (lextable.table[i].lexema != LEX_RIGHTHESIS)
				i++;
			while (lextable.table[i].lexema != LEX_LEFTHESIS)
			{
				if (lextable.table[i].lexema == LEX_ID)
				{
					out << idtable.table[lextable.table[i].idxTI].id << ": SDWORD";
					if (lextable.table[i - 2].lexema != LEX_LEFTHESIS)
						out << ", ";
				}
				i--;
			}
			i = backup;
			out << std::endl;
			break;
		}
		case LEX_MAIN: {
			main = true;
			out << "main PROC\n";
			break;
		}
		case LEX_BRACELET: {
			if (func)
			{
				out << idtable.table[lextable.table[indOfFunc].idxTI].id << " ENDP\n\n";
				func = false;
			}
			else
				out << "\tcall\t\tExitProcess\nmain ENDP\n";
			indOfFunc = 0;
			break;
		}
		case LEX_RETURN: {
			if (main) {
				out << "\tpush\t\t";
				if (lextable.table[i + 1].lexema == LEX_ID) {
					out << idtable.table[lextable.table[i + 1].idxTI].scope
						<< idtable.table[lextable.table[i + 1].idxTI].id;
				}
				else
					out << idtable.table[lextable.table[i + 1].idxTI].literalID;
				out << std::endl;
			}
			else
			{
				if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::CH) {
					if (idtable.table[lextable.table[i + 1].idxTI].idtype != IT::IDTYPE::L)
						out << "\tmov\t\teax, " << idtable.table[lextable.table[i + 1].idxTI].scope
						<< idtable.table[lextable.table[i + 1].idxTI].id << "\n\tret\n";
					else
						out << "\tmov\t\teax, offset " << idtable.table[lextable.table[i + 1].idxTI].literalID << "\n\tret\n";
				}
				else
					out << "\tmov\t\teax, " << idtable.table[lextable.table[i + 1].idxTI].scope
					<< idtable.table[lextable.table[i + 1].idxTI].id << "\n\tret\n";
			}
			break;
		}
		case LEX_PRINT: {
			if (lextable.table[i + 1].lexema == LEX_ID) {
				if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::INT) {
					out << "\tpush\t\t" << idtable.table[lextable.table[i + 1].idxTI].scope
						<< idtable.table[lextable.table[i + 1].idxTI].id;
					out << "\n\tcall\t\t_ConsoleWriteInt\n";
				}
				else {
					out << "\tpush\t\t" << idtable.table[lextable.table[i + 1].idxTI].scope
						<< idtable.table[lextable.table[i + 1].idxTI].id;
					out << "\n\tcall\t\toutput\n\n";
				}
			}
			else if (lextable.table[i + 1].lexema == LEX_LITERAL) {
				if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::INT) {
					out << "\tpush\t\t" << idtable.table[lextable.table[i + 1].idxTI].literalID;
					out << "\n\tcall\t\t_ConsoleWriteInt\n";
				}
				else {
					out << "\tpush\t\toffset " << idtable.table[lextable.table[i + 1].idxTI].literalID;
					out << "\n\tcall\t\toutput\n\n";
				}
			}
			break;
		}
		case LEX_EQUAL: {
			indOflex = i - 1;
			while (lextable.table[i].lexema != LEX_SEMICOLON) {
				if (lextable.table[i].lexema == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype != IT::IDTYPE::F)
					if (!func)
						out << "\tpush\t\t" << idtable.table[lextable.table[i].idxTI].scope
						<< idtable.table[lextable.table[i].idxTI].id << "\n";
					else
						out << "\tpush\t\t" << idtable.table[lextable.table[i].idxTI].id << "\n";
				if (lextable.table[i].lexema == LEX_LITERAL) {
					if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
						out << "\tpush\t\t";
					else
						out << "\tpush\t\toffset ";
					out << idtable.table[lextable.table[i].idxTI].literalID << "\n";
				}
				if (lextable.table[i].lexema == LEX_HEADOFFUNC)
				{
					int delta = lextable.table[i + 1].lexema - '0' + 1;
					out << "\tcall\t\t" << idtable.table[lextable.table[i - delta].idxTI].id << "\n";
					out << "\tpush\t\teax\n";
				}
				if (lextable.table[i].lexema == LEX_PLUS)
				{
					out << "\t;\\/(ADD)+\\/\n";
					out << "\tpop\t\teax\n";
					out << "\tpop\t\tebx\n";
					out << "\tADD\t\teax, ebx\n";
					out << "\tpush\t\teax\n";
					out << "\t;/\\(ADD)+/\\\n";
				}
				if (lextable.table[i].lexema == LEX_MINUS)
				{
					out << "\t;\\/(SUB)-\\/\n";
					out << "\tpop\t\tebx\n";
					out << "\tpop\t\teax\n";
					out << "\tSUB\t\teax, ebx\n";
					out << "\tpush\t\teax\n";
					out << "\t;/\\SUB(-)/\\\n";
				}
				if (lextable.table[i].lexema == LEX_STAR)
				{
					out << "\t;\\/(MUL)*\\/\n";
					out << "\tpop\t\teax\n";
					out << "\tpop\t\tebx\n";
					out << "\tMUL\t\tebx\n";
					out << "\tpush\t\teax\n";
					out << "\t;/\\(MUL)*/\\\n";
				}
				if (lextable.table[i].lexema == LEX_AND) {
					out << "\t;\\/AND(&)\\/\n";
					out << "\tpop\t\teax\n";
					out << "\tpop\t\tedx\n";
					out << "\tAND\t\teax, edx\n";
					out << "\tpush\t\teax\n";
					out << "\t;/\\AND(&)/\\\n";
				}
				if (lextable.table[i].lexema == LEX_OR) {
					out << "\t;\\/(OR)|\\/\n";
					out << "\tpop\t\teax\n";
					out << "\tpop\t\tedx\n";
					out << "\tOR\t\teax, edx\n";
					out << "\tpush\t\teax\n";
					out << "\t;/\\(OR)|/\\\n";
				}
				if (lextable.table[i].lexema == LEX_INVERSE) {
					out << "\t;\\/(INVERSE(NOT)):\\/\n";
					out << "\tpop\t\teax\n";
					out << "\tNOT\t\t\teax\n";
					out << "\tpush\t\teax\n";
					out << "\t;/\\(INVERSE(NOT)):/\\\n";
				}
				i++;
			}
			out << "\tpop\t\t\t" << idtable.table[lextable.table[indOflex].idxTI].scope
				<< idtable.table[lextable.table[indOflex].idxTI].id << "\n\n";
			break;
		}
					  

		case LEX_IF: {
			i += 2;
			auto lhs = lextable.table[i];
			i++;

			if_marks.push(if_mark_template + std::to_string(if_mark_count++));

			if (lextable.table[i].lexema == LEX_RIGHTHESIS)
			{
				out << "\tpush ";
				out << idtable.table[lhs.idxTI].scope << idtable.table[lhs.idxTI].id << "\n";
				out << "\tpop eax\n";
				out << "\ttest eax, eax\n";
				out << "\tjz " << if_marks.top() << "\n";
				break;
			}

			auto op = lextable.table[i].lexema;
			auto rhs = lextable.table[++i];
			i++;

			out << "\tpush ";
			if (lhs.lexema == LEX_LITERAL)
				out << idtable.table[lhs.idxTI].literalID << "\n";
			else
				out << idtable.table[lhs.idxTI].scope << idtable.table[lhs.idxTI].id << "\n";

			out << "\tpush ";
			if (rhs.lexema == LEX_LITERAL)
				out << idtable.table[rhs.idxTI].literalID << "\n";
			else
				out << idtable.table[rhs.idxTI].scope << idtable.table[rhs.idxTI].id << "\n";

			out << "\tpop ebx\n";
			out << "\tpop eax\n";

			switch (op)
			{
			case LEX_LOWER:
				out << "\tcmp eax, ebx\n";
				out << "\tjge " << if_marks.top() << "\n";
				break;
			case LEX_HIGHER:
				out << "\tcmp eax, ebx\n";
				out << "\tjle " << if_marks.top() << "\n";
				break;
			case LEX_OR:
				out << "\tor eax, ebx\n";
				out << "\ttest eax, eax\n";
				out << "\tjz " << if_marks.top() << "\n";
				break;
			case LEX_AND:
				out << "\ttest eax, ebx\n";
				out << "\tjz " << if_marks.top() << "\n";
				break;
			}
			break;
		}


		case LEX_LEFTSQUARE: {
			
			break;
		}
		case LEX_RIGHTSQUARE: {

			out << if_marks.top() << ":\n";
			if_marks.pop();

			
			break;
		}
		default:break;
		}

	}
	out << "end main\n";
}