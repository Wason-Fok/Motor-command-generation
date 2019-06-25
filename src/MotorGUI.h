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
	int OnBtnCmd();				// 常用控制命令按钮
	int OnBtnGen();				// 调试命令生成按钮
	int OnCmBoxChanged();		// 控制命令组合框
	int OnBtnKinetic();			// Kinetic 
	int OnAboutAction();		// 关于按钮

private:
	void setCmBoxMin_Max(int minValue, int maxValue);					// 限制数据值输入最大值
	QString hexToString(const unsigned char *data, int len, bool mode);	// 将 cmd 数组转换成字符串
	QString cmdGenerate(bool mode);										// 控制命令生成函数

private:
	Ui::MotorGUIClass ui;
	ComandList *m_comandList;		// 常用控制命令窗口
	GetCrc16_Modbus *m_getCrc;		// 计算 crc16 校验值

	unsigned char m_cmd[11];		// 控制命令数组


};
