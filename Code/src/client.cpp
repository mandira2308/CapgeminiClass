#include<client.h>
#include<server.h>
#include<netstat_r.h>
#include<netstat_tcp.h>
#include<netstat_udp.h>
#include<netstat_listen.h>
#include<netstat_firefox.h>


Client :: Client()								//constructor call
{
}

void Client :: createSock()						//creating Socket
{
	cl<<"INFO : In Create Socket"<<endl;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if(sockfd < 0)
		{
			cl<<"ERROR : Socket didnot create."<<endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			cl<<"INFO : Socket created."<<endl;
		}
}

void Client :: connectServer()					//Connecting to server
{
	cl<<"INFO : In connectServer() function."<<endl;
	memset(&server_addr, '\0', sizeof(server_addr));

	server_addr.sin_family = AF_INET;				//Assigning the port and address to family
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr(ADDR);

	//establishing Connection with server
	client_fd = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(client_fd < 0){
		cl<<"FATAL : Error in connection."<<endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		cl<<"DEBUG : Connected to Server , PORT :"<<PORT<<" ADDRESS : "<<ADDR<<endl;
		cout<<"Connected to server."<<endl;
	}
}

void Client :: send_recv(string temp) //sending and receiving info to and from server
{

	while(1)
	{
		if(temp == "exit")
		{
			close(sockfd);
			exit(EXIT_SUCCESS);
		}
		else
		{
			if(send(sockfd, temp.c_str(), strlen(temp.c_str()),0)<0)
			{
				cl<<"ERROR :"<<"Send Command error"<<endl;
				exit(EXIT_FAILURE);
			}


		   		if(temp == "RT") //receiving from mainClient based on Command.
				{
					char buffData[SIZE];
					if(recv(sockfd, buffData, sizeof(buffData),0)<0)
					{
					
						cl<<"ERROR :"<<"Receive RT Command error"<<endl;
						exit(EXIT_FAILURE);
					}
					else
					{
						cl<<"INFO : Received Successfully RT table data"<<endl;
				  	}
					string rtData=buffData;
					RTdriver(rtData);  //passing the raw data to driverFunction
			
				}
				else if(temp == "TCP") //receiving from mainClient based on Command.
				{
					char buffData[SIZE];
					if(recv(sockfd, buffData, sizeof(buffData),0)<0)
					{
						cl<<"ERROR :"<<"Receive TCP Command error"<<endl;
						exit(EXIT_FAILURE);
					}
					else
					{
						cl<<"INFO : Received Successfully TCP table data"<<endl;
					}
					string tcpData=buffData;
					TCPdriver(tcpData); //passing the raw data to driverFunction
				}
				else if(temp == "UDP") //receiving from mainClient based on Command.
				{
					char buffData[SIZE];
					if(recv(sockfd, buffData, sizeof(buffData),0)<0)
					{
						cl<<"ERROR :"<<"Receive UDP Command error"<<endl;
						exit(EXIT_FAILURE);
					}
					else
					{
						cl<<"INFO : Received Successfully UDP table data"<<endl;
					}
					string udpData=buffData;
					UDPdriver(udpData); //passing the raw data to driverFunction
					
				}
				else if(temp == "Listen") //receiving from mainClient based on Command.
				{
					char buffData[SIZE];
					if(recv(sockfd, buffData, sizeof(buffData),0)<0)
					{
						cl<<"ERROR :"<<"Receive TCP Connections with state LISTEN Command error"<<endl;
						exit(EXIT_FAILURE); 
					}
					else
					{
						cl<<"INFO : Received Successfully TCP Connections with state LISTEN table data"<<endl;
					}
					string listenData=buffData;
					listendriver(listenData); //passing the raw data to driverFunction
					}
				else if (temp == "Firefox") //receiving from mainClient based on Command.
				{
					char buffData[SIZE*3];
					if(recv(sockfd, buffData, sizeof(buffData),0)<0)
					{
						cl<<"ERROR :"<<"Receive TCP Connections with application Firefox Command error"<<endl;
						exit(EXIT_FAILURE);
					}
					else
					{
						cl<<"INFO : Received Successfully TCP Connections with application Firefox table data"<<endl;
					}
					string firefoxData=buffData;

					if(firefoxData=="NA")
					{
						cout<<"No such Application Running"<<endl;
						exit(EXIT_SUCCESS);
					}
					else
					{
						firefoxdriver(buffData); //passing the raw data to driverFunction
					}
					
							
				}
			}

	}	
	
}

void Client :: closeSock()
{
	close(sockfd);
	cl<<"INFO : Closing client Socket"<<endl;
}

Client :: ~Client()
{

}