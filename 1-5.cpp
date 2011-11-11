#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<math.h>
using namespace std;

string add(string, string);
int char_to_binary(char);
char binary_to_char(int);
string hex_to_binary(int);
int binary_to_hex(string);
string compliment(string);

int main(){
	// Get hex IP
	int ip_header[40];
	cout<<"Input IP header: \n";
	for(int i=0;i<40;i++){
		cin>>hex>>ip_header[i];
	}

	cout<<"Hex IP:\n";
	for(int i=0;i<40;i++){
		cout<<hex<<ip_header[i];
	}
	cout<<endl;
	// Got hex IP

	// Get binary IP
	cout<<"Binary IP:\n";
	string binary = "";
	for(int i=0;i<40;i++){
		binary.append(hex_to_binary(ip_header[i]));
	}
	cout<<binary<<endl;
	// Got binary IP

	// Calculate checksum
	string checksum(16, '0');
	for(int i=0;i<10;i++){
		checksum = add(checksum, binary.substr(i*16, 16));
	}
	checksum = compliment(checksum);
	cout<<"Checksum: "<<checksum<<endl;

	// Print as hex
	cout<<"Hex: ";
	for(int i=0;i<16;i+=4){
		cout<<hex<<binary_to_hex(checksum.substr(i, 4));
	}
	cout<<endl;
}

string add(string a, string b){
	a.insert(0, 16-a.size(), '0');
	b.insert(0, 16-b.size(), '0');
	string ret(16, '0');;
	int carry = 0;
	int sum = 0;
	for(int i=15;i>=0;i--){
		int ai = char_to_binary(a[i]);
		int bi = char_to_binary(b[i]);
		sum = ai + bi + carry;
		if(sum == 3){
			sum = 1;
			carry = 1;
		}
		else if(sum == 2){
			sum = 0;
			carry = 1;
		}
		else if(sum == 1){
			sum = 1;
			carry = 0;
		}
		else if(sum == 0){
			sum = 0;
			carry = 0;
		}
		else{
			cout<<"Unknown error while addition\n";
			exit(0);
		}
		ret[i] = binary_to_char(sum);
	}
	if(carry == 1){
		string c = "";
		c.push_back(binary_to_char(carry));
		ret = add(ret, c);
	}
	else if (carry != 0){
		cout<<"Unknown error in add\n";
		exit(0);
	}
	cout<<"16-bit sum: "<<ret<<" Hex: "<<binary_to_hex(ret)<<endl;
	return ret;
}

int char_to_binary(char c){
	if(c == '0') return 0;
	else if(c == '1') return 1;
	cout<<"Invalid argument to char_to_binary\n";
	exit(0);
}

char binary_to_char(int b){
	if(b == 0) return '0';
	else if(b == 1) return '1';
	cout<<"Invalid argument to binary_to_char\n";
	exit(0);
}

string hex_to_binary(int n){
	string ret(4, '0');
	for(int i=3;i>=0;i--){
		int rem = n%2;
		n = n/2;
		if(rem != 0) ret[i] = '1';
	}
	return ret;
}

int binary_to_hex(string s){
	int ret = 0;
	int s_size = s.size();
	for(int i=0;i<s_size;i++){
		int b = char_to_binary(s[i]);
		ret += b*pow(2, s_size - 1 - i);
	}
	return ret;
}

string compliment(string s){
	string ret(s.size(), '0');
	for(int i=0;i<s.size();i++){
		if(s[i] == '0') ret[i] = '1';
	}
	return ret;
}
