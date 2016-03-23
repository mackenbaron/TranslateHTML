#include "WEBOptions.h"
#include "..\字符串拓展\StringEx.h"


//检测制定URL的网络状况
int CheckNetWork(string url)
{
	int NetWorkFlag = 0;//存放网络标记的东西
	HINTERNET hSession = InternetOpen(TEXT("UrlTest"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hSession != NULL)
	{
		HINTERNET hHttp = InternetOpenUrlA(hSession, url.c_str(), NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
		if (hHttp != NULL)
		{
			NetWorkFlag = 1;
		}
	}
	return NetWorkFlag;
}




//对字符串进行URL编码
void URLCode(string &str_source)
{
	const char *in_str = str_source.c_str();
	int in_str_len = strlen(in_str);
	int out_str_len = 0;
	string out_str;
	register unsigned char c;
	unsigned char *to, *start;
	unsigned char const *from, *end;
	unsigned char hexchars[] = "0123456789ABCDEF";

	from = (unsigned char *)in_str;
	end = (unsigned char *)in_str + in_str_len;
	start = to = (unsigned char *)malloc(3 * in_str_len + 1);

	while (from < end) {
		c = *from++;

		if (c == ' ') {
			*to++ = '+';
		}
		else if ((c < '0' && c != '-' && c != '.') ||
			(c < 'A' && c > '9') ||
			(c > 'Z' && c < 'a' && c != '_') ||
			(c > 'z')) {
			to[0] = '%';
			to[1] = hexchars[c >> 4];
			to[2] = hexchars[c & 15];
			to += 3;
		}
		else {
			*to++ = c;
		}
	}
	*to = 0;
	out_str_len = to - start;
	out_str = (char *)start;
	free(start);
	//return out_str;
	str_source = out_str;
}



//扒下网页里的网页源码
string GeWebInfo(string url)
{
	string ReturnStr = "";
	HINTERNET hSession = InternetOpen(_T("UrlTest"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hSession != NULL)
	{
		HINTERNET hHttp = InternetOpenUrlA(hSession, url.c_str(), NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);

		if (hHttp != NULL)
		{
			char Temp[MAXSIZE];
			ULONG Number = 1;
			string tempstr = "";
			while (Number > 0)
			{
				InternetReadFile(hHttp, Temp, MAXSIZE - 1, &Number);
				//cout << Temp << endl;
				Temp[Number] = '\0';
				tempstr += Temp;
			}
			//cout << tempstr << endl;
			ReturnStr = tempstr;
			InternetCloseHandle(hHttp);
			hHttp = NULL;
		}
		InternetCloseHandle(hSession);
		hSession = NULL;
	}
	return ReturnStr;
}

//添加字符编码转换功能和网络异常情况下三次自动重连功能，和手动设置文件编码
string GeWebInfoEx(string url, int CharCodeFlag)
{
	string HTMLSource = "";
	string TempText = GeWebInfo(url);//得到网页源码
	//cout << TempText << endl;
	//第一次判断获取网页源码的情况，如果王爷额源码字数小于100，说明获取网络异常，则启动异常机制自动重复三次查询
	if (TempText.length() < 100)
	{
		cout << "当前网络异常，无法获取网页源码,启动异常机制，将会自动重连三次……" << endl;
		//Sleep(1000);//延时1s执行异常机制
		size_t ReSetFlag1 = 3;
		//判断第一次抓取网页源码的情况，如果获取不妙则启动重连机制
		while (ReSetFlag1 > 0)//获取三次，在三次之内，只要MDResArr长度不为零，即可跳出循环
		{
			cout << "当前ReSetFlag为" << ReSetFlag1 << endl;
			TempText = GeWebInfo(url);
			if (TempText.length() < 100)//如果没有抓取到网页源码，则循环
			{
				cout << "第" << (4 - ReSetFlag1) << "次获取网页源码失败" << endl;
				ReSetFlag1--;
			}
			else {//确定扒下小说名称后即可跳出循环了
				ReSetFlag1 = 0;
			}
		}
	}

	//经过重连机制后，如果还是不行，则返回网络异常提示
	if (TempText.length() < 100)//如果没有抓取到网页源码，则循环
	{
		cout << "当前网络异常，获取网页源码失败,请检查网络……" << endl;
	}
	else {//获取成功，返回结果
		//在某些情况下需要进行字符编码
		switch (CharCodeFlag)
		{
		case 1:
		{
				  HTMLSource = TempText;
		}; break;
		case 2:
		{
				  HTMLSource = Convert(string(TempText), CP_UTF8, 936);//将UTF-8转换成GB2312编码
		}; break;
		default:
			break;
		}
	}
	return HTMLSource;
}




//添加字符编码转换功能和网络异常情况下三次自动重连功能，字符串编码不更改
string GeWebInfoEx(string url)
{
	string HTMLSource = "";
	string TempText = GeWebInfo(url);//得到网页源码
	//cout << TempText << endl;
	//第一次判断获取网页源码的情况，如果王爷额源码字数小于100，说明获取网络异常，则启动异常机制自动重复三次查询
	if (TempText.length() < 100)
	{
		cout << "当前网络异常，无法获取网页源码,启动异常机制，将会自动重连三次……" << endl;
		//Sleep(1000);//延时1s执行异常机制
		size_t ReSetFlag1 = 3;
		//判断第一次抓取网页源码的情况，如果获取不妙则启动重连机制
		while (ReSetFlag1 > 0)//获取三次，在三次之内，只要MDResArr长度不为零，即可跳出循环
		{
			cout << "当前ReSetFlag为" << ReSetFlag1 << endl;
			TempText = GeWebInfo(url);
			if (TempText.length() < 100)//如果没有抓取到网页源码，则循环
			{
				cout << "第" << (4 - ReSetFlag1) << "次获取网页源码失败" << endl;
				ReSetFlag1--;
			}
			else {//确定扒下小说名称后即可跳出循环了
				ReSetFlag1 = 0;
			}
		}
	}

	//经过重连机制后，如果还是不行，则返回网络异常提示
	if (TempText.length() < 100)//如果没有抓取到网页源码，则循环
	{
		cout << "当前网络异常，获取网页源码失败,请检查网络……" << endl;
	}
	else {//获取成功，返回结果
		//在某些情况下需要进行字符编码
		/*
		switch (CharCodeFlag)
		{
		case 1:
		{
		*/
		HTMLSource = TempText;
		/*
		}; break;
		case 2:
		{
		HTMLSource = Convert(string(TempText), CP_UTF8, 936);//将UTF-8转换成GB2312编码
		}; break;
		default:
		break;
		}
		*/
	}
	return HTMLSource;
}



//判断当前字符串是否是合法URL
bool IsAvailableURL(_TCHAR* strurl)
{
	bool ReturnFlag = false;
	int retval = PathIsURL(strurl);
	if (retval == 1)
	{
		ReturnFlag = true;
	}
	return ReturnFlag;
}

bool IsAvailableURL(string strurl)
{
	bool ReturnFlag = false;
	int retval = PathIsURLA(strurl.c_str());
	if (retval == 1)
	{
		//由于下面这句也会被它认定为URL，所以，添加判断字符串里是否包含\\作为修正方法
		//string str = "NOTE: Input and output worlds with the same dimensions can use different ";
		if (strurl.length() > strurl.find("\\") && strurl.find("\\") > 0)
		{
			ReturnFlag = true;
		}
	}
	return ReturnFlag;
}