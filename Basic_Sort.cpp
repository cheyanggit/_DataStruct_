

/*************************
 *ð������
 *ѡ������
 *��������
	-----��ֱ�Ӳ���
	-----���۰����
 *������
 *��������
	-----��begin��end���ݹ��ջ����
	-----��prev��cur���ݹ��ջ��
	-----������ȡ��
	-----�������������ﵽһ����������ʹ�ò�������
 *ϣ������
 *�鲢����
 *��������
 *��������
	-----�����λ����MSD
	-----�����λ����LSD
 *************************/

#include <iostream>
#include <assert.h>
#include<stack>
using namespace std;

/*#################<<<<��ð������>>>>############################*/
/*ʱ�临�Ӷ� N^2  */
void BubbleSort(int *array, int size)
{
	assert(array && size > 0);
	int i, j;
	bool exchange = false;
	for (i = 0; i < size - 1; ++i)         //���ƱȽ������ֻ�
	{
		for (j = 0; j < size - i - 1; ++j) //����ÿһ�ֻصıȽ�
		{
			if (array[j]>array[j + 1])
			{
				swap(array[j], array[j + 1]);
				exchange = true;
			}
		}
		if (exchange == false)
		{//˵��û�з����任�������������
			return;
		}
	}
}
/*#################<<<<��ѡ������>>>>############################*/
/*ʱ�临�Ӷȣ�N^2 */
void SelectSort(int* array,int size)
{
	assert(array && size > 0);
	int begin = 0;
	int end = size - 1;
	int min,max,left, right;
	for (; begin < size-1,end>=0; ++begin,--end)
	{
		min = begin;
		max = end;
		left = begin;
		right = end;
		while (left<right)//��ֻ��һ�����ݣ��򲻱�Ҫ����
		{ //9 4 8 5 0--0 4 8 5 9
			if (array[min]>array[left])
			{
				swap(array[min], array[left]);
			}
			if (array[max] < array[left])
			{
				swap(array[max], array[left]);
			}
			++left;
		}
	}
}
/*#################<<<<��ֱ�Ӳ�������>>>>########################*/
/*ʱ�临�Ӷ�Ϊ N^2 */
void InsertSort(int* array, int size)
{
	assert(array && size > 0);
	int begin,end,tmp;
	for (begin = 1; begin < size; ++begin)
	{
		end = begin - 1;
		tmp = array[begin];
		while (end >= 0 && tmp < array[end])
		{
			array[end + 1] = array[end];
			--end;
		}
		if (array[end + 1] != tmp)  //�Լ�����ȥ�ģ�û��Ҫ�Լ����Լ���ֵ��
		{						    //��ʹ�����к��ж����ͬԪ��Ҳ���ԣ��磺9 0 4 3 8 8 2 8  
			array[end + 1] = tmp;
		}
	}
}
/*#################<<<<���۰��������>>>>########################*/
/*ʱ�临�Ӷ�Ϊ N^2 */
void InsertSort_Half(int *array, int size)
{
	assert(array && size > 0);
	int begin,tmp,left,right,mid,k;
	for (begin = 1; begin < size; begin++)
	{
		tmp = array[begin];
		left = 0;
		right = begin - 1;
		while (left <= right)
		{
			mid = left + (right-left) / 2;  //�˴���������(left+right-left)/2���������left = mid + 1; 
			if (array[mid] < tmp)      //������ѭ����(left+right-left)/2+1Ҳ������
			{
				left = mid + 1; 
			}
			else
			{
				right = mid - 1;
			}
		}
		for (k = begin - 1; k >= left; --k)
		{
			array[k + 1] = array[k];
		}
		array[left] = tmp;
	}
}
/*#################<<<<��������>>>>##############################*/
/*
*ʱ�临�Ӷ�  N*logN + N*logN = 2N*logN ������ʡ�Լ���� N*logN
�����������N�������ܵ���������ÿ��ÿ��������Ҫ�Ӹ��ڵ㿪ʼ�۰���������߶ȣ�
*Ӧ�ã��������ǰ����
*/
//�����µ�������ʱ�临�Ӷ� N*logN 
void seftDown(int* array, int size, int root)
{
	if (array == NULL || size <= 0 || root < 0 || root>size - 1)
	{
		return;
	}
	int left = root * 2 + 1;
	while (left < size)   //����������ҿ����䣬������Խ�磬��ô�ұ߾Ϳ϶�ҲԽ����
	{
		int right = left + 1;
		int max = left;
		if (right<size && array[max]<array[right])
		{
			max = right;
		}
		if (array[max] > array[root])
		{
			swap(array[max], array[root]);
			root = max;
			left = root * 2 + 1;
		}
		else
		{
			break;
		}
	}
}
void Heap(int* array, int size) //������
{
	if (array == NULL || size <= 0)
	{
		return;
	}
	int begin;
	for (begin = size / 2 - 1; begin >= 0; --begin)//��һ�����µ���
	{
		seftDown(array, size, begin);
	}
	int end = size-1;
	while (end)
	{
		swap(array[0], array[end]);
		seftDown(array,end,0);
		//����֮ǰ�Ѿ��������ˣ���ʱֻ��Ҫ�Ӹ��ڵ�������ͷ�ڵ���бȽϾͺ�
		//�����Ѿ��ɶ���
		--end;
	}
}


