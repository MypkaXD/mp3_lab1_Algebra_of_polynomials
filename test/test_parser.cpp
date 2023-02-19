#include "Polynom.h"
#include <gtest.h>

TEST(Polynom, can_read_polynom) 
{

	ASSERT_NO_THROW(Polynom p("12.2 1 1 1 41 2 2 0 .03 0 0 1"));


}

TEST(Polynom, can_read_polynom_correctly)
{

	Polynom p("12.2 1 1 1 41 2 2 0 .03 0 0 1 0.8 1 1 1");
	p.print();
	SUCCEED();

}

TEST(Polynom, sums_polynoms_correctly)
{
	Polynom p1("1 1 0 0 -2 0 1 0");
	Polynom p2("3 1 0 0 3 0 1 0");
	ASSERT_NO_THROW((p1 + p2).print());

}

TEST(Polynom, subs_polynoms_correctly)
{
	Polynom p1("1 1 0 0 2 0 1 0");
	Polynom p2("3 1 0 0 3 0 1 0");
	ASSERT_NO_THROW((p1 - p2).print());

}

TEST(Polynom, muls_polynoms_correctly)
{
	Polynom p1("1 2 0 0 3 3 0 0");
	Polynom p2("1 2 0 0 3 3 0 0");
	ASSERT_NO_THROW((p1 * p2).print());

}

TEST(Polynom, divs_polynoms_correctly)
{
	Polynom p1("1 2 0 0 2 1 0 0");
	Polynom p2("1 1 0 0");
	ASSERT_NO_THROW((p1 / p2).print());

}
