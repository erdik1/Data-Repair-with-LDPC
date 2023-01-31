#ifndef HandleMessages_H
#define HandleMessages_H

/*Use of Sidelink between two ue nodes */
/*Elif*/

#include <sys/stat.h>
#include <unistd.h>
#include "ns3/command-line.h"
#include "ns3/config.h"
#include "ns3/string.h"
#include "ns3/log.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/ssid.h"
#include "ns3/mobility-helper.h"
#include "ns3/on-off-helper.h"
#include "ns3/yans-wifi-channel.h"
#include "ns3/mobility-model.h"
#include "ns3/packet-sink.h"
#include "ns3/packet-sink-helper.h"
#include "ns3/tcp-westwood.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/ipv4-global-routing-helper.h"

#include "TcpSocketProcesses.h"
#include "messages.h"
#include "userDefinedFunctions.h"

#include <filesystem>

//#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>
#include <cmath>
#include <filesystem>
//#include "ipv4-interface-container.h"
//#include "ns3/eps-bearer-tag.h"
#include <random>
//#include "ns3/application.h"

// Elif hocanın eklediği bölüm
#include <sys/types.h>

using namespace ns3;
using namespace std;

//typedef struct singleRepairAlgorithmV1Returns Struct;

//TCPSocketProcesses ata sınıf olarak alınıyor burada fakat ReceivePacket, WriteUntilBufferFull gibi metodlar kendisine göre override ediliyor.
//Bu nedenle TCPSocketProcesses sınıfı içerisinde bu metodlar virtual olarak oluşturuluyor.
class  HandleMessages : public TCPSocketProcesses 
{
   public:
        using  TCPSocketProcesses::TCPSocketProcesses;
        void ReceivePacket (Ptr<Socket> socket);
        void RepairOperation();

        // Elif hocanın eklediği değişkenler ve fonksiyonlar
        int index = 0;
        int nextRead;
        int readed=0;
        int shouldbeRead; 
        int localIndex;
        FILE * fileTobeRead;
        char* fileNameFromHelper;
        int stopState = 0;
        int readedCounter = 0;
        int totalIndex = 0;
        int casual= MTU;
        int sstop = 0;
        uint8_t readedByte; 
        int columnIndex = 0;
        void StartSignalPacketwithParameters(enum MType MESSAGETYPE,Ptr<Socket> socket);
        void WriteUntilBufferFullFromHelperNodes(Ptr<Socket> socket, uint32_t txSpace);
        void WriteUntilBufferFullFromBS(Ptr<Socket> socket, uint32_t txSpace);
        void WriteIntoFileByNewComerNodeApp(uint8_t* bufData, int casual,struct fileChunk fchunk);  

        // Benim eklediklerim
        // void StartSignalPacketwithParameters(enum MType MESSAGETYPE, Ptr<Node> senderNode, Ptr<Node> receiverNode, Ipv4Address senderAddress, Ipv4Address receiverAddress, uint16_t servPort);
        // void WriteUntilBufferFullFromHelperNodes();
        // void WriteUntilBufferFullFromBS();
        // void WriteIntoFileByNewComerNodeApp(uint8_t* bufData, int casual, std::string tempUsedEmptyNodeforRepair);
};

void  HandleMessages::StartSignalPacketwithParameters(enum MType MESSAGETYPE,Ptr<Socket> socket)
{     
    //cout << "We are in StartSignalPacketwithParameters of HandleMessages" << endl;
    NS_LOG_LOGIC ("In HandleMessages::StartSignalPacketwithParameters, Starting flow at time " <<  Simulator::Now ().GetSeconds ());
    //cout << "We are in StartSignalPacketwithParameters of HandleMessages 1" << endl;
    printf ("In HandleMessages::StartSignalPacketwithParameters, Starting flow at time %f \n",  Simulator::Now ().GetSeconds ());

    cout << "In HandleMessages::StartSignalPacketwithParameters, senderNode->GetId(): " << socket->GetNode()->GetId() << endl;
    
    //cout << "We are in StartSignalPacketwithParameters of HandleMessages 3" << endl;
    uint8_t *bufferStruct = (uint8_t *)(malloc(MESSAGETYPE));
    memcpy(bufferStruct, &MESSAGETYPE, sizeof(enum MType));
    //cout << "We are in StartSignalPacketwithParameters of HandleMessages4" << endl;
    Ptr <Packet> pkt1 = Create<Packet>(bufferStruct, sizeof(enum MType));
    //cout << "We are in StartSignalPacketwithParameters of HandleMessages 5" << endl;
    [[maybe_unused]] int res = socket->Send(pkt1);
    cout<<"In HandleMessages::StartSignalPacketwithParameters, res :"<<res<<"\n";
    if(res == -1)
        cout << "In HandleMessages::StartSignalPacketwithParameters, Packet cannot be sent." << endl;
    else
        cout << "In HandleMessages::StartSignalPacketwithParameters, Packet is sent successfully." << endl;
    cout << endl;
    //cout << "We are in StartSignalPacketwithParameters of HandleMessages 6" << endl;
}

// void HandleMessages::StartSignalPacketwithParameters(enum MType MESSAGETYPE, Ptr<Node> senderNode, Ptr<Node> receiverNode, Ipv4Address senderAddress, Ipv4Address receiverAddress, uint16_t servPort)
// {
//     //cout << "We are in StartSignalPacketwithParameters of HandleMessages" << endl;
//     NS_LOG_LOGIC ("Starting flow at time " <<  Simulator::Now ().GetSeconds ());
//     //cout << "We are in StartSignalPacketwithParameters of HandleMessages 1" << endl;
//     printf ("Starting flow at time %f \n",  Simulator::Now ().GetSeconds ());
    
//     // senderSocket = Socket::CreateSocket (senderNode, TcpSocketFactory::GetTypeId ());
//     cout << "In HandleMessages::StartSignalPacketwithParameters, senderNode->GetId(): " << senderNode->GetId() << endl;
//     // cout << "In HandleMessages::StartSignalPacketwithParameters, receiverNode->GetId(): " << receiverNode->GetId() << endl;
//     cout << "In HandleMessages::StartSignalPacketwithParameters, receiverNode->GetId(): " << receiverNode->GetId() <<", servPort:" <<servPort<<", receiverAddress:"<<receiverAddress<<endl;

//     // servPort = servPort + 1;
//     senderSocket = Socket::CreateSocket (senderNode, TcpSocketFactory::GetTypeId ());
//     // receiverSocket = Socket::CreateSocket(receiverNode, TcpSocketFactory::GetTypeId());
//     // senderSocket->Connect (InetSocketAddress (receiverAddress, servPort)); //connect
  
//     //cout << "We are in StartSignalPacketwithParameters of HandleMessages 2" << endl;
//     //cout << "receiverAddress: " << receiverAddress << endl;
//     //cout << "servPort: " << servPort << endl; 
//     //cout << "senderSocket: " << senderSocket << endl;
//     // senderSocket->Connect (InetSocketAddress (receiverAddress, servPort)); //connect

//     // Elif hocanın eklediği bölüm
//     this->SetReceiverSocket();
//     senderSocket->Connect (InetSocketAddress (receiverAddress, servPort)); //connect

//     //cout << "We are in StartSignalPacketwithParameters of HandleMessages 3" << endl;
//     uint8_t *bufferStruct = (uint8_t *)(malloc(MESSAGETYPE));
//     memcpy(bufferStruct, &MESSAGETYPE, sizeof(enum MType));
//     //cout << "We are in StartSignalPacketwithParameters of HandleMessages4" << endl;
//     Ptr <Packet> pkt1 = Create<Packet>(bufferStruct, sizeof(enum MType));
//     //cout << "We are in StartSignalPacketwithParameters of HandleMessages 5" << endl;
//     [[maybe_unused]] int res = senderSocket->Send(pkt1);
//     //cout << "We are in StartSignalPacketwithParameters of HandleMessages 6" << endl;
//     if(res == -1)
//         cout << "In HandleMessages::StartSignalPacketwithParameters, Packet cannot be sent." << endl;
//     else
//         cout << "In HandleMessages::StartSignalPacketwithParameters, Packet is sent successfully." << endl;
//     cout << endl;
// }

