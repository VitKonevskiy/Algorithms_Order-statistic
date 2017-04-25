#pragma once
#include <stdlib.h>
#include <utility>
#include <time.h>
#include <iostream>
#include <string>

template <class T>
T order_statistics(T *a, unsigned n, unsigned k)
{
	unsigned l = 1, r = n;
	for ( ; ; )
	{
		if (r <= l + 1)
		{
			// ������� ����� ������� �� 1 ��� 2 ��������� -
			//	 ����� ����� ����� �����
			if (r == l + 1 && a[r] < a[l])
				swap(a[l], a[r]);
			return a[k];
		}

		// ������������� a[l], a[l+1], a[r]
		unsigned mid = (l + r) >> 1;
		swap(a[mid], a[l + 1]);
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

		// ��������� ������
		a[l + 1] = a[j];
		a[j] = cur;

		// ���������� �������� � ��� �����,
		//	 ������� ������ ��������� ������� �������
		if (j >= k)
			r = j - 1;
		if (j <= k)
			l = i;

	}
}