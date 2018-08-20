#include"FileInfo.h"
#include<iostream>
using namespace std;

/*
	char fileName[6];
	char createTime[30];
	int fileSize;
	int address;
	int numOfBlock;
*/

// copy constructor
FileInfo::FileInfo(const FileInfo & fileInfo) {
	strcpy_s(fileName, fileInfo.fileName);
	strcpy_s(createTime, fileInfo.createTime);
	fileSize = fileInfo.fileSize;
	address = fileInfo.address;
	numOfBlock = fileInfo.numOfBlock;
}
// assign constructor
FileInfo & FileInfo::operator=(const FileInfo & fileInfo) {
	if (this == &fileInfo) return *this;
	strcpy_s(fileName, fileInfo.fileName);
	strcpy_s(createTime, fileInfo.createTime);
	fileSize = fileInfo.fileSize;
	address = fileInfo.address;
	numOfBlock = fileInfo.numOfBlock;
	return *this;
}

// default constructor
FileInfo::FileInfo() {
	fileSize = 0;
	address = 0;
	numOfBlock = 0;
	fileName[0] = '\0';
	createTime[0] = '\0';
}