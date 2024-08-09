#pragma once

#pragma region defines
#define ID_MAXSIZE 15				// максимальное количество символов в идентификаторе 
#define ID_SCOPE_SIZE 15			
#define TI_MAXSIZE 4096
#define TI_INT_DEFAUL 0x0000000
#define TI_STR_DEFAULT 0x00
#define TI_NULLIDX -1
#define TI_CH_MAXSIZE 255
#pragma endregion

namespace IT {
	enum class IDDATATYPE { INT = 1, CH = 2, STR = 3};
	enum class IDTYPE { V = 1, F = 2, P = 3, L = 4 }; // ТИПЫ ИДЕНТИФИКАТОРОВ: ПЕРЕМЕННАЯ, ФУНКЦИЯ, ПАРАМЕТР, ЛИТЕРАЛ

	struct Entry {
		int idxfirstLE;
		char id[ID_MAXSIZE];			// идентификатор (автоматически усекается до ID_MAXSIZE)
		char scope[ID_SCOPE_SIZE];
		char literalID[ID_MAXSIZE];
		IDDATATYPE iddatatype;			// тип данных
		IDTYPE idtype;					// тип идентификатора
		union Value {
			int vint;					// значение integer
			struct Char {//
				size_t len;
				char str[TI_CH_MAXSIZE];
			} vch;
		} value;
		Entry() = default;
		Entry(int idxfirstLE, const char* id, const char* scope, const char* literalID, IDDATATYPE iddatatype, IDTYPE idtype, std::string value);
	};

	struct IdTable 
	{		 // экземпляр таблицы идентификаторов
		int maxsize, size;	 // емкость таблицы идентификаторов < TI_MAXSIZE
		Entry* table;
	};

	IdTable Create(int size);
	void Add(IdTable& idtable, const Entry& entry);
	Entry GetEntry(IdTable& idtable, int n);	// получить строку таблицы идентификаторов
	bool is_digit(std::string str);
	int IsId(IdTable& idtable, const char id[ID_MAXSIZE], const char prefix[ID_SCOPE_SIZE]); //q Возврат номера строки, если существует || TI_NULLIDX
	int LiteralRepeat(IdTable& idtable, std::string literal);
	void Delete(IdTable& idtable);		// удалить таблицу лексем (освободить память)
}
