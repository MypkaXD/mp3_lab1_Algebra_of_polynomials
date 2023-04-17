#pragma once

#include <stack>
#include <queue>
#include <iostream>

	const unsigned int MAX_TOKEN_LENGTH = 256;

	enum States {
		START,
		FIRST_PART,
		SECOND_PART,
		AFTER_OPERATOR,
		AFTER_CLOSE_BRACKET,
		END,
		NAME,
		FAIL
	};

	//lists of chars
	const char lit[27] = { 'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m','_' };
	const char dec[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	const char ops[4] = { '+', '-', '*', '/' };
	const char sps[1] = { ' ' };
	const char dot[1] = { '.' };
	const char opb[1] = { '(' };
	const char clb[1] = { ')' };
	const char min[1] = { '-' };
	//special names
	const char* name_sin = "sin";
	const char* name_exp = "exp";
	const char* name_log = "log";

	enum Chars {
		DECIMAL,
		OPERATOR,
		SPACE,
		DOT,
		OPEN_BRACKET,
		CLOSE_BRACKET,
		MINUS,
		CHAR,
		NOT_VALID
	};

	enum TokenPrio {       //priorities
		NAME_ = -1,
		BRACKET_ = 0,
		SUM_ = 1,
		MUL_ = 2,
		UNARY_OPERATOR_ = 3,
	};

	enum TokenId {
		OP_B,
		CL_B,
		VAR,
		NUMBER,
		SIN,
		LOG,
		EXP,
		PLS,
		MIN,
		DIV,
		MUL,
		U_MIN
	};

	struct Token
	{
		int id;
		int prio;
		const char* val;
		int len;

		Token(int i, int t, const char* v, int l) : id(i), prio(t), val(v), len(l) {}
		Token(int i, int t) : prio(t), len(0), val("") {}                                                              //for brackets
		Token() : len(0), prio(TokenPrio::BRACKET_), val("") {}
		Token(const Token& old) : id(old.id), prio(old.prio), val(old.val), len(old.len) {}


	};
