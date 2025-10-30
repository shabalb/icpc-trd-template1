#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
	int** g;
	int n,m, first, second,k;
	cin >> n>>m;
	g = new int* [n];
	for (int i = 0; i < n; ++i) {
		g[i] = new int[n];
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			g[i][j] = 0;
		}
	}
	for (int i = 0; i < m; ++i) {
		cin >> first >> second;
		g[first-1][second-1] = 1;
	}
	cin >> k;
	for (int tp = 0; tp < k; ++tp) {
		cin >> first >> second;
		int s = first-1;
		queue<int> q;
		q.push(s);
		vector<bool> used(n);
		vector<int> d(n), p(n);
		used[s] = true;
		p[s] = -1;
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (int i = 0; i < n; ++i) {
				if (g[v][i] != 0) {
					if (i == second - 1) {
						cout << "Yes" << endl;
						goto exit;
					}
					int to = i;
					if (!used[to]) {
						used[to] = true;
						q.push(to);
						d[to] = d[v] + 1;
						p[to] = v;
					}
				}

			}
		}
		cout << "No"<<endl;
	exit:
		continue;
	}
	/*
	int to;
	cin >> to;
	if (!used[to])
		cout << "No path!";
	else {
		vector<int> path;
		for (int v = to; v != -1; v = p[v])
			path.push_back(v);
		reverse(path.begin(), path.end());
		cout << "Path: ";
		for (size_t i = 0; i < path.size(); ++i)
			cout << path[i] + 1 << " ";
	}*/
}