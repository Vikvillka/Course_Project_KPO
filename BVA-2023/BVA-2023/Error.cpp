#include "pch.h"
#include "Error.h"

//   0 -  99 - системные ошибки
// 100 - 109 - ошибки параметров
// 110 - 119 - ошибки открытия и чтения файлов
Error::ERROR errors[ERROR_MAX_ENTRY] = {
	ERROR_ENTRY(0, "Недопустимый код ошибки"),
	ERROR_ENTRY(1, "Системный сбой"),
	ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
	ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
	ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
	ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
	ERROR_ENTRY(100, "Параметр -in должен быть задан"),
	ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
	ERROR_ENTRY(104, "Превышена длина входного параметра"),
	ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
	ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
	ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
	ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in)"),
	ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
	ERROR_ENTRY(113, "Превышено максимальное кол-во лексем"),
	ERROR_ENTRY(114, "Превышено кол-во идентификаторов"),
	ERROR_ENTRY(115, "Лексема не распознана"),
	ERROR_ENTRY(116, "[LA]: Несоответствие кавычек"),
	ERROR_ENTRY(117, "Превышен диапозон значений (int)"),
	ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
	ERROR_ENTRY_NODEF(120),
	ERROR_ENTRY(121, "[LA]: Используется необъявленный идентификатор"),
	ERROR_ENTRY(122, "[LA]: Переполнение таблицы идентификаторов"),
	ERROR_ENTRY(123, "[LA]: Переполнение таблицы лексем"),
	ERROR_ENTRY(124, "[LA]: Отсутствует точка входа или их несколько в функции"),
	ERROR_ENTRY(125, "[LA]: Обнаружено несколько точек входа"),
	ERROR_ENTRY(126, "[LA]: У точки входа нет тела"),
	ERROR_ENTRY_NODEF(127),
	ERROR_ENTRY(128, "[LA]: Необъявленный идентификатор"),
	ERROR_ENTRY(129, "[LA]: Переопределение идентификатора"),
	ERROR_ENTRY(130, "[PN]: Не удалось построить польскую запись"),
	ERROR_ENTRY(131, "[LA]: Слишком длинное имя идентификатора"),
	ERROR_ENTRY(132, "[LA]: Слишком длинный строковый литерал"),
	ERROR_ENTRY_NODEF(133), ERROR_ENTRY_NODEF(134), ERROR_ENTRY_NODEF(135),
	ERROR_ENTRY_NODEF(136), ERROR_ENTRY_NODEF(137), ERROR_ENTRY_NODEF(138), ERROR_ENTRY_NODEF(139),
	ERROR_ENTRY_NODEF10(140),
	ERROR_ENTRY_NODEF10(150),
	ERROR_ENTRY_NODEF10(160),
	ERROR_ENTRY_NODEF10(170),
	ERROR_ENTRY_NODEF10(180),
	ERROR_ENTRY_NODEF10(190),
	ERROR_ENTRY_NODEF100(200),
	ERROR_ENTRY_NODEF100(300),
	ERROR_ENTRY_NODEF100(400),
	ERROR_ENTRY_NODEF100(500),
	ERROR_ENTRY(600, "[SA]: Неверная структура программы"),
	ERROR_ENTRY(601, "[SA]: Несоответсвие синтаксису языка"),
	ERROR_ENTRY(602, "[SA]: Ошибка в выражении"),
	ERROR_ENTRY(603, "[SA]: Ошибка в параметрах функции"),
	ERROR_ENTRY(604, "[SA]: Ошибка в параметрах вызываемой функции"),
	ERROR_ENTRY(605, "[SA]: Ошибка в подвыражении"),
	ERROR_ENTRY(606, "[SA]: Ошибка в if"),
	ERROR_ENTRY_NODEF(607), ERROR_ENTRY_NODEF(608), ERROR_ENTRY_NODEF(609),
	ERROR_ENTRY_NODEF10(610), ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640),
	ERROR_ENTRY_NODEF10(650), ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680),
	ERROR_ENTRY_NODEF10(690),
	ERROR_ENTRY(700, "[SemA]: Ошибка в возвращаемом значении"),
	ERROR_ENTRY(701, "[SemA]: Ошибка в параметрах функции"),
	ERROR_ENTRY(702, "[SemA]: Ошибка в параметрах функции библиотеки"),
	ERROR_ENTRY(703, "[SemA]: Ошибка в параметрах функции библиотеки (неверное кол-во аргументов)"),
	ERROR_ENTRY(704, "[SemA]: Ошибка в значении для вывода в консоль"),
	ERROR_ENTRY(705, "[SemA]: Превышено стандартное число параметров функции"),
	ERROR_ENTRY(706, "[SemA]: Несоответсвие присваимаего типа данных"),
	ERROR_ENTRY(707, "[SemA]: Несоответствие типа функции и возвращаемого значения"),
	ERROR_ENTRY(708, "[SemA]: Main Должен возвращать числовое значение"),
	ERROR_ENTRY_NODEF(709),
	ERROR_ENTRY(710, "[SemA]: Ошибка в условном операторе"),
	ERROR_ENTRY_NODEF(711, ""), ERROR_ENTRY_NODEF(712), ERROR_ENTRY_NODEF(713),ERROR_ENTRY_NODEF(714),ERROR_ENTRY_NODEF(715),
	ERROR_ENTRY_NODEF(716),ERROR_ENTRY_NODEF(717),ERROR_ENTRY_NODEF(718),ERROR_ENTRY_NODEF(719),
	ERROR_ENTRY_NODEF10(720), ERROR_ENTRY_NODEF10(730), ERROR_ENTRY_NODEF10(740),
	ERROR_ENTRY_NODEF10(750), ERROR_ENTRY_NODEF10(760), ERROR_ENTRY_NODEF10(770), ERROR_ENTRY_NODEF10(780),
	ERROR_ENTRY_NODEF10(790),
	ERROR_ENTRY_NODEF100(800),
	ERROR_ENTRY_NODEF100(900)
};

Error::ERROR Error::geterror(int id) {
	ERROR e;

	e.id = (id < 0 || id >= ERROR_MAX_ENTRY) ? 0 : id;
	strcpy_s(e.message, errors[e.id].message);

	std::cout << "Ошибка, подробнее см. файл лога\n";

	return e;
}

Error::ERROR Error::geterrorin(int id, int line = -1, int col = -1) {
	ERROR e;

	e = geterror(id);
	e.inext.line = line +1;
	e.inext.col = col;

	std::cout << "Ошибка, подробнее см. файл лога\n";

	return e;
}

Error::ERROR Error::geterrors(int id, int line)
{
	ERROR e;

	e = geterror(id);
	e.inext.line = line +1;

	std::cout << "Ошибка, подробнее см. файл лога\n";

	return e;
}