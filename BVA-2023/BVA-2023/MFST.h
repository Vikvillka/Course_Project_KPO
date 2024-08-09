#pragma once
#include "GRB.h"

#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3

#pragma region define
#define MFST_TRACE_START *log.stream << std::setw( 4)<<std::left<<"Шаг"<<": " \
	<< std::setw(30) << std::left << "Правило"  \
	<< std::setw(30) << std::left << "Входная лента" \
	<< std::setw(20) << std::left << "Стек" \
	<< std::endl;

#define NS(n)GRB::Rule::Chain::N(n)
#define TS(n)GRB::Rule::Chain::T(n)
#define ISNS(n) GRB::Rule::Chain::isN(n)

#define MFST_TRACE1 *log.stream <<std::setw( 4)<<std::left<<++FST_TRACE_n<<": " \
	<< std::setw(30) << std::left << rule.getCRule(nrulechain)  \
	<< std::setw(30) << std::left << getCLenta(lenta_position) \
	<< std::setw(20) << std::left << getCSt() \
	<< std::endl;

#define MFST_TRACE2    *log.stream <<std::setw( 4)<<std::left<<FST_TRACE_n<<": " \
	<< std::setw(30) << std::left << " "  \
	<< std::setw(30) << std::left << getCLenta(lenta_position) \
	<< std::setw(20) << std::left << getCSt() \
	<< std::endl;

#define MFST_TRACE3     *log.stream<<std::setw( 4)<<std::left<<++FST_TRACE_n<<": " \
	<< std::setw(30) << std::left << " "  \
	<< std::setw(30) << std::left << getCLenta(lenta_position) \
	<< std::setw(20) << std::left << getCSt() \
	<< std::endl;

#define MFST_TRACE4(c) *log.stream<<std::setw(4)<<std::left<<++FST_TRACE_n<<": "<<std::setw(20)<<std::left<<c<<std::endl;
#define MFST_TRACE5(c) *log.stream<<std::setw(4)<<std::left<<  FST_TRACE_n<<": "<<std::setw(20)<<std::left<<c<<std::endl;

#define MFST_TRACE6(c,k) *log.stream<<std::setw(4)<<std::left<<++FST_TRACE_n<<": "<<std::setw(20)<<std::left<<c<<k<<std::endl;

#define MFST_TRACE7  *log.stream<<std::setw(4)<<std::left<<state.lenta_position<<": "\
	<< std::setw(20) << std::left << rule.getCRule(state.nrulechain) \
	<< std::endl;
#pragma endregion

template <typename T>
struct use_container : T
{
	using T::T;
	using T::c;
};

typedef use_container<std::stack<short>> MFSTSTSTACK;

namespace MFST {
	struct MfstState {
		short lenta_position, nrule, nrulechain;
		MFSTSTSTACK st;
		MfstState();
		MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain);
		MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain);
	};

	struct Mfst {
		enum class RC_STEP {	//! Код возврата функции step
			NS_OK,				//! Найдено правило и цепочка, цепочка записана в стек
			NS_NORULE,			//! Не найдено правило грамматики (ошибки в грамматике)
			NS_NORULECHAIN,		//! Не найдена подходящая цепочка правила (ошибка в исходном коде)
			NS_ERROR,			//! Неизвестный нетерминальный символ грамматики
			TS_OK,				//! Текущий символ ленты == вершине стека, продвинулась лента, рор стека
			TS_NOK,				//! Текущий символ ленты != вершине стека, восстановлено состояние
			LENTA_END,			//! Текущая позиция ленты >= lenta_size
			SURPRISE			//! Неожиданный код возврата ( ошибка в step)
		};
		struct MfstDiagnosis {
			short lenta_position, nrule, nrule_chain;
			RC_STEP rc_step;
			MfstDiagnosis();
			MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain);
		}diagnosis[MFST_DIAGN_NUMBER];
		std::vector<GRBALPHABET> tape;
		short lenta_position, nrule, nrulechain, lenta_size;
		GRB::Greibach grebach;
		LT::LexTable lex;
		MFSTSTSTACK st;
		use_container<std::stack<MfstState>> storestate;
		Mfst();
		Mfst(LT::LexTable plex, GRB::Greibach pgrebach);
		std::string getCSt();
		std::string getCLenta(short pos, short n = 25);
		std::string getDiagnosis(short n);
		bool savestate(const Log::LOG& log);
		bool reststate(const Log::LOG& log);
		bool push_chain(GRB::Rule::Chain chain);
		RC_STEP step(const Log::LOG& log);
		bool start(const Log::LOG& log);
		bool savediagnois(RC_STEP pprc_step);
		void printrules(const Log::LOG& log);
		static void clearGreibach(Mfst&);
		struct Deducation {
			short size;
			std::vector<short> nrules, nrulechains;
			Deducation() : size(0), nrules(0), nrulechains(0) { };
		}deducation;
		bool savededucation();
	};
};

