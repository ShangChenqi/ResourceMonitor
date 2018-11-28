#ifndef CPU_H
#define CPU_H

#include <Windows.h>
#include "stdafx.h"
#include <string>

class Cpu
{
private:
	HANDLE hEvent;
	BOOL res;
	FILETIME preidleTime;
	FILETIME prekernelTime;
	FILETIME preuserTime;
	FILETIME idleTime;
	FILETIME kernelTime;
	FILETIME userTime;
	int persent;
	std::string descrip;
public:
	Cpu();
	void setusepersent();
	int getusepersent();
	std::string getdescrip();
	int CompareFileTime(FILETIME time1, FILETIME time2);
	~Cpu();
};

#endif // !CPU_H