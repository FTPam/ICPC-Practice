#include <bits/stdc++.h>
using namespace std;

#define MAX_LEN 362880
#define NUM 9
#define Swap(a, b) {int T = a; a = b; b = T;}

int ha[MAX_LEN] = { 0 };

typedef struct Node {
	int a[NUM];	// 九宫格
	int num;	// 九宫格代表的数字
	int zerop;	// 零的位置
	int move;	// 移动次数
}node;

// 没有重复则返回true
bool Cantor(node b) {
	int a = b.num;
	// 哈希
	int rec[10];	// 记录每个数字是否已经被前面的位用过
	for (int i = 0; i < 10; i++) {
		rec[i] = 1;	// 初始化
	}
	int value = 0;	// 哈希值
	int times = 8 * 7 * 6 * 5 * 4 * 3 * 2;
	for (int i = 0; i < NUM - 1; i++) {
		int p = a % 10;	// 获取到当前位
		a = a / 10;
		int num = 0;
		for (int i = 0; i < p; i++) {
			num += rec[i];	// 小于当前位且还未被用过的位数
		}
		value += num * times;	// 计算当前位小于当前排列的排列数量
		if (NUM - i - 1 > 0) {
			times /= (NUM - i - 1);		// 阶乘数-1
		}
		rec[p] = 0;				// 标记为使用过
	}
	// 判重
	if (ha[value]) {
		return false;
	}
	else {
		ha[value] = 1;
		return true;
	}
}

int main() {
	node start, des;
	start.move = 0;
	des.move = 0;
	start.num = 0;
	des.num = 0;
	// 九宫格的第九格代表的是个位数
	for (int i = 0; i < NUM; i++) {
		cin >> start.a[i];
		start.num = start.num * 10 + start.a[i];
		if (!start.a[i]) {
			start.zerop = i;	// 获取零在九宫格中的位置
		}
	}
	for (int i = 0; i < NUM; i++) {
		cin >> des.a[i];
		des.num = des.num * 10 + des.a[i];
		if (!des.a[i]) {
			des.zerop = i;	// 获取零在九宫格中的位置
		}
	}

	Cantor(start);	// 记录一下初始状态
	int move[] = { -3,-1,1,3 };	// 零在九宫格中的位移操作
	queue<node>a;
	a.push(start);
	bool found = false;	// 记录是否已经找到目标
	while (!a.empty() && !found) {
		node p = a.front();
		for (int i = 0; i < 4; i++) {
			if (p.zerop + move[i] >= 0 && p.zerop + move[i] < NUM) {
				if ((p.zerop % 3 == 0 && move[i] == -1) || (p.zerop % 3 == 2 && move[i] == 1)) {
					continue;
				}
				node en = p;	// 复制一个用来入队列的结点
				en.move = p.move + 1;	// 移动步数增加
				en.zerop = p.zerop + move[i];	// 改变zerop
				Swap(en.a[en.zerop], en.a[p.zerop]);	// 交换零的位置
				en.num = 0;
				for (int i = 0; i < NUM; i++) {
					en.num = en.num * 10 + en.a[i];
				}
				if (en.num == des.num) {
					found = true;	// 已经找到
					cout << en.move;
					break;
				}
				if (Cantor(en)) {
					a.push(en);	//入队列
				}
			}
		}
		a.pop();	// 弹出当前队头元素
	}
}
