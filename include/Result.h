#ifndef RESULT_H
#define RESULT_H

namespace ql
{
	template < typename F = double >
	struct Result
	{
		Result() = default;

		F premium = F(0);
		F delta = F(0);
		F gamma = F(0);
		F vega = F(0);
	};

	template Result <double>;
}

#endif