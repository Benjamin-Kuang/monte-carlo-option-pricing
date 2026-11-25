// Monte Carlo Option Pricing
// Author: Jin Kuang
// Calculate European call and put options using the Black-Scholes formula and Monte Carlo simulation	
// The underlying stock pays no dividend

#include "OptionPricing.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

// Prints the Black-Scholes price for a plain vanilla European call and put option without dividend, 
// given the spot price, strike price, risk-free rate, volatility, and time to maturity in years
int main()
{	
	// plain vanilla option without dividend
	const double spot = 100;
	const double strike = 100;
	const double rate = 0.05;

	// const double volatility = 0.2;
	// const double years = 1;

	// const double volatility = 0.4;
	// const double years = 1;

	const double volatility = 0.2;
	const double years = 2;

	const OptionPrice price = BlackScholes(spot, strike, rate, volatility, years);

	cout << fixed << setprecision(4);
	cout << "European Call Price: $" << price.call << endl;
	cout << "European Put Price: $" << price.put << endl;

	// Check Put-call parity formula: P + S =  C + K * e^(-rT).
	const double protectivePut = price.put + spot;
	const double fiduciaryCall = price.call + strike * exp(-rate * years);
	const double tolerance = 1e-10;

	if (abs(protectivePut - fiduciaryCall) >= tolerance)
	{	
		cout << "Put-call parity check failed" << endl;
		return 1;
	}

	cout << "Put-call parity holds" << endl;

	const int initialSeed = 2026;
	const int seedsNumber = 10;
	const int paths[] = {1000, 10000, 100000, 1000000};

	cout << endl;
	cout << "Monte Carlo results (average of " << seedsNumber << " seeds):" << endl;

	for (int path : paths)
	{	
		double totalCallPrice = 0.0;
		double totalPutPrice = 0.0;
		double totalTime = 0.0;
		double totalAbsErrorCall = 0.0;
		double totalAbsErrorPut = 0.0;
		double totalSECall = 0.0;
		double totalSEPut = 0.0;

		for (int seed = initialSeed; seed < initialSeed + seedsNumber; ++seed)
		{	
			const steady_clock::time_point start = steady_clock::now();
			const OptionPrice MC = MonteCarloPricing(spot, strike, rate, volatility, years, path, seed);
			const steady_clock::time_point finish = steady_clock::now();

			const duration<double, milli> time = finish - start;
			const double absErrorCall = abs(MC.call - price.call);
			const double absErrorPut = abs(MC.put - price.put);

			totalCallPrice += MC.call;
			totalPutPrice += MC.put;
			totalTime += time.count();
			totalAbsErrorCall += absErrorCall;
			totalAbsErrorPut += absErrorPut;
			totalSECall += MC.callSE;
			totalSEPut += MC.putSE;
		}

		cout << "Number of path: " << path << endl;
		cout << "Simulated call price: $" << totalCallPrice / seedsNumber << endl;
		cout << "Simulated put price: $" << totalPutPrice / seedsNumber << endl;
		cout << "Time taken to run the Monte Carlo simulation: " << totalTime / seedsNumber << " ms" << endl;
		cout << "Call absolute error: $" << totalAbsErrorCall / seedsNumber << endl;
		cout << "Put absolute error: $" << totalAbsErrorPut / seedsNumber << endl;
		cout << "Average standard error of call option: $" << totalSECall / seedsNumber << endl;
		cout << "Average standard error of put option: $" << totalSEPut / seedsNumber << endl;
		cout << endl;
	}
}