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
	vector<double> smg;
	vector<double> signals = { 100, 32 };
	vector<Perceptron> perceptrons;

	for (int i = 0; i < 500; ++i)
	{
		smg.push_back(0);
		perceptrons.push_back(Perceptron(2));
	}

	smg[signals[0] + signals[1]] = 0.5f;

	for (int i = signals[0] + signals[1] - 1; i > 0; --i)
	{
		smg[i] = smg[i + 1] - 0.5f / 500;
		cout << smg[i] << ' ';
	}

	cout << endl;

	for (int i = signals[0] + signals[1] + 1; i < 500; ++i)
	{
		smg[i] = smg[i - 1] + 0.5f / 500;
		cout << smg[i] << ' ';
	}

	cout << endl;
	int agr = 0;
	int disagr = 0;
	while (true)
	{
		for (double i = 0; i < 250; i++)
		{
			for (double j = 0; j < 250; j++)
			{
				vector<double> temp_l = { i, j };
				for (int l = 0; l < 500; l++)
				{
					double temp = perceptrons[l].process(temp_l);
					if (abs(0.5f - temp) == 0.5f) agr++;
					else disagr++;
					perceptrons[l].learn(0.5f);
				}
			}
		}
		cout << agr << ' ' << disagr << endl;
		agr = 0;
		disagr = 0;
	}
}