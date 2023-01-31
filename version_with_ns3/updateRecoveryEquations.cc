#include "userDefinedFunctions.h"

#include <vector>
#include <iostream>

using namespace std;

typedef struct updateRecoveryEquationsReturns Struct;

Struct updateRecoveryEquations(int failedSymbolID, std::vector<int> lostLDPCChunkSymbols, std::vector<std::vector<int>> allEquationsR2, std::vector<std::vector<int>> allEquationsR2ReducedCopy)
{
	Struct urerLocal;

	std::vector<int> relatedIndexes;
	std::vector<std::vector<int>> relatedEquations;
	std::vector<std::vector<int>> relatedEquationsReduced;
	int baseStationUsage, M, I, minEquationScore, subM, subI;
	std::vector<int> currentColumns{}, minValues{};
	std::vector<int> selectedEquation, selectedEquationReduced;
	std::vector<int> deleteRows{};
	int breakState = 0;
	// std::vector<int> equationScores;
	// std::vector<int> numberofSymbolsInEquations;
	std::vector<int> usedSymbols{};
	//cout << "We are here in updateRecoveryEquations 1" << endl;
	for (size_t r = 0; r < allEquationsR2.size(); r++)
	{
		if (allEquationsR2[r][0] == failedSymbolID)
			relatedIndexes.push_back(r);
	}
	//relatedIndexes = find(allEquationsR2(:, 1) == failedSymbolID);
	//cout << "We are here in updateRecoveryEquations 2" << endl;
	for (size_t i = 0; i < relatedIndexes.size(); i++)
	{
		//for (int j = 0; j < allEquationsR2[0].size(); j++)
		//	relatedEquations[i].push_back(allEquationsR2[relatedIndexes[i]][j]);
		relatedEquations.push_back(allEquationsR2[relatedIndexes[i]]);

		//for (int j = 0; j < allEquationsR2ReducedCopy[0].size(); j++)
		//	relatedEquationsReduced[i].push_back(allEquationsR2ReducedCopy[relatedIndexes[i]][j]);
		relatedEquationsReduced.push_back(allEquationsR2ReducedCopy[relatedIndexes[i]]);
	}		
	//cout << "We are here in updateRecoveryEquations 3" << endl;
	for (size_t i = 0; i < relatedEquations.size(); i++)
	{
		for (size_t c = 1; c < relatedEquations[i].size(); c++)
		{
			for (size_t l = 1; l < lostLDPCChunkSymbols.size(); l++)
			{
				if (relatedEquations[i][c] == lostLDPCChunkSymbols[l])
				{
					deleteRows.push_back(i);
					breakState = 1;
					break;
				}
			}
			if (breakState == 1)
				break;
		}
		breakState = 0;
	}
	//cout << "We are here in updateRecoveryEquations 4" << endl;
	if (deleteRows.size() < relatedEquations.size())
	{
		for (size_t i = 0; i < deleteRows.size(); i++)
			relatedEquations.erase(relatedEquations.begin() + deleteRows[i]);
		//relatedEquations(deleteRows, :) = [];
		baseStationUsage = 0;
	}
	else
		baseStationUsage = 1;

	// cout << "failedSymbolID: " << failedSymbolID << endl;
	// cout << "allEquationsR2: " << endl;
	// for (size_t r = 0; r < allEquationsR2.size(); r++)
	// {
	// 	for (size_t c = 0; c < allEquationsR2[r].size(); c++)
	// 	{
	// 		cout << allEquationsR2[r][c] << " " ;
	// 	}
	// 	cout << endl;
	// }

	// cout << "relatedIndexes: " << endl;
	// for (size_t r = 0; r < relatedIndexes.size(); r++)
	// 	cout << relatedIndexes[r] << " " ;			
	// cout << endl;

	// cout << "relatedEquations: " << endl;
	// for (size_t r = 0; r < relatedEquations.size(); r++)
	// {
	// 	for (size_t c = 0; c < relatedEquations[r].size(); c++)
	// 	{
	// 		cout << relatedEquations[r][c] << " " ;
	// 	}
	// 	cout << endl;
	// }

	// equationScores.resize(relatedEquations.size());
	std::vector<int> equationScores (relatedEquations.size(),0);
	// numberofSymbolsInEquations.resize(relatedEquations.size());
	std::vector<int> numberofSymbolsInEquations(relatedEquations.size(), 0);
	//cout << "We are here in updateRecoveryEquations 5" << endl;
	for (size_t i = 0; i < relatedEquations.size(); i++)
	{
		for (size_t c = 1; c < relatedEquationsReduced[i].size(); c++)
		{
			if (relatedEquationsReduced[i][c] != -1)
				usedSymbols.push_back(relatedEquationsReduced[i][c]);
		}
		numberofSymbolsInEquations.push_back(usedSymbols.size());
		usedSymbols.clear();
	}
	//cout << "We are here in updateRecoveryEquations 6" << endl;
	if (baseStationUsage == 0)
	{
		//cout << "We are here in updateRecoveryEquations 6_1" << endl;
		M = numberofSymbolsInEquations[0];
		I = 0;
		for (size_t i = 1; i < numberofSymbolsInEquations.size(); i++)
		{
			if (numberofSymbolsInEquations[i] < M)
			{
				M = numberofSymbolsInEquations[i];
				I = i;
			}
		}
		//[M, I] = min(numberofSymbolsInEquations);
	}
	else
	{
		//cout << "We are here in updateRecoveryEquations 6_2" << endl;
		for (size_t k = 0; k < relatedEquationsReduced.size(); k++)
		{			
			for (size_t c = 1; c < relatedEquationsReduced[k].size(); c++)
			{
				for (size_t l = 1; l < lostLDPCChunkSymbols.size(); l++)
				{
					if (relatedEquationsReduced[k][c] == lostLDPCChunkSymbols[l])
						currentColumns.push_back(c);
				}
			}
			equationScores.push_back(currentColumns.size());
			currentColumns.clear();
		}
		//currentColumns = ismember(relatedEquationsReduced(k, 2:end), lostLDPCChunkSymbols);
		//cout << "We are here in updateRecoveryEquations 6_3" << endl;

		// cout << "size of allEquationsR2: " << allEquationsR2.size() << endl;
		// cout << "size of relatedEquations: " << relatedEquations.size() << endl;
		// cout << "size of relatedEquationsReduced: " << relatedEquationsReduced.size() << endl;
		// cout << "size of equationScores: " << equationScores.size() << endl;
		minEquationScore = equationScores[0];
		// cout << "minEquationScore: " << minEquationScore << endl;
		for (size_t i = 0; i < equationScores.size(); i++)
		{
			if (equationScores[i] < minEquationScore)
				minEquationScore = equationScores[i];
		}
		//cout << "We are here in updateRecoveryEquations 6_4" << endl;
		for (size_t i = 0; i < equationScores.size(); i++)
		{
			if (equationScores[i] == minEquationScore)
				minValues.push_back(i);
		}
		//minValues = find(equationScores == min(equationScores));
		//cout << "We are here in updateRecoveryEquations 6_5" << endl;
		if (minValues.size() > 1)
		{
			subM = minValues[0];
			subI = 0;
			for (size_t i = 0; i < minValues.size(); i++)
			{
				if (numberofSymbolsInEquations[minValues[i]] < subM)
				{
					subM = numberofSymbolsInEquations[minValues[i]];
					subI = minValues[i];
				}
			}
			I = minValues[subI];
		}
		else
			I = minValues[0];
	}
	//cout << "We are here in updateRecoveryEquations 7" << endl;
	// Selecting the column whose size is minimum
	selectedEquation = relatedEquations[I];
	selectedEquationReduced = relatedEquationsReduced[I];
	//selectedEquation = relatedEquations(I, :);
	//selectedEquationReduced = relatedEquationsReduced(I, :);

	urerLocal.selectedEquation = selectedEquation;
	urerLocal.selectedEquationReduced = selectedEquationReduced;
	//cout << "We are here in updateRecoveryEquations 8" << endl;
	return urerLocal;
}