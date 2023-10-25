#include <stdio.h>

int Insertion_Sort(int* data, int left, int right) {
	int i, j, temp;
	for (i = left + 1; i <= right; i++) {
		temp = data[i];
		j = i;
		while ((j > left) && (temp < data[j - 1])) {
			data[j] = data[j - 1];
			j--;
		}
		data[j] = temp;
	}

	return 0;
}