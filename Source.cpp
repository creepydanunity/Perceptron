#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

class Perceptron
{
private:
	double result;
	vector<double> sm;
	vector<double> weights;
	double b;
	double s;
public:
	Perceptron(int n = 2)
	{
		for (int i = 0; i < n; ++i)
		{
			weights.push_back((rand() % 1000 - 500) / 1000.);
		}
		b = (rand() % 1000 - 500) / 1000.;
	}

	double process(vector<double>& x)
	{
		s = b;
		for (int i = 0; i < x.size(); ++i)
		{
			s += x[i] * weights[i];
		}
		result = activationFunction(s);
		sm = x;
		return result;
	}

	double activationFunction(double aS)
	{
		return 1. / (1. + exp(-aS));
	}

	double dActivationFunction(double aS)
	{
		return activationFunction(aS) * (1 - activationFunction(aS));
	}

	void learn(int n)
	{
		double error = n - result;
		double tetta = error * dActivationFunction(s);
		for (int i = 0; i < weights.size(); ++i)
		{
			weights[i] += tetta * sm[i];
		}
		b += tetta;
	}
};

int main()
{
	srand(time(0));
	vector<Perceptron> pts;
	vector<vector<double>> signals = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
	Perceptron test_per;
	while (true)
	{
		for (int i = 0; i < signals.size(); ++i)
		{
			cout << test_per.process(signals[i]) << ' ';
			test_per.learn(signals[i][0] * signals[i][1]);
		}
		cout << endl;
	}
}
