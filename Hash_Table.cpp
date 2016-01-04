
/******************************************
 *ɢ�б���ϣ��--> ɢ�к���
 *�����ϣ��ͻ�ķ�����
	��1����ɢ�з�����a������̽�� b������̽��
	��2����ɢ�з�������ʽ�ṹ
 ******************************************/

/////////////////��1����ɢ�з�����////////////////// 

#include<iostream>
using namespace std;

enum State       //������ݵ�״̬
{
	EMPTY,   //���������
	EXIST,   //������ݴ���
	DELETE,  //������ݱ�ɾ������ʱ���ݻ��Ǳ��������������
};

template<class k>
class HashTableClose
{
public:
	HashTableClose(const k& capacity)
		:_size(0)
		, _capacity(capacity)
	{
		_tables = new k[_capacity];
		_states = new State[_capacity];
		memset(_tables, k(), sizeof(k)*_capacity); //��ʼ��
		memset(_states, EMPTY, sizeof(State)*_capacity);
	}
	~HashTableClose()
	{
		delete[] _tables;
		delete[] _states;
	}
	//////����̽�⣨һ��̽�⣩///////
	k HashFunc1(const k& key)
	{
		return key % _capacity;         //��ֹԽ��
	}
	bool Insert1(const k& key)
	{
		_CheckCapacity();
		k pos = HashFunc1(key);         //��λ�����봦
		while (_states[pos] == EXIST)   //���posλ���Ѿ���ű�������ˣ���ô����Ѱ�ҿ�λ��
		{
			if (_states[pos] != DELETE && _tables[pos] == key)  //�������Ѿ�����Ҫ���������
			{                                                   //���ܴ����ͬ����
				return false;
			}
			pos++;
			if (pos == _capacity)
			{
				pos = 0;        //�ӿ�ʼ��ѭ�����ҿ�λ��
			}
		}
		_tables[pos] = key;
		_states[pos] = EXIST;
		++_size;
		return true;
	}
	/////////����̽��/////////
	k HashFunc2(const k& lastHash, int i)
	{
		return (lastHash + 2 * i - 1) % _capacity;//lastHashΪ��һ�������λ��
	}
	bool Insert2(const k& key)
	{
		_CheckCapacity();
		k pos = HashFunc1(key);
		int i = 1;
		while (_states[pos] == EXIST)            //���posλ���Ѿ���ű�������ˣ���ô����Ѱ�ҿ�λ��
		{
			if (_states[pos] != DELETE && _tables[pos] == key) 
			{                                                   
				return false;
			}
			pos = HashFunc2(pos, i++);   //Ϊ��������洢�����ݲ���ôӵ��,���׳��ֳ�ͻ
			if (pos == _capacity)
			{
				pos = 0;            //�ӿ�ʼ��ѭ�����ҿ�λ��
			} 
		}
		_tables[pos] = key;
		_states[pos] = EXIST;
		++_size;
		return true;
	}
	void Print()
	{
		int index = 0;
		for (; index < _capacity; index++) //����˳��洢��Ҫ����һ�飬���Բ�����_size
		{
			cout << "[" << _tables[index] << "," << _states[index] << "]  ";
		}
	}
	bool Remove(const k& key)
	{
		k pos = HashFunc1(key);
		int i = 1;
		while (_states[pos] != EMPTY)  
		{
			if (_states[pos] == EXIST && _tables[pos] == key)   
			{                                                  
				_states[pos] = DELETE;//ʵ�����ݻ����������棬ֻ�Ǳ�Ǳ��˶���
				--_size;
				return true;
			}
			pos = HashFunc2(pos, i++);
			if (pos == _capacity)
			{
				pos = 0; 
			}
		}
		return false;
	}
protected:
	void _CheckCapacity()     //��������
	{ 
		if ((float)_size / (float)_capacity >= 0.8)   //����Ч���ݸ����ﵽ��������80%��ʱ��������
		{
			int n = _capacity;
			_capacity = 2 * _capacity + 1;
			k* tmp_tables = new k[_capacity];
			State* tmp_states = new State[_capacity];
			memset(tmp_tables, k(), sizeof(k)*_capacity);    
			memset(tmp_states, EMPTY, sizeof(State)*_capacity);
			int index = 0;
			while (index != n)
			{
				if (_states[index] != EMPTY)
				{
					int pos = HashFunc1(_tables[index]);//����̽�⣨һ��̽�⣩�����������¶�λ���¿��ٵ���������
					tmp_tables[pos] = _tables[index];
					tmp_states[pos] = _states[index];
				}
				index++;
			}
			delete[] _tables;
			delete[] _states;
			_tables = tmp_tables;
			_states = tmp_states;
		}
	}
private:
	k* _tables;     //�������
	State* _states; //�������״̬
	k _size;        //��Ч����
	k _capacity;    //����
};


