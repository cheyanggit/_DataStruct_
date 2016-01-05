

//��С�ѣ�������С�ѡ����ѣ�ʵ�ֲ��롢ɾ�������򡢲��ң�
//�÷º��������Ѻ���С��֮������л�
#include <iostream>
#include <vector>
using namespace std;

////�º�����ʵ����С��������֮����л�////
template<class T>
class Less       //С�ں�����������С��
{
public:
	bool operator() (const T& left, const T& right)//����()
	{
		return right < left;
	}
};

template<class T>
class Greater   //С�ں�������������
{
public:
	bool operator() (const T& left, const T& right)
	{
		return right > left;
	}
};

template<class T,template<class> class Compare>  //ģ���ģ������
class Heap					 //��template<class> class Compare���޶��˵ڶ�������������ģ��������
{
public:
	Heap()                   //�����ն�
	{}
	Heap(T* array, int size) //������
	{
		int i = 0;
		_array.reserve(size);//֪��Ҫ���ٿռ�Ĵ�С��reserve����ֱ�Ӱ�����ǿ��ٺã�����ռ��С
				     //��������ÿ�β������������ռ䲻��ʱ��һ��һ�������������Ӷ����Ч��
		for (; i < size; i++)
		{
			_array.push_back(array[i]);//����ֵ
		}
		int begin = size / 2 - 1;
		for (; begin >= 0; begin--)       //�ӵ�����һ����Ҷ�ӽڵ㿪ʼ���µ���
		{
			seftDown(begin, size);
		}
	}
	Heap(vector<T> array)   //������С�� 
	{
		swap(_array, array);
		int begin = size / 2 - 1;
		for (; begin >= 0; begin--)  
		{
			seftDown(begin, size);
		}
	}
	//����һ��
	void seftDown_flag(int root, int size)	 //���µ���,�������flag
	{
		int flag = 1;
		while (flag)
		{
			int left = root * 2 + 1;
			int right = root * 2 + 2;
			if (left > size-1)
			{
				return;
			}
			int key = left;    //��¼��Сֵ���ؼ�����С���������ֵ���ؼ������
 			if (right < size && Compare<T>()(_array[left], _array[right]))
			{///////////////////Compare()Ϊ��ʱ��������+������������Ĭ�Ϲ��캯��������ʱ����
				key = right;
			}
			flag = 0;
			if (Compare<T>()(_array[root], _array[key]))
			{
				swap(_array[key], _array[root]);
				root = key;
				flag = 1;
			}
		}
	}
	//��������
        void seftDown(int root, int size)      //���µ���
	{
		int left = root * 2 + 1;      ////
		while (left < size)	      ////
		{	
			int right = left + 1; 
			int key = left;  
 			if (right < size && Compare<T>()(_array[left], _array[right]))
			{
				key = right;
			}
			if (Compare<T>()(_array[root], _array[key]))
			{
				swap(_array[key], _array[root]);
				root = key;
				left = root * 2 + 1;  ////
			}
			else
			{
				break;  	     ////
			}
		}
	}
	void Insert(const T& data)
	{
		_array.push_back(data);   //������β�嵽�������
		int begin = _array.size() - 1;
		seftUp(begin);
	}
	void seftUp(int root)		 //���ϵ����������Ԫ��ֻ����ÿ������ĸ��ڵ�Ƚϣ�
	{
		int flag = 1;
		while (flag)
		{
			int parent = (root - 1) / 2;
			flag = 0;
			if (_array[parent] > _array[root])
			{
				flag = 1;
				swap(_array[parent], _array[root]);
				root = parent;
			}
		}
	}
	void RemoveHead()   	    //ɾ����һ���ڵ㣨�±�Ϊ0��ͷ��㣩: �������һ��Ԫ�ش�����Ԫ��
	{
		int size = _array.size();
		_array[0] = _array[size - 1];
		_array.pop_back(); //�����һ������ɾ��
		int begin = 0;
		size = _array.size();
		seftDown(begin, size);
	}
	const T& GetTop()         //���ضѶ�Ԫ��
	{
		return _array[0];
	}
	bool Empty()             //�ж϶��Ƿ�Ϊ�ն�
	{
		return size == 0;
	}
	void ChangeHeapHead(int value)
	{
		_array[0] = value;
	}
	//����һ��
	void HeapSort(int root, int size)                   //����������С�ѣ������������ѣ�ֱ���������н��в���
	{
		int tmp = size - 1;
		while(tmp)
		{
			swap(_array[root], _array[tmp]);    //�������е�һ�������һ�����ݽ��н���
			seftDown(root, tmp);		    //���µ���
			tmp--;				    //��Ч��������
		}
	}
	//��������
	void HeapSort_Stack(int *Array, int root, int size) //����������С�ѣ������������ѣ�������������
	{
		int num = size;
		while (!_array.empty())
		{
			Array[size - 1] = _array.front();
			RemoveHead();
			seftDown(root, --size);
		}
		for (int i = 0; i < num; i++)
		{
			_array.push_back(Array[i]);
		}
	}
	void _Print()
	{
		int index = 0,size = _array.size();
		while (index < size)
		{
			cout << _array[index] << " ";
			index++;
		}
		cout << endl;
	}
private:
	vector<T> _array;   //��̬˳���
};

//��չ�⣺ʮ���������߸��������в�������ǰ�������
//���죺�����д���4G�����в�������ǰk��������ʱ�ڴ��Ǵ治����Щ���ݵģ���ô�Ϳ��Խ���������

void SearchNumHeap(int array[],int size,int k)
{
	int Array[5] = {0};
	for (int i = 0; i < k; i++)
	{
		Array[i] = array[i];
	}
	Heap<int, Less> hp(Array, k);   //��ʮ�����е�ǰ���������С��
	for (int i = k; i < size; i++)
	{
		int tmp = hp.GetTop();
		if (array[i] > tmp)
		{
			hp.ChangeHeapHead(array[i]);
			hp.seftDown(0, k);
		}
	}
	hp._Print();
}
void TestHeap()
{
	int array[10] = { 10, 16, 18, 13, 12, 15, 17, 9, 8, 19 };
	//Heap<int, Less> com(array, 10);//��С��
	//Heap<int, Greater> com(array, 10);//����
	//com.HeapSort(0,10);
	//com.HeapSort_Stack(array, 0, 10);
	//com._Print();
	SearchNumHeap(array, 10, 5);
}
int main()
{
	//TestMin_Heap();
	TestHeap();
	system("pause");
	return 0;
}