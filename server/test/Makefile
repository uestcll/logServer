main : test.o CLLogHeadTester.o CLAbnormalAndErrnoLogTester.o
	g++ -I gtest-1.4.0/include -o main test.o CLLogHeadTester.o CLAbnormalAndErrnoLogTester.o gtest-1.4.0/libgtest.a -g -lmysqlclient
	rm *.o

test.o : test.cpp
	g++ -I gtest-1.4.0/include -o test.o -c test.cpp -g
CLLogHeadTester.o : CLLogHeadTester.cpp
	g++ -I gtest-1.4.0/include -o CLLogHeadTester.o -c CLLogHeadTester.cpp -g
CLAbnormalAndErrnoLogTester.o : CLAbnormalAndErrnoLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLAbnormalAndErrnoLogTester.o -c CLAbnormalAndErrnoLogTester.cpp -g
