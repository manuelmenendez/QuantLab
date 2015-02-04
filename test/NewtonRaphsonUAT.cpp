#include <functional>
#include <gtest/gtest.h>

#include "NewtonRaphson.h"


double ec(const double x, double y)
{
	return  6 * x*x - 5 * x + 3 + y*x + y*y;
}


double dec_x(const double x, double y)
{
	return  12 * x - 5 + y + 2 * y ;
}


const double solution = 0.0605641;

TEST(Solvers, NewtonRaphson1D_Callables_Simple_function_1V)
{
	//simple function 1 V
	ql::NewtonRapshon1D <double, decltype(&ec),double> mysolver(ec, dec_x);
	mysolver.Eps(1e-4);
	mysolver.FirstGuess(0.5);
	mysolver.Solve(0.5,0.0);
	EXPECT_NEAR(1e-4, mysolver.Eps(),1e-4);
	EXPECT_NEAR(mysolver.Solution(), solution, mysolver.Eps());
}
