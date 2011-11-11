//Author: P. Bharat
//Roll No: 08114022
//Branch: CSE, 4th year


#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

//Global time
int globalTime = 0;

//the area till which the receiver has acknowedged
int receiverAck;  

// To determine the efficiency of the network
float percentageEff;
int numberPacketsLost;

//The sender window. SWP stands for Sender window pointer. The four
//entries are packetNumber, time of generation, time of receipt of acknowledgement, time of timeout
int sender[10][4];
int SWPToSend = 0;
int SWPToReceive = 0;

//Various times for the network
int transmitTime;
int generationTime;
int timeOut;


//This will generate packet
void generate(int genTime,int packetNo)
{
    if(packetNo<11)cout<<"Packet number "<<packetNo<<" is generated at time = "<<genTime<<endl;
    //Entering all values into sended window
    sender[SWPToSend][0] = packetNo;
    sender[SWPToSend][1] = genTime;
    sender[SWPToSend][2] = 0;
    sender[SWPToSend][3] = 0;
    
    
    //Determing if the packet will reach safely
    int randTemp = rand()%100;
    if(randTemp<numberPacketsLost)
    {
        if(packetNo<11)cout<<"This packet will be lost in transit"<<endl<<endl;
        //Setting the time out time
        sender[SWPToSend][3] = genTime+timeOut;
    }
    else
    {
        if(packetNo<11)cout<<"This packet will reach safely"<<endl<<endl;
        //Setting the time at which the acknowledgement will be received
        sender[SWPToSend][2] = genTime+2*transmitTime;
    }
    
}

void goBack()
{
    //Building the senderWindow
    for(int i = 0; i<10; i++)
    {
        for(int j = 0; j<4; j++)
        {
            sender[i][j] = 0;
        }
    }        
                
    int packetNumber = 1;
    while(true)
    {
        bool timeOutOcc = false;
        if(sender[SWPToReceive][2]<=globalTime+generationTime&&sender[SWPToReceive][2]!=0)
        {
            //Packet received is acknowledged
            cout<<"Packet Number "<<sender[SWPToReceive][0]<<" has been acknowledged at time = "<<sender[SWPToReceive][2]<<endl;
            if(sender[SWPToReceive][0]==10)break;
            SWPToReceive = (SWPToReceive+1)%10;
            
        }
        else if(sender[SWPToReceive][3]<=globalTime+generationTime&&sender[SWPToReceive][3]!=0)
        {
            //Some earlier Packet has caused timeout
            cout<<"!!!Time out in packet number "<<sender[SWPToReceive][0]<<" has occured at time = "<<sender[SWPToReceive][3]<<"!!!"<<endl;
            SWPToSend = SWPToReceive;
            packetNumber = sender[SWPToReceive][0];
            timeOutOcc = true;
        }
        
        globalTime = globalTime+generationTime;
        
        if(timeOutOcc)
        {
            globalTime = sender[SWPToReceive][3];
        }        
            
        
        if(sender[SWPToReceive][0]==0)
        {
            generate(globalTime, packetNumber);
            packetNumber++;
            SWPToSend = (SWPToSend+1)%10;
        }    
        else if(sender[(SWPToSend-1+10)%10][0]<11)
        {
            generate(globalTime, packetNumber);
            packetNumber++;
            SWPToSend = (SWPToSend+1)%10;
        }
        
    }
}        
            
int main()
{
    cout<<"Enter the times for different network parameters:"<<endl;
    cout<<"Generation Time (ms):";cin>>generationTime;
    cout<<"Transmission Time (ms):";cin>>transmitTime;               
    cout<<"TimeOut Time (ms):";cin>>timeOut;cout<<endl;
    
    cout<<"Enter The percentage efficiency:";cin>>percentageEff;
    numberPacketsLost = 100 -(int)percentageEff;

    cout<<endl<<"Running Go back N"<<endl;
    for(int i = 0; i<30;i++)cout<<"_";
    cout<<endl<<endl;
    goBack();
    
    system("pause");
    return 0;
}    
