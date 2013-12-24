test : test.o CLSQL.o CLAbnormalAndErrnoLogTester.o CLAdministratorAuthorityManagerLogTester.o CLAdministratorLoginLogTester.o CLAllSubordinateAccountAuthorityManagerLogTester.o CLChangeNodeCapacityLogTester.o CLChangeNodeDiskLogTester.o CLDiskForDepartmentLogTester.o CLDiskForUserLogTester.o CLModifyDepartmentNameLogTester.o CLModifyDiskAccessAuthorityLogTester.o CLModifyNameLogTester.o CLModifyPasswordLogTester.o CLModifyShareDiskCapacityLogTester.o CLModifySubordinateAdministratorNameLogTester.o CLModifySubordinateDepartmentCapacityLogTester.o CLModifyUserDiskCapacityLogTester.o CLModifyUserNameLogTester.o CLNodeLogTester.o CLOperationAndMaintenancePersonLogTester.o CLOtherTypeLogTester.o CLRebootLogTester.o CLServerStatusLogTester.o CLServerUpdatePublicKeyLogTester.o CLSubordinateAccountLogTester.o CLSubordinateAdministratorLogTester.o CLSubordinateDepartmentAccountLogTester.o CLUserAccessDiskLogTester.o CLUserLoginLogTester.o
	g++ -I gtest-1.4.0/include -o test test.o CLSQL.o CLAbnormalAndErrnoLogTester.o CLAdministratorAuthorityManagerLogTester.o CLAdministratorLoginLogTester.o CLAllSubordinateAccountAuthorityManagerLogTester.o CLChangeNodeCapacityLogTester.o CLChangeNodeDiskLogTester.o CLDiskForDepartmentLogTester.o CLDiskForUserLogTester.o CLModifyDepartmentNameLogTester.o CLModifyDiskAccessAuthorityLogTester.o CLModifyNameLogTester.o CLModifyPasswordLogTester.o CLModifyShareDiskCapacityLogTester.o CLModifySubordinateAdministratorNameLogTester.o CLModifySubordinateDepartmentCapacityLogTester.o CLModifyUserDiskCapacityLogTester.o CLModifyUserNameLogTester.o CLNodeLogTester.o CLOperationAndMaintenancePersonLogTester.o CLOtherTypeLogTester.o CLRebootLogTester.o CLServerStatusLogTester.o CLServerUpdatePublicKeyLogTester.o CLSubordinateAccountLogTester.o CLSubordinateAdministratorLogTester.o CLSubordinateDepartmentAccountLogTester.o CLUserAccessDiskLogTester.o CLUserLoginLogTester.o gtest-1.4.0/libgtest.a -g -lmysqlclient
	rm *.o

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
CLModifyPasswordLogTester.o : CLModifyPasswordLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLModifyPasswordLogTester.o -c CLModifyPasswordLogTester.cpp -g -DSERVER
CLModifyShareDiskCapacityLogTester.o : CLModifyShareDiskCapacityLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLModifyShareDiskCapacityLogTester.o -c CLModifyShareDiskCapacityLogTester.cpp -g -DSERVER
CLModifySubordinateAdministratorNameLogTester.o : CLModifySubordinateAdministratorNameLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLModifySubordinateAdministratorNameLogTester.o -c CLModifySubordinateAdministratorNameLogTester.cpp -g -DSERVER
CLModifySubordinateDepartmentCapacityLogTester.o : CLModifySubordinateDepartmentCapacityLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLModifySubordinateDepartmentCapacityLogTester.o -c CLModifySubordinateDepartmentCapacityLogTester.cpp -g -DSERVER
CLModifyUserDiskCapacityLogTester.o : CLModifyUserDiskCapacityLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLModifyUserDiskCapacityLogTester.o -c CLModifyUserDiskCapacityLogTester.cpp -g -DSERVER
CLModifyUserNameLogTester.o : CLModifyUserNameLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLModifyUserNameLogTester.o -c CLModifyUserNameLogTester.cpp -g -DSERVER
CLNodeLogTester.o : CLNodeLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLNodeLogTester.o -c CLNodeLogTester.cpp -g -DSERVER
CLOperationAndMaintenancePersonLogTester.o : CLOperationAndMaintenancePersonLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLOperationAndMaintenancePersonLogTester.o -c CLOperationAndMaintenancePersonLogTester.cpp -g -DSERVER
CLOtherTypeLogTester.o : CLOtherTypeLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLOtherTypeLogTester.o -c CLOtherTypeLogTester.cpp -g -DSERVER
CLRebootLogTester.o : CLRebootLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLRebootLogTester.o -c CLRebootLogTester.cpp -g -DSERVER
CLServerStatusLogTester.o : CLServerStatusLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLServerStatusLogTester.o -c CLServerStatusLogTester.cpp -g -DSERVER
CLServerUpdatePublicKeyLogTester.o : CLServerUpdatePublicKeyLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLServerUpdatePublicKeyLogTester.o -c CLServerUpdatePublicKeyLogTester.cpp -g -DSERVER
CLSubordinateAccountLogTester.o : CLSubordinateAccountLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLSubordinateAccountLogTester.o -c CLSubordinateAccountLogTester.cpp -g -DSERVER
CLSubordinateAdministratorLogTester.o : CLSubordinateAdministratorLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLSubordinateAdministratorLogTester.o -c CLSubordinateAdministratorLogTester.cpp -g -DSERVER
CLSubordinateDepartmentAccountLogTester.o : CLSubordinateDepartmentAccountLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLSubordinateDepartmentAccountLogTester.o -c CLSubordinateDepartmentAccountLogTester.cpp -g -DSERVER
CLUserAccessDiskLogTester.o : CLUserAccessDiskLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLUserAccessDiskLogTester.o -c CLUserAccessDiskLogTester.cpp -g -DSERVER
CLUserLoginLogTester.o : CLUserLoginLogTester.cpp
	g++ -I gtest-1.4.0/include -o CLUserLoginLogTester.o -c CLUserLoginLogTester.cpp -g -DSERVER
