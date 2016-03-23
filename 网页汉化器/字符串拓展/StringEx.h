#ifndef __STRING_H
#define __STRING_H
#include <string>
#include <vector>
#include <windows.h>
#include <algorithm>//大小写转换函数的头文件
using namespace std;

//Unicode转换为多字节
char* UnicodeToANSI(const wchar_t* wp);

//多字节转换为Unicode
wchar_t* AnsiToUnicode(const char* szStr);

//全局替换字符串
void GlobalReStr(string&   str, string old_value, string new_value);

//SourceStr:被分割的字符串
//FirstFlag:分割的起始标记
//FinalFlag:分割的末尾标记
vector<string> GetArrBySpliteString(string SourceStr, string FirstFlag, string FinalFlag);

//SourceStr:被分割的字符串
//FirstFlag:分割的起始标记
//FinalFlag:分割的末尾标记
string GetStrBySpliteString(string SourceStr, string FirstFlag, string FinalFlag);

//将所有小写字母转换成大写
string SmallCharToBigChar(const char* Str);
void SmallCharToBigChar(string &TempStr);

//UTF-8和ASCI互转函数
string Convert(string str, int sourceCodepage, int targetCodepage);

//判断字符串是否属于UTF-8编码
BOOL IsTextUTF8(char* str, ULONGLONG length);

//判断字符串是否属于UTF-8编码的
bool IsUTF8String(const char* str, int length);

//字符串转换成整型
int str2int(string string_temp);

//整型转换成字符串
string int2str(int int_temp);

//定义一个函数来判断一个字符串里是否含有脏字，第一个参数是待判断的字符串，第二个参数是脏字库
bool FilterStr(string Str, vector<string>& FilterLib, int ModeFlag);

//Unicode下/多字符集下
wstring UT2WC(const char* buf);

//多字符集下/Unicode下
std::string WC2UT(const wchar_t* buf);

//ANSI转换成UNICODE
std::wstring MB2WC(const char* buf);

//UNICODE转换成ANSI
std::string WC2MB(const wchar_t* buf);

//判断当前字符串是否全为数字，过滤各种运算符号后才判断哦
bool IsNumberStr(string str);

//显示字符串里的特殊字符
void ShowSpecialChars(string str);

//输出ASCII码表
void PrintASCIIList();

//枚举PrintByHex的显示模式
typedef enum{
	ShowOneChar,//仅仅将逐个字符的十六进制逐行显示出来
	ShowAllChar,//将逐个字符的十六进制以整体方式输出
	ShowCharInfo,//显示此字符的十六进制信息和十进制信息
	ShowNoting//不显示任何信息
}PrintType;
//将字符串以十六进制形式输出
string SourceStrToHexStr(string str, PrintType ShowType);

//将字符串以十六进制形式输出
string SourceStrToHexStr(string SourceStr, string HexFlag);

//将十六进制数值转换为十进制数值
int HexStrToInt(string HexStr);

//将十六进制字符串转换为其相应的源字符串
string HexStrToSourceStr(string HexStr, string CutFlag);


//判断是否全为大写字母（仅仅对字母进行判断，跳过所有其他非字母字符）
bool IsAllBigEn(string EnStr);


//判断当前字符串是否包含非ASCII字符
bool IsIncludeNoASCII(string SourceStr);


//判断当前字符串是否需要翻译
bool IsCanTranslateEx(string EnStr);


#endif