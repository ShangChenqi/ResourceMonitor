#pragma once
#include <qcolor.h>
#ifndef MEMENTO_H
#define MEMENTO_H

class Memento
{
public:
	bool saveData;	
	bool highDensity;
	QColor cpuLine;		
	QColor memoryLine;
	QColor onSpeedLine;
	QColor downSpeedLine;

public:
	Memento(bool sd, bool hd, QColor cl, QColor ml, QColor onl, QColor downl);
	~Memento();
};

class State
{
private:
	bool saveData;
	bool highDensity;
	QColor cpuLine;
	QColor memoryLine;
	QColor onSpeedLine;
	QColor downSpeedLine;
public:
	State();
	Memento save();
	void load(Memento memento);

	void setSaveData(bool sd)
	{
		saveData = sd;
	}

	void setHighDensity(bool hd)
	{
		highDensity = hd;
	}

	void setCpuLine(QColor cp)
	{
		cpuLine = cp;
	}

	void setMemoryLine(QColor ml)
	{
		memoryLine = ml;
	}

	void setOnSpeedLine(QColor onl)
	{
		onSpeedLine = onl;
	}

	void setDownSpeedLine(QColor downl)
	{
		downSpeedLine = downl;
	}

	bool getsaveData()
	{
		return saveData;
	}

	bool gethighDensity()
	{
		return highDensity;
	}

	QColor getcpuLine()
	{
		return cpuLine;
	}

	QColor getmemoryLine()
	{
		return memoryLine;
	}

	QColor getonspeedLine()
	{
		return onSpeedLine;
	}

	QColor getdownspeedLine()
	{
		return downSpeedLine;
	}

	void reset();
	~State();
};

class Caretake
{
public:
	Caretake();
	void Save(Memento menento);
	Memento Load();
};


#endif // !MEMENTO_H