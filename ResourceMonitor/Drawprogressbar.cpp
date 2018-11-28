#include "Drawprogressbar.h"
#include "qwidget.h"
#include "qpainter.h"

#include "qdebug.h"

Drawprogressbar::Drawprogressbar(QWidget *parent, int h, int w, int p, std::string t) : QWidget(parent)
{
	mheight = h;
	mwidth = w;
	persent = p;
	type = t;
}

void Drawprogressbar::paintEvent(QPaintEvent *event)
{
	//���û�����С
	setFixedHeight(mheight);
	setFixedWidth(mwidth);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);	//������

	int rotateAngle = 360 * persent / 100;	//���ýǶ�
	int side = qMin(width(), height());		//ȡwidth()��height()�Ľ�Сֵ���Խ�����ͼ����������ʾ�ڿؼ���
	
	QRectF outRect(0, 0, side, side);		//�����
	QRectF inRect(20, 20, side - 40, side - 40);		//�ھ���
	QString valueStr = QString("%1%").arg(QString::number(persent));

	//����Բ
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(QColor(97, 117, 118)));
	painter.drawEllipse(outRect);	//����ε��ڽ�Բ
	if (type == "memory")
		painter.setBrush(QColor(255, 107, 107));
	else
		painter.setBrush(QColor(100, 149, 237));
	painter.drawPie(outRect, (90 - rotateAngle) * 16, rotateAngle * 16);

	//������
	painter.setBrush(palette().window().color());
	painter.drawEllipse(inRect);

	//������
	QFont f = QFont("Microsoft YaHei", 15, QFont::Bold);
	painter.setFont(f);
	painter.setFont(f);
	painter.setPen(QColor("#555555"));
	painter.drawText(inRect, Qt::AlignCenter, valueStr);

}

void Drawprogressbar::resetpersent(int p)
{
	persent = p;
}

Drawprogressbar::~Drawprogressbar()
{
}
