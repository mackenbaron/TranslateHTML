#include "WEBOptions.h"
#include "..\�ַ�����չ\StringEx.h"


//����ƶ�URL������״��
int CheckNetWork(string url)
{
	int NetWorkFlag = 0;//��������ǵĶ���
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




//���ַ�������URL����
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



//������ҳ�����ҳԴ��
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

//����ַ�����ת�����ܺ������쳣����������Զ��������ܣ����ֶ������ļ�����
string GeWebInfoEx(string url, int CharCodeFlag)
{
	string HTMLSource = "";
	string TempText = GeWebInfo(url);//�õ���ҳԴ��
	//cout << TempText << endl;
	//��һ���жϻ�ȡ��ҳԴ�������������ү��Դ������С��100��˵����ȡ�����쳣���������쳣�����Զ��ظ����β�ѯ
	if (TempText.length() < 100)
	{
		cout << "��ǰ�����쳣���޷���ȡ��ҳԴ��,�����쳣���ƣ������Զ��������Ρ���" << endl;
		//Sleep(1000);//��ʱ1sִ���쳣����
		size_t ReSetFlag1 = 3;
		//�жϵ�һ��ץȡ��ҳԴ�������������ȡ������������������
		while (ReSetFlag1 > 0)//��ȡ���Σ�������֮�ڣ�ֻҪMDResArr���Ȳ�Ϊ�㣬��������ѭ��
		{
			cout << "��ǰReSetFlagΪ" << ReSetFlag1 << endl;
			TempText = GeWebInfo(url);
			if (TempText.length() < 100)//���û��ץȡ����ҳԴ�룬��ѭ��
			{
				cout << "��" << (4 - ReSetFlag1) << "�λ�ȡ��ҳԴ��ʧ��" << endl;
				ReSetFlag1--;
			}
			else {//ȷ������С˵���ƺ󼴿�����ѭ����
				ReSetFlag1 = 0;
			}
		}
	}

	//�����������ƺ�������ǲ��У��򷵻������쳣��ʾ
	if (TempText.length() < 100)//���û��ץȡ����ҳԴ�룬��ѭ��
	{
		cout << "��ǰ�����쳣����ȡ��ҳԴ��ʧ��,�������硭��" << endl;
	}
	else {//��ȡ�ɹ������ؽ��
		//��ĳЩ�������Ҫ�����ַ�����
		switch (CharCodeFlag)
		{
		case 1:
		{
				  HTMLSource = TempText;
		}; break;
		case 2:
		{
				  HTMLSource = Convert(string(TempText), CP_UTF8, 936);//��UTF-8ת����GB2312����
		}; break;
		default:
			break;
		}
	}
	return HTMLSource;
}




//����ַ�����ת�����ܺ������쳣����������Զ��������ܣ��ַ������벻����
string GeWebInfoEx(string url)
{
	string HTMLSource = "";
	string TempText = GeWebInfo(url);//�õ���ҳԴ��
	//cout << TempText << endl;
	//��һ���жϻ�ȡ��ҳԴ�������������ү��Դ������С��100��˵����ȡ�����쳣���������쳣�����Զ��ظ����β�ѯ
	if (TempText.length() < 100)
	{
		cout << "��ǰ�����쳣���޷���ȡ��ҳԴ��,�����쳣���ƣ������Զ��������Ρ���" << endl;
		//Sleep(1000);//��ʱ1sִ���쳣����
		size_t ReSetFlag1 = 3;
		//�жϵ�һ��ץȡ��ҳԴ�������������ȡ������������������
		while (ReSetFlag1 > 0)//��ȡ���Σ�������֮�ڣ�ֻҪMDResArr���Ȳ�Ϊ�㣬��������ѭ��
		{
			cout << "��ǰReSetFlagΪ" << ReSetFlag1 << endl;
			TempText = GeWebInfo(url);
			if (TempText.length() < 100)//���û��ץȡ����ҳԴ�룬��ѭ��
			{
				cout << "��" << (4 - ReSetFlag1) << "�λ�ȡ��ҳԴ��ʧ��" << endl;
				ReSetFlag1--;
			}
			else {//ȷ������С˵���ƺ󼴿�����ѭ����
				ReSetFlag1 = 0;
			}
		}
	}

	//�����������ƺ�������ǲ��У��򷵻������쳣��ʾ
	if (TempText.length() < 100)//���û��ץȡ����ҳԴ�룬��ѭ��
	{
		cout << "��ǰ�����쳣����ȡ��ҳԴ��ʧ��,�������硭��" << endl;
	}
	else {//��ȡ�ɹ������ؽ��
		//��ĳЩ�������Ҫ�����ַ�����
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
		HTMLSource = Convert(string(TempText), CP_UTF8, 936);//��UTF-8ת����GB2312����
		}; break;
		default:
		break;
		}
		*/
	}
	return HTMLSource;
}



//�жϵ�ǰ�ַ����Ƿ��ǺϷ�URL
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
		//�����������Ҳ�ᱻ���϶�ΪURL�����ԣ�����ж��ַ������Ƿ����\\��Ϊ��������
		//string str = "NOTE: Input and output worlds with the same dimensions can use different ";
		if (strurl.length() > strurl.find("\\") && strurl.find("\\") > 0)
		{
			ReturnFlag = true;
		}
	}
	return ReturnFlag;
}