/*#################<<<<����������>>>>###########################*/
/*��ʱ�临�Ӷȣ�N*logN����������Ѿ���������л��߽ӽ��������÷�Χ�㣬�ȽϿ�*/

/**************************************************
 *����һ���ݹ�ͷǵݹ��ʵ�֣�begin��end��ʽ��
 *���������ݹ�ͷǵݹ��ʵ�֣�prev��cur��ʽ��
 *������������ȡ��
 *�����ģ�����������ﵽһ�����������Ͳ��ò�������
 *************************************************/

//����һ���ݹ�ʵ�֣�һ�ֻ����㷨��ʵ�֣�
void _QuickSort1(int* array, int left,int right)
{
	int key = array[right];
	int begin = left;     //�������ұ�array[key]�������array[begin]����
	int end = right-1;    //���ҵ����ұ�array[key]С������array[end]����
	if (left >= right)
	{
		return;
	}
	while (begin<end)
	{
		while (begin < end && array[begin] <= key) //�ȺŴ������Ԫ��
		{
			++begin;
		}
		while (begin < end && array[end] >= key)
		{
			--end;
		}
		if (begin < end)
		{
			swap(array[begin], array[end]);
			++begin;
			--end;
		}
	}
	if (array[begin] < key)  //���beginͣ���±��Ӧ��Ԫ�ز�һ���Ǵ���key��Ԫ��
	{						 //�����ʱ��0123456789�������begin��endָͬ��8����Ӧ��ֱ�ӽ�8��9����
		begin++;             //begin++֮��begin�����right��
	}
	swap(array[begin], array[right]);//����array[right]�������м�
	_QuickSort1(array, left, begin - 1); //�ݹ����������⣨�����䣩
	_QuickSort1(array, begin+1,right);//�ݹ����������⣨�����䣩
}
//�ǵݹ�ʵ�֣�ѹջ
int _NonR_QuickSort1(int *array, int left, int right)
{										//��NonR_QuickSort1_or_2�����е���
	assert(array);
	int key = array[right];
	int begin = left;
	int end = right - 1;
	while (begin < end)
	{
		while (begin < end && array[begin] <= key)
		{
			++begin;
		}
		while (begin < end && array[end] >= key)
		{
			--end;
		}
		if (begin < end)
		{
			swap(array[begin],array[end]);
			++begin;
			--end;
		}
	}
	if (array[begin] < key)
	{
		++begin;
	}
	swap(array[begin],array[right]);
	return begin;
}

