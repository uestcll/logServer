server : CLEchoServer.o startup.o
	g++ -o server CLEchoServer.o startup.o -g -pg -L ../.. -lnetwork -I../../include -g
	rm *.o

CLEchoServer.o : ./src/CLEchoServer.cpp
	g++ -o CLEchoServer.o -c ./src/CLEchoServer.cpp  -L ../.. -lnetwork -I../../include -g
startup.o : ./src/startup.cpp
	g++ -o startup.o -c ./src/startup.cpp  -L ../.. -lnetwork -I../../include -g

