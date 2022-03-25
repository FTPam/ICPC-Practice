#include <iostream>
using namespace std;
#define MAX 8010

typedef struct Tree {
	int start, end, total;
}tree;

tree t[40000];

void buildTree(int start, int end, int n) {
	t[n] = { start, end, end - start + 1 };
	if (start == end) {
		return;
	}
	buildTree(start, (start + end) / 2, 2 * n);
	buildTree((start + end) / 2 + 1, end, 2 * n + 1);
}

int query(int pre, int n) {
	t[n].total--;
	if (t[n].start == t[n].end) {
		return t[n].start;
	}
	if (pre > t[2 * n].total) {
		return query(pre - t[2 * n].total, 2 * n + 1);
	}
	return query(pre, 2 * n);
}

int main() {
	int a[MAX];	// 输入
	int c[MAX];	// 输出
	int n;
	cin >> n;
	a[0] = 0;
	for (int i = 1; i < n; i++) {
		cin >> a[i];
	}
	buildTree(1, n, 1);
	for (int i = n - 1; i >= 0; i--) {
		c[i] = query(a[i] + 1, 1);
	}
	for (int i = 0; i < n; i++) {
		cout << c[i] << endl;
	}
}
