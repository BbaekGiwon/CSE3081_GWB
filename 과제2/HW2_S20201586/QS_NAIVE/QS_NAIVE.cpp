#include <stdio.h>

void SWAP(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int* data, int left, int right) {
	int pivot = left, l = left + 1, r = right;
	while (l <= r) {
		while ((data[l] < data[pivot]) && l <= r) ++l;
		while ((data[r] >= data[pivot]) && l <= r) --r;
		if (l <= r) {
			SWAP(&data[l], &data[r]);
			l++; r--;
		}
	}
	SWAP(&data[pivot], &data[r]);
	return r;
}

int Quick_Sort_NAIVE(int* data, int left, int right) {
	int p;
	if (left < right) {
		int i, j;
		if (right - left < 3) {
			for (i = left; i < right; i++) {
				for (j = left + 1; j <= right; j++) {
					if (data[i] > data[j]) {
						SWAP(&data[i], &data[j]);
					}
				}
			}
		}
		else {
			p = partition(data, left, right);
			Quick_Sort_NAIVE(data, left, p - 1);
			Quick_Sort_NAIVE(data, p + 1, right);
			return 0;
		}
	}

	return 0;
}