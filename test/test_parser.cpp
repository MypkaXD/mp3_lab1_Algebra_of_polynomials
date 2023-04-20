#include "Polynom.h"
#include <gtest/gtest.h>

TEST(Polynom, can_read_polynom) {

	ASSERT_NO_THROW(Polynom p("12.2 1 1 1 41 2 2 0 .03 0 0 1"));
}

TEST(Polynom, can_read_polynom_correctly) {

	Polynom p("-12.2x^1y^1z^1 41x^2y^2z^0 .03z^0z^1 0.8");

	p.print();

	SUCCEED();
}

TEST(Polynom, sums_polynoms_correctly) {

	Polynom p1("1x^1 -2z^1");
	Polynom p2("3x^1 3y^1");

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

	Polynom p1("12x^4y^15z^1 .4x^21y^1z^1 9.7x^0y^1z^0");
	Polynom p2("48x^3y^15z^1 8.4x^20y^1z^1 0x^0y^1z^0");
	
	p1.differentiationX();

	ASSERT_EQ(p1, p2);
}

TEST(Polynom, can_diff_Y) {

	Polynom p1("12x^4y^15z^1 .4x^21y^1z^1 9.7x^0y^1z^0");
	Polynom p2("180x^4y^14z^1 .4x^21y^0z^1 9.7x^0y^0z^0");

	p1.differentiationY();

	ASSERT_EQ(p1, p2);
}

TEST(Polynom, can_diff_Z) {

	Polynom p1("12x^4y^15z^1 .4x^21y^1z^1 9.7x^0y^1z^0");
	Polynom p2("12x^4y^15z^0 .4x^21y^1z^0 0x^0y^1z^0");

	p1.differentiationZ();

	ASSERT_EQ(p1, p2);
}

TEST(Polynom, can_intgr_X) {

	Polynom p1("12x^4y^15z^1 22x^21y^1z^1 9.7x^0y^1z^0");
	Polynom p2("2.4x^5y^15z^1 1x^22y^1z^1 9.7x^1y^1z^0");

	p1.integrationX();

	ASSERT_EQ(p1, p2);
}

TEST(Polynom, can_intgr_Y) {

	Polynom p1("12x^4y^11z^1 2x^21y^1z^1 5x^0y^4z^0");
	Polynom p2("1x^4y^12z^1 1x^21y^2z^1 1x^0y^5z^0");

	p1.integrationY();
	p1.print();

	ASSERT_EQ(p1, p2);
}

TEST(Polynom, can_intgr_Z) {

	Polynom p1("12x^4y^15z^1 2x^21y^1z^1 9.7x^0y^1z^0");
	Polynom p2("6x^4y^15z^2  1x^21y^1z^2 9.7x^0y^1z^1");

	p1.integrationZ();

	ASSERT_EQ(p1, p2);
}

TEST(Polynom, point_calculation_possible_v1) {

	Polynom p("12x^4y^15z^1 .4x^21y^1z^1 9.7x^0y^1z^0");

	ASSERT_EQ(22.1, p.point_calculation(1, 1, 1));
}

TEST(Polynom, point_calculation_possible_v2) {

	Polynom p("12x^4y^15z^1 .4x^21y^1z^1 9.7x^0y^1z^0");

	ASSERT_EQ(0, p.point_calculation(0, 0, 0));
}

TEST(Polynom, point_calculation_possible_v3) {

	Polynom p("0x^4y^15z^1 0x^21y^1z^1 0x^0y^1z^0");

	ASSERT_EQ(0, p.point_calculation(1, 1, 1));
}

TEST(Polynom, can_pow) {

	Polynom p1("1x^2y^0z^0 3x^3y^0z^0");
	Polynom p2("1x^4y^0z^0 6x^5y^0z^0 9x^6y^0z^0");

	p1.pow_polinom(2);

	ASSERT_EQ(p1, p2);
}

TEST(Polynom, throw_if_power_less_than_zero) {

	Polynom p1("1x^2y^0z^0 3x^3y^0z^0");

	ASSERT_ANY_THROW(p1.pow_polinom(-1););
}

TEST(Polynom, if_power_eq_1_return_polynom_eq) {

	Polynom p1("1x^2y^0z^0 3x^3y^0z^0");
	Polynom p2("1x^2y^0z^0 3x^3y^0z^0");

	p1.pow_polinom(1);

	ASSERT_EQ(p1, p2);
}

TEST(Polynom, if_power_eq_0_return_1) {

	Polynom p1("1x^2y^0z^0 3x^3y^0z^0");
	Polynom p2("1");

	p1.pow_polinom(0);

	ASSERT_EQ(p1, p2);
}
