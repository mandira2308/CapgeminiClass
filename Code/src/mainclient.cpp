#include<client.h>
#include<netstat_r.h>
#include<netstat_tcp.h>
#include<netstat_udp.h>
#include<netstat_listen.h>
#include<netstat_firefox.h>


int main()
{
	
	Client c;	//creating client class object
	c.createSock();			//calling different functions.
	c.connectServer(); 
	cout<<"\n";				//menu driven 
	cout<<"------------WELCOME To PortScanner Implementation using Netstat-----------"<<endl;
	cout<<"\n";
	cout<<"\t\tFollowing are the commands given :"<<endl;
	cout<<"\t\tEnter 1 for netstat -r"<<endl;
	cout<<"\t\tEnter 2 for netstat -tan"<<endl;
	cout<<"\t\tEnter 3 for netstat -uan"<<endl;
	cout<<"\t\tEnter 4 for netstat -tanp | grep -i LISTEN"<<endl;
	cout<<"\t\tEnter 5 for netstat -tanp | grep -i firefox"<<endl;
	cout<<"\t\tEnter 6 to exit code"<<endl;
	cout<<"\n";
	cout<<"---------------------------------------------------------------------------"<<endl;
	cout<<"Enter your choice :";
	int choice;
	cin>>choice;
	string temp;

	switch(choice) //switching on the input 
	{
		case 1:
			temp="RT";
			c.send_recv(temp);
			c.closeSock();	
			break;
		case 2:
			temp="TCP";
			c.send_recv(temp);
			c.closeSock();
			break;
		case 3:
			temp="UDP";
			c.send_recv(temp);
			c.closeSock();
			break;
		case 4:
			temp="Listen";
			c.send_recv(temp);
			c.closeSock();
			break;
		case 5:
			temp="Firefox";
			c.send_recv(temp);
			c.closeSock();
			break;
		case 6:
			temp="exit";
			exit(EXIT_SUCCESS);
			break;
		default:
			cout<<"Invalid Choice"<<endl;
			exit(EXIT_FAILURE);

	}
	cl.close(); //closing global logFile
}

