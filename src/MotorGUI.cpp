#include "MotorGUI.h"
#include "GetCrc16_Modbus.h"
//#include <QDebug>

MotorGUI::MotorGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// 创建常用控制命令窗口对象
	m_comandList = new ComandList(this);
	m_comandList->setWindowFlag(Qt::Window);
	

	// 初始化未加校验值命令数组
	for (int i = 0; i < 11; i++) {
		m_cmd[i] = 0;
	}

	connect(ui.btnCmd, SIGNAL(clicked()), this, SLOT(OnBtnCmd()));								// 连接常用控制命令按钮
	connect(ui.genBtn, SIGNAL(clicked()), this, SLOT(OnBtnGen()));								// 连接调试命令生成按钮
	connect(ui.funcComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(OnCmBoxChanged()));	// 连接控制命令组合框
	connect(ui.kineticBtn, SIGNAL(clicked()), this, SLOT(OnBtnKinetic()));						// 连接 Kinetic 命令按钮
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(OnAboutAction()));					// 连接工具栏关于按钮
}

// 显示常用控制命令窗口
int MotorGUI::OnBtnCmd() {
	m_comandList->show();
	return 0;
}

// 限制数据值输入最大值
void MotorGUI::setCmBoxMin_Max(int minValue, int maxValue) {
	ui.dataSpingBox->setMinimum(minValue);
	ui.dataSpingBox->setMaximum(maxValue);
}

int MotorGUI::OnCmBoxChanged() {
	// 0 : 启动速度		1 - 100
	// 1 : 加速度		1 - 30
	// 2 : 运行速度		1 - 2000
	// 3 : 脉冲数量		0 - 9999
	// 4 : 脉冲数量(万) 0 - 9999

	// 获取 index 值,并限制输入数据最大和最小值
	switch (ui.funcComboBox->currentIndex()) {
	case 0:
		setCmBoxMin_Max(1, 100);
		break;
	case 1:
		setCmBoxMin_Max(1, 30);
		break;
	case 2:
		setCmBoxMin_Max(1, 2000);
		break;
	case 3:
		setCmBoxMin_Max(0, 9999);
		break;
	case 4:
		setCmBoxMin_Max(0, 9999);
		break;
	default:
		break;
	}
	// QString data = ui.funcComboBox->currentText();	// 测试 ComboBox text
	// qDebug() << index << " " << data;				// 测试 ComboBox
	return 0;
}

int MotorGUI::OnBtnGen() {
	ui.cmdTextEdit->setPlainText(cmdGenerate(0));
	return 0;
}

int MotorGUI::OnBtnKinetic() {
	ui.cmdTextEdit->setPlainText(cmdGenerate(1));
	return 0;
}

int MotorGUI::OnAboutAction() {
	AboutDialog dlg;
	int ret = dlg.exec();
	return 0;
}

QString MotorGUI::hexToString(const unsigned char *data, int len, bool mode) {
	// 定义单个字节变量、字节高位、字节低位、返回字符串
	unsigned char byte, hBit, lBit;
	QString s = "";

	for (int i = 0; i < len; i++)
	{
		if (mode == 1) {
			s.append('$');
		}
		byte = data[i];

		// 计算高位字符并添加到字符串中
		hBit = (byte & 0xF0) >> 4;
		if (hBit > 9)
			hBit = 'A' + (hBit - 0x0A);
		else
			hBit += 0x30;
		s.append(hBit);

		// 计算低位字符并添加到字符串中
		lBit = byte & 0x0F;
		if (lBit > 9)
			lBit = 'A' + (lBit - 0x0A);
		else
			lBit += 0x30;
		s.append(lBit);
		if (mode == 0) {
			if (i != len - 1) {
				s.append(0x20);
			}
		}
	}
	return s;
}

QString MotorGUI::cmdGenerate(bool mode) {
	// 数据样本：07 10 00 0A 00 01 02 09 C4 8A 99

	// 将机器码复制到数组中
	m_cmd[0] = ui.idSpingBox->value();

	// 设置数组固定数值
	m_cmd[1] = 0x10;
	m_cmd[2] = 0x00;
	m_cmd[6] = 0x02;

	// 获取控制命令组合框 index 值，并设置数组值
	switch (ui.funcComboBox->currentIndex())
	{
	case 0:
		m_cmd[3] = 0x06;
		m_cmd[4] = 0x00;
		m_cmd[5] = 0x01;
		break;
	case 1:
		m_cmd[3] = 0x07;
		m_cmd[4] = 0x00;
		m_cmd[5] = 0x01;
		break;
	case 2:
		m_cmd[3] = 0x08;
		m_cmd[4] = 0x00;
		m_cmd[5] = 0x01;
		break;
	case 3:
		m_cmd[3] = 0x0A;
		m_cmd[4] = 0x00;
		m_cmd[5] = 0x01;
		break;
	case 4:
		m_cmd[3] = 0x09;
		m_cmd[4] = 0x01;
		m_cmd[5] = 0x00;
		break;
	default:
		break;
	}

	// 获取高 8 位数据值
	m_cmd[7] = (ui.dataSpingBox->value() & 0xFF00) >> 8;
	// 获取低 8 位数据值
	m_cmd[8] = ui.dataSpingBox->value() & 0x00FF;

	// 计算校验值并赋值到数组中
	m_getCrc = new GetCrc16_Modbus(NULL);
	unsigned short crc_16 = m_getCrc->CheckCRC(m_cmd, 9);
	delete m_getCrc;
	m_getCrc = NULL;

	m_cmd[9] = (crc_16 & 0xFF00) >> 8;
	m_cmd[10] = crc_16 & 0x00FF;
	if (mode == 0) {
		return hexToString(m_cmd, 11, 0);
	}
	else {
		return hexToString(m_cmd, 11, 1);
	}
}
