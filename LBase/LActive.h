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
	Lint	m_id;				//���ݿ�����
	Lint	m_RewardID;			//���е�ת��
	Lstring	m_phoneNum;			//�绰��
	Lint	m_date;				//�н�ʱ��
	Lint    m_state;            //1�ȴ�����2�ȴ��绰���룬3��ɡ�
};

#endif
