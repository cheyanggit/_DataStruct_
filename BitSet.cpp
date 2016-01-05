/***************************************************************************************
 *λͼ����Ѷ�����⣺��40�ڸ��޷���������������û���Ź���������ô�жϸ�����һ�����Ƿ�
 *����40�ڸ������桾��Ѷ��
 *˼·������ڴ湻�Ļ���40�ڸ�����ʹ��λͼ�洢��Ҫ500M���ҵĿռ䡣
 **************************************************************************************/

//BitMap��λͼ��һ�������ÿ�����ݵ�ÿ��������λ��ʾһ�����ݣ�0��ʾ���ݲ����ڣ�1��ʾ���ݴ���

#include <iostream>
using namespace std;

template<class T>
class BitSet
{
public:
	BitSet(size_t num)
		:_size(num / 32 + 1)   //��num������32ʱ������Ŀռ���٣�����Ҫ����1
	{
		SetVector = new T[_size];	         //����100��������4��T�ռ�Ĵ�С
		memset(SetVector, 0, sizeof(T)*_size);   //��ʼ��
	}
	void Set(size_t num)
	{
		size_t index = num / 32;//��λ���ĸ�T���䣨�磺T��int����ô��λ���ĸ��������䣩
		size_t pos = num % 32;  //��λ����T�ռ��еľ�����һλ
					//���������涨λ�������ڵ�1���������䣬��ô���Ŷ�λ������32λ�е���һλ��
		SetVector[index] |= (1 << (31 - pos));
		printf("0x%x\n", SetVector[index]);
	}
	void Reset(size_t num)
	{
		size_t index = num / 32;
		size_t pos = num % 32;
		SetVector[index] &= ~(1 << 31 - pos);
		printf("0x%x\n", SetVector[index]);
	}
	void Clear()
	{
		memset(SetVector, 0, sizeof(T)*_size);
	}
private:
	T* SetVector;  
	size_t _size;  
};
void TestBitSet()
{
	BitSet<int> bt1(100);//��100����
	bt1.Set(10);         //��һ������Ϊ10
	//bt1.Set(8); 	     //��һ������Ϊ8
	bt1.Set(1);  	     //��һ������Ϊ1
	bt1.Reset(1);
	/*bt1.Reset(8);
	bt1.Reset(10);*/
	//bt1.Clear();
}
int main()
{
	TestBitSet();
	getchar();
	return 0;
}