#include <gtest/gtest.h>
#include "DataController.h"

TEST(commands, can_initialize) {
	DataController dc;
}

TEST(commands, can_write_polynom) {
	DataController dc;
	ASSERT_NO_THROW(dc.parseQuery("enter p1 -12.2x^1y^1z^1 41x^2y^2z^0 .03z^0z^1 0.8"));
}

TEST(commands, can_write_polynom_and_read_it) {
	DataController dc;
	dc.parseQuery("enter p1 -12.2x^1y^1z^1 41x^2y^2z^0 .03z^0z^1 0.8");
	ASSERT_NO_THROW(dc.parseQuery("calculate p1"));
}

TEST(commands, enter_without_name_throws) {
	DataController dc;
	ASSERT_ANY_THROW(dc.parseQuery("enter -12.2x^1y^1z^1 41x^2y^2z^0 .03z^0z^1 0.8"));
}

TEST(commands, expressions_with_polynoms_work_correctly) {
	DataController dc;
	dc.parseQuery("enter p1 -12.2x^1y^1z^1 41x^2y^2z^0 .03z^0z^1 0.8");
	dc.parseQuery("enter p2 2x^1y^1z^1 4x^2y^2z^0 1z^0z^1 0.8");
	dc.parseQuery("enter p3 41");
	ASSERT_NO_THROW(dc.parseQuery("calculate p1 - p2 * p3"));
}

TEST(commands, expressions_with_polynoms_work_correctly_with_every_table) {
	DataController dc;
	dc.parseQuery("enter p1 -12.2x^1y^1z^1 41x^2y^2z^0 .03z^0z^1 0.8");
	dc.parseQuery("enter p2 2x^1y^1z^1 4x^2y^2z^0 1z^0z^1 0.8");
	dc.parseQuery("enter p3 41");
	dc.parseQuery("mode Unordered Map");
	dc.parseQuery("calculate p1 - p2 * p3");
	std::cout << '\n';
	dc.parseQuery("mode Ordered Map");
	dc.parseQuery("calculate p1 - p2 * p3");
	std::cout << '\n';
	dc.parseQuery("mode Map On List");
	dc.parseQuery("calculate p1 - p2 * p3");
	std::cout << '\n';
	dc.parseQuery("mode AVL");
	dc.parseQuery("calculate p1 - p2 * p3");
	std::cout << '\n';
	dc.parseQuery("mode Hash Refresh");
	dc.parseQuery("calculate p1 - p2 * p3");
	std::cout << '\n';
	dc.parseQuery("mode Hash Chain");
	dc.parseQuery("calculate p1 - p2 * p3");
	std::cout << '\n';
	SUCCEED();
}
