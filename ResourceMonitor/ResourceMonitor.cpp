#include "ResourceMonitor.h"
#include <qdebug.h>

ResourceMonitor::ResourceMonitor(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//初始化
	init();
}

void ResourceMonitor::init()
{
	//初始化程序时间
	seconds = 0;
	count = 0;

	//初始化三个tab
	ui.tabWidget->setTabText(0, "Simple view");
	ui.tabWidget->setTabText(1, "Detailed view");
	ui.tabWidget->setTabText(2, "Setting up");
	ui.tabWidget->setCurrentIndex(0);

	//初始化内存
	memory = new Memory();
	memory->setAvailableUsage();
	memory->setTotalUsage();
	memory->setUsePercent();

	//初始化cpu
	cpu = new Cpu();

	//初始化网络
	internet = new Internet();
	internet->setDownSpeed();
	internet->setOnSpeed();

	//加载用户设置
	Caretake caretake;
	state = new State();
	state->load(caretake.Load());

	//初始化环形百分比
	progressbar = new Drawprogressbar(ui.widget, ui.widget->height(), ui.widget->width(), memory->getUsePercent(), "memory");
	pregressbar_cpu = new Drawprogressbar(ui.widget_2, ui.widget_2->height(), ui.widget_2->width(), cpu->getusepersent(), "cpu");

	//初始化Label组件
	QString str1 = "Memory : ";
	QFont ft1 = QFont("Microsoft YaHei", 10, QFont::Bold);
	ui.label1->setFont(ft1);
	ui.label1->setText(str1);

	QString str2 = "";
	str2.append(QString::number(int((memory->getTotalUsage() - memory->getAvailableUsage()) * 100) / 100.0));
	QFont ft2 = QFont("Microsoft YaHei", 10, QFont::Bold);
	ft2.setItalic(true);
	QPalette palette;
	palette.setColor(QPalette::WindowText, QColor(255, 107, 107));	//������ɫ
	ui.label2->setPalette(palette);
	ui.label2->setFont(ft2);
	ui.label2->setText(str2);

	QString str3 = "/  ";
	str3.append(QString::number(int(memory->getTotalUsage() * 100) / 100.0));
	str3.append(" (GB)");
	ui.label3->setFont(ft2);
	ui.label3->setText(str3);

	QString str4 = QString::fromStdString(cpu->getdescrip());
	ui.label4->setFont(ft1);
	ui.label4->setText(str4);

	ui.label5->setFont(ft1);
	ui.label5->setText("Basic setting");

	ui.label6->setFont(ft1);
	ui.label6->setText("Color setting");

	QFont ft3 = QFont("Microsoft YaHei", 9);
	ui.dataSave->setFont(ft3);
	ui.highDensity->setFont(ft3);

	QPalette palette1;
	palette1.setColor(QPalette::WindowText, state->getdownspeedLine());
	ui.labelDown->setPalette(palette1);
	ui.labelDown->setFont(ft1);
	ui.labelDown->setText(QString::number(int(internet->getDownSpeed() * 100) / 100.0) + "KB/S");

	QPalette palette2;
	palette2.setColor(QPalette::WindowText, state->getonspeedLine());
	ui.labelOn->setPalette(palette2);
	ui.labelOn->setFont(ft1);
	ui.labelOn->setText(QString::number(int(internet->getOnSpeed() * 100) / 100.0) + "KB/S");

	QPalette palette3;
	palette3.setColor(QPalette::WindowText, state->getcpuLine());
	ui.labelCpu->setPalette(palette3);
	ui.labelCpu->setFont(ft1);
	ui.labelCpu->setText(QString::number(cpu->getusepersent()) + "%");

	QPalette palette4;
	palette4.setColor(QPalette::WindowText, state->getmemoryLine());
	ui.labelMemory->setPalette(palette4);
	ui.labelMemory->setFont(ft1);
	ui.labelMemory->setText(QString::number((int)memory->getUsePercent()) + "%");

	ui.label7->setFont(ft3);
	ui.label7->setAlignment(Qt::AlignRight);
	ui.label8->setFont(ft3);
	ui.label8->setAlignment(Qt::AlignRight);
	ui.label9->setFont(ft3);
	ui.label9->setAlignment(Qt::AlignRight);
	ui.label10->setFont(ft3);
	ui.label10->setAlignment(Qt::AlignRight);

	fillColorList(ui.cpuLine);
	fillColorList(ui.memoryLine);
	fillColorList(ui.downSpeedLine);
	fillColorList(ui.onSpeedLine);

	ui.cpuLine->setCurrentIndex(10);
	ui.memoryLine->setCurrentIndex(20);
	ui.downSpeedLine->setCurrentIndex(30);
	ui.onSpeedLine->setCurrentIndex(40);

	//初始化定时器
	mytimer = new QTimer(this);
	mytimer->start(1000);

	//初始化折线图
	ui.widget_3->legend->setVisible(true);		//设置图例
	ui.widget_3->legend->setBrush(QColor(139, 126, 102, 60));	//设置图例颜色和透明度
	ui.widget_3->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignLeft);		//设置图例出现的位置

	ui.widget_3->xAxis->setLabel("Time(s)");	//x轴
	ui.widget_3->yAxis->setLabel("Rate(%)");	//左y轴
	ui.widget_3->yAxis2->setLabel("Internet speed(kb/s)");	//右y轴
	ui.widget_3->yAxis->setRange(0, 100);	//设置左y轴取值范围
	ui.widget_3->yAxis2->setRange(0, internet->getDownSpeed() + 50);	//设置右y轴取值范围
	ui.widget_3->yAxis2->setVisible(true);

	if (state->gethighDensity())
	{
		ui.widget_3->xAxis->grid()->setSubGridVisible(true);
		ui.widget_3->yAxis->grid()->setSubGridVisible(true);
	}

	ui.widget_3->addGraph();	//添加内存数据曲线
	ui.widget_3->graph(0)->setPen(QPen(state->getmemoryLine()));
	ui.widget_3->graph(0)->setName("MemoryInfo");

	ui.widget_3->addGraph();	//添加cpu数据曲线
	ui.widget_3->graph(1)->setPen(QPen(state->getcpuLine()));
	ui.widget_3->graph(1)->setName("CpuInfo");

	ui.widget_3->addGraph(ui.widget_3->xAxis, ui.widget_3->yAxis2);	//添加下载网速数据曲线
	ui.widget_3->graph(2)->setPen(QPen(state->getdownspeedLine()));
	ui.widget_3->graph(2)->setName("DownSpeedInfo");

	ui.widget_3->addGraph(ui.widget_3->xAxis, ui.widget_3->yAxis2);	//添加上传网速数据曲线
	ui.widget_3->graph(3)->setPen(QPen(state->getonspeedLine()));
	ui.widget_3->graph(3)->setName("OnSpeedInfo");

	// connect 函数
	connect(ui.submit, SIGNAL(clicked()), this, SLOT(submit()));
	connect(ui.quit, SIGNAL(clicked()), this, SLOT(reset()));
	connect(mytimer, SIGNAL(timeout()), this, SLOT(update()));
}

