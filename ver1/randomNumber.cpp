#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <algorithm>

#define SUM_AVERAGE 120
#define MAX_DO_COUNT 1358480 // 8145060
#define MAX_ANS_COUNT 5
#define MAX_NUM 45
#define MAX_SIZE 6

using namespace std;

int goodNumArr[MAX_NUM] = {0}, gNSize = 0;
int goodNumCheck[MAX_NUM + 1] = {0};
int badNumArr[MAX_NUM] = {0}, bNSize = 0;
int badNumCheck[MAX_NUM + 1] = {0};

int ansCount = MAX_ANS_COUNT;
int doCount = (MAX_DO_COUNT - 1000);

int numCountArr[MAX_NUM + 1] = {0};

void getRandomNumber(int arr[]) {
	int check[MAX_NUM + 1] = {0};
	int cnt = 0;

	while(cnt < MAX_SIZE) {
		int rNum = (rand() % MAX_NUM) + 1;
		if(check[rNum] == 0) {
			arr[cnt++] = rNum;
			check[rNum] = 1;
			numCountArr[rNum]++;
		}
	}

	sort(arr, arr + MAX_SIZE);
}

void printNumCountArr() {
	int check[MAX_NUM + 1] = {0};
	int max;
	int indexTemp;
	int sum = 0;

	for(int i = 1; i <= MAX_NUM; i++) {
		max = -1;
		for(int j = 1; j <= MAX_NUM; j++) {
			if(check[j] == 0 && max < numCountArr[j]) {
				max = numCountArr[j];
				indexTemp = j;
			}
		}

		printf("%2d : %d\n", indexTemp, numCountArr[indexTemp]);
		sum += numCountArr[indexTemp];

		check[indexTemp] = 1;
	}

	printf("\n%d\n", sum);
}

void printNumber(int arr[], int size) {
	for(int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

bool checkNumber(int num) {
	if(1 <= num && num <= MAX_NUM) {
		if(goodNumCheck[num] == 0 && badNumCheck[num] == 0)
			return true;
		else return false;
	}
	else return false;
}

void printException() {
	printf("\n");
	printf("\t번호를 다시 입력해주세요\n");
	sleep(3);
}

void getGoodNumber() {
	FILE *fp = fopen("goodNumber.txt", "r");
	int nTemp;

	while(fscanf(fp, "%d", &nTemp) != EOF) {
		goodNumArr[gNSize++] = nTemp;
		goodNumCheck[nTemp] = 1;
	}

	sort(goodNumArr, goodNumArr + gNSize);
}

void getBadNumber() {
	FILE *fp = fopen("badNumber.txt", "r");
	int nTemp;

	while(fscanf(fp, "%d", &nTemp) != EOF) {
		badNumArr[bNSize++] = nTemp;
		badNumCheck[nTemp] = 1;
	}

	sort(badNumArr, badNumArr + bNSize);

}

void homeOutput() {
	getGoodNumber();
	getBadNumber();

	while(1) {

		system("clear");

		printf("\n\n");
		printf("\t1. 가능성 숫자\n");
		printf("\t-> ");
		printNumber(goodNumArr, gNSize);
		printf("\n");

		printf("\t2. 제외 숫자\n");
		printf("\t-> ");
		printNumber(badNumArr, bNSize);
		printf("\n");

		printf("\t3. 예상 숫자 갯수\n");
		printf("\t->  %d\n\n", ansCount); // 5

		printf("\t4. 추첨 횟수\n");
		printf("\t-> %d\n\n", doCount); // 8,000,000

		printf("\t5. 추첨 시작\n\n");

		printf("\t6. 종료\n\n");

		printf("\t번호를 입력하세요 : ");
		int temp, nTemp;
		scanf("%d", &temp);
		printf("\n");

		if(temp == 1) {
			printf("\t숫자를 입력해주세요 : ");

			scanf("%d", &nTemp);
			
			if(checkNumber(nTemp)) {
				goodNumArr[gNSize++] = nTemp;
				goodNumCheck[nTemp] = 1;

				sort(goodNumArr, goodNumArr + gNSize);
			}
			else printException();
		}
		else if(temp == 2) {
			printf("\t숫자를 입력해주세요 : ");

			scanf("%d", &nTemp);

			if(checkNumber(nTemp)) {
				badNumArr[bNSize++] = nTemp;
				badNumCheck[nTemp] = 1;

				sort(badNumArr, badNumArr + bNSize);
			}
			else printException();
		}
		else if(temp == 3) {
			printf("\t숫자를 입력해주세요 : ");
			scanf("%d", &nTemp);
			ansCount = nTemp;
		}
		else if(temp == 4) {
			printf("\t숫자를 입력해주세요 : ");
			scanf("%d", &nTemp);
			doCount = nTemp;
		}
		else if(temp == 5) {
			printf("\n");

			int ansCntTemp = 0;
			int arr[MAX_SIZE] = {0};

			for(int i = 0; i < doCount; i++) {
				getRandomNumber(arr);
			}

			while(ansCntTemp < ansCount) {
				int numSum = 0;
				int gNCheck = 0;
				int bNCheck = 0;

				if(gNSize == 0) gNCheck = 1;

				getRandomNumber(arr);

				for(int i = 0; i < MAX_SIZE; i++) {
					numSum += arr[i];

					for(int j = 0; j < gNSize; j++) {
						if(arr[i] == goodNumArr[j]) {
							gNCheck = 1;
							break;
						}
					}
					for(int j = 0; j < bNSize; j++) {
						if(arr[i] == badNumArr[j]) {
							bNCheck = 1;
							break;
						}
					}
				}

				if(gNCheck == 1 && bNCheck == 0 && numSum >= SUM_AVERAGE) {
					ansCntTemp++;
					printf("\t-> ");
					printNumber(arr, MAX_SIZE);
				}
			}

			printf("\n");

			printNumCountArr();
			printf("\n");
			break;
		}
		else if(temp == 6) {
			system("clear");
			break;
		}
		else {
			printException();
		}
	}
}


int main() {
	srand(time(NULL));

	homeOutput();

	return 0;
}
