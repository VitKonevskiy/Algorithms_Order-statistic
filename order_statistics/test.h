#pragma once
#include <stdlib.h>
#include <utility>
#include <time.h>
#include <iostream>
#include <string>

template <class T>
T order_statistics(T *a, unsigned n, unsigned k)
{
	int Tmp = 0;
	unsigned l = 1, r = n - 1;
	for (; ; )
	{
		if (r <= l + 1)
		{
			// текущая часть состоит из 1 или 2 элементов -
			//	 легко можем найти ответ
			if (r == l + 1 && a[r] < a[l])
				swap(a[l], a[r]);
			return a[k];
		}




		// упорядочиваем a[l], a[l+1], a[r]
		unsigned mid = (l + r) >> 1;
		swap(a[mid], a[l + 1]);




		if (a[l] > a[r])
			swap(a[l], a[r]);
		if (a[l + 1] > a[r])
			swap(a[l + 1], a[r]);
		if (a[l] > a[l + 1])
			swap(a[l], a[l + 1]);

		// выполняем разделение
		// барьером является a[l+1], т.е. медиана среди a[l], a[l+1], a[r]
		unsigned i = l + 1;
		unsigned j = r;
		const T
			cur = a[l + 1];
		for (;;)
		{
			while (a[++i] < cur);
			while (a[--j] > cur);
			if (i > j)
				break;
			swap(a[i], a[j]);
		}


		/*printf("Iteration 2 #%d\n", Tmp);
		for (int i = 0; i < ARR_SIZE; i++)
		{
		printf("%lf ", a[i]);
		}
		printf("\n");*/

		// вставляем барьер
		a[l + 1] = a[j];
		a[j] = cur;


		/*	printf("Iteration 3 #%d\n", Tmp);
		for (int i = 0; i < ARR_SIZE; i++)
		{
		printf("%lf ", a[i]);
		}
		printf("\n");*/

		// продолжаем работать в той части,
		//	 которая должна содержать искомый элемент
		if (j >= k)
			r = j - 1;
		if (j <= k)
			l = i;

		/*printf("Iteration 4 #%d\n",Tmp);
		for (int i = 0; i < ARR_SIZE; i++)
		{
		printf("%lf ", a[i]);
		}
		printf("\n");
		Tmp++;*/
	}
}