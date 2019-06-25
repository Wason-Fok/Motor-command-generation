#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MotorGUI.h"
#include "ComandList.h"
#include "GetCrc16_Modbus.h"
#include "AboutDialog.h"

class MotorGUI : public QMainWindow
{
	Q_OBJECT

public:
	MotorGUI(QWidget *parent = Q_NULLPTR);

private slots:
	int OnBtnCmd();				// ���ÿ������ť
	int OnBtnGen();				// �����������ɰ�ť
	int OnCmBoxChanged();		// ����������Ͽ�
	int OnBtnKinetic();			// Kinetic 
	int OnAboutAction();		// ���ڰ�ť

private:
	void setCmBoxMin_Max(int minValue, int maxValue);					// ��������ֵ�������ֵ
	QString hexToString(const unsigned char *data, int len, bool mode);	// �� cmd ����ת�����ַ���
	QString cmdGenerate(bool mode);										// �����������ɺ���

private:
	Ui::MotorGUIClass ui;
	ComandList *m_comandList;		// ���ÿ��������
	GetCrc16_Modbus *m_getCrc;		// ���� crc16 У��ֵ

	unsigned char m_cmd[11];		// ������������


};
