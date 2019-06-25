// ----------------------------------------------
// ���ڼ��㲽������������� CRC16/MODBUS У��ֵ
// ----------------------------------------------
#pragma once

#include <QObject>

class GetCrc16_Modbus : public QObject
{
	Q_OBJECT

public:
	GetCrc16_Modbus(QObject *parent);
	~GetCrc16_Modbus();
	unsigned short CheckCRC(unsigned char *pdata, unsigned int len);	// �������ݲ����� CRC У��ֵ

private:
	unsigned short m_crcInit;		// CRC ��ʼֵ
};
