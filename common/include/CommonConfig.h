#ifndef __COMMON_CONFIG_H
#define __COMMON_CONFIG_H

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string.h>
#include <vector>
#include <sstream>

#include<cv.h>
#include<highgui.h>

#ifdef __linux
	#include <sys/wait.h>
	#include "algorithm"
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <sys/time.h>
	#include <dirent.h>
#else
	#include <Windows.h>
	#include <Psapi.h>
	#include <io.h>
	#include <direct.h>
	#include <psapi.h>
	#pragma comment(lib,"psapi.lib")
#endif
#include<queue>

using namespace std;
using namespace cv;

///*计算时间*//
double StartTime();

double EndTime(double startTime);

///*建立文件夹*///
void CreateFoder(char filepath[256], char filename[128]);

void quick_sort(float *x, int *index, int low, int high);

void readImagePath(string path, int depth, vector<string>& pic_list);

#ifdef __linux

#else
int BrowseVideoPicturePath(string path, vector<string>& pic_list, bool subFilter, int Type);

DWORD getCpuUsgae();

void MemoryStatistical(int fram, FILE *fp, DWORD dwValue);
#endif

string GetDateTimeString(unsigned int timestamp);

double RectDiff(Rect r1, Rect r2);

#endif
