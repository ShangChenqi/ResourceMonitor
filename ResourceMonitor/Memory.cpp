#include "stdafx.h"
#include "Memory.h"
#include <string>
#include <iostream>
#include <Windows.h>

#define  GBYTES  1073741824
#define  MBYTES  1048576
#define  KBYTES  1024  
#define  DKBYTES 1024.0 

Memory::Memory()
{
	typeName = "Memory";
	description = "NULL";
	totalUsage = 0;
	availbleUsage = 0;
	usePercent = 0;
}

void Memory::setTypeName(const std::string & na) {
	typeName = na;
}

void Memory::setDescription(const std::string & des) {
	description = des;
}

void Memory::setTotalUsage() {
	//获取内存总容量
	MEMORYSTATUSEX statusex;
	statusex.dwLength = sizeof(statusex);
	if (GlobalMemoryStatusEx(&statusex)) {
		unsigned long long total = 0, remainTotal = 0;
		double decimalTotal = 0;
		remainTotal = statusex.ullTotalPhys % GBYTES;
		total = statusex.ullTotalPhys / GBYTES;
		if(remainTotal > 0)
			decimalTotal = (remainTotal / MBYTES) / DKBYTES;
		decimalTotal += (double)total;
		totalUsage = decimalTotal;
	}
}

void Memory::setAvailableUsage() {
	//获取内存可用容量
	MEMORYSTATUSEX statusex;
	statusex.dwLength = sizeof(statusex);
	if (GlobalMemoryStatusEx(&statusex)) {
		unsigned long long avl = 0, remainAvl = 0;
		double decimalAvl = 0;
		remainAvl = statusex.ullAvailPhys % GBYTES;
		avl = statusex.ullAvailPhys / GBYTES;
		if (remainAvl > 0)
			decimalAvl = (remainAvl / MBYTES) / DKBYTES;
		decimalAvl += (double)avl;
		availbleUsage = decimalAvl;
	}
}

void Memory::setUsePercent() {
	usePercent = 100.0 - availbleUsage / totalUsage * 100;
}

std::string Memory::getTypeName() const {
	return typeName;
}

std::string Memory::getDescription() const {
	return description;
}

double Memory::getTotalUsage() const {
	return totalUsage;
}

double Memory::getAvailableUsage() const {
	return availbleUsage;
}

double Memory::getUsePercent() const {
	return usePercent;
}

Memory::~Memory()
{
}
