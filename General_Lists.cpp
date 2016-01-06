

/**************************
 *������Ƿ����ԵĽṹ�������Ա��һ����չ������n��Ԫ������������С�
 *�����Ķ����ǵݹ�ģ���Ϊ�ڱ���������ֵõ��˱���������б�
 *----------<1> A = ()
 *----------<2> B = (a,b)
 *----------<3> C = (a,b,(c,d))
 *----------<4> D = (a,b,(c,d),(e,(f),h)) 
 *----------<5> E = (((),()))
 *
 *�����Ļ���������
 *----------���������
 *----------���������
 *----------���������
 *----------������Ľڵ���������ȡ����
 **************************/

#include <iostream>
using namespace std;

enum NodeType
{
	HeadType,  //ͷ�ڵ�
	ValueType, //ֵ�ڵ�
	SubType,   //�ӱ�ڵ�
};
struct GeneralNode
{
	GeneralNode* _next;
	NodeType _type;  //���������ʱ��֪���ýڵ��Ǻνڵ�
	union
	{//Ҫ��ֵ�ڵ㣬Ҫ���ӱ�ڵ�
		char _value;
		GeneralNode* _sublink;
	};

	GeneralNode(NodeType type,char value = '\0')
		:_next(NULL)
		, _type(type)
	{
		if (_type == SubType)
		{
			_sublink = NULL;
		}
		else if (_type == ValueType)
		{
			_value = value;
		}
	}
};
class GeneralLists
{
public:
	GeneralLists(const char* str)         //���캯��
		:_Link(NULL)
	{
		_GreadList(_Link, str);//���������
	}
	GeneralLists(const GeneralLists& g)   //�������캯��
		:_Link(NULL)
	{
		//DiList(_Link,g._Link);
		_Link = DiList(g._Link);
	}
	void DiList(GeneralNode*& link, GeneralNode* gbegin)//����
	{
		GeneralNode* begin = link;
		while (gbegin)
		{
			if (gbegin->_type == HeadType)
			{
				GeneralNode* HeadNode = new GeneralNode(HeadType);//����ͷ�ڵ�
				link = HeadNode;
				begin = link;
			}
			if (gbegin->_type == ValueType)   //ֵ�ڵ�
			{
				begin->_next = new GeneralNode(ValueType, gbegin->_value);
				begin = begin->_next;
			}
			if (gbegin->_type == SubType)     //�ӱ�ڵ�
			{
				begin->_next = new GeneralNode(SubType);
				begin = begin->_next;
				DiList(begin->_sublink, gbegin->_sublink);
			}
			gbegin = gbegin->_next;
		}
	}
	GeneralNode* DiList(GeneralNode* gbegin)//�Է���ֵ����ʽ
	{
		GeneralNode* HeadNode = new GeneralNode(HeadType);//����ͷ�ڵ�
		//HeadNode��Ϊ���շ���ֵ
		GeneralNode* cur = gbegin->_next;
		GeneralNode* begin = HeadNode;
		while (cur)
		{
			if (cur->_type == ValueType)   //ֵ�ڵ�
			{
				begin->_next = new GeneralNode(ValueType, cur->_value);
			}
			else if (cur->_type == SubType)     //�ӱ�ڵ�
			{
				begin->_next = new GeneralNode(SubType);
				begin->_next->_sublink = DiList(cur->_sublink);
			}
			cur = cur->_next;
			begin = begin->_next;
		}
		return HeadNode;
	}

	//����һ��
	//GeneralLists& operator= (const GeneralLists& g)   //��ֵ���������غ���
	//{
	//	if (&g != this)
	//	{
	//		this->_Distory(); //�ȴݻ�ԭ��
	//		DiList(_Link,g._Link);
	//		//_Link = DiList(g._Link);//�Է���ֵ����ʽ
	//	}
	//	return *this;
	//}