//����ȡ��ʵ��
int GetMidIndex(int* array, int left, int right)
{
	int mid = left + (right - left) / 2;
	int k = left;
	if (array[mid] < array[k])
	{
		k = mid;
	}
	if (array[right] < array[k])//�ҳ���СԪ���±�
	{
		k = right;
	}
	if (k != left)
	{
		swap(array[k], array[left]);
	}
	if (mid != right && array[mid] < array[right])
	{
		swap(array[mid], array[right]);
	}
	return array[right];
}
//���������ݹ�ʵ�֣�ʱ�临�Ӷ� N*logN Ӧ�õ���������Ҫ��ʱ�临�Ӷ�Ϊ N*logN ��
void _QuickSort2(int* array, int left, int right)
{
	assert(array);
	if (left >= right)
	{
		return;
	}
	//���������Ż�������ȡ�з�
	//int key = GetMidIndex(array, left, right);
	//�����ģ����Ż�������������ﵽһ����������13���������̫�󣬾����Ʋ��������ˣ����Ͳ��ò�������
	if (right - left < 3)
	{
		InsertSort(array + left, right - left + 1);
		//�ݹ�����������±�5��right��������Ӧ�Ĳ�������Ҳ���ڴ��������
		return;
	}
	int key = array[right];
	int prev = left - 1;
	int cur = left;
	while (cur < right)
	{
		if (array[cur] < key)
		{
			++prev;
			if (prev != cur)
			{
				swap(array[prev], array[cur]);
			}
		}
		++cur;
	}
	while (array[prev] < array[right])//������ǵ�prev�ߵ�right��ֹͣ
	{ //9, 5, 0, 4, 2, 3, 4, 8, 5, 7 ����һ�ֱȽϽ�����5042345897ʱ��
		//curָ��9��prevָ�����һ��5����ʱֱ��ִ��swap(array[right], array[prev]);
		//�����ܴﵽ���Ԫ�ض���7С���ұ�Ԫ�ض���7������prevҪ���ұ��ҵ�һ�����ڵ���7����
		//������array[right]���н���
		++prev;
	}
	swap(array[right], array[prev]);
	_QuickSort2(array, left, prev - 1);
	_QuickSort2(array, prev + 1, right);
}
//�ǵݹ�ʵ�֣�������ݹ麯��ջ��������⣩
int _NonR_QuickSort2(int* array, int left, int right)
{                                //��NonR_QuickSort1_or_2�����е���
	assert(array);
	if (left >= right)
	{
		return -1;
	}
	int key = array[right];
	int cur = left;
	int prev = left - 1;
	while (cur < right)
	{
		if (array[cur] < key)
		{
			++prev;
			if (prev != cur)
			{
				swap(array[prev], array[cur]);
			}
		}
		++cur;
	}
	while (array[prev] < array[right])
	{
		++prev;
	}
	swap(array[right], array[prev]);
	return prev;
}
//ѹջ
void NonR_QuickSort1_or_2(int* array, int size)
{
	assert(array && size > 0);
	stack<int> s;
	s.push(size - 1);//�ұ߽�
	s.push(0);     //��߽�
	int left;
	int right;
	while (!s.empty())
	{
		left = s.top();
		s.pop();
		right = s.top();
		s.pop();
		int key = _NonR_QuickSort2(array, left, right);//keyΪÿһ�ֱȽϺ�prev���±�
		if (key - 1 > left)  //���������������������������ϵ����Ž��в���
		{
			s.push(key - 1);
			s.push(left);
		}
		if (right - 1 > key) //���������������������������ϵ����Ž��в���
		{
			s.push(right);
			s.push(key + 1);
		}
	}
}

