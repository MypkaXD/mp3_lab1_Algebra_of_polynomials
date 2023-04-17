#pragma once
#include <math.h>
#include "FiniteStateMachineValidator.h"
#include "PrefixFormer.h"


class Expression
{
private:

	const char* source;
	FSMValidator fsmv;
	PFormer pf;

public:

	Expression();
	Expression(const char* s);
	double calculate();
	static double parseNumber(Token number);
	double ask(Token& name);

};

Expression::Expression() : source(nullptr){}

Expression::Expression(const char* s) : source(s) {
	std::queue<int> tokens;
	fsmv.validate(s, tokens);
	pf.buildPrefix(s, tokens);
}

double Expression::ask(Token& name) {
	double r;
	std::cout << "Enter a value of: ";
	for (int i = 0; i < name.len; i++) {
		std::cout << name.val[i];
	}
	std::cout << '\n';
	std::cin >> r;
	return r;
}

double Expression::parseNumber(Token number) {

	double res = 0;
	int dot;
	for (dot = 0; dot < number.len; dot++)
		if (number.val[dot] == '.')
			break;

	double pow = 1;
	for (int i = dot - 1; i >= 0; i--) {
		res += ((unsigned long long)number.val[i] - 48) * pow;
		pow *= 10.0;
	}

	pow = 0.1;
	for (int i = dot + 1; i < number.len; i++) {
		res += ((unsigned long long)number.val[i] - 48) * pow;
		pow /= 10;
	}

	return res;

}

double Expression::calculate() {

	std::stack<double> numbers;
	Token cur;
	double b;
	double a;
	while (!pf.empty()) {
		cur = pf.getNext();
		//std::cout << cur.id;
		switch (cur.id)
		{

		case TokenId::VAR:
			numbers.push(ask(cur));
			break;

		case TokenId::NUMBER:
			numbers.push(parseNumber(cur));
			break;

		case TokenId::PLS:
			b = numbers.top();
			numbers.pop();
			a = numbers.top();
			numbers.pop();
			numbers.push(a + b);
			break;

		case TokenId::MIN:
			b = numbers.top();
			numbers.pop();
			a = numbers.top();
			numbers.pop();
			numbers.push(a - b);
			break;

		case TokenId::MUL:
			b = numbers.top();
			numbers.pop();
			a = numbers.top();
			numbers.pop();
			numbers.push(a * b);
			break;

		case TokenId::DIV:
			b = numbers.top();
			numbers.pop();
			a = numbers.top();
			numbers.pop();
			if (b == 0)
				throw std::exception("divide by zero");
			numbers.push(a / b);
			break;

		case TokenId::U_MIN:
			b = numbers.top();
			numbers.pop();
			numbers.push(-b);
			break;

		case TokenId::SIN:
			b = numbers.top();
			numbers.pop();
			numbers.push(std::sin(b));
			break;

		case TokenId::LOG:
			b = numbers.top();
			numbers.pop();
			numbers.push(std::log(b));
			break;

		case TokenId::EXP:
			b = numbers.top();
			numbers.pop();
			numbers.push(std::exp(b));
			break;

		}
		//std::cout << numbers.size();
	}

	return numbers.top();

}
