#include "pch.h"
#include "Error.h"
#include "LT.h"

LT::LexTable LT::Create(int size) {
	if (size > LT_MAXSIZE)
		throw ERROR_THROW(113);
	LT::LexTable lextable;
	lextable.size = 0;
	lextable.maxsize = size;
	lextable.table = DBG_NEW Entry[size];
	return lextable;
}

void LT::Add(LexTable& lextable, Entry entry)
{
	if (lextable.maxsize == lextable.size)
		throw ERROR_THROW(113);
	lextable.table[lextable.size] = entry;
	lextable.size++;
}

LT::Entry LT::GetEntry(LexTable& lextable, int n)
{
	return lextable.table[n];
}

void LT::Delete(LexTable& lextable)
{
	delete[] lextable.table;
}