#ifndef __TRANSLATEEN_H
#define __TRANSLATEEN_H
#include <string>
using namespace std;
//�ȸ跭��APIӦ��
string QueryTranslateForGoogle(string SourceStr);

//�е�����APIӦ��
string QueryTranslateForYoudao(string SourceStr);

//��Ӧ����APIӦ��
string QueryTranslateForBing(string SourceStr);

//�ֶ�ѡ����API
string TranslateEnStrByShoudong(string SourceStr, int APIFlag);

//����ʵ������Զ�ѡ����еķ���API�����ȼ�Ϊ�ȸ衢��Ӧ���е�
string TranslateEnStrByAuto(string SourceStr);

#endif



