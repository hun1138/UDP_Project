#include <stdio.h>

#define MAX_NUM 45
#define MAX_SIZE 300

#define START_NUM 106
#define END_NUM 170

int numCntArr[MAX_SIZE] = {0};
int totalCnt = 0;

int goodCnt = 0; // 128 148 // 100 176

void numCnt(int iTemp, int sum, int length) {
	if(length == 6) {
		numCntArr[sum]++;
		totalCnt++;
		if(START_NUM <= sum && sum <= END_NUM) {
			goodCnt++;
		}
		return;
	}
	for(int i = iTemp; i <= MAX_NUM ;i++) {
		numCnt(i + 1, sum + i, length + 1);
	}
}

void output() {
	for(int i = 21; i <= MAX_SIZE; i++) {
		if(numCntArr[i] == 0) break;
		printf("%3d# %d\n", i, numCntArr[i]);
	}

	printf("\n%d\n", totalCnt);
	printf("%d\n", goodCnt);
	printf("%lf\n", ((double)goodCnt / (double)totalCnt) * 100);
}

void cntWinNumber() {
	FILE *in = fopen("winNumber.txt", "r");
	int cnt = 0;
	int winCnt = 0;
	bool check = true;
	for(int i = 0; ; i++) { // 782
		int sum = 0;
		for(int j = 0; j < 6; j++) {
			int num;
			if(fscanf(in, "%d", &num) == EOF) {
				check = false;
				break;
			}
			sum += num;
		}
		if(!check) break;
		if(START_NUM <= sum && sum <= END_NUM) cnt++;
		winCnt++;
	}

	printf("win : %d\ncnt : %d\n", winCnt, cnt);
	printf("%lf\n", ((double)cnt / (double)winCnt) * 100);
}

int main() {
	numCnt(1, 0, 0);
	output();
	cntWinNumber();
	return 0;
}
