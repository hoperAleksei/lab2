#include <iostream>

using namespace std;

int binarySearch(int* mArray, int find_el, int size)
{
	
	
	
	int l = 0;
	int k = size;
	
	int i = 0;
	
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



int interpolationSearch(int *sortedArray, int toFind, int length)
{
	int mid;
	int low = 0;
	int high = length - 1;
	while (sortedArray[low] < toFind && sortedArray[high] > toFind)
	{
		if (sortedArray[low] == sortedArray[high])
		{
			break;
		}
		mid = low + ((toFind - sortedArray[low]) * (high - low)) / (sortedArray[high] - sortedArray[low]);
		
		if (sortedArray[mid] < toFind)
		{
			low = mid + 1;
		}
		else if (sortedArray[mid] > toFind)
		{
			high = mid - 1;
		}
		else
		{
			return mid;
		}
	}
	
	if (sortedArray[high] == toFind)
	{
		return high;
	}
	if (sortedArray[low] == toFind)
	{
		return low;
	}
	
	
	
	return -1;
}



bool isSorted(int* arr, int n)
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
				int index = interpolationSearch(diagonal, toFind, k);
				cout << "Интерполяционный поиск: " << index << endl;
				index = binarySearch(diagonal, toFind, k);
				cout << "Бинарный поиск: " << index << endl;
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
				int index = interpolationSearch(diagonal, toFind, k);
				cout << "Интерполяционный поиск: " << index << endl;
				index = binarySearch(diagonal, toFind, k);
				cout << "Бинарный поиск: " << index << endl;
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
				int index = interpolationSearch(diagonal, toFind, k);
				cout << "Интерполяционный поиск: " << index << endl;
				index = binarySearch(diagonal, toFind, k);
				cout << "Бинарный поиск: " << index << endl;
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
		cout << "Если хотите ввести матрицу сами введите 1, если хотите запустить тестирование введите 0: ";
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
		 *
		 * */
		for (int i = 0; i < n; ++i)
		{
			arr[i] = new int[n];
			for (int j = 0; j < n; ++j)
			{
				arr[i][j] = i + j;
			}
		}
		
		
		cout << "Матрица: " << endl;
		printMx(arr, n);
		
		cout << "Ищем 5: " << endl;
		
		globalSearch(n, arr, 5);
		
	}
	
	
	if (enter == 1)
	{
		int n;
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
		
		int a;
		cout << "Введите искомое число: ";
		cin >> a;
		globalSearch(n, arr, a);
	}
	
	return 0;
}
