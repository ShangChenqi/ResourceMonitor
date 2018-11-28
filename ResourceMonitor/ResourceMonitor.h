#pragma once

#include <QtWidgets/QDialog>
#include "ui_ResourceMonitor.h"
#include "Drawprogressbar.h"
#include "qtimer.h"
#include "qfile.h"
#include "Memory.h"
#include "Cpu.h"
#include "Internet.h"
#include "qcustomplot.h"
#include "Memento.h"

class ResourceMonitor : public QDialog
{
	Q_OBJECT

public:
	ResourceMonitor(QWidget *parent = Q_NULLPTR);
	void init();
	void savedata();
	void fillColorList(QComboBox * cbb);
	

public slots:
	void submit();
	void reset();
	void update();

private:
	Ui::ResourceMonitorClass ui;
	Drawprogressbar * progressbar;	//绘制内存进度条
	Drawprogressbar * pregressbar_cpu;
	QTimer * mytimer;
	Memory * memory;
	Cpu * cpu;
	Internet * internet;
	State * state;
	int seconds;
	int count;
};
