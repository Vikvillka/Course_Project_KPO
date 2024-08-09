#pragma once
#include <vector>
#include <iostream>
#include "LT.h"
#include "IT.h"

#pragma region ALL_FST

#pragma region functions
#define FST_MAIN FST(5, LEX_MAIN,\
	NODE(1, RELATION('m', 1)),\
	NODE(1, RELATION('a', 2)),\
	NODE(1, RELATION('i', 3)),\
	NODE(1, RELATION('n', 4)),\
	NODE())

#define FST_PRINT FST(6, LEX_PRINT,\
	NODE(1, RELATION('w', 1)),\
	NODE(1, RELATION('r', 2)),\
	NODE(1, RELATION('i', 3)),\
	NODE(1, RELATION('t', 4)),\
	NODE(1, RELATION('e', 5)),\
	NODE())

#define FST_RETURN FST(4, LEX_RETURN,\
	NODE(1, RELATION('r', 1)),\
	NODE(1, RELATION('e', 2)),\
	NODE(1, RELATION('t', 3)),\
	NODE())

#define FST_DECLARE FST(4, LEX_DECLARE,\
	NODE(1, RELATION('s', 1)),\
	NODE(1, RELATION('e', 2)),\
	NODE(1, RELATION('t', 3)),\
	NODE())

#define FST_INTEGER FST(4, LEX_INTEGER,\
	NODE(1, RELATION('i', 1)),\
	NODE(1, RELATION('n', 2)),\
	NODE(1, RELATION('t', 3)),\
	NODE())

#define FST_CHAR FST(5, LEX_CHAR,\
	NODE(1, RELATION('s', 1)),\
	NODE(1, RELATION('y', 2)),\
	NODE(1, RELATION('m', 3)),\
	NODE(1, RELATION('b', 4)),\
	NODE())

#define FST_FUNCTION FST(5, LEX_FUNCTION,\
	NODE(1, RELATION('f', 1)),\
	NODE(1, RELATION('u', 2)),\
	NODE(1, RELATION('n', 3)),\
	NODE(1, RELATION('c', 4)),\
	NODE())

#define FST_IF FST(3, LEX_IF,\
	NODE(1, RELATION('i', 1)),\
	NODE(1, RELATION('f', 2)),\
	NODE())

#define FST_ELSE FST(5, LEX_ELSE,\
	NODE(1, RELATION('e', 1)),\
	NODE(1, RELATION('l', 2)),\
	NODE(1, RELATION('s', 3)),\
	NODE(1, RELATION('e', 4)),\
	NODE())
#pragma endregion

#pragma region SYMBOLS
#define FST_LEFT_BRACKET FST(2, LEX_LEFTHESIS,\
	NODE(1, RELATION('(', 1)),\
	NODE()\
)
#define FST_LEFTSQUARE FST(2, LEX_LEFTSQUARE,\
	NODE(1, RELATION('[', 1)),\
	NODE()\
)
#define FST_RIGHTSQUARE FST(2, LEX_RIGHTSQUARE,\
	NODE(1, RELATION(']', 1)),\
	NODE()\
)
#define FST_RIGHT_BRACKET FST(2, LEX_RIGHTHESIS,\
	NODE(1, RELATION(')', 1)),\
	NODE()\
)
#define FST_LEFT_BRACE FST(2, LEX_RIGHTBRACE,\
	NODE(1, RELATION('{', 1)),\
	NODE()\
)
#define FST_RIGHT_BRACE FST(2, LEX_BRACELET,\
	NODE(1, RELATION('}', 1)),\
	NODE()\
)
#define FST_PLUS FST(2, LEX_PLUS,\
	NODE(1, RELATION('+', 1)),\
	NODE()\
)
#define FST_MINUS FST(2, LEX_MINUS,\
	NODE(1, RELATION('-', 1)),\
	NODE()\
)
#define FST_MULTI FST(2, LEX_STAR,\
	NODE(1, RELATION('*', 1)),\
	NODE()\
)

