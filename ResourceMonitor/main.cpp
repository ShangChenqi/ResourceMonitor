#include "ResourceMonitor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ResourceMonitor w;
	w.setFixedSize(w.width(), w.height());		//�̶����ڴ�С
	w.setWindowFlags(Qt::WindowCloseButtonHint);	//���ذ�����ť
	w.show();
	return a.exec();
}
