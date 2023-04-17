#pragma once
#include "Enums.h"



class FSMValidator {
private:
	int state;
	std::queue<int> res;                             //remember positions of tokens
	                                                 //start and end for numbers, start for brackets and operators

	bool brackets(const char* s);
	void push(int i);
	int findType(const char i);
	int isFunc(const char* s, int cur);
	int start(const char i, int c);
	int afterOperator(const char i, int c);
	int firstPart(const char i, int c);
	int secondPart(const char i, int c);
	int afterCloseBracket(const char i, int c);
	int name(const char i, int c);
	int end(const char i, int c);

public:

	FSMValidator();
	void validate(const char* str, std::queue<int>& r);

};

FSMValidator::FSMValidator() : state(States::START) {}


int FSMValidator::isFunc(const char* s, int cur) {
	
	for (int i = 0; s[i] != '\0'; i++) {
		if (name_log[i] == '\0' && findType(s[i]) != Chars::CHAR && findType(s[i]) != Chars::DECIMAL) {
			push(cur);
			push(cur + i - 1);
			return i - 1;
		}
		if (s[i] != name_log[i]) {
			break;
		}
	}

	for (int i = 0; s[i] != '\0'; i++) {
		if (name_log[i] == '\0' && findType(s[i]) != Chars::CHAR && findType(s[i]) != Chars::DECIMAL) {
			push(cur);
			push(cur + i - 1);
			return i - 1;
		}
		if (s[i] != name_sin[i]) {
			break;
		}
	}

	for (int i = 0; s[i] != '\0'; i++) {
		if (name_log[i] == '\0' && findType(s[i]) != Chars::CHAR && findType(s[i]) != Chars::DECIMAL) {
			push(cur);
			push(cur + i - 1);
			return i - 1;
		}
		if (s[i] != name_exp[i]) {
			break;
		}
	}

	return 0;
}

bool FSMValidator::brackets(const char* s) {
	int c1 = 0;
	char c = s[0];
	for (int i = 0; s[i] != '\0'; c = s[i]) {
		i++;
		if (c == '(')
			c1++;
		else if (c == ')')
			if (c1 == 0)
				return false;
			else
				c1--;

	}

	if (c1 == 0)
		return true;
	else
		return false;

}

void FSMValidator::push(int i) {
	res.push(i);
	//std::cout << "push";
}

int FSMValidator::findType(const char i) {

	for (char a : lit) {
		if (a == i)
			return Chars::CHAR;
	}

	for (char a : dec) {
		if (a == i)
			return Chars::DECIMAL;
	}

	for (char a : opb) {
		if (a == i)
			return Chars::OPEN_BRACKET;
	}

	for (char a : clb) {
		if (a == i)
			return Chars::CLOSE_BRACKET;
	}

	for (char a : min) {                        //minus before operator is essential
		if (a == i)
			return Chars::MINUS;
	}

	for (char a : ops) {
		if (a == i)
			return Chars::OPERATOR;
	}

	for (char a : dot) {
		if (a == i)
			return Chars::DOT;
	}

	for (char a : sps) {
		if (a == i)
			return Chars::SPACE;
	}

	return Chars::NOT_VALID;

}

int FSMValidator::start(const char i, int c) {
	int type = findType(i);
	//std::cout << " /" << type << "/ ";
	switch (type)
	{

	case Chars::SPACE:
		return States::START;

	case Chars::OPEN_BRACKET:
		push(c);
		return States::START;

	case Chars::MINUS:
		push(c);
		return States::AFTER_OPERATOR;

	case Chars::DECIMAL:
		push(c);
		return States::FIRST_PART;

	case Chars::DOT:
		push(c);
		return States::SECOND_PART;

	case Chars::CHAR:
		push(c);
		return States::NAME;

	default:
		return States::FAIL;

	}
}

int FSMValidator::afterOperator(const char i, int c) {
	int type = findType(i);
	//std::cout << " /" << type << "/ ";
	switch (type)
	{

	case Chars::SPACE:
		return States::AFTER_OPERATOR;

	case Chars::OPEN_BRACKET:
		push(c);
		return States::START;

	case Chars::DECIMAL:
		push(c);
		return States::FIRST_PART;

	case Chars::DOT:
		push(c);
		return States::SECOND_PART;

	case Chars::CHAR:
		push(c);
		return States::NAME;

	default:
		return States::FAIL;

	}
}

