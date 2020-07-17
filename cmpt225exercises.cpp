// cmpt225exercises.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "Sequence.h"
using std::cout;
using std::endl;

void exercise1();
void quiz2();
void foo(int arr[], int n);


int main()
{
	exercise1();
	//quiz2();


	cout << endl;
	return 0;
}

void exercise1()
{
	Sequence sq;
	cout << "size = " << sq.size() << endl; // outputs 0
	cout << "standard deviation = " << sq.stdDeviation() << endl;
}

void quiz2()
{
	int* arr1 = new int[3];
	cout << "arr1 = " << arr1 << endl;
	cout << "&arr1[2] = " << &arr1[2] << endl;

	int arr2[] = { 1,2,3 };
	int n = 3;
	int sum = 0;
	foo(arr2, n);

	for (int i = 0; i < n; ++i) {
		sum += arr2[i];
	}
	cout << sum << endl;

	int* p = new int[254]; 
	p = new int[2544]; 
	delete[] p;

	cout << endl;
}

void foo(int arr[], int n)
{
	for (int i = 0; i < n; ++i) {
		arr[i] *= 2;
	}
}

