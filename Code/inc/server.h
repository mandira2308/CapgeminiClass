#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include<fstream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444
#define ADDR "127.0.0.1"
#define SIZE 4096
using namespace std;

static fstream sl("./bin/serverLog.txt",ios::in|ios::out|ios::trunc); //creating global Logfile

class Server
{
	private:
		int sockfd;
		int newsockfd;
		struct sockaddr_in server_addr;
		struct sockaddr_in client_addr;
		int server_addr_len = sizeof(server_addr);
		int client_addr_len = sizeof(client_addr);

	public:
		Server();
		void createSock();
		void bindClient();
		void listenClient();
		void send_recv();
		void closeSock();
		~Server();
};
