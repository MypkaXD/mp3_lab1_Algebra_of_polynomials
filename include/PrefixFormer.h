#pragma once
#include "Enums.h"



class PFormer {
private:
	
	std::queue<Token> pForm;
	std::stack<Token> operators;

public:

	PFormer();
	void buildPrefix(const char* str, std::queue<int>& iForm);
	bool empty();
	Token getNext();
	int tokenType(const char* ptr, int len);

};


PFormer::PFormer() {}

int PFormer::tokenType(const char* ptr, int len) { //for variables, functions and numbers
	
	for (char b : dec) {
		if (b == ptr[0])
			return TokenId::NUMBER;
	}
	if (dot[0] == ptr[0])
		return TokenId::NUMBER;
	
	int i;
	for (i = 0; i < len; i++) {
		if (ptr[i] != name_log[i]) {
			break;
		}
	}
	//std::cout << len;
	if (i == len)
		return TokenId::LOG;

	for (i = 0; i < len; i++) {
		if (ptr[i] != name_exp[i]) {
			break;
		}
	}
	if (i == len)
		return TokenId::EXP;

	for (i = 0; i < len; i++) {
		if (ptr[i] != name_sin[i]) {
			break;
		}
	}
	if (i == len)
		return TokenId::SIN;

	return TokenId::VAR;
}

bool PFormer::empty() {
	return pForm.empty();
}

Token PFormer::getNext() {
	Token a = pForm.front();
	pForm.pop();
	return a;
}

void PFormer::buildPrefix(const char* str, std::queue<int>& iForm) {

	bool start = true;                                           //tracking unary minus
	if (iForm.empty()) {
		return;
	}
	for (int i = iForm.front(); true; i = iForm.front()) {
		//std::cout << i;
		iForm.pop();

		switch (str[i])
		{

		case '(':
			//std::cout << "case (\n";
			operators.push(Token(TokenId::OP_B, TokenPrio::BRACKET_));
			start = true;
			break;

		case ')':
			//std::cout << "case )\n";
			for (Token j = operators.top(); j.prio != TokenPrio::BRACKET_; j = operators.top()) {
				operators.pop();
				pForm.push(j);
				if (operators.empty())
					break;
			}
			operators.pop();
			break;

		case '+':
			//std::cout << "case +\n";
			if (!operators.empty() && operators.top().prio > TokenPrio::SUM_) {
				for (Token j = operators.top(); j.prio > TokenPrio::SUM_; j = operators.top()) {
					operators.pop();
					pForm.push(j);
					if (operators.empty())
						break;
				}
			}
			operators.push(Token(TokenId::PLS, TokenPrio::SUM_, str + i, 1));
			break;

		case '-':
			//std::cout << "case -\n";
			if (start) {
				operators.push(Token(TokenId::U_MIN, TokenPrio::UNARY_OPERATOR_, str + i, 1));
				start = false;
				break;
			}

			if (!operators.empty() && operators.top().prio > TokenPrio::SUM_) {
				for (Token j = operators.top(); j.prio > TokenPrio::SUM_; j = operators.top()) {
					operators.pop();
					pForm.push(j);
					if (operators.empty())
						break;
				}
			}

			operators.push(Token(TokenId::MIN, TokenPrio::SUM_, str + i, 1));
			break;

		case '*':
			//std::cout << "case *\n";
			if (!operators.empty() && operators.top().prio > TokenPrio::MUL_) {
				for (Token j = operators.top(); j.prio > TokenPrio::MUL_; j = operators.top()) {
					operators.pop();
					pForm.push(j);
					if (operators.empty())
						break;
				}
			}
			operators.push(Token(TokenId::MUL, TokenPrio::MUL_, str + i, 1));
			break;

		case '/':
			//std::cout << "case /\n";
			if (!operators.empty() && operators.top().prio > TokenPrio::MUL_) {
				for (Token j = operators.top(); j.prio > TokenPrio::MUL_; j = operators.top()) {
					operators.pop();
					pForm.push(j);
					if (operators.empty())
						break;
				}
			}
			operators.push(Token(TokenId::DIV, TokenPrio::MUL_, str + i, 1));
			break;

		default:                                                                  //only numbers and names
			//std::cout << "case number\n";
			int tType = tokenType(str + i, iForm.front() - i + 1);
			if(tType == TokenId::NUMBER || tType == TokenId::VAR)
				pForm.push(Token(tType, TokenPrio::NAME_, str + i, iForm.front() - i + 1));
			else
				operators.push(Token(tType, TokenPrio::UNARY_OPERATOR_, str + i, iForm.front() - i + 1));
			
			//std::cout << iForm.front();
			start = false;
			iForm.pop();
			break;

		}
		if (iForm.empty())
			break;
	}

	if (!operators.empty())
		for (Token j = Token(1, 1); !operators.empty(); ) {
			j = operators.top();
			operators.pop();
			pForm.push(j);
		}

}

