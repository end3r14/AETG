#include "aetgfunctions.h"
#include <iomanip>
#include <numeric>

using namespace std;

/** 
 *  
 *  Creates an array of all possible pairs of components based
 *  on number of factors and levels per factor.
 *  
 *	This function is used for factors with equal number of levels.
 * 
 */
vector<ComponentPair> makePairs(int factors, int levels)
{
	//calculate total number of components, and track which numbers start new factors, one at a time
	//ex: 0 1 2 | 3 4 5 | 6 7 8 <--- 9 components, '3' and '6' are the next factors' first numbers
	int totalComponents = factors * levels;
	int nextFactorStart = levels;
	vector<ComponentPair> pairs;
	
	//select first component in a pair, excluding the last factor's levels
	for (int i = 0; i < (totalComponents - levels); i++)
	{
		//select second components in each pair and store
		for (int j = nextFactorStart; j < totalComponents; j++)
		{
			pairs.push_back(ComponentPair(i, j));
		}
		
		//when finished with a factor's levels, update the next factor's first number
		if ((i + 1) % levels == 0)
		{
			nextFactorStart += levels;
		}
	}
	
	return pairs;
}

/**
 *
 *  Creates an array of all possible pairs of components based
 *  on number of factors and levels per factor.
 *
 *	This function is used for factors with mixed number of levels.
 *
 */
vector<ComponentPair> makeMCAPairs(int factors, vector<int> levels)
{
	//calculate total number of components
	int totalComponents = 0;
	for (int i = 0; i != levels.size(); i++)
	{
		totalComponents += levels[i];
	}
	cout << totalComponents << endl;

	//track which numbers start new factors, one at a time
	//ex: 0 1 2 3 | 4 5 6 | 7 8 <--- 9 components, '4' and '7' are the next factors' first numbers
	int currentFactor = 0;
	int nextFactorStart = levels[currentFactor];
	vector<ComponentPair> pairs;

	//select first component in a pair, excluding the last factor's levels
	for (int i = 0; i < (totalComponents - levels[levels.size()-1]); i++)
	{
		//select second components in each pair and store
		for (int j = nextFactorStart; j < totalComponents; j++)
		{
			pairs.push_back(ComponentPair(i, j));
		}

		//when finished with a factor's levels, update the next factor's first number
		if ((i + 1) % nextFactorStart == 0)
		{
			currentFactor++;
			//ensure that no out of bounds errors occur
			if (currentFactor != levels.size())
			{
				nextFactorStart += levels[currentFactor];
			}
		}
	}

	return pairs;
}

/**
 *
 *	Prints all pairs stored in the component pair array.
 *	
 *	This function works for factors with either fixed or mixed levels.
 *
 */
void printPairs(vector<ComponentPair> pairs)
{
	//print formatted version of each pair on a new line
	for (int i = 0; i != pairs.size(); i++)
	{
		cout << "(" << pairs[i].first() << ", " << pairs[i].second() << ")" << endl;
	}
}

int countComponents(vector<int>& levels)
{
	int totalComponents = accumulate(levels.begin(), levels.end(), 0);
	//cout << "total: " << totalComponents << endl;
	
	return totalComponents;
}

vector<vector<int>> componentGrid(int factors, vector<int> levels, int totalComponents)
{
	vector<vector<int>> grid(totalComponents, vector<int>(totalComponents, 0));
	int currentFactor = 0;
	int currentFactorStart = 0;
	int nextFactorStart = currentFactorStart + levels[currentFactor];

	while (currentFactor != (levels.size() - 1))
	{
		//for each level in each factor, don't combine with levels in the same factor
		for (int i = currentFactorStart; i != nextFactorStart; i++)
		{
			for (int j = currentFactorStart; j != nextFactorStart; j++)
			{
				grid[i][j] = -1;
			}

			//when finished with a factor's levels, update the next factor's first number
			if ((i + 1) % nextFactorStart == 0 && currentFactor != (levels.size() - 1))
			{
				currentFactor++;
				currentFactorStart = nextFactorStart;
				nextFactorStart += levels[currentFactor];
			}
		}
	}

	return grid;
}

void printGrid(vector<vector<int>> &grid)
{
	for (int i = 0; i != grid.size(); i++)
	{
		cout << "outer " << setw(3) << i << ": ";
		for (int j = 0; j != grid[i].size(); j++)
		{
			if (grid[i][j] == 0)
			{
				cout << "-";
			}
			else if (grid[i][j] == -1)
			{
				cout << "x";
			}
			else
			{
				cout << grid[i][j];
			}
		}
		cout << endl;
	}
}

vector<int> initializeUncovered(vector<int>& levels, int totalComponents)
{
	vector<int> uncoveredCount(totalComponents);
	int currentFactor = 0;
	int currentFactorStart = 0;
	int nextFactorStart = currentFactorStart + levels[currentFactor];

	for (int i = currentFactorStart; i != nextFactorStart; i++)
	{
		uncoveredCount[i] = totalComponents - levels[currentFactor];

		//when finished with a factor's levels, update the next factor's first number
		if ((i + 1) % nextFactorStart == 0 && currentFactor != (levels.size() - 1))
		{
			currentFactor++;
			currentFactorStart = nextFactorStart;
			nextFactorStart += levels[currentFactor];
		}
	}
	
	//cout << "UNCOVERED COUNT" << endl;
	//for (int i = 0; i != uncoveredCount.size(); i++)
	//{
	//	cout << "Component " << i << ": " << uncoveredCount[i] << endl;
	//}
	//cout << "---------------" << endl;

	return uncoveredCount;
}

vector<int> factorStartingNums(vector<int>& levels)
{
	vector<int> factorBegin(levels);

	int currentNum = 0;
	for (int i = 0; i != factorBegin.size(); i++)
	{
		factorBegin[i] = currentNum;
		currentNum += levels[i];
	}
	//cout << "STARTING POSITIONS" << endl;
	//for (int i = 0; i != factorBegin.size(); i++)
	//{
	//	cout << i << ": " << factorBegin[i] << endl;
	//}
	//cout << "++++++++++++++++++" << endl;

	return factorBegin;
}