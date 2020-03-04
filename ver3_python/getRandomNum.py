import random
import math

MAX_COMB_SIZE = 8145060
NUM_SIZE = 45

def getPrimeNum(primeNum):
    primeNumList = [0 for i in range(MAX_COMB_SIZE + 1)]
    primeNumList[1]
    sqrtNum = int(math.sqrt(MAX_COMB_SIZE))
    for i in range(2, sqrtNum + 1):
        if primeNumList[i] == 1:
            continue

        primeNum.append(i)
        j = 2
        while i * j <= MAX_COMB_SIZE:
            primeNumList[i * j] = 1
            j += 1
    for i in range(sqrtNum, MAX_COMB_SIZE + 1):
        if primeNumList[i] == 0:
            primeNum.append(i)

def writeToFile(primeNum):
    f = open("primeNum.txt", 'w')
    for pn in primeNum:
        f.write(str(pn) + '\n')
    f.close()

def getRandomNum():
    numList = list(range(1, NUM_SIZE + 1))
    for i in range(NUM_SIZE - 6):
        numList.remove(random.choice(numList))
    return " ".join(map(str, numList))

def prime():
    primeNum = []
    getPrimeNum(primeNum)
    writeToFile(primeNum)

def readFromFile():
    primeNum = []
    f = open("primeNum.txt", "r")
    lines = f.readlines()
    for line in lines:
        primeNum.append(int(line))
    f.close()
    return primeNum

def printFiveSetByPrimeNum(primeNum):
    printTime = set()
    while len(printTime) < 5:
        numTemp = random.choice(primeNum)
        printTime.add(numTemp)
    
    cnt = 0   
    for i in range(1, MAX_COMB_SIZE + 1):
        numStrTemp = getRandomNum()
        if i in printTime:
            print(numStrTemp)
            cnt += 1
            if cnt == 5:
                break

#prime()
primeNum = readFromFile()
printFiveSetByPrimeNum(primeNum)
