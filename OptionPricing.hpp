// OptionPricing.hpp
// Declare the OptionPricing Struct, the Black-Scholes formula, and Monte Carlo pricing functions
// Author: Jin Kuang

struct OptionPrice
{
	double call;
	double put;
	double callSE = 0.0;
	double putSE = 0.0;
};

// calculate call price and put price for the European options using Black-Scholes formula
OptionPrice BlackScholes(double spot, double strike, double rate, double volatility, double years);

// estimate European call and put prices using Monte Carlo simulation with the given number of paths and random seed
OptionPrice MonteCarloPricing(double spot, double strike, double rate, double volatility, double years, int paths, int seed);