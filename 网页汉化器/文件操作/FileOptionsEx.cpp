#include "FileOptionsEx.h"
#include "..\�ַ�����չ\StringEx.h"

//����ļ����벢�����ض�����ֵ���
int CheckFileCode(const char* str)
{
	int CodeTag = 0;
	FILE *rFile;
	string FileCodeFlag = "";
	//����VC 6.0
#if _MSC_VER<1400   //VS 2005�汾����            
	rFile = fopen(str, "r");
	if (rFile == NULL)
#else  //VS 2005�汾����
	errno_t Rerr = fopen_s(&rFile, str, "r");
	if (Rerr == 0)
#endif   
	{
		//char ch;
		int i = 0;
		char temp[10];
		while (!feof(rFile) && i<3)
		{
			//����VC 6.0
#if _MSC_VER<1400   //VS 2005�汾����            
			sprintf(temp, "%X", fgetc(rFile));
#else  //VS 2005�汾����
			sprintf_s(temp, "%X", fgetc(rFile));
#endif   
			FileCodeFlag += temp;
			//cout << temp << endl;
			//cout << fgetc(rFile) << endl;
			i++;
		}
		fclose(rFile);

		//cout << "�ļ�ͷΪ" << FileCodeFlag.find("FFFE") << endl;
		if (FileCodeFlag.find("FFFE") >= 0 && FileCodeFlag.find("FFFE") < strlen(FileCodeFlag.c_str()))
		{
			//cout << "���ļ���Unicode����" << endl;
			CodeTag = 1200;
		}
		else if (FileCodeFlag.find("FEFF") >= 0 && FileCodeFlag.find("FEFF") < strlen(FileCodeFlag.c_str()))
		{
			//cout << "���ļ���Unicode big endian����" << endl;
			CodeTag = 1201;
		}
		else if (FileCodeFlag.find("EFBBBF") >= 0 && FileCodeFlag.find("EFBBBF") < strlen(FileCodeFlag.c_str()))
		{
			//cout << "���ļ���UTF-8����" << endl;
			CodeTag = 65001;
		}
		else
		{
			//cout << "���ļ���ANSI��GB2312����" << endl;
			CodeTag = 936;
		}


	}
	else { cout << "���ļ�������" << endl; }
	return CodeTag;

}



//��ȡ�ļ��������
string ReadTextInFile(const char* FilePath)
{

	std::ifstream in(FilePath, std::ios::in | std::ios::binary);
	if (!in) {
		std::cout << "File " << FilePath << " not found!\n";
		exit(EXIT_FAILURE);
	}

	std::string contents;
	in.seekg(0, std::ios::end);
	contents.resize((size_t)in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(&contents[0], contents.size());
	in.close();
	//cout << contents << endl;
	return contents;
}




//���ı������һ���ļ�
bool CreateFileFromText(string TextInfo, const char* FilePath)
{
	bool IsOK = false;
	if (TextInfo.length() > 0)
	{
		FILE *wFile;
		//����VC 6.0
#if _MSC_VER<1400   //VS 2005�汾����            
		wFile = fopen(FilePath, "w");
		if (wFile == NULL)
#else  //VS 2005�汾����
		errno_t Werr = fopen_s(&wFile, FilePath, "w"); // ����һ���ļ�ָ��, ������fopen()��������һ���ļ�ָ��  
		if (Werr != 0)//�ļ��򿪳ɹ�
#endif   
		{
			IsOK = false;
			cout << "wFile��ʧ��" << endl;
		}
		else
		{
			fputs(TextInfo.c_str(), wFile);
			IsOK = true;
		}
		fclose(wFile);             // �ر��ļ�ָ���, �����������������ݽ�д�뵽������, һ�������, ���ļ�������Ϻ�, Ӧ�ر���Ӧ���ļ�ָ��  
	}
	return IsOK;
}




BOOL FileExists(LPCTSTR lpszFileName, BOOL bIsDirCheck)//�ú���ר�������ж�ĳ���ļ���Ŀ¼�Ƿ���ڵģ�����ڶ�������ΪTRUE������Ŀ¼�����ΪFALSE�������ļ�
{
	//��ͼȡ���ļ�����
	DWORD dwAttributes = ::GetFileAttributes(lpszFileName);
	
		//����VC 6.0
#if _MSC_VER<1400   //VS 2005�汾����            
	if (((DWORD)-1)== dwAttributes)//������VC 6.0�в�û�ж���INVALID_FILE_ATTRIBUTES������ʹ��ԭֵ
#else  //VS 2005�汾����
	if (INVALID_FILE_ATTRIBUTES == dwAttributes)
#endif   
	{
		return FALSE;
	}

	//��Ŀ¼
	if (dwAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		if (bIsDirCheck) //��ǰ����Ҳ��Ŀ¼
		{
			return TRUE;
		}
		else
			return FALSE;
	}
	else //���ļ�
	{
		if (bIsDirCheck)
		{
			return FALSE;
		}
		else
			return TRUE;
	}
}


//�������ֿ⣨�ļ����Ʊ�Ǽ��ϣ�������ָ��Ŀ¼�µ��ļ�
bool FindFilesByNameFlag(string SearchingMD, vector<string>& FindedFilesArrary, vector<string>& NameFlagLib)
{
	bool IsAvailable = false;
	//�ļ����  
	long   hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;//��Ҫ#include <io.h>
	string p;
	if ((hFile = _findfirst(p.assign(SearchingMD).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					//�������������õ�Ŀ¼��
					FindFilesByNameFlag(p.assign(SearchingMD).append("\\").append(fileinfo.name), FindedFilesArrary, NameFlagLib);
				}
			}
			else
			{
				//���������������ļ���
				if (FilterStr(p.assign(SearchingMD).append("\\").append(fileinfo.name), NameFlagLib, 2))
				{
					cout << "else:" << p.assign(SearchingMD).append("\\").append(fileinfo.name) << endl;
					FindedFilesArrary.push_back(p.assign(SearchingMD).append("\\").append(fileinfo.name));
				}
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	if (FindedFilesArrary.size() > 0)//��FindedFilesArrary��Ԫ�ش���1ʱ��˵��ȷʵ�ҵ��˷����������ļ�
	{
		IsAvailable = true;
	}
	return IsAvailable;
}




//��ȡ�ļ����������Ϣ
vector<string> GetArrInfoFromFile(const char* FilePath)
{
	ifstream ReadedFile;
	string info = "";
	vector<string> TextContext;
	ReadedFile.open(FilePath);
	if (!ReadedFile)
	{
		cout << "/*******************************���ļ�ʧ�ܣ�*********************************/";
	}
	else{
		while (getline(ReadedFile, info))//���ж�ȡ�ı��ļ�
		{

			//cout << info << endl;
			TextContext.push_back(info);
		}
	}
	ReadedFile.close();
	return TextContext;
}






//���ַ������鱣���һ���ļ�
bool CreateFileFromArrInfo(vector<string> ArrInfo, const char* FilePath)
{
	bool IsOK = false;
	vector<string> TextContext;
	ofstream WriteFile;
	WriteFile.open(FilePath);
	if (ArrInfo.size() > 0)
	{
		for (size_t n = 0; n < ArrInfo.size(); n++)
		{
			WriteFile << ArrInfo[n] << endl;
		}
		WriteFile.close();
		IsOK = true;
	}
	return IsOK;
}