////////////��2����ɢ�з���//////////////

#include <vector>
template<class k, class v>
struct HashTableOpenNode                               //ÿ���ڵ���һ���ṹ��
{
	k _key;
	v _value;
	HashTableOpenNode<k, v>* _next;

	HashTableOpenNode(const k& key,const v& value) //���캯��
		:_key(key)
		, _value(value)
		, _next(NULL)
	{}
};
const size_t PrimeSize = 28;
static const unsigned long _Prime[PrimeSize] =
{//��ֹ��ϣ��ͻ����֤������Ӧ�ÿ��ٿռ�Ĵ�С
	53ul, 97ul, 193ul, 389ul, 769ul,
	1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
	49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
	1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
	50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
	1610612741ul, 3221225473ul, 4294967291ul
};

template<class k,class v>
class HashTableOpen
{
	typedef HashTableOpenNode<k,v> Node;
public:
	HashTableOpen()
		:_size(0)
	{}
public:
	bool Insert(const k& key, const v& value)   
	{//�������ݣ����磺һ�����Ķ�Ӧ������Ӣ��Ӧ�ò嵽ͬһ�����ϣ����ҵ�ʱ���ܸ�Ч��
		unsigned long num = _GetPrime();
		_CheckCapacity(num);
		size_t pos = HashFunc(key,num);
		Node* tmp = new Node(key, value);
		Node* begin = _tables[pos];
		while (begin)   //������������Ѿ�����ͬ�����ݣ���ô�Ͳ����ظ�������
		{
			if (begin->_key == key && begin->_value == value)
			{
				return false;
			}
			begin = begin->_next;
		}
		tmp->_next = _tables[pos];//����ͷ��
		_tables[pos] = tmp;
		++_size;
		return true;
	}
	bool Find(const k& key)   //���ң����磺һ�����Ķ�Ӧ������Ӣ�ģ���֮Ҳ������
	{
		size_t pos = HashFunc(key,_tables.size());
		Node* begin = _tables[pos];
		while (begin)
		{
			if (begin->_key == key)
			{
				cout << "[" << begin->_key << ",";
				cout << begin->_value << "]->";
			}
			begin = begin->_next;
		}
	}
	bool Remove(const k& key) //ɾ�������磺ɾ��һ�����Ķ�Ӧ������Ӣ�ģ���֮Ҳ������
	{
		size_t pos = HashFunc(key, _tables.size());
		Node* begin = _tables[pos];
		while (begin)
		{
			if (begin->_key == key)
			{
				Node* del = begin;
				begin = begin->_next;
				delete del;
			}
			begin = begin->_next;
		}
	}
	size_t HashFunc(const k& key,const k& capacity)
	{
		return key % capacity;
	}
	void _Print()    //��ӡ��ϣ��
	{
		for (int i = 0; i < _tables.size(); i++)
		{
			Node* begin = _tables[i];
			printf("HashTable[%d]->", i);
			while (begin)
			{
				cout << "[" << begin->_key << ",";
				cout << begin->_value << "]->";
				begin = begin->_next;
			}
			cout <<"NULL"<< endl;
		}
	}
protected:
	unsigned long _GetPrime()        //��ȡ����
	{
		for (int i = 0; i<PrimeSize; i++)
		{
			if (_Prime[i]>_size)
			{
				return _Prime[i];
			}
		}
		return _Prime[PrimeSize];
	}
	void _CheckCapacity(size_t num)   //��һ���Զ࿪�ټ����ֽ�
	{
		if (num > _tables.size())
		{
			vector<Node*> NewTables;
			NewTables.assign(num,NULL);//��NewTables��ÿ��Ԫ�س�ʼ��ΪNULL
			for (int i = 0; i < _tables.size(); i++)//����ֵ
			{
				while (_tables[i])
				{
					Node* begin = _tables[i];
					_tables[i] = _tables[i]->_next;
					size_t pos = HashFunc(begin->_key,num);
					begin->_next = NewTables[pos];//����ͷ��
					NewTables[pos] = begin;
				}
			}
			_tables.swap(NewTables);
		}
	}
private:
	vector<Node*> _tables;
	size_t _size;
};
void TestHashTableOpen()
{
	HashTableOpen<int, double> open;
	open.Insert(1, 1.1);
	open.Insert(1, 1.2);
	open.Insert(2, 2.2);
	open.Insert(2, 2.4);
	open.Insert(1, 1.1);
	open.Insert(20, 1.6);
	open.Insert(30, 1.1);
	open._Print();
}
int main()
{
	//TestHashTableClose();
	TestHashTableOpen();
	system("pause");
	return 0;
}

