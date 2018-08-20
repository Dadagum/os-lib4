#include"Runner.h"
#include<iostream>
#include<fstream>
#include<ctime>
using namespace std;

/*
private member:
	int* fat;
	int round;
	int tableSize;
	int numOfFileInFat;
*/

Runner::Runner(int round, int tableSize) {
	this->round = round;
	this->tableSize = tableSize;
	this->numOfFileInFat = 0;
	fat = NULL;
	srand((unsigned int)(time(NULL)));
}

void Runner::run() {
	createFAT();
	createAndDeleteFile();
	showRootFile();
	showFat();
}

void Runner::showFat() {
	for (int i = 0, count = 0; i < tableSize; i++) {
		if (fat[i] != 0) {
			cout << "[" << i << "]" << " : " << fat[i] << " ";
			count++;
		}
		if (count % 10 == 0 && count != 0) {
			cout << endl;
			count = 0;
		}
	}
	cout << endl;
}

void Runner::createFAT() {
	if (fat != NULL) delete [] fat;
	fat = new int[tableSize];
	for (int i = 0; i < tableSize; i++) fat[i] = 0;
}

void Runner::setFileName(FileInfo& fileInfo) {
	static char ch = 'a';
	for (int i = 0; i < 5; i++) fileInfo.fileName[i] = ch;
	ch++;
	fileInfo.fileName[5] = '\0';
}

void Runner::allocateFat(FileInfo &f) {
	// calculate num of blocks that this file needs
	f.numOfBlock = f.fileSize % 4 == 0 ? f.fileSize / 4 : f.fileSize / 4 + 1;
	int numOfBlock = f.numOfBlock;
	// find the first free block
	int startPos = 0;
	for (; startPos < tableSize && fat[startPos] != 0; startPos++);
	f.address = startPos; // set f.address to this
	numOfBlock--;

	int pre = startPos;
	while (numOfBlock != 0) {
		for (startPos++; startPos < tableSize && fat[startPos] != 0; startPos++);
		fat[pre] = startPos;
		pre = startPos;
		numOfBlock--;
	}
	fat[pre] = -1;
	// update num of file in memory
	numOfFileInFat++;
}

void Runner::setFileSize(FileInfo& fileInfo) {
	int size = rand() % 100 + 1;
	fileInfo.fileSize = size;
}

void Runner::setFileCreateTime(FileInfo& f) {
	time_t now = time(0);
	ctime_s(f.createTime, sizeof f.createTime, &now);
	int place;
	for (place = 0; place < 30 && f.createTime[place] != '\n' && f.createTime[place] != '\r'; place++);
	f.createTime[place] = '\0';
}

void Runner::createAndDeleteFile() {
	FileInfo memory[20]; // store fileInfo in memory first intead of record them in disk right now.
	int pre = 0; // insert pos in memory
	FileInfo f1;
	for (int i = 0; i < round; i++) {
		// create file and allocate fat
		for (int j = 0; j < 4; j++, pre = numOfFileInFat) {
			setFileName(f1); // set fileName;
			setFileSize(f1); // set fileSize
			allocateFat(f1); // set fileAddress and block size
			setFileCreateTime(f1);
			memory[pre] = f1;
		}
		// delete file and free fat
		pre = deleteAndFree(memory);
	}
	// open root file
	ofstream rootFile("D:/testing/c/root.dat", ios_base::out | ios_base::binary);
	if (!rootFile.is_open()) {
	cout << "fail to open file!" << endl;
	exit(EXIT_FAILURE);
	}
	// record file in memory info into root.dat:
	for (int i = 0; i < numOfFileInFat; i++) rootFile.write((char *)&memory[i], sizeof f1);
	// close file
	rootFile.close();
}

int Runner::deleteAndFree(FileInfo* memory) {
	// determine the block which to be removed
	int next = rand() % numOfFileInFat;
	// find the first block of fat
	int start = memory[next].address;
	int pre = start; // record 
	for (int i = start; fat[i] != -1; i = pre) { 
		pre = fat[i];
		fat[i] = 0; 
	} // reset fat
	fat[pre] = 0;
	// update file in memory currently
	numOfFileInFat--;
	// return the next pos to be inserted
	return next;
}

void Runner::showRootFile() {
	// open root file
	ifstream fin;
	fin.open("D:/testing/c/root.dat", ios_base::out);
	if (!fin.is_open()) {
		cout << "fail to open file!" << endl;
		exit(EXIT_FAILURE);
	}
	// read fileInfo
	FileInfo f1;
	cout << "name  file's create time       len start numOfBlock" << endl;
	while (fin.read((char *) &f1, sizeof f1)) {
		cout << f1.fileName << " " << f1.createTime << " " << f1.fileSize << " " << f1.address << " " << f1.numOfBlock << endl;
	}
	// close file
	fin.close();
}

Runner::~Runner() {
	delete[] fat;
}