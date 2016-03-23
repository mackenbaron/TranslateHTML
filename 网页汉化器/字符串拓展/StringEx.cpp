#include "StringEx.h"

//Unicode转换为多字节
char* UnicodeToANSI(const wchar_t* wp)
{
	int len = WideCharToMultiByte(CP_ACP, 0, wp, wcslen(wp), NULL, 0, NULL, NULL);
	char* m_char = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, wp, wcslen(wp), m_char, len, NULL, NULL);
	m_char[len] = '\0';
	return m_char;
}

//多字节转换为Unicode
wchar_t* AnsiToUnicode(const char* szStr)
{
	int nLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szStr, -1, NULL, 0);
	if (nLen == 0)
	{
		return NULL;
	}
	wchar_t* pResult = new wchar_t[nLen];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szStr, -1, pResult, nLen);
	return pResult;
}

string SmallCharToBigChar(const char* Str)
{
	string TempStr(Str);
	transform(TempStr.begin(), TempStr.end(), TempStr.begin(), ::toupper);//将所有小写字母转换成大写
	return TempStr;
}

void SmallCharToBigChar(string &TempStr)
{
	transform(TempStr.begin(), TempStr.end(), TempStr.begin(), ::toupper);//将所有小写字母转换成大写
}



//全局替换字符串
void GlobalReStr(string&   str, string old_value, string new_value)
{
	for (string::size_type pos(0); pos != string::npos; pos += new_value.length())   {
		if ((pos = str.find(old_value, pos)) != string::npos)
			str.replace(pos, old_value.length(), new_value);
		else   break;
	}
}




//SourceStr:被分割的字符串
//FirstFlag:分割的起始标记
//FinalFlag:分割的末尾标记
string GetStrBySpliteString(string SourceStr, string FirstFlag, string FinalFlag)
{
	int ROffset = 0;
	string SpliteResult = "";
	while (SourceStr.find(FirstFlag, ROffset) >= 0 && SourceStr.find(FirstFlag, ROffset) <= strlen(SourceStr.c_str()))
	{
		int findex = SourceStr.find(FirstFlag, ROffset);//得到起始标记De所在index
		int sindex = SourceStr.find(FinalFlag, findex + strlen(FirstFlag.c_str()));//得到末尾标记的所在index
		if (SourceStr.find(FinalFlag, findex + strlen(FirstFlag.c_str())) >= 0 && SourceStr.find(FinalFlag, findex + strlen(FirstFlag.c_str())) <= strlen(SourceStr.c_str()))
		{
			SpliteResult += SourceStr.substr(findex + strlen(FirstFlag.c_str()), sindex - findex - strlen(FirstFlag.c_str()));
		}
		ROffset = sindex;
	}
	return SpliteResult;
}



//SourceStr:被分割的字符串
//FirstFlag:分割的起始标记
//FinalFlag:分割的末尾标记
vector<string> GetArrBySpliteString(string SourceStr, string FirstFlag, string FinalFlag)
{
	int ROffset = 0;
	vector<string>SpliteResult;
	while (SourceStr.find(FirstFlag, ROffset) >= 0 && SourceStr.find(FirstFlag, ROffset) <= strlen(SourceStr.c_str()))
	{
		int findex = SourceStr.find(FirstFlag, ROffset);//得到起始标记De所在index
		int sindex = SourceStr.find(FinalFlag, findex + strlen(FirstFlag.c_str()));//得到末尾标记的所在index
		if (SourceStr.find(FinalFlag, findex + strlen(FirstFlag.c_str())) >= 0 && SourceStr.find(FinalFlag, findex + strlen(FirstFlag.c_str())) <= strlen(SourceStr.c_str()))
		{
			SpliteResult.push_back(SourceStr.substr(findex + strlen(FirstFlag.c_str()), sindex - findex - strlen(FirstFlag.c_str())));
		}
		ROffset = sindex;
	}
	return SpliteResult;
}




