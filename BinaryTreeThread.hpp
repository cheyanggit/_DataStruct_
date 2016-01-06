

/***********************************************
 *������������
 *
 *-------����������
 *-----------------�������
 *-------����������
 *-----------------����������������
 *-----------------������������µĵ�һ���ڵ�
 *-----------------������������µ����һ���ڵ�
 *-----------------�����������current�ڵ�ĺ��
 *-----------------�����������current�ڵ��ǰ��
 *-------����������
************************************************/

#include<iostream>
using namespace std;

enum type
{
	THREAD,//������
	LINK   //��Ů�ڵ�
};

template<class T>
struct BinaryTreeThreadNode
{
	T _data;
	BinaryTreeThreadNode<T>* _leftNode;
	BinaryTreeThreadNode<T>* _rightNode;
	type leftTag; //ΪTHREADʱ��ڵ���ǰ����ΪLINKʱ�������
	type rightTag;//ΪTHREADʱ��ڵ��ź�̣�ΪLINKʱ����Һ���

	BinaryTreeThreadNode(const T& data)
		:_data(data)
		, _leftNode(NULL)
		, _rightNode(NULL)
		, leftTag(LINK)
		, rightTag(LINK)
	{}
};

template<class T>
class BinaryTreeThread
{
public:
	BinaryTreeThread(T* array, int size)
		:_root(NULL)
	{
		int index = 0;
		_CreateBinaryTreeThreadPre(_root, array, size, index);
	}
	void PrevOrderThread()  //���������������ֱ���˳���������򡢺���
	{
		BinaryTreeThreadNode<T>* prev = NULL;
		PrevOrderGreadThread(_root, prev);
	}
	void InOrderThread()   //���������������ֱ���˳���������򡢺���
	{
		BinaryTreeThreadNode<T>* prev = NULL;
		InOrderGreadThread(_root, prev);
	}
	BinaryTreeThreadNode<T>* First(BinaryTreeThreadNode<T>* cur)    //������������������������µĵ�һ���ڵ�
	{
		while (cur && cur->leftTag == LINK)
		{
			cur = cur->_leftNode;
		}
		return cur;
	}
	BinaryTreeThreadNode<T>* Last(BinaryTreeThreadNode<T>* cur)    //������������������������µ����һ���ڵ�
	{
		while (cur && cur->rightTag == LINK)
		{
			cur = cur->_rightNode;
		}
		return cur;
	}
	BinaryTreeThreadNode<T>* Post(BinaryTreeThreadNode<T>* current)//�������������������current�ڵ�ĺ��
	{
		if (current && current->_rightNode != NULL)
		{
			First(current->_rightNode);
		}
		return NULL;
	}

	BinaryTreeThreadNode<T>* Prev(BinaryTreeThreadNode<T>* current)//�������������������current�ڵ��ǰ��
	{
		if (current && current->_leftNode != NULL)
		{
			Last(current->_leftNode);
		}
		return NULL;
	}
	void HostOrderThread()   //���������������ֱ���˳���������򡢺���
	{
		BinaryTreeThreadNode<T>* prev = NULL;
		HostOrderGreadThread(_root, prev);
	}
	void Print()
	{
		/*Non_RPreOrder_In();
		cout << endl;
		Non_RInOrder_In();
		cout << endl;*/
		
		/*Non_RPreOrder_Pre();
		cout << endl;
		Non_RInOrder_Pre();
		cout << endl;*/
	}
protected:
	void _CreateBinaryTreeThreadPre(BinaryTreeThreadNode<T>*& root,
		T* array, int size, int& index)//������һ�ö�������û����������
	{
		if (index < size && array[index] != '#')
		{
			root = new BinaryTreeThreadNode<T>(array[index]);
			_CreateBinaryTreeThreadPre(root->_leftNode, array, size, ++index);
			_CreateBinaryTreeThreadPre(root->_rightNode, array, size, ++index);
		}
	}
	void PrevOrderGreadThread(BinaryTreeThreadNode<T>*& cur,
		BinaryTreeThreadNode<T>*& prev)//����������������
	{
		if (cur)
		{
			if (cur->_leftNode == NULL)//����ΪNULL
			{
				cur->leftTag = THREAD;
				cur->_leftNode = prev;
			}
			if (prev && prev->_rightNode == NULL)
			{
				prev->rightTag = THREAD;
				prev->_rightNode = cur;
			}
			prev = cur;		 //������һ���ڵ�
			if (cur->leftTag == LINK)//���Ӵ�����������������
			{
				PrevOrderGreadThread(cur->_leftNode, prev);
			}
			if (cur->rightTag == LINK)
			{
				PrevOrderGreadThread(cur->_rightNode, prev);
			}
		}
	}
	void InOrderGreadThread(BinaryTreeThreadNode<T>*& cur,
		BinaryTreeThreadNode<T>*& prev)                   //����������������
	{
		if (cur)
		{
			InOrderGreadThread(cur->_leftNode, prev); //����������������
			if (cur->_leftNode == NULL)
			{
				cur->leftTag = THREAD;
				cur->_leftNode = prev;
			}
			if (prev && prev->_rightNode == NULL)
			{
				prev->rightTag = THREAD;
				prev->_rightNode = cur;
			}
			prev = cur;
			InOrderGreadThread(cur->_rightNode, prev);//����������������
		}
	}
	void HostOrderGreadThread(BinaryTreeThreadNode<T>*& cur,
		BinaryTreeThreadNode<T>*& prev)		         //����������������
	{
		if (cur)
		{
			HostOrderGreadThread(cur->_leftNode, prev);
			HostOrderGreadThread(cur->_rightNode, prev);
			if (cur->_leftNode == NULL)
			{
				cur->leftTag = THREAD;
				cur->_leftNode = prev;
			}
			if (prev && prev->_rightNode == NULL)
			{
				prev->rightTag = THREAD;
				prev->_rightNode = cur;
			}
			prev = cur;
		}
	}

