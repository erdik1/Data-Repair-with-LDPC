#include "userDefinedFunctions.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <memory>
#include <filesystem>

using namespace std;

typedef struct encodingReturns Struct;

void write_to_file(ofstream fp, uint8_t *ptr, string fileName) 
{
    fp.open(fileName.c_str(),ios::out | ios :: binary );
    fp.write((char*)ptr, 1);
}

void write_to_fileV2(ofstream fp, uint8_t *ptr) 
{
    fp.write((char*)ptr, 1);
}

std::ifstream::pos_type filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}

Struct ldpcEncodingforArrrayLDPC(std::vector<std::vector<int>> G, int numberofInitialLDPCStorageNodes, std::string rawFileName, std::string baseStation, int numberofRoundforBuffer, int p, int j, int k, std::vector<struct ns> nodeStr)
{
	FILE *baseStationID, *rawFileID; 
	FILE *nodeIDs[numberofInitialLDPCStorageNodes];
	Struct erLocal;
	int remainder = 0;
	int buffer = 0;
	[[maybe_unused]] int countttt = 0;
	string path;
	int redundantFileSize;
	int rows = G.size();
	int cols = G[0].size();
	// ifstream rawFile(rawFileName.c_str(), ios::binary);
	// rawFile.seekg(0, ios::end);
	// int rawFileSize = rawFile.tellg();
	int rawFileSize = std::filesystem::file_size(rawFileName);
	int blockSize = ceil((double)rawFileSize / (double)(cols - rows));
	[[maybe_unused]] int fileSize;
	int quotient = ceil((double)cols / (double)numberofInitialLDPCStorageNodes);
	std::vector<int> aliveLDPCStorageNodes(numberofInitialLDPCStorageNodes, 0);	
	string root_directory = "scratch/testFolder/files/";
	std::vector<string> repairedFiles;
	string tempS1;
	string tempS1FullDirectory;	
	//std::vector<shared_ptr<ofstream>> nodeIDs;
	[[maybe_unused]] size_t retVal, retVal2;
	std::vector<uint8_t> totalData;
	uint8_t tempData;
	uint8_t parityData;
	int stopState = 0;
	int columnIndex = 0;
	int totalColumnIndex = 0;
	int counter = 0;
	std::vector<std::vector<uint8_t>> readedDatainBuffer;
	int lastBlock;
	std::vector<uint8_t> readedData(cols - rows);
	uint8_t read;
	int exceptionPoint;
	size_t result;
	std::vector<uint8_t> encodedData(rows, 0);
	std::vector<int> ldpcFileSizes(numberofInitialLDPCStorageNodes, 0);
	int totalEncodedData = 0;

	if (fmod(rawFileSize, blockSize) != 0)
	{
		redundantFileSize = blockSize * (cols - rows);
		remainder = redundantFileSize - rawFileSize;
	}
	fileSize = rawFileSize + remainder;

	for (int i = 0; i < numberofInitialLDPCStorageNodes; i++)
	{
		tempS1 = "nodeFile";
		tempS1.append(to_string(i + 1));
		tempS1.append(".bin");
		tempS1FullDirectory = root_directory + tempS1;
		ifstream file; 

		//nodeIDs.push_back(make_shared<ofstream>(tempS1FullDirectory.c_str(), std::ios::binary));   
		nodeIDs[i] = fopen(tempS1FullDirectory.c_str(), "wb"); 
		nodeStr.push_back(ns());

		// aliveLDPCStorageNodes[i] = i + 1;
		// nodeStr[i].nodeID = i + 1;
		// nodeStr[i].logicalNodeID = i + 1;
		// nodeStr[i].fileName = tempS1;
		// nodeStr[i].isLive = 1;
		// nodeStr[i].encodingType = 1;
		// nodeStr[i].repairedNodeID = i + 1;

		aliveLDPCStorageNodes[i] = i;
		nodeStr[i].nodeID = i;
		nodeStr[i].logicalNodeID = i;
		nodeStr[i].fileName = tempS1;
		nodeStr[i].isLive = 1;
		nodeStr[i].encodingType = 1;
		nodeStr[i].repairedNodeID = i;
	}
	
	baseStationID = fopen(baseStation.c_str(), "wb");
	if (baseStationID == NULL)
	{
		cout << "Could not open file " << baseStation << std::endl;
	}
	rawFileID = fopen(rawFileName.c_str(), "rb");
	if (rawFileID == NULL)
	{
		cout << "Could not open file " << rawFileName << std::endl;
	}

	while (stopState == 0)
	{
		std::fill(readedData.begin(), readedData.end(), 0);
		lastBlock = 0;
		exceptionPoint = 0;

		for (int i = 0; i < (cols - rows); i++)
		{
			if (rawFileSize >= i * blockSize + totalColumnIndex)
			{
				if (rawFileSize == i * blockSize + totalColumnIndex)
				{
					exceptionPoint = 1;
				}

				fseek(rawFileID, i * blockSize + totalColumnIndex, SEEK_SET);
				result = fread(&read, sizeof(std::uint8_t), 1, rawFileID);
				if (result == 1)
					readedData[i] = read;
				else
					exceptionPoint = 1;
			}
			else
				exceptionPoint = 1;

			if (exceptionPoint == 1)
			{
				counter = counter + 1;
				if (remainder == 0 || counter == remainder)
				{
					stopState = 1;
					lastBlock = 1;
					break;
				}
			}
		}

		if (stopState == 0 || lastBlock == 1)
			readedDatainBuffer.push_back(readedData);


		if (columnIndex == numberofRoundforBuffer-1 || stopState == 1)
		{
			encodedData.clear();
			encodedData.resize(rows);
			for (size_t i2 = 0; i2 < readedDatainBuffer.size(); i2++)
			{
				readedData = readedDatainBuffer[i2];
				
				for (int r = (p*j)-1; r >= 0; r--)
				{				
					tempData = 0;
					parityData = 0;
					for (int t = p*j; t < p*k; t++)
					{
					    //int a = G[r][t];
					    uint8_t a = G[r][t];
						uint8_t b = readedData[t - p*j];
						tempData = (a * b) ^ tempData;
						//tempData = bitxor(G[r, t]*readedData[t - p*j], tempData);
					}
					for (int m = (p*j) - 1; m >= r; m--)
					{
						//int a = G[r][m];
						uint8_t a = G[r][m];
						uint8_t b = encodedData[m];
						parityData = (a * b) ^ parityData;
						//parityData = bitxor(G(r, m)*encodedData(m), parityData);
					}
					encodedData[r] = tempData ^ parityData;
					//encodedData(r) = bitxor(tempData, parityData);				
				}
				totalData = encodedData;
				totalData.insert(totalData.end(), readedData.begin(), readedData.end());

				//for (auto& stream : nodeIDs)
				

				for (int v = 0; v < numberofInitialLDPCStorageNodes; v++)
				{
					for (int by = v*quotient; by < v*quotient + quotient; by++)
					{
						if ((unsigned) by < totalData.size())
						{
							retVal2 = fwrite(&totalData[by], sizeof(std::uint8_t), 1, nodeIDs[v]);
							retVal = fwrite(&totalData[by], sizeof(std::uint8_t), 1, baseStationID);	

							if (retVal2 == 0 || retVal == 0)
								cout << "Data are not written to the files" << endl;
					
						}
						else
						{
							//(*stream) << int(0);
							retVal2 = fwrite(&buffer, sizeof(std::uint8_t), 1, nodeIDs[v]);
							retVal = fwrite(&buffer, sizeof(std::uint8_t), 1, baseStationID);
						}
							
					}
				}
				cout << endl;

			}			
			readedDatainBuffer.clear();
		}

		if (columnIndex == numberofRoundforBuffer-1)
			columnIndex = 0;
		else
			columnIndex = columnIndex + 1;
		totalColumnIndex = totalColumnIndex + 1;
	}

	// for (int ind = 0; ind < numberofInitialLDPCStorageNodes; ind++)
	// {
	// 	ifstream nodeFile(nodeStr[ind].fileName, ios::binary);
	// 	nodeFile.seekg(0, ios::end);
	// 	ldpcFileSizes[ind] = nodeFile.tellg();
	// 	nodeStr[ind].fileSize = ldpcFileSizes[ind];
	// 	totalEncodedData = totalEncodedData + ldpcFileSizes[ind];
	// }

	for (int ind = 0; ind < numberofInitialLDPCStorageNodes; ind++)
	{
		path = root_directory + nodeStr[ind].fileName;
		ldpcFileSizes[ind] = std::filesystem::file_size(path);
		//cout << "Size of "<< nodeStr[ind].fileName <<" is: " << ldpcFileSizes[ind] << " bytes.\n";
		nodeStr[ind].fileSize = ldpcFileSizes[ind];
		totalEncodedData = totalEncodedData + ldpcFileSizes[ind];
	}

	// Closing all open files
	// for (auto& stream : nodeIDs)
	// {
	// 	(*stream).close();
	// }
	for (int i3 = 0; i3 < numberofInitialLDPCStorageNodes; i3++)
		fclose(nodeIDs[i3]);

	fclose(rawFileID);
	fclose(baseStationID);

	erLocal.blockSize = blockSize;
	erLocal.aliveLDPCStorageNodes = aliveLDPCStorageNodes;
	erLocal.totalEncodedData = totalEncodedData;
	erLocal.ldpcFileSizes = ldpcFileSizes;
	erLocal.nodeStr = nodeStr;

	return erLocal;
}