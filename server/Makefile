server : CLLoggerProcess.o CLPraseContent.o CLPraseManager.o CLPraseUserAccessDiskLog.o CLSQL.o startup.o
   g++ -o server CLLoggerProcess.o CLPraseContent.o CLPraseManager.o CLPraseUserAccessDiskLog.o CLSQL.o startup.o -g -pg
   rm *.o

CLLoggerProcess.o : ./src/CLLoggerProcess.cpp
	g++ -o CLLoggerProcess.o -c ./src/CLLoggerProcess.cpp -I./include -g
CLPraseContent.o : ./src/CLPraseContent.cpp
	g++ -o CLPraseContent.o -c ./src/CLPraseContent.cpp -I./include -g
CLPraseManager.o : ./src/CLPraseManager.cpp
	g++ -o CLPraseManager.o -c ./src/CLPraseManager.cpp -I./include -g
CLPraseUserAccessDiskLog.o : ./src/CLPraseUserAccessDiskLog.cpp
	g++ -o CLPraseUserAccessDiskLog.o -c ./src/CLPraseUserAccessDiskLog.cpp -I./include -g
CLSQL.o : ./src/CLSQL.cpp
	g++ -o CLSQL.o -c ./src/CLSQL.cpp -I./include -g
startup.o : ./src/startup.cpp
	g++ -o startup.o -c ./src/startup.cpp -I./include -g
