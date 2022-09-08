#include<server.h>
#include<netstat_r.h>
#include<netstat_tcp.h>
#include<netstat_udp.h>
#include<netstat_listen.h>
#include<netstat_firefox.h>

int main()
{
	Server s;
	s.createSock();
	s.bindClient();
	s.listenClient();
	s.send_recv();
	s.closeSock();
	sl.close();
}