#define INPUT_FILE_NAME "input_data_rd_256.bin"
#define OUTPUT_FILE_NAME "output_data_rd_256.bin"
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#define CHECK_TIME_START(start,freq) QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start)
#define CHECK_TIME_END(start,end,freq,time) QueryPerformanceCounter((LARGE_INTEGER*)&end); time = (float)((float)(end - start) / (freq * 1.0e-3f))
__int64 _start, _freq, _end;
float compute_time;


int Quick_Sort_P(int* data, int left, int right);

int main(void) {
	FILE* fp, * out_fp;
	int i = 0, num_data;

	fp = fopen(INPUT_FILE_NAME, "rb");
	if (fp == NULL) {
		printf("File doesn't exisist!\n");
		return 1;
	}
	fread(&num_data, sizeof(int), 1, fp);
	int* data = (int*)malloc(sizeof(int) * (num_data));
	fread(data, sizeof(int), num_data, fp);
	Quick_Sort_P(data, 0, num_data - 1);

	out_fp = fopen(OUTPUT_FILE_NAME, "wb");
	if (out_fp == NULL) {
		printf("Can't open file!\n");
		return 1;
	}
	fwrite(&num_data, sizeof(int), 1, out_fp);
	fwrite(data, sizeof(int), num_data, out_fp);


	free(data);

	return 0;
}