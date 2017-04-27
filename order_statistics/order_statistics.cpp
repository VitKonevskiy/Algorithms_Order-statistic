// order_statistics.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "test.h"
#include <Windows.h>
using namespace std;

#define RAND_MAX 1000
#define PRINT_LIMIT 20
static unsigned ARR_SIZE = 7;

/*double order_stat(double *input_array, int size, int k)
{
	int left_pos = 1;
	int right_pos = size;

	while(true)
	{
		if (right_pos <= (left_pos + 1))
		{
			// массив состоит из 1 или 2 элементов
			if ((right_pos == (left_pos + 1)) && (input_array[right_pos] < input_array[left_pos]))
			{
				// сортируем такой массив
				swap(input_array[left_pos], input_array[right_pos]);
			}	
			// находим к-тый элемент ( либо 0 либо 1 )
			return input_array[k];
		}

		// упорядочиваем input_array[l], input_array[l+1], input_array[r]
		int middle_elem = (left_pos + right_pos) / 2;
		swap(input_array[middle_elem], input_array[left_pos + 1]);

		if (input_array[left_pos] > input_array[right_pos])
		{
			swap(input_array[left_pos], input_array[right_pos]);
		}			

		if (input_array[left_pos + 1] > input_array[right_pos])
		{
			swap(input_array[left_pos + 1], input_array[right_pos]);
		}			

		if (input_array[left_pos] > input_array[left_pos + 1])
		{
			swap(input_array[left_pos], input_array[left_pos + 1]);
		}		

		// выполняем разделение
		// барьером является input_array[l+1], т.е. медиана среди input_array[l], input_array[l+1], input_array[r]
		
		int i = left_pos + 1;
		int	j = right_pos;
		const double cur = input_array[left_pos + 1];
		
		i++;
		j--;
		while(true)
		{
			while (input_array[i] < cur)
			{
				i++;
			}
			while (input_array[j] > cur)
			{
				j--;
			}
			if (i > j)
			{
				break;
			}
				
			swap(input_array[i], input_array[j]);
		}

		// вставляем барьер
		input_array[left_pos + 1] = input_array[j];
		input_array[j] = cur;

		// продолжаем работать в той части,
		// которая должна содержать искомый элемент
		if (j >= k)
			right_pos = j - 1;
		if (j <= k)
			left_pos = i;
	}
}
*/

void init_arr_randomize(double *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = (double) rand() / (double) RAND_MAX;
	}
}

static int compare(const void * a, const void * b)
{
	if (*(double*)a > *(double*)b) return 1;
	else if (*(double*)a < *(double*)b) return -1;
	else return 0;
}

void print_array(double *arr, int size, string label = "print_array")
{
	cout << label << endl;
	for (int i = 0; i < size; i++)
	{
		cout << " | " << arr[i];
	}
	cout << endl;
}

template<class T>
void bubbleSort(T a[], long size) {
	long i, j;
	T x;

	for (i = 0; i < size; i++) {            // i - номер прохода
		for (j = size - 1; j > i; j--) {     // внутренний цикл прохода
			if (a[j - 1] > a[j]) {
				x = a[j - 1]; a[j - 1] = a[j]; a[j] = x;
			}
		}
	}
}

int main()
{
	srand(time(0));

	double *arr_for_order_stat = new double [ARR_SIZE];
	double *testarray = new double[ARR_SIZE];
	unsigned k = ARR_SIZE + 1;
	long int qStart, qFinish;
	long int osStart, osFinish;
	long int qTime, osTime;
	double qResult, osResult;
	for (int i = 0; i < ARR_SIZE; i++)
	{
		testarray[i] = arr_for_order_stat[i] = (double)rand() / (double)RAND_MAX;
	}

	if (ARR_SIZE <= PRINT_LIMIT)
	{
		print_array(arr_for_order_stat, ARR_SIZE, "generated array");
	}
	
	while (k < 0 || k > ARR_SIZE)
	{
		cout << "Insert the k - number of order" << endl;
		cin >> k;
	}

	qStart = GetTickCount();
	qsort(testarray, ARR_SIZE, sizeof(double), compare);
	qResult = testarray[k];
	qFinish = GetTickCount();
	qTime = qFinish - qStart;

	if (ARR_SIZE <= PRINT_LIMIT)
	{
		print_array(testarray, ARR_SIZE, "[Debug] sorted by qsort");
	}
	osStart= GetTickCount();
	
	osResult = order_statistics(arr_for_order_stat, ARR_SIZE, k);
	osFinish = GetTickCount();
	osTime = osFinish - osStart;

	cout << "----- Order statistics -----" << endl;
	cout << k << "-th order statistics is = " << osResult << endl;
	//cout << "Time = " << osTime << " sec" << endl;
	printf("Time = %d\n", osTime);
	cout << endl;
	cout << "----------- QSORT ----------" << endl;
	cout << k << "-th order statistics is = " << qResult  << endl;
	printf("Time = %d\n", qTime);
	//cout << "Time = " << qTime << " sec" << endl;
	cout << endl;
	cout << (osResult == qResult ? "true" : "else") << endl;

	delete[] arr_for_order_stat;
	delete[] testarray;
	//system("pause");
    return 0;
}

