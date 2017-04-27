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
	unsigned l = 0, r = n - 1;
	for (; ; )
	{
		if (r <= l + 1)
		{
			// ������� ����� ������� �� 1 ��� 2 ��������� -
			//	 ����� ����� ����� �����
			if (r == l + 1 && a[r] < a[l])
				swap(a[l], a[r]);
			return a[k];
		}
		/*printf("Iteration 0 #%d\n", Tmp);
		for (int i = 0; i < ARR_SIZE; i++)
		{
			printf("%lf ", a[i]);
		}
		printf("\n");*/



		// ������������� a[l], a[l+1], a[r]
		unsigned mid = (l + r) >> 1;
		swap(a[mid], a[l + 1]);
		/*printf("Iteration 1 #%d\n", Tmp);
		for (int i = 0; i < ARR_SIZE; i++)
		{
		printf("%lf ", a[i]);
		}
		printf("\n");*/



		if (a[l] > a[r])
			swap(a[l], a[r]);
		if (a[l + 1] > a[r])
			swap(a[l + 1], a[r]);
		if (a[l] > a[l + 1])
			swap(a[l], a[l + 1]);

		// ��������� ����������
		// �������� �������� a[l+1], �.�. ������� ����� a[l], a[l+1], a[r]
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

		// ��������� ������
		a[l + 1] = a[j];
		a[j] = cur;


		/*	printf("Iteration 3 #%d\n", Tmp);
		for (int i = 0; i < ARR_SIZE; i++)
		{
		printf("%lf ", a[i]);
		}
		printf("\n");*/

		// ���������� �������� � ��� �����,
		//	 ������� ������ ��������� ������� �������
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