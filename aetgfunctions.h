#pragma once
#include "aetgstructs.h"

//definitions found in pairs.cpp
std::vector<ComponentPair> makePairs(int factors, int levels);
std::vector<ComponentPair> makeMCAPairs(int factors, std::vector<int> levels);
void printPairs(std::vector<ComponentPair> pairs);
int countComponents(std::vector<int>& levels);
std::vector<std::vector<int>> componentGrid(int factors, std::vector<int> levels, int totalComponents);
void printGrid(std::vector<std::vector<int>> &grid);
std::vector<int> initializeUncovered(std::vector<int>& levels, int totalComponents);
std::vector<int> factorStartingNums(std::vector<int>& levels);

//definitions found in testcases.cpp
TestCase firstTestGenerator(int factors, std::vector<int> levels, std::vector<std::vector<int>>& grid);
TestCase testGenerator(int factors, std::vector<int> levels, std::vector<int> pairsRemaining, std::vector<int> factorBegin, int totalComponents, std::vector<std::vector<int>>& grid);
void factorShuffle(std::vector<int>& factorOrder);
void countNewPairs(TestCase& currentTestCase, std::vector<std::vector<int>>& grid);
TestCase selectCandidate(int factors, std::vector<int>& levels, std::vector<int>& pairsRemaining, std::vector<int>& factorBegin, int totalComponents, std::vector<std::vector<int>>& grid);
void addToSuite(TestCase currentTestCase, std::vector<std::vector<int>>& grid, std::vector<int>& pairsRemaining);