#ifndef DRAWPROGRESSBAR_H
#define DRAWPROGRESSBAR_H

#include "qwidget.h"
#include <string>

class Drawprogressbar : public QWidget
{
private:
	int mheight;
	int mwidth;
	int persent;
	std::string type;
public:
	explicit Drawprogressbar(QWidget *parent = nullptr, int h = 100, int w = 100, int p = 0, std::string t = "");
	void resetpersent(int p);
	void paintEvent(QPaintEvent *event);
	~Drawprogressbar();

};

#endif // !DRAWGROGRESSBAR_H