#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include <iomanip>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

typedef struct point {
	double x;
	double y;
}point;

double dis(point a, point b, int  a_dix, int b_idx) {
	if (abs(a_dix - b_idx) <= 1) return 0;
	return sqrt(pow(a.x - b.x,2) + pow(a.y - b.y,2));
}

int*** temp_table;
vector<pair<int, int>> div_p;

bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
	if (a.first == b.first) {
		return a.second < b.second;
	}
	return a.first < b.first;
}

void push_num(int a, int b) {
	if (temp_table[a][b][0] > -1 && temp_table[a][b][1] > -1) {
		div_p.push_back(pair<int,int>(temp_table[a][b][0], temp_table[a][b][0] + temp_table[a][b][1]));
		push_num(temp_table[a][b][0], temp_table[a][b][1]);
	}
	
	if (temp_table[a][b][2] > -1 && temp_table[a][b][3] > -1) {
		div_p.push_back(pair<int,int>(temp_table[a][b][2], temp_table[a][b][2] + temp_table[a][b][3]));
		push_num(temp_table[a][b][2], temp_table[a][b][3]);
	}
}

int main(void) {
	int num;
	ifstream test_command("PT_test_command.txt");
	if (!test_command.is_open()) {
		cerr << "File doesn't exist\n";
		return 1;
	}
	test_command >> num;
	for (int i = 0; i < num; i++) {
		int n;
		string input, output;
		test_command >> input >> output;
		ifstream input_file(input);
		ofstream output_file(output);
		if (!input_file.is_open() || !output_file.is_open()) {
			cerr << "File doesn't exist\n";
			return 1;
		}

		input_file >> n;
		point* p = new point[n];
		for (int i = 0; i < n; i++) {
			input_file >> p[i].x >> p[i].y;
		}

		double** dp = new double* [n];
		for (int i = 0; i < n; i++) {
			dp[i] = new double [n];
		}
		
		int *** table = new int** [n];
		for (int i = 0; i < n; i++) {
			table[i] = new int* [n];
			for (int j = 0; j < n; j++) {
				table[i][j] = new int [4];
				for (int k = 0; k < 4; k++) {
					table[i][j][k] = -1;
				}
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= 2; j++) {
				dp[i][j] = 0;
			}
		}

		for (int gap = 3; gap < n; gap++) {
			for (int i = 0; i + gap < n; i++) {
				dp[i][gap] = numeric_limits<double>::max();
				for (int k = 1; gap - k >= 1; k++) {
					double temp = dp[i][k] + dp[i + k][gap - k] + dis(p[i], p[i + k], i, i + k) + dis(p[i + k], p[i + gap], i + k, i + gap);
					if (dp[i][gap] > temp) {
						dp[i][gap] = temp;
						if (k > 1) {
							table[i][gap][0] = i;
							table[i][gap][1] = k;
						}
						else {
							table[i][gap][0] = -1;
							table[i][gap][1] = -1;
						}
						if (gap - k > 1) {
							table[i][gap][2] = i + k;
							table[i][gap][3] = gap-k;
						}
						else {
							table[i][gap][2] = -1;
							table[i][gap][3] = -1;
						}
					}
				}
			}
		}

		output_file << fixed << setprecision(6) << dp[0][n-1] << "\n";
		temp_table = table;
		push_num(0, n - 1);

		sort(div_p.begin(), div_p.end(), cmp);

		for (int i=0; i < div_p.size(); i++) {
			output_file << div_p[i].first << " " << div_p[i].second << "\n";
		}

		for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					delete[] table[i][j];	
				}
				delete[] table[i];
		}
		delete[] table;

		for (int i = 0; i < n; i++) {
			delete[] dp[i];
		}
		delete[] dp;

		delete[] p;

		div_p.shrink_to_fit();
		div_p.clear();
	}
	return 0;
}