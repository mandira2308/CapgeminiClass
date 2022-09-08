CC=g++
CPPFLAGS = -c -g -Wall
LDFLAGS = -o
IFLAGS = -I
OBJ = obj
SRC = src
BIN = bin/
INCLUDE = inc/

all: server client

server: $(OBJ)/mainserver.o $(OBJ)/server.o $(OBJ)/netstat_r.o $(OBJ)/netstat_tcp.o $(OBJ)/netstat_udp.o $(OBJ)/netstat_listen.o $(OBJ)/netstat_firefox.o
	$(CC) $(LDFLAGS) $(BIN)/server $(OBJ)/mainserver.o $(OBJ)/server.o $(OBJ)/netstat_r.o $(OBJ)/netstat_tcp.o $(OBJ)/netstat_udp.o $(OBJ)/netstat_listen.o $(OBJ)/netstat_firefox.o
$(OBJ)/mainserver.o: $(SRC)/mainserver.cpp
	$(CC) $(CPPFLAGS) $(SRC)/mainserver.cpp $(IFLAGS) $(INCLUDE)
	mv *.o $(OBJ)/
$(OBJ)/server.o : $(SRC)/server.cpp
	$(CC) $(CPPFLAGS) $(SRC)/server.cpp $(IFLAGS) $(INCLUDE)
	mv *.o $(OBJ)/
client: $(OBJ)/mainclient.o $(OBJ)/client.o $(OBJ)/netstat_r.o $(OBJ)/netstat_tcp.o $(OBJ)/netstat_udp.o $(OBJ)/netstat_listen.o $(OBJ)/netstat_firefox.o
	$(CC) $(LDFLAGS) $(BIN)/client $(OBJ)/mainclient.o $(OBJ)/client.o $(OBJ)/netstat_r.o $(OBJ)/netstat_tcp.o $(OBJ)/netstat_udp.o $(OBJ)/netstat_listen.o $(OBJ)/netstat_firefox.o
$(OBJ)/mainclient.o: $(SRC)/mainclient.cpp
	 $(CC) $(CPPFLAGS) $(SRC)/mainclient.cpp $(IFLAGS) $(INCLUDE)
	 mv *.o $(OBJ)/
$(OBJ)/client.o : $(SRC)/client.cpp
	$(CC) $(CPPFLAGS) $(SRC)/client.cpp $(IFLAGS) $(INCLUDE)
	mv *.o $(OBJ)/
$(OBJ)/netstat_r.o : $(SRC)/netstat_r.cpp
	$(CC) $(CPPFLAGS) $(SRC)/netstat_r.cpp $(IFLAGS) $(INCLUDE)
	mv *.o $(OBJ)/
$(OBJ)/netstat_tcp.o : $(SRC)/netstat_tcp.cpp
	$(CC) $(CPPFLAGS) $(SRC)/netstat_tcp.cpp $(IFLAGS) $(INCLUDE)
	mv *.o $(OBJ)/
$(OBJ)/netstat_udp.o : $(SRC)/netstat_udp.cpp
	$(CC) $(CPPFLAGS) $(SRC)/netstat_udp.cpp $(IFLAGS) $(INCLUDE)
	mv *.o $(OBJ)/
$(OBJ)/netstat_listen.o : $(SRC)/netstat_listen.cpp
	$(CC) $(CPPFLAGS) $(SRC)/netstat_listen.cpp $(IFLAGS) $(INCLUDE)
	mv *.o $(OBJ)/
$(OBJ)/netstat_firefox.o : $(SRC)/netstat_firefox.cpp
	$(CC) $(CPPFLAGS) $(SRC)/netstat_firefox.cpp $(IFLAGS) $(INCLUDE)
	mv *.o $(OBJ)/



valgrindServer : $(BIN)/server
	valgrind --leak-check=full --show-reachable=yes $(BIN)server 1>$(BIN)/valgrind_s.txt
valgrindClient : $(BIN)/client
	valgrind --leak-check=full --show-reachable=yes $(BIN)client 1>$(BIN)/valgrind_c.txt


clean:
	rm $(OBJ)/*.o
	rm firefoxFile.txt rtFile.txt tcpFile.txt udpFile.txt listen_File.txt
	rm $(BIN)/server $(BIN)/client
	rm -f $(BIN)/valgrind_s.txt
	rm -f $(BIN)/valgrind_c.txt
	@echo "cleaning done"



