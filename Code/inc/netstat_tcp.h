#include<iostream>
#include<string>
#include<fstream>
#include<list>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<fstream>
#include<sys/wait.h>
#include<sstream>
#include<cstring>
#include<cstring>
#include<sstream>
#include<vector>

using namespace std;

class netstatTCP
{
	public :
		netstatTCP();    
		void setProto(char [][20]);
		string getProto();
		void setRecv(char [][20]);
		string getRecv();
		void setSend(char [][20]);
		string getSend();
		void setLocal_Address(char [][20]);
		string getLocal_Address();
		void setForeign_Address(char [][20]);
		string getForeign_Address();
		void setState(char [][20]);
		string getState();
		~netstatTCP();

	private :
		string Proto;
		string Recv;
		string Send;
		string Local_Address;
		string Foreign_Address;
		string State;

};
void getTCP_Table();
string storeTCP_Table();
void TCPdriver(string);

