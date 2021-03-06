#include "stdafx.h"

#include "../EquationRoot4/Solve4Facade.h"


BOOST_AUTO_TEST_SUITE(Equation)

	BOOST_AUTO_TEST_CASE(could_not_have_null_first_coefficient)
	{
		BOOST_REQUIRE_THROW(CSolve4Facade(0, 1, 13, 1, 3), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(could_have_all_imaginary_roots)
	{
		BOOST_REQUIRE_THROW(CSolve4Facade(1, 1, 1, 1, 1), std::domain_error);
	}


	BOOST_AUTO_TEST_CASE(could_have_all_real_roots)
	{
		{ //s<0
			CSolve4Facade equation(2, 5, -11, -20, 12);
			BOOST_CHECK(equation.GetNumRoots() == 4);
			double roots[4] = {-3, 2, -2, 0.5};
			BOOST_CHECK(*equation.GetRoots() == *roots);
		}

		{//s>0
			CSolve4Facade equation(1, 4, -4, -20, -5);
			BOOST_CHECK(equation.GetNumRoots() == 4);
			double roots[4] = {-3.7320508075688781, 2.2360679774997902, -2.2360679774997889, -0.26794919243112347};
			BOOST_CHECK(*equation.GetRoots() == *roots);
		}
	}
	
	BOOST_AUTO_TEST_CASE(could_have_two_real_roots)
	{
		{
			CSolve4Facade equation(7, 9, 1, 2, 2);
			BOOST_CHECK(equation.GetNumRoots() == 2);
			double roots[4] = {-1.1996765912015668, -0.62757306265855406, static_cast<double>(0), static_cast<double>(0)};
			BOOST_CHECK(*equation.GetRoots() == *roots);
		}

		{
			CSolve4Facade equation(1, 2, 7, 9, 2);
			BOOST_CHECK(equation.GetNumRoots() == 2);
			double roots[4] = {-1.2164845038809537, -0.27836306273874734, static_cast<double>(0), static_cast<double>(0)};
			BOOST_CHECK(*equation.GetRoots() == *roots);
		}
	}
BOOST_AUTO_TEST_SUITE_END()
