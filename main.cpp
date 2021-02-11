#include "aetgfunctions.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <numeric>
#include <random>

using namespace std;

int main()
{
	//int factors = 0, levels = 0;
	//
	//cout << "Enter the number of factors: ";
	//cin >> factors;
	//cout << "Enter the number of levels per factor: ";
	//cin >> levels;
	//
	//vector<ComponentPair> pairs = makePairs(factors, levels);
	//
	//printPairs(pairs);
	//cout << endl;

	//srand(time(NULL));
	srand(rand() ^ time(0));
	//for (int i = 0; i < 10; i++)
	//{
	//	cout << rand() % factors << endl;
	//}
	
	/*
	vector<int> mixedLevels;
	cout << "Enter the number of factors: ";
	cin >> factors;
	for (int i = 0; i < factors; i++)
	{
		cout << "Enter the number of levels in factor " << i << ": ";
		cin >> levels;
		mixedLevels.push_back(levels);
	}

	//vector<int> mixedLevels{6, 5, 4, 3, 2};
	vector<ComponentPair> pairs = makeMCAPairs(factors, mixedLevels);

	printPairs(pairs);
	*/
	vector<TestCase> testSuite;
	vector<vector<TestCase>> bestSuites;
	vector<int> testL(20, 10);
	vector<int> testML{ 6, 5, 4, 3, 2 };
	vector<int> testSL{ 10, 9, 8, 7, 6, 5, 4, 3, 2 };
	unsigned int smallestSuiteSize = 10000;
	unsigned int largestSuiteSize = 0;
	int totalCases = 0;

	vector<int> factorBegin = factorStartingNums(testL);

	int totalComponents = countComponents(testL);
	for (int i = 0; i != 10; i++)
	{
		testSuite.clear();
		//cout << "TEST SUITE " << i + 1 << endl;
		vector<vector<int>> grid = componentGrid(testL.size(), testL, totalComponents);
		vector<int> pairsRemaining = initializeUncovered(testL, totalComponents);

		//printGrid(grid);

		//cout << "INITIAL Pairs remaining: " << endl;
		//for (int j = 0; j != pairsRemaining.size(); j++)
		//{
		//	cout << "Component " << j << ": " << pairsRemaining[j] << endl;
		//}
		//cout << endl;

		TestCase tester = firstTestGenerator(testL.size(), testL, grid);
		addToSuite(tester, grid, pairsRemaining);
		testSuite.push_back(tester);
		//cout << "# cases: 1" << endl;
		//tester.printTestCase();

		//cout << "Pairs remaining: " << endl;
		//for (int j = 0; j != pairsRemaining.size(); j++)
		//{
		//	cout << "Component " << j << ": "<< pairsRemaining[j] << endl;
		//}
		//cout << endl;

		//TestCase ourSelection = selectCandidate(testML.size(), testML, pairsRemaining, factorBegin, totalComponents, grid);
		//testGenerator(testML.size(), testML, pairsRemaining, factorBegin, totalComponents, grid);

		//addToSuite(ourSelection, grid, pairsRemaining);
		//ourSelection.printTestCase();
		//cout << "*&*&*&*&*&*&*&*&*&*&*&*" << endl;
		//cout << "Pairs remaining: " << endl;
		//for (int j = 0; j != pairsRemaining.size(); j++)
		//{
		//	cout << "Component " << j << ": " << pairsRemaining[j] << endl;
		//}
		//cout << endl;

		int counter = 1;
		while (*max_element(pairsRemaining.begin(), pairsRemaining.end()) != 0)
		{
			TestCase nextSelection = selectCandidate(testL.size(), testL, pairsRemaining, factorBegin, totalComponents, grid);
			addToSuite(nextSelection, grid, pairsRemaining);
			testSuite.push_back(nextSelection);
			counter++;
			//cout << "# cases: " << counter << endl;
			//cout << "Pairs remaining: " << endl;
			//for (int j = 0; j != pairsRemaining.size(); j++)
			//{
			//	cout << "Component " << j << ": " << pairsRemaining[j] << endl;
			//}
			//cout << endl;
		}

		//cout << "Size: " << testSuite.size() << endl;

		if (testSuite.size() < smallestSuiteSize)
		{
			smallestSuiteSize = testSuite.size();
			bestSuites.clear();
			bestSuites.push_back(testSuite);
		}
		else if (testSuite.size() == smallestSuiteSize)
		{
			bestSuites.push_back(testSuite);
		}
		else
		{
			//nothing. continue?
		}
		
		if (testSuite.size() > largestSuiteSize)
		{
			largestSuiteSize = testSuite.size();
		}
		
		totalCases += testSuite.size();

		//cout << "Smallest suite size so far: " << smallestSuiteSize << endl;
		//cout << "Largest suite size so far: " << largestSuiteSize << endl;
		//cout << "Total cases so far: " << totalCases << endl;
		//for (int i = 0; i != 26; i++)
		//{
		//	TestCase nextSelection = selectCandidate(testML.size(), testML, pairsRemaining, factorBegin, totalComponents, grid);
		//	addToSuite(nextSelection, grid, pairsRemaining);
		//	
		//	cout << "Pairs remaining: ";
		//	for (int j = 0; j != pairsRemaining.size(); j++)
		//	{
		//		cout << pairsRemaining[j] << " ";
		//	}
		//	cout << endl;
		//}

		//cout << "----------------" << endl;
		//tester.printTestCase();
		//cout << "*** " << tester.newPairsCount() << " ***" << endl;
		//
		//tester.setNewPairs(0);
		//cout << "*** " << tester.newPairsCount() << " ***" << endl;

		//printGrid(grid);
	}

	//show all best suites
	//for (int i = 0; i != bestSuites.size(); i++)
	//{
	//	cout << "Best test suite " << i + 1 << endl;
	//	cout << endl;
	//	cout << bestSuites[i].size() << endl;
	//	cout << endl;
	//	for (int j = 0; j != bestSuites[i].size(); j++)
	//	{
	//		bestSuites[i][j].printTestCase();
	//	}
	//	cout << endl;
	//}

	//select one of the best suites
	vector<TestCase> selectedSuite = bestSuites[rand() % bestSuites.size()];
	cout << "*******************************" << endl;
	cout << selectedSuite.size() << endl;
	cout << endl;
	for (int i = 0; i != selectedSuite.size(); i++)
	{
		selectedSuite[i].printTestCase();
	}
	cout << "*******************************" << endl;

	cout << "Smallest suite size: " << smallestSuiteSize << endl;
	cout << "Largest suite size: " << largestSuiteSize << endl;
	cout << "Average suite size (truncated): " << totalCases / 10 << endl;

	return 0;
}