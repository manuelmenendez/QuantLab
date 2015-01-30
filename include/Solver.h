#ifndef SOLVER_H
#define SOLVER_H

#include <functional>
#include <memory>

#include "DynamicAssert.h"

// This is an interface for solvers
// Do not instantiate this class, use istead one of its implemetations, suchs as NewtonRapshon1D...

namespace  ql
{

	template< typename RealType, typename DERIVED_CLASS, typename... TArgs>
	class Solver_BASE
	{
	public:
		Solver_BASE():eps_(RealType(1e-16)),maxIterations_(10000){}

		void Solve(TArgs... args)
		{
			 static_cast<DERIVED_CLASS*>(this)->Solve(args...);
		}

		const RealType & Eps() const  { return eps_; }
		void Eps(const RealType & eps) { eps_ = eps; }

		const size_t & MaxIterations() const  { return maxIterations_; }
		void MaxIterations(const size_t & maxIterations) { maxIterations_ = maxIterations; }
	
		RealType Solution(){ return static_cast<DERIVED_CLASS*>(this)->Solution(); }
		bool FoundSolution(){ return static_cast<DERIVED_CLASS*>(this)->FoundSolution(); }

	private:
		RealType eps_;
		size_t maxIterations_;
	};
}

#endif
