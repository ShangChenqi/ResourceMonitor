#include "Memento.h"
#include <qstring.h>
#include <qfile.h>
#include <qdebug.h>

Memento::Memento(bool sd, bool hd, QColor cl, QColor ml, QColor onl, QColor downl)
{
	saveData = sd;
	highDensity = hd;
	cpuLine = cl;
	memoryLine = ml;
	onSpeedLine = onl;
	downSpeedLine = downl;
}

Memento::~Memento()
{
}

State::State()
{
	saveData = true;
	highDensity = false;
	cpuLine = QColor(100, 149, 237);
	memoryLine = QColor(255, 107, 107);
	onSpeedLine = QColor(255, 165, 0);
	downSpeedLine = QColor(0, 250, 154);
}

Memento State::save()
{
	Memento memento(saveData, highDensity, cpuLine, memoryLine, onSpeedLine, downSpeedLine);
	return memento;
}

void State::load(Memento memento)
{
	saveData = memento.saveData;
	highDensity = memento.highDensity;
	cpuLine = memento.cpuLine;
	memoryLine = memento.memoryLine;
	onSpeedLine = memento.onSpeedLine;
	downSpeedLine = memento.downSpeedLine;
}

void State::reset()
{
	saveData = true;
	highDensity = false;
	cpuLine = QColor(100, 149, 237);
	memoryLine = QColor(255, 107, 107);
	onSpeedLine = QColor(255, 165, 0);
	downSpeedLine = QColor(0, 250, 154);
}

State::~State()
{
}

Caretake::Caretake()
{

}

void Caretake::Save(Memento menento)
{
	QString path = "state.txt";
	QFile file(path);
	file.open(QIODevice::WriteOnly | QIODevice::Text);

	if (menento.saveData)
		file.write("1\n");
	else
		file.write("0\n");
	if (menento.highDensity)
		file.write("1\n");
	else
		file.write("0\n");

	QString cpu = QString::number(menento.cpuLine.red()) +
		"\n" + QString::number(menento.cpuLine.green()) +
		"\n" + QString::number(menento.cpuLine.blue()) + "\n";

	QString memory = QString::number(menento.memoryLine.red()) +
		"\n" + QString::number(menento.memoryLine.green()) +
		"\n" + QString::number(menento.memoryLine.blue()) + "\n";

	QString onspeed = QString::number(menento.onSpeedLine.red()) +
		"\n" + QString::number(menento.onSpeedLine.green()) +
		"\n" + QString::number(menento.onSpeedLine.blue()) + "\n";

	QString downspeed = QString::number(menento.downSpeedLine.red()) +
		"\n" + QString::number(menento.downSpeedLine.green()) +
		"\n" + QString::number(menento.downSpeedLine.blue());

	file.write(cpu.toStdString().c_str());
	file.write(memory.toStdString().c_str());
	file.write(onspeed.toStdString().c_str());
	file.write(downspeed.toStdString().c_str());

	file.close();
}

Memento Caretake::Load()
{
	QString path = "state.txt";
	QFile file(path);
	file.open(QIODevice::ReadOnly | QIODevice::Text);

	QString qstring;
	bool saveData;
	bool highDensity;
	int cpu_r, cpu_g, cpu_b;
	int m_r, m_g, m_b;
	int on_r, on_g, on_b;
	int down_r, down_g, down_b;


	qstring = file.readLine();
	if (qstring == "1")
		saveData = true;
	else
		saveData = false;

	qstring = file.readLine();
	if (qstring == "1\n")
		highDensity = true;
	else
		highDensity = false;

	qstring = file.readLine();
	cpu_r = qstring.toInt();

	qstring = file.readLine();
	cpu_g = qstring.toInt();

	qstring = file.readLine();
	cpu_b = qstring.toInt();

	qstring = file.readLine();
	m_r = qstring.toInt();

	qstring = file.readLine();
	m_g = qstring.toInt();

	qstring = file.readLine();
	m_b = qstring.toInt();

	qstring = file.readLine();
	on_r = qstring.toInt();

	qstring = file.readLine();
	on_g = qstring.toInt();

	qstring = file.readLine();
	on_b = qstring.toInt();

	qstring = file.readLine();
	down_r = qstring.toInt();

	qstring = file.readLine();
	down_g = qstring.toInt();

	qstring = file.readLine();
	down_b = qstring.toInt();
	
	file.close();

	return Memento(saveData, highDensity, QColor(cpu_r, cpu_g, cpu_b), QColor(m_r, m_g, m_b), QColor(on_r, on_g, on_b), QColor(down_r, down_g, down_b));
}