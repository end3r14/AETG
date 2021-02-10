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
	
	vector<int> testL(20, 10);
	vector<int> testML{ 6, 5, 4, 3, 2 };
	
	vector<int> factorBegin = factorStartingNums(testML);

	int totalComponents = countComponents(testML);
	vector<vector<int>> grid = componentGrid(testML.size(), testML, totalComponents);
	vector<int> pairsRemaining = initializeUncovered(testML, totalComponents);

	cout << "INITIAL Pairs remaining: " << endl;
	for (int j = 0; j != pairsRemaining.size(); j++)
	{
		cout << "Component " << j << ": " << pairsRemaining[j] << endl;
	}
	cout << endl;

	TestCase tester = firstTestGenerator(testML.size(), testML, grid);
	addToSuite(tester, grid, pairsRemaining);
	tester.printTestCase();
	
	cout << "Pairs remaining: " << endl;
	for (int j = 0; j != pairsRemaining.size(); j++)
	{
		cout << "Component " << j << ": "<< pairsRemaining[j] << endl;
	}
	cout << endl;

	TestCase ourSelection = selectCandidate(testML.size(), testML, pairsRemaining, factorBegin, totalComponents, grid);
	//testGenerator(testML.size(), testML, pairsRemaining, factorBegin, totalComponents, grid);
	
	addToSuite(ourSelection, grid, pairsRemaining);
	ourSelection.printTestCase();
	cout << "*&*&*&*&*&*&*&*&*&*&*&*" << endl;
	cout << "Pairs remaining: " << endl;
	for (int j = 0; j != pairsRemaining.size(); j++)
	{
		cout << "Component " << j << ": " << pairsRemaining[j] << endl;
	}
	cout << endl;

	while (*max_element(pairsRemaining.begin(), pairsRemaining.end()) != 0)
	{
		TestCase nextSelection = selectCandidate(testML.size(), testML, pairsRemaining, factorBegin, totalComponents, grid);
		addToSuite(nextSelection, grid, pairsRemaining);

		cout << "Pairs remaining: " << endl;
		for (int j = 0; j != pairsRemaining.size(); j++)
		{
			cout << "Component " << j << ": " << pairsRemaining[j] << endl;
		}
		cout << endl;
	}
	
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
	cout << "*** " << tester.newPairsCount() << " ***" << endl;
	
	tester.setNewPairs(0);
	cout << "*** " << tester.newPairsCount() << " ***" << endl;

	printGrid(grid);

	return 0;
}