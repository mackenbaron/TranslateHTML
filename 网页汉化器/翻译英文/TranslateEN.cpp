#include "TranslateEN.h"
#include "..\�������\WEBOptions.h"
#include "..\�ַ�����չ\StringEx.h"



//�ȸ跭��APIӦ��
string QueryTranslateForGoogle(string SourceStr)
{
	URLCode(SourceStr);//�������������ַ�������URL���룬���ڷ���API���Ѿ�������URL�����ˣ�����һ�������ܱ�֤���ܹ���������
	string Trans = "";//������
	string googleAPI = "http://translate.google.cn/translate_a/single?client=t&sl=en&tl=zh-CN&dt=t&ie=UTF-8&oe=UTF-8&otf=1&ssel=6&tsel=3&kc=14&tk=522876|17099&q=";//�ȽϾ���ķ���API��ע�⣬>�����滻��\u003e
	string url = googleAPI + SourceStr;


#define _ISOPEN_GOOGLE 200

#if _ISOPEN_GOOGLE<100

	//����GeWebInfoEx����ȡ��ҳԴ�룬�ֶ������ַ������뷽ʽ
	//string tempstr = GeWebInfoEx(url, 2);
	//����GeWebInfoEx����ȡ��ҳԴ�룬�������ַ������뷽ʽ
	string tempstr = GeWebInfoEx(url);
	Trans = SpliteString(tempstr, "[\"", "\",\"");//��ȡ�õ����ս����ֱ�ӽ�ȡgoogle�ķ���API
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
				tempstr += Convert(string(Temp), CP_UTF8, 936);//��UTF-8ת����GB2312����
			}
			//cout << tempstr << endl;
			//MessageBoxA(NULL, tempstr.c_str(), "��Ϣ", MB_OK);
			Trans = SpliteString(tempstr, "[\"", "\",\"");//��ȡ�õ����ս����ֱ�ӽ�ȡgoogle�ķ���API
			InternetCloseHandle(hHttp);
			hHttp = NULL;
		}
		InternetCloseHandle(hSession);
		hSession = NULL;
	}
#else 
	string GoogleURL = string("http://translate.google.cn/translate_t?q=") + SourceStr + string("&hl=zh-CN&langpair=en|zh-CN");
	//����GeWebInfoEx����ȡ��ҳԴ�룬�ֶ������ַ������뷽ʽ
	//string tempstr = GeWebInfoEx(GoogleURL, 1);
	//����GeWebInfoEx����ȡ��ҳԴ�룬�������ַ������뷽ʽ
	string tempstr = GeWebInfoEx(GoogleURL);
	Trans = GetStrBySpliteString(tempstr, ";TRANSLATED_TEXT='", "';INPUT_TOOL_PATH=");

#endif
	return Trans;
}





//�е�����APIӦ��
string QueryTranslateForYoudao(string SourceStr)
{
	URLCode(SourceStr);//�������������ַ�������URL���룬���ڷ���API���Ѿ�������URL�����ˣ�����һ�������ܱ�֤���ܹ���������
	string Trans = "";//������
	string youdaoAPI = "http://fanyi.youdao.com/openapi.do?keyfrom=chenqiushi&key=835334021&type=data&doctype=json&version=1.1&q=";
	string url = youdaoAPI + SourceStr;

#ifndef _ISOPEN_YOUDAO

	//����GeWebInfoEx����ȡ��ҳԴ�룬�ֶ������ַ������뷽ʽ
	//string tempstr = GeWebInfoEx(url, 2);
	//����GeWebInfoEx����ȡ��ҳԴ�룬�������ַ������뷽ʽ
	string tempstr = GeWebInfoEx(url);

	Trans = GetStrBySpliteString(tempstr, "translation\":[\"", "\"],");//�е�����API
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
				tempstr += Convert(string(Temp), CP_UTF8, 936);//��UTF-8ת����GB2312����
			}
			//cout << tempstr << endl;
			//MessageBoxA(NULL, tempstr.c_str(),"��Ϣ",MB_OK);
			Trans = SpliteString(tempstr, "translation\":[\"", "\"],");//�е�����API
			InternetCloseHandle(hHttp);
			hHttp = NULL;
		}
		InternetCloseHandle(hSession);
		hSession = NULL;
	}
#endif
	return Trans;
}




