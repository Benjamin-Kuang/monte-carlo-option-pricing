// OptionPricing.cpp
// Implement the OptionPricing Struct, the Black-Scholes formula, and Monte Carlo pricing functions
// Author: Jin Kuang

#include "OptionPricing.hpp"
#include <cmath>
#include <algorithm>
#include <random>

using namespace std;

// return the probability of a standard normal variable less than x
double normalCDF(double x)
{
	return 0.5 * erfc(-x / sqrt(2.0));
}

// calculate call price and put price for the European options using Black-Scholes formula
OptionPrice BlackScholes(double spot, double strike, double rate, double volatility, double years)
{
	const double volatilityPeriod = sqrt(years) * volatility;
	const double discountedStrike = strike * exp(-rate * years);

	const double d1 = (log(spot / strike) + (rate + 0.5 * volatility * volatility) * years) / volatilityPeriod;
	const double d2 = d1 - volatilityPeriod;

	OptionPrice price;
	price.call = spot * normalCDF(d1) - discountedStrike * normalCDF(d2);
	price.put = discountedStrike * normalCDF(-d2) - spot * normalCDF(-d1);

	return price;
}

// calculate the standard error of average discounted payoff
double StandardError(double sum, double sumSquares, int paths, double discount)
{
	const double variance = (sumSquares - sum * (sum / paths)) / (paths - 1);
	return sqrt(max(variance, 0.0) / paths) * discount;
}

// estimate European call and put prices using Monte Carlo simulation with the given number of paths and random seed
OptionPrice MonteCarloPricing(double spot, double strike, double rate, double volatility, double years, int paths, int seed)
{
	mt19937 generator(seed);
	normal_distribution<double> normal(0.0, 1.0);

	const double drift = (rate - 0.5 * volatility * volatility) * years;

	double callSum = 0.0;
	double putSum = 0.0;
	double callSumSquares = 0.0;
	double putSumSquares = 0.0;

	for (int i = 0; i < paths; ++i)
	{
		const double z = normal(generator);
		const double finalSpot = spot * exp(drift + volatility * sqrt(years) * z);

		callSum += max(finalSpot - strike, 0.0);
		putSum += max(strike - finalSpot, 0.0);

		const double difference = finalSpot - strike;

		if (difference > 0.0)
		{
			callSumSquares += difference * difference;
		}
		else
		{
			putSumSquares += difference * difference;
		}
	}

	OptionPrice price;
	price.call = (callSum / paths) * exp(-rate * years);
	price.put = (putSum / paths) * exp(-rate * years);
	price.callSE = StandardError(callSum, callSumSquares, paths, exp(-rate * years));
	price.putSE = StandardError(putSum, putSumSquares, paths, exp(-rate * years));
	return price;
}