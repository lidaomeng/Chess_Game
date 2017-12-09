#ifndef _L_ACTIVE_H
#define _L_ACTIVE_H
#include "LBase.h"
#include "LBuff.h"
class LActive
{
public:
	LActive();
	~LActive();

	void	Read(LBuff& buff);
	void	Write(LBuff& buff);

public:
	Lint	m_id;				//数据库主键
	Lint	m_RewardID;			//抽中的转数
	Lstring	m_phoneNum;			//电话号
	Lint	m_date;				//中奖时间
	Lint    m_state;            //1等待分享，2等待电话号码，3完成。
};

#endif
