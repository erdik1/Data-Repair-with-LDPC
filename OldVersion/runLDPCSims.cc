#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>
//#include <direct.h>
#include <fstream>
#include <cstring>

#include "userDefinedFunctions.h"

using namespace std;

void runLDPCSims()
{
  string root_directory = "scratch/testFolder";
  string basic_directory = root_directory + "/files";
  // if (mkdir(basic_directory.c_str(), 0777) == -1)
  //   cerr << "Error :  " << strerror(errno) << endl;
  // else
  //     cout << "Directory created";
  mkdir(basic_directory.c_str(), 0777);

  int AllSimsnkd[2][2] = { { 424,318 } };
  int storageNodes[] = { 12 };
  int allN = storageNodes[0] * 5;
  int p[] = { 53 };

  //int AllSimsnkd[2][2] = { { 388,194 },{ 424,318 } };
  //int storageNodes[] = {30,30};
  //int allN = storageNodes[0] * 5;
  //int p[] = { 97,53 };
  int allNodes[] = {allN, allN};
  
  int n, k, initStorageNodes, initNodes;
  stringstream tmp_stream1, tmp_stream2, tmp_stream3, tmp_stream4;
  string folderName, fileNameAlg1, fileNameAlg2, oldPath, newPath, path1, path2;

  for (int j = 0; j < 2; j++)
  {
    n = AllSimsnkd[j][0];
    k = AllSimsnkd[j][1];
    initStorageNodes = storageNodes[j];
    initNodes = allNodes[j];

    // tmp_stream1 = "";
    tmp_stream1.str(std::string());
    tmp_stream1 << n << "_" << k << "_all_" << initNodes << "_" << initStorageNodes;
    folderName = basic_directory + "/" + tmp_stream1.str();
    // tmp_stream2 = "";
    tmp_stream2.str(std::string());
    tmp_stream2 << "Alg1_" << n << "_" << k << "_all_" << initNodes << "_" << initStorageNodes << ".txt";
    fileNameAlg1 = tmp_stream2.str();
    // tmp_stream3 = "";
    tmp_stream3.str(std::string());
    tmp_stream3 << "Alg2_" << n << "_" << k << "_all_" << initNodes << "_" << initStorageNodes << ".txt";
    fileNameAlg2 = tmp_stream3.str();

    // Creating a directory
    mkdir(folderName.c_str(),0777);

    // Create and open a text file
    ofstream MyFile1(folderName + "/" + fileNameAlg1);
    ofstream MyFile2(folderName + "/" + fileNameAlg2);
    path1 = folderName + "/" + fileNameAlg1;
    path2 = folderName + "/" + fileNameAlg2;


    // Write to the file
    MyFile1 << "Delta\t ReadedOtherNodesPerLost\t stder\t ReadedBSPerLost\t stder\t AverageRepairTimeperNode\t AverageRepairTimeperSymbol\t TotalEncodedData\n";
    MyFile2 << "Delta\t ReadedOtherNodesPerLost\t stder\t ReadedBSPerLost\t stder\t AverageRepairTimeperNode\t AverageRepairTimeperSymbol\t TotalEncodedData\n";

    // Close the file
    MyFile1.close();
    MyFile2.close();

    for (int i = 1; i <= 10; i++)
    {
      double delta = 0.1*i;
      int c = 1000;
      int pp = p[j];
      callHildegard(delta, c, n, k, pp, initNodes, initStorageNodes, path1, path2);  
      cout << "We are here in runLDPCSims after callHildegard" << endl;  

      cout << "root_directory: " << root_directory << endl;
      cout << endl;
      cout << "basic_directory: " << basic_directory << endl;
      cout << endl;
      cout << "tmp_stream1: " << tmp_stream1.str() << endl;
      cout << endl;
      cout << "folderName: " << folderName << endl;
      cout << endl;
      cout << "fileNameAlg1: " << fileNameAlg1 << endl;
      cout << endl;
      cout << "fileNameAlg2: " << fileNameAlg2 << endl;
      cout << endl;
      cout << "MyFile1: " << folderName + "/" + fileNameAlg1 << endl;
      cout << endl;
      cout << "MyFile2: " << folderName + "/" + fileNameAlg2 << endl; 
      cout << endl;

      // tmp_stream4 = "";
      tmp_stream4.str(std::string());
      tmp_stream4 << basic_directory << "/" << n << "_" << k << "_delta0" << i << "_" << initNodes << "_" << initStorageNodes;
      folderName = tmp_stream4.str();
      cout << "tmp_stream4: " << tmp_stream4.str() << endl;
      cout << endl;
      cout << "folderName 2: " << folderName << endl;

      // Creating a directory
      mkdir(folderName.c_str(),0777);

      oldPath = basic_directory + "/ledgerV2.txt";
      newPath = folderName + "/ledgerV2.txt";
      if (rename(oldPath.c_str(), newPath.c_str()) != 0)
        perror("Error moving file 1");
      //rename(oldPath.c_str(), newPath.c_str());
      oldPath = basic_directory + "/ledgerV4.txt";
      newPath = folderName + "/ledgerV4.txt";
      if (rename(oldPath.c_str(), newPath.c_str()) != 0)
        perror("Error moving file 2");
      // rename(oldPath.c_str(), newPath.c_str());
      oldPath = basic_directory + "/ledger.txt";
      newPath = folderName + "/ledger.txt";
      if (rename(oldPath.c_str(), newPath.c_str()) != 0)
        perror("Error moving file 3");
      // rename(oldPath.c_str(), newPath.c_str());

    }
  }
}