//UTF-8和ASCI互转函数
string Convert(string str, int sourceCodepage, int targetCodepage)
{
	size_t len = str.length();
	size_t unicodeLen = MultiByteToWideChar(sourceCodepage, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pUnicode = NULL;
	pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1)*sizeof(wchar_t));
	MultiByteToWideChar(sourceCodepage, 0, str.c_str(), -1, (LPWSTR)pUnicode, (int)unicodeLen);

	BYTE* pTargetData = NULL;
	int targetLen = WideCharToMultiByte(targetCodepage, 0, (LPWSTR)pUnicode, -1,
		(char *)pTargetData, 0, NULL, NULL);
	pTargetData = new BYTE[targetLen + 1];
	memset(pTargetData, 0, targetLen + 1);

	WideCharToMultiByte(targetCodepage, 0, (LPWSTR)pUnicode, -1,
		(char*)pTargetData, targetLen, NULL, NULL);
	string  rt((char*)pTargetData);

	delete[] pUnicode;
	delete[] pTargetData;
	return  rt;
}


//判断字符串是否属于UTF-8编码的
bool IsUTF8String(const char* str, int length)
{
	int i = 0;
	int nBytes = 0;//UTF8可用1-6个字节编码,ASCII用一个字节
	unsigned char chr = 0;
	bool bAllAscii = true;//如果全部都是ASCII,说明不是UTF-8

	while (i < length)
	{
		chr = *(str + i);
		if ((chr & 0x80) != 0)
			bAllAscii = false;
		if (nBytes == 0)//计算字节数
		{
			if ((chr & 0x80) != 0)
			{
				while ((chr & 0x80) != 0)
				{
					chr <<= 1;
					nBytes++;
				}
				if (nBytes < 2 || nBytes > 6)
					return false;//第一个字节最少为110x xxxx
				nBytes--;//减去自身占的一个字节
			}
		}
		else//多字节除了第一个字节外剩下的字节
		{
			if ((chr & 0xc0) != 0x80)
				return false;//剩下的字节都是10xx xxxx的形式
			nBytes--;
		}
		++i;
	}
	if (bAllAscii)
		return false;
	return nBytes == 0;
}



//判断字符串是否属于UTF-8编码
BOOL IsTextUTF8(char* str, ULONGLONG length)
{
	DWORD nBytes = 0;//UFT8可用1-6个字节编码,ASCII用一个字节  
	UCHAR chr;
	BOOL bAllAscii = TRUE; //如果全部都是ASCII, 说明不是UTF-8  
	for (int i = 0; i<length; ++i)
	{
		chr = *(str + i);
		if ((chr & 0x80) != 0) // 判断是否ASCII编码,如果不是,说明有可能是UTF-8,ASCII用7位编码,但用一个字节存,最高位标记为0,o0xxxxxxx  
			bAllAscii = FALSE;
		if (nBytes == 0) //如果不是ASCII码,应该是多字节符,计算字节数  
		{
			if (chr >= 0x80)
			{
				if (chr >= 0xFC && chr <= 0xFD)
					nBytes = 6;
				else if (chr >= 0xF8)
					nBytes = 5;
				else if (chr >= 0xF0)
					nBytes = 4;
				else if (chr >= 0xE0)
					nBytes = 3;
				else if (chr >= 0xC0)
					nBytes = 2;
				else
					return FALSE;

				nBytes--;
			}
		}
		else //多字节符的非首字节,应为 10xxxxxx  
		{
			if ((chr & 0xC0) != 0x80)
				return FALSE;

			nBytes--;
		}
	}
	if (nBytes > 0) //违返规则  
		return FALSE;
	if (bAllAscii) //如果全部都是ASCII, 说明不是UTF-8  
		return FALSE;

	return TRUE;
}



//字符串转换成整型
int str2int(string string_temp)
{
	return atoi(string_temp.c_str());
}

//整型转换成字符串
string int2str(int int_temp)
{
	char s[12];             //设定12位对于存储32位int值足够  
#if _MSC_VER<1400   //VS 2005版本以下            
	itoa(int_temp, s, 10);
#else  //VS 2005版本以上
	_itoa_s(int_temp, s, 10); //itoa函数亦可以实现，但是属于C中函数，在C++中推荐用流的方法，另外，由于VS 2013已经将C里面标准库函数重新定义了一次，所以，itoa在VS 2013中就变成了_itoa_s
#endif   

	return s;
}



