
/**************************************************************************************************
 *���Գƾ��󡷣���һ��N*N�ķ���A��A������Ԫ��Aij�����ҽ���Aij == Aji(0 <= i <= N-1 && 0 <= j <= N-1)��
 *�����A�ǶԳƾ����Ծ���ĶԽ���Ϊ�ָ�����Ϊ�����Ǻ������ǡ�
 *���Գƾ���ѹ���洢����ֻ��Ҫ�洢������/�����ǵ����ݣ��������洢n(n+1)/2�����ݡ�
 *�Գƾ����ѹ���洢�Ķ�Ӧ��ϵ�������Ǵ洢  
 *���ۣ�i>=j,  SymmetricMatrix[i][j] == Array[i*(i+1)/2+j]�����Գƾ����е�Ԫ�ض�Ӧ�洢�����Ԫ��
***************************************************************************************************/

//{0,1,2,3,4}
//{1,0,1,2,3}
//{2,1,0,1,2}
//{3,2,1,0,1}
//{4,3,2,1,0}

#include <iostream>
using namespace std;

#define N 3

template<class T>
class SymmetricMatrix
{
public:
	SymmetricMatrix(T* matrixarray, int L) //T*array Ҳ������ T array[][N]
		:_arrayLen(L*(L+1)/2)       
		, _array(new T[_arrayLen])
		, _mtrixLen(L*L)
	{
		int index = 0;
		for (int i = 0; i < L; i++)
		{
			for (int j = 0; j < L; j++)
			{
				if (i >= j)
				{
					_array[index++] = matrixarray[i*L+ j] ;//��һά����洢
				}
			}
		}
	}
	const T& GetVal(int row,int col)
	{
		if (row < col)
		{
			swap(row,col);
		}
		return _array[row*(row + 1) / 2 + col];//���Ͻ��ۿɵ�
	}
private:
	T* _array;		 //�洢���������
	size_t _arrayLen;//�洢����������С
	size_t _mtrixLen;//�����С
};

//int main()
//{
//	int matrixarray[N][N] = {
//								{0,1,2},
//								{1,0,1},
//								{2,1,0},
//							};
//	SymmetricMatrix<int> M((int*)matrixarray, N);
//	cout<<M.GetVal(1,2)<<endl;
//	system("pause");
//	return 0;
//}

/*****************************************************************************************************
 *��ϡ����󡷣�M*N�ľ��󣬾�������Чֵ�ĸ���ԶС����Чֵ�ĸ���������Щ���ݵķֲ�û�й��ɡ�
 *��ϡ������ѹ���洢�����洢����������Ч���ݣ�
 * ��ʹ��{row,col,value}��Ԫ��洢ÿһ����Ч���ݣ���Ԫ�鰴ԭ�����е�λ�ã��������ȼ��Ⱥ�˳�����δ�š�
 *****************************************************************************************************/

//{1,0,3,0,5}
//{0,0,0,0,0}
//{0,0,0,0,0}
//{1,0,3,0,5}
//{0,0,0,0,0}
//{0,0,0,0,0}

/****************************************************
 *ϡ����������
 {1,0,3,0,5}			  {1,0,0,1,0,0}
 {0,0,0,0,0}			  {0,0,0,0,0,0}
 {0,0,0,0,0}  -------->   {3,0,0,3,0,0}
 {1,0,3,0,5}			  {0,0,0,0,0,0}
 {0,0,0,0,0}			  {5,0,0,5,0,0}
 {0,0,0,0,0}
*****************************************************/

#include <vector>

#define ROW 3
#define COL 4

template<class T>
struct Tuple   //��Ԫ��
{
	int Trow;   //��
	int Tcol;   //��
	int Tvalue; //����
};

