#include "AVL.h"
#include "HashChain.h"
#include "HashRefresh.h"
#include "MapOnList.h"
#include "OrderedMap.h"
#include "UnorderedMap.h"
#include "Polynom.h"
#include "Expression.h"
#include <string>


//todo: remaster parser at Polynom.h
//parseQuery function 
//interconnect expression with the database


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

	AVL<std::string, Polynom> avl;
	OrderedMap<std::string, Polynom> om;
	HashChain<Polynom> hc;
	HashRefresh<Polynom> hr;
	MapOnList<std::string, Polynom> mol;
	UnorderedMap<std::string, Polynom> um;

	enum DBModes {
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
		readMode = AVLm;
		avl = AVL<std::string, Polynom>(&strComp);
		om = OrderedMap<std::string, Polynom>(&strComp);
		mol = MapOnList<std::string, Polynom>(&strComp);
		um = UnorderedMap<std::string, Polynom>(&strComp);
	}

	

	bool strStartCmp(const char* str1, const char* str2) {
		int i = 0;
		while (str1[i] != '\0' && str2[i] != '\0') {
			if (str1[i] != str2[i])
				return false;
		}
		return true;
	}

	int firstDigitAt(const char* s) {
		for (int i = 0; s[i] != '\0'; i++) {
			if ((int)s[i] > 47 || (int)s[i] < 58)
				return i;
		}
		return -1;
	}

	//1) parse polynom "enter PolynomName 12x^12y^4z^0 +3x^6y^1z^0"
	//2) calculate "calculate P1 + P2 / 12"
	//3) switch database read mode "mode avl"
	typename const char* parseQuery(const char* query) {

		if      (strStartCmp(query, "enter ")) {

			int firstSpace = 6;
			while (query[firstSpace] != ' ') {
				firstSpace++;
				if (query[firstSpace] == '\0')
					throw std::exception("invalid input");
			}


			Polynom p(query + firstDigitAt(query + firstSpace + 1));
			std::string name(query + 6);
			avl.push(name.substr(0, firstSpace), p);

		}
		else if (strStartCmp(query, "calculate ")) {

		}
		else if (strStartCmp(query, "mode ")) {

		}

	}

};




