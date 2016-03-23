#include "TranslateEN.h"
#include "..\网络操作\WEBOptions.h"
#include "..\字符串拓展\StringEx.h"



//谷歌翻译API应用
string QueryTranslateForGoogle(string SourceStr)
{
	URLCode(SourceStr);//对这个待翻译的字符串进行URL编码，至于翻译API其已经进行了URL编码了，这样一来，才能保证其能够正常翻译
	string Trans = "";//翻译结果
	string googleAPI = "http://translate.google.cn/translate_a/single?client=t&sl=en&tl=zh-CN&dt=t&ie=UTF-8&oe=UTF-8&otf=1&ssel=6&tsel=3&kc=14&tk=522876|17099&q=";//比较精简的翻译API，注意，>将会替换成\u003e
	string url = googleAPI + SourceStr;


#define _ISOPEN_GOOGLE 200

#if _ISOPEN_GOOGLE<100

	//调用GeWebInfoEx来获取网页源码，手动设置字符串编码方式
	//string tempstr = GeWebInfoEx(url, 2);
	//调用GeWebInfoEx来获取网页源码，不设置字符串编码方式
	string tempstr = GeWebInfoEx(url);
	Trans = SpliteString(tempstr, "[\"", "\",\"");//截取得到最终结果，直接截取google的翻译API
#elif _ISOPEN_GOOGLE>100&&_ISOPEN_GOOGLE<150
	HINTERNET hSession = InternetOpen(TEXT("UrlTest"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
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
				tempstr += Convert(string(Temp), CP_UTF8, 936);//将UTF-8转换成GB2312编码
			}
			//cout << tempstr << endl;
			//MessageBoxA(NULL, tempstr.c_str(), "信息", MB_OK);
			Trans = SpliteString(tempstr, "[\"", "\",\"");//截取得到最终结果，直接截取google的翻译API
			InternetCloseHandle(hHttp);
			hHttp = NULL;
		}
		InternetCloseHandle(hSession);
		hSession = NULL;
	}
#else 
	string GoogleURL = string("http://translate.google.cn/translate_t?q=") + SourceStr + string("&hl=zh-CN&langpair=en|zh-CN");
	//调用GeWebInfoEx来获取网页源码，手动设置字符串编码方式
	//string tempstr = GeWebInfoEx(GoogleURL, 1);
	//调用GeWebInfoEx来获取网页源码，不设置字符串编码方式
	string tempstr = GeWebInfoEx(GoogleURL);
	Trans = GetStrBySpliteString(tempstr, ";TRANSLATED_TEXT='", "';INPUT_TOOL_PATH=");

#endif
	return Trans;
}





//有道翻译API应用
string QueryTranslateForYoudao(string SourceStr)
{
	URLCode(SourceStr);//对这个待翻译的字符串进行URL编码，至于翻译API其已经进行了URL编码了，这样一来，才能保证其能够正常翻译
	string Trans = "";//翻译结果
	string youdaoAPI = "http://fanyi.youdao.com/openapi.do?keyfrom=chenqiushi&key=835334021&type=data&doctype=json&version=1.1&q=";
	string url = youdaoAPI + SourceStr;

#ifndef _ISOPEN_YOUDAO

	//调用GeWebInfoEx来获取网页源码，手动设置字符串编码方式
	//string tempstr = GeWebInfoEx(url, 2);
	//调用GeWebInfoEx来获取网页源码，不设置字符串编码方式
	string tempstr = GeWebInfoEx(url);

	Trans = GetStrBySpliteString(tempstr, "translation\":[\"", "\"],");//有道翻译API
#else

	HINTERNET hSession = InternetOpen(TEXT("UrlTest"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
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
				tempstr += Convert(string(Temp), CP_UTF8, 936);//将UTF-8转换成GB2312编码
			}
			//cout << tempstr << endl;
			//MessageBoxA(NULL, tempstr.c_str(),"信息",MB_OK);
			Trans = SpliteString(tempstr, "translation\":[\"", "\"],");//有道翻译API
			InternetCloseHandle(hHttp);
			hHttp = NULL;
		}
		InternetCloseHandle(hSession);
		hSession = NULL;
	}
#endif
	return Trans;
}




