#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits>

using namespace std;

/*
	Write a function that calculates the nth Fibonacci number in O(n) time or better without using any "for" or "while" loops. (Feel free to use the space below or submit a link to your work.)

	Personal Notes:
		- Doesn't specify needed range
		- Making solution work with int returns so fib(0) through fib(46)
				- http://www.maths.surrey.ac.uk/hosted-sites/R.Knott/Fibonacci/fibtable.html
		- If n > 46 I will return -1 and print a message indicating the number is invalid
		- If n < 0 I will return 0

	Approach
		- Without for or while loops so use recursion
				- Basic recursion takes O(2^n) time
				- If we store intermediate values we reduce time to O(n) (reduce repetitive computations)
						- Can use bottom up or top down
								- Buttom up would need a loop to get to the given n so use top down
*/

// Array to store values
vector<int> arr(47, INT_MIN);

// Top down memoization
int memo(int n)
{
	if (arr[n] != INT_MIN)
	{
		return arr[n];
	}

	else
	{
		arr[n] = memo(n - 1) + memo(n - 2);
		return memo(n);
	}
}

// Fibonacci
int fib(int n)
{
	if (n <= 0)
	{
		return 0;
	}

	else if (n == 1)
	{
		return 1;
	}

	else if (n > 46)
	{
		return -1;
	}

	else
	{
		arr[0] = 0;
		arr[1] = 1;

		return memo(n);
	}
}

void testFib(int n, int answer)
{
	if (n > 46)
	{
		cout << "This implementation of fibonacci is only valid through n == 46; Test will fail" << endl;
	}

	if (fib(n) == answer)
	{
		cout << "Test Case Passed" << endl;
	}

	else
	{
		cout << "Test Case Failed" << endl;
	}

	cout << endl;
}

int main()
{
	testFib(0, 0);

	testFib(-1, 0);
	testFib(-4, 0);

	testFib(1, 1);
	testFib(14, 377);
	testFib(16, 987);
	testFib(40, 102334155);
	testFib(46, 1836311903);

	testFib(47, 2971215073);
	testFib(49, 7778742049);

	return 0;
}