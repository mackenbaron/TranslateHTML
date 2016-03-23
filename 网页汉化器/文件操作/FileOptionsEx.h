#ifndef __FILEOPTIONSEX_H
#define __FILEOPTIONSEX_H
#include <io.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
using namespace std;

/*****************************************�ļ������غ���************************************/
//�ж��ļ�����Ŀ¼�Ƿ����
BOOL FileExists(LPCTSTR lpszFileName, BOOL bIsDirCheck);

//����ļ����벢�����ض�����ֵ���
int CheckFileCode(const char* str);

/*****************************************�ļ�������غ���************************************/
//�������ֿ⣨�ļ����Ʊ�Ǽ��ϣ�������ָ��Ŀ¼�µ��ļ�
bool FindFilesByNameFlag(string SearchingMD, vector<string>& FindedFilesArrary, vector<string>& NameFlagLib);

/*****************************************�ļ���ȡ��غ���************************************/
//��ȡ�ļ����������Ϣ
vector<string> ReadArrInfoInFile(const char* FilePath);

//��ȡ�ļ�������ݣ����Զ�ȡ��ANSI������ļ�����Ϊ�������Զ����Ƶķ�ʽ����ȡ�ļ���
string ReadTextInFile(const char* FilePath);

//���ı������һ���ļ�
bool CreateFileFromText(string TextInfo, const char* FilePath);

//���ַ������鱣���һ���ļ�
bool CreateFileFromArrInfo(vector<string> ArrInfo, const char* FilePath);

#endif