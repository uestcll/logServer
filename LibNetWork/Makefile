libnetwork.a : CLSocket.o CLAgent.o CLBuffer.o CLAgentManager.o CLEpoll.o CLListenAgent.o CLRelayAgent.o 
	ar -rc libnetwork.a CLSocket.o CLAgent.o CLBuffer.o CLAgentManager.o CLEpoll.o CLListenAgent.o CLRelayAgent.o
	rm *.o

CLSocket.o : ./src/CLSocket.cpp
	g++ -o CLSocket.o -c ./src/CLSocket.cpp -I./include -g
CLAgent.o : ./src/CLAgent.cpp
	g++ -o CLAgent.o -c ./src/CLAgent.cpp -I./include -g
CLBuffer.o : ./src/CLBuffer.cpp
	g++ -o CLBuffer.o -c ./src/CLBuffer.cpp -I./include -g
CLAgentManager.o : ./src/CLAgentManager.cpp
	g++ -o CLAgentManager.o -c ./src/CLAgentManager.cpp -I./include -g
CLEpoll.o : ./src/CLEpoll.cpp
	g++ -o CLEpoll.o -c ./src/CLEpoll.cpp -I./include -g
CLListenAgent.o : ./src/CLListenAgent.cpp
	g++ -o CLListenAgent.o -c ./src/CLListenAgent.cpp -I./include -g
CLRelayAgent.o : ./src/CLRelayAgent.cpp
	g++ -o CLRelayAgent.o -c ./src/CLRelayAgent.cpp -I./include -g
