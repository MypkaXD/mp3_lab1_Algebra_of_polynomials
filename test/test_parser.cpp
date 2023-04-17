#include "Polynom.h"
#include <gtest/gtest.h>

TEST(Polynom, can_read_polynom) {

	ASSERT_NO_THROW(Polynom p("12.2 1 1 1 41 2 2 0 .03 0 0 1"));
}

TEST(Polynom, can_read_polynom_correctly) {

	Polynom p("12.2 1 1 1 41 2 2 0 .03 0 0 1 0.8 1 1 1");

	p.print();

	SUCCEED();
}

TEST(Polynom, sums_polynoms_correctly) {

	Polynom p1("1 1 0 0 -2 0 1 0");
	Polynom p2("3 1 0 0 3 0 1 0");

	ASSERT_NO_THROW((p1 + p2).print());
}

TEST(Polynom, subs_polynoms_correctly) {

	Polynom p1("1 1 0 0 2 0 1 0");
	Polynom p2("3 1 0 0 3 0 1 0");

	ASSERT_NO_THROW((p1 - p2).print());
}

TEST(Polynom, muls_polynoms_correctly)
{
	Polynom p1("1 2 0 0 1 3 0 0");
	Polynom p2("1 2 0 0 1 3 0 0");
	ASSERT_NO_THROW((p1 * p2).print());
}

TEST(Polynom, divs_polynoms_correctly) {

	Polynom p1("1 2 0 0 2 1 0 0");
	Polynom p2("1 1 0 0");

	ASSERT_NO_THROW((p1 / p2).print());
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

	Polynom p1("1 2 0 0 3 3 0 0");
	Polynom p2("1 4 0 0 6 5 0 0 9 6 0 0");

	p1.pow_polinom(2);

	ASSERT_EQ(p1, p2);
}

TEST(Polynom, throw_if_power_less_than_zero) {

	Polynom p1("1 2 0 0 3 3 0 0");

	ASSERT_ANY_THROW(p1.pow_polinom(-1););
}

TEST(Polynom, if_power_eq_1_return_polynom_eq) {

	Polynom p1("1 2 0 0 3 3 0 0");
	Polynom p2("1 2 0 0 3 3 0 0");

	p1.pow_polinom(1);

	ASSERT_EQ(p1, p2);
}

TEST(Polynom, if_power_eq_0_return_1) {

	Polynom p1("1 2 0 0 3 3 0 0");
	Polynom p2("1 0 0 0");

	p1.pow_polinom(0);

	ASSERT_EQ(p1, p2);
}

TEST(Polynom, can_correctly_pow_v1) {

	Polynom p1("1 2 3 4 1 1 1 1");
	Polynom p2("1 4 6 8 2 3 4 5 1 2 2 2");

	p1.pow_polinom(2);

	p1.print();

	ASSERT_EQ(p1, p2);
}

TEST(Polynom, can_correctly_pow_v2) {

	Polynom p1("1 2 3 4 1 1 1 1");
	Polynom p2("1 6 9 12 3 5 7 9 3 4 5 6 1 3 3 3");

	p1.pow_polinom(3);

	p1.print();

	ASSERT_EQ(p1, p2);
}
