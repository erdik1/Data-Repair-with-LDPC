#include "userDefinedFunctions.h"
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>
#include <cmath>
#include <filesystem>

using namespace std;

typedef struct singleRepairAlgorithmV1Returns Struct;

void transpose(std::vector<std::vector<uint8_t>> &b)
{
    if (b.size() == 0)
        return;

    std::vector<std::vector<uint8_t>> trans_vec(b[0].size(), std::vector<uint8_t>());

    for (size_t i = 0; i < b.size(); i++)
    {
        for (size_t j = 0; j < b[i].size(); j++)
        {
            trans_vec[j].push_back(b[i][j]);
        }
    }

    b = trans_vec;    // <--- reassign here
}

//Struct LDPCSingleRepairAlgorithmV1(std::vector<std::vector<int>> Hsys, std::vector<ns> nodeStr, int counterLeavingNodes, std::vector<int> leavingNodes, int numberofLDPCStorageNodes, int numberofInitialLDPCStorageNodes, double baseStationSize, std::vector<double> ldpcFileSizes, struct strP strParameters, struct strP strParameters2, int numberofRoundforBuffer, double blockSize, std::vector<int> aliveLDPCStorageNodes)
Struct LDPCSingleRepairAlgorithmV1(int foundOne, std::string repairedFile, std::vector<int> currentLostSymbols, std::vector<string> totalHelperFiles, int cols, int quotient, std::vector<std::vector<int>> Hsys, std::vector<ns> nodeStr, std::vector<int> lostLDPCChunkSymbols, struct strP strParameters, int numberofRoundforBuffer, std::vector<int> aliveLDPCStorageNodes, double blockSize, int maxColLength)
{
	Struct sraV1Local;
	struct generateHelpersReturns gHR;
	struct firstPhaseReturns fpr;
	struct secondPhaseReturns spr;
	
	// string root_directory = "C:\\Users/Erdi/Documents/Visual Studio 2015/Projects/HildegardvonBingen/HildegardvonBingen/files/";
	string root_directory = "scratch/testFolder/files/";
	//string root_directory = "files/";
	int numberofLostSymbols = currentLostSymbols.size();
	//cout << "numberofLostSymbols: " << numberofLostSymbols << endl;
	std::vector<int> currentLostLDPCChunkSymbols = lostLDPCChunkSymbols;

	FILE *repairedFileID;
	repairedFileID = fopen(repairedFile.c_str(), "a");

	// Generating helper symbol indexes for each lost symbol
	std::vector<int> L = currentLostSymbols;
	// int index1 = 0;
	// int index2 = 0;
	std::vector<std::vector<int>> R1;
	//std::vector<int> localR1;
	std::vector<std::vector<int>> R2;
	std::vector<int> localR2;
	//std::vector<std::vector<int>> recoveryEquations (numberofLostSymbols, vector<int>(cols - 1, 0));
	std::vector<std::vector<int>> recoveryEquations;
	recoveryEquations.resize(numberofLostSymbols);
	std::vector<int> unrepairedSymbolsfromNodes;
	std::vector<int> unrepairedSymbolsfromBS;
	std::vector<std::vector<int>> allEquationsR2;
	//std::vector<int> copyAllEquationsR2;
	std::vector<int>::iterator it;
	std::vector<int> v;
	int intR;
	int failedSymbolID;
	std::vector<int> helperSymbolIndexes;
	//std::vector<std::vector<int>> allEquations (recoveryEquations[0].size() + allEquationsR2[0].size(), std::vector<int>(std::max(recoveryEquations[0].size(), allEquationsR2.size() - 1)));
	std::vector<std::vector<int>> allEquations;
	// tempEquations = recoveryEquations;
	std::vector<std::vector<int>> tempEquations;
	std::vector<int> symbols;
	std::vector<int> fileIndexes;
	int tempVal;
	std::vector<string> inputFiles {};
	//std::vector<int> inputFileIDs {};
	std::vector<int> synchronisedFileIndexes{};
	std::vector<int> foundIndexes {};
	std::vector<std::ifstream *> inputFileIDs;
	string fileFullDirectory;

	std::vector<int> readIndexes(inputFiles.size(), 0);
	std::vector<uint8_t> read(quotient, 1);
	std::vector<std::vector<uint8_t>> encodedData;
	std::vector<std::vector<int>> R2ReducedCopy;
	std::vector<int> usedHelpers;
	std::vector<std::vector<int>> R2Reduced;
	std::vector<std::vector<int>> tempR2;
	std::vector<int> tempL;
	std::vector<int> tempUnrepairedSymbolsfromNodes;
	std::vector<int> tempUnrepairedSymbolsfromBS;
	std::vector<int> tempCurrentLostLDPCChunkSymbols;
	std::vector<std::vector<uint8_t>> readedDatainBuffer{};
	std::vector<uint8_t> readedEncodedData(maxColLength,0);
	int jj;
	int readIndex;
	std::vector<std::vector<int>> R1Temp;
	std::vector<std::vector<int>> R2Temp;
	std::vector<uint8_t> buffer2(quotient);
	// int bInd;
	char * buffer = new char[quotient];
	int stopState;
	int columnIndex;
	int currentColumnIndex;
	std::vector<int> inputFilesSize {};
	string path;
	int intersectionState;

	// for(size_t i = 0; i < nodeStr.size(); i++)
	// {
	// 	// if (nodeStr[i].encodingType == 1 && nodeStr[i].isLive == 0)
	// 	// {
	// 		cout << "nodeStr[i].nodeID: " << nodeStr[i].nodeID << endl;
	// 		cout << "nodeStr[i].logicalNodeID: " << nodeStr[i].logicalNodeID << endl;
	// 		cout << "nodeStr[i].fileName: " << nodeStr[i].fileName << endl;
	// 		cout << "nodeStr[i].isLive: " << nodeStr[i].isLive << endl;
	// 		cout << "nodeStr[i].encodingType: " << nodeStr[i].encodingType << endl;
	// 		cout << "nodeStr[i].repairedNodeID: " << nodeStr[i].repairedNodeID << endl;
	// 		cout << endl;
	// 	// }
	// }
	cout << "We are at the beginning of SingleRepairFile" << endl;
	// cout << "aliveLDPCStorageNodes: " ;
	// for (size_t t = 0; t < aliveLDPCStorageNodes.size(); t++)
	// {
	// 	cout << aliveLDPCStorageNodes[t] << " ";
	// }
	// cout << endl;

	// for (size_t t = 0; t < aliveLDPCStorageNodes.size(); t++)
	// {
	// 	if (aliveLDPCStorageNodes[t] == -1)
	// 	{
	// 		cout << "t: " << t << endl;
	// 		cout << "aliveLDPCStorageNodes[t]: " << aliveLDPCStorageNodes[t] << endl;
	// 	}
	// }
	// cout << endl;

	// cout << "size of numberofLostSymbols: " << numberofLostSymbols << endl;
	// cout << "quotient: " << quotient << endl;
	for (int index = 0; index < numberofLostSymbols; index++)
	{
		failedSymbolID = currentLostSymbols[index];
		cout << "We are here in SingleRepairFile 1" << endl;
		gHR = GenerateHelpers(Hsys, failedSymbolID, lostLDPCChunkSymbols, allEquationsR2);
		cout << "We are here in SingleRepairFile 2" << endl;
		helperSymbolIndexes = gHR.helperSymbolIndexes;
		allEquationsR2 = gHR.allEquationsR2;
		cout << "We are here in SingleRepairFile 3" << endl;
		for (size_t i=0; i<helperSymbolIndexes.size(); i++)
			recoveryEquations[index].push_back(helperSymbolIndexes[i]);
			//recoveryEquations[index][i] = helperSymbolIndexes[i];
		cout << "We are here in SingleRepairFile 4" << endl;

		// cout << "helperSymbolIndexes: ";
		// for (size_t i = 0; i < helperSymbolIndexes.size(); i++)
		// 	cout << helperSymbolIndexes[i] << " ";
		// cout << endl;

		// cout << "lostLDPCChunkSymbols: " ;
		// for (size_t i = 0; i < lostLDPCChunkSymbols.size(); i++)
		// 	cout << lostLDPCChunkSymbols[i] << " ";
		// cout << endl;

		intersectionState = 0;
		for (size_t i = 0; i < helperSymbolIndexes.size(); i++)
		{
			for (size_t j = 0; j < lostLDPCChunkSymbols.size(); j++)
			{
				if (helperSymbolIndexes[i] == lostLDPCChunkSymbols[j])
				{
					intersectionState = 1;
					break;
				}
			}
			if (intersectionState == 1)
				break;
		}
		// cout << "intersectionState: " << intersectionState << endl;
		cout << "We are here in SingleRepairFile 5" << endl;
		// it = std::set_intersection(helperSymbolIndexes.begin(), helperSymbolIndexes.end(), lostLDPCChunkSymbols.begin(), lostLDPCChunkSymbols.end(), v.begin());
		// v.resize(it - v.begin());		
		// if (v.size() > 0)
		if (intersectionState == 1)
		{
			//R2[index2][0] = failedSymbolID;
			localR2.push_back(failedSymbolID);
			for (size_t in = 0; in < helperSymbolIndexes.size(); in++)
				localR2.push_back(helperSymbolIndexes[in]);
				//R2[index2][in+1] = helperSymbolIndexes[in];
			R2.push_back(localR2);
			//R2[index2][2:helperSymbolIndexes.size() + 1] = helperSymbolIndexes;
			//unrepairedSymbolsfromBS[index2] = failedSymbolID;
			unrepairedSymbolsfromBS.push_back(failedSymbolID);
			//index2 = index2 + 1;

			// R2.push_back(helperSymbolIndexes);
			// R2.insert(R2.begin(), failedSymbolID);
		}
		else
		{					
			// for (size_t in = 0; in < helperSymbolIndexes.size(); in++)
			// 	localR1.push_back(helperSymbolIndexes[in]);
			// 	//R1[index1][in] = helperSymbolIndexes[in];
			// R1.push_back(localR1);

			R1.push_back(helperSymbolIndexes);

			//R1(index1, 1:size(helperSymbolIndexes, 2)) = helperSymbolIndexes;
			//unrepairedSymbolsfromNodes[index1] = failedSymbolID;
			unrepairedSymbolsfromNodes.push_back(failedSymbolID);
			//index1 = index1 + 1;
		}

		//localR1.clear();
		localR2.clear();
		helperSymbolIndexes.clear();
		//allEquationsR2.clear();
		cout << "We are here in SingleRepairFile 6" << endl;
	}

	allEquations.resize(recoveryEquations.size() + allEquationsR2.size());
	
	// for (size_t r = 0; r < recoveryEquations.size(); r++)
	// {
	// 	for (size_t c = 0; c < recoveryEquations[0].size(); c++)
	// 	{
	// 		allEquations[r][c] = recoveryEquations[r][c];
	// 	}
	// }
	//allEquations(1:recoveryEquations.size(), : ) = recoveryEquations;
	intR = 0;
	for (size_t r = 0; r < recoveryEquations.size(); r++)
	{
		for (size_t c = 0; c < recoveryEquations[r].size(); c++)
			allEquations[intR].push_back(recoveryEquations[r][c]);
		intR = intR + 1;
	}

	// int intR = 0;
	// for (size_t r = recoveryEquations.size(); r < allEquations.size(); r++)
	// {	
	// 	for (size_t c = 1; c < allEquationsR2[0].size(); c++)
	// 	{
	// 		allEquations[r][c-1] = allEquationsR2[intR][c];
	// 	}
	// 	intR = intR + 1;
	// }
	//allEquations(recoveryEquations.size() + 1:end, 1 : allEquationsR2[0].size() - 1) = allEquationsR2(:, 2 : end);
	
	//copyAllEquationsR2 = allEquationsR2;
	for (size_t r = 0; r < allEquationsR2.size(); r++)
	{
		for (size_t c = 1; c < allEquationsR2[r].size(); c++)
			allEquations[intR].push_back(allEquationsR2[r][c]);
		//allEquations[intR].erase(allEquations[intR].begin());
		intR = intR + 1;
	}
	
	// in the end of the this section, tempEquations(i + 1) stores the information of the union of the helper symbols idxes
	tempEquations = allEquations;
	for (size_t i = 0; i < tempEquations.size(); i++)
	{
		for (size_t j = 0; j < tempEquations[i].size(); j++)
		{
			// if (tempEquations[i][j] != 0)
			// {
				symbols.push_back(tempEquations[i][j]);
				tempVal = ceil((double)tempEquations[i][j] / (double)quotient);
				fileIndexes.push_back(tempVal);
			// }
		}
	}

	sort(fileIndexes.begin(), fileIndexes.end());
	// std::vector<int>::iterator it2;
	std::vector<int>::iterator it2 = unique(fileIndexes.begin(), fileIndexes.end());
	fileIndexes.resize(distance(fileIndexes.begin(), it2));

	// Opening files which are encoded by LDPC	
	for (size_t t = 0; t < aliveLDPCStorageNodes.size(); t++)
	{
		for (size_t si = 0; si < fileIndexes.size(); si++)
		{
			if (fileIndexes[si] == (int)t+1)
				foundIndexes.push_back(t);
		}
		//if (aliveLDPCStorageNodes[t] != 0 && foundIndexes.size()>0)
		if (aliveLDPCStorageNodes[t] != -1 && foundIndexes.size()>0)
		{
			
			// cout << "t: " << t << endl;
			// cout << "aliveLDPCStorageNodes[t]: " << aliveLDPCStorageNodes[t] << endl;
			// cout << "size of nodeStr: " << nodeStr.size() << endl;
			// cout << "nodeStr[aliveLDPCStorageNodes[t]].fileName: " << nodeStr[aliveLDPCStorageNodes[t]].fileName << endl;
			fileFullDirectory = root_directory + nodeStr[aliveLDPCStorageNodes[t]].fileName.c_str();
			// cout << "fileFullDirectory: " << fileFullDirectory << endl;
			// cout << endl;
			//inputFiles.push_back(nodeStr[aliveLDPCStorageNodes[t]].fileName);
			inputFiles.push_back(fileFullDirectory);
			synchronisedFileIndexes.push_back(t);
			std::ifstream* f = new std::ifstream(fileFullDirectory.c_str(), std::ios::in| std::ios::binary| std::ios::ate);
			inputFileIDs.push_back(f);
		}
	}
	// cout << "File open process is done in SingleRepairFile" << endl;	
	//totalHelperFiles = [totalHelperFiles, inputFiles];
	for (size_t r = 0; r < inputFiles.size(); r++)
		totalHelperFiles.push_back(inputFiles[r]);

	stopState = 0;
	columnIndex = 0;
	currentColumnIndex = 0;

	for (size_t g = 0; g < inputFiles.size(); g++)
	{
		// ifstream inputFile(inputFiles[g].c_str(), ios::binary);
		// inputFile.seekg(0, ios::end);
		// inputFilesSize.push_back(inputFile.tellg());
		//inputFilesSize.push_back(std::filesystem::file_size(root_directory + inputFiles[g].c_str()));
		inputFilesSize.push_back(std::filesystem::file_size(inputFiles[g].c_str()));
	}

	readIndexes.resize(inputFiles.size());

	//std::fill(readedEncodedData.begin(), readedEncodedData.end(), 0);
	tempR2 = R2;
	tempL = L;
	tempUnrepairedSymbolsfromNodes = unrepairedSymbolsfromNodes;
	tempUnrepairedSymbolsfromBS = unrepairedSymbolsfromBS;
	tempCurrentLostLDPCChunkSymbols = currentLostLDPCChunkSymbols;

	while (stopState == 0)
	{
		std::fill(readedEncodedData.begin(), readedEncodedData.end(), 0);
		jj = 0;
		//for (int jj = 0; jj < synchronisedFileIndexes.size(); jj++)
		for (auto& stream : inputFileIDs)
		{
			readIndexes[jj] = readIndexes[jj] + quotient;
			if (readIndexes[jj] > inputFilesSize[jj])
			{
				stopState = 1;
				break;
			}
			else
			{
				//char * buffer = new char[quotient];
				(*stream).read(buffer, quotient);
				//size_t result = fread(&read, sizeof(std::uint8_t), quotient, inputFileIDs[jj]);
				readIndex = 0;
				//for (size_t ind = (synchronisedFileIndexes[jj] - 1)*quotient; ind < (synchronisedFileIndexes[jj] - 1)*quotient + read.size(); ind++)
				for (size_t ind = (synchronisedFileIndexes[jj])*quotient; ind < (synchronisedFileIndexes[jj])*quotient + read.size(); ind++)
				{
					readedEncodedData[ind] = read[readIndex];
					readIndex = readIndex + 1;
				}
				//readedEncodedData(((synchronisedFileIndexes[jj] - 1)*quotient + 1) : ((synchronisedFileIndexes[jj] - 1)*quotient + size(read, 2)), 1) = read;
			}
			jj = jj + 1;
		}

		if (stopState != 1)
		{
			//for (int j = 0; j < readedEncodedData.size(); j++)
			//{
			//	readedDatainBuffer[j][columnIndex] = readedEncodedData[j];
			//}
			readedDatainBuffer.push_back(readedEncodedData);
			//readedDatainBuffer(:, columnIndex) = readedEncodedData;
		}

		if((columnIndex == numberofRoundforBuffer-1) || (stopState == 1))
		{
			transpose(readedDatainBuffer);
		
			if(!readedDatainBuffer.empty())
			{
				R1Temp = R1;
				R2Temp = R2;
				cout << "We are in SingleRepairFile before FirstPhase" << endl;
				// cout << "size of L before FirstPhase: " << L.size() << endl;
				// cout << "readedDatainBuffer Before FirstPhase: " << endl;
				// cout << "size of readedDatainBuffer: " << readedDatainBuffer.size() << endl;
				// for (size_t r = 0; r < readedDatainBuffer.size(); r++)
				// {
				// 	cout << "size of readedDatainBuffer[r]: " << readedDatainBuffer[r].size() << endl;
				// }
				fpr = FirstPhase(currentLostLDPCChunkSymbols, L, R1, R2, strParameters, unrepairedSymbolsfromNodes, unrepairedSymbolsfromBS, readedDatainBuffer, allEquationsR2);	
				cout << "We are in SingleRepairFile after FirstPhase" << endl;
				
				encodedData.clear();
				L.clear();
				currentLostLDPCChunkSymbols.clear();
				R2.clear();
				R2ReducedCopy.clear();
				unrepairedSymbolsfromNodes.clear();
				unrepairedSymbolsfromBS.clear();
				usedHelpers.clear();

				strParameters = fpr.strParameters;
				encodedData = fpr.encodedData;
				// cout << "After FirstPhase: " << endl;
				// cout << "size of encodedData: " << encodedData.size() << endl;
				// for (size_t r = 0; r < encodedData.size(); r++)
				// {
				// 	cout << "size of encodedData[r]: " << encodedData[r].size() << endl;
				// }
				L = fpr.L;
				cout << "size of L after FirstPhase: " << L.size() << endl;
				currentLostLDPCChunkSymbols = fpr.currentLostLDPCChunkSymbols;				
				R2 = fpr.R2;
				R2ReducedCopy = fpr.R2ReducedCopy;
				unrepairedSymbolsfromNodes = fpr.unrepairedSymbolsfromNodes;
				unrepairedSymbolsfromBS = fpr.unrepairedSymbolsfromBS;
				usedHelpers = fpr.usedHelpers;
				cout << "We are in SingleRepairFile before SecondPhase" << endl;
				// cout << "size of L before SecondPhase: " << L.size() << endl;
				spr = SecondPhase(currentLostLDPCChunkSymbols, L, R2, R2ReducedCopy, strParameters, encodedData, currentColumnIndex, cols, stopState, maxColLength);	
				cout << "We are in SingleRepairFile after SecondPhase" << endl;					
				
				encodedData.clear();
				cout << "We are here in SingleRepairFile 7" << endl;	
				strParameters = spr.strParameters;			
				encodedData = spr.encodedData;
				currentColumnIndex = spr.currentColumnIndex;
				stopState = spr.stopState;
				cout << "We are here in SingleRepairFile 7_1" << endl;
				readedDatainBuffer.clear();				
				R1 = R1Temp;
				R2 = R2Temp;
				// WRITING TO EMPTY NODES	
				// cout << "After SecondPhase: " << endl;
				// cout << "size of encodedData: " << encodedData.size() << endl;
				// for (size_t r = 0; r < encodedData.size(); r++)
				// {
				// 	cout << "size of encodedData[r]: " << encodedData[r].size() << endl;
				// }
				for (size_t l = 0; l < encodedData[0].size(); l++)
				{
					// cout << "We are here in SingleRepairFile 7_1_1" << endl;
					// cout << "foundOne: " << foundOne << endl;
					// cout << "quotient: " << quotient << endl;
					// cout << "size of encodedData: " << encodedData.size() << endl;
					// cout << "size of encodedData[29]: " << encodedData[29].size() << endl;
					// cout << "foundOne * quotient: " << foundOne * quotient << endl;
					// cout << "foundOne * quotient + quotient: " << foundOne * quotient + quotient << endl;
					// cout << "size of buffer2 before: " << buffer2.size() << endl;
					buffer2.clear();
					// cout << "size of buffer2 after: " << buffer2.size() << endl;
					//bInd = 0;
					//for (int b = (foundOne - 1) * quotient; b < (foundOne - 1) * quotient + quotient; b++)
					for (int b = foundOne * quotient; b < foundOne * quotient + quotient; b++)
					{
						// cout << "We are here in SingleRepairFile 7_1_2" << endl;
						// cout << "b: " << b << endl;
						// cout << "l: " << l << endl;
						// cout << "size of encodedData[b]: " << encodedData[b].size() << endl;
						// if (encodedData[b].size() > 0)
						// 	cout << "encodedData[b][l]: " << encodedData[b][l] << endl;
						// buffer2[bInd] = encodedData[b][l];
						// bInd = bInd + 1;
						buffer2.push_back(encodedData[b][l]);
						// cout << "We are here in SingleRepairFile 7_1_3" << endl;
						// cout << endl;
					}
					// cout << "We are here in SingleRepairFile 7_1_4" << endl;			
					fwrite(&buffer2, sizeof(std::uint8_t), quotient, repairedFileID);
					// cout << "We are here in SingleRepairFile 7_1_5" << endl;
					//fwrite(buffer2, sizeof(char), sizeof(buffer2), pFile)
					//fwrite(repairedFileID, encodedData((foundOne - 1) * quotient + 1:(foundOne - 1) * quotient + quotient, l), 'uint8');
				}
				cout << "We are here in SingleRepairFile 7_2" << endl;
				if (stopState != 1)
				{
					L.clear();
					R2.clear();
					unrepairedSymbolsfromNodes.clear();
					unrepairedSymbolsfromBS.clear();
					currentLostLDPCChunkSymbols.clear();
					R2 = tempR2;
					L = tempL;
					unrepairedSymbolsfromNodes = tempUnrepairedSymbolsfromNodes;
					unrepairedSymbolsfromBS = tempUnrepairedSymbolsfromBS;
					currentLostLDPCChunkSymbols = tempCurrentLostLDPCChunkSymbols;
				}
				cout << "We are here in SingleRepairFile 7_3" << endl;
			}
		}	

		if(columnIndex == numberofRoundforBuffer-1)
			columnIndex = 1;
		else
			columnIndex = columnIndex + 1;

		if(currentColumnIndex >= blockSize-1)
			stopState = 1;
	}
	cout << "We are here in SingleRepairFile 8" << endl;	
	// Closing all open files
	//for(int i = 0;inputFiles.size();i++)
	//	fclose(inputFileIDs[i]);
	for (auto& stream : inputFileIDs)
	{
		(*stream).close();	
	}
	fclose(repairedFileID);
	cout << "File close process is done in SingleRepairFile" << endl;

	strParameters.usedNodes = inputFiles;

	sraV1Local.totalHelperFiles = totalHelperFiles;
	sraV1Local.nodeStr = nodeStr;
	sraV1Local.strParameters = strParameters;
	sraV1Local.aliveLDPCStorageNodes = aliveLDPCStorageNodes;
	cout << "We are at the end of SingleRepairFile" << endl;
	return sraV1Local;
}