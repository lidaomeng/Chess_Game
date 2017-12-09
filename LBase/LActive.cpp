#include "LActive.h"


LActive::LActive(void)
{
	m_id = 0;
	m_RewardID = 0;	
	m_date = 0;
}


LActive::~LActive(void)
{
}

void LActive::Read(LBuff& buff)
{
	buff.Read(m_id);
	buff.Read(m_RewardID);
	buff.Read(m_phoneNum);
	buff.Read(m_date);
}

void LActive::Write(LBuff& buff)
{
	buff.Write(m_id);
	buff.Write(m_RewardID);
	buff.Write(m_phoneNum);
	buff.Write(m_date);
}
