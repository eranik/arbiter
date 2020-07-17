// cmpt225a1statistics.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <vector>
#include "Sequence.h"

using std::cout;
using std::endl;
using std::vector;

int marking();

void basicTest();
int constructorTest();
int simpleInsertTest();
int doubleInsertTest();
int arrayInsertTest();
int statisticsTest1();
int statisticsTest2();
int concatenateTest();
int copyConstructorTest();
int assignmentTest();
bool approx(double test, double correct, double delta);

int main()
{
	//basicTest();
	marking();

	cout << endl;
	return 0;
}

int marking()
{
	int total = 0;
	total += constructorTest(); //out of 1
	total += simpleInsertTest(); //out of 2
	total += doubleInsertTest(); //out of 2
	total += arrayInsertTest(); //out of 4
	total += statisticsTest1(); //out of 5
	total += statisticsTest2(); //out of 7
	total += concatenateTest(); //out of 4
	total += copyConstructorTest(); //out of 4
	total += assignmentTest(); //out of 3

	cout << "TOTAL: " << total << "/32" << endl << endl;

	cout << endl << endl;
	return total;
}

int constructorTest()
{
	cout << "DEFAULT CONSTRUCTOR" << endl;
	Sequence sq;
	int mark = 0;

	if (sq.size() == 0) {
		mark += 1;
	}
	else {
		cout << "size (0)" << endl;
	}

	cout << "default constructor mark = " << mark << "/1" << endl << endl;
	return mark;
}

int simpleInsertTest()
{
	cout << "SIMPLE INSERT" << endl;
	Sequence sq;
	int mark = 0;
	sq.insert(3.14);

	if (sq.find(3.14) == 1 && sq.size() == 1) {
		mark += 2;
	}
	
	cout << "simple insert mark = " << mark << "/2" << endl << endl;
	return mark;
}

int doubleInsertTest()
{
	cout << "DOUBLE ARRAY INSERT" << endl;
	Sequence sq;
	int mark = 0;
	bool check = true;
	int n = 4;
	
	// Test 1: Insert four items (doubles in size)
	for (int i = 0; i < n; ++i) {
		sq.insert((double)i + 1);
	}

	for (int i = 0; i < n; ++i) {
		if (sq.find((double)i + 1) != 1) {
			check = false;
		}
	}

	if (sq.size() == 4 && check) {
		mark += 1;
	}
	else {
		cout << "x insert 4" << endl;
	}

	// Test 2: Insert eight items (doubles in size)
	n = 8;
	for (int i = 0; i < n; ++i) {
		sq.insert((double)i + 5);
	}

	n = 12;
	for (int i = 0; i < n; ++i) {
		if (sq.find((double)i + 1) != 1) {
			check = false;
		}
	}

	if (sq.size() == 12 && check) {
		mark += 1;
	}
	else {
		cout << "x insert 8" << endl;
	}

	cout << "double array mark = " << mark << "/2" << endl << endl;
	return mark;
}

int arrayInsertTest()
{
	cout << "ARRAY INSERT" << endl;
	// Test 1 -- empty
	Sequence sq1;
	int mark = 0;
	bool check = true;

	// Test 1: room in underlying array of size 16
	double darr1[] = { 10,11,12,13 };
	int n = 4;
	for (int i = 0; i < 9; ++i) {
		sq1.insert((double)i + 1);
	}
	sq1.insert(darr1, n);
	int newn = 13;

	if(sq1.size() == newn){
		mark += 1;
	}
	else {
		cout << "x insert 4 size" << endl;
	}
	for (int i = 0; i < newn; ++i) {
		if (sq1.find(i + 1) != 1) {
			check = false;
		}
	}
	if (check) {
		mark += 1;
	}
	else {
		cout << "x insert 4 find" << endl;
	}
	check = true;

	// Test 2: insufficient room in underlying array
	Sequence sq2;
	double darr2[] = { 8,9,10,11,12,13,14,15,16,17 };
	n = 10;
	for (int i = 0; i < 7; ++i) {
		sq2.insert((double)i + 1);
	}
	sq2.insert(darr2, n);
	newn = 17;

	if (sq2.size() == newn) {
		mark += 1;
	}
	else {
		cout << "x insert 10 size" << endl;
	}
	for (int i = 0; i < newn; ++i) {
		if (sq2.find(i + 1) != 1) {
			check = false;
		}
	}
	if (check) {
		mark += 1;
	}
	else {
		cout << "x insert 10 find" << endl;
	}
	check = true;

	cout << "array insert mark = " << mark << "/4" << endl << endl;
	return mark;
}

// Statistics with sample data: odd number, no duplicates
int statisticsTest1()
{
	cout << "STATISTICS 1" << endl;
	vector<double> v = { 58.06,49.39,27.93,88.62,32.78,69.21,2.69, 
		41.69,29.55,16.02,7.94,70.46,94.23 };
	Sequence sq;
	int mark = 0;
	bool check = true;
	double vsum = 588.57;
	double vmean = 45.27;
	double vstddev = 28.34;
	double vmedian = 41.69;
	double delta = 0.05;
	
	for(double d : v) {
		sq.insert(d);
	}

	// Find
	for (double d : v) {
		if (sq.find(d) != 1) {
			check = false;
		}
	}
	if (check) {
		mark++;
	}
	else {
		cout << "x find" << endl;
	}

	// Sum
	if (approx(sq.sum(), vsum, delta)) {
		mark++;
	}
	else {
		cout << "x sum" << endl;
	}

	// Mean
	if (approx(sq.mean(), vmean, delta)) {
		mark++;
	}
	else {
		cout << "x mean" << endl;
	}

	// Median
	if (approx(sq.median(), vmedian, delta)) {
		mark++;
	}
	else {
		cout << "x median" << endl;
	}

	// Standard Deviation
	if (approx(sq.stddev(), vstddev, delta)) {
		mark++;
	}
	else {
		cout << "x stddev" << endl;
	}

	cout << "statistics 1 mark = " << mark << "/5" << endl << endl;
	return mark;
}