/*#################<<<<��ϣ������>>>>############################*/
// ��ʱ�临�Ӷ� ƽ����N^1.3 ��ã�N  ���N^2 
void ShellSort(int *array, int size)
{
	assert(array && size > 0);
	int gap = size;
	int begin, end, tmp;
	int left = 0;
	int right = size - 1;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (end = left + gap; end <= right; end++)
		{
			if (array[end]<array[end - gap])
			{
				tmp = array[end];
				begin = end - gap;
				while (begin >= left && array[begin] > tmp)
				{
					array[begin+gap] = array[begin];
					begin -= gap;
				}
				array[begin + gap] = tmp;
			}
		}
	}
}

/*#################<<<<���鲢����>>>>############################*/
//ʱ�临�Ӷ� N*logN   Ӧ�ã�����
void MergeSort(int *array, int size)
{
	assert(array && size > 0);
	int *tmp = new int[size];//��������
	memset(tmp,0,size);
	int left = 0;
	int right = size - 1;
	int mid = left + (right - left) / 2;
	for (int begin = 0; begin <= mid; begin++)
	{
		tmp[begin] = array[begin];
	}
	InsertSort(tmp, mid+1);//������ǰ�벿��Ԫ�ؽ�������
	for (int begin = 0; begin <= mid; begin++)
	{
		array[begin] = tmp[begin];
	}
	int begin, i;
	for (begin = mid+1, i = 0; begin <= right; begin++, i++)//�ظ���ԭ����
	{
		tmp[i] = array[begin];
	}
	InsertSort(tmp, right-mid);//�������벿��ԭ��������
	for (begin = mid+1,i = 0; begin <= right; begin++,i++)//�ظ���ԭ����
	{
		array[begin] = tmp[i];
	}
	int left1 = mid + 1;
	int index = 0;
	while (left <= mid && left1 <= right)//�������Ѿ��ź����Ԫ�ؽ��кϲ�
	{
		if (array[left] < array[left1])
		{
			tmp[index] = array[left];
			++left;
			++index;
		}
		else
		{
			tmp[index] = array[left1];
			++index;
			++left1;
		}
	}
	while (left1 <= right) //�Ұ벿�ֻ���ʣ��Ԫ�أ��ϲ�ʣ��Ԫ��
	{
		tmp[index] = array[left1];
		left1++;
		index++;
	}
	while (left <= mid) //��벿�ֻ���ʣ��Ԫ�أ��ϲ�ʣ��Ԫ��
	{
		tmp[index] = array[left];
		left++;
		index++;
	}
	for (begin = 0; begin <= right; begin++)//�Ӹ�������ظ���ԭ����
	{
		array[begin] = tmp[begin];
	}
}

/*#################<<<<����������>>>>###########################*/
//Ҫ��Ӧ���ٺܴ�Ŀռ䣬������������п��ٿռ䣬��Ҫ�������û���ظ��������������λͼ
void CountSort(int *array, int size)
{
	assert(array && size > 0);
	int min = array[0], max = array[0];
	int i = 1;
	for (; i < size; i++)
	{
		if (array[i] > max)
		{
			max = array[i];
		}
		if (array[i] < min)
		{
			min = array[i];
		}
	}
	int len = max - min + 1;
	int *count = new int[len];
	memset(count, 0, sizeof(int)*len);
	for (i = 0; i < size; i++)
	{
		count[array[i] - min]++;
	}
	memset(array,0,sizeof(int)*size);
	int index = 0;
	for (i = 0; i < len; i++)
	{
		while (count[i] != 0)
		{
			array[index] = i + min;
			index++;
			count[i]--;
		}
	}
}