//定义一个函数来判断一个字符串里是否含有脏字，第一个参数是待判断的字符串，第二个参数是脏字库
bool FilterStr(string Str, vector<string>& FilterLib, int ModeFlag)
{
	int FilterCount = FilterLib.size();//获得容器里元素的个数
	int MatchCount = 0;//定义一个匹配个数计数器
	//定义一个变量来判断
	bool ResultFlag = false;//如果始终为0(false)，那么说明这个字符串里没有脏字
	switch (ModeFlag)
	{
	case 1://全字匹配保存
	{
			   ModeFlag = FilterCount;
			   //由于这个FilterLib只有在初始化时才能知道其值的，所以这里不能够使用sizeof(FilterLib) / sizeof(FilterLib[1])的方式来获得此数组的个数，必须预先指定，所以为其设置一个计数器，和argc argv相似
			   for (int i = 0; i < FilterCount&&MatchCount < ModeFlag; i++)//添加两个处理机制，1.搜索完所有脏字库或者是找到一个匹配后就中止，节省时间
			   {
				   //首先，这个找到的位置标记绝对不会大于字符串本身长度，而且索引好必定大于-1，本来应该设置为-1的，不过由于编译器在编译时有时候会将其认定为
				   //Str.find(FilterLib[i]) < strlen(Str.c_str()) ? cout << "Yes" << endl : cout << "No" << endl;
				   //Str.find(FilterLib[i])>-1 ? cout << "Yes" << endl : cout << "No" << endl;//通过这个判断可以知道，有时候-1会被认定为其它数值，以此作为判断并不可靠，将>-1改为>=0即可
				   //Str.find(FilterLib[i])>=0 ? cout << "Yes" << endl : cout << "No" << endl;//这里就能够很好地证明了
				   if (Str.find(FilterLib[i].c_str()) < strlen(Str.c_str()) && Str.find(FilterLib[i].c_str()) >= 0)
				   {
					   //ResultFlag = Str.find(FilterLib[i]);
					   MatchCount++;
				   }
			   }
			   if (MatchCount == ModeFlag)
			   {
				   ResultFlag = true;
			   }
	}; break;
	case 2://部分匹配保存
	{
			   ModeFlag = 1;
			   //由于这个FilterLib只有在初始化时才能知道其值的，所以这里不能够使用sizeof(FilterLib) / sizeof(FilterLib[1])的方式来获得此数组的个数，必须预先指定，所以为其设置一个计数器，和argc argv相似
			   for (int i = 0; i < FilterCount&&MatchCount < ModeFlag; i++)//添加两个处理机制，1.搜索完所有脏字库或者是找到一个匹配后就中止，节省时间
			   {
				   if (Str.find(FilterLib[i].c_str()) < strlen(Str.c_str()) && Str.find(FilterLib[i].c_str()) >= 0)
				   {
					   MatchCount++;
				   }
			   }
			   if (MatchCount == ModeFlag)
			   {
				   ResultFlag = true;
			   }
	}; break;
	}
	return ResultFlag;
}

//Unicode下/多字符集下
wstring UT2WC(const char* buf)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, buf, -1, NULL, 0);
	std::vector<wchar_t> unicode(len);
	MultiByteToWideChar(CP_UTF8, 0, buf, -1, &unicode[0], len);
	return std::wstring(&unicode[0]);
}

//多字符集下/Unicode下
std::string WC2UT(const wchar_t* buf)
{
	int len = WideCharToMultiByte(CP_UTF8, 0, buf, -1, NULL, 0, NULL, NULL);
	std::vector<char> utf8(len);
	WideCharToMultiByte(CP_UTF8, 0, buf, -1, &utf8[0], len, NULL, NULL);
	return std::string(&utf8[0]);
}


//ANSI转换成UNICODE
std::wstring MB2WC(const char* buf)
{
	int len = MultiByteToWideChar(CP_ACP, 0, buf, -1, NULL, 0);
	std::vector<wchar_t> unicode(len);
	MultiByteToWideChar(CP_ACP, 0, buf, -1, &unicode[0], len);
	return std::wstring(&unicode[0]);
}


//UNICODE转换成ANSI
std::string WC2MB(const wchar_t* buf)
{
	int len = WideCharToMultiByte(CP_ACP, 0, buf, -1, NULL, 0, NULL, NULL);
	std::vector<char> utf8(len);
	WideCharToMultiByte(CP_ACP, 0, buf, -1, &utf8[0], len, NULL, NULL);
	return std::string(&utf8[0]);
}



