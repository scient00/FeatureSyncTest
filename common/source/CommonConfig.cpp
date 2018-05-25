#include<CommonConfig.h>


///*计算时间*//
double StartTime()
{
	return cvGetTickCount();
}
double EndTime(double startTime)
{
	return ((double)cvGetTickCount() - startTime) / ((double)cvGetTickFrequency() * 1000);
}
///*快速排序*///
int Partition(float *x, int *index, int low, int high)
{
	float pivotkey = 0, temp = 0;
	int _temp = 0;
	temp = x[low];
	pivotkey = x[low];
	while (low<high)
	{
		while (low<high&&x[high] <= pivotkey)
			--high;
		//lowhighλüλñ
		x[low] = x[high];
		_temp = index[high];
		index[high] = index[low];
		index[low] = _temp;

		while (low<high&&x[low] >= pivotkey)
			++low;
		//lowhighλü
		x[high] = x[low];
		_temp = index[high];
		index[high] = index[low];
		index[low] = _temp;
	}
	x[low] = temp;
	return(low);
}
void quick_sort(float *x, int *index, int low, int high)
{
	int pivotloc;
	if (low<high)
	{
		pivotloc = Partition(x, index, low, high);

		quick_sort(x, index, low, pivotloc - 1);
		quick_sort(x, index, pivotloc + 1, high);
	}
}

