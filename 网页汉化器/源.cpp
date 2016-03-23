#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include "htmlcxx\ParserDom.h"
#include "htmlcxx\Extensions.h"
#include "翻译英文\TranslateEN.h"
#include "字符串拓展\StringEx.h"
#include "网络操作\WEBOptions.h"
#include "文件操作\FileOptionsEx.h"
using namespace std;
using namespace htmlcxx;


//翻译指定标签里的文本节点，并将翻译结果更改到DOM树里
void TranslateHTMLContent(tree<HTML::Node> &dom)
{
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	for (; it != end; ++it)
	{
		if (MyExtension::IsAvailableTextNodeEx(it))
		{
			unsigned int SubNumInPreNode = ((tree<HTML::Node>)it.node->parent).begin().number_of_children();//父标签下的子节点个数
			const char* PreTagName = it.node->parent->data.tagName().c_str(); //文本标签的父标签

			string nonbreaking_inline = "|a|abbr|acronym|b|bdo|big|cite|code|dfn|em|font|i|img|kbd|nobr|s|small|span|strike|strong|sub|sup|tt|";
			string treat_like_inline = "|p|";
			//vector<string> FilterLIB = { "P", "DIV", "A", "H1", "H2", "H3", "H4","LI" };
			vector<string> nonbreaking_inlineLIB = htmlcxx::Extensions::GetArrBySpliteString(htmlcxx::Extensions::SmallCharToBigChar(nonbreaking_inline.c_str()), "|", "|");
			vector<string> treat_like_inlineLIB = htmlcxx::Extensions::GetArrBySpliteString(htmlcxx::Extensions::SmallCharToBigChar(treat_like_inline.c_str()), "|", "|");
			vector<string> FilterLIB;
			FilterLIB.insert(FilterLIB.begin(), nonbreaking_inlineLIB.begin(), nonbreaking_inlineLIB.end());
			FilterLIB.insert(FilterLIB.begin(), treat_like_inlineLIB.begin(), treat_like_inlineLIB.end());
			//执行相应翻译API来将其翻译
			if (htmlcxx::Extensions::FilterStr(htmlcxx::Extensions::SmallCharToBigChar(PreTagName), FilterLIB, 2))
			{
				string str = it->text();
				cout << str << endl;
				//自动跳过那些URL字符串和字母全为大写的专有名词
				if (!IsAvailableURL(str) && IsCanTranslateEx(str))
				{
					string TranslatedStr = TranslateEnStrByAuto(str);
					it->text(str + string("(译为：") + TranslatedStr + string(")"));
					cout << it->text() << endl;
				}

			}
		}
	}
	//cout << dom << endl;
}





//翻译指定标签里的文本节点，并将翻译结果更改到DOM树里，另外
void TranslateHTMLContentEx(tree<HTML::Node> &dom)
{
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	for (; it != end; ++it)
	{
		if (MyExtension::IsAvailableTextNodeEx(it))
		{
			///*
			unsigned int SubNumInPreNode = ((tree<HTML::Node>)it.node->parent).begin().number_of_children();//父标签下的子节点个数
			const char* PreTagName = it.node->parent->data.tagName().c_str(); //文本标签的父标签

			string nonbreaking_inline = "|a|abbr|acronym|b|bdo|big|cite|code|dfn|em|font|i|img|kbd|nobr|s|small|span|strike|strong|sub|sup|tt|";
			string treat_like_inline = "|p|";
			//vector<string> FilterLIB = { "P", "DIV", "A", "H1", "H2", "H3", "H4","LI" };
			vector<string> nonbreaking_inlineLIB = htmlcxx::Extensions::GetArrBySpliteString(htmlcxx::Extensions::SmallCharToBigChar(nonbreaking_inline.c_str()), "|", "|");
			vector<string> treat_like_inlineLIB = htmlcxx::Extensions::GetArrBySpliteString(htmlcxx::Extensions::SmallCharToBigChar(treat_like_inline.c_str()), "|", "|");
			vector<string> FilterLIB;
			FilterLIB.insert(FilterLIB.begin(), nonbreaking_inlineLIB.begin(), nonbreaking_inlineLIB.end());
			FilterLIB.insert(FilterLIB.begin(), treat_like_inlineLIB.begin(), treat_like_inlineLIB.end());
			//执行相应翻译API来将其翻译
			if (htmlcxx::Extensions::FilterStr(htmlcxx::Extensions::SmallCharToBigChar(PreTagName), FilterLIB, 2))
			{
				string str = it->text();
				cout << str << endl;
				//自动跳过那些URL字符串和字母全为大写的专有名词
				if (!IsAvailableURL(str) && IsCanTranslateEx(str) && str != string("&zwnj;"))
				{
					//vector<MyExtension::NodePropBase> ConditionLIB = { { "class", "s9" }, { "class", "s12" }, { "class", "s23" }, { "class", "h3" }, { "class", "nav" } };
					MyExtension::NodePropBase TempBase[]= { { "class", "s9" }, { "class", "s12" }, { "class", "s23" }, { "class", "h3" }, { "class", "nav" } };
					vector<MyExtension::NodePropBase> ConditionLIB(TempBase, TempBase + sizeof(TempBase) / sizeof(MyExtension::NodePropBase));

					if (!MyExtension::IsNeedTagNodeByNodeProp((tree<HTML::Node>)it.node->parent, ConditionLIB, MyExtension::PartMatching))
					{
						MyExtension::NodePropBase TempBase;
						if (MyExtension::GetPropValueByPropIndex(it.node->parent, 1, TempBase))
						{
							//cout << "第一个属性为为：" << TempBase.PropName << endl;
							//size_t index = TempBase.PropName.find("bookmark");//不翻译网页里的书签
							////if (TempBase.PropName != string("name") && TempBase.PropName != string("href"))
							//if (TempBase.PropName != string("name") && TempBase.PropName != string("href") && !(index<string("bookmark").length() && index >= 0))
							if (TempBase.PropName != string("href"))
							{
								string TranslatedStr = TranslateEnStrByAuto(str);
								it->text(str + string("(译为：") + TranslatedStr + string(")"));
								//it->text(TranslatedStr);
								cout << it->text() << endl;
							}
						}

						//cout << "其父节点为：" << it.node->parent->data.tagName() << endl;
						//cout << "输出父节点的所有标签：" << endl;
						//MyExtension::ShowPropInfoInNode(it.node->parent);
						////cout << HTML::unparseDom(it.node->parent) << endl;
						//cout << "这个是匹配属性的结果：" << endl << endl;
						//cout << it->text() << endl;
						//system("pause");
						//跳开AE插件里列表框里那些AE SDK特有的标记来翻译
						//string tempstr = it->text();
						//it->text(TranslateEnStrByAuto(tempstr));
						//cout << it->text() << endl;

					}



				}

			}
			//*/
		}
	}
	//cout << dom << endl;
}



