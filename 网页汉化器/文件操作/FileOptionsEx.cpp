#include "FileOptionsEx.h"
#include "..\字符串拓展\StringEx.h"

//检测文件编码并返回特定的数值标记
int CheckFileCode(const char* str)
{
	int CodeTag = 0;
	FILE *rFile;
	string FileCodeFlag = "";
	//兼容VC 6.0
#if _MSC_VER<1400   //VS 2005版本以下            
	rFile = fopen(str, "r");
	if (rFile == NULL)
#else  //VS 2005版本以上
	errno_t Rerr = fopen_s(&rFile, str, "r");
	if (Rerr == 0)
#endif   
	{
		//char ch;
		int i = 0;
		char temp[10];
		while (!feof(rFile) && i<3)
		{
			//兼容VC 6.0
#if _MSC_VER<1400   //VS 2005版本以下            
			sprintf(temp, "%X", fgetc(rFile));
#else  //VS 2005版本以上
			sprintf_s(temp, "%X", fgetc(rFile));
#endif   
			FileCodeFlag += temp;
			//cout << temp << endl;
			//cout << fgetc(rFile) << endl;
			i++;
		}
		fclose(rFile);

		//cout << "文件头为" << FileCodeFlag.find("FFFE") << endl;
		if (FileCodeFlag.find("FFFE") >= 0 && FileCodeFlag.find("FFFE") < strlen(FileCodeFlag.c_str()))
		{
			//cout << "此文件是Unicode编码" << endl;
			CodeTag = 1200;
		}
		else if (FileCodeFlag.find("FEFF") >= 0 && FileCodeFlag.find("FEFF") < strlen(FileCodeFlag.c_str()))
		{
			//cout << "此文件是Unicode big endian编码" << endl;
			CodeTag = 1201;
		}
		else if (FileCodeFlag.find("EFBBBF") >= 0 && FileCodeFlag.find("EFBBBF") < strlen(FileCodeFlag.c_str()))
		{
			//cout << "此文件是UTF-8编码" << endl;
			CodeTag = 65001;
		}
		else
		{
			//cout << "此文件是ANSI或GB2312编码" << endl;
			CodeTag = 936;
		}


	}
	else { cout << "此文件不存在" << endl; }
	return CodeTag;

}



//读取文件里的内容
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




//将文本保存成一个文件
bool CreateFileFromText(string TextInfo, const char* FilePath)
{
	bool IsOK = false;
	if (TextInfo.length() > 0)
	{
		FILE *wFile;
		//兼容VC 6.0
#if _MSC_VER<1400   //VS 2005版本以下            
		wFile = fopen(FilePath, "w");
		if (wFile == NULL)
#else  //VS 2005版本以上
		errno_t Werr = fopen_s(&wFile, FilePath, "w"); // 定义一个文件指针, 并调用fopen()函数返回一个文件指针  
		if (Werr != 0)//文件打开成功
#endif   
		{
			IsOK = false;
			cout << "wFile打开失败" << endl;
		}
		else
		{
			fputs(TextInfo.c_str(), wFile);
			IsOK = true;
		}
		fclose(wFile);             // 关闭文件指针后, 输入流缓冲区的数据将写入到磁盘中, 一般情况下, 对文件操作完毕后, 应关闭相应的文件指针  
	}
	return IsOK;
}




BOOL FileExists(LPCTSTR lpszFileName, BOOL bIsDirCheck)//该函数专门用来判断某个文件或目录是否存在的，如果第二个参数为TRUE，则检测目录，如果为FALSE，则检测文件
{
	//试图取得文件属性
	DWORD dwAttributes = ::GetFileAttributes(lpszFileName);
	
		//兼容VC 6.0
#if _MSC_VER<1400   //VS 2005版本以下            
	if (((DWORD)-1)== dwAttributes)//由于在VC 6.0中并没有定义INVALID_FILE_ATTRIBUTES，所以使用原值
#else  //VS 2005版本以上
	if (INVALID_FILE_ATTRIBUTES == dwAttributes)
#endif   
	{
		return FALSE;
	}

	//是目录
	if (dwAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		if (bIsDirCheck) //当前检测的也是目录
		{
			return TRUE;
		}
		else
			return FALSE;
	}
	else //是文件
	{
		if (bIsDirCheck)
		{
			return FALSE;
		}
		else
			return TRUE;
	}
}


//根据脏字库（文件名称标记集合）来查找指定目录下的文件
bool FindFilesByNameFlag(string SearchingMD, vector<string>& FindedFilesArrary, vector<string>& NameFlagLib)
{
	bool IsAvailable = false;
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;//需要#include <io.h>
	string p;
	if ((hFile = _findfirst(p.assign(SearchingMD).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					//这里获得搜索所得的目录名
					FindFilesByNameFlag(p.assign(SearchingMD).append("\\").append(fileinfo.name), FindedFilesArrary, NameFlagLib);
				}
			}
			else
			{
				//这里获得搜索到的文件名
				if (FilterStr(p.assign(SearchingMD).append("\\").append(fileinfo.name), NameFlagLib, 2))
				{
					cout << "else:" << p.assign(SearchingMD).append("\\").append(fileinfo.name) << endl;
					FindedFilesArrary.push_back(p.assign(SearchingMD).append("\\").append(fileinfo.name));
				}
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	if (FindedFilesArrary.size() > 0)//当FindedFilesArrary的元素大于1时，说明确实找到了符合条件的文件
	{
		IsAvailable = true;
	}
	return IsAvailable;
}




//获取文件里的逐行信息
vector<string> GetArrInfoFromFile(const char* FilePath)
{
	ifstream ReadedFile;
	string info = "";
	vector<string> TextContext;
	ReadedFile.open(FilePath);
	if (!ReadedFile)
	{
		cout << "/*******************************打开文件失败！*********************************/";
	}
	else{
		while (getline(ReadedFile, info))//逐行读取文本文件
		{

			//cout << info << endl;
			TextContext.push_back(info);
		}
	}
	ReadedFile.close();
	return TextContext;
}






//将字符串数组保存成一个文件
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