#include "StringEx.h"

//Unicodeת��Ϊ���ֽ�
char* UnicodeToANSI(const wchar_t* wp)
{
	int len = WideCharToMultiByte(CP_ACP, 0, wp, wcslen(wp), NULL, 0, NULL, NULL);
	char* m_char = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, wp, wcslen(wp), m_char, len, NULL, NULL);
	m_char[len] = '\0';
	return m_char;
}

//���ֽ�ת��ΪUnicode
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
	transform(TempStr.begin(), TempStr.end(), TempStr.begin(), ::toupper);//������Сд��ĸת���ɴ�д
	return TempStr;
}

void SmallCharToBigChar(string &TempStr)
{
	transform(TempStr.begin(), TempStr.end(), TempStr.begin(), ::toupper);//������Сд��ĸת���ɴ�д
}



//ȫ���滻�ַ���
void GlobalReStr(string&   str, string old_value, string new_value)
{
	for (string::size_type pos(0); pos != string::npos; pos += new_value.length())   {
		if ((pos = str.find(old_value, pos)) != string::npos)
			str.replace(pos, old_value.length(), new_value);
		else   break;
	}
}




//SourceStr:���ָ���ַ���
//FirstFlag:�ָ����ʼ���
//FinalFlag:�ָ��ĩβ���
string GetStrBySpliteString(string SourceStr, string FirstFlag, string FinalFlag)
{
	int ROffset = 0;
	string SpliteResult = "";
	while (SourceStr.find(FirstFlag, ROffset) >= 0 && SourceStr.find(FirstFlag, ROffset) <= strlen(SourceStr.c_str()))
	{
		int findex = SourceStr.find(FirstFlag, ROffset);//�õ���ʼ���De����index
		int sindex = SourceStr.find(FinalFlag, findex + strlen(FirstFlag.c_str()));//�õ�ĩβ��ǵ�����index
		if (SourceStr.find(FinalFlag, findex + strlen(FirstFlag.c_str())) >= 0 && SourceStr.find(FinalFlag, findex + strlen(FirstFlag.c_str())) <= strlen(SourceStr.c_str()))
		{
			SpliteResult += SourceStr.substr(findex + strlen(FirstFlag.c_str()), sindex - findex - strlen(FirstFlag.c_str()));
		}
		ROffset = sindex;
	}
	return SpliteResult;
}



//SourceStr:���ָ���ַ���
//FirstFlag:�ָ����ʼ���
//FinalFlag:�ָ��ĩβ���
vector<string> GetArrBySpliteString(string SourceStr, string FirstFlag, string FinalFlag)
{
	int ROffset = 0;
	vector<string>SpliteResult;
	while (SourceStr.find(FirstFlag, ROffset) >= 0 && SourceStr.find(FirstFlag, ROffset) <= strlen(SourceStr.c_str()))
	{
		int findex = SourceStr.find(FirstFlag, ROffset);//�õ���ʼ���De����index
		int sindex = SourceStr.find(FinalFlag, findex + strlen(FirstFlag.c_str()));//�õ�ĩβ��ǵ�����index
		if (SourceStr.find(FinalFlag, findex + strlen(FirstFlag.c_str())) >= 0 && SourceStr.find(FinalFlag, findex + strlen(FirstFlag.c_str())) <= strlen(SourceStr.c_str()))
		{
			SpliteResult.push_back(SourceStr.substr(findex + strlen(FirstFlag.c_str()), sindex - findex - strlen(FirstFlag.c_str())));
		}
		ROffset = sindex;
	}
	return SpliteResult;
}




//UTF-8��ASCI��ת����
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


