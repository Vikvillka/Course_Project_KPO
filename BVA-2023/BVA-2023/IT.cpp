#include "pch.h"
#include "Error.h"
#include "IT.h"

IT::IdTable IT::Create(int size)
{
	if (size > TI_MAXSIZE)
		throw ERROR_THROW(114);
	IdTable idtable;
	idtable.table = DBG_NEW Entry[size];
	idtable.maxsize = size;
	idtable.size = 0;
	return idtable;
}

void IT::Add(IdTable& idtable, const Entry& entry)
{
	if (idtable.size == idtable.maxsize)
		throw ERROR_THROW(114);
	idtable.table[idtable.size] = entry;
	idtable.size++;
}

IT::Entry IT::GetEntry(IdTable& idtable, int n)
{
	return idtable.table[n];
}

bool IT::is_digit(std::string str)
{
	for (size_t i = 0; i < str.size(); i++)
		if ((str[i] < '0' || str[i] > '9'))
			return false;
	return true;
}


int IT::IsId(IdTable& idtable, const char id[ID_MAXSIZE], const char prefix[ID_SCOPE_SIZE])
{
	bool is_found = false;
	for (int i = 0; i < idtable.size; i++) {
		for (size_t j = 0; j < strlen(idtable.table[i].id); j++) 
		{
			is_found = false;
			if (idtable.table[i].id[j] == id[j] && strlen(id) <= strlen(idtable.table[i].id))
				is_found = true;
			else
				break;
		}
		if (is_found)
			for (size_t j = 0; j < strlen(idtable.table[i].scope); j++) 
			{
				is_found = false;
				if (idtable.table[i].scope[j] == prefix[j])
					is_found = true;
				else
					break;
			}
		if (is_found)
			return i;
	}
	return TI_NULLIDX;
}

int IT::LiteralRepeat(IdTable& idtable, std::string literal)
{
	bool rc = false;
	IT::IDDATATYPE iddatatype = IT::IDDATATYPE::INT;
	/*for (size_t i = 0; i < literal.size(); i++)
		if (literal[i] < '0' || literal[i] > '9' || (literal.size() >= 2 && literal.substr(0, 2) != "0x"))
		{
			iddatatype = IT::IDDATATYPE::STR;
			break;
		}*/
	if (literal.size() >= 2 && (literal.substr(0, 2) == "0x" || literal.substr(0, 1) == "X")) {
		bool isHex = true;
		for (size_t i = 2; i < literal.size(); i++) {
			if (!isxdigit(literal[i])) {
				isHex = false;
				break;
			}
		}
		if (!isHex) {
			iddatatype = IT::IDDATATYPE::STR;
		}
	}
	else {
		for (size_t i = 0; i < literal.size(); i++) {
			if (literal[i] < '0' || literal[i] > '9') {
				iddatatype = IT::IDDATATYPE::STR;
				break;
			}
		}
	}
	for (int i = 0; i < idtable.size; i++)
		if (idtable.table[i].idtype == IT::IDTYPE::L)
			if (idtable.table[i].iddatatype == IT::IDDATATYPE::INT && iddatatype == IT::IDDATATYPE::INT) 
			{
				int temp = std::stoi(literal);
				
				if (temp == idtable.table[i].value.vint)
					return i;
			}
			else if (idtable.table[i].value.vch.str == literal)
				return i;
	return TI_NULLIDX;
}

void IT::Delete(IdTable& idtable)
{
	delete[] idtable.table;
}

IT::Entry::Entry(int idxfirstLE, const char* id, const char* scope, const char* literalID, IDDATATYPE iddatatype, IDTYPE idtype, std::string value)
	: idxfirstLE(idxfirstLE), iddatatype(iddatatype), idtype(idtype)
{
	if (idtype != IT::IDTYPE::L) 
	{
		if (strlen(id) > ID_MAXSIZE)
			throw ERROR_THROW(131);
		for (int i = 0; i < ID_MAXSIZE; i++) 
		{
			this->id[i] = id[i];
		}
		this->id[ID_MAXSIZE - 1] = '\0';
		for (int i = 0; i < ID_SCOPE_SIZE; i++) 
		{
			this->scope[i] = scope[i];
		}
		this->scope[ID_SCOPE_SIZE - 1] = '\0';

		this->literalID[0] = '-'; this->literalID[1] = '1'; this->literalID[2] = '\0';

		if (iddatatype == IT::IDDATATYPE::INT)
			if (is_digit(value))
				this->value.vint = std::stoi(value);
			else
				this->value.vint = 0;
		else if (idtype != IT::IDTYPE::L) 
		{
			this->value.vch.str[0] = '\0';
			this->value.vch.len = 0;
		}
	}
	else 
	{
		this->id[0] = '\0';
		this->scope[0] = '\0';
		this->literalID[0] = 'l';
		for (int i = 0; i < ID_MAXSIZE; i++) 
		{
			this->literalID[i + 1] = literalID[i];
		}
		this->literalID[ID_MAXSIZE - 1] = '\0';
		if (iddatatype == IT::IDDATATYPE::INT && is_digit(value)) {
			this->value.vint = std::stoi(value);
		}
		else 
		{
			for (size_t i = 0; i < value.size(); i++)
				this->value.vch.str[i] = value[i];
			this->value.vch.str[value.size()] = '\0';
			this->value.vch.len = value.size();
		}
	}
}