//必应翻译API应用
string QueryTranslateForBing(string SourceStr)
{
	URLCode(SourceStr);//对这个待翻译的字符串进行URL编码，至于翻译API其已经进行了URL编码了，这样一来，才能保证其能够正常翻译
	string Trans = "";//翻译结果
	//这里用到了必应API，也就是微软翻译API
	string url = string("http://api.microsofttranslator.com/v2/ajax.svc/TranslateArray2?appId=\"TU3t20HGaosm9bxLaoSpD5wU7oUrrX4xl7Hiy_RcKbp9qcRY7stT7Et66JRPN1vF4\"&texts=[\"") + SourceStr + string("\"]&from=\"\"&to=\"zh-CHS\"&options={}&oncomplete=onComplete_5&onerror=onError_5&_=1447944047998");

#ifndef _ISOPEN_BING

	//调用GeWebInfoEx来获取网页源码，手动设置字符串编码方式
	//string tempstr = GeWebInfoEx(url, 2);
	//调用GeWebInfoEx来获取网页源码，不设置字符串编码方式
	string tempstr = GeWebInfoEx(url);
	Trans = GetStrBySpliteString(tempstr, "TranslatedText\":\"", "\",\"Trans");//截取得到最终结果，直接截取google的翻译API
#else
	HINTERNET hSession = InternetOpen(TEXT("UrlTest"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
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
				tempstr += Convert(string(Temp), CP_UTF8, 936);//将UTF-8转换成GB2312编码
			}
			//cout << tempstr << endl;
			//MessageBoxA(NULL, tempstr.c_str(), "信息", MB_OK);
			//cout << "提取到的翻译结果为：" << SpliteString(tempstr, "[\"", "\",\"") << endl;
			Trans = SpliteString(tempstr, "TranslatedText\":\"", "\",\"Trans");//截取得到最终结果，直接截取google的翻译API
			InternetCloseHandle(hHttp);
			hHttp = NULL;
		}
		InternetCloseHandle(hSession);
		hSession = NULL;
	}
#endif
	return Trans;
}






//手动选择翻译API
string TranslateEnStrByShoudong(string SourceStr, int APIFlag)
{
	string trans = "";//存放翻译结果
	switch (APIFlag)
	{
	case 1:
	{
			  //MessageBoxA(NULL,"选择的是谷歌翻译","翻译API",MB_OK);
			  trans = QueryTranslateForGoogle(SourceStr);//谷歌翻译
	}; break;
	case 2:
	{
			  //MessageBoxA(NULL, "选择的是必应翻译", "翻译API", MB_OK);
			  trans = QueryTranslateForBing(SourceStr);//必应翻译
	}; break;
	case 3:
	{
			  //MessageBoxA(NULL, "选择的是有道翻译", "翻译API", MB_OK);
			  trans = QueryTranslateForYoudao(SourceStr);//有道翻译
	}; break;
	}

	return trans;
}




//根据实际情况自动选择可行的翻译API，优先级为谷歌、必应、有道
string TranslateEnStrByAuto(string SourceStr)
{
	if (IsAvailableURL(SourceStr))//判断字符串是否为合法的URL，如果是则直接返回源字符串
	{
		return SourceStr;
	}
	else
	{
		string TempStr = SourceStr;
		string trans = "";//存放翻译结果
		string IsNULL = "";//专门用来验证翻译结果除开那些特殊字符后，是否为空的标记
		for (int i = 1; i < 4 && string("") == IsNULL; i++)//遍历所有翻译API，一旦获得的翻译文本不为空时，即刻中断循环
		{
			string TempCodeStr = TranslateEnStrByShoudong(TempStr, i);
			//cout << "当前得到的翻译结果为：" <<TempCodeStr << endl;
			//如果检测到字符串是utf-8编码的，那么就执行转码操作
			if (IsUTF8String(trans.c_str(), trans.length()))
			{
				trans = Convert(TempCodeStr, 65001, 936);
			}
			else
			{
				trans = TempCodeStr;
			}

			IsNULL = trans;
			GlobalReStr(IsNULL, " ", "");
			GlobalReStr(IsNULL, "	", "");
			GlobalReStr(IsNULL, "？", "");
			GlobalReStr(IsNULL, "?", "");
			GlobalReStr(IsNULL, "\\r\\n", "");
		}



		if (string("") == trans)
		{
			//经过翻译API的查询后，所得返回数据依然为空，那么可以说明此剪贴板里的数据不是标准的英文字符串了
			//MessageBoxA(NULL, "查询异常，当前文本内容不是有效的英文语句或词汇，请缩小查询范围\n注意，此工具仅能翻译英文而已", "警告", MB_OK);
			trans = SourceStr;
			//ExitProcess(0);//终止进程
		}
		return trans;
	}
	//cout << "执行到这恶吏" << endl;

}
