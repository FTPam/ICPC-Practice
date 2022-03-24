#include <iostream>
using namespace std;

#define MAX 8010

int main() {
	int a[MAX];	// 输入
	int b[MAX];	// 辅助
	int c[MAX];	// 输出
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		b[i] = i + 1;
	}
	for (int i = n - 1; i >= 0; i--) {
		int t = a[i];
		for (int j = 0; j < n; j++) {
			if (t == 0 && b[j] != 0) {
				c[i] = b[j];
				b[j] = 0;
				break;
			}
			if (b[j] != 0) {
				t--;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		cout << c[i] << " ";
	}
}
