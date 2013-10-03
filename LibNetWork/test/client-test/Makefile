client : CLEchoClient.o startup.o
	g++ -o client CLEchoClient.o startup.o -g -pg -L ../.. -lnetwork -I../../include -g
	rm *.o

CLEchoClient.o : ./src/CLEchoClient.cpp
	g++ -o CLEchoClient.o -c ./src/CLEchoClient.cpp  -L ../.. -lnetwork -I../../include -g
startup.o : ./src/startup.cpp
	g++ -o startup.o -c ./src/startup.cpp  -L ../.. -lnetwork -I../../include -g

