#pragma once
#include <QDialog>
#include<QLineEdit>
#include<QMessageBox>
#include<QInputDialog>
#include <QtWidgets/QMainWindow>
#include <QWidget>
#include <QFile>
#include "ui_intersect_ui.h"
#include "qcustomplot.h"
#include "./include/pch.h"
#pragma comment(lib,"DllWork.lib")

class intersect_ui : public QMainWindow
{
	Q_OBJECT

public:
	intersect_ui(QWidget *parent = Q_NULLPTR);

private:
	Ui::intersect_uiClass ui;

private slots:
	void on_AddLine_clicked();
	void on_DelLine_clicked();
	void on_GenerateGraph_clicked();
	void on_GeneratePoint_clicked();
	void on_AddFile_clicked();
	//void on_Exit_clicked();
	//��Щ�����������ʽ���źŶ��壬����Ҫдconnect��������ʵҲ���������ʦ�������ź����
	//���������������ľͱ���дconnect������ͨ�������ʦ�������ź�����Զ�����connect
};

