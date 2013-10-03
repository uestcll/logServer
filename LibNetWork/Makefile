libnetwork.a : CLSocket.o CLAgent.o CLBuffer.o CLAgentManager.o CLEpollEvent.o CLEpoll.o CLListenAgent.o CLCommunication.o CLProcessRequest.o 
	ar -rc libnetwork.a CLSocket.o CLAgent.o CLBuffer.o CLAgentManager.o CLEpollEvent.o CLEpoll.o CLListenAgent.o CLCommunication.o CLProcessRequest.o
	rm *.o

CLSocket.o : ./src/CLSocket.cpp
	g++ -o CLSocket.o -c ./src/CLSocket.cpp -I./include -g
CLAgent.o : ./src/CLAgent.cpp
	g++ -o CLAgent.o -c ./src/CLAgent.cpp -I./include -g
CLBuffer.o : ./src/CLBuffer.cpp
	g++ -o CLBuffer.o -c ./src/CLBuffer.cpp -I./include -g
CLAgentManager.o : ./src/CLAgentManager.cpp
	g++ -o CLAgentManager.o -c ./src/CLAgentManager.cpp -I./include -g
CLEpollEvent.o : ./src/CLEpollEvent.cpp
	g++ -o CLEpollEvent.o -c ./src/CLEpollEvent.cpp -I./include -g
CLEpoll.o : ./src/CLEpoll.cpp
	g++ -o CLEpoll.o -c ./src/CLEpoll.cpp -I./include -g
CLListenAgent.o : ./include/CLListenAgent.h
	g++ -o CLListenAgent.o -c ./include/CLListenAgent.h -I./include -g
CLCommunication.o : ./src/CLCommunication.cpp
	g++ -o CLCommunication.o -c ./src/CLCommunication.cpp -I./include -g
CLProcessRequest.o : ./src/CLProcessRequest.cpp
	g++ -o CLProcessRequest.o -c ./src/CLProcessRequest.cpp -I./include -g
