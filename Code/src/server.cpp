#include<server.h>
#include<netstat_r.h>
#include<netstat_tcp.h>
#include<netstat_udp.h>
#include<netstat_listen.h>
#include<netstat_firefox.h>

Server :: Server()
{

}
void Server :: createSock() //creation of socket
{

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		sl<<"FATAL:Socket not created"<<endl;
		exit(EXIT_FAILURE);
	}
	cout<<"Server Running...."<<endl;
	sl<<"INFO :Server Socket is created successfully" <<endl;
}

void Server :: bindClient() //func to bind with the client
{
	memset(&server_addr, '\0', sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr(ADDR);

	sl<<"DEBUG : Connected to Address"<<ADDR<<"and Port "<<PORT<<endl;

	int ret =bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(ret < 0)
	{
		sl<<"ERROR : Error in binding."<<endl;
		exit(EXIT_FAILURE);
	}
	sl<<"INFO : Binded to port :"<<PORT<<endl;
}

void Server :: listenClient()  //listening to the client
{
	if(listen(sockfd, 5) == 0)
	{
		sl<<"INFO : Listening to clients "<<endl;
	}
	else
	{
		sl<<"ERROR : Error in Listening"<<endl;
	}

}

void Server :: send_recv()
{
	int count =0;
	while(1)
	{	
		count++;
		//accpting the client and establishing connection.
		newsockfd = accept(sockfd, (struct sockaddr*)&client_addr,(socklen_t*)&client_addr_len);
		if(newsockfd < 0)
		{
			sl<<"ERROR :Could not Connect"<<endl;
			exit(EXIT_FAILURE);
		}
		sl<<"INFO : Connected successfully"<<endl;
		sl<<"Connection accepted from "<<count<<" client"<<endl;

		if(fork() == 0)  //Child process for accepting multiclients.
		{
				close(sockfd);
				char buffer[30]; //buffer to receive client data;

				if(recv(newsockfd,buffer,sizeof(buffer),0)<0)
				{
					sl<<"ERROR :recv() error"<<endl;
					exit(EXIT_FAILURE);
				}
				else
				{
					sl<<"INFO : Received Data Successfully"<<endl;
				}

				if(strcmp(buffer,"RT")==0)  //Comparing client data with the commands
				{
					cout<<"Client:"<<buffer<<endl;
					string data=storeRoutingTable(); //storing the appended rawData in string

					char buffData[SIZE];
					strcpy(buffData,data.c_str()); //copying to a buffer.
					if(send(newsockfd, buffData, sizeof(buffData),0)<0)
					{
						sl<<"ERROR: RT send() error"<<endl;
						exit(EXIT_FAILURE);
					}
					else
					{
						sl<<"INFO : RT output sent"<<endl;
					}
				}
				else if(strcmp(buffer,"TCP")==0) //storing the appended rawData in string
				{
					cout<<"Client:"<<buffer<<endl;
					string data=storeTCP_Table();

					char buffData[SIZE];
					strcpy(buffData,data.c_str()); //copyning to a buffer
					if(send(newsockfd, buffData, sizeof(buffData), 0)<0)
					{
						sl<<"ERROR: TCP send() error"<<endl;
						exit(EXIT_FAILURE);
					}
					else
					{
						sl<<"INFO : TCP output sent"<<endl;
					}
				}
				else if(strcmp(buffer,"UDP")==0)
				{
					cout<<"Client:"<<buffer<<endl;
					string data=storeUDP_Table(); //storing appended rawData in a string

					char buffData[SIZE];
					strcpy(buffData,data.c_str()); //copyning to a buffer
					if(send(newsockfd, buffData, sizeof(buffData), 0)<0)
					{
						sl<<"ERROR: UDP send() error"<<endl;
						exit(EXIT_FAILURE);
					}
					else
					{
						sl<<"INFO : UDP output sent"<<endl;
					}
					
				}
				else if(strcmp(buffer,"Listen")==0)
				{
					cout<<"Client:"<<buffer<<endl;
					string data=storeListen(); //storing rawData in string

					char buffData[SIZE]; //copying to a buffer
					strcpy(buffData,data.c_str());
					if(send(newsockfd, buffData, sizeof(buffData), 0)<0)
					{
						sl<<"ERROR: Listen send() error"<<endl;
						exit(EXIT_FAILURE);
					}
					else
					{
						sl<<"INFO : Listen output sent"<<endl;
					}


				}
				else if (strcmp(buffer,"Firefox")==0)
				{
					cout<<"Client:"<<buffer<<endl;
					string data=storeFIREFOX_Table(); //storing rawData in a string
					char buffData[SIZE*3];

					if(data.empty())
					{
						strcpy(buffData,"NA");
					}
					else
					{
						strcpy(buffData,data.c_str()); //copying to a buffer.
					}
					if(send(newsockfd, buffData, sizeof(buffData),0)<0)
					{
						sl<<"ERROR: firefox send() error"<<endl;
						exit(EXIT_FAILURE);
					}
					else
					{
						sl<<"INFO : firefox output sent"<<endl;
					}
					
				}
			
		}

	}

}

void Server :: closeSock()
{
	close(newsockfd);
}

Server :: ~Server()
{

}