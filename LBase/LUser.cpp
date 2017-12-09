#include "LUser.h"

LUser::LUser()
{
	m_id = 0;
	m_sex = 1;

	m_playerType = "P";

	m_numOfCard1s = 0;
	m_numOfCard2s = 0;
	m_numOfCard3s = 0;
	m_regTime = 0;
	m_regFrom = 0;
	m_lastLoginTime = 0;
	m_new = 0;
	m_gm = 0;
	m_totalbuynum = 0;
	m_totalplaynum = 0;
	m_diamondNum = 0;
	m_couponNum = 0;
}

LUser::~LUser()
{

}

void LUser::Read(LBuff& buff)
{
	buff.Read(m_id);
	buff.Read(m_openid);
	buff.Read(m_nike);

	buff.Read(m_sex);
	buff.Read(m_provice);
	buff.Read(m_city);

	buff.Read(m_country);
	buff.Read(m_headImageUrl);
	buff.Read(m_unioid);
	buff.Read(m_playerType);

	buff.Read(m_numOfCard1s);
	buff.Read(m_numOfCard2s);
	buff.Read(m_numOfCard3s);

	buff.Read(m_lastLoginTime);
	buff.Read(m_regTime);
	buff.Read(m_regFrom);
	buff.Read(m_new);
	buff.Read(m_gm);
	buff.Read(m_totalbuynum);
	buff.Read(m_totalplaynum);
	buff.Read(m_diamondNum);
	buff.Read(m_couponNum);
	
}

void LUser::Write(LBuff& buff)
{
	buff.Write(m_id);
	buff.Write(m_openid);
	buff.Write(m_nike);

	buff.Write(m_sex);
	buff.Write(m_provice);
	buff.Write(m_city);

	buff.Write(m_country);
	buff.Write(m_headImageUrl);
	buff.Write(m_unioid);
	buff.Write(m_playerType);

	buff.Write(m_numOfCard1s);
	buff.Write(m_numOfCard2s);
	buff.Write(m_numOfCard3s);

	buff.Write(m_lastLoginTime);
	buff.Write(m_regTime);
	buff.Write(m_regFrom);

	buff.Write(m_new);
	buff.Write(m_gm);
	buff.Write(m_totalbuynum);
	buff.Write(m_totalplaynum);
	buff.Write(m_diamondNum);
	buff.Write(m_couponNum);
}