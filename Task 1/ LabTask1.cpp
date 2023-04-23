#include <omp.h>
#include <iostream>
#include <cmath>
#include <time.h> 
using namespace std;

int f(int b)
{
	for (int i = 1; i < 9e7; i++) 
	{
		b = b * 1;
	}
	return b;
}


int main()
{
	int a[1000], b[1000];
	// Èíèöèàëèçàöèÿ ìàññèâà b
	for (int i = 0; i < 1000; i++)
		b[i] = i;

	clock_t start = clock();
	// Äèðåêòèâà OpenMP äëÿ ðàñïàðàëëåëèâàíèÿ öèêëà
#pragma omp parallel for
	for (int i = 0; i < 1000; i++)
	{
		a[i] = f(b[i]);
		b[i] = 2 * a[i];
	}
	int result = 0;
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	// Äàëåå çíà÷åíèÿ a[i] è b[i] èñïîëüçóþòñÿ, íàïðèìåð, òàê:
#pragma omp parallel for reduction(+ : result)
	for (int i = 0; i < 1000; i++)
		result += (a[i] + b[i]);

	cout << "Result = " << result << endl;
	//
	cout << "time = " << seconds;
	
	return 0;
}
