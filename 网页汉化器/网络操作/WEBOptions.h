#ifndef __WEBOPTIONS_H
#define __WEBOPTIONS_H
#include <windows.h>
#include <string>
#include <tchar.h>
#include <iostream>
//����Shlwapi�����ж�URL�Ƿ�Ϸ�
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
//����web��صĵ�����ͷ�ļ�
#include <wininet.h>
#pragma comment(lib, "Wininet.lib")

#define MAXSIZE 1024
using namespace std;

//����ƶ�URL������״��
int CheckNetWork(string url);

//���ַ�������URL����
void URLCode(string &str_source);

//������ҳ�����ҳԴ��
string GeWebInfo(string url);

//����ַ�����ת�����ܺ������쳣����������Զ��������ܣ����ֶ������ļ�����
string GeWebInfoEx(string url, int CharCodeFlag);

//����ַ�����ת�����ܺ������쳣����������Զ��������ܣ��ַ������벻����
string GeWebInfoEx(string url);

//�жϵ�ǰ�ַ����Ƿ��ǺϷ�URL
bool IsAvailableURL(_TCHAR* strurl);
bool IsAvailableURL(string strurl);

#endif