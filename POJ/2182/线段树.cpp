#include <iostream>
using namespace std;
#define MAX 8010

typedef struct Tree {
	int start, end, total;
}tree;

tree t[40000];
int pre;

void buildTree(int start, int end, int n) {
	t[n] = { start, end, end - start + 1 };
	if (start == end) {
		return;
	}
	buildTree(start, (start + end) / 2, 2 * n);
	buildTree((start + end) / 2 + 1, end, 2 * n + 1);
}

int query(int n) {
	if (t[n].total == 0) {
		return 0;
	}
	if (t[n].start == t[n].end) {	// 如果找到叶子
		if (t[n].total == 1 && pre == 0) {		// 说明是要找的那个叶子
			t[n].total = 0;
			return t[n].start;
		}
		else {	// 是前面的叶子
			pre--;
			return 0;
		}
	}
	int a = query(2 * n);
	if (a == 0) {
		a = query(2 * n + 1);
		if (a == 0) {
			return 0;
		}
	}
	t[n].total--;
	return a;
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
		pre = a[i];
		c[i] = query(1);
	}
	for (int i = 0; i < n; i++) {
		cout << c[i] << endl;
	}
}
