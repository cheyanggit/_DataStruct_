#pragma once

/*************************************
 *�������Ľ���
 *�������ı���
 *		------����������ݹ�ͷǵݹ�ʵ�֣�
 *		------����������ݹ�ͷǵݹ�ʵ�֣�
 *		------����������ݹ�ͷǵݹ�ʵ�֣�
 *		------����������ǵݹ�ʵ�֣�
 ************************************/
#include <queue>
#include <stack>

template<class T>
struct TreeNode          //��ͨ���ڵ�ṹ�������ֵܱ�ʾ����
{
	T _value;
	TreeNode<T>* _leftNode;   //����
	TreeNode<T>* _brotherNode;//���ֵ�
};

template<class T>
struct BinaryTreeNode    //�������ڵ�ṹ
{
	T _value;
	BinaryTreeNode<T>* _leftNode; //������
	BinaryTreeNode<T>* _rightNode;//������

	BinaryTreeNode(const T& value)//���캯��
		:_value(value)
		, _leftNode(NULL)
		, _rightNode(NULL)
	{}
};

template<class T>
class BinaryTree
{
public:
	BinaryTree(char* str)
		:_root(NULL)
	{
		_GreateTree(_root, str);
	}
	BinaryTreeNode<T>* _Copy(BinaryTreeNode<T>* cur)
	{
		BinaryTreeNode<T>* root = NULL;
		if (cur)
		{
			root = new BinaryTreeNode<T>(cur->_value);
			BinaryTreeNode<T>* begin = root;
			begin->_leftNode = _Copy(cur->_leftNode);
			begin->_rightNode = _Copy(cur->_rightNode);
		}
		return root;
	}
	/*�Ż��棺
	BinaryTree(BinaryTree<T>* cur)        //�������캯������һ����ȥ��ʼ������һ����
	{
		swap(_root, cur);
		return *this;
	}*/
	//��ͨ�棺
	BinaryTree(const BinaryTree<T>& cur)  //�������캯��������������
	{
		_root = _Copy(cur._root);
	}
	/*�Ż��棺
	BinaryTree<T>& operator= (BinaryTree<T>* cur) //��ֵ���������غ�����������������
	{
		if (this != &cur)
		{
			swap(_root, cur);
		}
		return *this;
	}*/
	//��ͨ�棺
	void _Distory(BinaryTreeNode<T>* tmp)
	{
		if (tmp)
		{
			_Distory(tmp->_leftNode);
			_Distory(tmp->_rightNode);
			delete tmp;
		}
	}
	BinaryTree<T>& operator= (const BinaryTree<T>& cur) //��ֵ���������غ���
	{
		if (this != &cur)
		{
			_Distory(_root);//������ʾ������������this->~BinaryTree();
			_root = _Copy(cur._root);
		}
		return *this;
	}
	~BinaryTree()
	{
		_Distory(_root);
	}
	void _GreateTree(BinaryTreeNode<T>*& root, char*& str) //����һ�ö�����
	{
		if (*str != '#' && *str != '\0')
		{
			root = new BinaryTreeNode<T>(*str);
			_GreateTree(root->_leftNode, ++str); //��������������
			_GreateTree(root->_rightNode, ++str);//��������������
		}
	}
	void _Print()      //���ñ�����Ա����
	{
		cout << "���������";
		PreOrder(_root);
		cout << endl;
		cout << "���������";
		InOrder(_root);
		cout << endl;
		cout << "���������";
		BackOrder(_root);
		cout << endl;
		cout << "���������";
		LevelOrder(_root);
		cout << endl;
	}
	void _NonR_Print()
	{
		NonR_PreOrder(_root);
		cout << endl;
		NonR_InOrder(_root);
		cout << endl;
		NonR_PostOrder(_root);
		cout << endl;
	}
	int Size()
	{
		cout << "�ڵ������";
		return size(_root);
	}
	int size(BinaryTreeNode<T>* root)   //�ڵ�������ݹ飩
	{
		int count = 0;
		if (root)
		{
			count = 1;
			count += size(root->_leftNode); //�ݹ��������
			count += size(root->_rightNode);//�ݹ��������
		}
		return count;
	}
	int Depth()
	{
		cout << "��ȣ�";
		return depth(_root);
	}
	int depth(BinaryTreeNode<T>* root)    //��ȣ��ݹ飩
	{
		if (root == NULL)
		{
			return 0;
		}
		int leftNum = 1 + _Depth(root->_leftNode);
		int rightNum = 1 + _Depth(root->_rightNode);
		return leftNum > rightNum ? leftNum : rightNum;
	}
protected:
	void PreOrder(BinaryTreeNode<T>* cur)  //����������ݹ鷽��һ��
	{
		if (cur)
		{
			cout << cur->_value << " ";    //���ȷ��ʸ��ڵ�
		}
		if (cur->_leftNode)
		{
			PreOrder(cur->_leftNode);
		}
		if (cur->_rightNode)
		{
			PreOrder(cur->_rightNode);
		}
	}
	void NonR_PreOrder(BinaryTreeNode<T>* root)   //����������ǵݹ鷽��һ��
	{
		stack<BinaryTreeNode<T>*> s;
		if (root)
		{
			s.push(root);
		}
		BinaryTreeNode<T>* cur = NULL;
		while (!s.empty())
		{
			cur = s.top();
			cout << cur->_value << " ";
			s.pop();
			if (cur->_rightNode)  //�����Һ���������ߺ�����ջ
			{
				s.push(cur->_rightNode);
			}
			if (cur->_leftNode)
			{
				s.push(cur->_leftNode);
			}
		}
	}
	void InOrder(BinaryTreeNode<T>* root)     //����������ݹ飩
	{
		if (root)
		{
			if (root->_leftNode)
			{
				InOrder(root->_leftNode);
			}
			cout << root->_value << " ";    //�м���ʸ��ڵ�
			if (root->_rightNode)
			{
				InOrder(root->_rightNode);
			}
		}
	}
	void NonR_InOrder(BinaryTreeNode<T>* root)   //����������ǵݹ飩
	{
		stack<BinaryTreeNode<T>*> s;
		BinaryTreeNode<T>* cur = root;
		while (cur || !s.empty())//����ѭ������������
		{
			while (cur)	//�����Ԫ��ȫ����ջ�����curΪNULL����ô��ֱ�ӳ����ݲ��Ҵ�ӡ����
			{
				s.push(cur);
				cur = cur->_leftNode;
			}
			BinaryTreeNode<T>* top = s.top();
			cout << top->_value << " ";
			s.pop();
			cur = top->_rightNode;//�Һ��ӿ��ܻ���һ������
		}
	}
	void BackOrder(BinaryTreeNode<T>* root)     //�������
	{
		if (root)
		{
			if (root->_leftNode)
			{
				BackOrder(root->_leftNode);
			}
			if (root->_rightNode)
			{
				BackOrder(root->_rightNode);
			}
			cout << root->_value << " ";//�����ʸ��ڵ�
		}
	}
	void NonR_PostOrder(BinaryTreeNode<T>* root)   //����������ǵݹ飩
	{
		stack<BinaryTreeNode<T>*> s;
		BinaryTreeNode<T>* cur = root;
		BinaryTreeNode<T>* visitedNode = NULL;
		while (cur || !s.empty())
		{
			while (cur)    //�����Ԫ��ȫ����ջ
			{
				s.push(cur);
				cur = cur->_leftNode;
			}
			BinaryTreeNode<T>* top = s.top();//��ʱ������������top�ڵ㣬��Ϊ�ýڵ��п��ܻ���������
			if (top->_rightNode == NULL || top->_rightNode == visitedNode)
			{
				cout << top->_value << " ";
				s.pop();
				visitedNode = top;//������һ�α����ʵĽڵ�
			}
			else
			{
				cur = top->_rightNode;
			}
		}
	}
	void LevelOrder(BinaryTreeNode<T>* root)  //������������У�
	{
		queue<BinaryTreeNode<T>* > q;
		if (root)
		{
			q.push(root);
		}
		BinaryTreeNode<T>* begin = NULL;
		while (!q.empty())    //ջΪ�����ʾ���ʽ���
		{
			begin = q.front();//����ջ�еĵ�һ��Ԫ���Է��������Һ���
			cout << begin->_value << " ";
			q.pop();
			if (begin->_leftNode)
			{
				q.push(begin->_leftNode);
			}
			if (begin->_rightNode)
			{
				q.push(begin->_rightNode);
			}
		}
	}
private:
	BinaryTreeNode<T>* _root;//���ڵ�
};

