test : test.o CLAbnormalAndErrnoLogTester.o CLSQL.o
	g++ -I gtest-1.4.0/include -o test test.o CLAbnormalAndErrnoLogTester.o CLSQL.o gtest-1.4.0/libgtest.a -g -lmysqlclient
	rm *.o

CLSQL.o : ../server/src/CLSQL.cpp
	g++ -o CLSQL.o -c ../server/src/CLSQL.cpp -g
test.o : test.cpp
	g++ -I gtest-1.4.0/include -o test.o -c test.cpp -g
CLAbnormalAndErrnoLogTester.o : CLAbnormalAndErrnoLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLAbnormalAndErrnoLogTester.o -c CLAbnormalAndErrnoLogTester.cpp -g
