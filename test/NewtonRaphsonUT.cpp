#include <functional>
#include <gtest/gtest.h>

#include "NewtonRaphson.h"


double ec(const double x, double y)
{
	return  6 * x*x - 5 * x + 3 + y*x + y*y;
}


double dec_x(const double x, double y)
{
	return  12 * x - 5 + y + 2 * y;
}


double ec2(const double x)
{
	return  6 * x*x - 5 * x + 3;
}

double dec2_x(const double x)
{
	return  12 * x - 5;
}

class testnr
{
public:
	double cec(const double x, double y)
	{
		return ec(x, y);
	}
	double cdec_x(const double x, double y)
	{
		return dec_x(x, y);
	}
};
const double solution = 0.0605641;

TEST(Solvers, NewtonRaphson1D_Callables_Simple_function_1V)
{
	//simple function 1 V
	ql::NewtonRapshon1D <double, decltype(&ec2)> mysolver(ec2, dec2_x);
	mysolver.Eps(1e-4);
	mysolver.FirstGuess(0.5);
	mysolver.Solve(0.5);
	EXPECT_NEAR(1e-4, mysolver.Eps(), 1e-4);
	EXPECT_NEAR(mysolver.Solution(), solution, mysolver.Eps());
}

TEST(Solvers, NewtonRaphson1D_Callables_Simple_function_2V)
{
	//simple function 2 V
	ql::NewtonRapshon1D <double, decltype(&ec), double> mysolver(ec, dec_x);
	mysolver.Eps(1e-4);
	mysolver.FirstGuess(0.5);
	mysolver.Solve(0.5, 0.0);
	EXPECT_NEAR(1e-4, mysolver.Eps(), 1e-4);
	EXPECT_NEAR(mysolver.Solution(), solution, mysolver.Eps());
}

TEST(Solvers, NewtonRaphson1D_Callables_Simple_pointer_1V)
{
	//simple pointer to function 2V
	double(*OneParamF)(const double) = &ec2;
	double(*OneParamFder)(const double) = &dec2_x;

	ql::NewtonRapshon1D <double, decltype(OneParamF)> mysolver(OneParamF, OneParamFder);
	mysolver.Eps(1e-4);
	mysolver.FirstGuess(0.5);
	mysolver.Solve(0.5);
	EXPECT_NEAR(1e-4, mysolver.Eps(), 1e-4);
	EXPECT_NEAR(mysolver.Solution(), solution, mysolver.Eps());
}


TEST(Solvers, NewtonRaphson1D_Callables_Simple_pointer_2V)
{
	//simple pointer to function 2V
	double(*TwoParamsF)(const double, double) = &ec;
	double(*TwoParamsFDer)(const double, double) = &dec_x;

	ql::NewtonRapshon1D <double, decltype(TwoParamsF), double> mysolver(TwoParamsF, TwoParamsFDer);
	mysolver.Eps(1e-4);
	mysolver.FirstGuess(0.5);
	mysolver.Solve(0.5, 0);
	EXPECT_NEAR(1e-4, mysolver.Eps(), 1e-4);
	EXPECT_NEAR(mysolver.Solution(), solution, mysolver.Eps());
}

TEST(Solvers, NewtonRaphson1D_function1v)
{
	typedef double(*OneParamF)(const double);

	std::function<double(const double)> f(ec2);
	std::function<double(const double)> fder(dec2_x);

	ql::NewtonRapshon1D <double, OneParamF> mysolver(*f.target<OneParamF>(), *fder.target<OneParamF>());
	mysolver.Eps(1e-4);
	mysolver.FirstGuess(0.5);
	mysolver.Solve(0.5);
	EXPECT_NEAR(1e-4, mysolver.Eps(), 1e-4);
	EXPECT_NEAR(mysolver.Solution(), solution, mysolver.Eps());
}

TEST(Solvers, NewtonRaphson1D_function2v)
{
	typedef double(*TwoParamF)(const double, double);

	std::function<double(const double, double)> f(ec);
	std::function<double(const double, double)> fder(dec_x);

	ql::NewtonRapshon1D <double, TwoParamF, double> mysolver(*f.target<TwoParamF>(), *fder.target<TwoParamF>());
	mysolver.Eps(1e-4);
	mysolver.FirstGuess(0.5);
	mysolver.Solve(0.5, 0.0);
	EXPECT_NEAR(1e-4, mysolver.Eps(), 1e-4);
	EXPECT_NEAR(mysolver.Solution(), solution, mysolver.Eps());
}

TEST(Solvers, NewtonRaphson1D_lambda)
{

	auto l = [](const double a, double b) { return ec(a, b); };
	auto l2 = [](const double a, double b) { return dec_x(a, b); };

	ql::NewtonRapshon1DLambda <double, decltype(l), decltype(l2), double> mysolver(l, l2);
	mysolver.Eps(1e-4);
	mysolver.FirstGuess(0.5);
	mysolver.Solve(0.5, 0.0);
	EXPECT_NEAR(1e-4, mysolver.Eps(), 1e-4);
	EXPECT_NEAR(mysolver.Solution(), solution, mysolver.Eps());
}


TEST(Solvers, NewtonRaphson1D_bind_lambda)
{

	std::function<double(const double)> f = std::bind(ec, std::placeholders::_1, 0.0);
	std::function<double(const double)> fder = std::bind(dec_x, std::placeholders::_1, 0.0);

	auto l = [f](const double a) { return f(a); };
	auto l2 = [fder](const double a) { return fder(a); };

	ql::NewtonRapshon1DLambda <double, decltype(l), decltype(l2)> mysolver(l, l2);
	mysolver.Eps(1e-4);
	mysolver.FirstGuess(0.5);
	mysolver.Solve(0.5);
	EXPECT_NEAR(1e-4, mysolver.Eps(), 1e-4);
	EXPECT_NEAR(mysolver.Solution(), solution, mysolver.Eps());
}