//将字符串以十六进制形式输出
string SourceStrToHexStr(string str, PrintType ShowType)
{
	const char *s = str.c_str();
	string HexStr = "";
	for (size_t i = 0; i<strlen(s); i++)
	{
		unsigned char TempChar = (unsigned char)s[i];//去掉字符的符号位
		char TempStr[5];//存放字符十六进制的字符串
		//兼容VC 6.0
#if _MSC_VER<1400   //VS 2005版本以下            
		sprintf(TempStr, "%x", TempChar);//将此字节的十六进制存放到TempStr中
#else  //VS 2005版本以上
		sprintf_s(TempStr, "%x", TempChar);//将此字节的十六进制存放到TempStr中
#endif   
		HexStr += string("\\x") + TempStr;
		switch (ShowType)
		{
		case ShowOneChar:
		{
							//兼容VC 6.0
#if _MSC_VER<1400   //VS 2005版本以下            
							printf("字节：\"%c \"的十六进制字符个数为：%d\n", TempChar, strlen(TempStr));
							printf("\\x%s\n", TempStr);
#else  //VS 2005版本以上
							printf_s("字节：\"%c \"的十六进制字符个数为：%d\n", TempChar, strlen(TempStr));
							printf_s("\\x%s\n", TempStr);
#endif
		}; break;
		case ShowAllChar:
		{
							//兼容VC 6.0
#if _MSC_VER<1400   //VS 2005版本以下            
							printf("\\x%s", TempStr);
#else  //VS 2005版本以上
							printf_s("\\x%s", TempStr);
#endif   
		}; break;
		case ShowCharInfo:
		{
							 int CharID = (int)TempChar;
							 if (CharID > 126)
							 {
								 //printf("由于此字符不再ASCII码表内，所以会在%cc的右边添加多一个空格，避免遇到非ASCII字符时时出现乱码\n",'%');
								 printf("经检测，发现此字符是非ASCII码，由于缺少了另一半，所以显示为%c ，\n其对应的十六进制为：%s，其对应的十进制为：%d\n", TempChar, TempStr, CharID);
							 }
							 else
							 {
								 printf("%c对应的十六进制为：%s，其对应的十进制为：%d\n", TempChar, TempStr, CharID);
							 }

		}; break;
		}
		//printf("\\x%x", (unsigned char)s[i]);//可以实现将汉字和十六进制进行互转，去掉符号位后就正常了
		//printf("\\x%x", s[i]);//遇到非ACSII码就会超出机器码字节，从而输出\xffffffe6\xffffff88之类的数据，这个是因为char 的符号位存在时才出现的
		//printf("0x%x", s[i]);
	}
	return HexStr;
}


//将字符串以十六进制形式输出
string SourceStrToHexStr(string SourceStr, string HexFlag)
{
	const char *s = SourceStr.c_str();
	string HexStr = "";//存放此字符串的十六进制数据结果
	//逐个字节读取字符串
	for (size_t i = 0; i<strlen(s); i++)
	{
		unsigned char TempChar = (unsigned char)s[i];//去掉字节的符号位
		char TempStr[3];//存放字节的十六进制形式，字符数在3之内
		//兼容VC 6.0
#if _MSC_VER<1400   //VS 2005版本以下            
		sprintf(TempStr, "%x", TempChar);//将此字节的十六进制存放到TempStr中
#else  //VS 2005版本以上
		sprintf_s(TempStr, "%x", TempChar);//将此字节的十六进制存放到TempStr中
#endif   
		HexStr += HexFlag + TempStr;//假设HexFlag为\x，则存储的十六进制数据形式为\xc0\xad\xbe\xab
	}
	return HexStr;
}



//判断当前字符串是否全为数字，过滤各种运算符号后才判断哦
bool IsNumberStr(string str)
{
	bool bIsDigit = true;
	GlobalReStr(str, ".", "");
	GlobalReStr(str, "-", "");
	GlobalReStr(str, "+", "");
	GlobalReStr(str, "*", "");
	GlobalReStr(str, "/", "");
	int nCount = str.length(); // 获得字符个数
	for (int i = 0; i < nCount; i++)
	{
		if (0 == isdigit(str.at(i))) // 不是数字就置标志位
		{
			bIsDigit = false;
			return false;// 退出
		}
	}
	return bIsDigit;
}



