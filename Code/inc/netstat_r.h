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

using namespace std;

class RoutingTable
{
	public :
		RoutingTable();
		void setDestination(char [][20]);
		string getDestination();
		void setGateway(char [][20]);
		string getGateway();
		void setGenmask(char [][20]);
		string getGenmask();
		void setFlags(char [][20]);
		string getFlags();
		void setMss(char [][20]);
		string getMss();
		void setWindow(char [][20]);
		string getWindow();
		void setirtt(char [][20]);
		string getirtt();
		void setIface(char [][20]);
		string getIface();
		~RoutingTable();

	private :
		string Destination;
		string Gateway;
		string Genmask;
		string Flags;
		string Mss;
		string Window;
		string irtt;
		string Iface;

};
void getRoutingTable();
string storeRoutingTable();
void RTdriver(string);