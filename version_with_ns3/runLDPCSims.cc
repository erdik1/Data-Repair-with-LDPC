#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>
//#include <direct.h>
#include <fstream>
#include <cstring>
//#include "ns3/mobility-helper.h"

#include "userDefinedFunctions.h"

using namespace std;
//using namespace ns3;

//void runLDPCSims(Ptr<Socket> ns3TcpSocket, Address sinkAddress, NodeContainer gNbNodes, NodeContainer ueNodes, NetDeviceContainer gNbNetDev, NetDeviceContainer ueNetDev, MobilityHelper mobility, InternetStackHelper internet) 
//void runLDPCSims(Ptr<Socket> ns3TcpSocket, Address sinkAddress, NodeContainer gNbNodes, NodeContainer ueNodes, NetDeviceContainer gNbNetDev, NetDeviceContainer ueNetDev, InternetStackHelper internet, Ipv4InterfaceContainer ipInterfs) 
void runLDPCSims()
{
  std::vector<std::vector<int>> H, G;
  string root_directory = "scratch/testFolder";
  //string root_directory = "scratch";
  string basic_directory = root_directory + "/files";
  string rawFileName = root_directory + "/TestFile_128KB.bin";
  // if (mkdir(basic_directory.c_str(), 0777) == -1)
  //   cerr << "Error :  " << strerror(errno) << endl;
  // else
  //     cout << "Directory created";
  mkdir(basic_directory.c_str(), 0777);

  int AllSimsnkd[2][2] = { { 30,15 }};
  int storageNodes[] = { 14, 12,10 };
  int allN = storageNodes[0] * 5;
  int p[] = { 53,5 };

  //int AllSimsnkd[2][2] = { { 388,194 },{ 424,318 } };
  //int storageNodes[] = {30,30};
  //int allN = storageNodes[0] * 5;
  //int p[] = { 97,53 };
  int allNodes[] = {allN, allN};
  
  int n, k, numberofInitialLDPCStorageNodes, numberofInitialNodes;
  stringstream tmp_stream1, tmp_stream2, tmp_stream3, tmp_stream4;
  string folderName, fileNameAlg1, fileNameAlg2, oldPath, newPath, path1, path2;

  //M = size(G, 1);
  //limit = 10000;
  [[maybe_unused]] int numberofRoundforBuffer = 10000; //udpPacketSize
  //lambda = 1;
  //a = M*lambda;
  [[maybe_unused]] int a = 1;                              //Arrival rate
  [[maybe_unused]] int b = 1;                              //Departure rate
  //N = 100;                              //Length of simulation
  //numberofInitialNodes = 40;            //Initial number of nodes in the cell
  //numberofInitialLDPCStorageNodes = 8;
  //h = 7;                                //Download locality
  //r = 7;                                //Repair locality
  //w = 10;                               //Request rate
  //delta = 0.9;                          //Interval time between two repairs
  //delta = ones(1, N + M) * 0.2;         //Interval time between two repairs
  //alpha = 100;                          //Each storage node is exactly alpha bits(bytes)
  
  int c = 1000;
  double delta;
  int pp, jj, kk;
  time_t startTimeSimulator, endTimeSimulator; 

  for (int j = 0; j < 1; j++)
  {
    n = AllSimsnkd[j][0];
    k = AllSimsnkd[j][1];
    numberofInitialLDPCStorageNodes = storageNodes[j];
    numberofInitialNodes = allNodes[j];

    // tmp_stream1 = "";
    tmp_stream1.str(std::string());
    tmp_stream1 << n << "_" << k << "_all_" << numberofInitialNodes << "_" << numberofInitialLDPCStorageNodes;
    folderName = basic_directory + "/" + tmp_stream1.str();
    // tmp_stream2 = "";
    tmp_stream2.str(std::string());
    tmp_stream2 << "Alg1_" << n << "_" << k << "_all_" << numberofInitialNodes << "_" << numberofInitialLDPCStorageNodes << ".txt";
    fileNameAlg1 = tmp_stream2.str();
    // tmp_stream3 = "";
    tmp_stream3.str(std::string());
    tmp_stream3 << "Alg2_" << n << "_" << k << "_all_" << numberofInitialNodes << "_" << numberofInitialLDPCStorageNodes << ".txt";
    fileNameAlg2 = tmp_stream3.str();

    // Creating a directory
    mkdir(folderName.c_str(),0777);

    // Create and open a text file
    ofstream MyFile1(folderName + "/" + fileNameAlg1);
    ofstream MyFile2(folderName + "/" + fileNameAlg2);
    path1 = folderName + "/" + fileNameAlg1;
    path2 = folderName + "/" + fileNameAlg2;


    // Write to the file
    MyFile1 << "Delta\t ReadedOtherNodesPerLost\t stder\t ReadedBSPerLost\t stder\t AverageRepairTimeperNode\t AverageRepairTimeperSymbol\t timeforRepairperNode\t numberofRepairs\t TotalEncodedData\n";
    MyFile2 << "Delta\t ReadedOtherNodesPerLost\t stder\t ReadedBSPerLost\t stder\t AverageRepairTimeperNode\t AverageRepairTimeperSymbol\t timeforRepairperNode\t numberofRepairs\t TotalEncodedData\n";

    // Close the file
    MyFile1.close();
    MyFile2.close();

    pp = p[j];
    jj = (n - k) / pp;
    kk = n / pp;
    H = callHildegard(n, k, pp, numberofInitialNodes, numberofInitialLDPCStorageNodes, path1, path2); 
    G = H;

    for (int i = 3; i <= 3; i++)
    {
      delta = 0.1*2*(i-1)+0.1;
      //callHildegard(delta, c, n, k, pp, numberofInitialNodes, numberofInitialLDPCStorageNodes, path1, path2, ns3TcpSocket, sinkAddress, gNbNodes, ueNodes, gNbNetDev, ueNetDev, mobility, internet); 
      //callHildegard(delta, c, n, k, pp, numberofInitialNodes, numberofInitialLDPCStorageNodes, path1, path2, ns3TcpSocket, sinkAddress, gNbNodes, ueNodes, gNbNetDev, ueNetDev, internet);  

      startTimeSimulator = time(0);
      //hildegardVonBingen(H, G, N, a, b, numberofInitialNodes, numberofInitialLDPCStorageNodes, delta, rawFileName, numberofRoundforBuffer, p, j, k, fileNameAlg1, fileNameAlg2, ns3TcpSocket, sinkAddress, gNbNodes, ueNodes, gNbNetDev, ueNetDev, mobility, internet);
      //hildegardVonBingen(H, G, c, a, b, numberofInitialNodes, numberofInitialLDPCStorageNodes, delta, rawFileName, numberofRoundforBuffer, pp, jj, kk, fileNameAlg1, fileNameAlg2, ns3TcpSocket, sinkAddress, gNbNodes, ueNodes, gNbNetDev, ueNetDev, internet, ipInterfs);
      cout << "We are here in runLDPC before  callHhildegardVonBingenildegard" << endl;  
      hildegardVonBingen(H, G, c, a, b, numberofInitialNodes, numberofInitialLDPCStorageNodes, delta, rawFileName, numberofRoundforBuffer, pp, jj, kk, fileNameAlg1, fileNameAlg2);
      endTimeSimulator = time(0);
      [[maybe_unused]] double elapsedTimeSimulator = difftime(startTimeSimulator, endTimeSimulator);

      cout << "We are here in runLDPC  after hildegardVonBingen" << endl;  

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
      tmp_stream4 << basic_directory << "/" << n << "_" << k << "_delta0" << i << "_" << numberofInitialNodes << "_" << numberofInitialLDPCStorageNodes;
      folderName = tmp_stream4.str();
      cout << "tmp_stream4: " << tmp_stream4.str() << endl;
      cout << endl;
      cout << "folderName 2: " << folderName << endl;

      cout << "We are at the end of simulation in runLDPCSims" << endl;

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