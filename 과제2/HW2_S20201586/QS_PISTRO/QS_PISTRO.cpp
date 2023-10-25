#include <stdio.h>

void SWAP(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

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

void find_pivot(int* data, int left, int right) {
	int mid = (left + right) / 2;

	if (data[left] > data[mid]) {
		if (data[mid] > data[right]) {
			SWAP(&data[left], &data[mid]);
			return;
		}
		else if (data[left] > data[right]) {
			SWAP(&data[left], &data[right]);
			return;
		}
		else {
			return;
		}
	}
	else {
		if (data[left] > data[right]) {
			return;
		}
		else if (data[mid] > data[right]) {
			SWAP(&data[left], &data[right]);
		}
		else {
			SWAP(&data[left], &data[mid]);
		}
	}
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

int Quick_Sort_P(int* data, int left, int right) {
	int p;
	int M = 15;//M이하의 원소를 가진 배열은 return
	while (left < right) {
		if (right - left < M) {
			break;
		}

		find_pivot(data, left, right);
		p = partition(data, left, right);
		// 작은 부분 배열을 먼저 정렬하도록 수정
		if (p - left < right - p) {
			Quick_Sort_P(data, left, p - 1);
			left = p + 1;
		}
		else {
			Quick_Sort_P(data, p + 1, right);
			right = p - 1;
		}
	}

	return 0;
}

int Quick_Sort_PISTRO(int* data, int left, int right) {
	Quick_Sort_P(data, left, right);

	Insertion_Sort(data, left, right);

	return 0;
}