#ifndef __STRING_H
#define __STRING_H
#include <string>
#include <vector>
#include <windows.h>
#include <algorithm>//��Сдת��������ͷ�ļ�
using namespace std;

//Unicodeת��Ϊ���ֽ�
char* UnicodeToANSI(const wchar_t* wp);

//���ֽ�ת��ΪUnicode
wchar_t* AnsiToUnicode(const char* szStr);

//ȫ���滻�ַ���
void GlobalReStr(string&   str, string old_value, string new_value);

//SourceStr:���ָ���ַ���
//FirstFlag:�ָ����ʼ���
//FinalFlag:�ָ��ĩβ���
vector<string> GetArrBySpliteString(string SourceStr, string FirstFlag, string FinalFlag);

//SourceStr:���ָ���ַ���
//FirstFlag:�ָ����ʼ���
//FinalFlag:�ָ��ĩβ���
string GetStrBySpliteString(string SourceStr, string FirstFlag, string FinalFlag);

//������Сд��ĸת���ɴ�д
string SmallCharToBigChar(const char* Str);
void SmallCharToBigChar(string &TempStr);

//UTF-8��ASCI��ת����
string Convert(string str, int sourceCodepage, int targetCodepage);

//�ж��ַ����Ƿ�����UTF-8����
BOOL IsTextUTF8(char* str, ULONGLONG length);

//�ж��ַ����Ƿ�����UTF-8�����
bool IsUTF8String(const char* str, int length);

//�ַ���ת��������
int str2int(string string_temp);

//����ת�����ַ���
string int2str(int int_temp);

//����һ���������ж�һ���ַ������Ƿ������֣���һ�������Ǵ��жϵ��ַ������ڶ������������ֿ�
bool FilterStr(string Str, vector<string>& FilterLib, int ModeFlag);

//Unicode��/���ַ�����
wstring UT2WC(const char* buf);

//���ַ�����/Unicode��
std::string WC2UT(const wchar_t* buf);

//ANSIת����UNICODE
std::wstring MB2WC(const char* buf);

//UNICODEת����ANSI
std::string WC2MB(const wchar_t* buf);

//�жϵ�ǰ�ַ����Ƿ�ȫΪ���֣����˸���������ź���ж�Ŷ
bool IsNumberStr(string str);

//��ʾ�ַ�����������ַ�
void ShowSpecialChars(string str);

//���ASCII���
void PrintASCIIList();

//ö��PrintByHex����ʾģʽ
typedef enum{
	ShowOneChar,//����������ַ���ʮ������������ʾ����
	ShowAllChar,//������ַ���ʮ�����������巽ʽ���
	ShowCharInfo,//��ʾ���ַ���ʮ��������Ϣ��ʮ������Ϣ
	ShowNoting//����ʾ�κ���Ϣ
}PrintType;
//���ַ�����ʮ��������ʽ���
string SourceStrToHexStr(string str, PrintType ShowType);

//���ַ�����ʮ��������ʽ���
string SourceStrToHexStr(string SourceStr, string HexFlag);

//��ʮ��������ֵת��Ϊʮ������ֵ
int HexStrToInt(string HexStr);

//��ʮ�������ַ���ת��Ϊ����Ӧ��Դ�ַ���
string HexStrToSourceStr(string HexStr, string CutFlag);


//�ж��Ƿ�ȫΪ��д��ĸ����������ĸ�����жϣ�����������������ĸ�ַ���
bool IsAllBigEn(string EnStr);


//�жϵ�ǰ�ַ����Ƿ������ASCII�ַ�
bool IsIncludeNoASCII(string SourceStr);


//�жϵ�ǰ�ַ����Ƿ���Ҫ����
bool IsCanTranslateEx(string EnStr);


#endif