int FSMValidator::name(const char i, int c) {
	int type = findType(i);
	//std::cout << " /" << type << "/ ";
	switch (type)
	{

	case Chars::SPACE:
		push(c - 1);
		return States::END;

	case Chars::DECIMAL:
		return States::NAME;

	case Chars::CHAR:
		return States::NAME;

	case Chars::OPERATOR:
		push(c - 1);
		push(c);
		return States::AFTER_OPERATOR;

	case Chars::MINUS:
		push(c - 1);
		push(c);
		return States::AFTER_OPERATOR;

	case Chars::CLOSE_BRACKET:
		push(c - 1);
		push(c);
		return States::AFTER_CLOSE_BRACKET;

	default:
		return States::FAIL;

	}
}

int FSMValidator::firstPart(const char i, int c) {
	int type = findType(i);
	//std::cout << " /" << type << "/ ";
	switch (type)
	{

	case Chars::SPACE:
		push(c - 1);
		return States::END;

	case Chars::DECIMAL:
		return States::FIRST_PART;

	case Chars::DOT:
		return States::SECOND_PART;

	case Chars::OPERATOR:
		push(c - 1);
		push(c);
		return States::AFTER_OPERATOR;

	case Chars::MINUS:
		push(c - 1);
		push(c);
		return States::AFTER_OPERATOR;

	case Chars::CLOSE_BRACKET:
		push(c - 1);
		push(c);
		return States::AFTER_CLOSE_BRACKET;

	default:
		return States::FAIL;

	}

}

int FSMValidator::secondPart(const char i, int c) {
	int type = findType(i);
	//std::cout << " /" << type << "/ ";
	switch (type)
	{

	case Chars::SPACE:
		push(c - 1);
		return States::END;

	case Chars::OPERATOR:
		push(c - 1);
		push(c);
		return States::AFTER_OPERATOR;

	case Chars::MINUS:
		push(c - 1);
		push(c);
		return States::AFTER_OPERATOR;

	case Chars::DECIMAL:
		return States::SECOND_PART;

	case Chars::CLOSE_BRACKET:
		push(c - 1);
		push(c);
		return States::AFTER_CLOSE_BRACKET;

	default:
		return States::FAIL;

	}

}

int FSMValidator::afterCloseBracket(const char i, int c) {
	int type = findType(i);
	//std::cout << " /" << type << "/ ";
	switch (type)
	{

	case Chars::SPACE:
		return States::AFTER_CLOSE_BRACKET;

	case Chars::OPERATOR:
		push(c);
		return States::AFTER_OPERATOR;

	case Chars::MINUS:
		push(c);
		return States::AFTER_OPERATOR;

	default:
		return States::FAIL;

	}
}

int FSMValidator::end(const char i, int c) {
	int type = findType(i);
	//std::cout << " /" << type << "/ ";
	switch (type)
	{

	case Chars::SPACE:
		return States::END;

	case Chars::OPERATOR:
		push(c);
		return States::AFTER_OPERATOR;

	case Chars::MINUS:
		push(c);
		return States::AFTER_OPERATOR;

	case Chars::CLOSE_BRACKET:
		push(c);
		return States::AFTER_CLOSE_BRACKET;

	default:
		return States::FAIL;

	}
}

void FSMValidator::validate(const char* str, std::queue<int>& r) {

	if (!brackets(str)) {
		throw std::exception();
	}

	state = States::START;
	int i;
	int skip = 0;
	for (i = 0; str[i] != '\0'; i++) {

		switch (state)
		{
		case States::START:
			skip = isFunc(str + i, i);
			if (skip > 0) {
				std::cout << "skip";
				state = States::AFTER_OPERATOR;
				i += skip;
				skip = 0;
			}
			else
				state = start(str[i], i);
			break;

		case States::FIRST_PART:
			state = firstPart(str[i], i);
			break;

		case States::SECOND_PART:
			state = secondPart(str[i], i);
			break;

		case States::AFTER_OPERATOR:
			skip = isFunc(str + i, i);
			if (skip > 0) {
				//std::cout << "skip";
				state = States::AFTER_OPERATOR;
				i += skip;
				skip = 0;
			}
			else
				state = afterOperator(str[i], i);
			break;

		case States::END:
			state = end(str[i], i);
			break;

		case States::NAME:
			state = name(str[i], i);
			break;

		case States::AFTER_CLOSE_BRACKET:
			state = afterCloseBracket(str[i], i);
			break;

		case States::FAIL:
			throw std::exception();


		}
		//std::cout << state;
	}

	if (state == States::FIRST_PART || state == States::SECOND_PART || state == States::NAME)
		push(i - 1);

	if (state == States::AFTER_OPERATOR || state == States::FAIL) {
		throw std::exception();
	}

	r = res;


}