void ResourceMonitor::update()
{
	seconds++;
	//�����ڴ�����
	memory->setAvailableUsage();
	memory->setUsePercent();
	progressbar->resetpersent(memory->getUsePercent());
	progressbar->repaint();
	QString str = "";
	str.append(QString::number(int((memory->getTotalUsage() - memory->getAvailableUsage()) * 100) / 100.0));
	ui.label2->setText(str);

	//����Cpu����
	cpu->setusepersent();
	pregressbar_cpu->resetpersent(cpu->getusepersent());
	pregressbar_cpu->repaint();

	//������������
	internet->setDownSpeed();
	internet->setOnSpeed();

	QPalette palette1;
	palette1.setColor(QPalette::WindowText, state->getdownspeedLine());
	ui.labelDown->setPalette(palette1);
	ui.labelDown->setText(QString::number(int(internet->getDownSpeed() * 100) / 100.0) + "KB/S");
	
	QPalette palette2;
	palette2.setColor(QPalette::WindowText, state->getonspeedLine());
	ui.labelOn->setPalette(palette2);
	ui.labelOn->setText(QString::number(int(internet->getOnSpeed() * 100) / 100.0) + "KB/S");

	QPalette palette3;
	palette3.setColor(QPalette::WindowText, state->getcpuLine());
	ui.labelCpu->setPalette(palette3);
	ui.labelCpu->setText(QString::number(cpu->getusepersent()) + "%");

	QPalette palette4;
	palette4.setColor(QPalette::WindowText, state->getmemoryLine());
	ui.labelMemory->setPalette(palette4);
	ui.labelMemory->setText(QString::number((int)memory->getUsePercent()) + "%");


	//������������
	ui.widget_3->graph(0)->addData(seconds, memory->getUsePercent());
	ui.widget_3->graph(1)->addData(seconds, cpu->getusepersent());
	ui.widget_3->graph(2)->addData(seconds, internet->getDownSpeed());
	ui.widget_3->graph(3)->addData(seconds, internet->getOnSpeed());

	//������y��ȡֵ��Χ(��ֵ����30s)
	if (count > 30)
	{
		ui.widget_3->yAxis2->setRange(0, internet->getDownSpeed() + 50);
		count = 0;
	}
	else
		count++;

	//����x�᷶Χ
	ui.widget_3->xAxis->setRange(seconds + 0.25, 60, Qt::AlignRight);
	//�ػ�����ͼ
	ui.widget_3->replot();

	if(state->getsaveData())
		savedata();
}

