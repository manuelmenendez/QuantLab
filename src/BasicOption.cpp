
#include "DynamicAssert.h"
#include "BasicOption.h"

namespace ql{

	template < typename P, typename I, typename VT, typename D>
	const double BasicOption <P,I,VT,D>::eps = 10e-12;

	template <typename P, typename I, typename VT, typename D>
	double BasicOption<P, I, VT, D>::YearFractionToExpiry() const
	{
		double yfte = (expiry_ - valueDate_) / 365.0;
		return yfte;
	};

	template class BasicOption<double, double, double, double>;
}