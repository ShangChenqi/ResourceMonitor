#include "ResourceMonitor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ResourceMonitor w;
	w.setFixedSize(w.width(), w.height());		//固定窗口大小
	w.setWindowFlags(Qt::WindowCloseButtonHint);	//隐藏帮助按钮
	w.show();
	return a.exec();
}