//显示字符串里的特殊字符
void ShowSpecialChars(string str)
{
	//注意：此函数仅仅支持ANSI码，一旦遇到非ANSI码将会出错
	//ShowSpecialChars("\x0d");
	//ShowSpecialChars("\r");

	//ShowSpecialChars("\x0a");
	//ShowSpecialChars("\n");

	//ShowSpecialChars("\x20");//空格
	//ShowSpecialChars(" ");//空格

	const char *s = str.c_str();
	size_t i;
	printf("%s\n", s);
	for (i = 0; i<strlen(s); i++)
	{
		if (ispunct(s[i])) printf("^");
		//else printf("此字符内容为：%c，其十六进制为%x", s[i], s[i]); 
		else printf("%x", s[i]);
	}
}



//输出ASCII码表
void PrintASCIIList()
{
	printf("ASCII码表的所在范围是十进制下的0-126，十六进制下的0-7e\n");
	//输出整张ASCII码表
	for (size_t x = 0; x < 127; x++)
	{
		printf("%c", (unsigned char)x);
		//printf("%c\n", (unsigned char)x);
	}
	printf("\n");
}



//将十六进制数值转换为十进制
//此函数经修改int ChangeNum(CString str,int length)所得，原函数使用了MFC里的CString，这里改成了string
//来源于：（十六进制字符串转换为十进制数值）http://blog.csdn.net/xhao014/article/details/6598672
int HexStrToInt(string HexStr)
{
	int length = HexStr.length();
	const char *revstr = HexStr.c_str();  //根据十六进制字符串的长度，这里注意数组不要越界   
	int   num[16] = { 0 };
	int   count = 1;
	int   result = 0;
	for (int i = length - 1; i >= 0; i--)
	{
		if ((revstr[i] >= '0') && (revstr[i] <= '9'))
			num[i] = revstr[i] - 48;//字符0的ASCII值为48   
		else if ((revstr[i] >= 'a') && (revstr[i] <= 'f'))
			num[i] = revstr[i] - 'a' + 10;
		else if ((revstr[i] >= 'A') && (revstr[i] <= 'F'))
			num[i] = revstr[i] - 'A' + 10;
		else
			num[i] = 0;
		result = result + num[i] * count;
		count = count * 16;//十六进制(如果是八进制就在这里乘以8)       
	}
	return result;
}


//将十六进制字符串转换为其相应的源字符串
string HexStrToSourceStr(string HexStr, string CutFlag)
{
	string SourceStr = "";
	char TempStr[3];//存放字节的十六进制形式，字符数在3之内
	HexStr += CutFlag;
	vector<string> CharLIB = GetArrBySpliteString(HexStr, CutFlag, CutFlag);
	for (size_t i = 0; i < CharLIB.size(); i++)
	{
		//兼容VC 6.0
#if _MSC_VER<1400   //VS 2005版本以下            
		//printf("%c",(unsigned char)HexStrToInt(CharLIB[i]));
		sprintf(TempStr, "%c", (unsigned char)HexStrToInt(CharLIB[i]));
#else  //VS 2005版本以上
		//printf_s("%c",(unsigned char)HexStrToInt(CharLIB[i]));
		sprintf_s(TempStr, "%c", (unsigned char)HexStrToInt(CharLIB[i]));
#endif   
		SourceStr += TempStr;
	}
	return SourceStr;
}



//判断是否全为大写字母（仅仅对字母进行判断，跳过所有其他非字母字符）
bool IsAllBigEn(string EnStr)
{
	const char* TempStr = EnStr.c_str();
	bool IsAll = true;
	char CharNum[5];//字节的对应索引最多是三位数
	for (size_t i = 0; i < strlen(TempStr); i++)
	{
		//兼容VC 6.0
#if _MSC_VER<1400   //VS 2005版本以下            
		sprintf(CharNum, "%d\n", (int)TempStr[i]);
#else  //VS 2005版本以上
		sprintf_s(CharNum, "%d\n", (int)TempStr[i]);
#endif  
		int CharID = atoi(CharNum);
		if (CharID>96 && CharID < 123)
		{
			return false;
		}
	}
	return IsAll;
}




