#ifndef __TRANSLATEEN_H
#define __TRANSLATEEN_H
#include <string>
using namespace std;
//谷歌翻译API应用
string QueryTranslateForGoogle(string SourceStr);

//有道翻译API应用
string QueryTranslateForYoudao(string SourceStr);

//必应翻译API应用
string QueryTranslateForBing(string SourceStr);

//手动选择翻译API
string TranslateEnStrByShoudong(string SourceStr, int APIFlag);

//根据实际情况自动选择可行的翻译API，优先级为谷歌、必应、有道
string TranslateEnStrByAuto(string SourceStr);

#endif



