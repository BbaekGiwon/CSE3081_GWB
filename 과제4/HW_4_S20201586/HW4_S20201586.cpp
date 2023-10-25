#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
#include <stdint.h>

using namespace std;

typedef struct _node {
	int rank=0;
	long long nodes_have = 1;
	int64_t weight_sum = 0;
	int parent;
}Node;

Node* vertex;

int find(int a) {
	if (a != vertex[a].parent) {
		vertex[a].parent = find(vertex[a].parent);
	}
	return vertex[a].parent;
}

void uni(int a, int b, int w) {
	if (vertex[a].rank >= vertex[b].rank) {
		vertex[b].parent = a;
		vertex[a].nodes_have += vertex[b].nodes_have;
		vertex[a].weight_sum += w + vertex[b].weight_sum;
		if (vertex[a].rank == vertex[b].rank) {
			vertex[a].rank++;
		}
	}
	else {
		vertex[a].parent = b;
		vertex[b].nodes_have += vertex[a].nodes_have;
		vertex[b].weight_sum += w + vertex[a].weight_sum;
	}
}

int main(void) {
	ifstream com("commands.txt");
	vector<string> file_name;

	if (com.is_open()) {
		string temp;
		while (getline(com, temp)) {
			file_name.push_back(temp);
		}
	}
	else {
		cout << "can't find it";
	}

	
	string file_root = file_name[0] + "\\" + file_name[1];
	ifstream input(file_root);
	if (input.is_open()) {
		vector<tuple<int, int, int>> edge;
		int n_vertices, n_edges, MAX_WEIGHT;
		input >> n_vertices >> n_edges >> MAX_WEIGHT;
		vertex = new Node[n_vertices];
		for (int j = 0; j < n_vertices; j++) {
			vertex[j].parent = j;
		}
		for (int j = 0; j < n_edges; j++) {
			int a, b, c;
			input >> a >> b >> c;
			if (c <= MAX_WEIGHT) {
				
				edge.push_back({ a,b,c });
			}
		}
	
		make_heap(edge.begin(), edge.end(),[](const auto& lhs, const auto& rhs) {
			return get<2>(lhs) > get<2>(rhs);
		});
	
		int idx = 0, left_vertex=n_vertices;
		while (left_vertex > 1 && idx < n_edges) {
			int l = find(get<0>(edge[0]));
			int r = find(get<1>(edge[0]));
			int w = get<2>(edge[0]);
			pop_heap(edge.begin(), edge.end(), [](const auto& lhs, const auto& rhs) {
				return get<2>(lhs) > get<2>(rhs);
			});
			edge.pop_back();

			if (l!=r) {
				left_vertex--;
				uni(l,r,w);
			}
		idx++;
		}
		vector<pair<int, long long>> ans;
		bool* visited = new bool[n_vertices];
		for (int j = 0; j < n_vertices; j++) visited[j] = false;
		for (int j = 0; j < n_vertices; j++) {
			int temp = find(j);
			if (visited[temp] == false) {
				visited[temp] = true;
				ans.push_back({ vertex[temp].nodes_have, vertex[temp].weight_sum });
			}
		}
		sort(ans.begin(), ans.end());
		
		string output_file_root = file_name[0] + "\\" + file_name[2];
		ofstream output(output_file_root);
		output << left_vertex << "\n";
		for (int j = 0; j < ans.size(); j++) {
			output << ans[j].first << " " << ans[j].second << "\n";
		}
		delete[] vertex;
		delete[] visited;

		
	}
	else {
		cout << "File doesn't exist\n";
	}
	
	return 0;
}