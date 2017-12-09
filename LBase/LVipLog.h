#ifndef _LVIP_LOG_H
#define _LVIP_LOG_H

#include "LTool.h"
#include "LBuff.h"
#include "GameDefine.h"

struct VipDeskLog
{
	Lstring	 m_videoId;//¼��id
	Lint	 m_gold[DESK_USER_COUNT];
	Lint	 m_win[DESK_USER_COUNT];
	Lint	 m_zhuangPos;//��ׯ��λ��
	Lint	 m_time;//����ʱ��
	Lint	 m_angang[DESK_USER_COUNT];//����
	Lint	 m_mgang[DESK_USER_COUNT];//����
	Lint	 m_bomb[DESK_USER_COUNT];	//�����ߵķ�����Ϣ
	VipDeskLog()
	{
		memset(m_gold, 0, sizeof(m_gold));
		memset(m_win, 0, sizeof(m_win));
		memset(m_angang, 0, sizeof(m_angang));
		memset(m_mgang, 0, sizeof(m_mgang));
		memset(m_bomb, 0, sizeof(m_bomb));
		m_zhuangPos = INVAILD_POS;
		m_time = 0;
		m_videoId = "";
	}
};

struct LVipLogItem
{
	Lstring			m_id;		//id
	Lint			m_time;		//ʱ��
	Lint			m_flag;		//�����淨0-������1-���ڣ�2-����
	Lint			m_deskId;	//����id
	Lstring			m_secret;	//����
	Lint			m_maxCircle;//��Ȧ��
	Lint			m_curCircle;//��ǰȦ��
	Lint			m_posUserId[DESK_USER_COUNT];//0-3����λ���ϵ����id
	Lint			m_curZhuangPos;//��ǰׯ��
	Lint			m_score[4];// ����λ������Ļ���
	Lint			m_reset;//�Ƿ����
	std::vector<Lint> m_playtype;		//�淨�б�
	std::vector<Lint> m_playtype_starthu;//���ֺ�����
	std::vector<VipDeskLog*> m_log;//ÿһ�ѵļ�¼
	bool			m_free;
	LVipLogItem();
	virtual  ~LVipLogItem();
	virtual  Lstring		ToString();

	virtual  void			FromString(Lstring str);

	virtual  Lstring		PlayTypeToStrint();

	virtual  void			PlayTypeFromString(Lstring str);

	virtual  Lstring        PlayTypeToString4RLog();
};
#endif