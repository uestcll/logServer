test : test.o CLSQL.o CLAbnormalAndErrnoLogTester.o CLAdministratorAuthorityManagerLogTester.o CLAdministratorLoginLogTester.o CLAllSubordinateAccountAuthorityManagerLogTester.o CLChangeNodeCapacityLogTester.o CLChangeNodeDiskLogTester.o CLDiskForDepartmentLogTester.o CLDiskForUserLogTester.o CLModifyDepartmentNameLogTester.o CLModifyDiskAccessAuthorityLogTester.o CLModifyNameLogTester.o
	g++ -I gtest-1.4.0/include -o test test.o CLSQL.o CLAbnormalAndErrnoLogTester.o CLAdministratorAuthorityManagerLogTester.o CLAdministratorLoginLogTester.o CLAllSubordinateAccountAuthorityManagerLogTester.o CLChangeNodeCapacityLogTester.o CLChangeNodeDiskLogTester.o CLDiskForDepartmentLogTester.o CLDiskForUserLogTester.o CLModifyDepartmentNameLogTester.o CLModifyDiskAccessAuthorityLogTester.o CLModifyNameLogTester.o gtest-1.4.0/libgtest.a -g -lmysqlclient

CLSQL.o : ../server/src/CLSQL.cpp
	g++ -o CLSQL.o -c ../server/src/CLSQL.cpp -g
test.o : test.cpp
	g++ -I gtest-1.4.0/include -o test.o -c test.cpp -g
CLAbnormalAndErrnoLogTester.o : CLAbnormalAndErrnoLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLAbnormalAndErrnoLogTester.o -c CLAbnormalAndErrnoLogTester.cpp -g -DSERVER
CLAdministratorAuthorityManagerLogTester.o : CLAdministratorAuthorityManagerLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLAdministratorAuthorityManagerLogTester.o -c CLAdministratorAuthorityManagerLogTester.cpp -g -DSERVER
CLAdministratorLoginLogTester.o : CLAdministratorLoginLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLAdministratorLoginLogTester.o -c CLAdministratorLoginLogTester.cpp -g -DSERVER
CLAllSubordinateAccountAuthorityManagerLogTester.o : CLAllSubordinateAccountAuthorityManagerLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLAllSubordinateAccountAuthorityManagerLogTester.o -c CLAllSubordinateAccountAuthorityManagerLogTester.cpp -g -DSERVER
CLChangeNodeCapacityLogTester.o : CLChangeNodeCapacityLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLChangeNodeCapacityLogTester.o -c CLChangeNodeCapacityLogTester.cpp -g -DSERVER
CLChangeNodeDiskLogTester.o : CLChangeNodeDiskLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLChangeNodeDiskLogTester.o -c CLChangeNodeDiskLogTester.cpp -g -DSERVER
CLDiskForDepartmentLogTester.o : CLDiskForDepartmentLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLDiskForDepartmentLogTester.o -c CLDiskForDepartmentLogTester.cpp -g -DSERVER
CLDiskForUserLogTester.o : CLDiskForUserLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLDiskForUserLogTester.o -c CLDiskForUserLogTester.cpp -g -DSERVER
CLModifyDepartmentNameLogTester.o : CLModifyDepartmentNameLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLModifyDepartmentNameLogTester.o -c CLModifyDepartmentNameLogTester.cpp -g -DSERVER
CLModifyDiskAccessAuthorityLogTester.o : CLModifyDiskAccessAuthorityLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLModifyDiskAccessAuthorityLogTester.o -c CLModifyDiskAccessAuthorityLogTester.cpp -g -DSERVER
CLModifyNameLogTester.o : CLModifyNameLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLModifyNameLogTester.o -c CLModifyNameLogTester.cpp -g -DSERVER
