#ifndef __FILEOPTIONSEX_H
#define __FILEOPTIONSEX_H
#include <io.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
using namespace std;

/*****************************************文件检测相关函数************************************/
//判断文件或者目录是否存在
BOOL FileExists(LPCTSTR lpszFileName, BOOL bIsDirCheck);

//检测文件编码并返回特定的数值标记
int CheckFileCode(const char* str);

/*****************************************文件搜索相关函数************************************/
//根据脏字库（文件名称标记集合）来查找指定目录下的文件
bool FindFilesByNameFlag(string SearchingMD, vector<string>& FindedFilesArrary, vector<string>& NameFlagLib);

/*****************************************文件读取相关函数************************************/
//获取文件里的逐行信息
vector<string> ReadArrInfoInFile(const char* FilePath);

//读取文件里的内容，可以读取非ANSI编码的文件，因为它就是以二进制的方式来读取文件的
string ReadTextInFile(const char* FilePath);

//将文本保存成一个文件
bool CreateFileFromText(string TextInfo, const char* FilePath);

//将字符串数组保存成一个文件
bool CreateFileFromArrInfo(vector<string> ArrInfo, const char* FilePath);

#endif