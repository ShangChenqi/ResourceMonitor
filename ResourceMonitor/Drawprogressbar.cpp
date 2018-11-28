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
	//设置画布大小
	setFixedHeight(mheight);
	setFixedWidth(mwidth);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);	//反走样

	int rotateAngle = 360 * persent / 100;	//设置角度
	int side = qMin(width(), height());		//取width()和height()的较小值，以将整个图形完整的显示在控件中
	
	QRectF outRect(0, 0, side, side);		//外矩形
	QRectF inRect(20, 20, side - 40, side - 40);		//内矩形
	QString valueStr = QString("%1%").arg(QString::number(persent));

	//画外圆
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(QColor(97, 117, 118)));
	painter.drawEllipse(outRect);	//外矩形的内接圆
	if (type == "memory")
		painter.setBrush(QColor(255, 107, 107));
	else
		painter.setBrush(QColor(100, 149, 237));
	painter.drawPie(outRect, (90 - rotateAngle) * 16, rotateAngle * 16);

	//画遮罩
	painter.setBrush(palette().window().color());
	painter.drawEllipse(inRect);

	//画文字
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
