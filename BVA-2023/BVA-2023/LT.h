#pragma once

#pragma region lexems
#define LEXEMA_FIXSIZE 1
#define LT_MAXSIZE 4096
#define LT_TI_NULLIDX (int)-1 //Нет элемента таблицы идентификаторов
#define LEX_INTEGER 't'
#define LEX_CHAR 't'
#define LEX_DATATYPE 't'
#define LEX_ID 'i'
#define LEX_LITERAL 'l'
#define LEX_FUNCTION 'f'
#define LEX_ST 'i'
#define LEX_IABS 'i'
#define LEX_TIME 'i'
#define LEX_CONVERT 'f'
#define LEX_DECLARE 'd'
#define LEX_RETURN 'r'
#define LEX_PRINT 'p'
#define LEX_SEMICOLON ';'
#define LEX_COMMA ','
#define LEX_RIGHTBRACE '{'
#define LEX_BRACELET '}'
#define LEX_LEFTHESIS '('
#define LEX_RIGHTHESIS ')'
#define LEX_PLUS '+'
#define LEX_MINUS '-'
#define LEX_STAR '*'
#define LEX_INVERSE '~'
#define LEX_OR '|'
#define LEX_AND '&'
#define LEX_MAIN 'm'
#define LEX_LEFTSQUARE '['
#define LEX_RIGHTSQUARE ']'
#define LEX_EQUAL '='
#define LEX_IF 'e'
#define LEX_ELSE 'T'
#define LEX_LOWER '<'
#define LEX_HIGHER '>'
#define LEX_HEADOFFUNC '@'
#pragma endregion

namespace LT {
	struct Entry {
		char lexema;
		int sn; //Номер строки в исходном коде
		int idxTI; //индекс в табллице идентификаторов (default = LT_TI_NULLIDX)
	};

	struct LexTable {
		int maxsize;
		int size; //Текущий размер < maxsize
		Entry* table;
	};

	LexTable Create(int size);
	void Add(LexTable& lextable, Entry entry);
	Entry GetEntry(LexTable& lextable, int n); //n - номер получаемой строки
	void Delete(LexTable& lextable);
}

