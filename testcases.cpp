#include "aetgfunctions.h"
#include <algorithm>
#include <numeric>
#include <random>

using namespace std;

TestCase firstTestGenerator(int factors, vector<int> levels, vector<vector<int>>& grid)
{
	TestCase firstCase(factors);
	vector<int> factorOrder(factors);
	int currentComponent = -1;
	int factorStart = 0;

	factorShuffle(factorOrder);

	//find ordered ordered component randomly
	for (int i = 0; i != factorOrder.size(); i++)
	{
		factorStart = 0;
		//for current factor, get the starting component number
		for (int j = 0; j != factorOrder[i]; j++)
		{
			factorStart += levels[j];
		}
		
		currentComponent = factorStart + (rand() % levels[factorOrder[i]]);
		firstCase.setComponent(factorOrder[i], currentComponent);
		
		//cout << "----------------------------" << endl;
		//firstCase.printTestCase();
	}
	countNewPairs(firstCase, grid);
	
	return firstCase;
}

TestCase testGenerator(int factors, vector<int> levels, vector<int> pairsRemaining, vector<int> factorBegin, int totalComponents, vector<vector<int>>& grid)
{
	TestCase testCase(factors);
	vector<int> factorOrder(factors);
	vector<int> maxPairs;
	int maxPairsLeft = 0;
	int currentFactor = -1;
	int selectedComponent = -1;
	int numFactorsSelected = 0;

	//randomize order for factor selection
	factorShuffle(factorOrder);

	currentFactor = factorOrder[0];
	//find the max number of remaining pairs from the currently selected factor's components
	maxPairsLeft = *max_element(pairsRemaining.begin() + factorBegin[currentFactor], pairsRemaining.begin() + factorBegin[currentFactor] + levels[currentFactor]);

	cout << "CHECK MAX PAIRS FOR FACTOR " << factorOrder[0] << ": " << maxPairsLeft << endl;

	//add any component in the current factor with the max number of remaining pairs to a vector (vector<int> maxPairs)
	for (int i = factorBegin[currentFactor]; i != factorBegin[currentFactor] + levels[currentFactor]; i++)
	{
		if (pairsRemaining[i] == maxPairsLeft)
		{
			maxPairs.push_back(i);
		}
	}
	//use rand() % maxPairs.size() to select a component
	selectedComponent = rand() % maxPairs.size();
	//cout << "----HERE ARE ALL COMPONENTS WITH MAX PAIRS LEFT----" << endl;
	//for (int n = 0; n != maxPairs.size(); n++)
	//{
	//	cout << maxPairs[n] << endl;
	//}

	//cout << "WE SELECTED COMPONENT " << maxPairs[selectedComponent] << "!!!" << endl;
	//add selected component to the test case in the correct factor position
	testCase.setComponent(currentFactor, maxPairs[selectedComponent]);
	numFactorsSelected++;
	//testCase.printTestCase();
	
	int totalNewPairs = 0;

	for (int i = 1; i != factorOrder.size(); i++)
	{
		currentFactor = factorOrder[i];
		//**********************************************************************************************
		//move to next factor
		//for each component in this factor, check how many pairs they make with previous factor selections

		int possiblePairs = 0;
		int currentMaxPairs = 0;
		maxPairs.clear(); //<---this was moved outside of first for loop's scope
		for (int i = factorBegin[currentFactor]; i != factorBegin[currentFactor] + levels[currentFactor]; i++)
		{
			possiblePairs = 0;
			for (int j = 0; j != numFactorsSelected; j++)
			{
				if (grid[i][testCase.atIndex(factorOrder[j])] == 0)
				{
					possiblePairs++;
				}
			}
			if (possiblePairs > currentMaxPairs)
			{
				currentMaxPairs = possiblePairs;
				//reset vector with just this component in it. it just took the crown of the max pairs option.
				maxPairs.clear();
				maxPairs.push_back(i);
			}
			else if (possiblePairs == currentMaxPairs)
			{
				//pushback into vector as a max pair candidate
				maxPairs.push_back(i);
			}
			else
			{
				//component doesn't have max pairs remaining to make
				//continue?
			}
		}
		//use rand() % maxPairs.size() to select a component
		selectedComponent = rand() % maxPairs.size();
		//cout << "----HERE ARE ALL COMPONENTS WITH MAX PAIRS LEFT----" << endl;
		//for (int n = 0; n != maxPairs.size(); n++)
		//{
		//	cout << maxPairs[n] << endl;
		//}

		//cout << "WE SELECTED COMPONENT " << maxPairs[selectedComponent] << "!!!" << endl;
		//add selected component to the test case in the correct factor position
		testCase.setComponent(currentFactor, maxPairs[selectedComponent]);
		numFactorsSelected++;
		//testCase.printTestCase();

		totalNewPairs += currentMaxPairs;
		cout << "Total new pairs so far: " << totalNewPairs << endl;
	}
	//**********************************************************************************************
	//consider that there may be multiple options which will make the most new pairs
	//select the component which will make the most new pairs (maybe keep count of pairs here)
	//repeat this process for each consecutive factor until finished
	
	testCase.setNewPairs(totalNewPairs);
	cout << "Final new pairs for this test: " << testCase.newPairsCount() << endl;

	return testCase;
}

