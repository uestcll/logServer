client : test.o
	g++ -I ../LibNetWork/include -L ../LibNetWork -o test test.o -lnetwork -g
	rm *.o

test.o : ./test.cpp
	g++ -I ../LibNetWork/include -o test.o -c test.cpp -g
