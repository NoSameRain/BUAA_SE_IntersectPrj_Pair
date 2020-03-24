#include "intersect_ui.h"

intersect_ui::intersect_ui(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
}

void intersect_ui::on_AddLine_clicked()
{
	ui.error_messege->clear();
	QString text = ui.InputStr->text();
	
	if (text.size() == 0)
	{
		ui.error_messege->setText("please input text");
	}
	else
	{
		line l1;
		string str = text.toStdString();
		l1.store_coor(str);
		addLine(l1);//���ֱ��	
		
		string message1 = InfinitePoints();
		QString qmessage1 = QString::fromStdString(message1);
		if (message1 != "NO InfinitePoints!")
		{
			ui.error_messege->setText(qmessage1);
			delLine(l1);//ɾ��ֱ��	
		}
	}
	ui.InputStr->clear();
	
}
void intersect_ui::on_DelLine_clicked()
{
	ui.error_messege->clear();
	QString text = ui.InputStr->text();
	if (text.size() == 0)
	{
		ui.error_messege->setText("please input text");
	}
	else
	{
		line l1;
		string str = text.toStdString();
		l1.store_coor(str);
		delLine(l1);//ɾ��ֱ��		
	}
	ui.InputStr->clear();
}

void intersect_ui::on_GenerateGraph_clicked()
{
	ui.error_messege->clear();
	ui.widget->clearItems(); //���֮ǰ���ɵ�ͼ��
	ui.widget->replot();

	vector<line> lines = getLine();//����ֱ�߼���
	for (int i = 0;i < lines.size();i++)
	{
		if (lines[i].type == "L")
		{
			QCPItemStraightLine* l = new QCPItemStraightLine(ui.widget);//����ֱ��
			ui.widget->addItem(l);//��ӵ�ͼ��
			l->setPen(QPen(Qt::blue)); //���û���
			l->point1->setCoords(lines[i].x1, lines[i].y1);
			l->point2->setCoords(lines[i].x2, lines[i].y2);
			ui.widget->replot();
		}
		else if (lines[i].type == "R")
		{
			QCPItemLine* r = new QCPItemLine(ui.widget);//��������
			ui.widget->addItem(r);//��ӵ�ͼ��
			r->setPen(QPen(Qt::green)); //���û���
			r->start->setCoords(lines[i].x1, lines[i].y1);
			if (lines[i].x1 > lines[i].x2)
			{
				int y = int(lines[i].k * (-99999.0) + (lines[i].y1 - double(lines[i].k*lines[i].x1)));
				r->end->setCoords(-99999, y);
			}
			else if (lines[i].x1 < lines[i].x2)
			{
				int y = int(lines[i].k * (99999.0) + (lines[i].y1 - double(lines[i].k * lines[i].x1)));
				r->end->setCoords(99999, y);
			}
			else if (lines[i].x1 == lines[i].x2)
			{
				if(lines[i].y2 > lines[i].y1) r->end->setCoords(lines[i].x1, 99999);
				else r->end->setCoords(lines[i].x1, -99999);
			}
			
			ui.widget->replot();
		}
		else if (lines[i].type == "S")
		{
			QCPItemLine* s = new QCPItemLine(ui.widget);//�����߶�
			ui.widget->addItem(s);//��ӵ�ͼ��
			s->setPen(QPen(Qt::red)); //���û���
			s->start->setCoords(lines[i].x1, lines[i].y1);
			s->end->setCoords(lines[i].x2, lines[i].y2);
			ui.widget->replot();
		}
	}

	//���ÿ���ק ���ַŴ���С ͼ���ѡ��
	ui.widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	
	 //QCustomPlot::removeItem
}

void intersect_ui::on_GeneratePoint_clicked()
{
	ui.error_messege->clear();
	ui.widget->clearGraphs(); //���֮ǰ���ɵ�ͼ��
	ui.widget->replot();

	solve();//���

	set<Point> pts = getPoints();//���ؽ���
	for (set<Point>::iterator iter = pts.begin();iter != pts.end();iter++)
	{
		ui.widget->addGraph();
		ui.widget->graph(0)->setPen(QPen(Qt::red));
		ui.widget->graph(0)->setLineStyle(QCPGraph::lsNone);
		ui.widget->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
		ui.widget->graph(0)->addData(iter->Xpoint, iter->Ypoint);
		ui.widget->replot();
	}
	//���ÿ���ק ���ַŴ���С ͼ���ѡ��
	ui.widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

	int cnt = getPointNum();//points size��ý������
	string str = to_string(cnt);
	QString qstr = QString::fromStdString(str);
	ui.point_cnt->setText(qstr);
}

void intersect_ui::on_AddFile_clicked()
{
	ui.error_messege->clear();
	QString text = ui.InputFileName->toPlainText();
	string str = text.toStdString();
	string message = inputHandler(str);
	QString qmessage = QString::fromStdString(message);
	if (message == "Everything is ok!")
	{
		string message1 = InfinitePoints();
		QString qmessage1 = QString::fromStdString(message1);
		if (message1 == "NO InfinitePoints!")
		{
			readin(str);//��������
		}
		else
		{
			ui.error_messege->setText(qmessage1);
		}
	}
	else
	{
		ui.error_messege->setText(qmessage);
	}
	
	ui.InputFileName->clear();
}

