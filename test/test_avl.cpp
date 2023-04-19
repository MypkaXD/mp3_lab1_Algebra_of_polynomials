#include "AVL.h"
#include <gtest/gtest.h>


int strComp1(std::string s1, std::string s2) {
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

TEST(AVL, can_push_in_empty_tree) {
	AVL<std::string, int> a(&strComp1);

	a.push("1", 10);

	SUCCEED();
}

TEST(AVL, pushing_many_elements_is_correct) {
	AVL<std::string, int> a(&strComp1);

	for (int count = 0; count < 10; ++count) {
		a.push(std::string(1, (char)count), (rand() + count) % 12);
	}

	SUCCEED();
}

TEST(AVL, pushing_elements_is_balance_v1) {
	AVL<std::string, int> a(&strComp1);

	a.push("30", 10);
	a.push("20", 12);
	a.push("10", 10);
	a.push("40", 12);
	a.push("60", 10);
	a.push("80", 12);
	a.push("50", 10);
	a.push("70", 12);

	SUCCEED();
}

TEST(AVL, pushing_elements_is_balance_v2) {
	AVL<std::string, int> a(&strComp1);

	a.push("1", 10);
	a.push("5", 12);
	a.push("6", 10);
	a.push("12", 12);
	a.push("15", 10);
	a.push("21", 12);
	a.push("23", 10);
	a.push("24", 12);

	SUCCEED();
}

TEST(AVL, cant_find_element_in_empty_tree) {
	AVL<std::string, int> a(&strComp1);

	EXPECT_EQ(int(), a.find("10"));
}

TEST(AVL, cant_find_element_in_tree_if_element_is_out) {
	AVL<std::string, int> a(&strComp1);

	a.push("1", 10);
	a.push("5", 12);
	a.push("6", 10);
	a.push("12", 12);
	a.push("15", 10);
	a.push("21", 12);
	a.push("23", 10);
	a.push("24", 12);

	ASSERT_EQ(int(), a.find("11"));
}

TEST(AVL, can_find_element) {
	AVL<std::string, int> a(&strComp1);

	a.push("1", 10);
	a.push("5", 12);
	a.push("6", 10);
	a.push("12", 12);
	a.push("15", 10);
	a.push("21", 12);
	a.push("23", 10);
	a.push("24", 12);

	ASSERT_EQ(12, a.find("21"));
}

TEST(AVL, can_find_element_in_very_big_tree) {
	AVL<std::string, int> a(&strComp1);

	for (int count = 0; count < 255; ++count)
		a.push(std::string(1, count), count);

	//a.print();

	ASSERT_EQ(12, a.find(std::string(1, (char)12)));
}
/*
TEST(AVL, can_find_element_in_very_huge_tree) {
	AVL<int, int> a;

	for (int count = 0; count < 10000; ++count)
		a.push(count, count);

	ASSERT_EQ(12, *a.find(12));
	ASSERT_EQ(13, *a.find(13));
	ASSERT_EQ(14, *a.find(14));
	ASSERT_EQ(15, *a.find(15));
	ASSERT_EQ(16, *a.find(16));
	ASSERT_EQ(17, *a.find(17));
	ASSERT_EQ(18, *a.find(18));
	ASSERT_EQ(19, *a.find(19));
	ASSERT_EQ(20, *a.find(20));
	ASSERT_EQ(21, *a.find(21));
	ASSERT_EQ(22, *a.find(22));
	ASSERT_EQ(23, *a.find(23));
	ASSERT_EQ(24, *a.find(24));
	ASSERT_EQ(25, *a.find(25));
	ASSERT_EQ(26, *a.find(26));
}
*/

TEST(AVL, can_get_min_elem) {
	AVL<std::string, int> a(&strComp1);

	for (int count = 1; count < 20; ++count)
		a.push(std::string(1, count), count);

	ASSERT_EQ(1, a.get_min()->m_data.m_elem);
}

TEST(AVL, can_get_max_elem) {
	AVL<std::string, int> a(&strComp1);

	for (int count = 1; count < 20; ++count)
		a.push(std::string(1, count), count);

	ASSERT_EQ(19, a.get_max()->m_data.m_elem);
}

TEST(AVL, cant_get_min_elem_in_empty_tree) {
	AVL<std::string, int> a(&strComp1);

	ASSERT_ANY_THROW(a.get_min());
}

TEST(AVL, cant_get_max_elem_in_empty_tree) {
	AVL<std::string, int> a(&strComp1);

	ASSERT_ANY_THROW(a.get_max());
}

TEST(AVL, print_tree_is_correct) {
	AVL<std::string, int> a(&strComp1);

	a.push("1", 10);
	a.push("5", 12);
	a.push("6", 10);
	a.push("12", 12);
	a.push("15", 10);
	a.push("21", 12);
	a.push("23", 10);
	a.push("24", 12);

	a.print();
	
	SUCCEED();
}

TEST(AVL, many_methods_with_tree) {
	AVL<std::string, int> a(&strComp1);

	a.push("1", 10);
	a.push("5", 12);
	a.push("6", 10);
	a.push("12", 12);
	a.push("15", 10);
	a.push("21", 12);
	a.push("23", 10);
	a.push("24", 12);

	a.print();

	a.erase("1");
	a.erase("5");
	a.erase("12");
	a.erase("15");
	a.erase("21");

	a.print();

	a.find("24");

	SUCCEED();
}

TEST(AVL, can_erase_root_from_tree) {
	AVL<std::string, int> a(&strComp1);

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

TEST(AVL, can_erase_from_tree) {
	AVL<std::string, int> a(&strComp1);
	
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

TEST(AVL, can_erase_leaf_from_tree) {
	AVL<std::string, int> a(&strComp1);

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

TEST(AVL, can_erase_leaf_from_tree_with_two_children) {
	AVL<std::string, int> a(&strComp1);

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

TEST(AVL, erasing_elem_from_empty_tree_does_nothing) {
	AVL<std::string, int> a(&strComp1);
	a.erase("1");
	a.print();
	SUCCEED();
}