void TestBinaryTree1()
{
	char* str1 = "123##4##56";
	BinaryTree<char> t1(str1);
	t1._Print();
	cout << endl;
	/*cout << t1.Size() << endl;
	cout << t1.Depth() << endl;*/
	BinaryTree<char> t2(t1);
	t2._Print();
	cout << endl;
	char* str3 = "456##7##89";
	BinaryTree<char> t3(str3);
	t3 = t2;
	t3._Print();
	cout << endl;
}

/*�������⣺�����ӡ�������ݹ�ͷǵݹ飨��ջ��*/

void TestBinaryTree2()
{
	char* str = "123##4##56";
	BinaryTree<char> t1(str);
	/*int a[10] = {1,2,3,-1,-1,4,-1.-1,5,6};
	BinaryTree<int> i1(a,10,-1);*/
	t1._NonR_Print();
}

//��չ
//��������洢�������ڵ�ṹ
template<class T>
struct BinaryTreeNode_PNode
{
	BinaryTreeNode_PNode<T>* _leftNode;  //����
	BinaryTreeNode_PNode<T>* _rightNode; //�Һ���
	BinaryTreeNode_PNode<T>* _parentNode;//���ڵ�
	T _data;

	BinaryTreeNode_PNode(const T& data)
		:_data(data)
		, _leftNode(NULL)
		, _rightNode(NULL)
		, _parentNode(NULL)//���ڵ�Ϊi��������Ϊ2*i+1,�Һ���Ϊ2*i+2
	{}
};
template<class T>
class BinaryTree_P
{
public:
	BinaryTree_P(T* array,int size)
		:_root(NULL)
	{
		int index = 0;
		_CreateBinaryTree_P(_root, array, size, index);
	}
protected:
	void _CreateBinaryTree_P(BinaryTreeNode_PNode<T>*& root, T* array, int size, int& index)
	{
		if (index < size && array[index] != '#')
		{   //�ȴ������ڵ㣬��ʶ���������˳���������
			root = new BinaryTreeNode_PNode<T>(array[index]);
			_CreateBinaryTree_P(root->_leftNode, array, size, ++index);
			_CreateBinaryTree_P(root->_rightNode, array, size, ++index);
		}
	}
private:
	BinaryTreeNode_PNode<T>* _root;
};

void TestBinaryTree_P()
{
	int array[20] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree_P<int> tree(array,10);
}