template<class T>
class SparseMatrix
{
public:
	SparseMatrix(T* _sparsearray, int row ,int col)//��һά���飨ǿת���洢��ά����
		:_row(row)
		, _col(col)
	{
		for (int i = 0; i < _row; i++)
		{
			for (int j = 0; j < _col; j++)
			{
				if (_sparsearray[i*_col + j] != 0)
				{
					Tuple<T> t;
					t.Trow = i;
					t.Tcol = j;
					t.Tvalue = _sparsearray[i*_col + j];
					_array.push_back(t);//����Ԫ�����������
				}
			}
		}
	}
	SparseMatrix()   //��ת�õ�ʱ������һ��SparseMatrix<T>�Ķ���Ҫ����û�в����Ĺ��캯��
	{}
	void Print()    //����ѹ���洢�������ӡ����
	{
		int index = 0;
		for (int i = 0; i < _row; i++)
		{
			for (int j = 0; j < _col; j++)
			{
				if (index < _array.size()				//��ֹԽ�����
					&& i == _array[index].Trow
					&& j == _array[index].Tcol)
				{
					cout << _array[index++].Tvalue<<" ";//�������ȴ洢
				}
				else
				{
					cout << '0'<<" ";
				}
			}
			cout << endl;
		}
	}
	SparseMatrix<T> TSmatrix()             //һ��ת�ã�����ֵ����������,��Ϊ���ص�����ʱ����
	{
		SparseMatrix<T> tmp;			    //��������Ϊ�˴����������飬����û�в����Ĺ��캯��
		tmp._row = _col;
		tmp._col = _row;
		int index = 0;
		for (int i = 0; i < _col; i++)      //�����б����������еĵ�һ���Ǵ洢��������ĵ�һ��
		{
			index = 0;
			while (index < _array.size())
			{
				if (i == _array[index].Tcol)//��������е��е��ڴ洢�����������
				{
					Tuple<T> t;
					t.Trow = _array[index].Tcol;
					t.Tcol = _array[index].Trow;
					t.Tvalue = _array[index].Tvalue;
					tmp._array.push_back(t);//�Ѹ�Ԫ�ص����н����ٲ��븨�����飬
											//������֤�˸�������Ҳ�ǰ������ȴ洢
				}
				index++;
			}
		}
		return tmp;
	}
	SparseMatrix<T> Quick_TSmatrix()       //����ת��
	{
		SparseMatrix<T> tmp;			  //�洢����ת�ú����
		tmp._row = _col;
		tmp._col = _row;
		int size = _array.size();
		int* count_col = new int[_col];   //�������飬ͳ�ƾ���ÿһ����Ч���ݵĸ���
		int* colIndex = new int[_col];    //�������飬ͳ�ƾ���ÿһ�е�һ����Ч������colIndex�����ŵ��±�
		memset(count_col, 0, sizeof(int)*_col);
		memset(colIndex, 0, sizeof(int)*_col);
		for (int i = 0; i < size; i++)
		{
			count_col[_array[i].Tcol]++;   //ͳ��ÿ����Ч���ݵĸ���
		}
		colIndex[0] = 0;				 //��һ�з������ֵ��±�϶����㣨�����һ�������ݣ�
		for (int i = 1; i < size; i++)  //ͳ��ÿһ�е�һ���������ֵ��±�
		{
			colIndex[i] = colIndex[i - 1] + count_col[i - 1];
		}
		for (int i = 0; i < size; i++)
		{
			tmp._array.push_back(Tuple<T>());    //����Ĭ�ϵ���Ԫ�飬�൱��ֱ�Ӵ�����Ԫ��
		}
		for (int i = 0; i < size; i++)
		{
			int index = colIndex[_array[i].Tcol];//ȡ��Ԫ�����Ӧ��ת�ú���±�
			tmp._array[index].Tvalue = _array[i].Tvalue;
			tmp._array[index].Trow = _array[i].Tcol;
			tmp._array[index].Tcol = _array[i].Trow;
			colIndex[_array[i].Tcol]++;
		}
		return tmp;
	}
private:
	vector<Tuple<T> > _array;//�洢ϡ����������
	int _row;				 //������У���Print������ʹ�ã��Ϳ��Բ��ô����⴫�Σ�
	int _col;				 //�������
};
int main()
{
	int Sparsearray[ROW][COL] = {
								{0,1,0,0},
								{1,0,1,0},
								{0,1,0,1},
							};
	SparseMatrix<int> s((int*)Sparsearray, ROW, COL);
	s.Print();
	cout <<"*********"<< endl;
	//SparseMatrix<int> sm = s.TSmatrix();    //һ��ת��
	//sm.Print();
	SparseMatrix<int> sm = s.Quick_TSmatrix();//����ת��
	sm.Print();
	system("pause");
	return 0;
}