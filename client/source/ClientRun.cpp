#include<CommonConfig.h>
#include<rsNet_api.h>

#define _LIYANG_DEBUG_ printf("[%s][%s](%d): \n", __FILE__, __FUNCTION__, __LINE__);

int main(int argc, char **argv) {
	printf("Start RS_ClientTest!!!\n");
	string svrIp, dbPath;
	int svrPort = 0;
	if (argc <= 1) {
		svrIp = "127.0.0.1";
		svrPort = 7777;
		dbPath = "./rsface.db";
	}else {
		svrIp = argv[1];
		svrPort = atoi(argv[2]);
		dbPath = argv[3];
	}
	int result = RS_FeatureSync_Init(svrIp.c_str(), svrPort, dbPath.c_str());
	if (result == 0) {
		printf("Start Client Success!!!\n");
	}
	while (true){
#ifdef _WIN32
		Sleep(1000);
#else
		sleep(1);
#endif
	}
	return 0;
}