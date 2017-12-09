#ifndef _L_USER_H_
#define _L_USER_H_ 

#include "LBase.h"
#include "LBuff.h"


class LUser
{
public:
	LUser();
	~LUser();

	void	Read(LBuff& buff);
	void	Write(LBuff& buff);

public:
	Lint		m_id;
	Lstring		m_openid;
	Lstring		m_nike;
	Lint		m_sex;
	Lstring		m_provice;
	Lstring		m_city;
	Lstring		m_country;
	Lstring		m_headImageUrl;
	Lstring		m_unioid;
	Lstring		m_playerType;
	Lint		m_numOfCard1s;
	Lint		m_numOfCard2s;
	Lint		m_numOfCard3s;
	Lint		m_regTime;
	Lint		m_regFrom;
	Lint		m_lastLoginTime;
	Lint		m_new;
	Lint		m_gm;
	Lint		m_totalbuynum;
	Lint		m_totalplaynum;
	Lint		m_diamondNum;
	Lint        m_couponNum;
};

#endif