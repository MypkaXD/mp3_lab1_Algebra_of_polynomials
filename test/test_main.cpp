#include <gtest.h>
#include <string>
#include <iostream>
#include <initializer_list>
#include <gtest.h>
#include "Forward_List.h"

int main(int argc, char** argv)
{

	List<int> l1;
	for (int count = 0; count < 10; ++count) {
		l1.push_front(count);
	}
	l1.print();
	std::cout << std::endl;
	l1.sort();
	l1.print();

	//::testing::InitGoogleTest(&argc, argv);
	//return RUN_ALL_TESTS();

	//test
}