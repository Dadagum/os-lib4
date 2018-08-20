#pragma once

class FileInfo {
public:
	char fileName[6];
	char createTime[40];
	int fileSize;
	int address;
	int numOfBlock;
	// copy constructor
	FileInfo(const FileInfo &);
	FileInfo();
	// assign
	FileInfo & operator=(const FileInfo &);
};