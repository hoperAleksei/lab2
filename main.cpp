#include <iostream>

using namespace std;



bool isSorted(int const* arr, int n)
{
	for (int i = 1; i < n; i++)
	{
		if (arr[i] < arr[i - 1])
		{
			return false;
		}
	}
	return true;
}

int binarySearch(int const* mArray, int find_el, int size)
{
	if (!isSorted(mArray, size))
	{
		return -2;
	}
	int l = 0;
	int k = size;
	
	int i;
	
	while (l <= k)
	{
		i = (l+k) / 2;
		if (find_el > mArray[i])
		{
			l = i + 1;
		}
		if (find_el < mArray[i])
		{
			k = i - 1;
		}
		
		if (find_el == mArray[i])
		{
			return i;
		}
	}
	
	return -1;
}



int interpolationSearch(int const* mArray, int toFind, int size)
{
	if (!isSorted(mArray, size))
	{
		return -2;
	}
	int mid;
	int low = 0;
	int high = size - 1;
	while (mArray[low] < toFind && mArray[high] > toFind)
	{
		if (mArray[low] == mArray[high])
		{
			break;
		}
		mid = low + ((toFind - mArray[low]) * (high - low)) / (mArray[high] - mArray[low]);
		
		if (mArray[mid] < toFind)
		{
			low = mid + 1;
		}
		else if (mArray[mid] > toFind)
		{
			high = mid - 1;
		}
		else
		{
			return mid;
		}
	}
	
	if (mArray[high] == toFind)
	{
		return high;
	}
	if (mArray[low] == toFind)
	{
		return low;
	}
	
	return -1;
}


void globalSearch(int n, int *const *arr, int toFind)
{
	int k;
	for (int i = 0; i < n; i++)
	{
		k = n - i;
		int* diagonal = new int[k];
		if (i == 0)
		{
			cout << "Побочная диагональ: ";
			for (int j = 0; j < k; j++)
			{
				diagonal[j] = arr[j][n-j-1];
				cout << diagonal[j] << " ";
			}
			cout << endl;
			if (!isSorted(diagonal, k))
			{
				cout << "Последовательность не отсортированна для поиска." << endl;
			}
			else
			{
				cout << "Интерполяционный поиск: " << interpolationSearch(diagonal, toFind, k) << endl;
				cout << "Бинарный поиск: " << binarySearch(diagonal, toFind, k) << endl;
			}
		}
		else
		{
			cout << '+' << i << " диагональ: ";
			for (int j = 0; j < k; ++j) {
				diagonal[j] = arr[j][n-1-j-i];
				cout << diagonal[j] << " ";
			}
			cout << endl;
			if (!isSorted(diagonal, k))
			{
				cout << "Последовательность не отсортированна для поиска." << endl;
			}
			else
			{
				cout << "Интерполяционный поиск: " << interpolationSearch(diagonal, toFind, k) << endl;
				cout << "Бинарный поиск: " << binarySearch(diagonal, toFind, k) << endl;
			}
			
			cout << '-' << i << " диагональ: ";
			for (int j = 0; j < k; ++j) {
				diagonal[j] = arr[j + i][n-1-j];
				cout << diagonal[j] << " ";
			}
			cout << endl;
			if (!isSorted(diagonal, k))
			{
				cout << "Последовательность не отсортированна для поиска." << endl;
			}
			else
			{
				cout << "Интерполяционный поиск: " << interpolationSearch(diagonal, toFind, k) << endl;
				cout << "Бинарный поиск: " << binarySearch(diagonal, toFind, k) << endl;
			}
		}
		cout << endl;
	}
}

void printMx(int **arr, const int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}
}

int main()
{
	bool ind = true;
	int enter;
	while (ind)
	{
		cout << "Если хотите ввести матрицу сами, то введите 1, а если хотите запустить тестирование введите 0: ";
		cin >> enter;
		
		if (((enter == 0) or (enter == 1)))
		{
			ind = false;
		}
		else
		{
			cout << "Повторите попытку!" << endl;
		}
	}
	
	if (enter == 0)
	{
		const int n = 10;
		int **arr = new int*[n];
		
		/*
		 * ЗАПОЛНЕНИЕ МАТРИЦЫ ДЛЯ ТЕСТА
		 *
		 * todo
		 *
		 * */
		
		for (int i = 0; i < n; ++i)
		{
			arr[i] = new int[n];
			for (int j = 0; j < n; ++j)
			{
				arr[i][j] = 2*i + j;
			}
		}
		
		
		cout << "Матрица: " << endl;
		printMx(arr, n);
		const int a = 11;
		
		cout << "Ищем " << a << ": " << endl;
		
		globalSearch(n, arr, a);
		
	}
	
	
	if (enter == 1)
	{
		int n;
		int a;
		
		cout << "Введите размерность матрицы ";
		cin >> n;
		
		if (n == 0)
		{
			 cout << "Такая матрица не содержит элементов!";
			 return 1;
		}
		
		int **arr = new int*[n];
		for (int i = 0; i < n; ++i)
		{
			arr[i] = new int[n];
		}
		
		cout << endl << "Введите матрицу (по строчно, начиная с левого верхнего угла): "<< endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cin >> arr[i][j];
			}
		}
		
		cout << "Введенная матрица: " << endl;
		printMx(arr, n);
		
		cout << "Введите искомое число: ";
		cin >> a;
		globalSearch(n, arr, a);
	}
	
	return 0;
}
