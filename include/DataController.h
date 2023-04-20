#pragma once
#include "AVL.h"
#include "HashChain.h"
#include "HashRefresh.h"
#include "MapOnList.h"
#include "OrderedMap.h"
#include "UnorderedMap.h"
#include "Polynom.h"
#include "Expression.h"
#include <string>

int strComp(std::string s1, std::string s2) {
	if (s1.size() > s2.size())
		return 1;
	if (s1.size() < s2.size())
		return -1;
	for (int i = 0; i < s1.size(); i++) {
		if ((int)s1[i] > (int)s2[i])
			return 1;
		if ((int)s1[i] < (int)s2[i])
			return -1;
	}
	return 0;
}


class DataController {

	AVL<std::string, Polynom> avl = AVL<std::string, Polynom>(&strComp);
	OrderedMap<std::string, Polynom> om = OrderedMap<std::string, Polynom>(&strComp);
	HashChain<Polynom> hc;
	HashRefresh<Polynom> hr;
	MapOnList<std::string, Polynom> mol = MapOnList<std::string, Polynom>(&strComp);
	UnorderedMap<std::string, Polynom> um = UnorderedMap<std::string, Polynom>(&strComp);

	enum BDModes {
		AVLm,
		OM,
		HC,
		HR,
		MOL,
		UM
	};

	int readMode;

public:

	DataController() {
		readMode = BDModes::AVLm;
	}

	

	bool strStartCmp(std::string str1, std::string str2) {
		int i = 0;
		while (str1[i] != '\0' && str2[i] != '\0') {
			if (str1[i] != str2[i])
				return false;
			i++;
		}
		return true;
	}

	int firstDigitAt(const char* s) {
		for (int i = 0; s[i] != '\0'; i++) {
			if ((int)s[i] > 47 || (int)s[i] < 58 || s[i] == '-')
				return i;
		}
		return -1;
	}

	bool nameValidator(const char* s) {
		for (char i : lit) {
			if (i == s[0]) {
				return true;
			}
		}
		return false;
	}

	//1) parse polynom "enter PolynomName 12x^12y^4z^0 +3x^6y^1z^0"
	//2) calculate "calculate PolynomNameToStoreResult P1 + P2 / 12"
	//3) switch database read mode "mode AVL"
	void parseQuery(const char* query) {

		if      (strStartCmp(query, "enter ")) {

			int firstSpace = 5;
			while (query[firstSpace + 1] == ' ') {
				firstSpace++;
				if (query[firstSpace] == '\0')
					throw std::exception("invalid input");
			}
			int secondSpace = firstSpace + 1;
			while (query[secondSpace] != ' ') {
				secondSpace++;
			}

			if (!nameValidator(query + firstSpace + 1))
				throw std::exception("invalid input");

			Polynom p(query + secondSpace + firstDigitAt(query + secondSpace));
			std::string name(query + firstSpace + 1);
			avl.push(name.substr(0, secondSpace - firstSpace - 1), p);
			om.push(name.substr(0, secondSpace - firstSpace - 1), p);
			um.push(name.substr(0, secondSpace - firstSpace - 1), p);
			mol.push(name.substr(0, secondSpace - firstSpace - 1), p);
			hc.push(name.substr(0, secondSpace - firstSpace - 1), p);
			hr.push(name.substr(0, secondSpace - firstSpace - 1), p);

		}
		else if (strStartCmp(query, "calculate ")) {

			Polynom r;
			Expression e(query + 10);
			switch (readMode) {

			case BDModes::AVLm:
				r = e.calculate(avl);
				break;

			case BDModes::UM:
				r = e.calculate(um);
				break;

			case BDModes::OM:
				r = e.calculate(om);
				break;

			case BDModes::HC:
				r = e.calculate(hc);
				break;

			case BDModes::HR:
				r = e.calculate(hr);
				break;

			case BDModes::MOL:
				r = e.calculate(mol);
				break;

			}
			r.print();
			std::cout << std::endl;

		}
		else if (strStartCmp(query, "mode ")) {
			if (strStartCmp(query + 5, "Unordered Map"))
				readMode = BDModes::UM;
			else if (strStartCmp(query + 5, "Ordered Map"))
				readMode = BDModes::OM;
			else if (strStartCmp(query + 5, "Map On List"))
				readMode = BDModes::MOL;
			else if (strStartCmp(query + 5, "AVL"))
				readMode = BDModes::AVLm;
			else if (strStartCmp(query + 5, "Hash Refresh"))
				readMode = BDModes::HR;
			else if (strStartCmp(query + 5, "Hash Chain"))
				readMode = BDModes::HC;
			else
				throw std::exception("invalid input");
			std::cout << "\nMode changed\n";
		}

	}

};




