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


double ec2(const double x)
{
	return  6 * x*x - 5 * x + 3 ;
}

double dec2_x(const double x)
{
	return  12* x - 5 ;
}


TEST(Solvers, NewtonRaphson1D_Callables) 
{
	ql::NewtonRapshon1D <double, decltype(&ec), double> solver(ec, dec_x);
	ql::NewtonRapshon1D <double, decltype(&ec2)> solver2(ec2, dec2_x);

	solver.Solve(0.5,1.0);
	solver2.Solve(0.5);
	
	solver.Eps(1e-8);
	solver.FirstGuess(0.5);
	solver.Solve(0.0, -1);
}


