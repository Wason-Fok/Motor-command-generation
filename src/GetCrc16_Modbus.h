// ----------------------------------------------
// 用于计算步进电机控制命令 CRC16/MODBUS 校验值
// ----------------------------------------------
#pragma once

#include <QObject>

class GetCrc16_Modbus : public QObject
{
	Q_OBJECT

public:
	GetCrc16_Modbus(QObject *parent);
	~GetCrc16_Modbus();
	unsigned short CheckCRC(unsigned char *pdata, unsigned int len);	// 传入数据并返回 CRC 校验值

private:
	unsigned short m_crcInit;		// CRC 初始值
};