	//��������
	GeneralLists& operator= (GeneralLists g)   //(ע������б��������ú�const)��ֵ���������غ���
	{//g��ʵ�ζ���Ŀ��������ÿ������캯�����ٿռ��g���г�ʼ�������g��ָ���
	 //ʵ�ζ���ָ��ͬ
		swap(_Link,g._Link);//��������������������g._Link�ᱻ�ͷ�
		return *this;
	}
	~GeneralLists()       //��������
	{
		_Distory();
	}
	void _Distory()       //�ݻٹ����
	{
		Distory(_Link);
	}
	void Distory(GeneralNode*& link)
	{
		while (link)
		{
			if (link->_type == SubType)//�ݻ��ӱ�
			{
				Distory(link->_sublink);
			}
			GeneralNode* del = link; //��һ����Ȼ��ͷ�ڵ�
			link = link->_next;
			delete del;
		}
	}
	void _Print()
	{
		_Print(_Link);
	}
	void _Print(GeneralNode* begin)//�ݹ����
	{//((b,c,d))
		while (begin)
		{
			if (begin->_type == HeadType)
			{
				cout << "(";
			}
			if (begin->_type == ValueType)
			{
				cout << begin->_value;
				if (begin->_next != NULL)
				{
					cout << ",";
				}
			}
			if (begin->_type == SubType)
			{
				_Print(begin->_sublink);
				if (begin->_next != NULL)
				{
					cout << ",";
				}
			}
			begin = begin->_next;
		}
		cout << ")";
	}
	void _Size()
	{
		cout << _Size(_Link) << "  ";
	}
	int _Size(GeneralNode* begin)//�����ֵ����
	{
		int Scount = 0;
		while (begin)
		{
			if (begin->_type == ValueType)
			{
				Scount++;
			}
			if (begin->_type == SubType)
			{
				Scount += _Size(begin->_sublink);//�ϲ�ڵ���������ӱ�������Ľڵ�ĸ���
			}
			begin = begin->_next;
		}
		return Scount;
	}
	int Length()   //������ȣ��ڵ�������������ӱ�����ģ�
	{
		GeneralNode* begin = _Link;
		int Lcount = 0;
		while (begin->_next != NULL)
		{
			Lcount++;
			begin = begin->_next;
		}
		return Lcount;
	}
	void Depth()
	{
		cout << Depth(_Link) << "  ";
	}

	int Depth(GeneralNode* begin) //��������ȣ������ٲ㣩
	{
		int depth = 1;
		while (begin)
		{
			if (begin->_type == SubType)
			{
				int subdepth = Depth(begin->_sublink);
				if(subdepth+1>depth)
				{
					depth = subdepth+1;
				}
			}
			begin = begin->_next;
		}
		return depth;
	}
protected:
	void _GreadList(GeneralNode*& link,const char*& str)//���������
	{
		if (*str != '(')
		{
			cout << "Invalid string" << endl;
			return;
		}
		str++;
		GeneralNode* HeadNode = new GeneralNode(HeadType);//����ͷ�ڵ�
		link = HeadNode;
		GeneralNode* begin = HeadNode;

		//(a, ((b), (c), d), e)
		while (*str != '\0')
		{
			if (*str == ',')
			{
 				str++;
			}
			if (*str != ')'&& *str != '(')//��չ��Ҫ�������ַ�����ո񣬿���дһ�����˺���
			{
				GeneralNode* valueNode = new GeneralNode(ValueType,*str);
				//����ֵ�ڵ�
				str++;
				begin->_next = valueNode;
				begin = begin->_next; 
			}
			else if (*str == ')')  //�ݹ��������
			{
				str++;
				return;
			}
			else if (*str == '(')  //�ݹ鹹���ӱ�
			{
				GeneralNode* subNode = new GeneralNode(SubType);//�����ӱ�ڵ�
				begin->_next = subNode;
				begin = begin->_next;
				_GreadList(subNode->_sublink, str); //�ݹ�����ӱ�
			}
		}
	}
	
private:
	GeneralNode* _Link;
};
void Test1()
{
	const char* s1 = "(a,((b),(c),d),e)";
	GeneralLists g1(s1);  //���캯��
	GeneralLists g2(g1);  //�������캯��

	g1._Print();
	cout << endl;
	g2._Print();

	cout << endl;
	cout << "Size : ";
	g1._Size();
	g2._Size();

	//���
	cout << "Depth : ";
	g1.Depth();
	g2.Depth();

	//����
	cout << "Length : ";
	cout << g1.Length() << "  ";
	cout << g2.Length() << "  ";
}

int main()
{
	Test1();
	system("pause");
	return 0;
}
