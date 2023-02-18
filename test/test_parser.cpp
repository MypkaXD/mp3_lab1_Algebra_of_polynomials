#include "Polynom.h"
#include <gtest.h>

TEST(Polynom, can_read_polynom) {

	ASSERT_NO_THROW(Polynom p("12.2 1 1 1 41 2 2 0 .03 0 0 1"));

}

TEST(Polynom, can_read_polynom_correctly){

	Polynom p("12.2 1 1 1 41 2 2 0 .03 0 0 1 0.8 1 1 1");

	//p.print();

	SUCCEED();

}

TEST(Polynom, can_diff_X) {

	Polynom p1("12 4 15 1 .4 21 1 1 9.7 0 1 0");
	Polynom p2("12 3 15 1 .4 20 1 1 9.7 0 1 0");
	
	p1.differentiationX();
	
	ASSERT_EQ(p1, p2);
}

TEST(Polynom, can_diff_Y) {

	Polynom p1("12 4 15 1 .4 21 1 1 9.7 0 1 0");
	Polynom p2("12 4 14 1 .4 21 0 1 9.7 0 0 0");

	p1.differentiationY();

	ASSERT_EQ(p1, p2);
}

TEST(Polynom, can_diff_Z) {

	Polynom p1("12 4 15 1 .4 21 1 1 9.7 0 1 0");
	Polynom p2("12 4 15 0 .4 21 1 0 9.7 0 1 0");

	p1.differentiationZ();

	ASSERT_EQ(p1, p2);
}

TEST(Polynom, can_intgr_X) {

	Polynom p1("12 4 15 1 .4 21 1 1 9.7 0 1 0");
	Polynom p2("12 5 15 1 .4 22 1 1 9.7 1 1 0");

	p1.integrationX();

	ASSERT_EQ(p1, p2);
}

TEST(Polynom, can_intgr_Y) {

	Polynom p1("12 4 15 1 .4 21 1 1 9.7 0 1 0");
	Polynom p2("12 4 16 1 .4 21 2 1 9.7 0 2 0");

	p1.integrationY();

	ASSERT_EQ(p1, p2);
}

TEST(Polynom, can_intgr_Z) {

	Polynom p1("12 4 15 1 .4 21 1 1 9.7 0 1 0");
	Polynom p2("12 4 15 2 .4 21 1 2 9.7 0 1 1");

	p1.integrationZ();

	ASSERT_EQ(p1, p2);
}

TEST(Polynom, point_calculation_possible_v1) {

	Polynom p("12 4 15 1 .4 21 1 1 9.7 0 1 0");

	ASSERT_EQ(22.1, p.point_calculation(1, 1, 1));
}

TEST(Polynom, point_calculation_possible_v2) {

	Polynom p("12 4 15 1 .4 21 1 1 9.7 0 1 0");

	ASSERT_EQ(0, p.point_calculation(0, 0, 0));
}

TEST(Polynom, point_calculation_possible_v3) {

	Polynom p("0 4 15 1 0 21 1 1 0 0 1 0");

	ASSERT_EQ(0, p.point_calculation(1, 1, 1));
}

TEST(Polynom, can_pow) {

	Polynom p1("12 4 15 1 .4 21 1 1 9.7 0 1 0");
	Polynom p2("12 12 45 3 .4 63 3 3 9.7 0 3 0");

	p1.powPolynom(3);

	ASSERT_EQ(p1, p2);
}

TEST(Polynom, trow_if_pow_less_than_0) {

	Polynom p1("12 4 15 1 .4 21 1 1 9.7 0 1 0");

	ASSERT_ANY_THROW(p1.powPolynom(-1));
}