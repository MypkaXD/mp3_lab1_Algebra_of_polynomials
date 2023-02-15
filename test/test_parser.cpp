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

