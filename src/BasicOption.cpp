
#include "DynamicAssert.h"
#include "BasicOption.h"

namespace ql{


	double BasicOption<>::yearFractionToExpiry() const
	{
		return (expiry_ - valueDate_) / 365.0;
	}
}