#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Merge(int* data, int left, int middle, int right);

int Merge_Sort(int* data, int left, int right) {
	int middle;

	if (left < right) {
		middle = (left + right) / 2;

		Merge_Sort(data, left, middle);
		Merge_Sort(data, middle + 1, right);
		Merge(data, left, middle, right);
	}
	return 0;
}

void Merge(int* data, int left, int middle, int right) {
	int i = left, j = middle + 1, k = left;
	int* buffer = (int*)malloc(sizeof(int) * (right + 1));

	memcpy(buffer + left, data + left, sizeof(int) * (right - left + 1));

	while (i <= middle && j <= right) {
		if (buffer[i] < buffer[j]) {
			data[k++] = buffer[i++];
		}
		else {
			data[k++] = buffer[j++];
		}
	}

	while (i <= middle) {
		data[k++] = buffer[i++];
	}
	while (j <= right) {
		data[k++] = buffer[j++];
	}
}