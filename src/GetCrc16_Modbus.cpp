#include "GetCrc16_Modbus.h"

GetCrc16_Modbus::GetCrc16_Modbus(QObject *parent)
	: QObject(parent)
{
}

GetCrc16_Modbus::~GetCrc16_Modbus()
{
}

unsigned short GetCrc16_Modbus::CheckCRC(unsigned char *pdata, unsigned int len) {
	// 检查数据完整性
	if (NULL == pdata || len <= 0) {
		return 0;
	}

	// 初始化 CRC 初始值
	m_crcInit = 0xFFFF;

	for (int i = 0; i < len; i++) {
		m_crcInit ^= (unsigned short)(pdata[i]);
		for (int j = 0; j <= 7; j++)
		{
			if (m_crcInit & 0x0001)
			{
				m_crcInit = (m_crcInit >> 1) ^ 0xA001;
			}
			else
			{
				m_crcInit = m_crcInit >> 1;
			}
		}
	}

	unsigned short siRet = 0;
	siRet = (m_crcInit & 0x00FF) << 8;
	siRet |= m_crcInit >> 8;

	return siRet;
}