#define FST_AND FST(2, LEX_AND,\
	NODE(1, RELATION('&', 1)),\
	NODE()\
)
#define FST_OR FST(2, LEX_OR,\
	NODE(1, RELATION('|', 1)),\
	NODE()\
)

#define FST_INVERSE FST(2, LEX_INVERSE,\
	NODE(1, RELATION('~', 1)),\
	NODE()\
)

#define FST_COMMA FST(2, LEX_COMMA,\
	NODE(1, RELATION(',', 1)),\
	NODE()\
)
#define FST_SEMICOLON FST(2, LEX_SEMICOLON,\
	NODE(1, RELATION(';', 1)),\
	NODE()\
)
#define FST_EQUALLY FST(2, LEX_EQUAL,\
	NODE(1, RELATION('=', 1)),\
	NODE()\
)

#define FST_LOWER FST(2, LEX_LOWER,\
	NODE(1, RELATION('<', 1)),\
	NODE()\
)

#define FST_HIGHER FST(2, LEX_HIGHER,\
	NODE(1, RELATION('>', 1)),\
	NODE()\
)

#pragma endregion

#pragma region LITERALS
#define FST_NUMBERS FST(1, LEX_LITERAL,\
	NODE(10, RELATION('0', 0), RELATION('1', 0), RELATION('2', 0), RELATION('3', 0), RELATION('4', 0), RELATION('5', 0),\
	RELATION('6', 0), RELATION('7', 0), RELATION('8', 0), RELATION('9', 0)),\
	NODE()\
)


#define FST_NUMBERS16 FST(4, LEX_LITERAL, \
    NODE(1, RELATION('0', 1)), \
    NODE(1, RELATION('x', 2)), \
    NODE(32, \
        RELATION('1', 2), RELATION('1', 3), RELATION('2', 2), RELATION('2', 3), \
        RELATION('3', 2), RELATION('3', 3), RELATION('4', 2), RELATION('4', 3), \
        RELATION('5', 2), RELATION('5', 3), RELATION('6', 2), RELATION('6', 3), \
        RELATION('7', 2), RELATION('7', 3), RELATION('8', 2), RELATION('8', 3), \
        RELATION('9', 2), RELATION('9', 3), RELATION('A', 2), RELATION('A', 3), \
        RELATION('B', 2), RELATION('B', 3), RELATION('C', 2), RELATION('C', 3), \
        RELATION('D', 2), RELATION('D', 3), RELATION('E', 2), RELATION('E', 3), \
        RELATION('F', 2), RELATION('F', 3), RELATION('0', 2), RELATION('0', 3)), \
    NODE() \
)

