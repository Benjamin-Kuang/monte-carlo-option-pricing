# Monte Carlo Option Pricing: Accuracy and Computational Cost

This C++ project compares Monte Carlo price estimates with Black-Scholes prices for European call and put options. It tests how many simulation paths are needed to keep the mean absolute pricing error below $0.05 for both options and measures how long each run takes.

## Simulation and results

1,000, 10,000, 100,000, and 1,000,000 paths were tested across three scenarios, using the same ten random seeds for each test. Each scenario used a $100 underlying stock price, a $100 option strike price, a 5% risk-free rate, and no dividends.

The table shows the 2 largest path counts. MAE is the mean absolute error from the price calculated by Black-Scholes formula across 10 runs. Standard error (SE) and runtime were calculated for each run and then averaged.

| Maturity and volatility | Paths per run | MAE Call ($) | SE Call ($) | MAE Put ($) | SE Put ($) | Runtime (ms) |
|---|---:|---:|---:|---:|---:|---:|
| 1 year, 20% | 100,000 | 0.0395 | 0.0466 | 0.0243 | 0.0273 | 2.62 |
| 1 year, 20% | 1,000,000 | 0.0151 | 0.0147 | 0.0080 | 0.0087 | 26.54 |
| 1 year, 40% | 100,000 | 0.0772 | 0.0991 | 0.0482 | 0.0530 | 2.69 |
| 1 year, 40% | 1,000,000 | 0.0309 | 0.0313 | 0.0143 | 0.0168 | 26.73 |
| 2 years, 20% | 100,000 | 0.0598 | 0.0713 | 0.0303 | 0.0334 | 2.58 |
| 2 years, 20% | 1,000,000 | 0.0230 | 0.0225 | 0.0099 | 0.0106 | 25.83 |

For 1-year options at 20% volatility, 100,000 paths was the first count tested that met the "below $0.05" target for both options. In the other two scenarios, the put option still met the target at 100,000 paths, but the call option first met it at 1 million paths. At 40% volatility, increasing the path count from 100,000 to 1 million reduced the MAE of call option from $0.0772 to $0.0309, while the average runtime rose from 2.69 to 26.73 milliseconds, which is 10 times before.

## Run the project

Open `MonteCarloOptionPricing.slnx` in Visual Studio and press Ctrl+F5. To run a different scenario, change `volatility` and `years` in `main.cpp`.

[Read the one-page project summary](Report/Monte%20Carlo%20Option%20Pricing%20Summary.pdf)