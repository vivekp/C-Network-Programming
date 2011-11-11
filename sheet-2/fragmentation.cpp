//Author: P. Bharat
//Roll No: 08114022
//Branch: CSE, 4th year


#include <iostream>
#include <stdlib.h>
using namespace std;

//Pointer for data
int* data;

//The size of hardware and that of data
int MTU, sizeData;

//Class that will simulate an IP packet
class IPPacket
{
	public:
	int headerLen;
	int lenData;
	
	int* header;
	int* fragData;

	IPPacket(int choose, int offset, int moreFrag)
	{
		if(choose == 0)
		{
			headerLen = 3;
			header = new int[3];

			header[0] = moreFrag;
			header[1] = offset;
			
			if(offset+MTU<=sizeData)
			{
				lenData = MTU;
			}
			else
			{
				lenData = sizeData-offset;
			}

			header[2] = 3+lenData;
			fragData = new int[lenData];
			for(int i = 0; i < lenData; i++)
			{
				fragData[i] = data[offset+i];
			}
		}

	}

	IPPacket(int choose, int lenD, int* data)
	{
		if(choose == 0)
		{
			headerLen = 3;
			header = new int[3];

			header[0] = 0;
			header[1] = 0;
			
			lenData = lenD;
			header[2] = 3+lenData;
			
			fragData = data;
			
		}

	}
	

	
	void displayFrag()
	{
		
		cout<<"More fragments      : "<<header[0]<<endl;
		cout<<"Offset              : "<<header[1]<<endl;
		cout<<"Total Packet Length : "<<header[2]<<endl;
		cout<<"Data fragment       : ";
		for(int i = 0; i< lenData; i++)
		{
			cout<<fragData[i];
		}
		cout<<endl;

		cout<<"The final packet sent is : ";
		

		for(int i = 0; i< headerLen; i++)
		{
			cout<<header[i]<<" ";
		}
		for(int i = 0; i< lenData; i++)
		{
			cout<<fragData[i]<<" ";
		}
	}

	void displayPacket()
	{
		
		cout<<"More fragments      : "<<header[0]<<endl;
		cout<<"Offset              : "<<header[1]<<endl;
		cout<<"Total Packet Length : "<<header[2]<<endl;
		cout<<"Data       : ";
		for(int i = 0; i< lenData; i++)
		{
			cout<<fragData[i];
		}
		cout<<endl;

		cout<<"The final packet sent is : ";
		

		for(int i = 0; i< headerLen; i++)
		{
			cout<<header[i]<<" ";
		}
		for(int i = 0; i< lenData; i++)
		{
			cout<<fragData[i]<<" ";
		}
		cout<<endl;
	}


};	

int main()
{
	cout<<"Enter the MTU:";
	cin>>MTU;
	
	char* s = new char[100];
	cout<<"Enter the initial message to be sent: ";
	cin>>s; sizeData = strlen(s);

	data = new int[sizeData];
	for( int i = 0; i<sizeData; i++)
	{
		data[i] = int(s[i])-48;
	}
	
	//Print the integer array and see if it matches
	for(int i = 0; i<sizeData; i++)
	cout<<data[i];
	cout<<endl;

	//Bulding the IP packets
	int fragments;
	if(sizeData%MTU==0)
	{
		fragments = sizeData/MTU;
	}
	else
	{
		fragments = sizeData/MTU+1;
	}


	IPPacket** packets = new IPPacket*[fragments];

	for(int i = 0; i<fragments; i++)
	{
		if(i == fragments-1)
		{
			packets[i] = new IPPacket(0, MTU*i, 0);
		}
		else
		{
			packets[i] = new IPPacket(0, MTU*i, 1);
		}
	}
	

	for(int i = 0; i<fragments; i++)
	{
		cout<<"Packet number: "<<i+1<<endl;
		packets[i]->displayFrag();
		cout<<endl<<endl;
	}
	
	cout<<"Showing reassembly model\n";
	
	bool* receive = new bool[fragments];for(int i = 0; i<fragments; i++)receive[fragments] = false;
	int maxFrags = fragments;

	while(true)
	{
		int tempRand = rand()%fragments;
		cout<<"fragment received = "<<tempRand+1<<endl;
		if(tempRand == fragments-1)
		{
			
			cout<<"Max frags is set\n\n";
			receive[tempRand] = true;
		}
		else
		{
			receive[tempRand] = true;
		}
		
		bool breakCheck = true;
		for(int i = 0; i<maxFrags; i++)
		{
			if(receive[i] == false)
			{
				breakCheck = false;
			}
		}
			
		if(breakCheck)
		break;
	}
	
	IPPacket* final = new IPPacket(0, sizeData, data);
	final->displayPacket();	


    system("pause");
	return 0;
}