#define FST_ID FST(2, LEX_ID, \
NODE(124,\
	RELATION('a', 0), RELATION('a', 1),\
	RELATION('b', 0), RELATION('b', 1),\
	RELATION('c', 0), RELATION('c', 1),\
	RELATION('d', 0), RELATION('d', 1),\
	RELATION('e', 0), RELATION('e', 1),\
	RELATION('f', 0), RELATION('f', 1),\
	RELATION('g', 0), RELATION('g', 1),\
	RELATION('h', 0), RELATION('h', 1),\
	RELATION('i', 0), RELATION('i', 1),\
	RELATION('j', 0), RELATION('j', 1),\
	RELATION('k', 0), RELATION('k', 1),\
	RELATION('l', 0), RELATION('l', 1),\
	RELATION('m', 0), RELATION('m', 1),\
	RELATION('n', 0), RELATION('n', 1),\
	RELATION('o', 0), RELATION('o', 1),\
	RELATION('p', 0), RELATION('p', 1),\
	RELATION('q', 0), RELATION('q', 1),\
	RELATION('r', 0), RELATION('r', 1),\
	RELATION('s', 0), RELATION('s', 1),\
	RELATION('t', 0), RELATION('t', 1),\
	RELATION('u', 0), RELATION('u', 1),\
	RELATION('v', 0), RELATION('v', 1),\
	RELATION('w', 0), RELATION('w', 1),\
	RELATION('x', 0), RELATION('x', 1),\
	RELATION('y', 0), RELATION('y', 1),\
	RELATION('z', 0), RELATION('z', 1),\
	RELATION('A', 0), RELATION('A', 1),\
	RELATION('B', 0), RELATION('B', 1),\
	RELATION('C', 0), RELATION('C', 1),\
	RELATION('D', 0), RELATION('D', 1),\
	RELATION('E', 0), RELATION('E', 1),\
	RELATION('F', 0), RELATION('F', 1),\
	RELATION('G', 0), RELATION('G', 1),\
	RELATION('H', 0), RELATION('H', 1),\
	RELATION('I', 0), RELATION('I', 1),\
	RELATION('J', 0), RELATION('J', 1),\
	RELATION('K', 0), RELATION('K', 1),\
	RELATION('L', 0), RELATION('L', 1),\
	RELATION('M', 0), RELATION('M', 1),\
	RELATION('N', 0), RELATION('N', 1),\
	RELATION('O', 0), RELATION('O', 1),\
	RELATION('P', 0), RELATION('P', 1),\
	RELATION('Q', 0), RELATION('Q', 1),\
	RELATION('R', 0), RELATION('R', 1),\
	RELATION('S', 0), RELATION('S', 1),\
	RELATION('T', 0), RELATION('T', 1),\
	RELATION('U', 0), RELATION('U', 1),\
	RELATION('V', 0), RELATION('V', 1),\
	RELATION('W', 0), RELATION('W', 1),\
	RELATION('X', 0), RELATION('X', 1),\
	RELATION('Y', 0), RELATION('Y', 1),\
	RELATION('Z', 0), RELATION('Z', 1),\
	RELATION('1', 0), RELATION('1', 1),\
	RELATION('2', 0), RELATION('2', 1),\
	RELATION('3', 0), RELATION('3', 1),\
	RELATION('4', 0), RELATION('4', 1),\
	RELATION('5', 0), RELATION('5', 1),\
	RELATION('6', 0), RELATION('6', 1),\
	RELATION('7', 0), RELATION('7', 1),\
	RELATION('8', 0), RELATION('8', 1),\
	RELATION('9', 0), RELATION('9', 1),\
	RELATION('0', 0), RELATION('0', 1)\
),\
NODE())