//得到指定标签名的所有迭代器
vector<tree<HTML::Node>::iterator> GetIteratorByTagName(tree<HTML::Node> dom, std::string TagName)
{
	vector<tree<HTML::Node>::iterator> IteratorArr;
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	for (; it != end; ++it)
	{
		if (MyExtension::IsAvailableTagNode(it))
		{
			if (it->tagName() == TagName)
			{
				IteratorArr.push_back(it);
			}
		}
	}
	return IteratorArr;
}


//得到指定标签名的所有迭代器
//vector<tree<HTML::Node>::iterator_base> GetTagNodeByTagName(tree<HTML::Node> dom, std::string TagName)
//vector<tree_node_<HTML::Node>> GetTagNodeByTagName(tree<HTML::Node> dom, std::string TagName)
vector<tree<HTML::Node>> GetTagNodeByTagName(tree<HTML::Node> dom, std::string TagName)
{
	//vector<tree<HTML::Node>::iterator_base> TagNodeArr;
	vector<tree<HTML::Node>> TagNodeArr;
	//vector<tree_node_<HTML::Node>> TagNodeArr;
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	for (; it != end; ++it)
	{
		if (MyExtension::IsAvailableTagNode(it))
		{
			if (it->tagName() == TagName)
			{
				//tree<HTML::Node>::iterator_base afasf = it.node;
				tree_node_<HTML::Node> *af = it.node;
				//TagNodeArr.push_back(*it.node);
				//TagNodeArr.push_back(it.node);
				TagNodeArr.push_back((tree<HTML::Node>)it.node);
				//cout << HTML::unparseDom(af->data)<<endl;
				//TagNodeArr.push_back(it.node);
				//IteratorArr.push_back(it);
			}
		}
	}
	return TagNodeArr;
}


void GetTextNode(tree<HTML::Node> dom, vector<tree<HTML::Node>::iterator_base> &itArr)
{
	//vector<tree<HTML::Node>::iterator> itArr;
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	for (; it != end; ++it)
	{
		if (MyExtension::IsAvailableTextNode(it))
		{
			itArr.push_back(it);
			cout << it->text() << endl;
			//it->text("--------");
		}
	}
}





void main(int argc, char*argv[])
{
	if (argc != 2) {
		std::cout << "prettyprint <html filename>\n";
		//MyExtension::NodePropBase MyBase[] = { { "border", "0" }, { "align", "center" }, { "class", "acss" } };
		//cout << sizeof(MyBase) / sizeof(MyExtension::NodePropBase) << endl;
	}
	else
	{
		const char* filename = argv[1];
		string contents = ReadTextInFile(filename);
		HTML::ParserDom parser;

		tree<HTML::Node> dom;


		//根据字符串生成DOM树
		if (IsUTF8String(contents.c_str(), contents.length()))
		{
			dom = parser.parseTree(Convert(contents, 65001, 936));
		}
		else
		{
			dom = parser.parseTree(contents);
		}
		//cout << dom << endl;

		TranslateHTMLContentEx(dom);

		//保存修改后的html文件
		std::string str;
		HTML::unparseDom(dom.begin(), dom.end(), str);

		//cout << str << endl;
		string NewFileName = string(filename).substr(0, string(filename).rfind(".")) + string("(翻译后).htm");
		//cout << NewFileName << endl;
		CreateFileFromText(str.c_str(), NewFileName.c_str());

	}
	system("pause");
}

