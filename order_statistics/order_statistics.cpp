// order_statistics.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "test.h"

using namespace std;

#define RAND_MAX 1000
static unsigned ARR_SIZE = 10;

double order_stat(double *input_array, int size, int k)
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

void init_arr_randomize(double *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = (double) rand() / (double) RAND_MAX;
	}
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

int main()
{
	srand(time(0));

	double *arr_for_order_stat = new double [ARR_SIZE];
	unsigned k;

	init_arr_randomize(arr_for_order_stat, ARR_SIZE);
	print_array(arr_for_order_stat, ARR_SIZE, "generated array");

	cout << "Insert the k - number of order" << endl;
	cin >> k;

	//double result = order_stat(arr_for_order_stat, ARR_SIZE, k); // мое адаптированное
	double result = order_statistics(arr_for_order_stat, ARR_SIZE, k); // копипаст с сайта
	
	cout << k << "-th order statistics is = " << result << endl;

	system("pause");
    return 0;
}