//判断当前字符串是否包含非ASCII字符
bool IsIncludeNoASCII(string SourceStr)
{
	const char* TempStr = SourceStr.c_str();
	bool IsInclude = false;
	for (size_t i = 0; i < strlen(TempStr); i++)
	{
		int CharID = (int)TempStr[i];
		if (CharID < 0)
		{
			return true;
		}
	}
	return IsInclude;
}




//判断当前字符串是否需要翻译
bool IsCanTranslateEx(string EnStr)
{
	if (IsAllBigEn(EnStr))//如果字母全部为大写，直接认定为无需翻译
	{
		return false;
	}
	string str = EnStr;
	bool IsEable = false;
	GlobalReStr(str, " ", "");
	GlobalReStr(str, "-", "");
	GlobalReStr(str, "_", "");
	if (str.length() == EnStr.length())
	{
		return true;
	}
	else
	{
		const char* TempStr = EnStr.c_str();
		int HeadIndex = 0;//从左往右第一个非空格字符的所在索引
		bool HeadsButton = true;
		int FinalIndex = 0;//从右往左第一个非空字符的所在索引
		bool FinalButton = true;
		//第一次扫描字符串，目的是为了确认此字符串从左到右首个非空格字符的索引
		for (size_t i1 = 0; i1 < strlen(TempStr) && HeadsButton; i1++)
		{
			int CharID1 = (int)TempStr[i1];
			if (CharID1 != 32)
			{
				HeadsButton = false;
				HeadIndex = i1;
			}
		}
		//第二次扫描字符串，目的是为了确认此字符串从右到左首个非空格字符的索引
		for (size_t i2 = strlen(TempStr) - 1; i2 >= 0 && FinalButton; i2--)
		{
			int CharID2 = (int)TempStr[i2];
			if (CharID2 != 32)
			{
				FinalButton = false;
				FinalIndex = i2;
			}
		}
		//cout << "从左到右首个非空格字符的索引号为：" << HeadIndex <<"字符为："<<TempStr[HeadIndex]<< endl;
		//cout << "从右到左首个非空格字符的索引号为：" << FinalIndex << "字符为：" << TempStr[FinalIndex] << endl;
		//cout << EnStr.substr(HeadIndex, FinalIndex+1) << endl;
		//cout << "|"<<EnStr.substr(HeadIndex, FinalIndex - HeadIndex)<<"|" << endl;
		string CutedStr = EnStr.substr(HeadIndex, FinalIndex - HeadIndex);//剪除字符串左右两端的空格
		//cout << CutedStr << "切割后的字符总数为：" << CutedStr.length() << endl;

		//如果是&zwnj;之类的HTML特殊字符串，则不做翻译<a name="bookmark1166">?(译为：＆zwnj;)</a>
		if (CutedStr.find("&") == 0 && CutedStr.find(";") == CutedStr.length() - 1)
		{
			//EnStr << CutedStr.substr(CutedStr.find("&") + 1, CutedStr.find(";") - 1) << endl;
			return false;

		}

		const char* CutedCharArr = CutedStr.c_str();
		for (size_t i3 = 0; i3 < strlen(CutedCharArr); i3++)
		{
			int CharID3 = (int)CutedCharArr[i3];
			//printf("字符串里：%c的索引号为：%d\n", CutedCharArr[i3], CharID3);

			//跳过所有字母来判断，判断非字母字符是否包含了_或-之外的字符，如果有那么就跳出
			if (!(CharID3 > 96 && CharID3 < 123) && !(CharID3>64 && CharID3 < 91))
			{
				if (CharID3 != 45 && CharID3 != 95)
				{
					/*
					if (CharID3 < 0)//如果包含了非ASCII码那么就认定为无需翻译的
					{
					return false;
					}
					*/
					if (CharID3 == 32)//一旦遇到空格即刻判断其是可以翻译的
					{
						//IsEable = true;
						//printf("ASCII码表的：%c的索引号为：%d\n", CutedCharArr[i3], CharID3);
						return true;
					}
				}
			}
		}
	}
	return IsEable;
}
