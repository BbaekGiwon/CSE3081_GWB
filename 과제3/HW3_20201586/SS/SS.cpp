#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include <iomanip>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

bool** temp_table;

void print_idx(const std::vector<int>& v, int i, int j, std::vector<int>& idx) {
	if (i == 0 || j == 0) return;

	if (temp_table[i][j]) {
		if (temp_table[i - 1][j]) {
			print_idx(v, i - 1, j, idx);
		}
		else if (j >= v[i - 1] && temp_table[i - 1][j - v[i - 1]]) {
			idx.push_back(i - 1);
			print_idx(v, i - 1, j - v[i - 1], idx);
		}
	}
}
int main(void) {
	int num;
	ifstream test_command("SS_test_command.txt");
	if (!test_command.is_open()) {
		cerr << "File doesn't exist\n";
		return 1;
	}
	test_command >> num;
	for (int i = 0; i < num; i++) {
		vector<int> v;
		int n, L;
		string input, output;
		test_command >> input >> output;
		ifstream input_file(input);
		ofstream output_file(output);
		if (!input_file.is_open() || !output_file.is_open()) {
			cerr << "File doesn't exist\n";
			return 1;
		}

		input_file >> n;
		
		for (int i = 0; i < n; i++) {
			int temp;
			input_file >> temp;
			v.push_back(temp);
		}
		input_file >> L;

		bool **table = new bool* [n+1];
		for (int i = 0; i <= n; i++) {
			table[i] = new bool [L + 1];
		}

		for (int j = 1; j <= L; j++) {
			table[0][j] = false;
		}

		for (int i = 0; i <= n; i++) {
			table[i][0] = true;
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= L; j++)
			{
				if (v[i - 1] > j) {
					table[i][j] = table[i - 1][j];
				}
				else {
					table[i][j] = table[i - 1][j] || table[i - 1][j - v[i - 1]];
				}
			}
		}

		if (table[n][L]) {
			output_file << "1\n";
			temp_table = table;
			vector<int> idx;

			print_idx(v, n, L, idx);

			sort(idx.begin(), idx.end());

			output_file << idx.size() << "\n";

			for (int i = 0; i < idx.size(); i++) {
				output_file << idx[i] << "\n";
			}
		}
		else {
			output_file << "0";
		}

		

		for (int i = 0; i <= n; i++) {
			delete[] table[i];
		}
		delete[] table;

		v.shrink_to_fit();
		v.clear();
	}
	return 0;
}