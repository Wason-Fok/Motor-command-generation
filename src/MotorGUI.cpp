#include "MotorGUI.h"
#include "GetCrc16_Modbus.h"
//#include <QDebug>

MotorGUI::MotorGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// �������ÿ�������ڶ���
	m_comandList = new ComandList(this);
	m_comandList->setWindowFlag(Qt::Window);
	

	// ��ʼ��δ��У��ֵ��������
	for (int i = 0; i < 11; i++) {
		m_cmd[i] = 0;
	}

	connect(ui.btnCmd, SIGNAL(clicked()), this, SLOT(OnBtnCmd()));								// ���ӳ��ÿ������ť
	connect(ui.genBtn, SIGNAL(clicked()), this, SLOT(OnBtnGen()));								// ���ӵ����������ɰ�ť
	connect(ui.funcComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(OnCmBoxChanged()));	// ���ӿ���������Ͽ�
	connect(ui.kineticBtn, SIGNAL(clicked()), this, SLOT(OnBtnKinetic()));						// ���� Kinetic ���ť
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(OnAboutAction()));					// ���ӹ��������ڰ�ť
}

// ��ʾ���ÿ��������
int MotorGUI::OnBtnCmd() {
	m_comandList->show();
	return 0;
}

// ��������ֵ�������ֵ
void MotorGUI::setCmBoxMin_Max(int minValue, int maxValue) {
	ui.dataSpingBox->setMinimum(minValue);
	ui.dataSpingBox->setMaximum(maxValue);
}

int MotorGUI::OnCmBoxChanged() {
	// 0 : �����ٶ�		1 - 100
	// 1 : ���ٶ�		1 - 30
	// 2 : �����ٶ�		1 - 2000
	// 3 : ��������		0 - 9999
	// 4 : ��������(��) 0 - 9999

	// ��ȡ index ֵ,��������������������Сֵ
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
	// QString data = ui.funcComboBox->currentText();	// ���� ComboBox text
	// qDebug() << index << " " << data;				// ���� ComboBox
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
	// ���嵥���ֽڱ������ֽڸ�λ���ֽڵ�λ�������ַ���
	unsigned char byte, hBit, lBit;
	QString s = "";

	for (int i = 0; i < len; i++)
	{
		if (mode == 1) {
			s.append('$');
		}
		byte = data[i];

		// �����λ�ַ�����ӵ��ַ�����
		hBit = (byte & 0xF0) >> 4;
		if (hBit > 9)
			hBit = 'A' + (hBit - 0x0A);
		else
			hBit += 0x30;
		s.append(hBit);

		// �����λ�ַ�����ӵ��ַ�����
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
	// ����������07 10 00 0A 00 01 02 09 C4 8A 99

	// �������븴�Ƶ�������
	m_cmd[0] = ui.idSpingBox->value();

	// ��������̶���ֵ
	m_cmd[1] = 0x10;
	m_cmd[2] = 0x00;
	m_cmd[6] = 0x02;

	// ��ȡ����������Ͽ� index ֵ������������ֵ
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

	// ��ȡ�� 8 λ����ֵ
	m_cmd[7] = (ui.dataSpingBox->value() & 0xFF00) >> 8;
	// ��ȡ�� 8 λ����ֵ
	m_cmd[8] = ui.dataSpingBox->value() & 0x00FF;

	// ����У��ֵ����ֵ��������
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
