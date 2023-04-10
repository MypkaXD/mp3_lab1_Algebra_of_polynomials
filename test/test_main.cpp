#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <initializer_list>
#include "Forward_List.h"

#include "AVL.h"

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}