#define FST_STRING_LITERAL FST(3, LEX_LITERAL,\
		NODE(1, RELATION('\'', 1)),\
		NODE(135,\
		RELATION('A', 1),\
		RELATION('B', 1),\
		RELATION('C', 1),\
		RELATION('D', 1),\
		RELATION('E', 1),\
		RELATION('F', 1),\
		RELATION('G', 1),\
		RELATION('H', 1),\
		RELATION('I', 1),\
		RELATION('J', 1),\
		RELATION('K', 1),\
		RELATION('L', 1),\
		RELATION('M', 1),\
		RELATION('N', 1),\
		RELATION('O', 1),\
		RELATION('P', 1),\
		RELATION('Q', 1),\
		RELATION('R', 1),\
		RELATION('S', 1),\
		RELATION('T', 1),\
		RELATION('U', 1),\
		RELATION('V', 1),\
		RELATION('W', 1),\
		RELATION('X', 1),\
		RELATION('Y', 1),\
		RELATION('Z', 1),\
		RELATION('a', 1),\
		RELATION('b', 1),\
		RELATION('c', 1),\
		RELATION('d', 1),\
		RELATION('e', 1),\
		RELATION('f', 1),\
		RELATION('g', 1),\
		RELATION('h', 1),\
		RELATION('i', 1),\
		RELATION('j', 1),\
		RELATION('k', 1),\
		RELATION('l', 1),\
		RELATION('m', 1),\
		RELATION('n', 1),\
		RELATION('o', 1),\
		RELATION('p', 1),\
		RELATION('q', 1),\
		RELATION('r', 1),\
		RELATION('s', 1),\
		RELATION('t', 1),\
		RELATION('u', 1),\
		RELATION('v', 1),\
		RELATION('w', 1),\
		RELATION('x', 1),\
		RELATION('y', 1),\
		RELATION('z', 1),\
		RELATION('А', 1),\
		RELATION('Б', 1),\
		RELATION('В', 1),\
		RELATION('Г', 1),\
		RELATION('Д', 1),\
		RELATION('Е', 1),\
		RELATION('Ж', 1),\
		RELATION('З', 1),\
		RELATION('И', 1),\
		RELATION('Й', 1),\
		RELATION('К', 1),\
		RELATION('Л', 1),\
		RELATION('М', 1),\
		RELATION('Н', 1),\
		RELATION('О', 1),\
		RELATION('П', 1),\
		RELATION('Р', 1),\
		RELATION('С', 1),\
		RELATION('Т', 1),\
		RELATION('У', 1),\
		RELATION('Ф', 1),\
		RELATION('Х', 1),\
		RELATION('Ц', 1),\
		RELATION('Ч', 1),\
		RELATION('Ш', 1),\
		RELATION('Щ', 1),\
		RELATION('Ъ', 1),\
		RELATION('Ы', 1),\
		RELATION('Ь', 1),\
		RELATION('Э', 1),\
		RELATION('Ю', 1),\
		RELATION('Я', 1),\
		RELATION('а', 1),\
		RELATION('б', 1),\
		RELATION('в', 1),\
		RELATION('г', 1),\
		RELATION('д', 1),\
		RELATION('е', 1),\
		RELATION('ж', 1),\
		RELATION('з', 1),\
		RELATION('и', 1),\
		RELATION('й', 1),\
		RELATION('к', 1),\
		RELATION('л', 1),\
		RELATION('м', 1),\
		RELATION('н', 1),\
		RELATION('о', 1),\
		RELATION('п', 1),\
		RELATION('р', 1),\
		RELATION('с', 1),\
		RELATION('т', 1),\
		RELATION('у', 1),\
		RELATION('ф', 1),\
		RELATION('х', 1),\
		RELATION('ц', 1),\
		RELATION('ч', 1),\
		RELATION('ш', 1),\
		RELATION('щ', 1),\
		RELATION('ъ', 1),\
		RELATION('ы', 1),\
		RELATION('ь', 1),\
		RELATION('э', 1),\
		RELATION('ю', 1),\
		RELATION('я', 1),\
		RELATION('0', 1),\
		RELATION('1', 1),\
		RELATION('2', 1),\
		RELATION('3', 1),\
		RELATION('4', 1),\
		RELATION('5', 1),\
		RELATION('6', 1),\
		RELATION('7', 1),\
		RELATION('8', 1),\
		RELATION('9', 1),\
		RELATION(',', 1),\
		RELATION('.', 1),\
		RELATION('!', 1),\
		RELATION('?', 1),\
		RELATION('"', 1),\
		RELATION('(', 1),\
		RELATION(')', 1),\
		RELATION(' ', 1),\
		RELATION('\'', 2)\
),\
NODE())
#pragma endregion

#pragma endregion

#pragma region DATA_TYPES
#define INTEGER "int"
#define CHAR "symb"
#pragma endregion

namespace FST {
	struct RELATION {			// ребро:символ -> вершина графа переходов КА
		unsigned char symbol;			// символ перехода
		short nnode;			// номер смежной вершины

		RELATION(char c = 0x00, short ns = NULL);
	};

	struct NODE {				// вершина графа переходов
		short n_relation;		// количество инцидентных ребер
		RELATION* relations;	// инцидентные ребра

		NODE();
		NODE(short n, RELATION rel, ...);
	};

	struct FST {				// недетерминированный конечный автомат
		short position;		// текущая позиция в цепочке
		short nstates;			// количество состояний автомата
		char symbol;			// символ замены
		NODE* nodes;			// граф переходов: [0] - начальное состояние, [nstate-1] - конечное
		short* rstates;			// возможные состояния автомата на данной позиции

		FST(short ns, char symbol, NODE n, ...);
		~FST();
	};

	// выполнить распознавание цепочки
	bool execute(FST& fst, std::string str);

	// НКА
	void Recognize(std::vector<std::pair<int, std::string>> lexems, std::ostream* logfile,
		LT::LexTable& lextable, IT::IdTable& idtable);
};