//��Ӧ����APIӦ��
string QueryTranslateForBing(string SourceStr)
{
	URLCode(SourceStr);//�������������ַ�������URL���룬���ڷ���API���Ѿ�������URL�����ˣ�����һ�������ܱ�֤���ܹ���������
	string Trans = "";//������
	//�����õ��˱�ӦAPI��Ҳ����΢����API
	string url = string("http://api.microsofttranslator.com/v2/ajax.svc/TranslateArray2?appId=\"TU3t20HGaosm9bxLaoSpD5wU7oUrrX4xl7Hiy_RcKbp9qcRY7stT7Et66JRPN1vF4\"&texts=[\"") + SourceStr + string("\"]&from=\"\"&to=\"zh-CHS\"&options={}&oncomplete=onComplete_5&onerror=onError_5&_=1447944047998");

#ifndef _ISOPEN_BING

	//����GeWebInfoEx����ȡ��ҳԴ�룬�ֶ������ַ������뷽ʽ
	//string tempstr = GeWebInfoEx(url, 2);
	//����GeWebInfoEx����ȡ��ҳԴ�룬�������ַ������뷽ʽ
	string tempstr = GeWebInfoEx(url);
	Trans = GetStrBySpliteString(tempstr, "TranslatedText\":\"", "\",\"Trans");//��ȡ�õ����ս����ֱ�ӽ�ȡgoogle�ķ���API
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
				tempstr += Convert(string(Temp), CP_UTF8, 936);//��UTF-8ת����GB2312����
			}
			//cout << tempstr << endl;
			//MessageBoxA(NULL, tempstr.c_str(), "��Ϣ", MB_OK);
			//cout << "��ȡ���ķ�����Ϊ��" << SpliteString(tempstr, "[\"", "\",\"") << endl;
			Trans = SpliteString(tempstr, "TranslatedText\":\"", "\",\"Trans");//��ȡ�õ����ս����ֱ�ӽ�ȡgoogle�ķ���API
			InternetCloseHandle(hHttp);
			hHttp = NULL;
		}
		InternetCloseHandle(hSession);
		hSession = NULL;
	}
#endif
	return Trans;
}






//�ֶ�ѡ����API
string TranslateEnStrByShoudong(string SourceStr, int APIFlag)
{
	string trans = "";//��ŷ�����
	switch (APIFlag)
	{
	case 1:
	{
			  //MessageBoxA(NULL,"ѡ����ǹȸ跭��","����API",MB_OK);
			  trans = QueryTranslateForGoogle(SourceStr);//�ȸ跭��
	}; break;
	case 2:
	{
			  //MessageBoxA(NULL, "ѡ����Ǳ�Ӧ����", "����API", MB_OK);
			  trans = QueryTranslateForBing(SourceStr);//��Ӧ����
	}; break;
	case 3:
	{
			  //MessageBoxA(NULL, "ѡ������е�����", "����API", MB_OK);
			  trans = QueryTranslateForYoudao(SourceStr);//�е�����
	}; break;
	}

	return trans;
}




//����ʵ������Զ�ѡ����еķ���API�����ȼ�Ϊ�ȸ衢��Ӧ���е�
string TranslateEnStrByAuto(string SourceStr)
{
	if (IsAvailableURL(SourceStr))//�ж��ַ����Ƿ�Ϊ�Ϸ���URL���������ֱ�ӷ���Դ�ַ���
	{
		return SourceStr;
	}
	else
	{
		string TempStr = SourceStr;
		string trans = "";//��ŷ�����
		string IsNULL = "";//ר��������֤������������Щ�����ַ����Ƿ�Ϊ�յı��
		for (int i = 1; i < 4 && string("") == IsNULL; i++)//�������з���API��һ����õķ����ı���Ϊ��ʱ�������ж�ѭ��
		{
			string TempCodeStr = TranslateEnStrByShoudong(TempStr, i);
			//cout << "��ǰ�õ��ķ�����Ϊ��" <<TempCodeStr << endl;
			//�����⵽�ַ�����utf-8����ģ���ô��ִ��ת�����
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
			GlobalReStr(IsNULL, "��", "");
			GlobalReStr(IsNULL, "?", "");
			GlobalReStr(IsNULL, "\\r\\n", "");
		}



		if (string("") == trans)
		{
			//��������API�Ĳ�ѯ�����÷���������ȻΪ�գ���ô����˵���˼�����������ݲ��Ǳ�׼��Ӣ���ַ�����
			//MessageBoxA(NULL, "��ѯ�쳣����ǰ�ı����ݲ�����Ч��Ӣ������ʻ㣬����С��ѯ��Χ\nע�⣬�˹��߽��ܷ���Ӣ�Ķ���", "����", MB_OK);
			trans = SourceStr;
			//ExitProcess(0);//��ֹ����
		}
		return trans;
	}
	//cout << "ִ�е������" << endl;

}
