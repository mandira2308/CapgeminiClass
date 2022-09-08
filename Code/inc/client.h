#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include<fstream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE 4096
#define PORT 4444
#define ADDR "127.0.0.1"
using namespace std;

static fstream cl("./bin/clientLog.txt",ios::in|ios::out|ios::trunc); //creating global Logfile

class Client
{
	private:
		int sockfd;
		int client_fd;
		struct sockaddr_in server_addr;
		struct sockaddr_in client_addr;
		int server_addr_len = sizeof(server_addr);
		int client_addr_len = sizeof(client_addr);

	public:
		Client();
		void createSock();
		void connectServer();
		void send_recv(string);
		void closeSock();
		~Client();
};