//�ж��ַ����Ƿ�����UTF-8�����
bool IsUTF8String(const char* str, int length)
{
	int i = 0;
	int nBytes = 0;//UTF8����1-6���ֽڱ���,ASCII��һ���ֽ�
	unsigned char chr = 0;
	bool bAllAscii = true;//���ȫ������ASCII,˵������UTF-8

	while (i < length)
	{
		chr = *(str + i);
		if ((chr & 0x80) != 0)
			bAllAscii = false;
		if (nBytes == 0)//�����ֽ���
		{
			if ((chr & 0x80) != 0)
			{
				while ((chr & 0x80) != 0)
				{
					chr <<= 1;
					nBytes++;
				}
				if (nBytes < 2 || nBytes > 6)
					return false;//��һ���ֽ�����Ϊ110x xxxx
				nBytes--;//��ȥ����ռ��һ���ֽ�
			}
		}
		else//���ֽڳ��˵�һ���ֽ���ʣ�µ��ֽ�
		{
			if ((chr & 0xc0) != 0x80)
				return false;//ʣ�µ��ֽڶ���10xx xxxx����ʽ
			nBytes--;
		}
		++i;
	}
	if (bAllAscii)
		return false;
	return nBytes == 0;
}



//�ж��ַ����Ƿ�����UTF-8����
BOOL IsTextUTF8(char* str, ULONGLONG length)
{
	DWORD nBytes = 0;//UFT8����1-6���ֽڱ���,ASCII��һ���ֽ�  
	UCHAR chr;
	BOOL bAllAscii = TRUE; //���ȫ������ASCII, ˵������UTF-8  
	for (int i = 0; i<length; ++i)
	{
		chr = *(str + i);
		if ((chr & 0x80) != 0) // �ж��Ƿ�ASCII����,�������,˵���п�����UTF-8,ASCII��7λ����,����һ���ֽڴ�,���λ���Ϊ0,o0xxxxxxx  
			bAllAscii = FALSE;
		if (nBytes == 0) //�������ASCII��,Ӧ���Ƕ��ֽڷ�,�����ֽ���  
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
		else //���ֽڷ��ķ����ֽ�,ӦΪ 10xxxxxx  
		{
			if ((chr & 0xC0) != 0x80)
				return FALSE;

			nBytes--;
		}
	}
	if (nBytes > 0) //Υ������  
		return FALSE;
	if (bAllAscii) //���ȫ������ASCII, ˵������UTF-8  
		return FALSE;

	return TRUE;
}



//�ַ���ת��������
int str2int(string string_temp)
{
	return atoi(string_temp.c_str());
}

//����ת�����ַ���
string int2str(int int_temp)
{
	char s[12];             //�趨12λ���ڴ洢32λintֵ�㹻  
#if _MSC_VER<1400   //VS 2005�汾����            
	itoa(int_temp, s, 10);
#else  //VS 2005�汾����
	_itoa_s(int_temp, s, 10); //itoa���������ʵ�֣���������C�к�������C++���Ƽ������ķ��������⣬����VS 2013�Ѿ���C�����׼�⺯�����¶�����һ�Σ����ԣ�itoa��VS 2013�оͱ����_itoa_s
#endif   

	return s;
}



