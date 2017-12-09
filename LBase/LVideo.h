//查牌功能


#ifndef _L_VIDEO_H_
#define _L_VIDEO_H_

#include "LTool.h"
#include "LBuff.h"

struct CardValue
{
	Lint m_color;
	Lint m_number;

	MSGPACK_DEFINE(m_color, m_number); 
	CardValue():m_color(0),m_number(0)
	{
	}

	void clear() {
		m_color=0;
		m_number=0;
	}

	bool valid() {
		if(m_color!=0&&m_number!=0)
		{
			return true;
		}
		else{
			return false;
		}
	}

	bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_color), m_color);
		ReadMapData(obj, NAME_TO_STR(m_number), m_number);
		return true;
	}

	bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteKeyValue(pack, NAME_TO_STR(m_color), m_color);
		WriteKeyValue(pack, NAME_TO_STR(m_number), m_number);
		return true;
	}
};



enum VIDEO_OPER
{
	VIDEO_OPER_GET_CARD = 1,	//摸牌
	VIDEO_OPER_OUT_CARD,		//出牌
	VIDEO_OPER_AN_GANG,			//暗杠
	VIDEO_OPER_MING_GANG,		//我出牌明杠
	VIDEO_OPER_PENG_CARD,		//碰牌
	VIDEO_OPER_GANG,			//别人出牌，我杠
	VIDEO_OPER_SHOUPAO,			//收炮
	VIDEO_OPER_ZIMO,			//自摸
	VIDEO_OPER_HUANGZHUANG,		//流局
	VIDEO_OPER_EAT,				//吃
	VIDEO_OPER_SELF_BU,			//明补自已的
	VIDEO_OPER_OTHER_BU,		//明补他人的
	VIDEO_OPER_AN_BU,			//暗补

	VIDEO_OPER_START_HU_QUEYISE,		//缺一色
	VIDEO_OPER_START_HU_BANBANHU,		//板板胡
	VIDEO_OPER_START_HU_DASIXI,			//大四喜
	VIDEO_OPER_START_HU_LIULIUSHUN,		//六六顺

	VIDEO_OPER_GET_BU_CARDS,			//获取补牌 2张
	
	VIDEO_OPEN_THINK		=21,//玩家思想
	VIDEO_OPEN_DOING		=22,//玩家决定

	VIDEO_OPER_START_HU_SANTONG,		//三同
	VIDEO_OPER_START_HU_JIEMEIDUI,		//节节高
	VIDEO_OPER_START_HU_YIZHIHUA,		//一枝花
	VIDEO_OPER_ZHONGTUSIXI,				//中途四喜

	VIDEO_OPEN_HAIDI_REMIND	=53,	//海底提示;
	VIDEO_OPEN_HAIDI_SELECT	=54,	//海底选择;
	VIDEO_OPEN_HAIDI_PASS	=55,	//海底过;
	VIDEO_OPEN_HAIDI_SHOW	=56,	//海底过;

	VIDEO_OPEN_BIRD_SHOW	=61,	//扎鸟;
	VIDEO_PLAYER_RECONNECT	=62,	//扎鸟;
	VIDEO_OPEN_USER_PIAO	=63,	//飘;

	VIDEO_OPEN_WANGBA = 73,
	VIDEO_OPER_XIABU = 64,        //补虾牌
};

struct VideoOper
{
	Lint		m_pos;
	Lint		m_oper;
	std::vector<CardValue> m_cards;		//第一个为目标牌（吃，碰，等），后面的是已有的牌

	MSGPACK_DEFINE(m_pos,m_oper,m_cards); 
	VideoOper()
	{
		m_pos = 0;
		m_oper = 0;
		m_cards.clear();
	}

	Lstring		ToString()
	{
		std::stringstream ss;
		ss << m_pos << ",";
		ss << m_oper << ",";
		for (int i = 0; i< m_cards.size(); i++)
		{
			ss << m_cards[i].m_color << "|" << m_cards[i].m_number;
			if (i < m_cards.size() - 1)
			{
				ss << ",";
			}
		}
		ss << ";";
		return ss.str();
	}

	void	FromString(Lstring str)
	{
		std::vector<Lstring> des;
		L_ParseString(str, des, ",");
		if (des.size() >= 3)
		{
			m_pos = atoi(des[0].c_str());
			m_oper = atoi(des[1].c_str());
			std::vector<Lstring> splids;
			for (int i = 2; i < des.size(); i ++)
			{
				L_ParseString(des[i], splids, "|");
				if (splids.size() >= 2)
				{
					CardValue card;
					card.m_color = atoi(splids[0].c_str());
					card.m_number = atoi(splids[1].c_str());
					m_cards.push_back(card);
				}
			}
		}
	}
};

class VideoLog
{
public:
	VideoLog();
	virtual~VideoLog();
	void		AddOper(Lint oper,Lint pos, std::vector<CardValue>& cards);

	void		DealCard(Lint* userId, std::vector<CardValue>* vec, Lint time,Lint zhuang,Lint* score,Lint deskId,Lint cur,Lint max,Lint flag, std::vector<Lint>* playType);

	Lstring		ToString();

	void		FromString(Lstring str,Lint user_count=4);

	void		Write(LBuff& buff);

	void		Read(LBuff& buff);

	void		Clear();

	Lstring		GetInsertSql();

	Lstring		PlayTypeToStrint();

	void		PlayTypeFromString(Lstring str);
public:
	Lint							m_time;
	Lstring							m_Id;
	Lint							m_zhuang;
	Lint							m_deskId;
	Lint							m_curCircle;
	Lint							m_maxCircle;
	Lint							m_score[4];
	Lint							m_userId[4];
	Lint							m_flag;//牌局玩法
	std::vector<CardValue>			m_handCard[4];
	std::vector<VideoOper>			m_oper;
	std::vector<Lint>				m_playType;
	Lstring							m_str;
	Lstring							m_str_playtype;
};


#endif