/*
 rsNet_api.h

 History:
    2018/04/13 - LHF, Created.

 Copyright (C) 2018, ReadSense Technology, Inc.
*/

#ifndef __FEATURE_SYNC_RSNETAPI_H__
#define __FEATURE_SYNC_RSNETAPI_H__


#define FACE_FEATURE_LEN		512
#define MAX_PERSON_FACE			10


/********************************************************/
/*                    structure definition              */
/********************************************************/
typedef struct tagRSVerInfo
{
	int major;
	int minor;
	char revision[40];
} __attribute__((aligned(4)))S_RSVER_INFO;



typedef struct tagRSFaceInfo
{
	unsigned int face_id;
	unsigned int feature_version;
	float faceFeature[FACE_FEATURE_LEN];
} __attribute__((aligned(4)))S_RSFACE_INFO;


typedef struct tagRSPersonInfo
{
	unsigned int person_id;
	unsigned int timestamp;
	unsigned int face_cnt;
	unsigned char tag1[4]; /*reserved field*/
	unsigned char tag2[4]; /*reserved field*/
	unsigned char tag3[4]; /*reserved field*/
	unsigned char tag4[4]; /*reserved field*/
	S_RSFACE_INFO face_info[MAX_PERSON_FACE];
}__attribute__((aligned(4)))S_RSPERSON_INFO;



/********************************************************/
/*                    interface definition              */
/********************************************************/

#if defined(__cplusplus)
extern "C"
{
#endif

int  RS_FeatureSync_Init(const char *svrIp, const int svrPort, const char *dbPath);
void RS_FeatureSync_Exit(void);
int  RS_FeatureSync_Ping(void);

#if defined(__cplusplus)
}
#endif

#endif
