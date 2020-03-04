#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <algorithm>

#define SUM_START_NUM 106
#define SUM_END_NUM 170

#define WIN_NUM_WEEK 24

#define MAX_DO_COUNT 8000000 // 8145060

#define MAX_NUM 45
#define MAX_SIZE 6

using namespace std;

int winNumCheck[MAX_NUM + 1] = {0};
int goodNum[MAX_SIZE] = {0};

// 1 ~ 45 숫자중에 6개의 중복되지않은 랜덤숫자를 구한다
void getRandomNumber(int arr[]) {
	int check[MAX_NUM + 1] = {0};
	int cnt = 0;

	while(cnt < MAX_SIZE) {
		int rNum = (rand() % MAX_NUM) + 1;
		if(check[rNum] == 0 && winNumCheck[rNum] == 1) {
			arr[cnt++] = rNum;
			check[rNum] = 1;
		}
	}

	sort(arr, arr + MAX_SIZE);
}

// 숫자 배열 출력
void printNumber(int arr[]) {
	for(int i = 0; i < MAX_SIZE; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n\n");
}

// winNumCheck를 전부 1로 초기화
void checkOneWinNum() {
	for(int i = 1; i <= MAX_NUM; i++) {
		winNumCheck[i] = 1;
	}
}

// winNumCheck를 전부 0으로 초기화
void checkZeroWinNum() {
	for(int i = 1; i <= MAX_NUM; i++) {
		winNumCheck[i] = 0;
	}
}

// 가장 최근 24주의 숫자 분포도(숫자별 나온 횟수)
void getWinNum() {
	FILE *fin = fopen("winNumber.txt", "r");
	
	int winCnt[MAX_NUM + 1] = {0};

	for(int i = 0; i < WIN_NUM_WEEK; i++) {
		for(int j = 0; j < MAX_SIZE; j++) {
			int numTemp;
			fscanf(fin, "%d", &numTemp);
			winCnt[numTemp]++;
		}
	}

	for(int i = 1; i <= MAX_NUM; i++) {
		// printf("%2d# %d\n", i, winCnt[i]);
		if(3 <= winCnt[i] && winCnt[i] <= 4) 
			winNumCheck[i] = 1;
	}
}

// 최소 1개이상 나와야할 숫자 목록을 파일에서 받아온다
// 지난주 숫자 6개
void getGoodNumber() {
	FILE *fin = fopen("winNumber.txt", "r");
	for(int i = 0; i < MAX_SIZE; i++) {
		fscanf(fin, "%d", &goodNum[i]);
	}
}

// 지난주 숫자가 최소 한개이산 존재하는지 확인
bool checkGoodNumber(int arr[]) {
	bool check = false;
	for(int i = 0; i < MAX_SIZE; i++) {
		for(int j = 0; j < MAX_SIZE; j++) {
			if(arr[i] == goodNum[j]) {
				check = true;
				break;
			}
		}
		if(check) break;
	}
	return check;
}


// 홀짝 갯수 확인
// 홀수 짝 -> 3:3, 2:4, 4:2 true
// 전부 홀수이거나 전부 짝수 false
// 하나만 홀수이거나 하나만 짝수 false
bool checkTwoCnt(int arr[]) {
	int twoCnt = 0;
	for(int i = 0; i < MAX_SIZE; i++) {
		if(arr[i] % 2 == 0) twoCnt++;
	}

	if(0 < twoCnt && twoCnt < 6 && twoCnt % 2 == 0)
		return true;
	else
		return false;
}

// 낮은수 : 1 ~ 22
// 높은수 : 23 ~ 45
// 비율이 2:4, 3:3, 4:2 true
// 나머지 false
bool checkSmallCnt(int arr[]) {
	int smallCnt = 0;
	for(int i = 0; i < MAX_SIZE; i++) {
		if(arr[i] <= 22) smallCnt++;
	}

	if(0 < smallCnt && smallCnt < 6 && smallCnt % 2 == 0)
		return true;
	else
		return false;
}

// 분포 확인
// 적어도 한구간 이상 비어있어야한다
// 4칸이 비어있으면 안된다 (나중에 갯수 수정)
bool checkTen(int arr[]) {
	int tenCheck[5] = {0};
	int cnt = 0;
	for(int i = 0; i < MAX_SIZE; i++) {
		tenCheck[arr[i] / 10] = 1;
	}

	for(int i = 0; i < 5; i++) {
		if(tenCheck[i] == 0) cnt++;
	}
	if(0 < cnt && cnt < 4) 
		return true;
	else
		return false;
}

// 합이 범위 안에 있는지 확인
// 106 ~ 170
bool checkSum(int arr[]) {
	int sum = 0;
	for(int i = 0; i < MAX_SIZE; i++) {
		sum += arr[i];
	}

	if(SUM_START_NUM <= sum && sum <= SUM_END_NUM)
		return true;
	else
		return false;
}

// 4가지 조건 전부 체크
bool checkAll(int arr[]) {
	if(!checkSum(arr)) return false;
	if(!checkTen(arr)) return false;
	if(!checkTwoCnt(arr)) return false;
	if(!checkSmallCnt(arr)) return false;
	return true;
}

// 카드뽑기 원리로 몇번 먼저 랜덤 실행
void doRandNum(int arr[]) {
	for(int i = 0; i < MAX_DO_COUNT; i++) {
		getRandomNumber(arr);
	}
}

/*********************************************************************/
int totalCnt = 0;
int winCnt = 0;

void countNum(int iTemp, int length, int arr[]) {
	if(length == MAX_SIZE) {
		totalCnt++;
		if(!checkAll(arr)) return;
		winCnt++;
		return;
	}

	for(int i = iTemp; i <= MAX_NUM; i++) {
		arr[length] = i;
		countNum(i + 1, length + 1, arr);
	}
}

void countNumProcess() {
	int arr[MAX_SIZE] = {0};

	countNum(1, 0, arr);

	printf("%d\n", totalCnt);
	printf("%d\n", winCnt);
	printf("%lf\n", ((double)winCnt / (double)totalCnt) * 100);
}
/**********************************************************************/

// 확률
void caseOne() {
	int arr[MAX_SIZE] = {0};

	checkOneWinNum();

	doRandNum(arr);
	while(1) {
		getRandomNumber(arr);
		if(!checkAll(arr)) continue;
		break;
	}
	printNumber(arr);
}

// 확률 + 지난주
void caseTwo() {
	int arr[MAX_SIZE] = {0};

	checkOneWinNum();
	getGoodNumber();

	doRandNum(arr);
	while(1) {
		getRandomNumber(arr);
		if(!checkAll(arr)) continue;
		if(!checkGoodNumber(arr)) continue;
		break;
	}
	printNumber(arr);
}

// 확률 + 지난주 + 24주
void caseThree() {
	int arr[MAX_SIZE] = {0};

	checkZeroWinNum();
	getWinNum();
	getGoodNumber();

	doRandNum(arr);

	while(1) {
		getRandomNumber(arr);
		if(!checkAll(arr)) continue;
		if(!checkGoodNumber(arr)) continue;
		break;
	}
	printNumber(arr);
}

// 랜덤
void caseFour() {
	int arr[MAX_SIZE] = {0};

	checkOneWinNum();
	doRandNum(arr);
	printNumber(arr);
}

// erase till six number
void cookieBottle() {
	int arr[MAX_NUM] = {0};
	

	for(int i = 0; i < MAX_NUM; i++) {
		arr[i] = i + 1;
	}

	for(int i = MAX_NUM; i >= MAX_SIZE + 1; i--) {
		random_shuffle(arr, arr + i);
	}

	sort(arr, arr + MAX_SIZE);


	for(int i = 0; i < MAX_SIZE; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n\n");
}

// by calc
void cookieBottleByCalc() {
	int arr[MAX_NUM] = {0};
	
	while(1) {

		for(int i = 0; i < MAX_NUM; i++) {
			arr[i] = i + 1;
		}

		for(int i = MAX_NUM; i >= MAX_SIZE + 1; i--) {
			random_shuffle(arr, arr + i);
		}

		sort(arr, arr + MAX_SIZE);

		if(checkAll(arr)) {

			for(int i = 0; i < MAX_SIZE; i++) {
				printf("%d ", arr[i]);
			}
			printf("\n\n");
			break;
		}
	}

}

int main() {
	srand(time(NULL));

	//countNumProcess();

	/*
	caseOne();
	caseTwo();
	caseThree();
	caseFour();
	*/

	int doTemp[MAX_SIZE] = {0};
	checkOneWinNum();
	doRandNum(doTemp);

	for(int i = 0; i < 5; i++) {

		//cookieBottle();
	}
	//caseThree();
	
	for(int i = 0; i < 5; i++) {
		cookieBottleByCalc();
	}
	
	return 0;
}
