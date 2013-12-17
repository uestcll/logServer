server : CLLoggerProcess.o CLPraseManager.o CLSQL.o startup.o
	g++ -I ../LibNetWork/include -L ../LibNetWork -o server CLLoggerProcess.o CLPraseManager.o CLSQL.o startup.o -lnetwork -g -lmysqlclient
	rm *.o

CLLoggerProcess.o : ./src/CLLoggerProcess.cpp
	g++ -I ./include -I ../LibNetWork/include -o CLLoggerProcess.o -c ./src/CLLoggerProcess.cpp -g -DSERVER
CLPraseManager.o : ./src/CLPraseManager.cpp
	g++ -I ./include -o CLPraseManager.o -c ./src/CLPraseManager.cpp -g -DSERVER
CLSQL.o : ./src/CLSQL.cpp 
	g++ -I ./include -o CLSQL.o -c ./src/CLSQL.cpp -g -DSERVER
startup.o : ./src/startup.cpp
	g++ -I ./include -I ../LibNetWork/include -o startup.o -c ./src/startup.cpp -g -DSERVER