// Even number of value including duplicates
int statisticsTest2()
{
	cout << "STATISTICS 2" << endl;
	vector<double> v = { 42.87,27.28,74.51,90.67,42.93,35.25,35.25,
		90.67,37.55,40.96,23.25,9.94,60.93,74.51,40.96,40.96 };
	Sequence sq;
	int mark = 0;
	bool check = true;
	double vsum = 768.49;
	double vmean = 48.03;
	double vstddev = 22.83;
	double vmedian = 40.96;
	double delta = 0.05;

	for (double d : v) {
		sq.insert(d);
	}

	// Find
	if (sq.find(40.96) == 3 && sq.find(35.25) == 2 && sq.find(90.67) == 2) {
		mark += 2;
	}
	else {
		cout << "x find duplicates" << endl;
	}

	// Sum
	if (approx(sq.sum(), vsum, delta)) {
		mark++;
	}
	else {
		cout << "x sum" << endl;
	}

	// Mean
	if (approx(sq.mean(), vmean, delta)) {
		mark++;
	}
	else {
		cout << "x mean" << endl;
	}

	// Median
	if (approx(sq.median(), vmedian, delta)) {
		mark += 2;
	}
	else {
		cout << "x median" << endl;
	}

	// Standard Deviation
	if (approx(sq.stddev(), vstddev, delta)) {
		mark++;
	}
	else {
		cout << "x stddev" << endl;
	}


	cout << "statistics 2 mark = " << mark << "/7" << endl << endl;
	return mark;
}

bool approx(double test, double correct, double delta)
{
	return (test >= (correct - delta) && test <= (correct + delta));
}

int concatenateTest()
{
	cout << "CONCATENATE" << endl;
	// Test 1 -- empty
	Sequence sq1;
	Sequence sq2;
	Sequence sq3;
	int mark = 0;
	bool check = true;

	int n = 4;
	for (int i = 0; i < n; ++i) {
		sq1.insert((double)i + 1);
	}

	for (int i = n; i < n*2; ++i) {
		sq1.insert((double)i + 1);
	}

	sq3 = sq1.concatenate(sq2);

	n = 8;
	// size
	if(sq3.size() == n) {
		mark += 2;
	}
	else {
		cout << "x size" << endl;
	}

	// Find
	for (int i = 0; i < n; ++i) {
		if (sq3.find(i+1) != 1) {
			check = false;
		}
	}

	if (check) {
		mark += 2;
	}
	else {
		cout << "x find" << endl;
	}
	
	cout << "concatenate = " << mark << "/4" << endl << endl;
	return mark;
}

int copyConstructorTest()
{
	cout << "COPY CONSTRUCTOR" << endl;
	Sequence sq1;
	int mark = 0;
	bool check = true;
	sq1.insert(1.1);

	// Test 1 -- size
	Sequence sq2(sq1);
	if (sq2.size() == 1) {
		mark++;
	}
	else {
		cout << "x size" << endl;
	}

	// Test 2 -- contents
	if (sq2.find(1.1) == 1){
		mark++;
	}
	else {
		cout << "x contents" << endl;
	}

	// Test 3 -- separate attributes
	sq2.insert(2.2);
	if (sq2.size() == 2 && sq1.size() == 1) {
		mark++;
	}
	else {
		cout << "x insert into copy (n)" << endl;
	}

	if (sq2.find(2.2) == 1 && sq1.find(2.2) == 0) {
		mark++;
	}
	else {
		cout << "x insert into copy (find)" << endl;
	}

	cout << "copy constructor mark = " << mark << "/4" << endl << endl;
	return mark;
}

int assignmentTest()
{
	cout << "ASSIGNMENT OPERATOR" << endl;
	Sequence sq1;
	int mark = 0;
	bool check = true;
	sq1.insert(1.1);
	Sequence sq2;
	for (int i = 0; i < 4; ++i) {

	}
	sq2 = sq1;
	sq2.insert(2.2);

	// Test 1 -- size
	if (sq2.size() == 2) {
		mark++;
	}
	else {
		cout << "x size" << endl;
	}

	// Test 2 -- contents
	if (sq2.find(1.1) == 1 && sq2.find(2.2) == 1 &&
		sq1.find(1.1) == 1 && sq1.find(2.2) == 0) {
		mark++;
	}
	else {
		cout << "x contents" << endl;
	}

	// Test 3 -- self assignment
	sq2 = sq2;
	if (sq2.size() == 2 && sq2.find(1.1) == 1 && sq2.find(2.2) == 1) {
		mark++;
	}
	else {
		cout << "x self-copy" << endl;
	}

	cout << "assignment operator = " << mark << "/3" << endl << endl;
	return mark;
}


void basicTest()
{
	Sequence sq1;
	double numbers[] = { 1.1,2.2,3.3 };
	int n = 3;

	sq1.insert(3.14);
	sq1.insert(numbers, n);

	int pies = sq1.find(3.14);
	int sqSize = sq1.size();
	double sqSum = sq1.sum();
	double sqMean = sq1.mean();
	double sqMedian = sq1.median();
	double sqStddev = sq1.stddev();

	Sequence sq2(sq1);
	Sequence sq3 = sq2.concatenate(sq1);

	cout << "end basic test" << endl;
}