	//******����������������*******//

	void Non_RPreOrder_Pre()  //�������������������
	{
		BinaryTreeThreadNode<T>* cur = _root;
		while (cur)
		{
			cout << cur->_data << " ";
			if (cur->leftTag == LINK)
			{
				cur = cur->_leftNode;
			}
			else if (cur->rightTag == LINK)
			{
				cur = cur->_rightNode;
			}
			else if (cur && cur->rightTag == THREAD)
			{
				cur = cur->_rightNode;//��ʼ�����ҽڵ�
			}
		}
	}

	//************����������������******************//

	void Non_RPreOrder_In()    //����������������������ǵݹ飩
	{
		BinaryTreeThreadNode<T>* cur = _root;
		while (cur)
		{
			cout << cur->_data << " ";
			if (cur->leftTag == LINK)   //���·�����ڵ�
			{
				cur = cur->_leftNode;
			}
			else if (cur->rightTag == LINK)//���·����ҽڵ�
			{
				cur = cur->_rightNode;
			}			
			else
			{
				while (cur && cur->rightTag == THREAD) //ֱ�����ҽڵ��ʱ��
				{
					cur = cur->_rightNode;
				}
				if (cur)
				{
					cur = cur->_rightNode; //����������
				}
			}
		}
	}

	void Non_RInOrder_In()  //����������������������ǵݹ飩
	{
		BinaryTreeThreadNode<T>* cur = _root;
		while (cur)
		{
			while (cur->leftTag != THREAD)//�ҵ�������һ������
			{
				cur = cur->_leftNode;
			}
			cout << cur->_data << " ";    //���ʸ��ڵ�
			while (cur->rightTag == THREAD)
			{
				cur = cur->_rightNode;     
				cout << cur->_data << " ";//û���Һ���������ҽڵ�
			}
			cur = cur->_rightNode;    //�Һ�����Ϊһ������ȥ����
		}
	}
	//******����������������*******//
	//void Non_RPostOrder_Post()    //����������������������ǵݹ飩
	//{ //����������ʵ�֣���ÿ�������ﶼ����һ��ָ�򸸽ڵ��ָ��_parent
	//	BinaryTreeThreadNode<T>* cur = _root;
	//	BinaryTreeThreadNode<T> visit = NULL;   //����Ѿ����ʹ��Ľڵ�
	//	if (cur)
	//	{
	//		while (cur && cur->leftTag == LINK)
	//		{
	//			cur = cur->_leftNode;
	//		}
	//		while (cur && cur->leftTag == THREAD)
	//		{
	//			cout << cur->_data << " ";
	//			visit = cur;
	//			cur = cur->_rightNode;
	//		}
	//		if (cur && cur->_rightNode == visit)
	//		{
	//			//cur = cur->_parent;
	//			cur = cur->_rightNode;
	//		}
	//		if (cur == root)
	//		{
	//			return;
	//		}
	//	}
	//}
private:
	BinaryTreeThreadNode<T>* _root;
};
void TestBinaryTreeThread()
{
	//int array[20] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int array[20] = { 1, 2, 3, '#', '#', 4, '#', 5, '#', '#', 6 ,7};
	//BinaryTreeThread<int> tree(array, 10);
	BinaryTreeThread<int> tree(array, 12);
	//tree.PrevOrderThread();//����������
	//tree.InOrderThread();//����������
	tree.HostOrderThread();//����������
	tree.Print();
}