//����һ���������ж�һ���ַ������Ƿ������֣���һ�������Ǵ��жϵ��ַ������ڶ������������ֿ�
bool FilterStr(string Str, vector<string>& FilterLib, int ModeFlag)
{
	int FilterCount = FilterLib.size();//���������Ԫ�صĸ���
	int MatchCount = 0;//����һ��ƥ�����������
	//����һ���������ж�
	bool ResultFlag = false;//���ʼ��Ϊ0(false)����ô˵������ַ�����û������
	switch (ModeFlag)
	{
	case 1://ȫ��ƥ�䱣��
	{
			   ModeFlag = FilterCount;
			   //�������FilterLibֻ���ڳ�ʼ��ʱ����֪����ֵ�ģ��������ﲻ�ܹ�ʹ��sizeof(FilterLib) / sizeof(FilterLib[1])�ķ�ʽ����ô�����ĸ���������Ԥ��ָ��������Ϊ������һ������������argc argv����
			   for (int i = 0; i < FilterCount&&MatchCount < ModeFlag; i++)//�������������ƣ�1.�������������ֿ�������ҵ�һ��ƥ������ֹ����ʡʱ��
			   {
				   //���ȣ�����ҵ���λ�ñ�Ǿ��Բ�������ַ��������ȣ����������ñض�����-1������Ӧ������Ϊ-1�ģ��������ڱ������ڱ���ʱ��ʱ��Ὣ���϶�Ϊ
				   //Str.find(FilterLib[i]) < strlen(Str.c_str()) ? cout << "Yes" << endl : cout << "No" << endl;
				   //Str.find(FilterLib[i])>-1 ? cout << "Yes" << endl : cout << "No" << endl;//ͨ������жϿ���֪������ʱ��-1�ᱻ�϶�Ϊ������ֵ���Դ���Ϊ�жϲ����ɿ�����>-1��Ϊ>=0����
				   //Str.find(FilterLib[i])>=0 ? cout << "Yes" << endl : cout << "No" << endl;//������ܹ��ܺõ�֤����
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
	case 2://����ƥ�䱣��
	{
			   ModeFlag = 1;
			   //�������FilterLibֻ���ڳ�ʼ��ʱ����֪����ֵ�ģ��������ﲻ�ܹ�ʹ��sizeof(FilterLib) / sizeof(FilterLib[1])�ķ�ʽ����ô�����ĸ���������Ԥ��ָ��������Ϊ������һ������������argc argv����
			   for (int i = 0; i < FilterCount&&MatchCount < ModeFlag; i++)//�������������ƣ�1.�������������ֿ�������ҵ�һ��ƥ������ֹ����ʡʱ��
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

//Unicode��/���ַ�����
wstring UT2WC(const char* buf)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, buf, -1, NULL, 0);
	std::vector<wchar_t> unicode(len);
	MultiByteToWideChar(CP_UTF8, 0, buf, -1, &unicode[0], len);
	return std::wstring(&unicode[0]);
}

//���ַ�����/Unicode��
std::string WC2UT(const wchar_t* buf)
{
	int len = WideCharToMultiByte(CP_UTF8, 0, buf, -1, NULL, 0, NULL, NULL);
	std::vector<char> utf8(len);
	WideCharToMultiByte(CP_UTF8, 0, buf, -1, &utf8[0], len, NULL, NULL);
	return std::string(&utf8[0]);
}


//ANSIת����UNICODE
std::wstring MB2WC(const char* buf)
{
	int len = MultiByteToWideChar(CP_ACP, 0, buf, -1, NULL, 0);
	std::vector<wchar_t> unicode(len);
	MultiByteToWideChar(CP_ACP, 0, buf, -1, &unicode[0], len);
	return std::wstring(&unicode[0]);
}


//UNICODEת����ANSI
std::string WC2MB(const wchar_t* buf)
{
	int len = WideCharToMultiByte(CP_ACP, 0, buf, -1, NULL, 0, NULL, NULL);
	std::vector<char> utf8(len);
	WideCharToMultiByte(CP_ACP, 0, buf, -1, &utf8[0], len, NULL, NULL);
	return std::string(&utf8[0]);
}



//���ַ�����ʮ��������ʽ���
string SourceStrToHexStr(string str, PrintType ShowType)
{
	const char *s = str.c_str();
	string HexStr = "";
	for (size_t i = 0; i<strlen(s); i++)
	{
		unsigned char TempChar = (unsigned char)s[i];//ȥ���ַ��ķ���λ
		char TempStr[5];//����ַ�ʮ�����Ƶ��ַ���
		//����VC 6.0
#if _MSC_VER<1400   //VS 2005�汾����            
		sprintf(TempStr, "%x", TempChar);//�����ֽڵ�ʮ�����ƴ�ŵ�TempStr��
#else  //VS 2005�汾����
		sprintf_s(TempStr, "%x", TempChar);//�����ֽڵ�ʮ�����ƴ�ŵ�TempStr��
#endif   
		HexStr += string("\\x") + TempStr;
		switch (ShowType)
		{
		case ShowOneChar:
		{
							//����VC 6.0
#if _MSC_VER<1400   //VS 2005�汾����            
							printf("�ֽڣ�\"%c \"��ʮ�������ַ�����Ϊ��%d\n", TempChar, strlen(TempStr));
							printf("\\x%s\n", TempStr);
#else  //VS 2005�汾����
							printf_s("�ֽڣ�\"%c \"��ʮ�������ַ�����Ϊ��%d\n", TempChar, strlen(TempStr));
							printf_s("\\x%s\n", TempStr);
#endif
		}; break;
		case ShowAllChar:
		{
							//����VC 6.0
#if _MSC_VER<1400   //VS 2005�汾����            
							printf("\\x%s", TempStr);
#else  //VS 2005�汾����
							printf_s("\\x%s", TempStr);
#endif   
		}; break;
		case ShowCharInfo:
		{
							 int CharID = (int)TempChar;
							 if (CharID > 126)
							 {
								 //printf("���ڴ��ַ�����ASCII����ڣ����Ի���%cc���ұ���Ӷ�һ���ո񣬱���������ASCII�ַ�ʱʱ��������\n",'%');
								 printf("����⣬���ִ��ַ��Ƿ�ASCII�룬����ȱ������һ�룬������ʾΪ%c ��\n���Ӧ��ʮ������Ϊ��%s�����Ӧ��ʮ����Ϊ��%d\n", TempChar, TempStr, CharID);
							 }
							 else
							 {
								 printf("%c��Ӧ��ʮ������Ϊ��%s�����Ӧ��ʮ����Ϊ��%d\n", TempChar, TempStr, CharID);
							 }

		}; break;
		}
		//printf("\\x%x", (unsigned char)s[i]);//����ʵ�ֽ����ֺ�ʮ�����ƽ��л�ת��ȥ������λ���������
		//printf("\\x%x", s[i]);//������ACSII��ͻᳬ���������ֽڣ��Ӷ����\xffffffe6\xffffff88֮������ݣ��������Ϊchar �ķ���λ����ʱ�ų��ֵ�
		//printf("0x%x", s[i]);
	}
	return HexStr;
}


//���ַ�����ʮ��������ʽ���
string SourceStrToHexStr(string SourceStr, string HexFlag)
{
	const char *s = SourceStr.c_str();
	string HexStr = "";//��Ŵ��ַ�����ʮ���������ݽ��
	//����ֽڶ�ȡ�ַ���
	for (size_t i = 0; i<strlen(s); i++)
	{
		unsigned char TempChar = (unsigned char)s[i];//ȥ���ֽڵķ���λ
		char TempStr[3];//����ֽڵ�ʮ��������ʽ���ַ�����3֮��
		//����VC 6.0
#if _MSC_VER<1400   //VS 2005�汾����            
		sprintf(TempStr, "%x", TempChar);//�����ֽڵ�ʮ�����ƴ�ŵ�TempStr��
#else  //VS 2005�汾����
		sprintf_s(TempStr, "%x", TempChar);//�����ֽڵ�ʮ�����ƴ�ŵ�TempStr��
#endif   
		HexStr += HexFlag + TempStr;//����HexFlagΪ\x����洢��ʮ������������ʽΪ\xc0\xad\xbe\xab
	}
	return HexStr;
}



//�жϵ�ǰ�ַ����Ƿ�ȫΪ���֣����˸���������ź���ж�Ŷ
bool IsNumberStr(string str)
{
	bool bIsDigit = true;
	GlobalReStr(str, ".", "");
	GlobalReStr(str, "-", "");
	GlobalReStr(str, "+", "");
	GlobalReStr(str, "*", "");
	GlobalReStr(str, "/", "");
	int nCount = str.length(); // ����ַ�����
	for (int i = 0; i < nCount; i++)
	{
		if (0 == isdigit(str.at(i))) // �������־��ñ�־λ
		{
			bIsDigit = false;
			return false;// �˳�
		}
	}
	return bIsDigit;
}



//��ʾ�ַ�����������ַ�
void ShowSpecialChars(string str)
{
	//ע�⣺�˺�������֧��ANSI�룬һ��������ANSI�뽫�����
	//ShowSpecialChars("\x0d");
	//ShowSpecialChars("\r");

	//ShowSpecialChars("\x0a");
	//ShowSpecialChars("\n");

	//ShowSpecialChars("\x20");//�ո�
	//ShowSpecialChars(" ");//�ո�

	const char *s = str.c_str();
	size_t i;
	printf("%s\n", s);
	for (i = 0; i<strlen(s); i++)
	{
		if (ispunct(s[i])) printf("^");
		//else printf("���ַ�����Ϊ��%c����ʮ������Ϊ%x", s[i], s[i]); 
		else printf("%x", s[i]);
	}
}



//���ASCII���
void PrintASCIIList()
{
	printf("ASCII�������ڷ�Χ��ʮ�����µ�0-126��ʮ�������µ�0-7e\n");
	//�������ASCII���
	for (size_t x = 0; x < 127; x++)
	{
		printf("%c", (unsigned char)x);
		//printf("%c\n", (unsigned char)x);
	}
	printf("\n");
}



//��ʮ��������ֵת��Ϊʮ����
//�˺������޸�int ChangeNum(CString str,int length)���ã�ԭ����ʹ����MFC���CString������ĳ���string
//��Դ�ڣ���ʮ�������ַ���ת��Ϊʮ������ֵ��http://blog.csdn.net/xhao014/article/details/6598672
int HexStrToInt(string HexStr)
{
	int length = HexStr.length();
	const char *revstr = HexStr.c_str();  //����ʮ�������ַ����ĳ��ȣ�����ע�����鲻ҪԽ��   
	int   num[16] = { 0 };
	int   count = 1;
	int   result = 0;
	for (int i = length - 1; i >= 0; i--)
	{
		if ((revstr[i] >= '0') && (revstr[i] <= '9'))
			num[i] = revstr[i] - 48;//�ַ�0��ASCIIֵΪ48   
		else if ((revstr[i] >= 'a') && (revstr[i] <= 'f'))
			num[i] = revstr[i] - 'a' + 10;
		else if ((revstr[i] >= 'A') && (revstr[i] <= 'F'))
			num[i] = revstr[i] - 'A' + 10;
		else
			num[i] = 0;
		result = result + num[i] * count;
		count = count * 16;//ʮ������(����ǰ˽��ƾ����������8)       
	}
	return result;
}


//��ʮ�������ַ���ת��Ϊ����Ӧ��Դ�ַ���
string HexStrToSourceStr(string HexStr, string CutFlag)
{
	string SourceStr = "";
	char TempStr[3];//����ֽڵ�ʮ��������ʽ���ַ�����3֮��
	HexStr += CutFlag;
	vector<string> CharLIB = GetArrBySpliteString(HexStr, CutFlag, CutFlag);
	for (size_t i = 0; i < CharLIB.size(); i++)
	{
		//����VC 6.0
#if _MSC_VER<1400   //VS 2005�汾����            
		//printf("%c",(unsigned char)HexStrToInt(CharLIB[i]));
		sprintf(TempStr, "%c", (unsigned char)HexStrToInt(CharLIB[i]));
#else  //VS 2005�汾����
		//printf_s("%c",(unsigned char)HexStrToInt(CharLIB[i]));
		sprintf_s(TempStr, "%c", (unsigned char)HexStrToInt(CharLIB[i]));
#endif   
		SourceStr += TempStr;
	}
	return SourceStr;
}



//�ж��Ƿ�ȫΪ��д��ĸ����������ĸ�����жϣ�����������������ĸ�ַ���
bool IsAllBigEn(string EnStr)
{
	const char* TempStr = EnStr.c_str();
	bool IsAll = true;
	char CharNum[5];//�ֽڵĶ�Ӧ�����������λ��
	for (size_t i = 0; i < strlen(TempStr); i++)
	{
		//����VC 6.0
#if _MSC_VER<1400   //VS 2005�汾����            
		sprintf(CharNum, "%d\n", (int)TempStr[i]);
#else  //VS 2005�汾����
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




//�жϵ�ǰ�ַ����Ƿ������ASCII�ַ�
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




//�жϵ�ǰ�ַ����Ƿ���Ҫ����
bool IsCanTranslateEx(string EnStr)
{
	if (IsAllBigEn(EnStr))//�����ĸȫ��Ϊ��д��ֱ���϶�Ϊ���跭��
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
		int HeadIndex = 0;//�������ҵ�һ���ǿո��ַ�����������
		bool HeadsButton = true;
		int FinalIndex = 0;//���������һ���ǿ��ַ�����������
		bool FinalButton = true;
		//��һ��ɨ���ַ�����Ŀ����Ϊ��ȷ�ϴ��ַ����������׸��ǿո��ַ�������
		for (size_t i1 = 0; i1 < strlen(TempStr) && HeadsButton; i1++)
		{
			int CharID1 = (int)TempStr[i1];
			if (CharID1 != 32)
			{
				HeadsButton = false;
				HeadIndex = i1;
			}
		}
		//�ڶ���ɨ���ַ�����Ŀ����Ϊ��ȷ�ϴ��ַ������ҵ����׸��ǿո��ַ�������
		for (size_t i2 = strlen(TempStr) - 1; i2 >= 0 && FinalButton; i2--)
		{
			int CharID2 = (int)TempStr[i2];
			if (CharID2 != 32)
			{
				FinalButton = false;
				FinalIndex = i2;
			}
		}
		//cout << "�������׸��ǿո��ַ���������Ϊ��" << HeadIndex <<"�ַ�Ϊ��"<<TempStr[HeadIndex]<< endl;
		//cout << "���ҵ����׸��ǿո��ַ���������Ϊ��" << FinalIndex << "�ַ�Ϊ��" << TempStr[FinalIndex] << endl;
		//cout << EnStr.substr(HeadIndex, FinalIndex+1) << endl;
		//cout << "|"<<EnStr.substr(HeadIndex, FinalIndex - HeadIndex)<<"|" << endl;
		string CutedStr = EnStr.substr(HeadIndex, FinalIndex - HeadIndex);//�����ַ����������˵Ŀո�
		//cout << CutedStr << "�и����ַ�����Ϊ��" << CutedStr.length() << endl;

		//�����&zwnj;֮���HTML�����ַ�������������<a name="bookmark1166">?(��Ϊ����zwnj;)</a>
		if (CutedStr.find("&") == 0 && CutedStr.find(";") == CutedStr.length() - 1)
		{
			//EnStr << CutedStr.substr(CutedStr.find("&") + 1, CutedStr.find(";") - 1) << endl;
			return false;

		}

		const char* CutedCharArr = CutedStr.c_str();
		for (size_t i3 = 0; i3 < strlen(CutedCharArr); i3++)
		{
			int CharID3 = (int)CutedCharArr[i3];
			//printf("�ַ����%c��������Ϊ��%d\n", CutedCharArr[i3], CharID3);

			//����������ĸ���жϣ��жϷ���ĸ�ַ��Ƿ������_��-֮����ַ����������ô������
			if (!(CharID3 > 96 && CharID3 < 123) && !(CharID3>64 && CharID3 < 91))
			{
				if (CharID3 != 45 && CharID3 != 95)
				{
					/*
					if (CharID3 < 0)//��������˷�ASCII����ô���϶�Ϊ���跭���
					{
					return false;
					}
					*/
					if (CharID3 == 32)//һ�������ո񼴿��ж����ǿ��Է����
					{
						//IsEable = true;
						//printf("ASCII���ģ�%c��������Ϊ��%d\n", CutedCharArr[i3], CharID3);
						return true;
					}
				}
			}
		}
	}
	return IsEable;
}
