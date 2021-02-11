#pragma once
#include <iostream>
#include <vector>

class ComponentPair
{
private:
	int id;
	int firstComponent;
	int secondComponent;
	int count;
public:
	ComponentPair()
	{
		id = -1;
		firstComponent = -1;
		secondComponent = -1;
		count = 0;
	}

	ComponentPair(int fc, int sc)
	{
		id = -1;
		firstComponent = fc;
		secondComponent = sc;
		count = 0;
	}

	ComponentPair(int fc, int sc, int c)
	{
		id = -1;
		firstComponent = fc;
		secondComponent = sc;
		count = c;
	}

	int getID()
	{
		return id;
	}

	int first()
	{
		return firstComponent;
	}

	int second()
	{
		return secondComponent;
	}

	int showCount()
	{
		return count;
	}

	void setFirst(int fc)
	{
		firstComponent = fc;
	}

	void setSecond(int sc)
	{
		secondComponent = sc;
	}

	void setCount(int c)
	{
		count = c;
	}

	void incrementCount()
	{
		count++;
	}

	void decrementCount()
	{
		count--;
	}

	void resetCount()
	{
		count = 0;
	}
};

class TestCase
{
private:
	std::vector<int> testComponents;
	int newPairs;
public:
	TestCase(int factors)
	{
		testComponents = std::vector<int>(factors, -1);
		newPairs = 0;
	}

	int newPairsCount()
	{
		return newPairs;
	}

	int testSize()
	{
		return testComponents.size();
	}

	int atIndex(int index)
	{
		return testComponents[index];
	}

	void setNewPairs(int numPairs)
	{
		newPairs = numPairs;
	}

	void incrementNewPairs()
	{
		newPairs++;
	}

	void decrementNewPairs()
	{
		newPairs--;
	}

	void setComponent(int factor, int componentNumber)
	{
		testComponents[factor] = componentNumber;
	}

	void printTestCase()
	{
		//std::cout << "Components: ";
		for (int i = 0; i != testComponents.size(); i++)
		{
			std::cout << testComponents[i] << " ";
		}
		std::cout << std::endl;
	}
};