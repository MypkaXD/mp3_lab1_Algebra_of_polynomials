#include "HashChain.h"
#include <gtest/gtest.h>

TEST(HASH, chain_can_push_into_empty_table) {
	HashChain<int> hc;
	hc.push("1", 1);
	std::cout << "expected: 1 1\n";
	hc.print();
	SUCCEED();
}

TEST(HASH, chain_can_push_multiple_elements_correctly) {
	HashChain<int> hc;
	hc.push("1", 1);
	hc.push("1", 2);
	hc.push("2", 3);
	hc.push("3", 4);
	std::cout << "expected: 1 2 | 2 3 | 3 4\n";
	hc.print();
	SUCCEED();
}



TEST(HASH, chain_cant_find_element_in_empty_table) {
	HashChain<int> hc;
	EXPECT_EQ(hc.find("1"), int());
}

TEST(HASH, chain_can_find_added_element) {
	HashChain<int> hc;
	hc.push("1", 1);
	EXPECT_EQ(hc.find("1"), 1);
}


TEST(HASH, chain_can_find_element_with_collided_HASH) {
	HashChain<int> hc;
	hc.push("+", 1);         //43
	hc.push("122", 2);       //43
	std::cout << hc.hash("+") << " " << hc.hash("122");
	EXPECT_EQ(hc.find("122"), 2);
}

TEST(HASH, chain_can_erase_not_collided_hash_correctly) {
	HashChain<int> hc;
	hc.push("+", 1);
	hc.erase("+");
	std::cout << "expected: empty\n";
	hc.print();
	SUCCEED();
}

TEST(HASH, chain_can_erase_collided_hash_correctly) {
	HashChain<int> hc;
	hc.push("+", 1);
	hc.push("122", 2);
	hc.erase("122");
	std::cout << "expected: + 1\n";
	hc.print();
	SUCCEED();
}