#ifdef __linux
void CreateFoder(char filepath[256], char filename[128])
{
	int status = 0;
	char cDir[512];
	sprintf(cDir, "%s/%s", filepath, filename);
	status = mkdir(cDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

}
void readImagePath(string dir, int depth, vector <string>&imgNames)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	char image[256];
	if ((dp = opendir(dir.c_str())) == NULL)
	{
		fprintf(stderr, "cannot open directory: %s\n", dir.c_str());
		return;
	}
	chdir(dir.c_str());
	while ((entry = readdir(dp)) != NULL)
	{
		//得到文本信息
		lstat(entry->d_name, &statbuf);
		//判断目录还是文件
		if (S_ISDIR(statbuf.st_mode))
		{
			/* 排除当前目录和上级目录 */
			if (strcmp(".", entry->d_name) == 0 ||
				strcmp("..", entry->d_name) == 0)
				continue;

			printf("%*s%s/\n", depth, "", entry->d_name);

			/* Recurse at a new indent level */
			readImagePath(entry->d_name, depth + 4, imgNames);
		}
		else
		{
			//printf("%*s%s\n",depth,"",entry->d_name);
			sprintf(image, "%s", entry->d_name);
			string sName = image;
			if (sName.substr(strlen(sName.c_str()) - 3, 3) == "jpg" || sName.substr(strlen(sName.c_str()) - 3, 3) == "JPG" || sName.substr(strlen(sName.c_str()) - 4, 4) == "jpeg" || sName.substr(strlen(sName.c_str()) - 3, 3) == "bmp")
			{
				string ImagePath = dir + image;
				imgNames.push_back(ImagePath);
			}

		}

	}
	chdir("..");
	closedir(dp);
}
#else
void CreateFoder(char filepath[256], char filename[128])
{
	char cDir[512];
	sprintf(cDir, "%s/%s", filepath, filename);
	if (_access(cDir, 0) != 0)    //_access访问文件所在的路径名，返回0表示文件在当前路径存在，返回-1表示文件在当前路径不存在
		_mkdir(cDir);
}
void readImagePath(string path, int depth, vector<string>& pic_list) //遍历文件目录下图片
{
	string postfix = "*";
	bool subFilter = true;
	WIN32_FIND_DATA findData;
	HANDLE hHandle = NULL;
	string filePathName;	// 查找文件名类型
	string fullPathName;	// 查找到的文件

	filePathName = path;
	filePathName += "\\*.";
	filePathName += postfix;

	hHandle = FindFirstFile(filePathName.data(), &findData);

	if (hHandle != INVALID_HANDLE_VALUE)
		do
		{
			if ("." == (string)findData.cFileName ||
				".." == (string)findData.cFileName)
				continue;

			fullPathName = path;
			fullPathName += "\\";
			fullPathName += findData.cFileName;

			if ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && subFilter)
				readImagePath(fullPathName.data(), 0, pic_list);
			else
			{
				string str = fullPathName.substr(fullPathName.length() - 3);
				if (str == "jpg" || str == "bmp" || str == "JPG" || str == "BMP")
				{
					pic_list.push_back(fullPathName);
				}
			}
		} while (FindNextFile(hHandle, &findData));

		FindClose(hHandle);
}
int BrowseVideoPicturePath(string path, vector<string>& pic_list, bool subFilter, int Type) //遍历当前路径下图片路径
{
	WIN32_FIND_DATA findData;
	HANDLE hHandle = NULL;
	string postfix = "*";
	string filePathName;
	string fullPathName;
	filePathName = path;
	filePathName += "\\*.";
	filePathName += postfix;
	hHandle = FindFirstFile(filePathName.data(), &findData);
	if (hHandle == INVALID_HANDLE_VALUE) return 1;

	do
	{
		if ("." == (string)findData.cFileName || ".." == (string)findData.cFileName) continue;
		fullPathName = path;
		fullPathName += "\\";
		fullPathName += findData.cFileName;
		if ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && subFilter) {
			if (Type == 4) {
				pic_list.push_back(fullPathName);
			}
			else if (Type == 2) {
				BrowseVideoPicturePath(fullPathName.data(), pic_list, subFilter, Type); //判断目标文件是否为文件夹
			}
		}
		else {

			string strTemp = fullPathName.substr(fullPathName.length() - 3);
			if (Type == 1) {
				if (strTemp == "jpg" || strTemp == "bmp" || strTemp == "JPG" || strTemp == "BMP") {
					pic_list.push_back(fullPathName);
				}
			}
			else if (Type == 2) {
				if (strTemp == "avi" || strTemp == "AVI" || strTemp == "MP4" || strTemp == "mp4") {
					pic_list.push_back(fullPathName);
				}
			}
			else if (Type == 3) {
				if (strTemp == "txt") {
					pic_list.push_back(fullPathName);
				}
			}
		}

	} while (FindNextFile(hHandle, &findData));
	FindClose(hHandle);
	return pic_list.size();
}
DWORD getCpuUsgae()  //内存使用率
{
	MEMORYSTATUS GetMemory;
	::GlobalMemoryStatus(&GetMemory);
	return GetMemory.dwMemoryLoad;//当前系统内存使用率
}
void MemoryStatistical(int fram, FILE *fp, DWORD dwValue)
{
	HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());
	PROCESS_MEMORY_COUNTERS MemoryInfo;
	GetProcessMemoryInfo(handle, &MemoryInfo, sizeof(MemoryInfo));
	//cout<<"进程ID:"<<GetCurrentProcessId()<<endl;
	fprintf(fp, "%d	%d%%		%dK		%dK\n", fram, dwValue, MemoryInfo.PeakWorkingSetSize / 1024, MemoryInfo.WorkingSetSize / 1024);
	fflush(fp);
	CloseHandle(handle);
}
#endif
string GetDateTimeString(unsigned int timestamp)
{
	string str;
	char buf[6][100];

	time_t nowtime;
	if (timestamp > 0)
		nowtime = timestamp;
	else
		time(&nowtime);

	tm *ptm = localtime(&nowtime);

	sprintf(buf[0], "%04d", ptm->tm_year + 1900);
	sprintf(buf[1], "%02d", ptm->tm_mon + 1);
	sprintf(buf[2], "%02d", ptm->tm_mday);
	sprintf(buf[3], "%02d", ptm->tm_hour);
	sprintf(buf[4], "%02d", ptm->tm_min);
	sprintf(buf[5], "%02d", ptm->tm_sec);

	//格式输出要求是连续的！
	str += buf[0];
	str += "-";
	str += buf[1];
	str += "-";
	str += buf[2];
	str += "-";
	str += buf[3];
	str += "-";
	str += buf[4];
	str += "-";
	str += buf[5];
	return str;
}
double RectDiff(Rect r1, Rect r2)//比较两个矩形框位置的相似度
{
	double dCoverRate = 0;
	if (MAX(r1.x, r2.x) <= MIN(r1.x + r1.width, r2.x + r2.width) && MAX(r1.y, r2.y) <= MIN(r1.y + r1.height, r2.y + r2.height))
	{
		int startx = MIN(r1.x, r2.x);
		int endx = MAX(r1.x + r1.width, r2.x + r2.width);
		int width = r1.width + r2.width - (endx - startx);

		int starty = MIN(r1.y, r2.y);
		int endy = MAX(r1.y + r1.height, r2.y + r2.height);
		int height = r1.height + r2.height - (endy - starty);

		if (width <= 0 || height <= 0)
			dCoverRate = 0;
		else
		{
			int Area = width * height;
			int Area1 = r1.width * r1.height;
			int Area2 = r2.width * r2.height;
			double c1 = (double)Area / Area1;
			double c2 = (double)Area / Area2;
			if (c1 >= c2)
				dCoverRate = c2;
			else
				dCoverRate = c1;
		}

	}

	return dCoverRate;
}

