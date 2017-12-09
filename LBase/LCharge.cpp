#include "LCharge.h"


LCharge::LCharge()
{
	m_time = 0;
	m_type = 0;
	m_cardType = 0;
	m_cardNum = 0;
	m_userId = 0;
}

LCharge::~LCharge()
{

}

void LCharge::Write(LBuff& buff)
{
	buff.Write(m_time);
	buff.Write(m_type);
	buff.Write(m_cardType);
	buff.Write(m_cardNum);
	buff.Write(m_userId);
	buff.Write(m_admin);
}

void LCharge::Read(LBuff& buff)
{
	buff.Read(m_time);
	buff.Read(m_type);
	buff.Read(m_cardType);
	buff.Read(m_cardNum);
	buff.Read(m_userId);
	buff.Read(m_admin);
}