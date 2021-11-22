#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Primes{
	public:
	vector<int> vec;
	Primes() { vec = {2, 3}; };
	
	void fill_up_to(int);
	void print();
	
	private:
	bool isprime(int);
};

Primes nprimi;

class Fraction{
	public:
	Fraction(int num = 1, int den = 1) 
		{ set(num, den); };
	
	void set(int Num, int Den) 
		{ 
			N = Num;
			if (Den == 0)
			{
				cout << 
				"\nDenominator not valid\n";
				D = 1;
			}
			else D = Den; 
		};
		
	string get_str() 
		{ return to_string(N) 
			+ '/' + to_string(D); };
			
	void minimize();
	
	private:
	int N; //numeratore
	int D; //denominatore
	
	int min(int a, int b)
		{ return ( a >= b ? b : a); };
};

bool Primes::isprime(int num)
{
	int root = sqrt(num);
	
	for(int x : vec)
	{
		if (num % x == 0)
			return 0; //not prime
		if (root < x)
			return 1;
	}
	return 1; //prime
}

void Primes::fill_up_to(int num)
{
	int num_to_check = 
		vec[vec.size() - 1] + 2;
	//2 e' l'unico primo pari
	//controlla solo i numeri dispari
	
	while (num_to_check <= num)
	{
		if (isprime(num_to_check))
			vec.push_back(num_to_check);
			
		num_to_check += 2;
	}
}

void Primes::print()
{
	cout << "\nI numeri primi sono:\n\n";
	
	for (int x : vec)
		cout << x << " ";
}

void Fraction::minimize()
{
	if (N % D == 0)
	{
		N /= D;
		D = 1;
		return;
	}
	else if (D % N == 0)
	{
		D /= N;
		N = 1;
		return;
	}
	
	int limit = sqrt(min(N, D)) +1; 
	
	nprimi.fill_up_to(limit);
	
	for (int x : nprimi.vec)
	{
		if (x > limit)
			break;
					
		while (N % x == 0 and D % x == 0)
		{
			N /= x;
			D /= x;
		}
	}		
}



void print_fracts(int denominatore, float begin = 0, float end = 1)
{
//	vector<Fraction> fracts(denominatore +1);
	Fraction fract;
	
	for (int i = 0; i <= denominatore; i++)
	{
		fract.set(i, denominatore);
		fract.minimize();
		
		cout << fract.get_str() << "\n";
	}
}

int main ()
{
	print_fracts(1000);
	
	return 0;
}
