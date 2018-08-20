#pragma once
#include"FileInfo.h"

class Runner {
private:
	int* fat; 
	int round;
	int tableSize;
	int numOfFileInFat;

	void setFileName(FileInfo&);
	void setFileSize(FileInfo&);
	void allocateFat(FileInfo&);
	void setFileCreateTime(FileInfo&);
	int deleteAndFree(FileInfo* fileInTable);
	
public:
	Runner(int round, int tableSize);
	~Runner();

	void run();
	void createFAT();
	void createAndDeleteFile();
	void showFat();
	void showRootFile();
};