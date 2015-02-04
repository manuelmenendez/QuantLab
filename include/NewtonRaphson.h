#ifndef NEWTONRAPHSON_H
#define NEWTONRAPHSON_H

#include <memory>
#include <functional>
#include <algorithm>
#include <vector>
#include <boost/any.hpp>

#include "Solver.h"
#include "DynamicAssert.h"

namespace ql{
	
	// Function objective has to have same c++ prototype as c++ derivative function
	// f(x1..xn)->z1  => f'(y1..yn)->z2 " xi,yj € A when i=j ,  z1,z2 € B
	// First template parameter is the function result type
	// Second template parameter is the signature of objective function (use decltype(&existing_function))
	// Third  template parameter is the signature of objective function derivative (use decltype(&existing_function))
	// Last variadic template parameters are the parameters types of the objective function except the first one objective parameter (variable to solve).
	// Last parameter can be empty
	//
	//Example:
	// double f(const double x, int y, unsigned z);		  // f : R x N x N+ -> R
	// double fderived(const double x, int y,unsigned z); // f´: R x N x N+ -> R
	// ql::NewtonRapshon1D <double, decltype(&f), int, unsigned> mySolver(f, fderived);
	// mySolver.Eps(1e-8);
	// mySolver.FirstGuess(0.5);
	// mySolver.Solve(0.0, -1, 1); <= Finds zero, when y = -1, when z = 1, using 0.5 as first value

	template <typename RealType, typename FunctionT, typename DerivativeT = FunctionT, typename...ArgsExceptFirst>
	class NewtonRapshon1D_BASE : public Solver_BASE <RealType, NewtonRapshon1D_BASE<RealType, FunctionT, DerivativeT, ArgsExceptFirst...>, ArgsExceptFirst...>
	{
	public:

		inline NewtonRapshon1D_BASE() = default;
		
		inline NewtonRapshon1D_BASE(FunctionT func, DerivativeT derivative) :function_(func), derivative_(derivative){};
		
		inline const RealType & FirstGuess() const  { return firstGuess_; }
		inline void FirstGuess(const RealType & firstGuess) { firstGuess_ = firstGuess; }

		inline void Solve(RealType first, ArgsExceptFirst... args) 
		{
			RealType xi = first;
			RealType xi1 = first+2*Eps();

			for (size_t iterations = 0, hasSolution_ = false; !hasSolution_ && iterations < MaxIterations(); iterations++)
			{
				xi1 = nextX(xi, args...);
				hasSolution_ = Error(xi1, xi)<Eps();
				xi = xi1;
			}
			solution_ = xi1;
		}
		
		const RealType Solution()   { Assert::dynamic_release(hasSolution_, "Function doesn´t converge"); return solution_; }
		bool FoundSolution(){ return  hasSolution_; }

	private:
		inline RealType   nextX(RealType x, ArgsExceptFirst... args) { return x - function_(x, args...) / derivative_(x, args...); }
		inline RealType   Error(RealType x, RealType y) { return std::abs(x - y); }

		FunctionT   function_;
		DerivativeT derivative_;
		RealType    epsilon_;
		RealType    firstGuess_;
		RealType    solution_;
		bool        hasSolution_;

	};

	template  <typename RealType, typename FunctionT, typename...ArgsExceptFirst> 
		using NewtonRapshon1D = NewtonRapshon1D_BASE<RealType, FunctionT, FunctionT, ArgsExceptFirst...>;

	template  <typename RealType, typename FunctionT, typename DerivativeT, typename...ArgsExceptFirst>
	using NewtonRapshon1DLambda = NewtonRapshon1D_BASE<RealType, FunctionT, DerivativeT, ArgsExceptFirst...>;


}//namespace

#endif
