#include "Cpu.h"
#include <Windows.h>
#include <qdebug.h>

Cpu::Cpu()
{
	persent = 37;
	res = GetSystemTimes(&idleTime, &kernelTime, &userTime);
	preidleTime = idleTime;
	prekernelTime = kernelTime;
	preuserTime = userTime;
	hEvent = CreateEventA(NULL, FALSE, FALSE, NULL); // 初始值为 nonsignaled ，并且每次触发后自动设置为nonsignaled

	const DWORD id = 0x80000002;
	char cpuType[49];
	memset(cpuType, 0, sizeof(cpuType));

	int cpuInfo[4] = { -1 };
	char cpu_manufacture[32] = { 0 };
	char cpu_type[32] = { 0 };
	char cpu_freq[32] = { 0 };

	__cpuid(cpuInfo, 0x80000002);
	memcpy(cpu_manufacture, cpuInfo, sizeof(cpuInfo));

	__cpuid(cpuInfo, 0x80000003);
	memcpy(cpu_type, cpuInfo, sizeof(cpuInfo));

	__cpuid(cpuInfo, 0x80000004);
	memcpy(cpu_freq, cpuInfo, sizeof(cpuInfo));

	descrip = (std::string)cpu_manufacture + (std::string)cpu_type + (std::string)cpu_freq;
}

void Cpu::setusepersent()
{
	res = GetSystemTimes(&idleTime, &kernelTime, &userTime);
	__int64 idle = CompareFileTime(preidleTime, idleTime);
	__int64 kernel = CompareFileTime(prekernelTime, kernelTime);
	__int64 user = CompareFileTime(preuserTime, userTime);

	__int64 p = (kernel + user - idle) * 100 / (kernel + user);

	preidleTime = idleTime;
	prekernelTime = kernelTime;
	preuserTime = userTime;

	persent = p;

}

int Cpu::CompareFileTime(FILETIME time1, FILETIME time2)
{
	__int64 a = time1.dwHighDateTime << 32 | time1.dwLowDateTime;
	__int64 b = time2.dwHighDateTime << 32 | time2.dwLowDateTime;

	return (b - a);
}

int Cpu::getusepersent()
{
	return persent;
}

std::string Cpu::getdescrip()
{
	return descrip;
}

Cpu::~Cpu()
{
}