//void HandleMessages::ReceivePacket(Ptr<Socket> socket, enum MType messageType, std::vector<string> inputFiles, int selectedHelperNodeIndex, std::vector<int> currentHelperNodeIndexes, int quotient, std::string tempUsedEmptyNodeforRepair, Ptr<Node> staWifiNode1, Ptr<Node> staWifiNode2, Ipv4InterfaceContainer ueIpIface, std::string baseStation, std::vector<int> failedSymbolIDsForRepairFromBS, int maxColLength, NodeContainer gNbNodes, NodeContainer ueNodes)
void HandleMessages::ReceivePacket(Ptr<Socket> socket)
{
    cout << endl;
    cout << "socket->GetRxAvailable(): " << socket->GetRxAvailable() << endl;
    cout << "Simulator::Now().GetSeconds(): " << Simulator::Now().GetSeconds() << endl;
    Ptr<Packet> packet;
    printf("socket->GetNode()->GetId(): %d \n",socket->GetNode()->GetId());
    while ((packet = socket->Recv ()))
    {
        std::cout << "Packet is received successfully at " << Simulator::Now().GetSeconds() <<"s " << "by Receiver Node " << receiverNode->GetId() << "\n";
        uint8_t* type = (uint8_t*)malloc(sizeof(enum MType));
        packet->CopyData(type, sizeof(enum MType));

        int me = socket->GetNode()->GetId();
        printf("Node %d received  a type %d packet with the size of %d bytes.\n", me, (int)*type, packet->GetSize());

        if(*type == 0) 
        {
            cout << "In HandleMessages::ReceivePacket, type 0, Node ID: " << senderNode->GetId() <<". Packet Type REQUESTREPAIRFROMBS is received."<<endl;
            cout << "In HandleMessages::ReceivePacket, type 0, Sender Node ID: " << senderNode->GetId() << endl;
            cout << "In HandleMessages::ReceivePacket, type 0, Receiver Node ID: " << receiverNode->GetId() << endl;
            cout << endl;
            // cout<<"Packet Type REQUESTREPAIRFROMBS is received"<<endl;

            // Elif hocanın eklediği kısım
            this->SetSenderSocketForReply();

            // Benim eklediğim kısım - şimdi kapatıldı
            // Ptr<Node> tempNode = senderNode;
            // senderNode = receiverNode;
            // receiverNode = tempNode;

            // Ptr<ns3::Socket> tempSocket = senderSocket;
            // senderSocket = receiverSocket;
            // receiverSocket = tempSocket;

            // Ptr<Ipv4> ipv4 = receiverNode->GetObject<Ipv4> ();
            // Ipv4InterfaceAddress iaddr = ipv4->GetAddress (1,0); 
            // receiverAddress =iaddr.GetLocal ();
            // servPort = 5000 + receiverNode->GetId();

            // Ptr<Ipv4> ipv4V2 = senderNode->GetObject<Ipv4> ();
            // Ipv4InterfaceAddress iaddrV2 = ipv4V2->GetAddress (1,0); 
            // senderAddress =iaddrV2.GetLocal ();
            // // SetSenderSocket();
            // SetReceiverSocket();
            // senderSocket->Connect (InetSocketAddress (receiverAddress, servPort)); //connect
            // enum MType messageType = REPLYREPAIRFROMBS;
            // StartSignalPacketwithParameters(messageType, senderNode, receiverNode, senderAddress, receiverAddress, servPort);

            //------------------------------------------------------------------------

            // Eskiden kapatılan kısım
            // servPort = servPort + 1;

            // senderSocket = Socket::CreateSocket (senderNode, TcpSocketFactory::GetTypeId ());
            // receiverSocket = Socket::CreateSocket(receiverNode, TcpSocketFactory::GetTypeId());
            // senderSocket->Connect (InetSocketAddress (receiverAddress, servPort)); //connect

            // struct fileParameters fileP; 
            // //fileP.buffer=(uint8_t *)(malloc((packet->GetSize())));
            // uint8_t* buf2 = (uint8_t*)malloc(packet->GetSize());
            // packet->CopyData(buf2, packet->GetSize());
            // memcpy(&fileP, buf2, sizeof(fileP));

            // Ptr<HandleMessages> bsObject = new HandleMessages(fileP.senderNode, fileP.receiverNode, fileP.receiverAddress, fileP.servPort);
            // bsObject->StartFlowV5(fileP.baseStation, fileP.failedSymbolIDsForRepairFromBS, fileP.maxColLength, fileP.tempUsedEmptyNodeforRepair, fileP.senderNode, fileP.receiverNode, fileP.foundOne, fileP.repairedFile, fileP.totalHelperFiles, fileP.cols, fileP.nodeStr, fileP.ueIpIface, fileP.inputFiles, fileP.selectedHelperNodeIndex, fileP.selectedEmptyNodeIndex, fileP.quotient, fileP.R1, fileP.R2, fileP.L, fileP.helperNodes, fileP.numberofRoundforBuffer, fileP.currentLostLDPCChunkSymbols, fileP.strParameters, fileP.unrepairedSymbolsfromNodes, fileP.unrepairedSymbolsfromBS, fileP.allEquationsR2, fileP.remoteHost, fileP.aliveLDPCStorageNodes, fileP.allHelperNodeIndexes);
            //WriteUntilBufferFullFromBS(senderSocket, receiverSocket, senderSocket->GetTxAvailable (), baseStation, failedSymbolIDsForRepairFromBS, maxColLength, tempUsedEmptyNodeforRepair, staWifiNode1, staWifiNode2, foundOne, repairedFile, totalHelperFiles, cols, nodeStr, ueIpIface, inputFiles, selectedHelperNodeIndex, selectedEmptyNodeIndex, quotient, R1, R2, L, helperNodes, numberofRoundforBuffer, currentLostLDPCChunkSymbols, strParameters, unrepairedSymbolsfromNodes, unrepairedSymbolsfromBS, allEquationsR2, remoteHost, aliveLDPCStorageNodes, allHelperNodeIndexes);
            //void WriteUntilBufferFullFromBS();
            
            // WriteUntilBufferFullFromBS(socket, socket->GetTxAvailable());
        }
        else if (*type == 1)
        {
            cout << "In HandleMessages::ReceivePacket, type 1, Node ID: " << socket->GetNode()->GetId() <<" has recevived Packet Type REQUESTREPAIRFROMUE is received."<<endl;
            cout << "In HandleMessages::ReceivePacket, type 1, Sender Node ID: " << senderNode->GetId() << endl;
            cout << "In HandleMessages::ReceivePacket, type 1, Receiver Node ID: " << receiverNode->GetId() << endl;
            cout << "socket->GetRxAvailable(): " << socket->GetRxAvailable() << endl;
            cout << endl;
 
            // Elif hocanın eklediği kısım
            nextRead=MTU;
            printf("File to be read is %s \n",inputFiles[0].c_str());
            struct stat status;
            stat(inputFiles[0].c_str(), &status);
            if((fileTobeRead = fopen(inputFiles[0].c_str(),"rb")) == NULL) 
                printf("Node %d UNABLE TO READ FILE \n",socket->GetNode()->GetId());
            else
            {
                int size = status.st_size;  //Dosyanın size'ı bulunuyor burada
                shouldbeRead = (int)(size * (int)(allHelperNodeIndexes.size()) / quotient);
                if (size%MTU>0)
                    totalIndex=totalIndex+1;
                printf("Node %d is ABLE TO READ FILE \n",socket->GetNode()->GetId());
                this->SetSenderSocketForReply();
            }

            // Benim eklediğim kısım
            // Ptr<Node> tempNode = senderNode;
            // senderNode = receiverNode;
            // receiverNode = tempNode;
            // Ptr<ns3::Socket> tempSocket = senderSocket;
            // senderSocket = receiverSocket;
            // receiverSocket = tempSocket;
            // Ptr<Ipv4> ipv4 = receiverNode->GetObject<Ipv4> ();
            // Ipv4InterfaceAddress iaddr = ipv4->GetAddress (1,0); 
            // receiverAddress =iaddr.GetLocal ();
            // servPort = 5000 + receiverNode->GetId();
            // Ptr<Ipv4> ipv4V2 = senderNode->GetObject<Ipv4> ();
            // Ipv4InterfaceAddress iaddrV2 = ipv4V2->GetAddress (1,0); 
            // senderAddress =iaddrV2.GetLocal ();
            // // SetSenderSocket();
            // SetReceiverSocket();
            // senderSocket->Connect (InetSocketAddress (receiverAddress, servPort)); //connect

            //----------------------------------------------------------------------------------------------

            // Eskiden kapatılan kısım
            // enum MType messageType = REPLYREPAIRFROMUE;
            // StartSignalPacketwithParameters(messageType, senderNode, receiverNode, senderAddress, receiverAddress, servPort);

            // servPort = servPort + 1;

            // senderSocket = Socket::CreateSocket (senderNode, TcpSocketFactory::GetTypeId ());
            // receiverSocket = Socket::CreateSocket(receiverNode, TcpSocketFactory::GetTypeId());
            // senderSocket->Connect (InetSocketAddress (receiverAddress, servPort)); //connect

            // struct fileParameters fileP; 
            // uint8_t* buf2 = (uint8_t*)malloc(packet->GetSize());
            // packet->CopyData(buf2, packet->GetSize());
            // memcpy(&fileP, buf2, sizeof(fileP));

            // struct fileParameters fileP = (struct fileParameters)malloc(packet->GetSize());
            // packet->CopyData(fileP, packet->GetSize());

            // Ptr<HandleMessages> helperNodeObject = new HandleMessages(fileP.senderNode, fileP.receiverNode, fileP.receiverAddress, fileP.servPort);
            // helperNodeObject->StartFlowV4(fileP.inputFiles, fileP.selectedHelperNodeIndex, fileP.selectedEmptyNodeIndex, fileP.quotient, fileP.tempUsedEmptyNodeforRepair, fileP.senderNode, fileP.receiverNode, fileP.ueIpIface, fileP.foundOne, fileP.repairedFile, fileP.totalHelperFiles, fileP.cols, fileP.nodeStr, fileP.baseStation, fileP.failedSymbolIDsForRepairFromBS, fileP.maxColLength, fileP.R1, fileP.R2, fileP.L, fileP.helperNodes, fileP.tempUsedEmptyNodeforRepair, fileP.numberofRoundforBuffer, fileP.currentLostLDPCChunkSymbols, fileP.strParameters, fileP.unrepairedSymbolsfromNodes, fileP.unrepairedSymbolsfromBS, fileP.allEquationsR2, fileP.remoteHost, fileP.aliveLDPCStorageNodes, fileP.allHelperNodeIndexes);
            //WriteUntilBufferFullFromHelperNodes(senderSocket, receiverSocket, senderSocket->GetTxAvailable (), inputFiles, selectedHelperNodeIndex, selectedEmptyNodeIndex, quotient, tempUsedEmptyNodeforRepair, staWifiNode1, staWifiNode2, ueIpIface, foundOne, repairedFile, totalHelperFiles, cols, nodeStr, baseStation, failedSymbolIDsForRepairFromBS, maxColLength, R1, R2, L, helperNodes, numberofRoundforBuffer, currentLostLDPCChunkSymbols, strParameters, unrepairedSymbolsfromNodes, unrepairedSymbolsfromBS, allEquationsR2, remoteHost, aliveLDPCStorageNodes, allHelperNodeIndexes);
            //void WriteUntilBufferFullFromHelperNodes();
            
            // WriteUntilBufferFullFromHelperNodes(socket, socket->GetTxAvailable());
        }
        else if (*type == 2)
        {
            cout<< "In HandleMessages::ReceivePacket, type 2, Node ID: " << socket->GetNode()->GetId()<<" has received Packet Type REPLYREPAIRFROMBS is received."<<endl;
            cout<< "In HandleMessages::ReceivePacket, type 2, Sender Node ID: " << senderNode->GetId() << endl;
            cout<< "In HandleMessages::ReceivePacket, type 2, Receiver Node ID: " << receiverNode->GetId() << endl;
            cout << endl;
            cout<<"Packet Type REPLYREPAIRFROMBS is received"<<endl;

            struct fileChunk filechunk; 
            filechunk.buffer=(uint8_t *)malloc(packet->GetSize());
            uint8_t* buf2 = (uint8_t *)malloc(packet->GetSize());
            packet->CopyData(buf2, packet->GetSize());
            memcpy(&filechunk, buf2, 10);

            // Elif hocanın eklediği kısım
            char *curdir;
            curdir = (char*)malloc(sizeof(char)*600);
            char* dire=getcwd(curdir, 600);
            printf("Directory%s\n",dire);
            fileNameFromHelper = (char*)malloc((sizeof(char)*(strlen(curdir)+150)));
            char* dirname=(char*)malloc((sizeof(char)*(strlen(curdir)+70)));
            sprintf(dirname,"%s/scratch/testFolder/files/%d/",curdir, socket->GetNode()->GetId());
            mkdir(dirname, S_IRWXU);
            sprintf(fileNameFromHelper,"%s/scratch/testFolder/files/%d/nodeFile%d.bin",curdir,socket->GetNode()->GetId(),filechunk.source);
            //printf("Filename is %s \n",fileName);
            char *com=(char*)malloc((sizeof(char)*500));
            sprintf(com,"touch %s",fileNameFromHelper);
            //FILE * writeStream;
            //writeStream = fopen(fileNameFromHelper,"ab+");
            //fclose(writeStream);

            // struct fileChunk filechunk = (struct fileChunk)malloc(packet->GetSize());
            // packet->CopyData(filechunk, packet->GetSize());

            cout<<"In HandleMessages::ReceivePacket, type 2, packet is coming from "<<filechunk.source<<". Index is "<<filechunk.index<<". Total Index is "<< filechunk.totalIndex<<". Target (Receiver Node) is " <<filechunk.target<<". Me (Receiver Node) is "<< me<< ". Sender Node is " << senderNode->GetId() << ". Write Size is (filechunk.dataSize - (packet->GetSize()-sizeof(filechunk))): " <<filechunk.dataSize <<" - "<<(packet->GetSize()-sizeof(filechunk)) <<std::endl;
            
            // WriteIntoFileByNewComerNodeApp(filechunk.buffer, filechunk.casual, tempUsedEmptyNodeforRepair);
           // WriteIntoFileByNewComerNodeApp(filechunk.buffer, filechunk.casual, filechunk);
            //this->SetSenderSocketForReply();
            // WriteIntoFileByNewComerNodeApp(filechunk.buffer, filechunk.casual, tempUsedEmptyNodeforRepair);
            //WriteIntoFileByNewComerNodeApp(filechunk.buffer, filechunk.casual, filechunk);
        }
        else if (*type == 3)
        {
            cout<< "In HandleMessages::ReceivePacket, type 3, Node ID: " << socket->GetNode()->GetId() <<"has received Packet Type REPLYREPAIRFROMUE is received."<<endl;
            cout<< "In HandleMessages::ReceivePacket, type 3, Sender Node ID: " << senderNode->GetId() << endl;
            cout<< "In HandleMessages::ReceivePacket, type 3, Receiver Node ID: " << receiverNode->GetId() << endl;
            cout << endl;
            // cout<<"Packet Type REPLYREPAIRFROMUE is received"<<endl;

            struct fileChunk filechunk; 
            filechunk.buffer=(uint8_t *)malloc(packet->GetSize());
            uint8_t* buf2 = (uint8_t *)malloc(packet->GetSize());
            packet->CopyData(buf2, packet->GetSize());
            memcpy(&filechunk, buf2, sizeof(filechunk));

            // Elif hocanın eklediği kısım
            char *curdir;
            curdir = (char*)malloc(sizeof(char)*600);
            char* dire=getcwd(curdir, 600);
            printf("Directory%s\n",dire);
            fileNameFromHelper = (char*)malloc((sizeof(char)*(strlen(curdir)+100)));
            char* dirname=(char*)malloc((sizeof(char)*(strlen(curdir)+70)));
            sprintf(dirname,"%s/scratch/testFolder/files/%d/",curdir, socket->GetNode()->GetId());
            mkdir(dirname, S_IRWXU);
            sprintf(fileNameFromHelper,"%s/scratch/testFolder/files/%d/nodeFile%d.bin",curdir,socket->GetNode()->GetId(),filechunk.source);
            //printf("Filename is %s \n",fileName);
            char *com=(char*)malloc((sizeof(char)*1500));
            sprintf(com,"touch %s",fileNameFromHelper);
           // FILE * writeStream;
           // writeStream = fopen(fileNameFromHelper,"ab+");
           // fclose(writeStream);

            // struct fileChunk filechunk = (struct fileChunk)malloc(packet->GetSize());
            // packet->CopyData(filechunk, packet->GetSize());

            cout<<"In HandleMessages::ReceivePacket, type 3, packet is coming from "<<filechunk.source<<". Index is "<<filechunk.index<<". Total Index is "<< filechunk.totalIndex<<". Target (Receiver Node) is " <<filechunk.target<<". Me (Receiver Node) is "<< me<< ". Sender Node is " << senderNode->GetId() << ". Write Size is (filechunk.dataSize - (packet->GetSize()-sizeof(filechunk))): " <<filechunk.dataSize <<" - "<<(packet->GetSize()-sizeof(filechunk)) <<std::endl;
            
            // WriteIntoFileByNewComerNodeApp(filechunk.buffer, filechunk.casual, tempUsedEmptyNodeforRepair);
            WriteIntoFileByNewComerNodeApp(filechunk.buffer, filechunk.casual, filechunk);
        }
        else if (*type == 4)
        {
            cout<< "In HandleMessages::ReceivePacket, type 4, Node ID: " << socket->GetNode()->GetId()<<" has received" <<endl;
            cout<< "In HandleMessages::ReceivePacket, type 4, Sender Node ID: " << senderNode->GetId() << endl;
            cout<< "In HandleMessages::ReceivePacket, type 4, Receiver Node ID: " << receiverNode->GetId() << endl;
            cout<<"Packet Type FIN is received."<<endl;
            cout<<"***************************************"<<endl;
            cout<<"***************************************"<<endl;
            cout<<"***************************************"<<endl;
            cout<<"***************************************"<<endl;
            cout << endl;
            // cout<<"Packet Type FIN is received"<<endl;
            finishStateCounter = finishStateCounter + 1;
            cout << "finishStateCounter: " << finishStateCounter << endl;
            if(finishStateCounter == 2)
            {
                //RepairOperation();
                //finishStateCounter = 0;
            }
        }
        // else if (*type == 5) 
        // {
        //     cout<<"Packet Type REQUESTSENDINGFROMUETOBS is received"<<endl;

        //     // struct fileParameters fileP; 
        //     // uint8_t* buf2 = (uint8_t*)malloc(packet->GetSize());
        //     // packet->CopyData(buf2, packet->GetSize());
        //     // memcpy(&fileP, buf2, sizeof(fileP));

        //     struct fileParameters fileP = (struct fileParameters)malloc(packet->GetSize());
        //     packet->CopyData(fileP, packet->GetSize());

        //     Ptr<HandleMessages> newComerNodeRequestObject = new HandleMessages(fileP.senderNode, fileP.receiverNode, fileP.receiverAddress, fileP.servPort);
        //     newComerNodeRequestObject->SendBufferFullFromNewComerNodeToBS(senderSocket, senderSocket->GetTxAvailable (), fileP.MESSAGETYPE, fileP.totalHelperFiles, fileP.nodeStr, fileP.strParameters, fileP.aliveLDPCStorageNodes);
        // }
        // else if (*type == 6) 
        // {
        //     cout<<"Packet Type REPLYSENDINGFROMUETOBS is received"<<endl;

        //     // uint8_t* buf2 = (uint8_t*)malloc(packet->GetSize());
        //     // packet->CopyData(buf2, packet->GetSize());
        //     // struct fileReturnings fileR; 
        //     // memcpy(&fileR, buf2, sizeof(fileR));

        //     struct fileReturnings fileR = (struct fileReturnings)malloc(packet->GetSize());
        //     packet->CopyData(fileR, packet->GetSize());

        //     // std::vector<string> totalHelperFiles = fileR.totalHelperFiles;
        //     // std::vector<struct ns> nodeStr = fileR.nodeStr;
        //     // struct strP strParameters = fileR.strParameters;
        //     // std::vector<int> aliveLDPCStorageNodes = fileR.aliveLDPCStorageNodes;

        //     FILE * fileTobeWritten;
        //     std::string fileToWrite = "scratch/testFolder/files/returnFileFromNewComerToBS.bin";
        //     if((fileTobeWritten = fopen(fileToWrite.c_str(),"w")) == NULL)  
        //         printf("Unable to open file to write\n");
        //     else
        //     {
        //         struct strP STR = fileR.strParameters;
        //         fwrite(&STR, sizeof(struct strP), 1, fileTobeWritten);

        //         //fwrite(&buf2, sizeof(std::uint8_t), packet->GetSize(), fileTobeWritten);

        //         // fwrite(&(fileR.totalHelperFiles)), sizeof(std::uint8_t), sizeof(fileR.totalHelperFiles), fileTobeWritten);
        //         // fwrite(&(fileR.nodeStr)), sizeof(std::uint8_t), sizeof(fileR.nodeStr), fileTobeWritten);
        //         // fwrite(&(fileR.strParameters)), sizeof(std::uint8_t), sizeof(fileR.strParameters), fileTobeWritten);
        //         // fwrite(&(fileR.aliveLDPCStorageNodes)), sizeof(std::uint8_t), sizeof(fileR.aliveLDPCStorageNodes), fileTobeWritten);
        //     }
        //     fclose(fileTobeWritten);
        // }
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void HandleMessages::WriteUntilBufferFullFromHelperNodes(Ptr<Socket> socket, uint32_t txSpace)
{
    // ELif hocanın versiyonda olmadığı için kapatılan bölüm
    // int casual=MTU;
    // int nextRead=casual;
    // int readed=0;
    // int shouldbeRead; 
    // int localIndex;
    // printf("File to be read is %s \n",inputFiles[selectedInputFileIndex].c_str());
    // struct stat status;
    // stat(inputFiles[selectedInputFileIndex].c_str(), &status);
    // FILE * fileTobeRead; 
    // if((fileTobeRead = fopen(inputFiles[selectedInputFileIndex].c_str(),"rb")) == NULL) 
    //     printf("Unable to read file \n");
    // int size = status.st_size;  //Dosyanın size'ı bulunuyor burada
    // int columnIndex = 0;
    // shouldbeRead = (int)(size * (int)(allHelperNodeIndexes.size()) / quotient);
    // int maxShouldbeRead = shouldbeRead;
    // int stopState = 0;
    // int readedCounter = 0;
    // int totalIndex = 0;
    // cout << "We are here 1 in WriteUntilBufferFullFromHelperNodes" << endl;
    // [[maybe_unused]] int sstop = 0;
    // uint8_t readedByte;

    // Burada kullanılacak helper node'a ait input file'ın indeksi belirleniyor
    int selectedInputFileIndex = 0;
    for(size_t i = 0; i < aliveLDPCStorageNodes.size(); i++)
    {
        if (selectedHelperNodeIndex == aliveLDPCStorageNodes[i])
            break;
        else
        {
            if (aliveLDPCStorageNodes[i] != -1)
                selectedInputFileIndex = selectedInputFileIndex + 1;
        }
    }

    for(size_t i = 0; i < inputFiles.size(); i++)
    {
        cout << "inputFiles[i]: " << inputFiles[i].c_str() << endl;
    }

    cout << "helperNodes: ";
    for(size_t i = 0; i < helperNodes.size(); i++)
        cout << helperNodes[i] << " ";
    cout << endl;

    cout << "aliveLDPCStorageNodes: ";
    for(size_t i = 0; i < aliveLDPCStorageNodes.size(); i++)
        cout << aliveLDPCStorageNodes[i] << " ";
    cout << endl;

    cout << "allHelperNodeIndexes: ";
    for(size_t i = 0; i < allHelperNodeIndexes.size(); i++)
        cout << allHelperNodeIndexes[i] << " ";
    cout << endl;

    cout << "We are at the beginning of WriteUntilBufferFullFromHelperNodes" << endl;
    cout << "selectedHelperNodeIndex: " << selectedHelperNodeIndex << endl;
    cout << "selectedInputFileIndex: " << selectedHelperNodeIndex << endl;
    cout << "Size of inputFiles: " << inputFiles.size() << endl;
    cout << "Size of helperNodes: " << helperNodes.size() << endl;
    cout << "Size of aliveLDPCStorageNodes: " << aliveLDPCStorageNodes.size() << endl;
    cout << "Size of allHelperNodeIndexes: " << allHelperNodeIndexes.size() << endl;
    cout << "quotient: " << quotient << endl;
    cout << "inputFiles[selectedInputFileIndex]: " << inputFiles[selectedInputFileIndex].c_str() << endl;
    
    //File directory'si verilen dosyadan paket oluşturuluyor. O dosya bitene kadar paket gönderiliyor. Örnek olarak oluşturulan bu dosyadan veri okunarak paketler oluşturuluyor kısaca.
    //O paketin türü de REPLYREPAIRFROMBS. Yani REPLYREPAIRFROMBS diye bir paket türü gönderiliyor. Karşı taraf da dosyamız bitene kadar alıyor.  

    // Ptr<Node> tempNode = CreateObject<Node>();
    // tempNode = receiverNode;
    // receiverNode = senderNode;
    // senderNode = tempNode;
    // senderSocket = Socket::CreateSocket(senderNode, TcpSocketFactory::GetTypeId());
    // receiverSocket = Socket::CreateSocket(receiverNode, TcpSocketFactory::GetTypeId());


    // senderSocket = Socket::CreateSocket (receiverNode, TcpSocketFactory::GetTypeId ());
    // receiverSocket = Socket::CreateSocket(senderNode, TcpSocketFactory::GetTypeId());

    // Kapatılan bölüm
    // servPort = servPort + 1;
    // senderSocket = Socket::CreateSocket (senderNode, TcpSocketFactory::GetTypeId ());
    // receiverSocket = Socket::CreateSocket(receiverNode, TcpSocketFactory::GetTypeId());
    // senderSocket->Connect (InetSocketAddress (receiverAddress, servPort)); //connect

    // uint8_t tempVal;
    // uint8_t* bufData=(uint8_t*)(malloc(nextRead));
    // std::vector<uint8_t> bufData(nextRead,0);

    struct fileChunk fchunk;
    std::vector<uint8_t> bufData;
    while(stopState == 0)
    {
        cout << endl;
        cout << "stopState: " << stopState << endl;
        cout << "We are here 1_1 in WriteUntilBufferFullFromHelperNodes" << endl;
        // Bu for döngüsünde ilgili input file'dan veriler okunuyor
        for (size_t r = 0; r < allHelperNodeIndexes.size(); r++)
        {
            localIndex = allHelperNodeIndexes[r] - ((allHelperNodeIndexes[r]/quotient)*quotient);
            cout << "localIndex: " << localIndex << endl; 
            cout << "selectedHelperNodeIndex: " << selectedHelperNodeIndex << endl;
            cout << "selectedEmptyNodeIndex: " << selectedEmptyNodeIndex << endl;
            cout << "selectedEmptyNodeLogicalIndex: " << selectedEmptyNodeLogicalIndex << endl;
            cout << "Size of inputFiles: " << inputFiles.size() << endl;
            cout << "inputFiles[selectedHelperNodeIndex]: " << inputFiles[selectedInputFileIndex].c_str() << endl;
            // cout << "inputFiles[selectedEmptyNodeIndex]: " << inputFiles[selectedEmptyNodeIndex].c_str() << endl;
            cout << "shouldbeRead: " << shouldbeRead << endl;
            cout << "casual: " << casual << endl;
            // cout << "maxShouldbeRead: " << maxShouldbeRead << endl;
            cout << "columnIndex: " << columnIndex << endl;
            cout << "quotient: " << quotient << endl;
            cout << "Size of allHelperNodeIndexes: " << allHelperNodeIndexes.size() << endl;
            cout << "allHelperNodeIndexes[r]: " << allHelperNodeIndexes[r] << endl;
            // cout << "Size of the selected input file: " << size << endl;

            fseek(fileTobeRead, columnIndex*quotient + localIndex, SEEK_SET);
            // if((readed = fread(bufData, sizeof(uint8_t), 1, fileTobeRead)) != 0  && shouldbeRead != 0)
            if((readed = fread(&readedByte, sizeof(uint8_t), 1, fileTobeRead)) != 0  && shouldbeRead > 0)
            {
                cout << "Data is readed" << endl;
                cout << "readedCounter: "<< readedCounter << endl;
                // cout << "size of bufData: " << bufData.size() << endl;
                bufData.push_back(readedByte);
                shouldbeRead = shouldbeRead-readed;
                readedCounter = readedCounter + 1;
            }
            else
            {
                cout << "Data is not readed" << endl;
                stopState = 1;
                if (fileTobeRead!=NULL)
                 fclose(fileTobeRead);
                //break;
                if (shouldbeRead > casual) 
                  nextRead = casual;
                else
                  nextRead = shouldbeRead;
            }
            cout << "readed: " << readed << endl;
        }
        cout << endl;
        cout << "We are here 1_2 in WriteUntilBufferFullFromHelperNodes" << endl;
        cout << "readedCounter: " << readedCounter << endl;
        cout << "nextRead: " << nextRead << endl;
        // Burada okunan veri miktarı, MTU değerine ya da son aşamada ise daha az veriye karşılık gelen nextRead ile kıyaslanıyor. 
        // Eğer aranan sınıra ulaşıldı ise fileChunk struct'ı oluşturulup bilgiler atanıyor değişkenlere ve paket halinde receiver pozisyonundaki node'a gönderiliyor. 
        // Bu döngü dosya stopState durumu 1'e dönene kadar devam ediyor. Dosyada okunacak veri kalmadığında aşağıdaki FIN mesajı gönderme işlemi yapılıyor. (770. satırda)
        if (((readedCounter == nextRead && readedCounter > 0) || (stopState == 1 && readedCounter > 0)) && socket->GetTxAvailable () >= (unsigned)(MTU))
        {
            cout << "We are here 1_2_1 in WriteUntilBufferFullFromHelperNodes" << endl;
            //Burada verinin başına overhead gibi bir header ekleniyor
            fchunk.MESSAGETYPE = REPLYREPAIRFROMUE;   //Paket türü REPLYREPAIRFROMUE oluyor. Yani baz istasyonundan gelen cevap.
            fchunk.index = index;//lastIndexREPAIRRESPONSE[to];
            //lastIndex[to]=index; // To trace for next writeuntilbuffer
            fchunk.source = socket->GetNode()->GetId();//senderSocket->GetNode()->GetId();
            //fchunk.target = staWifiNode2.GetId(); //node Id to be target/destination
            fchunk.target = receiverNode->GetId();//receiverSocket->GetNode()->GetId();
            //fchunk.dataSize = sizeof(readed);
            fchunk.dataSize = bufData.size();
            fchunk.totalIndex = totalIndex; //totalIndex-1;
            fchunk.blocksize = readed;

            // fchunk.buffer = bufData;
            fchunk.buffer = bufData.data();
            fchunk.casual = casual;
            //fchunk.tempUsedEmptyNodeforRepair = tempUsedEmptyNodeforRepair;
            index = index + 1 ;
            //lastIndexREPAIRRESPONSE[to]++;//++; To trace for next writeuntilbuffer  

            const struct fileChunk fchunkc = fchunk;     
            //int readed=fread(bufint, sizeof(uint8_t), 1460-sizeof(fchunk) , readFileStreams[j]);
            uint8_t *bufferStruct = (uint8_t *)(malloc(MTU));  //Okuduğumuz veri bufferStruct içerisine atılıyor
            //memcpy(bufferStruct,&fchunkc, sizeof(struct fileChunk));  
            memcpy(bufferStruct,&fchunkc, sizeof(fchunkc));  
            // uint8_t* bufint2 = bufferStruct + sizeof(fchunkc);
            // memcpy(bufint2, bufData, readed);

            Ptr<Packet> pkt1 = Create<Packet>(bufferStruct,MTU);
            // Ptr<Packet> pkt1 = Create<Packet> (MTU);
            // Ptr<Packet> pkt1 = Create<Packet> (reinterpret_cast<const uint8_t*> ("hello"), 5);

            //Ptr <Packet> pkt1 = Create<Packet>(bufint2,MTU);
            // cout << "Packet Size: " << pkt1.GetSize() << endl;
            [[maybe_unused]] int res = socket->Send(pkt1);
            if(res == -1)
                cout << "Packet cannot be sent." << endl;
            else
                cout << "Packet is sent successfully." << endl;

            cout << endl;
            cout << "stopState: " << stopState << endl;
            cout << "servPort: " << servPort << endl;
           // cout << "senderSocket->GetTxAvailable(): " << senderSocket->GetTxAvailable () << endl;
            //cout << "receiverSocket->GetRxAvailable(): " << receiverSocket->GetRxAvailable () << endl;
           // cout << size"senderNode->GetId(): " << senderNode->GetId() << endl;
            //cout << "receiverNode->GetId(): " << receiverNode->GetId() << endl;
            cout << "fchunkc.source: " << fchunkc.source << endl;
            cout << "fchunkc.target: " << fchunkc.target << endl;
            cout << "selectedHelperNodeIndex: " << selectedHelperNodeIndex << endl;
            cout << "selectedEmptyNodeIndex: " << selectedEmptyNodeIndex << endl;
            cout << "selectedEmptyNodeLogicalIndex: " << selectedEmptyNodeLogicalIndex << endl; 
            // if (receiverSocket->GetRxAvailable() > 0)
            cout << "shouldbeRead: " << shouldbeRead << endl;
            // cout << "maxShouldbeRead: " << maxShouldbeRead << endl;
            cout << "readedCounter: " << readedCounter << endl;
            cout << "nextRead: " << nextRead << endl;
            cout << "casual: " << casual << endl;
            cout << "senderSocket: " << senderSocket << endl;
            cout << "senderNode: " << senderNode << endl;
            cout << "pkt1: " << pkt1 << endl;
            cout << "res: " << res << endl;
            cout << "MTU: " << MTU << endl;
            cout << "size of bufferStruct: " << sizeof(bufferStruct) << endl;
            // cout << "size of bufint2: " << sizeof(bufint2) << endl;
            // cout << "size of bufData: " << sizeof(bufData) << endl;
            cout << "size of bufData: " << bufData.size() << endl;
            cout << "size of uint8_t: " << sizeof(uint8_t) << endl;
            cout << "fchunkc.dataSize: " << fchunkc.dataSize << endl;
            cout << "size of fchunkc: " << sizeof(fchunkc) << endl;
            cout << "size of struct fileChunk: " << sizeof(struct fileChunk) << endl;
            cout << "Size of allHelperNodeIndexes: " << allHelperNodeIndexes.size() << endl;
            strParameters.numberofReadedSymbolsfromNodesforLDPCRepair = strParameters.numberofReadedSymbolsfromNodesforLDPCRepair + readedCounter;

            printf("\n Writeuntilbuffer has send a packet  %d index %d lastIndexREPAIRRESPONSE %d totalIndex %d \n", res, fchunk.index, index, totalIndex);
            cout << endl;
            readedCounter = 0;
            totalIndex = totalIndex + 1;

            bufData.clear();
            cout << "We are here 1_2_2 in WriteUntilBufferFullFromHelperNodes" << endl;
        } 
        cout << "We are here 1_3 in WriteUntilBufferFullFromHelperNodes" << endl; 
        // if (sstop == 1)
        //     break;
    }
    if (fileTobeRead!=NULL)
        fclose(fileTobeRead);
    
    // fclose(fileTobeRead);

    // struct fileSIGNAl fS;
    // fS.MESSAGETYPE = FIN;
    // fS.source = senderSocket->GetNode()->GetId();
    // fS.target = receiverSocket->GetNode()->GetId(); 
    // uint8_t *bufferLocalStruct = (uint8_t *)(malloc(struct fileSIGNAl));
    // memcpy(bufferLocalStruct, &fS, sizeof(struct fileSIGNAl));
    // Ptr <Packet> finishPkt1 = Create<Packet>(bufferLocalStruct, sizeof(struct fileSIGNAl);
    // int res2 = senderSocket->Send(finishPkt1); 

    // struct fileParameters fP;
    // fP.MESSAGETYPE = FIN;
    // // fP.senderNode = senderNode; 
    // // fP.receiverNode = receiverNode;
    // fP.senderNode = staWifiNode1;  //senderNode
    // //fP.receiverNode = staWifiNode2;   //receiverNode
    // fP.receiverNode = remoteHost;   //receiverNode 
    // // fP.senderAddress = senderAddress;
    // // fP.receiverAddress = receiverAddress;
    // fP.senderAddress = ueIpIface.GetAddress (selectedEmptyNodeIndex);;
    // fP.receiverAddress = ueIpIface.GetAddress (selectedHelperNodeIndex);
    // fP.servPort = servPort;
    // fP.ueIpIface = ueIpIface; 
    // fP.allHelperNodeIndexes = allHelperNodeIndexes; 
    // fP.inputFiles = inputFiles;
    // fP.selectedHelperNodeIndex = selectedHelperNodeIndex;
    // fP.selectedEmptyNodeIndex = selectedEmptyNodeIndex;
    // fP.quotient = quotient;
    // //fP.tempUsedEmptyNodeforRepair = quotient; 
    // fP.baseStation = baseStation;
    // fP.failedSymbolIDsForRepairFromBS = failedSymbolIDsForRepairFromBS; 
    // fP.maxColLength = maxColLength;
    // fP.R1 = R1;
    // fP.R2 = R2;
    // fP.L = L;
    // fP.helperNodes = helperNodes;
    // fP.tempUsedEmptyNodeforRepair = tempUsedEmptyNodeforRepair;
    // fP.numberofRoundforBuffer = numberofRoundforBuffer;
    // fP.currentLostLDPCChunkSymbols = currentLostLDPCChunkSymbols;
    // fP.strParameters = strParameters;
    // fP.unrepairedSymbolsfromNodes = unrepairedSymbolsfromNodes;
    // fP.unrepairedSymbolsfromBS = unrepairedSymbolsfromBS;
    // fP.allEquationsR2 = allEquationsR2;
    // fP.foundOne = foundOne;
    // fP.repairedFile = repairedFile;
    // fP.totalHelperFiles = totalHelperFiles;
    // fP.cols = cols;
    // fP.nodeStr = nodeStr;
    // fP.aliveLDPCStorageNodes = aliveLDPCStorageNodes;
    // fP.remoteHost = remoteHost;
    // uint8_t *bufferLocalStruct = (uint8_t *)(malloc(sizeof(struct fileParameters)));
    // memcpy(bufferLocalStruct, &fP, sizeof(struct fileParameters));
    // Ptr <Packet> finishPkt1 = Create<Packet>(bufferLocalStruct, sizeof(sizeof(struct fileParameters));
    // [[maybe_unused]] int res2 = senderSocket->Send(finishPkt1); 
    cout << "We are here 1_4 in WriteUntilBufferFullFromHelperNodes" << endl;
    // Burada dosyadan okuma işleminin tamamlandığı FIN mesajı ile gönderiliyor. Buradaki mesaj daha sonra receivePacket içerisinde değerlendiriliyor. 
    enum MType currentMessage = FIN;
    uint8_t *bufferLocalStruct = (uint8_t *)(malloc(sizeof(currentMessage)));
    memcpy(bufferLocalStruct, &currentMessage, sizeof(currentMessage));
    Ptr <Packet> finishPkt1 = Create<Packet>(bufferLocalStruct, sizeof(currentMessage));
    [[maybe_unused]] int res2 = socket->Send(finishPkt1); 
    if(res2 == -1)
        cout << "Packet 2 cannot be sent." << endl;
    else
        cout << "Packet 2 is sent successfully." << endl;
    cout << endl;
    
    cout << "stopState: " << stopState << endl;
    cout << "servPort: " << servPort << endl;
    //: " << socket->GetTxAvailable () << endl;
    //cout << "receiverSocket->GetRxAvailable(): " << receiverSocket->GetRxAvailable () << endl;
    //cout << "senderNode->GetId(): " << senderNode->GetId() << endl;
    //cout << "receiverNode->GetId(): " << receiverNode->GetId() << endl;
    cout << "fchunk.source: " << fchunk.source << endl;
    cout << "fchunk.target: " << fchunk.target << endl;
    cout << "senderSocket: " << senderSocket << endl;
    cout << "senderNode: " << senderNode << endl; 
    cout << "finishPkt1: " << finishPkt1 << endl;
    cout << "res2: " << res2 << endl;
    cout << "MTU: " << MTU << endl;
    cout << "readedCounter: " << readedCounter << endl;
    cout << "nextRead: " << nextRead << endl;
    //cout << "senderSocket->GetTxAvailable(): " << senderSocket->GetTxAvailable () << endl;
    cout << "size of bufferLocalStruct: " << sizeof(bufferLocalStruct) << endl;
    cout << "We are at the end of WriteUntilBufferFullFromHelperNodes" << endl;
    cout << endl;
}

// Veri okuma işlemi ilgili düğüm ya da baz istasyonundan tamamlandıktan sonra bu fonksiyon yardımıyla dosyaya yazdırılıyor.
// void HandleMessages::WriteIntoFileByNewComerNodeApp(uint8_t* bufData, int casual, std::string tempUsedEmptyNodeforRepair)
// {
//     FILE * fileTobeWritten;
//     if((fileTobeWritten = fopen(tempUsedEmptyNodeforRepair.c_str(),"wb")) == NULL)  
//         printf("Unable to open file to write\n");
//     else
//         fwrite(&bufData, sizeof(std::uint8_t), casual, fileTobeWritten);
//     fclose(fileTobeWritten);
// }

// Elif hocanın eklediği fonksiyon
void HandleMessages::WriteIntoFileByNewComerNodeApp(uint8_t* bufData, int casual,struct fileChunk fchunk)
{
    FILE * fileTobeWritten;
    if((fileTobeWritten = fopen(fileNameFromHelper,"wb")) == NULL)  
        printf("Unable to open file to write\n");
    else
    {
        int seekSize=fchunk.index*(MTU-sizeof(fchunk));
        cout<<"seekSize "<<seekSize <<"\n";
        ofstream file2 (fileNameFromHelper, ios::in | ios::binary | ios::ate);
        file2.seekp(seekSize,ios::beg);
        for (int i = 0; i < fchunk.dataSize; i++) 
        {
            char CStr = (char) bufData[i];
            file2.write(&CStr, 1);
        }
    }
}

// Helper node'lar için gerçekleştirilen veri okuma işlemi burada baz istasyonu üzerinden gerçekleştiriliyor. 
// Baz istasyonunu temsil eden dosyada encoded veri tutuluyor o yüzden direk işleme tabi tutmadan kullanılabiliyor.
void HandleMessages::WriteUntilBufferFullFromBS(Ptr<Socket> socket, uint32_t txSpace)
{
    [[maybe_unused]] int casual=MTU;
    [[maybe_unused]] int nextRead=casual;
    int readed=0;
  
    //File directory'si verilen dosyadan paket oluşturuluyor. O dosya bitene kadar paket gönderiliyor. Örnek olarak oluşturulan bu dosyadan veri okunarak paketler oluşturuluyor kısaca.
    //O paketin türü de REPLYREPAIRFROMBS. Yani REPLYREPAIRFROMBS diye bir paket türü gönderiliyor. Karşı taraf da dosyamız bitene kadar alıyor.  
    printf("File to be read is %s \n",baseStation.c_str());
    char *curdir;
     curdir = (char*)malloc(sizeof(char)*600);
    char* dire=getcwd(curdir, 600);
    printf("Directory%s\n",dire);
    char * BSFile      = (char*)malloc((sizeof(char)*(strlen(curdir)+150)));
    //char* dirname=(char*)malloc((sizeof(char)*(strlen(curdir)+70)));
    sprintf(BSFile,"%s/%s",curdir, baseStation.c_str());
    struct stat status;
    stat(BSFile, &status);
    FILE * fileTobeRead; 
    if((fileTobeRead = fopen(BSFile,"rb")) == NULL)  
        printf("Unable to read file \n");

   

    int size = status.st_size;  //Dosyanın size'ı bulunuyor burada
    int columnIndex;
    int totalIndex;
    //uint8_t localBufData;
    int stopState = 0;
    int readedCounter = 0;
    int numberofTotalColumns = (int)(size / maxColLength);
    uint8_t readedByte;

    struct fileChunk fchunk;
    std::vector<uint8_t> bufData;
    // while(stopState == 0)
    // {
    for (size_t r = 0; r < failedSymbolIDsForRepairFromBS.size(); r++)
    {
      columnIndex = 0;
      while(columnIndex < numberofTotalColumns || stopState == 0)
      {
        fseek(fileTobeRead, columnIndex * maxColLength + failedSymbolIDsForRepairFromBS[r], SEEK_SET);
        // if((readed = fread(bufData, sizeof(uint8_t), 1, fileTobeRead)) != 0)
        if((readed = fread(&readedByte, sizeof(uint8_t), 1, fileTobeRead)) != 0)
        {
            readedCounter = readedCounter + 1;
            cout << "readedCounter: "<< readedCounter << endl;
            cout << "size of bufData: " << bufData.size() << endl;
            bufData.push_back(readedByte);
        }
        else
        {
            if(readedCounter == (int)MTU)
                nextRead = MTU;
            else
                nextRead = readedCounter;
            stopState = 1;
        }

        //memcpy(bufData, localBufData, readed);
        //if ((readedCounter == nextRead || (stopState == 1 && readedCounter > 0)) && senderSocket->GetTxAvailable () >= (unsigned)(MTU))
        if (((readedCounter == nextRead && readedCounter > 0) || (stopState == 1 && readedCounter > 0)) && socket->GetTxAvailable () >= (unsigned)(MTU))
        {
            //Burada verinin başına overhead gibi bir header ekleniyor
            fchunk.MESSAGETYPE = REPLYREPAIRFROMBS;   //Paket türü REPLYREPAIRFROMBS oluyor. Yani baz istasyonundan gelen cevap.
            fchunk.index = index; //lastIndexREPAIRRESPONSE[to];
            //lastIndex[to]=index; // To trace for next writeuntilbuffer
            fchunk.source = socket->GetNode()->GetId();
            //fchunk.target = staWifiNode2.GetId();; //node Id to be target/destination
            //fchunk.target = receiverSocket->GetNode()->GetId();
            // fchunk.dataSize = readedCounter;
            fchunk.dataSize = bufData.size();
            fchunk.totalIndex = totalIndex; //totalIndex-1;
            fchunk.blocksize = columnIndex;

            // fchunk.buffer = bufData;
            fchunk.buffer = bufData.data();
            fchunk.casual = casual;
            //fchunk.tempUsedEmptyNodeforRepair = tempUsedEmptyNodeforRepair;

            index = index + 1;   
            const struct fileChunk fchunkc = fchunk;     
            //int readed=fread(bufint, sizeof(uint8_t), 1460-sizeof(fchunk) , readFileStreams[j]);
            uint8_t *bufferStruct = (uint8_t *)(malloc(MTU));  //Okuduğumuz veri bufferStruct içerisine atılıyor
            //memcpy((bufferStruct),&fchunkc,(sizeof(struct fileChunk))); 
            memcpy(bufferStruct,&fchunkc, sizeof(fchunkc));   
            // uint8_t* bufint2 = bufferStruct + sizeof(fchunkc);
            // memcpy(bufint2, bufData, readed);
            Ptr<Packet> pkt1 = Create<Packet>(bufferStruct,MTU);
            //Ptr <Packet> pkt1 = Create<Packet>(bufint2,MTU);
             printf("\n BS beforeWriteuntilbuffer has send a");
            [[maybe_unused]] int res = socket->Send(pkt1);

            strParameters.numberofReadedSymbolsfromBSforLDPCRepair = strParameters.numberofReadedSymbolsfromBSforLDPCRepair + readedCounter;

            //localNewComerNodeApp->WriteIntoFileByNewComerNodeApp(bufData, casual, tempUsedEmptyNodeforRepair);
            //fwrite(&bufData, sizeof(std::uint8_t), readedCounter, fileTobeWritten);

            printf("\n Writeuntilbuffer has send a packet  %d index %d lastIndexREPAIRRESPONSE %d totalIndex %d \n",res,fchunk.index,index,totalIndex);
            readedCounter = 0;

            bufData.clear();

            // free(bufData);
            // bufData=(uint8_t*)(malloc(casual));

            totalIndex = totalIndex + 1;
        }
        columnIndex = columnIndex + 1;
      }
    }
    // }
    fclose(fileTobeRead);
    //fclose(fileTobeWritten);

    enum MType currentMessage = FIN;
    uint8_t *bufferLocalStruct = (uint8_t *)(malloc(sizeof(currentMessage)));
    memcpy(bufferLocalStruct, &currentMessage, sizeof(currentMessage));
    Ptr <Packet> finishPkt1 = Create<Packet>(bufferLocalStruct, sizeof(sizeof(currentMessage)));
    [[maybe_unused]] int res2 = socket->Send(finishPkt1); 
}

// void HandleMessages::SendBufferFullFromNewComerNodeToBS (Ptr<Socket> senderSocket, uint32_t txSpace, enum MType messageType, std::vector<std::string> totalHelperFiles, std::vector<struct ns> nodeStr, struct strP strParameters, std::vector<int> aliveLDPCStorageNodes)
// {
//     struct fileReturnings fR;

//     fR.MESSAGETYPE = REPLYSENDINGFROMUETOBS; 
//     fR.totalHelperFiles = totalHelperFiles;
//     fR.nodeStr = nodeStr;
//     fR.strParameters = strParameters;
//     fR.aliveLDPCStorageNodes = aliveLDPCStorageNodes;

//     uint8_t *bufferStruct1 = (uint8_t *)(malloc(sizeof(struct fileReturnings)));
//     memcpy(bufferStruct1, &fR, sizeof(struct fileReturnings));
//     Ptr <Packet> pkt1 = Create<Packet>(bufferStruct1, sizeof(fR));
//     [[maybe_unused]] int res = senderSocket->Send(pkt1);
//     //fwrite(&bufferStruct1, sizeof(std::uint8_t), sizeof(totalHelperFiles), fileTobeWritten);

//     //std::vector<string> totalHelperFiles, std::vector<struct ns> nodeStr, struct strP strParameters, std::vector<int> aliveLDPCStorageNodes

// }

//void HandleMessages::RepairOperation(Ptr<Socket> socket, int foundOne, std::string repairedFile, std::vector<string> totalHelperFiles, int cols, std::vector<struct ns> nodeStr, Ipv4InterfaceContainer ueIpIface, std::vector<std::string> inputFiles, int selectedHelperNodeIndex, int selectedEmptyNodeIndex, int quotient, std::string tempUsedEmptyNodeforRepair, std::vector<int> failedSymbolIDsForRepairFromBS, int maxColLength, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, std::vector<int> L, std::vector<int> helperNodes, int numberofRoundforBuffer, std::vector<int> currentLostLDPCChunkSymbols, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<int>> allEquationsR2, Ptr<Node> remoteHost, std::vector<int> aliveLDPCStorageNodes, std::vector<int> allHelperNodeIndexes)
// Bu fonksiyonda da helper node'lara ait dosyalardan veri okuma süreci tamamlandıktan sonra son aşamada xor'lama ile onarım işlemi gerçekleştiriliyor.
void HandleMessages::RepairOperation()
{
    //Struct sraV1Local;
    struct generateHelpersReturns gHR;
    struct firstPhaseReturns fpr;
    struct secondPhaseReturns spr;
    
    // string root_directory = "C:\\Users/Erdi/Documents/Visual Studio 2015/Projects/HildegardvonBingen/HildegardvonBingen/files/";
    std::string root_directory = "scratch/testFolder/files/";
    std::string baseStation = root_directory + "baseStation.bin";

    // Generating helper symbol indexes for each lost symbol
    std::vector<int>::iterator it;
    std::vector<int> v;
    //int intR;
    //int failedSymbolID;
    std::vector<int> helperSymbolIndexes;
    //std::vector<std::vector<int>> allEquations (recoveryEquations[0].size() + allEquationsR2[0].size(), std::vector<int>(std::max(recoveryEquations[0].size(), allEquationsR2.size() - 1)));
    std::vector<std::vector<int>> allEquations;
    // tempEquations = recoveryEquations;
    std::vector<std::vector<int>> tempEquations;
    std::vector<int> symbols;
    std::vector<int> fileIndexes;
    //int tempVal;
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
    //int jj;
    //int readIndex;
    std::vector<std::vector<int>> R1Temp;
    std::vector<std::vector<int>> R2Temp;
    std::vector<uint8_t> buffer2(quotient);
    // int bInd;
    //char * buffer = new char[quotient];
    int stopState = 0;
    int readed = 0;
    int columnIndex = 0;
    int currentColumnIndex = 0;
    std::vector<int> inputFilesSize {};
    string path;
    //int intersectionState;
    [[maybe_unused]] uint32_t  udpPacketSize = (uint32_t)numberofRoundforBuffer;

    std::vector<int> tempUsedHelpers{};
    //std::vector<int> helperNodes; 
    std::vector<int>  helperNodes2;
    std::vector<int> currentHelperNodeIndexes{};
    std::vector<int> currentHelperNodeIndexes2{};
    //std::vector<int> allHelperNodeIndexes{};
    std::vector<int>::iterator tempIt, tempIt2;
    [[maybe_unused]]int repairedFileSize;
    [[maybe_unused]]int tempUsedEmptyNodeFileSize;
    ;
    Ipv4Address receiverAddress;

    [[maybe_unused]]uint16_t servPort = 5000;
    Ptr<Node> staWifiNode1, staWifiNode2;
    Address defaultAddress;
    FILE *repairedFileID, *tempUsedEmptyNodeID;
    repairedFileID = fopen(repairedFile.c_str(), "a");
    tempUsedEmptyNodeID = fopen(tempUsedEmptyNodeforRepair.c_str(), "rb+");
    //tempUsedEmptyNodeFileSize = std::filesystem::file_size(tempUsedEmptyNodeforRepair.c_str());
    struct stat st;
    stat(tempUsedEmptyNodeforRepair.c_str(), &st);
    tempUsedEmptyNodeFileSize = st.st_size;
    int allRepairFileData;
    std::vector<int> numberofCurrentHelperNodeIndexes, shouldbeReads;
    //std::vector<std::vector<int>> vectorofCurrentHelperNodeIndexes(helperNodes.size());
    std::vector<std::vector<int>> vectorofCurrentHelperNodeIndexes{};
    int totalDatafromNodes = 0;
    int selectedCurrentHelperNodeIndex;

    cout << "We are 1 in HandleMessages::RepairOperation." << endl;
    for (size_t h = 0; h < helperNodes.size(); h++)
    {
        selectedCurrentHelperNodeIndex = aliveLDPCStorageNodes[helperNodes[h]];
        currentHelperNodeIndexes.clear();
        for (size_t r = 0; r < allHelperNodeIndexes.size(); r++)
        {
            if (selectedCurrentHelperNodeIndex == allHelperNodeIndexes[r]/quotient)
                currentHelperNodeIndexes.push_back(allHelperNodeIndexes[r]);
        }
        numberofCurrentHelperNodeIndexes.push_back(currentHelperNodeIndexes.size());
        shouldbeReads.push_back((int)(inputFilesSize[h] * (int)currentHelperNodeIndexes.size() / quotient));
        totalDatafromNodes = totalDatafromNodes + (int)(inputFilesSize[h] * (int)currentHelperNodeIndexes.size() / quotient);
        //vectorofCurrentHelperNodeIndexes[h].push_back(currentHelperNodeIndexes);
        vectorofCurrentHelperNodeIndexes.push_back(currentHelperNodeIndexes);
    }

    cout << "We are 2 in HandleMessages::RepairOperation." << endl;
    //std::vector<uint8_t> bufData2;
    uint8_t* bufData2 = new uint8_t;
    uint8_t* bufData3 = new uint8_t;
    while (stopState == 0)
    {
        //Helper node'lara ait veriler new comer node'un dosyasından okunarak vektöre atılıyor.
        allRepairFileData = 0;
        for (size_t h = 0; h < helperNodes.size(); h++)
        {   
            fseek (tempUsedEmptyNodeID, allRepairFileData + (columnIndex*numberofCurrentHelperNodeIndexes[h]), SEEK_SET);
            //bufData2.resize(numberofCurrentHelperNodeIndexes[h]);            // Allocate required storage
            if ((readed = fread(&bufData2, sizeof(uint8_t), numberofCurrentHelperNodeIndexes[h], tempUsedEmptyNodeID)) != 0)
            {
                for (int i = 0; i < numberofCurrentHelperNodeIndexes[h]; i++)
                    readedDatainBuffer[vectorofCurrentHelperNodeIndexes[h][i]].push_back(bufData2[i]);
            }
            else
                stopState = 1;
            allRepairFileData = allRepairFileData + shouldbeReads[h];
        }
        //bufData2.clear();
        cout << "We are 3 in HandleMessages::RepairOperation." << endl;

        //Baz istasyonundan okunarak new comer node'un dosyasına atılan veriler okunarak vektöre ekleniyor.
        for (size_t r = 0; r < failedSymbolIDsForRepairFromBS.size(); r++)
        {   
            fseek(tempUsedEmptyNodeID, totalDatafromNodes + columnIndex * failedSymbolIDsForRepairFromBS.size() + r, SEEK_SET);
            if ((readed = fread(&bufData3, sizeof(uint8_t), 1, tempUsedEmptyNodeID)) != 0)
                readedDatainBuffer[failedSymbolIDsForRepairFromBS[r]].push_back(bufData3[0]);
            else
                stopState = 1;
        }

        cout << "We are 4 in HandleMessages::RepairOperation." << endl;
        if((columnIndex == numberofRoundforBuffer-1) || (stopState == 1))
        {
            //transposeV1(readedDatainBuffer);
        
            if(!readedDatainBuffer.empty())
            {
                R1Temp = R1;
                R2Temp = R2;
                cout << "We are 5 in HandleMessages::RepairOperation." << endl;
                //fpr = FirstPhaseV2(currentLostLDPCChunkSymbols, L, R1, R2, strParameters, unrepairedSymbolsfromNodes, unrepairedSymbolsfromBS, readedDatainBuffer, allEquationsR2, quotient, selectedEmptyNodeIndex, ueNetDev, numberofRoundforBuffer, servPort, mobility, address, inputFiles, aliveLDPCStorageNodes, ueNodes, wifiHelper);          
                fpr = FirstPhaseV2(currentLostLDPCChunkSymbols, L, R1, R2, strParameters, unrepairedSymbolsfromNodes, unrepairedSymbolsfromBS, readedDatainBuffer, allEquationsR2); 
                encodedData.clear();
                L.clear();
                currentLostLDPCChunkSymbols.clear();
                R2.clear();
                R2ReducedCopy.clear();
                unrepairedSymbolsfromNodes.clear();
                unrepairedSymbolsfromBS.clear();
                usedHelpers.clear();

                //strParameters = fpr.strParameters;
                encodedData = fpr.encodedData;
                L = fpr.L;
                currentLostLDPCChunkSymbols = fpr.currentLostLDPCChunkSymbols;              
                R2 = fpr.R2;
                R2ReducedCopy = fpr.R2ReducedCopy;
                unrepairedSymbolsfromNodes = fpr.unrepairedSymbolsfromNodes;
                unrepairedSymbolsfromBS = fpr.unrepairedSymbolsfromBS;
                usedHelpers = fpr.usedHelpers;
                cout << "We are 6 in HandleMessages::RepairOperation." << endl;
                //spr = SecondPhaseV2(currentLostLDPCChunkSymbols, L, R2, R2ReducedCopy, strParameters, encodedData, currentColumnIndex, cols, stopState, maxColLength, quotient, selectedEmptyNodeIndex, ueNetDev, gNbNetDev, numberofRoundforBuffer, ipInterfs, staInterface, servPort, apWifiNode, ueIpIface, remoteHost, inputFiles, aliveLDPCStorageNodes, wifiHelper);    
                spr = SecondPhaseV2(currentLostLDPCChunkSymbols, L, R2, R2ReducedCopy, strParameters, encodedData, currentColumnIndex, cols, stopState);   
                encodedData.clear();    
                //strParameters = spr.strParameters;          
                encodedData = spr.encodedData;
                currentColumnIndex = spr.currentColumnIndex;
                stopState = spr.stopState;
                readedDatainBuffer.clear();             
                R1 = R1Temp;
                R2 = R2Temp;
                // WRITING TO EMPTY NODES   
                cout << "We are 7 in HandleMessages::RepairOperation." << endl;
                for (size_t l = 0; l < encodedData[0].size(); l++)
                {
                    buffer2.clear();
                    for (int b = foundOne * quotient; b < foundOne * quotient + quotient; b++)
                        buffer2.push_back(encodedData[b][l]);       
                    fwrite(&buffer2, sizeof(std::uint8_t), quotient, repairedFileID);
                }
                cout << "We are 8 in HandleMessages::RepairOperation." << endl;
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
            }
        }   
        cout << "We are 9 in HandleMessages::RepairOperation." << endl;
        if(columnIndex == numberofRoundforBuffer-1)
            columnIndex = 1;
        else
            columnIndex = columnIndex + 1;
    }   
    // Closing all open files
    for (auto& stream : inputFileIDs)
    {
        (*stream).close();  
    }
    fclose(repairedFileID);
    cout << "File close process is done in SingleRepairFile" << endl;

    strParameters.usedNodes = inputFiles;

    // sraV1Local.totalHelperFiles = totalHelperFiles;
    // sraV1Local.nodeStr = nodeStr;
    // sraV1Local.strParameters = strParameters;
    // sraV1Local.aliveLDPCStorageNodes = aliveLDPCStorageNodes;

    //return sraV1Local;
}

#endif 