void ResourceMonitor::submit()
{
	if (ui.dataSave->isChecked())
		state->setSaveData(true);
	else
		state->setSaveData(false);

	if (ui.highDensity->isChecked())
	{
		state->setHighDensity(true);		
		ui.widget_3->xAxis->grid()->setSubGridVisible(true);
		ui.widget_3->yAxis->grid()->setSubGridVisible(true);
	}
	else
	{
		state->setHighDensity(false);
		ui.widget_3->xAxis->grid()->setSubGridVisible(false);
		ui.widget_3->yAxis->grid()->setSubGridVisible(false);
	}

	QStringList colorList = QColor::colorNames();

	state->setCpuLine(colorList[ui.cpuLine->currentIndex()]);
	state->setMemoryLine(colorList[ui.memoryLine->currentIndex()]);
	state->setOnSpeedLine(colorList[ui.onSpeedLine->currentIndex()]);
	state->setDownSpeedLine(colorList[ui.downSpeedLine->currentIndex()]);

	ui.widget_3->graph(0)->setPen(QPen(state->getmemoryLine()));
	ui.widget_3->graph(1)->setPen(QPen(state->getcpuLine()));
	ui.widget_3->graph(2)->setPen(QPen(state->getdownspeedLine()));
	ui.widget_3->graph(3)->setPen(QPen(state->getonspeedLine()));

	//保存设置信息
	Caretake caretake;
	caretake.Save(state->save());
	QMessageBox::information(NULL, "Success", "Submitted successfully", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

}

void ResourceMonitor::reset()
{
	state->reset();

	if (state->gethighDensity())
	{
		ui.widget_3->xAxis->grid()->setSubGridVisible(true);
		ui.widget_3->yAxis->grid()->setSubGridVisible(true);
	}
	else
	{
		state->setHighDensity(false);
		ui.widget_3->xAxis->grid()->setSubGridVisible(false);
		ui.widget_3->yAxis->grid()->setSubGridVisible(false);
	}

	ui.widget_3->graph(0)->setPen(QPen(state->getmemoryLine()));
	ui.widget_3->graph(1)->setPen(QPen(state->getcpuLine()));
	ui.widget_3->graph(2)->setPen(QPen(state->getdownspeedLine()));
	ui.widget_3->graph(3)->setPen(QPen(state->getonspeedLine()));

	Caretake caretake;
	caretake.Save(state->save());

	QMessageBox::information(NULL, "Success", "Reset successful", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

}

void ResourceMonitor::savedata()
{
	//将数据保存到文件
	QString path1 = "memorydata.txt";
	QString path2 = "cpudata.txt";
	QString path3 = "internet.txt";

	QFile file1(path1);
	QFile file2(path2);
	QFile file3(path3);

	if (!file1.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append) || !file2.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append) || !file3.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
	{
		QMessageBox::critical(nullptr, "Tip", "Can't create files");
		return;
	}

	QDateTime current = QDateTime::currentDateTime();	//获取当前系统时间
	QString time = current.toString("yyyy.MM.dd hh:mm:ss");

	QString memoryInfo = time + "	" + QString::number((int)memory->getUsePercent(), 10) + "%\n";
	QString cpuInfo = time + "	" + QString::number(cpu->getusepersent(), 10) + "%\n";
	QString internetInfo = time + "	 " + QString::number((int)internet->getDownSpeed(), 10) + "KB" + "	 " + QString::number((int)internet->getOnSpeed(), 10) + "KB\n";

	file1.write(memoryInfo.toStdString().c_str());
	file2.write(cpuInfo.toStdString().c_str());
	file3.write(internetInfo.toStdString().c_str());

	file1.close();
	file2.close();
	file3.close();
}

void ResourceMonitor::fillColorList(QComboBox * cbb)
{
	QStringList colorNameList = QColor::colorNames();
	QString colorName;
	foreach(colorName, colorNameList)
	{
		QPixmap pix_color(70, 20);
		pix_color.fill(QColor(colorName));
		cbb->addItem(QIcon(pix_color), NULL);
		cbb->setIconSize(QSize(70, 20));
		cbb->setSizeAdjustPolicy(QComboBox::AdjustToContents);   //���������б�ĳߴ�������ݵĴ�С  
	}
}
