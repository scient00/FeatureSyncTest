#ifndef FR_SDK_H
#define FR_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
    #if defined(FRSDK_BUILD_STATIC)
        #define FR_API
    #elif defined(FRSDK_BUILD_SHARED)
        #define FR_API __declspec(dllexport)
    #else
        #define FR_API __declspec(dllimport)
    #endif  
#elif __GNUC__ >= 4
    #define FR_API __attribute__((visibility("default")))
#else
    #define FR_API
#endif

#ifdef __GNUC__
    #define GCC_ALIGN(n)   __attribute__((aligned(n))) 
#else
    #define GCC_ALIGN(n)
#endif

#define MAXNUM_DEVICE_CONNECT   256
#define PERSON_MAXNUM_FACE      10
#define FACE_FEATURE_LEN        512

/*------------------------struct definition----------------------------------------*/
#ifdef _WIN32
#pragma pack(4)
#endif

typedef struct fr_device_s {
    int  hdev;
    char ip[32];
    char uuid[64];
} GCC_ALIGN(4) fr_device_t;

typedef struct fr_version_s {
	int major;
	int minor;
	char revision[40];
} GCC_ALIGN(4) fr_version_t;

typedef struct fr_face_s {
	unsigned int face_id;
	unsigned int version;
	float features[FACE_FEATURE_LEN];
} GCC_ALIGN(4) fr_face_t;

typedef struct fr_person_s{
    unsigned int person_id;
	unsigned int timestamp;
	unsigned int face_cnt;
	unsigned char tag1[4]; /*reserved field*/
	unsigned char tag2[4]; /*reserved field*/
	unsigned char tag3[4]; /*reserved field*/
	unsigned char tag4[4]; /*reserved field*/
    fr_face_t faces[PERSON_MAXNUM_FACE];
} GCC_ALIGN(4) fr_person_t;

#ifdef _WIN32
#pragma pack()
#endif
//=======================================================================================

//------------------------------func definition----------------------------------------------------------
FR_API int  FR_Init();
FR_API void FR_Cleanup();
FR_API const char* FR_Errmsg(int errcode);

/*-------------------------------------------------
*@function
*   get connect device list
*@param
*   devs:       array, need alloc by caller
*   dev_cnt:    array cnt    
*@return
*   device nums
---------------------------------------------------*/
FR_API int FR_GetDeviceList(fr_device_t* devs, int* dev_cnt);

FR_API int FR_GetVersion(int hdev, fr_version_t* version);

FR_API int FR_GetDBSize(int hdev, int* size);
FR_API int FR_ResetDB(int hdev);

FR_API int FR_GetPersonList(int hdev, unsigned int** person_ids, int* person_cnt);
FR_API int FR_FreePersonList(unsigned int* person_ids);

FR_API int FR_GetPerson(int hdev, fr_person_t* person);
FR_API int FR_AddPerson(int hdev, fr_person_t* person);
FR_API int FR_DelPerson(int hdev, fr_person_t* person);
FR_API int FR_ModPerson(int hdev, fr_person_t* person);
//==================================================================================================================

#ifdef __cplusplus
}
#endif

#endif // FR_SDK_H