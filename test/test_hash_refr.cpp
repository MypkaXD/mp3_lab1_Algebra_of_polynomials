#include "HashRefresh.h"
#include <gtest/gtest.h>

TEST(HASH, refresh_can_push_into_empty_table) {
	HashRefresh<int> hc;
	hc.push("1", 1);
	std::cout << "expected: 1 1\n";
	hc.print();
	SUCCEED();
}

TEST(HASH, refresh_can_push_multiple_elements_correctly) {
	HashRefresh<int> hc;
	hc.push("1", 1);
	hc.push("1", 2);
	hc.push("2", 3);
	hc.push("3", 4);
	std::cout << "expected: 1 2 | 2 3 | 3 4\n";
	hc.print();
	SUCCEED();
}



TEST(HASH, refresh_cant_find_element_in_empty_table) {
	HashRefresh<int> hc;
	EXPECT_EQ(hc.find("1"), int());
}

TEST(HASH, refresh_can_find_added_element) {
	HashRefresh<int> hc;
	hc.push("1", 1);
	EXPECT_EQ(hc.find("1"), 1);
}


TEST(HASH, refresh_can_find_element_with_collided_HASH) {
	HashRefresh<int> hc;
	hc.push("+", 1);         //43
	hc.push("122", 2);       //43
	std::cout << hc.hash("+") << " " << hc.hash("122");
	EXPECT_EQ(hc.find("122"), 2);
}

TEST(HASH, refresh_can_erase_not_collided_hash_correctly) {
	HashRefresh<int> hc;
	hc.push("+", 1);
	hc.erase("+");
	std::cout << "expected: empty\n";
	hc.print();
	SUCCEED();
}

TEST(HASH, refresh_can_erase_collided_hash_correctly) {
	HashRefresh<int> hc;
	hc.push("+", 1);
	hc.push("122", 2);
	hc.erase("122");
	std::cout << "expected: + 1\n";
	hc.print();
	SUCCEED();
}
