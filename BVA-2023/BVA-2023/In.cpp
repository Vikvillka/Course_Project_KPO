#include "pch.h"
#include "Error.h"
#include "In.h"

void writeCharToInput(In::IN& input, const char& ch) 
{
	input.text[input.size] = ch;
	input.size++;
}

void writeNewLexem(std::vector<std::pair<int, std::string>>& lexems, std::string& lexem, int line) 
{
	if (!lexem.empty() && lexem != "\'") 
	{
		if (!lexems.empty() && (line - lexems[lexems.size() - 1].first > 1))
			line -= 1;
		lexems.push_back({ line, lexem });
	}
	lexem.clear();
}

In::IN In::getin(wchar_t infile[], wchar_t outfile[]) 
{
	std::ifstream inputFile(infile, std::ifstream::ate);
	std::ofstream outputFile(outfile);
	size_t fileSize = (size_t)inputFile.tellg();
	IN input;
	std::string temp_lexem;
	if (!inputFile.is_open())
		throw ERROR_THROW(110);

	if (!outputFile.is_open())
		throw ERROR_THROW(110);

	inputFile.seekg(std::ios::beg);

	input.text = DBG_NEW unsigned char[fileSize + 1];
	int real_size = 0;

	for (int column = 0, readChar = 0; readChar != EOF;) 
	{
		readChar = inputFile.get();
		real_size++;
		if (readChar < 0) 
		{
			writeNewLexem(input.lexems, temp_lexem, input.lines);
			break;
		}

		if (input.code[readChar] == IN::Q) 
		{
			writeNewLexem(input.lexems, temp_lexem, input.lines);
			temp_lexem += readChar;
			do 
			{
				if (readChar == IN_CODE_ENDL)
					throw ERROR_THROW(116);
				writeCharToInput(input, readChar);
				column++;
				readChar = inputFile.get();
				temp_lexem += readChar;
			} while (input.code[readChar] != IN::Q);
			writeNewLexem(input.lexems, temp_lexem, input.lines);
		}

		if (input.code[readChar] == IN::O || input.code[input.text[input.size - 1]] == IN::O) 
		{
			writeNewLexem(input.lexems, temp_lexem, input.lines);
			if (input.code[input.text[input.size - 1]] == IN::S) 
			{
				input.size--;
				input.ignor++;
			}
		}

		//точка с запятой конец main
		if (readChar == EOF || readChar == IN_CODE_ENDL) 
		{
			input.lines++;
			if (input.text[input.size - 1] != IN_CODE_ENDL) 
			{
				writeCharToInput(input, IN_CODE_DELIM);
				writeCharToInput(input, IN_CODE_ENDL);
				column = 0;
			}
			writeNewLexem(input.lexems, temp_lexem, input.lines);
			continue;
		}

		else if (input.code[readChar] == IN::S) 
		{
			writeNewLexem(input.lexems, temp_lexem, input.lines);
			if (input.code[input.text[input.size - 1]] != IN::S && input.code[input.text[input.size - 1]] != IN::O &&
				input.text[input.size - 1] != IN_CODE_ENDL) 
			{
				writeCharToInput(input, readChar);
			}
			else 
			{
				input.ignor++;
			}
		}
		else if (input.code[readChar] == IN::F) 
		{
			throw ERROR_THROW_IN(111, input.lines, column);
		}
		else if (input.code[readChar] == IN::I)
			input.ignor++;
		else if (input.code[readChar] == IN::T || input.code[readChar] == IN::O || input.code[readChar] == IN::Q) 
		{
			writeCharToInput(input, readChar);
			temp_lexem += readChar;
		}
		else 
		{
			writeCharToInput(input, input.code[readChar]);
			temp_lexem += readChar;
		}
		column++;
	}
	input.text[input.size] = '\0';
	input.size = real_size - 1;

	inputFile.close();
	outputFile << input.text;
	outputFile.close();
	return input;
}

In::IN::IN()
	:size(0), lines(0), ignor(0), text(nullptr)
{
	int tempCodeTable[] = IN_CODE_TABLE;
	memcpy_s(code, sizeof(code), tempCodeTable, sizeof(tempCodeTable));
}

In::IN::IN(const IN& other)
	: size(other.size), lines(other.lines), ignor(other.ignor), lexems(other.lexems)
{
	//int tempCodeTable[] = IN_CODE_TABLE;
	memcpy_s(code, sizeof(code), other.code, sizeof(other.code));

	text = DBG_NEW unsigned char[strlen((const char*)other.text) + 1];
	std::copy(other.text, other.text + strlen((const char*)other.text) + 1, text);
}

In::IN::~IN() {
	delete[] text;
	lexems.clear();
	text = nullptr;
}