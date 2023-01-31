#include "userDefinedFunctions.h"

#include <vector>
#include<algorithm>
#include <iostream>

using namespace std;

typedef struct generateHelpersReturns Struct;

Struct GenerateHelpers(std::vector<std::vector<int>> Hsys, int failedSymbolID, std::vector<int> lostLDPCChunkSymbols, std::vector<std::vector<int>> allEquationsR2)
{
	Struct ghrLocal;

	std::vector<int> helperSymbolIndexes{};
	int M, I;
	std::vector<int> currentRows;
	std::vector<int> foundIndexes;
	std::vector<std::vector<int>> subMatrix;
	std::vector<int> deleteRows{};
	int stopState = 0;
	int baseStationUsage;
	// std::vector<int> equationScores(subMatrix.size(), 0);
	// std::vector<int> numberofSymbolsInEquations(subMatrix.size(), 0);
	std::vector<int> equationScores;
	std::vector<int> numberofSymbolsInEquations;
	std::vector<int> currentColumns;
	std::vector<int> helperSymbols;
	std::vector<int> usedCols;
	std::vector<int> minValues;
	int em;
	[[maybe_unused]] int ei;
	std::vector<int> Helpers{};
	// std::vector<int> helperSymbolIndexes{};

	// Finding rows which are equal to 1 on the column which is equal to the lost chunk index in the systematic H matrix
	for (size_t r = 0; r < Hsys.size(); r++)
	{
		if (Hsys[r][failedSymbolID] == 1)
			foundIndexes.push_back(r);
	}
	currentRows = foundIndexes; //Find in matlab
	//currentRows = find(Hsys(:, failedSymbolID) == 1);
	
	//std::vector<std::vector<unsigned long int>> subMatrix{};
	subMatrix.resize(currentRows.size());
	for (size_t r = 0; r < currentRows.size(); r++)
	{
		for (size_t c = 0; c < Hsys[0].size(); c++)
		{
			subMatrix[r].push_back(Hsys[currentRows[r]][c]);
		}
		subMatrix[r][failedSymbolID] = 0;
	}
	
	//subMatrix = Hsys(currentRows, :);
	//subMatrix(:, failedSymbolID) = 0;
	foundIndexes.clear();
	
	for (size_t i = 0; i< subMatrix.size(); i++)
	{
		for (size_t c = 0; c < lostLDPCChunkSymbols.size(); c++)
		{
			if (subMatrix[i][lostLDPCChunkSymbols[c]] == 1)
				foundIndexes.push_back(c);
		}
		if (foundIndexes.size() > 0)
			deleteRows.push_back(i);		
	}
	
	for (size_t r = 0; r< subMatrix.size(); r++)
	{
		for (size_t c = 0; c < subMatrix[0].size(); c++)
		{
			if (subMatrix[r][c] != 0)
			{
				stopState = 1;
				break;
			}			
		}
		if (stopState == 1)
			break;
	}
	cout << "We are here in GenerateHelpers 0" << endl;
	//currentRows.size();
	cout << "We are here in GenerateHelpers 1 deleteRows.size()"<<deleteRows.size() << endl;
	if((deleteRows.size() < currentRows.size()) & (stopState == 1))
	{
		cout << "We 1.0.0\n";
		for (size_t c = 0; c < deleteRows.size(); c++)
		{
			cout << "We 1.0 subMatrix.size()"<<subMatrix.size()<<"\n";
			subMatrix.erase(subMatrix.begin() + deleteRows[c]);
			for (size_t x = 0; x < deleteRows.size(); x++)
			{
				deleteRows[x] =deleteRows[x]-1;
			}
			      
		}
		//subMatrix(deleteRows, :) = [];
		baseStationUsage = 0;
		cout << "We after subMatrix.size()\n";
	}
	else
		baseStationUsage = 1;
	
	cout << "We are here in GenerateHelpers 2" << endl;
	for (size_t k = 0; k < subMatrix.size(); k++)
	{
		for (size_t c = 0; c < subMatrix[0].size(); c++)
		{
			if (subMatrix[k][c] == 1)
				currentColumns.push_back(c);
		}
		//currentColumns = find(subMatrix(k, :) == 1);
		numberofSymbolsInEquations.push_back(currentColumns.size());
	}
	cout << "We are here in GenerateHelpers 3" << endl;
	if (baseStationUsage == 0)
	{
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
		for (size_t k = 0; k < subMatrix.size(); k++)
		{
			//equationScores.push_back(0);
			
			for (size_t c = 0; c < subMatrix[0].size(); c++)
			{
				if (subMatrix[k][c] == 1)
					usedCols.push_back(c);
			}
			for (size_t uc = 0; uc < usedCols.size(); uc++)
			{
				for (size_t ls = 0; ls < lostLDPCChunkSymbols.size(); ls++)
				{
					if (usedCols[uc] == lostLDPCChunkSymbols[ls])
					{
						currentColumns.push_back(usedCols[uc]);
						break;
					}				
				}
			}
			//equationScores[k] = currentColumns.size();
			equationScores.push_back(currentColumns.size());
			cout << "We are here in GenerateHelpers 2" << endl;
			helperSymbols = usedCols;
			helperSymbols.insert(helperSymbols.begin(), failedSymbolID);
			allEquationsR2.push_back(helperSymbols);
			usedCols.clear();
			currentColumns.clear();
		}
		cout << "We are here in GenerateHelpers 3_1" << endl;

		// cout << "subMatrix: " << endl;
		// for (size_t r = 0; r < subMatrix.size(); r++)
		// {
		// 	for (size_t c = 0; c < subMatrix[r].size(); c++)
		// 	{
		// 		cout << subMatrix[r][c] << " " ;
		// 	}
		// 	cout << endl;
		// }
		// cout << "size of subMatrix: " << subMatrix.size() << endl;
		// cout << "size of equationScores: " << equationScores.size() << endl;
		em = equationScores[0];
		// cout << "em: " << em << endl;
		ei = 0;
		for (size_t i = 1; i < equationScores.size(); i++)
		{
			if (equationScores[i] < em)
			{
				em = equationScores[i];
				ei = i;
			}
		}

		//cout << "We are here in GenerateHelpers 3_2" << endl;
		for (size_t i = 0; i < equationScores.size(); i++)
		{
			if (equationScores[i] == em)
				minValues.push_back(i);
		}
		//minValues = find(equationScores == min(equationScores));
		//cout << "We are here in GenerateHelpers 3_3" << endl;
		if (minValues.size() > 1)
		{
			int subM = numberofSymbolsInEquations[minValues[0]];
			int subI = 0;
			for (size_t i = 1; i < minValues.size(); i++)
			{
				if (numberofSymbolsInEquations[minValues[i]] < subM)
				{
					subM = numberofSymbolsInEquations[minValues[i]];
					subI = i;
				}
			}
			I = minValues[subI];
		}
		else
			I = minValues[0];

		minValues.clear();
	}
	//cout << "We are here in GenerateHelpers 4" << endl;
	// Selecting the column whose size is minimum
	Helpers.clear();	
	for (size_t c = 0; c < subMatrix[0].size(); c++)
	{
		Helpers.push_back(subMatrix[I][c]);
	}
	//Helpers = subMatrix(I, :);
	//cout << "We are here in GenerateHelpers 5" << endl;
	for (size_t c = 0; c < Helpers.size(); c++)
	{
		if (Helpers[c] == 1)
			helperSymbolIndexes.push_back(c);
	}
	//helperSymbolIndexes = find(Helpers == 1);
	//cout << "We are here in GenerateHelpers 6" << endl;
	ghrLocal.helperSymbolIndexes = helperSymbolIndexes;
	ghrLocal.allEquationsR2 = allEquationsR2;
	//cout << "We are here in GenerateHelpers 7" << endl;
	return ghrLocal;
}