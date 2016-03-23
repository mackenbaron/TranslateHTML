#ifndef __WEBOPTIONS_H
#define __WEBOPTIONS_H
#include <windows.h>
#include <string>
#include <tchar.h>
#include <iostream>
//引入Shlwapi库来判断URL是否合法
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
//引入web相关的导入库和头文件
#include <wininet.h>
#pragma comment(lib, "Wininet.lib")

#define MAXSIZE 1024
using namespace std;

//检测制定URL的网络状况
int CheckNetWork(string url);

//对字符串进行URL编码
void URLCode(string &str_source);

//扒下网页里的网页源码
string GeWebInfo(string url);

//添加字符编码转换功能和网络异常情况下三次自动重连功能，和手动设置文件编码
string GeWebInfoEx(string url, int CharCodeFlag);

//添加字符编码转换功能和网络异常情况下三次自动重连功能，字符串编码不更改
string GeWebInfoEx(string url);

//判断当前字符串是否是合法URL
bool IsAvailableURL(_TCHAR* strurl);
bool IsAvailableURL(string strurl);

#endif