/*#################<<<<����������>>>>###########################*/
//ʱ�临�Ӷ� ����λ*N��Ӧ�ã����Ƚϼ��е�����
//���λ����MSD��MostSignificant Digit first��
int GetDigit(int value, int d)
{
	while (--d)
	{
		value /= 10;
	}
	return value%10;
}
const int size = 10;
void _RadixSort_MSD(int* array, int left, int right, int d)  //dΪ�����λ������λ��ʮλ����λ
{
	assert(array);
	if (d <= 0 || left >= right)
	{
		return;
	}
	int count[size];
	int *auxArray = new int[right-left+1]; //��������
	memset(count, 0, sizeof(count));
	memset(auxArray, 0, sizeof(int)*(right-left+1));
	int i, j;
	for (i = left; i <= right; i++)
	{
		count[GetDigit(array[i], d)]++;
	}
	for (i = 1; i < size; i++)
	{
		count[i] += count[i - 1];
	}
	for (i = left; i <= right; i++)
	{//�����������ǰ�棬count˳��ִ�б�֤���������Ͱ�ף�
	 //ÿ�λ���Ͱ�ڶ��Ԫ�أ�һ��Ԫ������Ҫ���У���������
		j = GetDigit(array[i], d);  //ȡԪ��array[i]��dλ��ֵ
		auxArray[count[j] - 1]  = array[i];
		count[j]--;
	}
 	for (i = left,j=0; i <= right; i++,++j)
	{
		array[i] = auxArray[j];//�Ӹ�������˳��д��ԭ����
	}
	for (i = 0; i < size; i++)
	{
		_RadixSort_MSD(array, count[i], count[i + 1] - 1, d - 1);
	}
}

//���λ����LSD��Least Significant Digit first��
int _GetMaxBit(int* array, int size)
{//����������ܹ�λ��
	int count = 1,flag = 0;
	int i = 0,tmp;
	for (; i < size; i++)
	{
		flag = count;
		tmp = array[i];
		while (tmp / 10)
		{
			count++;
			tmp /= 10;
		}
		if (count > flag)
		{
			flag = count;
		}
	}
	return flag;
}
void RadixSort_LSD(int* array, int size)
{
	int maxBit = _GetMaxBit(array, size);
	int* count = new int[size];
	int* auxArray = new int[size];

	int radix = 1;
	for (int bit = 1; bit <= maxBit; ++bit)
	{
		memset(count, 0, sizeof(int)* size);
		memset(auxArray, 0, sizeof(int)* size);
		for (int i = 0; i < size; ++i)
		{
			int k = (array[i]/radix) % 10;
			count[k]++;   
		}
		for (int i = 1; i < size; ++i)
		{
			count[i] += count[i - 1];
		}
		for (int i = size - 1; i >= 0; --i)
		{//С����������ǰ�棬count����ִ�б�֤���������Ͱ��
			int k = (array[i] / radix) % 10;
			auxArray[--count[k]] = array[i];
		}
		memcpy(array, auxArray, sizeof(int)*size);//������ԭ����
		radix *= 10;
		//radix = pow(10.0,bit-1);
	}
}
void TestAllSort()
{
	//int array[] = { 11, 0, 1, 4, 22, 0, 4, 8, 0, 7 };
	int array[] = { 90, 35, 40, 46, 27, 53, 64, 88, 75, 67 };
	//int array[] = { 1, 325, 403, 436, 237, 9, 664, 887, 755, 67 };
	//int array[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	int size = sizeof(array) / sizeof(array[0]);
	//BubbleSort(array,size);      //ð������
	//SelectSort(array,size);      //ѡ������
	//InsertSort(array,size);      //ֱ�Ӳ���
	//InsertSort_Half(array,size); //�۰����
	//Heap(array, size);		   //������
	//QuickSort(array,size);       //�����������֣�begin��end���ݹ��ջ����prev��cur���ݹ��ջ����
								   //����ȡ�С������������ﵽһ����������ʹ�ò�������
	//ShellSort(array, size);	   //ϣ������ gap = (gap/3)/2 ��
	//MergeSort(array,size);       //�鲢����
	//CountSort(array,size);       //��������
	//_RadixSort_MSD(array, 0, size - 1, 3);//MSD
	RadixSort_LSD(array,size);				//LSD
	for (int i = 0; i < size; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}
int main()
{
	TestAllSort();
	//Schedule();
	//getchar();
	system("pause");
	return 0;
}