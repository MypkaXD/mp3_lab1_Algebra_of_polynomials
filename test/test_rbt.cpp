#include "RBT.h"
#include <gtest/gtest.h>

int strComp2(std::string s1, std::string s2) {
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

TEST(RBT, can_push_in_empty_tree) {
	RBT<std::string, int> a(&strComp2);

	a.push("1", 10);

	SUCCEED();
}

TEST(RBT, pushing_many_elements_is_correct) {
	RBT<std::string, int> a(&strComp2);

	for (int count = 0; count < 10; ++count) {
		a.push(std::string(1, count), (rand() + count) % 12);
	}
	a.print();
	SUCCEED();
}

TEST(RBT, pushing_elements_is_balance) {
	RBT<std::string, int> a(&strComp2);

	a.push("30", 10);
	a.push("20", 12);
	a.push("10", 10);
	a.push("40", 12);
	a.push("60", 10);
	a.push("80", 12);
	a.push("50", 10);
	a.push("70", 12);
	
	//a.print();

	SUCCEED();
}

TEST(RBT, cant_find_element_in_empty_tree) {
	RBT<std::string, int> a(&strComp2);

	EXPECT_EQ(int(), a.find("10"));
}

TEST(RBT, cant_find_element_in_tree_if_element_is_out) {
	RBT<std::string, int> a(&strComp2);

	a.push("30", 10);
	a.push("20", 12);
	a.push("10", 10);
	a.push("40", 12);
	a.push("60", 10);
	a.push("80", 12);
	a.push("50", 10);
	a.push("70", 12);

	ASSERT_EQ(int(), a.find("11"));
}

TEST(RBT, can_find_element) {
	RBT<std::string, int> a(&strComp2);

	a.push("30", 10);
	a.push("20", 12);
	a.push("10", 10);
	a.push("40", 12);
	a.push("60", 10);
	a.push("80", 12);
	a.push("50", 10);
	a.push("70", 12);

	ASSERT_EQ(12, a.find("80"));
}

TEST(RBT, can_find_element_in_very_big_tree) {
	RBT<std::string, int> a(&strComp2);

	for (int count = 0; count < 255; ++count)
		a.push(std::string(1, count), count);

	//a.print();

	ASSERT_EQ(12, a.find(std::string(1, (char)12)));
}

TEST(RBT, can_get_min_elem) {
	RBT<std::string, int> a(&strComp2);

	for (int count = 1; count < 20; ++count)
		a.push(std::string(1, count), count);

	ASSERT_EQ(0, strComp2(a.get_min()->data.key, std::string(1, (char)1)));
}

TEST(RBT, can_get_max_elem) {
	RBT<std::string, int> a(&strComp2);

	for (int count = 1; count < 20; ++count)
		a.push(std::string(1, count), count);

	ASSERT_EQ(0, strComp2(a.get_max()->data.key, std::string(1, (char)19)));
}

TEST(RBT, cant_get_min_elem_in_empty_tree) {
	RBT<std::string, int> a(&strComp2);

	ASSERT_ANY_THROW(a.get_min());
}

TEST(RBT, cant_get_max_elem_in_empty_tree) {
	RBT<std::string, int> a(&strComp2);

	ASSERT_ANY_THROW(a.get_max());
}

TEST(RBT, many_methods_with_tree) {
	RBT<std::string, int> a(&strComp2);

	a.push("30", 10);
	a.push("20", 12);
	a.push("10", 10);
	a.push("40", 12);
	a.push("60", 10);
	a.push("80", 12);
	a.push("50", 10);
	a.push("70", 12);

	a.erase("30");
	a.erase("10");

	a.print();
	
	a.find("20");

	SUCCEED();
}

TEST(RBT, can_erase_root_from_tree) {
	RBT<std::string, int> a(&strComp2);

	a.push("1", 10);
	a.push("5", 12);
	a.push("6", 10);
	a.push("12", 12);
	a.push("15", 10);
	a.push("21", 12);
	a.push("23", 10);
	a.push("24", 12);

	a.erase("15");

	SUCCEED();
}

TEST(RBT, can_erase_from_tree) {
	RBT<std::string, int> a(&strComp2);

	a.push("1", 10);
	a.push("5", 12);
	a.push("6", 10);
	a.push("12", 12);
	a.push("15", 10);
	a.push("21", 12);
	a.push("23", 10);
	a.push("24", 12);

	a.erase("21");

	SUCCEED();
}

TEST(RBT, can_erase_leaf_from_tree) {
	RBT<std::string, int> a(&strComp2);

	a.push("1", 10);
	a.push("5", 12);
	a.push("6", 10);
	a.push("12", 12);
	a.push("15", 10);
	a.push("21", 12);
	a.push("23", 10);
	a.push("24", 12);

	a.erase("1");

	SUCCEED();
}

TEST(RBT, can_erase_leaf_from_tree_with_two_children) {
	RBT<std::string, int> a(&strComp2);

	a.push("1", 10);
	a.push("5", 12);
	a.push("6", 10);
	a.push("12", 12);
	a.push("15", 10);
	a.push("21", 12);
	a.push("23", 10);
	a.push("24", 12);

	a.erase("6");

	SUCCEED();
}

TEST(RBT, erasing_elem_from_empty_tree_does_nothing) {
	RBT<std::string, int> a(&strComp2);

	ASSERT_NO_THROW(a.erase("1"));
}