void factorShuffle(vector<int>& factorOrder)
{
	for (int i = 0; i != factorOrder.size(); i++)
	{
		factorOrder[i] = i;
		//cout << i << ": " << factorOrder[i] << endl;
	}

	random_device device;
	auto randomNums = default_random_engine{ device() };
	shuffle(factorOrder.begin(), factorOrder.end(), randomNums);

	//for (auto&& i : factorOrder) {
	//	cout << i << ' ';
	//}
	//cout << endl;
}

void countNewPairs(TestCase& currentTestCase, vector<vector<int>>& grid)
{
	int newPairCounter = 0;
	for (int i = 0; i != currentTestCase.testSize(); i++)
	{
		for (int j = i+1; j != currentTestCase.testSize(); j++)
		{
			if (grid[currentTestCase.atIndex(i)][currentTestCase.atIndex(j)] == 0)
			{
				newPairCounter++;
			}
		}
	}
	currentTestCase.setNewPairs(newPairCounter);
}

TestCase selectCandidate(int factors, vector<int> levels, vector<int> pairsRemaining, vector<int> factorBegin, int totalComponents, vector<vector<int>>& grid)
{
	vector<TestCase> candidates;
	int currentMaxPairs = 0;
	int selectedTest = -1;

	for (int i = 0; i != 1; i++)
	{
		cout << "+++++++++++++ATTEMPTING NEW TEST CASE+++++++++++++" << endl;
		TestCase newTest = testGenerator(factors, levels, pairsRemaining, factorBegin, totalComponents, grid);

		if (newTest.newPairsCount() > currentMaxPairs)
		{
			currentMaxPairs = newTest.newPairsCount();
			candidates.clear();
			candidates.push_back(newTest);
		}
		else if (newTest.newPairsCount() == currentMaxPairs)
		{
			candidates.push_back(newTest);
		}
		else
		{
			//nothing. continue?
		}
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	}
	selectedTest = rand() % candidates.size();
	
	//cout << "&&&&&&&&&&&&&&&& OUR SELECTED CASE &&&&&&&&&&&&&&&&" << endl;
	candidates[selectedTest].printTestCase();
	//cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;

	return candidates[selectedTest];
}

void addToSuite(TestCase currentTestCase, vector<vector<int>>& grid, vector<int>& pairsRemaining)
{
	for (int i = 0; i != currentTestCase.testSize(); i++)
	{
		for (int j = i + 1; j != currentTestCase.testSize(); j++)
		{
			if (grid[currentTestCase.atIndex(i)][currentTestCase.atIndex(j)] == 0)
			{
				grid[currentTestCase.atIndex(i)][currentTestCase.atIndex(j)] = 1;
				grid[currentTestCase.atIndex(j)][currentTestCase.atIndex(i)] = 1;

				if (pairsRemaining[currentTestCase.atIndex(i)] > 0)
				{
					pairsRemaining[currentTestCase.atIndex(i)]--;
				}

				if (pairsRemaining[currentTestCase.atIndex(j)] > 0)
				{
					pairsRemaining[currentTestCase.atIndex(j)]--;
				}
			}
		}
	}
}