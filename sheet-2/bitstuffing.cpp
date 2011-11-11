//Author: P. Bharat
//Roll No: 08114022
//Branch: CSE, 4th year


#include <iostream>
#include <string>
using namespace std;

//Length of the string
int len;

//Shifting the bits by one starting from index
string shift(int index, string inp)
{
	string newone = inp.substr(0,index)+"0"+inp.substr(index,1000);
	return newone;
}
	

int main()
{
	//Taking the original message as input
	char* s = new char[100];
	cout<<"Enter the message to be passed:"<<endl;
	cin>>s;
	int len = strlen(s);
		
	//Here we take those parameters to measure those indexes where stuffing is needed
	int pointer = 0;int num1 = 0;
	int* indexes = new int[10];
	string final = (string)s;

	//Calculating all indexes where insertion is needed
	for(int i = 0; i<len; i++)
	{
		if(s[i] == '1')
		{
			switch(num1){
				case 0: num1++;break;
				case 1: num1++;break;
				case 2: num1++;break;	
				case 3: num1++;break;	
				case 4: num1 = 0;
					indexes[pointer] = i+1;	
					pointer++;
					break;
			}
			
		}
		else
		{
			num1 = 0;
		}
	}

	cout<<endl<<"The original message pattern is : "<<final<<endl;
	//This will have the final message that is transmitted
	for(int i = 0; i<pointer; i++)
	{
		final = shift(indexes[i]+i, final);
	}

	cout<<"The bit stuffed pattern is      : "<<final<<endl;
	system("pause");
	return 0;
}
