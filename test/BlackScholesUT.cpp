#include <gtest/gtest.h>
#include "StandardBlackScholes.h"

TEST(StandardBlackScholes, dummyTest) {

	double spot = 1 , strike = 1, tipoInteres = 1, FechaValor = 1, FechaVcto= 1, Volatilidad = 1, Dividendos = 1;
	double expected_dummy = spot+ strike + tipoInteres + FechaValor + FechaValor + FechaVcto+ Volatilidad + Dividendos;
	double actual = StandardBlackScholes(spot, strike, tipoInteres, FechaValor, FechaVcto, Volatilidad, Dividendos, false);
	EXPECT_EQ(expected_dummy, actual);
}