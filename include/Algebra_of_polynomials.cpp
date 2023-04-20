#include "DataController.h"

int main(int argc, char** argv) {

	DataController dc;
	std::string s;

	while (true) {
		std::cin >> s;
		std::cout << std::endl;
		if (dc.strStartCmp(s, "end"))
			break;
		dc.parseQuery(s.c_str());
	}

	return 0;
}

