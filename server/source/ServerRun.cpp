#include<CommonConfig.h>
#include<frsdk.h>

#define _LIYANG_DEBUG_ printf("[%s][%s](%d): \n", __FILE__, __FUNCTION__, __LINE__);


int AddRandPerson(int hdev, fr_person_t &person, int personId,int face_cnt) {
	memset(&person, 0, sizeof(person));
	person.person_id = personId;
	person.face_cnt = face_cnt;
	for (int i = 0; i < person.face_cnt; ++i) {
		person.faces[i].face_id = i + 1;
		person.faces[i].version = 1;
		for (int j = 0; j < FACE_FEATURE_LEN; ++j) {
			person.faces[i].features[j] = rand() / (double)(RAND_MAX);//Ëæ»úÌØÕ÷Öµ
		}
	}
	int result = FR_AddPerson(hdev, &person);
	if (result != 0) {
		printf("FR_AddPerson=%s\n", FR_Errmsg(result));
		return -1;
	}else {
		printf("<FR_AddPerson>,[success]\n");
	}
	return 0;
}

int FrSDKTest() {
	int result = FR_Init();
	printf("FR_Init=%s\n", FR_Errmsg(result));

	while (true) {
		int dev_cnt = MAXNUM_DEVICE_CONNECT;
		fr_device_t devs[MAXNUM_DEVICE_CONNECT];
		result = FR_GetDeviceList(devs, &dev_cnt);
		if (result <= 0) {
			cout << "no device connect" << endl;;
			continue;
		}
		for (int i = 0; i < dev_cnt; i++) {
			printf("<FR_GetDeviceList>[Device=%d], [hdev=%d ,ip=%s ,uuid=%s]\n", i, devs[i].hdev, devs[i].ip, devs[i].uuid);

			fr_version_t version;
			result = FR_GetVersion(devs[i].hdev, &version);
			if (result != 0) {
				printf("FR_GetVersion=%s\n", FR_Errmsg(result));
			}else {
				printf("<FR_GetVersion>[Device=%d], [major=%d,minor=%d,revision=%s]\n", i, version.major, version.minor, version.revision);
			}
			int size = 0;
			result = FR_GetDBSize(devs[i].hdev, &size);
			if (result != 0) {
				printf("FR_GetDBSize=%s\n", FR_Errmsg(result));
			}
			else {
				printf("<FR_GetDBSize>[Device=%d],[DBsize=%d]\n", i, size);
			}

			result = FR_ResetDB(devs[i].hdev);
			if (result != 0) {
				printf("FR_ResetDB=%s\n", FR_Errmsg(result));
			}
			else {
				printf("<FR_ResetDB>[Device=%d],[success]\n", i);
			}
			fr_person_t personA, personB;
			AddRandPerson(devs[i].hdev, personA, rand(), 5);
			AddRandPerson(devs[i].hdev, personB, rand(), 5);


			unsigned int* person_ids = NULL;
			int person_cnt;
			result = FR_GetPersonList(devs[i].hdev, &person_ids, &person_cnt);
			if (result != 0) {
				printf("FR_GetPersonList=%s\n", FR_Errmsg(result));
			}
			else {
				printf("<FR_GetPersonList>[Device=%d],[success]\n", i);
				for (int z = 0; z < person_cnt; ++z) {
					printf("\t[PersonId=%d]\n", person_ids[z]);
				}
				FR_FreePersonList(person_ids);
			}

			result = FR_DelPerson(devs[i].hdev, &personA);
			if (result != 0) {
				printf("FR_DelPerson=%s\n", FR_Errmsg(result));
				continue;
			}
			else {
				printf("<FR_DelPerson>[Device=%d],[success]\n", i);
			}

		}


#ifdef _WIN32
		Sleep(1000);
#else
		sleep(1);
#endif
	}

	FR_Cleanup();
	return 0;
}

int main(int argc, char **argv) {
	printf("Start RS_ServerTest!!!\n");
	
	FrSDKTest();
	return 0;
}