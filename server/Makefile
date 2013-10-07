server : CLLoggerProcess.o CLPraseManager.o CLSQL.o startup.o
	g++ -o server CLLoggerProcess.o CLPraseManager.o CLSQL.o startup.o -L ../LibNetWork -lnetwork -I../LibNetWork/include -g -pg -lmysqlclient
	rm *.o

CLLoggerProcess.o : ./src/CLLoggerProcess.cpp
	g++ -o CLLoggerProcess.o -c ./src/CLLoggerProcess.cpp -I./include -L ../LibNetWork -lnetwork -I../LibNetWork/include -g
CLPraseManager.o : ./src/CLPraseManager.cpp
	g++ -o CLPraseManager.o -c ./src/CLPraseManager.cpp -I./include -g
CLSQL.o : ./src/CLSQL.cpp
	g++ -o CLSQL.o -c ./src/CLSQL.cpp -I./include -g -lmysqlclient
startup.o : ./src/startup.cpp
	g++ -o startup.o -c ./src/startup.cpp -I./include -L ../LibNetWork -lnetwork -I../LibNetWork/include -g
