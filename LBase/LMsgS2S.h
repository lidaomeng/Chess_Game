#ifndef _LMSG_S2S_H_
#define _LMSG_S2S_H_

#include "defines.h"
#include "LMsg.h"
#include "LUser.h"
#include "LCharge.h"
#include "TCPClient.h"


//////////////////////////////////////////////////////////////////////////
//logic 跟 center 
struct LMsgL2CeSynConfigInfo :public LMsg
{
	LMsgL2CeSynConfigInfo() :LMsg(MSG_L_2_CE_SYN_CONFIG_INFO)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2CeSynConfigInfo();
	}
};

//////////////////////////////////////////////////////////////////////////
struct LMsgCe2LSynConfigInfo :public LMsg
{
	Lstring m_PhoneAuthAddr;//手机号验证的地址

	LMsgCe2LSynConfigInfo() :LMsg(MSG_CE_2_L_SYN_CONFIG_INFO)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_PhoneAuthAddr);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_PhoneAuthAddr);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCe2LSynConfigInfo();
	}
};

//////////////////////////////////////////////////////////////////////////
struct LMsgL2CeLogin:public LMsg
{
	Lint	m_ID;//类型
	Lstring m_key;
	Lstring m_ServerName;
	Lint	m_needUserIdInfo;

	LMsgL2CeLogin() :LMsg(MSG_L_2_CE_LOGIN),m_ID(0), m_needUserIdInfo(1)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_ID);
		buff.Read(m_key);
		buff.Read(m_ServerName);
		buff.Read(m_needUserIdInfo);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_ID);
		buff.Write(m_key);
		buff.Write(m_ServerName);
		buff.Write(m_needUserIdInfo);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2CeLogin();
	}
};


//////////////////////////////////////////////////////////////////////////

struct LogicInfo
{
	Lint			m_id;
	Lint			m_deskCount;
	Lstring			m_ip;
	Lshort			m_port;
	LSocketPtr		m_sp;
	TCPClientPtr	m_client;
	Lint		m_flag;	//0,normal; -1,failover
	LogicInfo():m_id(0),m_deskCount(0),m_port(0){}
};

#define NUM_LOGIC		40

struct LMsgLMG2GateLogicInfo :public LMsg
{
	Lint		m_ID;
	Lint		m_count;
	LogicInfo	m_logic[NUM_LOGIC];

	LMsgLMG2GateLogicInfo() :LMsg(MSG_LMG_2_G_SYNC_LOGIC),m_ID(0),m_count(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_ID);
		buff.Read(m_count);
		for (Lint i = 0; i < m_count && i < NUM_LOGIC; ++i)
		{
			buff.Read(m_logic[i].m_id);
			buff.Read(m_logic[i].m_deskCount);
			buff.Read(m_logic[i].m_ip);
			buff.Read(m_logic[i].m_port);
		}

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_ID);
		buff.Write(m_count);
		for (Lint i = 0; i < m_count && i < NUM_LOGIC; ++i)
		{
			buff.Write(m_logic[i].m_id);
			buff.Write(m_logic[i].m_deskCount);
			buff.Write(m_logic[i].m_ip);
			buff.Write(m_logic[i].m_port);
		} 
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2GateLogicInfo();
	}
};

struct GateInfo
{
	Lint		m_id;
	Lint		m_userCount;
	Lstring		m_ip;
	Lshort		m_port;
	LSocketPtr	m_sp;
	GateInfo():m_id(0),m_userCount(0),m_port(0){}
};

#define NUM_GATE		100
struct LMsgL2CeGateInfo :public LMsg
{
	Lint		m_ID;
	Lint		m_count;
	GateInfo	m_gate[NUM_GATE];

	LMsgL2CeGateInfo() :LMsg(MSG_L_2_CE_GATE_INFO),m_ID(0),m_count(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_ID);
		buff.Read(m_count);
		for (Lint i = 0; i < m_count && i < NUM_GATE; ++i)
		{
			buff.Read(m_gate[i].m_id);
			buff.Read(m_gate[i].m_userCount);
			buff.Read(m_gate[i].m_ip);
			buff.Read(m_gate[i].m_port);
		}
		
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_ID);
		buff.Write(m_count);
		for (Lint i = 0; i < m_count && i < NUM_GATE; ++i)
		{
			buff.Write(m_gate[i].m_id);
			buff.Write(m_gate[i].m_userCount);
			buff.Write(m_gate[i].m_ip);
			buff.Write(m_gate[i].m_port);
		} 
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2CeGateInfo();
	}
};


//////////////////////////////////////////////////////////////////////////
struct LMsgCe2LUserLogin:public LMsg
{
	Lint		m_seed;
	LUser		user;

	LMsgCe2LUserLogin() :LMsg(MSG_CE_2_L_USER_LOGIN),m_seed(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_seed);
		user.Read(buff);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_seed);
		user.Write(buff);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCe2LUserLogin();
	}
};

//////////////////////////////////////////////////////////////////////////
//center发送玩家id信息到

//玩家基本信息
struct UserIdInfo
{
	Lint		m_id;
	Lstring		m_unionId;
	Lstring		m_nike;
	Lstring		m_headImageUrl;
	Lint		m_sex;
};

struct LMsgCe2LUserIdInfo:public LMsg
{
	Lint	m_count;
	std::vector<UserIdInfo> m_info;
	
	LMsgCe2LUserIdInfo() :LMsg(MSG_CE_2_L_USER_ID_INFO),m_count(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_count);
		for(Lint i = 0 ; i < m_count; ++i)
		{
			UserIdInfo info;
			buff.Read(info.m_id);
			buff.Read(info.m_unionId);
			buff.Read(info.m_nike);
			buff.Read(info.m_sex);
			buff.Read(info.m_headImageUrl);
			m_info.push_back(info);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		m_count = m_info.size();
		buff.Write(m_count);
		for(Lint i = 0 ; i < m_count; ++i)
		{
			buff.Write(m_info[i].m_id);
			buff.Write(m_info[i].m_unionId);
			buff.Write(m_info[i].m_nike);
			buff.Write(m_info[i].m_sex);
			buff.Write(m_info[i].m_headImageUrl);
		}
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCe2LUserIdInfo();
	}

	virtual Lint preAllocSendMemorySize() //重新分配64K,由于消息长度是short型
	{
		return 1024 * 64;
	}
};


//////////////////////////////////////////////////////////////////////////
//logic 发送保存 玩家信息
struct LMsgL2CeSaveUser:public LMsg
{
	Lint	m_ID;//类型
	Lint	m_type;
	LUser	m_user;

	LMsgL2CeSaveUser() :LMsg(MSG_L_2_CE_USER_SAVE),m_ID(0),m_type(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_ID);
		buff.Read(m_type);
		m_user.Read(buff);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_ID);
		buff.Write(m_type);
		m_user.Write(buff);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2CeSaveUser();
	}
};


//logic 发送保存 玩家信息
struct LMsgLMG2CeSaveUserPlayCount:public LMsg
{
	Lstring	m_unionid;//类型
	Lint	m_playCount;

	LMsgLMG2CeSaveUserPlayCount() :LMsg(MSG_LMG_2_CE_User_Save_PlayCount)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_unionid);
		buff.Read(m_playCount);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_unionid);
		buff.Write(m_playCount);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2CeSaveUserPlayCount();
	}
};


//////////////////////////////////////////////////////////////////////////
//logic 发送保存 桌子信息
struct LMsgL2CeSaveLogItem:public LMsg
{
	Lint		m_type;//类型,0-插入,1-更新
	Lstring		m_sql;

	LMsgL2CeSaveLogItem() :LMsg(MSG_L_2_CE_ROOM_SAVE),m_type(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_type);
		buff.Read(m_sql);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_type);
		buff.Write(m_sql);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2CeSaveLogItem();
	}
};

//////////////////////////////////////////////////////////////////////////
//logic 发送保存 玩家房卡信息
struct LMsgL2CeSaveCardInfo:public LMsg
{
	LCharge	m_charge;

	LMsgL2CeSaveCardInfo() :LMsg(MSG_L_2_CE_CARD_SAVE)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		m_charge.Read(buff);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		m_charge.Write(buff);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2CeSaveCardInfo();
	}
};

struct LMsgLMG2CeCouponChanged : public LMsg
{
	Lstring		m_unionId;
	Lint		m_count;
	Lint		m_changedReason;

	LMsgLMG2CeCouponChanged() : LMsg(MSG_LMG_2_CE_COUPON_CHANGED) {}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_unionId);
		buff.Read(m_count);
		buff.Read(m_changedReason);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_unionId);
		buff.Write(m_count);
		buff.Write(m_changedReason);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2CeCouponChanged;
	}
};

struct LMsgLMG2CeOfflineUserCardChanged : public LMsg
{
	Lstring		m_unionId;
	Lint		m_count;
	Lint		m_cardType;
	Lint		m_operType;
	Lstring		m_admin;

	LMsgLMG2CeOfflineUserCardChanged() : LMsg(MSG_LMG_2_CE_OFFLINE_USER_CARD_CHANGED) {}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_unionId);
		buff.Read(m_count);
		buff.Read(m_cardType);
		buff.Read(m_operType);
		buff.Read(m_admin);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_unionId);
		buff.Write(m_count);
		buff.Write(m_cardType);
		buff.Write(m_operType);
		buff.Write(m_admin);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2CeOfflineUserCardChanged;
	}
};

//////////////////////////////////////////////////////////////////////////
//logic 通知玩家登陆服务器
struct LMsgL2CeUserServerLogin :public LMsg
{
	Lint		m_serverID;//类型,0-插入,1-更新
	Lstring		m_openID;

	LMsgL2CeUserServerLogin() :LMsg(MSG_L_2_CE_USER_LOGIN),m_serverID(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_serverID);
		buff.Read(m_openID);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_serverID);
		buff.Write(m_openID);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2CeUserServerLogin();
	}
};

//////////////////////////////////////////////////////////////////////////
//logic 通知玩家登出服务器
struct LMsgL2CeUserServerLogout:public LMsg
{
	Lint		m_serverID;//类型,0-插入,1-更新
	Lstring		m_openID;

	LMsgL2CeUserServerLogout() :LMsg(MSG_L_2_CE_USER_LOGOUT),m_serverID(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_serverID);
		buff.Read(m_openID);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_serverID);
		buff.Write(m_openID);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2CeUserServerLogout();
	}
};

//////////////////////////////////////////////////////////////////////////
//center 发送玩家充值
struct LMsgCe2LGMCharge:public LMsg
{
	Lint		m_userid;
	Lint		m_cardType;
	Lint		m_cardCount;
	Lint		m_oper; //赠送 //购买
	Lstring		m_admin;

	LMsgCe2LGMCharge() :LMsg(MSG_CE_2_L_GM_CHARGE)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userid);
		buff.Read(m_cardType);
		buff.Read(m_cardCount);
		buff.Read(m_oper);
		buff.Read(m_admin);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userid);
		buff.Write(m_cardType);
		buff.Write(m_cardCount);
		buff.Write(m_oper);
		buff.Write(m_admin);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCe2LGMCharge();
	}
};


//////////////////////////////////////////////////////////////////////////
//center 发送gm设置跑马灯
struct LMsgCe2LGMHorse :public LMsg
{
	Lstring		m_str;
	
	LMsgCe2LGMHorse() :LMsg(MSG_CE_2_L_GM_HORSE)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_str);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_str);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCe2LGMHorse();
	}
};

//////////////////////////////////////////////////////////////////////////
//center 发送gm够买提示
struct LMsgCe2LGMBuyInfo:public LMsg
{
	Lstring		m_str;

	LMsgCe2LGMBuyInfo() :LMsg(MSG_CE_2_L_GM_BUYINFO)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_str);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_str);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCe2LGMBuyInfo();
	}
};

//////////////////////////////////////////////////////////////////////////
//center 发送gm够买提示
struct LMsgCe2LGMHide:public LMsg
{
	Lint		m_hide;

	LMsgCe2LGMHide() :LMsg(MSG_CE_2_L_GM_HIDE),m_hide(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_hide);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_hide);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCe2LGMHide();
	}
};

struct LMsgCe2LGMModifyPlayerType : public LMsg
{
	Lint	m_userId;
	Lstring m_playerType;

	LMsgCe2LGMModifyPlayerType() :LMsg(MSG_CE_2_LMG_GM_MODIFY_PLAYERTYPE)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_playerType);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_playerType);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCe2LGMModifyPlayerType();
	}
};

struct LMsgCe2LGMChargeDiamond : public LMsg
{
	Lint		m_userId;
	Lint		m_error;			// 0-succeed, 1-failed
	Lint		m_diamondCharged;

	LMsgCe2LGMChargeDiamond() : LMsg(MSG_CE_2_LMG_GM_CHARGE_DIAMOND)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_error);
		buff.Read(m_diamondCharged);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_error);
		buff.Write(m_diamondCharged);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCe2LGMChargeDiamond();
	}
};

struct LMsgCe2LGMPurchase : public LMsg
{
	Lint		m_userId;
	Lint		m_error;			// 0-succeed, 1-failed
	Lint		m_itemId;
	Lint		m_diamondPaid;
	Lint		m_cardAdded;
	Lint		m_cardType;
	Lint		m_operType;

	LMsgCe2LGMPurchase() : LMsg(MSG_CE_2_LMG_GM_PURCHASE)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_error);
		buff.Read(m_itemId);
		buff.Read(m_diamondPaid);
		buff.Read(m_cardAdded);
		buff.Read(m_cardType);
		buff.Read(m_operType);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_error);
		buff.Write(m_itemId);
		buff.Write(m_diamondPaid);
		buff.Write(m_cardAdded);
		buff.Write(m_cardType);
		buff.Write(m_operType);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCe2LGMPurchase();
	}
};

struct LMsgCe2LGMTimeLimitFree : public LMsg
{
	Lint m_count;
	std::vector<GameTypeInfo> m_gameTypeInfos;

	LMsgCe2LGMTimeLimitFree() :LMsg(MSG_CE_2_L_GM_TIMELIMITFREE),m_count(0) {}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_count);
		for (Lint i = 0; i < m_count; i++)
		{
			GameTypeInfo gametype;
			buff.Read(gametype.m_id);
			buff.Read(gametype.m_timeLimitFree);
			buff.Read(gametype.m_timeLimitStart);
			buff.Read(gametype.m_timeLimitEnd);
			m_gameTypeInfos.push_back(gametype);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		m_count = m_gameTypeInfos.size();
		buff.Write(m_count);
		for (Lint i = 0; i < m_count; i++)
		{
			GameTypeInfo& gametype = m_gameTypeInfos[i];
			buff.Write(gametype.m_id);
			buff.Write(gametype.m_timeLimitFree);
			buff.Write(gametype.m_timeLimitStart);
			buff.Write(gametype.m_timeLimitEnd);
		}
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCe2LGMTimeLimitFree();
	}
};

struct LMsgLMG2CeCardExchange : public LMsg
{
	Lstring		m_unionId;
	Lint		m_oper;
	Lint		m_exchangeType; //0减 1加
	Lint		m_cardType;
	Lint		m_cardNum;

	LMsgLMG2CeCardExchange() : LMsg(MSG_LMG_2_CE_CardExchange),m_oper(0),m_exchangeType(0),m_cardType(2),m_cardNum(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_unionId);
		buff.Read(m_oper);
		buff.Read(m_exchangeType);
		buff.Read(m_cardType);
		buff.Read(m_cardNum);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_unionId);
		buff.Write(m_oper);
		buff.Write(m_exchangeType);
		buff.Write(m_cardType);
		buff.Write(m_cardNum);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2CeCardExchange();
	}
};


//////////////////////////////////////////////////////////////////////////
//logic 跟 gate 之间的消息交互
//////////////////////////////////////////////////////////////////////////

struct LMsgG2LLogin :public LMsg
{
	Lint		m_id;
	Lstring		m_key;
	Lstring		m_ip;
	Lshort		m_port;

	LMsgG2LLogin() :LMsg(MSG_G_2_L_LOGIN),m_id(0),m_port(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_id);
		buff.Read(m_key);
		buff.Read(m_ip);
		buff.Read(m_port);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_id);
		buff.Write(m_key);
		buff.Write(m_ip);
		buff.Write(m_port);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgG2LLogin();
	}
};

struct LMsgG2LMGLogin :public LMsg
{
	Lint		m_id;
	Lstring		m_key;
	Lstring		m_ip;
	Lshort		m_port;

	LMsgG2LMGLogin() :LMsg(MSG_G_2_LMG_LOGIN),m_id(0),m_port(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_id);
		buff.Read(m_key);
		buff.Read(m_ip);
		buff.Read(m_port);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_id);
		buff.Write(m_key);
		buff.Write(m_ip);
		buff.Write(m_port);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgG2LMGLogin();
	}
};

struct LMsgL2LMGLogin :public LMsg
{
	Lint		m_id;
	Lstring		m_key;
	Lstring		m_ip;
	Lshort		m_port;
	Lint		m_firstLogin;

	LMsgL2LMGLogin() :LMsg(MSG_L_2_LMG_LOGIN),m_id(0),m_port(0), m_firstLogin(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_id);
		buff.Read(m_key);
		buff.Read(m_ip);
		buff.Read(m_port);
		buff.Read(m_firstLogin);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_id);
		buff.Write(m_key);
		buff.Write(m_ip);
		buff.Write(m_port);
		buff.Write(m_firstLogin);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LMGLogin();
	}
};


//////////////////////////////////////////////////////////////////////////
//gate 发送玩家消息 到 logic
struct LMsgG2LUserMsg :public LMsg
{
	Luuid					m_userGateId;
	Lint					m_userMsgId;
	Lstring					m_ip;
	LBuffPtr				m_dataBuff;
	LMsg*					m_userMsg;

	LMsgG2LUserMsg() :LMsg(MSG_G_2_L_USER_MSG), m_userGateId(Luuid_NULL), m_userMsg(NULL),m_userMsgId(0)
	{
	}

	virtual~LMsgG2LUserMsg()
	{
		if (m_userMsg)
			delete m_userMsg;
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userGateId);
		buff.Read(m_userMsgId);
		buff.Read(m_ip);

		int msgid = MSG_ERROR_MSG;

		try{
			msgpack::unpacked  unpack;
			msgpack::unpack(&unpack, buff.Data() + buff.GetOffset(), buff.Size() - buff.GetOffset());
			msgpack::object obj = unpack.get();

			ReadMapData(obj, "m_msgId", msgid);
			m_userMsg = LMsgFactory::Instance().CreateMsg(m_userMsgId);
			if (m_userMsg)
			{
				m_userMsg->Read(obj);
			}
			else
			{
				LLOG_ERROR("LMsgG2LUserMsg read msgId not exiest %d", m_userMsgId);
			}
		}
		catch (...)
		{
			LLOG_ERROR("MSG_G_2_L_USER_MSG::RecvMsgPack error");
		}
		
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userGateId);
		buff.Write(m_userMsgId);
		buff.Write(m_ip);
		buff.Write(m_dataBuff->Data() + m_dataBuff->GetOffset(), m_dataBuff->Size() - m_dataBuff->GetOffset());
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgG2LUserMsg();
	}
};


//////////////////////////////////////////////////////////////////////////
//logic 发现玩家消息到 gate
struct LMsgL2GUserMsg : public LMsg
{
	Luuid						m_id;
	LBuffPtr					m_dataBuff;
	
	LMsgL2GUserMsg() :LMsg(MSG_L_2_G_USER_MSG), m_id(Luuid_NULL)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_id);
		m_dataBuff = LBuffPtr(new LBuff);
		m_dataBuff->Write(buff.Data() + buff.GetOffset(), buff.Size() - buff.GetOffset());
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_id);
		buff.Write(m_dataBuff->Data() + m_dataBuff->GetOffset(), m_dataBuff->Size() - m_dataBuff->GetOffset());
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2GUserMsg();
	}
};


//////////////////////////////////////////////////////////////////////////
//gate 发送玩家掉线消息 到 logic
struct LMsgG2LUserOutMsg :public LMsg
{
	Luuid				m_userGateId;
	
	LMsgG2LUserOutMsg():LMsg(MSG_G_2_L_USER_OUT_MSG), m_userGateId(Luuid_NULL)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userGateId);

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userGateId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgG2LUserOutMsg();
	}
};


//////////////////////////////////////////////////////////////////////////
//logic 发送玩家消息到 gate
struct LMsgL2GUserOutMsg : public LMsg
{
	Luuid				m_id;

	LMsgL2GUserOutMsg():LMsg(MSG_L_2_G_USER_OUT_MSG), m_id(Luuid_NULL)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_id);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_id);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2GUserOutMsg();
	}
};


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//logicmanager 跟 logicdb 之间的消息交互
//logic 登录 logicdb
struct LMsgLMG2LdbLogin : public LMsg
{
	Lstring			m_key;
	Lint			m_serverID;
	LMsgLMG2LdbLogin():LMsg(MSG_LMG_2_LDB_LOGIN),m_serverID(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_key);
		buff.Read(m_serverID);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_key);
		buff.Write(m_serverID);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LdbLogin();
	}
};

struct LMsgLMG2LdbSaveGameTypeFree : public LMsg
{
	Lint m_count;
	std::vector<GameTypeInfo> m_gameFreeInfos;

	LMsgLMG2LdbSaveGameTypeFree() :LMsg(MSG_LMG_2_LDB_SAVE_GAMEFREE), m_count(0) {}
	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_count);
		for (Lint i = 0; i < m_count; i++)
		{
			GameTypeInfo gameFreeInfo;
			buff.Read(gameFreeInfo.m_id);
			buff.Read(gameFreeInfo.m_timeLimitFree);
			buff.Read(gameFreeInfo.m_timeLimitStart);
			buff.Read(gameFreeInfo.m_timeLimitEnd);
			m_gameFreeInfos.push_back(gameFreeInfo);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		m_count = m_gameFreeInfos.size();
		buff.Write(m_count);
		for (Lint i = 0; i < m_count; i++)
		{
			GameTypeInfo& gameFreeInfo = m_gameFreeInfos[i];
			buff.Write(gameFreeInfo.m_id);
			buff.Write(gameFreeInfo.m_timeLimitFree);
			buff.Write(gameFreeInfo.m_timeLimitStart);
			buff.Write(gameFreeInfo.m_timeLimitEnd);
		}
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LdbSaveGameTypeFree();
	}
};

struct LMsgLMG2LdbGetGameTypeFree : public LMsg
{
	LMsgLMG2LdbGetGameTypeFree() :LMsg(MSG_LMG_2_LDB_GET_GAMEFREE) {}
	virtual bool Read(LBuff& buff)
	{
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LdbGetGameTypeFree();
	}
};

struct LMsgLdb2LMGGetGameTypeFree : public LMsg
{
	Lint m_count;
	std::vector<GameTypeInfo> m_gameFreeInfos;

	LMsgLdb2LMGGetGameTypeFree() :LMsg(MSG_LDB_2_LMG_GET_GAMEFREE), m_count(0) {}
	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_count);
		for (Lint i = 0; i < m_count; i++)
		{
			GameTypeInfo gameFreeInfo;
			buff.Read(gameFreeInfo.m_id);
			buff.Read(gameFreeInfo.m_timeLimitFree);
			buff.Read(gameFreeInfo.m_timeLimitStart);
			buff.Read(gameFreeInfo.m_timeLimitEnd);
			m_gameFreeInfos.push_back(gameFreeInfo);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		m_count = m_gameFreeInfos.size();
		buff.Write(m_count);
		for (Lint i = 0; i < m_count; i++)
		{
			GameTypeInfo& gameFreeInfo = m_gameFreeInfos[i];
			buff.Write(gameFreeInfo.m_id);
			buff.Write(gameFreeInfo.m_timeLimitFree);
			buff.Write(gameFreeInfo.m_timeLimitStart);
			buff.Write(gameFreeInfo.m_timeLimitEnd);
		}
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLdb2LMGGetGameTypeFree();
	}
};

//////////////////////////////////////////////////////////////////////////
//logic 登录 logicdb
struct LMsgL2LdbLogin : public LMsg
{
	Lstring			m_key;
	Lint			m_serverID;
	LMsgL2LdbLogin():LMsg(MSG_L_2_LDB_LOGIN),m_serverID(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_key);
		buff.Read(m_serverID);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_key);
		buff.Write(m_serverID);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LdbLogin();
	}
};

//////////////////////////////////////////////////////////////////////////
//logic 发送保存 桌子信息
struct LMsgL2LDBSaveLogItem:public LMsg
{
	Lint		m_type;//类型,0-插入,1-更新
	Lstring		m_sql;
	Lint		m_serverID;

	LMsgL2LDBSaveLogItem() :LMsg(MSG_L_2_LDB_ROOM_SAVE),m_type(0),m_serverID(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_type);
		buff.Read(m_sql);
		buff.Read(m_serverID);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_type);
		buff.Write(m_sql);
		buff.Write(m_serverID);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LDBSaveLogItem();
	}
};


//////////////////////////////////////////////////////////////////////////
//logic 发送保存录像
struct LMsgL2LDBSaveVideo :public LMsg
{
	Lint		m_type;//类型,0-插入,1-更新
	Lstring		m_sql;
	Lint		m_serverID;

	LMsgL2LDBSaveVideo() :LMsg(MSG_L_2_LDB_VIDEO_SAVE),m_type(0),m_serverID(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_type);
		buff.Read(m_sql);
		buff.Read(m_serverID);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_type);
		buff.Write(m_sql);
		buff.Write(m_serverID);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LDBSaveVideo();
	}
};

//////////////////////////////////////////////////////////////////////////
//logic 发送玩家请求战绩
struct LMsgL2LBDReqVipLog:public LMsg
{
	Lint	m_userId;
	Lint	m_reqUserId;

	LMsgL2LBDReqVipLog() :LMsg(MSG_L_2_LDB_VIP_LOG),m_userId(0),m_reqUserId(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_reqUserId);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_reqUserId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LBDReqVipLog();
	}
};

//玩家请求查看某轮录像
struct LMsgL2LBDReqOneVipLog:public LMsg
{
	Lstring	m_log_Id;
	Lint	m_reqUserId;
	
	LMsgL2LBDReqOneVipLog() :LMsg(MSG_L_2_LDB_ONE_VIP_LOG),m_reqUserId(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_log_Id);
		buff.Read(m_reqUserId);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_log_Id);
		buff.Write(m_reqUserId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LBDReqOneVipLog();
	}
};


//////////////////////////////////////////////////////////////////////////
//logicdb 返回 玩家战绩
struct LogInfo
{
	Lstring			m_id;		//id
	Lint			m_time;		//时间
	Lint			m_flag;		//房间规则
	Lint			m_deskId;	//桌子id
	Lstring			m_secret;	//密码
	Lint			m_maxCircle;//总圈数
	Lint			m_curCircle;//当前圈数
	Lint			m_posUserId[4];//0-3各个位置上的玩家id
	Lint			m_curZhuangPos;//当前庄家
	Lint			m_score[4];// 各个位置上面的积分
	Lint			m_reset;//是否解算
	Lstring			m_data;
	Lstring			m_playtype;	//玩法
	Lint			m_userCount;
	LogInfo():m_time(0),m_flag(0),m_deskId(0),m_maxCircle(0),m_curCircle(0),m_curZhuangPos(0),m_reset(0),m_userCount(4){
		memset(m_posUserId,0,sizeof(m_posUserId));
		memset(m_score,0,sizeof(m_score));
	}
};

struct LMsgLBD2LReqOneVipLog:public LMsg
{
	Lint		m_userid;
	Lint		m_size;
	Lstring		m_data;
	Lint        m_usercount;
	LMsgLBD2LReqOneVipLog() :LMsg(MSG_LDB_2_L_ONE_VIP_LOG),m_size(0),m_userid(0), m_usercount(4)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userid);
		buff.Read(m_size);
		buff.Read(m_data);
		buff.Read(m_usercount);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userid);
		buff.Write(m_size);
		buff.Write(m_data);
		buff.Write(m_usercount);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLBD2LReqOneVipLog();
	}
};

struct LMsgLBD2LReqVipLog:public LMsg
{
	Lint		m_userid;
	Lint		m_count;
	LogInfo		m_info[10];

	LMsgLBD2LReqVipLog() :LMsg(MSG_LDB_2_L_VIP_LOG),m_userid(0),m_count(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userid);
		buff.Read(m_count);
		for(Lint i = 0 ; i < m_count; ++i)
		{
			LogInfo& info = m_info[i];
			buff.Read(info.m_id);
			buff.Read(info.m_time);
			buff.Read(info.m_deskId);
			buff.Read(info.m_posUserId[0]);
			buff.Read(info.m_posUserId[1]);
			buff.Read(info.m_posUserId[2]);
			buff.Read(info.m_posUserId[3]);
			buff.Read(info.m_score[0]);
			buff.Read(info.m_score[1]);
			buff.Read(info.m_score[2]);
			buff.Read(info.m_score[3]);
			buff.Read(info.m_reset);
			buff.Read(info.m_flag);
			buff.Read(info.m_playtype);
			buff.Read(info.m_userCount);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userid);
		buff.Write(m_count);
		for(Lint i = 0 ; i < m_count; ++i)
		{
			LogInfo& info = m_info[i];
			buff.Write(info.m_id);
			buff.Write(info.m_time);
			buff.Write(info.m_deskId);
			buff.Write(info.m_posUserId[0]);
			buff.Write(info.m_posUserId[1]);
			buff.Write(info.m_posUserId[2]);
			buff.Write(info.m_posUserId[3]);
			buff.Write(info.m_score[0]);
			buff.Write(info.m_score[1]);
			buff.Write(info.m_score[2]);
			buff.Write(info.m_score[3]);
			buff.Write(info.m_reset);
			buff.Write(info.m_flag);
			buff.Write(info.m_playtype);
			buff.Write(info.m_userCount);
		}
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLBD2LReqVipLog();
	}
};

//////////////////////////////////////////////////////////////////////////
//logic 发送玩家请求录像
struct LMsgL2LDBReqVideo:public LMsg
{
	Lint	m_userId;
	Lstring	m_videoId;

	LMsgL2LDBReqVideo() :LMsg(MSG_L_2_LDB_VIDEO),m_userId(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_videoId);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_videoId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LDBReqVideo();
	}
};

//////////////////////////////////////////////////////////////////////////
//center 返回 玩家战绩
struct LMsgLDB2LReqVideo:public LMsg
{
	Lint		m_userid;
	Lint		m_count;
	VideoLog	m_video;
	Lint		m_userCount;

	LMsgLDB2LReqVideo() :LMsg(MSG_LDB_2_L_VIDEO),m_userid(0),m_count(0), m_userCount(4)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userid);
		buff.Read(m_count);
		buff.Read(m_userCount);
		m_video.Read(buff);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userid);
		buff.Write(m_count);
		buff.Write(m_userCount);
		m_video.Write(buff);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLDB2LReqVideo();
	}
};

struct LMsgLDB2LLogInfo:public LMsg
{
	Lint	m_lastId;
	Lint	m_videoId;
	Lint	m_count;
	std::vector<LogInfo> m_info;

	LMsgLDB2LLogInfo() :LMsg(MSG_LDB_2_L_LOG_INFO),m_lastId(0),m_videoId(0),m_count(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_lastId);
		buff.Read(m_videoId);
		buff.Read(m_count);
		for(Lint i = 0 ; i < m_count; ++i)
		{
			LogInfo info;
			buff.Read(info.m_id);
			buff.Read(info.m_time);
			buff.Read(info.m_flag);
			buff.Read(info.m_deskId);
			buff.Read(info.m_secret);
			buff.Read(info.m_maxCircle);
			buff.Read(info.m_curCircle);
			buff.Read(info.m_posUserId[0]);
			buff.Read(info.m_posUserId[1]);
			buff.Read(info.m_posUserId[2]);
			buff.Read(info.m_posUserId[3]);

			buff.Read(info.m_curZhuangPos);
			buff.Read(info.m_score[0]);
			buff.Read(info.m_score[1]);
			buff.Read(info.m_score[2]);
			buff.Read(info.m_score[3]);
			buff.Read(info.m_reset);
			buff.Read(info.m_data);
			buff.Read(info.m_playtype);

			m_info.push_back(info);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_lastId);
		buff.Write(m_videoId);
		m_count = m_info.size();
		buff.Write(m_count);
		for(Lint i = 0 ; i < m_count; ++i)
		{
			LogInfo& info = m_info[i];
			buff.Write(info.m_id);
			buff.Write(info.m_time);
			buff.Write(info.m_flag);
			buff.Write(info.m_deskId);
			buff.Write(info.m_secret);
			buff.Write(info.m_maxCircle);
			buff.Write(info.m_curCircle);
			buff.Write(info.m_posUserId[0]);
			buff.Write(info.m_posUserId[1]);
			buff.Write(info.m_posUserId[2]);
			buff.Write(info.m_posUserId[3]);

			buff.Write(info.m_curZhuangPos);
			buff.Write(info.m_score[0]);
			buff.Write(info.m_score[1]);
			buff.Write(info.m_score[2]);
			buff.Write(info.m_score[3]);
			buff.Write(info.m_reset);
			buff.Write(info.m_data);
			buff.Write(info.m_playtype);
		}


		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLDB2LLogInfo();
	}
};

//////////////////////////////////////////////////////////////////////////
//logic 发送玩家请求活动
struct LMsgL2LDBReqActive:public LMsg
{
	Lint	m_userId;
	Lint	m_activeId;

	LMsgL2LDBReqActive() :LMsg(MSG_L_2_LDB_REQ_ACTIVE),m_userId(0),m_activeId(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_activeId);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_activeId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LDBReqActive();
	}
};

struct LMsgLDB2LActiveInfo:public LMsg
{
	Lint		m_userid;
	Lint		m_count;
	LActiveInfo	m_DrawInfo[10];
	LMsgLDB2LActiveInfo() :LMsg(MSG_LDB_2_L_REQ_ACTIVE),m_userid(0),m_count(0){ }

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userid);
		buff.Read(m_count);
		for (Lint i = 0; i < 10 && i < m_count; ++i)
		{
			buff.Read(m_DrawInfo[i].m_id);
			buff.Read(m_DrawInfo[i].m_rewardID);
			buff.Read(m_DrawInfo[i].m_phoneNum);
			buff.Read(m_DrawInfo[i].m_date);
			buff.Read(m_DrawInfo[i].m_state);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userid);
		buff.Write(m_count);
		for (Lint i = 0; i < m_count && i < 10; ++i)
		{
			buff.Write(m_DrawInfo[i].m_id);
			buff.Write(m_DrawInfo[i].m_rewardID);
			buff.Write(m_DrawInfo[i].m_phoneNum);
			buff.Write(m_DrawInfo[i].m_date);
			buff.Write(m_DrawInfo[i].m_state);
		} 
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgLDB2LActiveInfo(); }
};
//logic 发送玩家抽奖结果
struct LMsgL2LDBSyncDraw:public LMsg
{
	Lint	m_userId;
	Lint	m_activeID;
	Lint	m_giftID;
	Lint	m_date;
	Lint    m_state;
	Lint	m_indexInMem;

	LMsgL2LDBSyncDraw() :LMsg(MSG_L_2_LDB_SYC_DRAW),m_userId(0),m_activeID(0),m_giftID(0),m_date(0), m_state(0), m_indexInMem(-1)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_activeID);
		buff.Read(m_giftID);
		buff.Read(m_date);
		buff.Read(m_state);
		buff.Read(m_indexInMem);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_activeID);
		buff.Write(m_giftID);
		buff.Write(m_date);
		buff.Write(m_state);
		buff.Write(m_indexInMem);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LDBSyncDraw();
	}
};

struct LMsgLDB2LSyncDraw : public LMsg
{
	Lint		m_userId;
	Lint		m_indexInMem;
	Lint		m_activeLogId;

	LMsgLDB2LSyncDraw() : LMsg(MSG_LDB_2_L_SYC_DRAW), m_userId(0), m_indexInMem(-1), m_activeLogId(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_indexInMem);
		buff.Read(m_activeLogId);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_indexInMem);
		buff.Write(m_activeLogId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLDB2LSyncDraw();
	}
};

//logic 发送玩家更新电话号码
struct LMsgL2LDBSyncPhone:public LMsg
{
	Lint	m_activeLogId;
	Lstring	m_phone;
	Lint    m_state;

	LMsgL2LDBSyncPhone() :LMsg(MSG_L_2_LDB_SYC_PHONE),m_activeLogId(0), m_state(3)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_activeLogId);
		buff.Read(m_phone);
		buff.Read(m_state);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_activeLogId);
		buff.Write(m_phone);
		buff.Write(m_state);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LDBSyncPhone();
	}
};


struct LMsgL2CeUerReLogin:public LMsg
{
	Lint	m_ID;//类型
	Lint	m_seed;
	Lint	m_userid;
	Lint	m_gateId;
	Luuid	m_geteUserId;
	Lstring	m_ip;
	Lstring	m_uuid;
	Lstring	m_md5;

	LMsgL2CeUerReLogin() :LMsg(MSG_L_2_CE_USER_RELOGIN),m_ID(0),m_seed(0),m_userid(0),m_gateId(0),m_geteUserId(Luuid_NULL)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_ID);
		buff.Read(m_seed);
		buff.Read(m_userid);
		buff.Read(m_gateId);
		buff.Read(m_geteUserId);
		buff.Read(m_ip);
		buff.Read(m_uuid);
		buff.Read(m_md5);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_ID);
		buff.Write(m_seed);
		buff.Write(m_userid);
		buff.Write(m_gateId);
		buff.Write(m_geteUserId);
		buff.Write(m_ip);
		buff.Write(m_uuid);
		buff.Write(m_md5);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2CeUerReLogin();
	}
};
struct LMsgCe2LUserReLogin:public LMsg
{
	Lint	m_seed;
	Lint	m_userid;
	Lint	m_gateId;
	Luuid	m_geteUserId;
	Lstring	m_ip;
	Lstring	m_md5;

	LMsgCe2LUserReLogin() :LMsg(MSG_CE_2_L_USER_RELOGIN),m_seed(0),m_userid(0),m_gateId(0),m_geteUserId(Luuid_NULL)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_seed);
		buff.Read(m_userid);
		buff.Read(m_gateId);
		buff.Read(m_geteUserId);
		buff.Read(m_ip);
		buff.Read(m_md5);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_seed);
		buff.Write(m_userid);
		buff.Write(m_gateId);
		buff.Write(m_geteUserId);
		buff.Write(m_ip);
		buff.Write(m_md5);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCe2LUserReLogin();
	}
};


//////////////////////////////////////////////////////////////////////////
//loigc 通过精确的videoid来查找sharevideo中的对应录像
struct LMsgL2LDBGetSsharedVideo:public LMsg
{
	Lint	m_userId;
	Lstring	m_videoId;

	LMsgL2LDBGetSsharedVideo() :LMsg(MSG_L_2_LDB_GETSHAREVIDEOBYVIDEOID),m_userId(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_videoId);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_videoId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LDBGetSsharedVideo();
	}
};

//logic 玩家请求分享某录像，先去sharevideo中查看是否已被分享
struct LMsgL2LDBGGetShareVideoId:public LMsg
{
	Lint	m_userId;
	Lstring	m_videoId;

	LMsgL2LDBGGetShareVideoId() :LMsg(MSG_L_2_LDB_GETSHAREVIDEOID),m_userId(0), m_videoId("")
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_videoId);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_videoId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LDBGGetShareVideoId();
	}
};

//logic 玩家通过shareid来获取该分享码下的录像 在sharevideo中查询
struct LMsgL2LDBGetShareVideo:public LMsg
{
	Lint	m_userId;
	Lint	m_shareId;

	LMsgL2LDBGetShareVideo() :LMsg(MSG_L_2_LDB_GETSHAREVIDEO),m_userId(0),m_shareId(0)
	{

	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_shareId);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_shareId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LDBGetShareVideo();
	}
};


//logic 请求保存某已转移到sharevideo中的某录像的shareid
struct LMsgL2LDBSaveShareVideoId:public LMsg
{
	Lint	m_shareId;
	Lstring	m_videoId;

	LMsgL2LDBSaveShareVideoId() :LMsg(MSG_L_2_LDB_SAVESHAREVIDEOID),m_shareId(0),m_videoId("")
	{

	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_shareId);
		buff.Read(m_videoId);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_shareId);
		buff.Write(m_videoId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LDBSaveShareVideoId();
	}
};


//logicdb返回某录像是否有shareid，没有则将其从video中移至sharevideo中
struct LMsgLDB2LRetShareVideoId:public LMsg
{
	Lint	m_userId;
	Lint	m_shareId;
	Lstring	m_videoId;

	LMsgLDB2LRetShareVideoId() :LMsg(MSG_LDB_2_L_RETSHAREVIDEOID),m_userId(0),m_shareId(0),m_videoId("")
	{

	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_shareId);
		buff.Read(m_videoId);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_shareId);
		buff.Write(m_videoId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLDB2LRetShareVideoId();
	}
};

struct ShareVideoInfo{
	Lstring	m_videoId;
	Lint	m_time;
	Lint	m_flag;
	Lint	m_userId[4];
	Lint	m_score[4];
	Lint    m_user_count;
	Lstring m_playtype;

	ShareVideoInfo():m_time(0),m_flag(0), m_user_count(4){
		memset(m_userId,0,sizeof(m_userId));
		memset(m_score,0,sizeof(m_score));
	}
};
//logicdb 返回 通过shareid查询到的可能的录像
struct LMsgLDB2LRetShareVideo:public LMsg
{
	Lint		m_userid;
	Lint		m_count;
	std::vector<ShareVideoInfo> m_info; 
	LMsgLDB2LRetShareVideo() :LMsg(MSG_LDB_2_L_RETSHAREVIDEO),m_count(0),m_userid(0)
	{

	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userid);
		buff.Read(m_count);
		for(int x=0;x<m_count;x++)
		{	
			ShareVideoInfo info;
			buff.Read(info.m_videoId);
			buff.Read(info.m_time);
			buff.Read(info.m_flag);
			buff.Read(info.m_user_count);
			for(int i=0;i<4;i++)
			{
				buff.Read(info.m_userId[i]);
				buff.Read(info.m_score[i]);
			}
			m_info.push_back(info);
		}

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userid);
		buff.Write(m_count);
		for(int x=0;x<m_count;x++)
		{
			ShareVideoInfo& info = m_info[x];
			buff.Write(info.m_videoId);
			buff.Write(info.m_time);
			buff.Write(info.m_flag);
			buff.Write(info.m_user_count);
			for(int i=0;i<4;i++)
			{
				buff.Write(info.m_userId[i]);
				buff.Write(info.m_score[i]);
			}
		}
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLDB2LRetShareVideo();
	}
};


struct LMsgLMG2GHorseInfo :public LMsg
{
	Lstring	m_str;

	LMsgLMG2GHorseInfo():LMsg(MSG_LMG_2_G_HORSE_INFO)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_str);

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_str);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2GHorseInfo();
	}
};


struct LMsgLMG2LLogin:public LMsg
{
	Lint		m_userid;
	Lint		m_gateId;
	Luuid		m_geteUserId;
	Lstring		m_ip;
	Lstring		m_buyInfo;//够买信息
	Lint		m_hide;//购买隐藏0-隐藏 1- 不隐藏
	Lint		m_card_num;	//房卡数 （Card2）
	LMsgLMG2LLogin() :LMsg(MSG_LMG_2_L_USER_LOGIN)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userid);
		buff.Read(m_gateId);
		buff.Read(m_geteUserId);
		buff.Read(m_ip);
		buff.Read(m_buyInfo);
		buff.Read(m_hide);
		buff.Read(m_card_num);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userid);
		buff.Write(m_gateId);
		buff.Write(m_geteUserId);
		buff.Write(m_ip);
		buff.Write(m_buyInfo);
		buff.Write(m_hide);
		buff.Write(m_card_num);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LLogin();
	}
};

struct LMsgL2LMGModifyUserState:public LMsg
{
	Lint	m_userid;
	Lint	m_userstate;
	Lint	m_logicID;

	LMsgL2LMGModifyUserState() :LMsg(MSG_L_2_LMG_MODIFY_USER_STATE),m_userid(0),m_userstate(0),m_logicID(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userid);
		buff.Read(m_userstate);
		buff.Read(m_logicID);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userid);
		buff.Write(m_userstate);
		buff.Write(m_logicID);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LMGModifyUserState();
	}
};

struct LMsgL2GModifyUserState:public LMsg
{
	Luuid				m_gateid;
	Lint				m_userstate;
	Lint				m_logicID;

	LMsgL2GModifyUserState() :LMsg(MSG_L_2_G_MODIFY_USER_STATE),m_gateid(Luuid_NULL), m_userstate(0),m_logicID(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_gateid);
		buff.Read(m_userstate);
		buff.Read(m_logicID);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_gateid);
		buff.Write(m_userstate);
		buff.Write(m_logicID);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2GModifyUserState();
	}
};


struct LMsgLMG2LCreateDesk : public LMsg
{
	Lint				m_userid;
	Lint				m_gateId;
	Luuid				m_geteUserId;
	Lint				m_deskID;
	Lstring				m_ip;
	LUser				m_usert;

	Lint				m_flag;				//房间类型，1-2圈，2-四圈，3-8圈 4:1
	Lstring				m_secret;			//房间密码，如果为空，服务器会随机一个密码
	Lint				m_gold;				//房间抵住，单位元，最低为1元，最多不能超过100
	Lint				m_state;			//玩法规则 0 转转   1 长沙, 100开始为比赛场
	Lint				m_robotNum;			// 0,不加机器人，1，2，3加机器人数量
	CardValue			m_cardValue[CARD_COUNT];
	Lint				m_playTypeCount;
	Lint				m_free;				//是否为免费
	std::vector<Lint>	m_playtype;			//玩法
	Lint				m_rank;				//第几名
	Lint				m_score;			//玩家分数
	Lint				m_overScore;		//淘汰分数
	Lint				m_process;          //比赛进程
	Lint				m_playTypeStartHuCount;
	std::vector<Lint>	m_playtype_starthu;//起手胡类型


	LMsgLMG2LCreateDesk() :LMsg(MSG_LMG_2_L_CREATE_DESK),m_userid(0),m_gateId(0),m_geteUserId(Luuid_NULL),m_deskID(0),m_flag(0),m_gold(0),m_state(0),m_robotNum(0),m_playTypeCount(0), m_free(0)
	,m_rank(0),m_score(0),m_overScore(0), m_process(0), m_playTypeStartHuCount(0)
	{

	};
	
	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userid);
		buff.Read(m_gateId);
		buff.Read(m_geteUserId);
		buff.Read(m_deskID);
		buff.Read(m_ip);
		m_usert.Read(buff);
		buff.Read(m_flag);
		buff.Read(m_gold);
		buff.Read(m_state);
		buff.Read(m_robotNum);
		buff.Read(m_free);
		for (Lint i = 0; i < 112; ++i)
		{
			buff.Read(m_cardValue[i].m_color);
			buff.Read(m_cardValue[i].m_number);
		}
		buff.Read(m_playTypeCount);
		for (Lint i = 0 ; i < m_playTypeCount; i ++ )
		{
			Lint playType;
			buff.Read(playType);
			m_playtype.push_back(playType);
		}
		buff.Read(m_rank);
		buff.Read(m_score);
		buff.Read(m_overScore);
		buff.Read(m_process);
		buff.Read(m_playTypeStartHuCount);
		for (Lint i = 0; i < m_playTypeStartHuCount; i++)
		{
			Lint playTypeStartHu;
			buff.Read(playTypeStartHu);
			m_playtype_starthu.push_back(playTypeStartHu);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userid);
		buff.Write(m_gateId);
		buff.Write(m_geteUserId);
		buff.Write(m_deskID);
		buff.Write(m_ip);
		m_usert.Write(buff);
		buff.Write(m_flag);
		buff.Write(m_gold);
		buff.Write(m_state);
		buff.Write(m_robotNum);
		buff.Write(m_free);
		for (Lint i = 0; i < 112; ++i)
		{
			buff.Write(m_cardValue[i].m_color);
			buff.Write(m_cardValue[i].m_number);
		}
		buff.Write(m_playTypeCount);
		for (Lint i = 0 ; i < m_playTypeCount; i ++ )
		{
			buff.Write(m_playtype[i]);
		}
		buff.Write(m_rank);
		buff.Write(m_score);
		buff.Write(m_overScore);
		buff.Write(m_process);
		buff.Write(m_playTypeStartHuCount);
		for (Lint i = 0; i < m_playTypeStartHuCount; i++)
		{
			buff.Write(m_playtype_starthu[i]);
		}
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LCreateDesk();
	}
};

struct LMsgLMG2LAddToDesk : public LMsg
{
	Lint			m_userid;
	Lint			m_gateId;
	Luuid			m_geteUserId;
	Lint			m_deskID;
	Lstring			m_ip;
	LUser			m_usert;
	Lint			m_rank;				//第几名
	Lint			m_score;			//玩家分数
	Lint			m_overScore;		//淘汰分数
	Lint            m_sportId;          //比赛场id
	Lint            m_process;          //比赛进程 0 就是 淘汰赛阶段 1 晋级 第一阶段 2 晋级第二阶段 3 晋级最后阶段

	LMsgLMG2LAddToDesk() :LMsg(MSG_LMG_2_L_ADDTO_DESK),m_userid(0),m_gateId(0),m_geteUserId(Luuid_NULL),m_deskID(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userid);
		buff.Read(m_gateId);
		buff.Read(m_geteUserId);
		buff.Read(m_deskID);
		buff.Read(m_ip);
		m_usert.Read(buff);
		buff.Read(m_rank);		
		buff.Read(m_score);	
		buff.Read(m_overScore);
		buff.Read(m_sportId);
		buff.Read(m_process);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userid);
		buff.Write(m_gateId);
		buff.Write(m_geteUserId);
		buff.Write(m_deskID);
		buff.Write(m_ip);
		m_usert.Write(buff);
		buff.Write(m_rank);		
		buff.Write(m_score);	
		buff.Write(m_overScore);
		buff.Write(m_sportId);
		buff.Write(m_process);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LAddToDesk();
	}
};

//MSG_LMG_2_L_MATCH_ADD_DESK = 12020,		//比赛场创建房间
struct LMsgLMG2LMatchAddDesk : public LMsg
{
	Lint m_add_count;
	LMsgLMG2LCreateDesk m_create;
	std::vector<LMsgLMG2LAddToDesk> m_adds;

	LMsgLMG2LMatchAddDesk() :LMsg(MSG_LMG_2_L_MATCH_ADD_DESK), m_add_count(0)
	{
		m_adds.clear();
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_add_count);
		m_create.Read(buff);

		for (int i = 0; i < m_add_count; ++i)
		{
			LMsgLMG2LAddToDesk tmp_add;
			tmp_add.Read(buff);
			m_adds.push_back(tmp_add);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_add_count);
		m_create.Write(buff);

		int sz = m_adds.size();
		for (int i = 0; i < sz; ++i)
		{
			m_adds[i].Write(buff);
		}
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LMatchAddDesk();
	}
};


struct LMsgL2LMGModifyCard :public LMsg
{
	Lint			m_userid;
	Lint			isAddCard;
	Lint			cardType;
	Lint			cardNum;
	Lint			operType;
	Lstring			admin;
	LMsgL2LMGModifyCard() :LMsg(MSG_L_2_LMG_MODIFY_USER_CARD)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userid);
		buff.Read(isAddCard);
		buff.Read(cardType);
		buff.Read(cardNum);
		buff.Read(operType);
		buff.Read(admin);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userid);
		buff.Write(isAddCard);
		buff.Write(cardType);
		buff.Write(cardNum);
		buff.Write(operType);
		buff.Write(admin);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LMGModifyCard();
	}
};


struct LMsgL2LMGModifyPlayCount :public LMsg
{
	Lint			m_userid;
	Lint			m_curPlayCount;
	LMsgL2LMGModifyPlayCount() :LMsg(MSG_L_2_LMG_MODIFY_USER_PLAYCOUNT)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userid);
		buff.Read(m_curPlayCount);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userid);
		buff.Write(m_curPlayCount);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LMGModifyPlayCount();
	}
};

struct LMsgL2LMGRecyleDeskID :public LMsg
{
	Lint			m_serverID;
	Lint			m_deskID;
	LMsgL2LMGRecyleDeskID() :LMsg(MSG_L_2_LMG_RECYLE_DESKID),m_serverID(0),m_deskID(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_serverID);
		buff.Read(m_deskID);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_serverID);
		buff.Write(m_deskID);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LMGRecyleDeskID();
	}
};

struct LMsgL2LMGUserCircleIncreased : public LMsg
{
	Lint			m_userid;
	LMsgL2LMGUserCircleIncreased() :LMsg(MSG_L_2_LMG_USER_CIRCLE_INCREASED)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userid);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userid);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LMGUserCircleIncreased();
	}
};

struct LMsgL2LMGUserCompleteGame : public LMsg
{
	Lint			m_userId;
	Lint			m_startTime;
	Lint			m_totalCircleNum;
	Lint			m_playerNum;
	Lint			m_players[DESK_USER_COUNT];

	LMsgL2LMGUserCompleteGame() : LMsg(MSG_L_2_LMG_USER_COMPLETE_GAME) {}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_startTime);
		buff.Read(m_totalCircleNum);
		buff.Read(m_playerNum);
		for(int i = 0; i < m_playerNum && i < DESK_USER_COUNT; i++)
			buff.Read(m_players[i]);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_startTime);
		buff.Write(m_totalCircleNum);
		buff.Write(m_playerNum);
		for (int i = 0; i < m_playerNum && i < DESK_USER_COUNT; i++)
			buff.Write(m_players[i]);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LMGUserCompleteGame();
	}
};

//G2L
struct LMsgG2LHEARTBEAT :public LMsg
{
	Lint			m_gateID;
	LMsgG2LHEARTBEAT() :LMsg(MSG_G_2_L_BREATH),m_gateID(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_gateID);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_gateID);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgG2LHEARTBEAT();
	}
};

struct LMsgL2GHEARTBEAT_BACK :public LMsg
{
	Lint			m_logicID;
	LMsgL2GHEARTBEAT_BACK() :LMsg(MSG_L_2_G_BREATH),m_logicID(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_logicID);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_logicID);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2GHEARTBEAT_BACK();
	}
};

//G2LMG
struct LMsgG2LMGHEARTBEAT :public LMsg
{
	Lint			m_gateID;
	LMsgG2LMGHEARTBEAT() :LMsg(MSG_G_2_LMG_BREATH),m_gateID(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_gateID);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_gateID);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgG2LMGHEARTBEAT();
	}
};

struct LMsgLMG2GHEARTBEAT_BACK :public LMsg
{
	LMsgLMG2GHEARTBEAT_BACK() :LMsg(MSG_LMG_2_G_BREATH)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2GHEARTBEAT_BACK();
	}
};


//L2LMG
struct LMsgL2LMGHEARTBEAT :public LMsg
{
	Lint			m_logicID;
	LMsgL2LMGHEARTBEAT() :LMsg(MSG_L_2_LMG_BREATH),m_logicID(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_logicID);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_logicID);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LMGHEARTBEAT();
	}
};

struct LMsgLMG2LHEARTBEAT_BACK :public LMsg
{
	LMsgLMG2LHEARTBEAT_BACK() :LMsg(MSG_LMG_2_L_BREATH)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LHEARTBEAT_BACK();
	}
};

//L2LDB
struct LMsgL2LDBHEARTBEAT :public LMsg
{
	Lint			m_logicID;
	LMsgL2LDBHEARTBEAT() :LMsg(MSG_L_2_LDB_BREATH),m_logicID(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_logicID);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_logicID);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LDBHEARTBEAT();
	}
};

struct LMsgLDB2LHEARTBEAT_BACK :public LMsg
{
	LMsgLDB2LHEARTBEAT_BACK() :LMsg(MSG_LDB_2_L_BREATH)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLDB2LHEARTBEAT_BACK();
	}
};

//LMG2LMG
struct LMsgLMG2LDBHEARTBEAT :public LMsg
{
	Lint			m_logicID;
	LMsgLMG2LDBHEARTBEAT() :LMsg(MSG_LMG_2_LDB_BREATH),m_logicID(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_logicID);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_logicID);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LDBHEARTBEAT();
	}
};

struct LMsgLDB2LMGHEARTBEAT_BACK :public LMsg
{
	LMsgLDB2LMGHEARTBEAT_BACK() :LMsg(MSG_LDB_2_LMG_BREATH)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLDB2LMGHEARTBEAT_BACK();
	}
};
//LMG2CE
struct LMsgLMG2CEHEARTBEAT :public LMsg
{
	Lint			m_logicID;
	LMsgLMG2CEHEARTBEAT() :LMsg(MSG_LMG_2_CE_BREATH),m_logicID(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_logicID);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_logicID);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2CEHEARTBEAT();
	}
};

struct LMsgCE2LMGHEARTBEAT_BACK :public LMsg
{
	LMsgCE2LMGHEARTBEAT_BACK() :LMsg(MSG_CE_2_LMG_BREATH)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCE2LMGHEARTBEAT_BACK();
	}
};

//center发给logicmanager礼券信息和礼物信息
struct LMsgCE2LMGUserGiftInfo :public LMsg
{
	Lint    m_gift_count;
	std::vector<gift_info> m_gift_info; 
	LMsgCE2LMGUserGiftInfo():LMsg(MSG_CE_2_LMG_User_Gift_Info)
	{
	}
	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_gift_count);
		for(int x=0;x<m_gift_count;x++)
		{
			gift_info l_gift;
			l_gift.Read(buff);
			m_gift_info.push_back(l_gift);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_gift_count);
		for(int x=0;x<m_gift_info.size();x++)
		{
			m_gift_info[x].Write(buff);
		}
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCE2LMGUserGiftInfo();
	}
};
//logicmanager 发给 center 礼券兑换记录
struct LMsgLMG2CEUserCouponsExchangeRecord :public LMsg
{
	Lstring	m_unionId;
	Lint	m_logicId;
	LMsgLMG2CEUserCouponsExchangeRecord() :LMsg(MSG_LMG_2_CE_User_Coupons_Exchange_Record)
	{
	}
	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_unionId);
		buff.Read(m_logicId);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_unionId);
		buff.Write(m_logicId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2CEUserCouponsExchangeRecord();
	}
};
//center 发给 logicmanager 礼券兑换记录
struct LMsgCE2LMGUserCouponsExchangeRecord :public LMsg
{
	Lint	m_userId;
	Lint	m_record_count;
	std::vector<gift_exchange_record> m_record;
	LMsgCE2LMGUserCouponsExchangeRecord() :LMsg(MSG_CE_2_LMG_User_Coupons_Exchange_Record),m_record_count(0),m_userId(0)
	{
	}
	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_record_count);
		for(int x=0;x<m_record_count;x++)
		{
			gift_exchange_record record;
			record.Read(buff);
			m_record.push_back(record);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_record_count);
		for(int x=0;x<m_record.size();x++)
		{
			m_record[x].Write(buff);
		}
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCE2LMGUserCouponsExchangeRecord();
	}
};



//logicmanager 发给 center 礼券兑换消息
struct LMsgLMG2CEUserCouponsExchangeInfo :public LMsg
{
	Lstring	m_unionId;
	Lint    m_logicId;
	Lint	m_giftId;
	Lint    m_time;
	Lstring m_phoneNum;
	Lstring m_receiverName;
	Lstring m_receiverAddress;
	LMsgLMG2CEUserCouponsExchangeInfo() :LMsg(MSG_LMG_2_CE_User_Coupons_Exchange_Info)
	{
	}
	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_unionId);
		buff.Read(m_logicId);
		buff.Read(m_giftId);
		buff.Read(m_time);
		buff.Read(m_phoneNum);
		buff.Read(m_receiverName);
		buff.Read(m_receiverAddress);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_unionId);
		buff.Write(m_logicId);
		buff.Write(m_giftId);
		buff.Write(m_time);
		buff.Write(m_phoneNum);
		buff.Write(m_receiverName);
		buff.Write(m_receiverAddress);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2CEUserCouponsExchangeInfo();
	}
};
//center 发给 logicmanager 礼券兑换结果
struct LMsgCE2LMGUserCouponsExchangeInfo :public LMsg
{
	Lint	m_userId;
	Lint	m_errorId;
	LMsgCE2LMGUserCouponsExchangeInfo() :LMsg(MSG_CE_2_LMG_User_Coupons_Exchange_Info)
	{
	}
	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_errorId);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_errorId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCE2LMGUserCouponsExchangeInfo();
	}
};

struct LMsgL2LDBExecSql : public LMsg
{
	Lstring		m_sql;

	LMsgL2LDBExecSql() : LMsg(MSG_L_2_LDB_EXEC_SQL) {}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_sql);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_sql);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LDBExecSql();
	}
};

struct LMsgLMG2LDBReqTaskProgress : public LMsg
{
	Lint			m_userId;
	Lint			m_taskId;
	Lstring			m_sql;

	LMsgLMG2LDBReqTaskProgress() : LMsg(MSG_LMG_2_LDB_REQ_TASK_PROGRESS) {}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_taskId);
		buff.Read(m_sql);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_taskId);
		buff.Write(m_sql);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LDBReqTaskProgress();
	}
};

struct LMsgLDB2LMGTaskProgress : public LMsg
{
	Lint		m_userId;
	Lint		m_taskId;
	Lint		m_result;
	Lint		m_progressId;
	Lint		m_progress;
	Lint		m_rewardRecved;

	LMsgLDB2LMGTaskProgress() : LMsg(MSG_LDB_2_LMG_REQ_TASK_PROGRESS) {}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_taskId);
		buff.Read(m_result);
		buff.Read(m_progressId);
		buff.Read(m_progress);
		buff.Read(m_rewardRecved);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_taskId);
		buff.Write(m_result);
		buff.Write(m_progressId);
		buff.Write(m_progress);
		buff.Write(m_rewardRecved);
		return true;
	}
	
	virtual LMsg* Clone()
	{
		return new LMsgLDB2LMGTaskProgress();
	}
};

struct LMsgLMG2LDBReqBindingRelationships : public LMsg
{
	Lint			m_userId;

	LMsgLMG2LDBReqBindingRelationships() : LMsg(MSG_LMG_2_LDB_REQ_BINDING_RELATIONSHIPS) {}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LDBReqBindingRelationships;
	}
};

struct LMsgLDB2LMGBindingRelationships : public LMsg
{
	Lint		m_userId;
	Lint		m_inviterId;
	Lint		m_finished;
	Lint		m_inviteeCount;
	Lint		m_invitees[NUM_MAX_INVITEE];
	Lint		m_taskFinished[NUM_MAX_INVITEE];

	LMsgLDB2LMGBindingRelationships() : LMsg(MSG_LDB_2_LMG_REQ_BINDING_RELATIONSHIPS) {}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_inviterId);
		buff.Read(m_finished);
		buff.Read(m_inviteeCount);
		for (int i = 0; i < m_inviteeCount; i++)
		{
			buff.Read(m_invitees[i]);
			buff.Read(m_taskFinished[i]);
		}

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_inviterId);
		buff.Write(m_finished);
		buff.Write(m_inviteeCount);
		for (int i = 0; i < m_inviteeCount; i++)
		{
			buff.Write(m_invitees[i]);
			buff.Write(m_taskFinished[i]);
		}

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLDB2LMGBindingRelationships;
	}
};

struct LMsgLMG2LDBInsertTaskProgress : public LMsg
{
	Lint		m_userId;
	Lint		m_taskId;
	Lstring		m_sql;

	LMsgLMG2LDBInsertTaskProgress() : LMsg(MSG_LMG_2_LDB_INSERT_TASK_PROGRESS) {}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_taskId);
		buff.Read(m_sql);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_taskId);
		buff.Write(m_sql);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LDBInsertTaskProgress;
	}

};

struct LMsgLDB2LMGInsertTaskProgress : public LMsg
{
	Lint		m_userId;
	Lint		m_taskId;
	Lint		m_progressId;

	LMsgLDB2LMGInsertTaskProgress() : LMsg(MSG_LDB_2_LMG_INSERT_TASK_PROGRESS) {}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_taskId);
		buff.Read(m_progressId);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_taskId);
		buff.Write(m_progressId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLDB2LMGInsertTaskProgress;
	}

};

struct LMsgLMG2LDBReqActiveGiftStock : public LMsg
{
	Lint	m_activeId;

	LMsgLMG2LDBReqActiveGiftStock() : LMsg(MSG_LMG_2_LDB_REQ_ACTIVE_GIFT_STOCK) {}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_activeId);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_activeId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LDBReqActiveGiftStock;
	}

};

struct LMsgLDB2LMGActiveGiftStock : public LMsg
{
	Lint					m_error;		// 0 : succeed, not 0 : failed
	Lint					m_activeId;
	std::vector<Lint>		m_giftStock;

	LMsgLDB2LMGActiveGiftStock() : LMsg(MSG_LDB_2_LMG_ACTIVE_GIFT_STOCK) {}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_error);
		buff.Read(m_activeId);
		Lsize size = 0;
		buff.Read(size);
		for (Lsize i = 0; i < size; i++)
		{
			Lint giftStock = 0;
			buff.Read(giftStock);
			m_giftStock.push_back(giftStock);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_error);
		buff.Write(m_activeId);
		Lsize size = m_giftStock.size();
		buff.Write(size);
		for (Lsize i = 0; i < size; i++)
			buff.Write(m_giftStock[i]);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLDB2LMGActiveGiftStock;
	}
};

struct LMsgLMG2LDBReqLuckyDrawNum : public LMsg
{
	Lint		m_userId;

	LMsgLMG2LDBReqLuckyDrawNum() : LMsg(MSG_LMG_2_LDB_REQ_LUCKY_DRAW_NUM) {}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LDBReqLuckyDrawNum;
	}
};

struct LMsgLDB2LMGLuckyDrawNum : public LMsg
{
	Lint	m_userId;
	Lint	m_error;
	Lint	m_drawNum;

	LMsgLDB2LMGLuckyDrawNum() : LMsg(MSG_LDB_2_LMG_LUCKY_DRAW_NUM) {}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_error);
		buff.Read(m_drawNum);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_error);
		buff.Write(m_drawNum);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLDB2LMGLuckyDrawNum;
	}

};

struct LMsgLMG2LDBInsertBindingRelationship : public LMsg
{
	Lint		m_userId;
	Lint		m_inviter;
	Lint		m_maxInviteeNum;

	LMsgLMG2LDBInsertBindingRelationship()
		: LMsg(MSG_LMG_2_LDB_INSERT_BINDING_RELATIONSHIP), m_userId(-1), m_inviter(-1), m_maxInviteeNum(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_inviter);
		buff.Read(m_maxInviteeNum);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_inviter);
		buff.Write(m_maxInviteeNum);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LDBInsertBindingRelationship;
	}
};

struct LMsgLDB2LMGInsertBindingRelationship : public LMsg
{
	Lint		m_userId;
	Lint		m_inviter;
	ErrorCode	m_errorCode;

	LMsgLDB2LMGInsertBindingRelationship()
		: LMsg(MSG_LDB_2_LMG_INSERT_BINDING_RELATIONSHIP), m_userId(-1), m_inviter(-1), m_errorCode(ErrorNone)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_inviter);
		buff.Read(m_errorCode);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_inviter);
		buff.Write(m_errorCode);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLDB2LMGInsertBindingRelationship;
	}
};

// logingate to center
struct LMsgLGCEUserMsgWrapper:public LMsg
{
	Lint	m_idOnGate;
	LMsg*	m_userMsg;
	bool	m_deleteUserMsg;

	LMsgLGCEUserMsgWrapper() : LMsg(MSG_LG_CE_USER_MSG_WRAPPER)
	{
		m_idOnGate = 0;
		m_userMsg = NULL;
		m_deleteUserMsg = true;
	}

	~LMsgLGCEUserMsgWrapper()
	{
		if(m_deleteUserMsg && m_userMsg != NULL)
			delete m_userMsg;
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_idOnGate);
		m_userMsg = NULL;

		MsgHeader header = {0};
		buff.Read((char*)&header, sizeof(header));
		if(header.bodySize > (0xFFFF - sizeof(header)))
		{
			LLOG_ERROR("LMsgLGCEUserMsgWrapper::Read -- The data len more than max value");
			return true;
		}

		try
		{
			msgpack::unpacked  unpack;
			msgpack::unpack(&unpack, buff.Data() + buff.GetOffset(), buff.Size() - buff.GetOffset());
			msgpack::object obj = unpack.get();

			Lint msgId = 0;
			ReadMapData(obj, "m_msgId", msgId);
			m_userMsg = LMsgFactory::Instance().CreateMsg(msgId);
			if (m_userMsg)
				m_userMsg->Read(obj);
			else
				LLOG_ERROR("LMsgLGCEUserMsgWrapper::Read(): user msg id %d does not exist.", msgId);
		}
		catch (...)
		{
			LLOG_ERROR("LMsgLGCEUserMsgWrapper::Read()::RecvMsgPack error");
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_idOnGate);
		auto dataBuff = m_userMsg->GetSendBuff();
		buff.Write(dataBuff->Data(), dataBuff->Size());
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLGCEUserMsgWrapper();
	}
};

struct LMsgLG2CEHeartBeat : public LMsg
{
	LMsgLG2CEHeartBeat() : LMsg(MSG_LG_2_CE_HEARTBEAT)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLG2CEHeartBeat();
	}
};

struct LMsgS2SKeepAlive : public LMsg
{
	LMsgS2SKeepAlive() : LMsg(MSG_S_2_S_KEEP_ALIVE){}

	virtual bool Read(LBuff& buff)
	{
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgS2SKeepAlive();
	}
};

struct LMsgS2SKeepAliveAck : public LMsg
{
	LMsgS2SKeepAliveAck() : LMsg(MSG_S_2_S_KEEP_ALIVE_ACK){}

	virtual bool Read(LBuff& buff)
	{
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgS2SKeepAliveAck();
	}
};

//////////////////////////////////////////////////////////////////////////////////
struct LMsgLMG2CEGetPhoneVldCode : public LMsg
{
	Lstring m_unionId;
	Lstring	m_phoneNum;  //手机号
	Lint    m_type;      //0 为只获得验证码，1 手机号绑定模块

	LMsgLMG2CEGetPhoneVldCode() : LMsg(MSG_LMG_2_CE_GET_PHONE_VLDCODE)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_unionId);
		buff.Read(m_phoneNum);
		buff.Read(m_type);

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_unionId);
		buff.Write(m_phoneNum);
		buff.Write(m_type);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2CEGetPhoneVldCode();
	}
};


struct LMsgCE2LMGGetPhoneVldCode : public LMsg
{
	Lint    m_userId;
	Lstring m_unionId;
	Lstring m_resCode;

	LMsgCE2LMGGetPhoneVldCode() : LMsg(MSG_CE_2_LMG_GET_PHONE_VALCODE)
	{
		m_userId = 0;
		m_unionId = "";
		m_resCode = "";
	}

	virtual bool Read(LBuff& buff)
	{

		buff.Read(m_userId);
		buff.Read(m_unionId);
		buff.Read(m_resCode);

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_unionId);
		buff.Write(m_resCode);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCE2LMGGetPhoneVldCode();
	}
};


struct LMsgLMG2CEBindPhoneNum : public LMsg
{
	Lstring m_unionId;
	Lstring	m_phoneNum;     //手机号
	Lstring m_vldCode;   //校验码

	LMsgLMG2CEBindPhoneNum() : LMsg(MSG_LMG_2_CE_BIND_PHONE_NUM)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_unionId);
		buff.Read(m_phoneNum);
		buff.Read(m_vldCode);

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_unionId);
		buff.Write(m_phoneNum);
		buff.Write(m_vldCode);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2CEBindPhoneNum();
	}
};


struct LMsgCE2LMGBindPhoneNum : public LMsg
{
	Lint m_userId;
	Lstring m_unionId;
	Lstring	m_phoneNum;  //手机号
	Lstring m_vldCode;   //校验码
	Lstring m_resCode;

	LMsgCE2LMGBindPhoneNum() : LMsg(MSG_CE_2_LMG_BIND_PHONE_NUM)
	{
		m_resCode = "";
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_unionId);
		buff.Read(m_phoneNum);
		buff.Read(m_vldCode);
		buff.Read(m_resCode);

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_unionId);
		buff.Write(m_phoneNum);
		buff.Write(m_vldCode);
		buff.Write(m_resCode);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCE2LMGBindPhoneNum();
	}
};

//请求是否绑定用户信息
//MSG_LMG_2_CE_IS_BIND_PHONE_NUM = 6420

struct LMsgLMG2CEIsBindPhoneNum : public LMsg
{
	Lstring m_unionId;

	LMsgLMG2CEIsBindPhoneNum() : LMsg(MSG_LMG_2_CE_IS_BIND_PHONE_NUM)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_unionId);

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_unionId);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2CEIsBindPhoneNum();
	}
};


//MSG_CE_2_LMG_IS_BIND_PHONE_NUM = 6421

struct LMsgCE2LMGIsBindPhoneNum : public LMsg
{
	Lint m_userId;
	Lstring m_unionId;
	Lint m_isBindPhoneNum;     //手机号是否绑定

	LMsgCE2LMGIsBindPhoneNum() : LMsg(MSG_CE_2_LMG_IS_BIND_PHONE_NUM)
	{
		m_userId = 0;
		m_isBindPhoneNum = 0;
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_unionId);
		buff.Read(m_isBindPhoneNum);

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_unionId);
		buff.Write(m_isBindPhoneNum);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCE2LMGIsBindPhoneNum();
	}
};


////////////////////////////////身份证绑定////////////////////////////////////

//请求 绑定身份证
//MSG_LMG_2_CE_BIND_IDCARD = 6423

struct LMsgLMG2CEBindIDCard : public LMsg
{
	Lstring m_unionId;    //unioId
	Lstring	m_name;      //名字
	Lstring m_IDCard;    //身份证号

	LMsgLMG2CEBindIDCard() : LMsg(MSG_LMG_2_CE_BIND_IDCARD)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_unionId);
		buff.Read(m_name);
		buff.Read(m_IDCard);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_unionId);
		buff.Write(m_name);
		buff.Write(m_IDCard);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2CEBindIDCard();
	}
};

//回应 绑定身份证
//MSG_CE_2_LMG_BIND_IDCARD = 6424

struct LMsgCE2LMGBindBindIDCard : public LMsg
{
	Lint m_userId;       //用户id
	Lint m_resCode; 	 //结果码，0 成功，其他异常

	LMsgCE2LMGBindBindIDCard() : LMsg(MSG_CE_2_LMG_BIND_IDCARD)
	{
		m_userId = 0;
		m_resCode = -1;
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_resCode);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_resCode);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCE2LMGBindBindIDCard();
	}
};



//请求 是否绑定身份证信息
//MSG_LMG_2_CE_IS_BIND_IDCARD = 6425

struct LMsgLMG2CEIsBindIDCard : public LMsg
{
	Lstring m_unionId;

	LMsgLMG2CEIsBindIDCard() : LMsg(MSG_LMG_2_CE_IS_BIND_IDCARD)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_unionId);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_unionId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2CEIsBindIDCard();
	}
};

//回应 是否绑定身份证信息
//MSG_CE_2_LMG_IS_BIND_IDCARDE = 6426

struct LMsgCE2LMGIsBindIDCard : public LMsg
{
	Lint m_userId;
	Lint m_resCode;     //0 表示尚未绑定 1表示已经绑定手机号

	LMsgCE2LMGIsBindIDCard() : LMsg(MSG_CE_2_LMG_IS_BIND_IDCARDE)
	{
		m_userId = 0;
		m_resCode = 0;
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_resCode);

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_resCode);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCE2LMGIsBindIDCard();
	}
};

//比赛结果返回
//MSG_L_2_LMG_SPORT_RESULT = 11031,

//LogServer 比赛结果返回
struct LMsgL2LMGSportResult:public LMsg
{
	Lint m_logicId; //具体逻辑服的id
	Lint m_rescode; //0 正常返回，1 等待超时
	Lint m_deskid;  //桌子号
	Lint m_desktype; //桌子类型
	
	Lint m_uid1; //第1个玩家id
	Lint m_uid2; //第2个玩家id
	Lint m_uid3; //第3个玩家id
	Lint m_uid4; //第4个玩家id
	
	Lint m_score1; //第1玩家的积分
	Lint m_score2; //第2玩家积分
	Lint m_score3; //第3玩家的积分
	Lint m_score4; //第4玩家的积分

	LMsgL2LMGSportResult() :LMsg(MSG_L_2_LMG_SPORT_RESULT)
	{
		m_logicId = 0;
		m_rescode = 0;
		m_deskid = 0;
		m_desktype = 0;
		m_uid1 = 0;
		m_uid2 = 0;
		m_uid3 = 0;
		m_uid4 = 0;
		m_score1 = 0;
		m_score2 = 0;
		m_score3 = 0;
		m_score4 = 0;
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_logicId);
		buff.Read(m_rescode);
		buff.Read(m_deskid);
		buff.Read(m_desktype);
		buff.Read(m_uid1);
		buff.Read(m_uid2);
		buff.Read(m_uid3);
		buff.Read(m_uid4);
		buff.Read(m_score1);
		buff.Read(m_score2);
		buff.Read(m_score3);
		buff.Read(m_score4);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_logicId);
		buff.Write(m_rescode);
		buff.Write(m_deskid);
		buff.Write(m_desktype);
		buff.Write(m_uid1);
		buff.Write(m_uid2);
		buff.Write(m_uid3);
		buff.Write(m_uid4);
		buff.Write(m_score1);
		buff.Write(m_score2);
		buff.Write(m_score3);
		buff.Write(m_score4);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2LMGSportResult();
	}
};

// 玩家登陆时 请求 LogicDB加载 比赛记录信息 [2016-8-16 willing]
struct LMsgLMG2LDBReqMatchRecord : public LMsg
{
	Lint	m_nUid;		// 角色ID [2016-8-16 willing]

	LMsgLMG2LDBReqMatchRecord() : LMsg(MSG_LMG_2_LDB_REQ_MATCH_RECORD)
	{
		m_nUid = 0;
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_nUid);

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_nUid);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LDBReqMatchRecord();
	}
};

struct MatchRecordInfo 
{
	Lstring		nId;			// 唯一ID [2016-8-13 willing]
	Lint		nSportID;		// 比赛ID [2016-8-17 willing]
	Lint		nTipsID;		// 记录内容 [2016-8-17 willing]
	Lint		nSaveTime;		// 保持时间 [2016-8-13 willing]
	Lint		nRewardID;		// 奖励表ID [2016-8-13 willing]
	Lint		nRank;			// 名次 [2016-8-13 willing]
	Lint		nRead;			// 读取标识 [2016-8-13 willing]
	Lint		nDraw;			// 领取标识 [2016-8-13 willing]
	Lint		nShare;			// 是否分享过了 [2016-8-17 willing]

	MSGPACK_DEFINE(nId,nSportID,nTipsID,nSaveTime,nRewardID,nRank,nRead,nDraw,nShare); 

	void	Read(LBuff& buff)
	{
		buff.Read(nId);
		buff.Read(nSportID);
		buff.Read(nTipsID);
		buff.Read(nSaveTime);
		buff.Read(nRewardID);
		buff.Read(nRank);
		buff.Read(nRead);
		buff.Read(nDraw);
		buff.Read(nShare);
	}

	void	Write(LBuff& buff)
	{
		buff.Write(nId);
		buff.Write(nSportID);
		buff.Write(nTipsID);
		buff.Write(nSaveTime);
		buff.Write(nRewardID);
		buff.Write(nRank);
		buff.Write(nRead);
		buff.Write(nDraw);
		buff.Write(nShare);
	}
};

struct LMsgLDB2LMGMatchRecord : public LMsg
{
	Lint	m_nUid;
	Lint	m_nRecordCount;
	std::vector<MatchRecordInfo>	m_tRecordVec;

	LMsgLDB2LMGMatchRecord():LMsg(MSG_LDB_2_LMG_MATCH_RECORD)
	{
		m_nUid = 0;
		m_nRecordCount = 0;
		m_tRecordVec.clear();
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_nUid);
		buff.Read(m_nRecordCount);

		for ( int i=0; i<m_nRecordCount; ++i )
		{
			MatchRecordInfo recordInfo;
			recordInfo.Read(buff);

			m_tRecordVec.push_back(recordInfo);
		}

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_nUid);
		buff.Write(m_nRecordCount);

		for ( int i=0; i<(int)(m_tRecordVec.size()); ++i )
		{
			m_tRecordVec[i].Write(buff);
		}

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLDB2LMGMatchRecord();
	}
};

// LogicManager 向 LogicDB 发送请求，创建新的 MatchRecord记录 [2016-8-16 willing]
struct LMsgLMG2LDBCreateNewMatchRecord : public LMsg
{
	Lint	nUid;
	Lint	nSportID;
	Lint    nTime;
	Lint	nTipsID;
	Lint	nRewardID;
	Lint	nRank;
	Lint	nRandid;
	Lint	nNeedLoad;		// 0 插入数据后，不需要 返回，1 需要返回 [2016-8-16 willing]

	LMsgLMG2LDBCreateNewMatchRecord():LMsg(MSG_LMG_2_LDB_NEW_MATCH_RECORD)
	{
		nUid = 0;
		nSportID = 0;
		nTime = 0;
		nTipsID = 0;
		nRewardID = 0;
		nRank = 0;
		nRandid = 0;
		nNeedLoad = 0;
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(nUid);
		buff.Read(nSportID);
		buff.Read(nTime);
		buff.Read(nTipsID);
		buff.Read(nRewardID);
		buff.Read(nRank);
		buff.Read(nRandid);
		buff.Read(nNeedLoad);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(nUid);
		buff.Write(nSportID);
		buff.Write(nTime);
		buff.Write(nTipsID);
		buff.Write(nRewardID);
		buff.Write(nRank);
		buff.Write(nRandid);
		buff.Write(nNeedLoad);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LDBCreateNewMatchRecord();
	}
};

// LogicDB 向 LogicManager 返回 新创建的 比赛记录 信息 [2016-8-16 willing]
struct LMsgLDB2LMGCreateNewMatchRecord : public LMsg
{
	Lint nUid;
	MatchRecordInfo recordInfo;

	LMsgLDB2LMGCreateNewMatchRecord() : LMsg(MSG_LDB_2_LMG_NEW_MATCH_RECORD)
	{
		nUid = 0;
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(nUid);
		recordInfo.Read(buff);
		return true;
	}
	
	virtual bool Write(LBuff& buff)
	{
		buff.Write(nUid);
		recordInfo.Write(buff);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLDB2LMGCreateNewMatchRecord();
	}
};

// LogicManager 修改比赛记录 [2016-8-16 willing]
struct LMsgLDB2LMGModifyMatchRecord : public LMsg
{
	Lstring nRecordID;
	Lint nUid;
	Lint nRank;
	Lint nRead;
	Lint nDraw;
	Lint nShare;

	LMsgLDB2LMGModifyMatchRecord() : LMsg(MSG_LMG_2_LDB_MODIFY_MATCH_RECORD)
	{
		nUid = -1;
		nRank = -1;
		nRead = -1;
		nDraw = -1;
		nShare = -1;
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(nRecordID);
		buff.Read(nUid);
		buff.Read(nRank);
		buff.Read(nRead);
		buff.Read(nDraw);
		buff.Read(nShare);

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(nRecordID);
		buff.Write(nUid);
		buff.Write(nRank);
		buff.Write(nRead);
		buff.Write(nDraw);
		buff.Write(nShare);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLDB2LMGModifyMatchRecord();
	}
};

// LogicManager 删除 比赛记录 [2016-8-18 willing]
struct LMsgLMG2LDBRmvMatchRecord : public LMsg
{
	Lstring nRecordID;
	Lint nUid;

	LMsgLMG2LDBRmvMatchRecord() : LMsg(MSG_LMG_2_LDB_RMV_MATCH_RECORD)
	{
		nUid = 0;
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(nRecordID);
		buff.Read(nUid);

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(nRecordID);
		buff.Write(nUid);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LDBRmvMatchRecord();
	}
};

// logicManager to CenterServer,客户端请求所有收件地址 [2016-8-17 willing]
struct LMsgLMG2CEReqAllAddr : public LMsg
{
	Lint	nUid;				// 玩家ID [2016-8-17 willing]
	Lstring strUnioid;
	
	LMsgLMG2CEReqAllAddr() : LMsg(MSG_LMG_2_CE_REQ_ALL_ADDR)
	{
		nUid = 0;
		strUnioid = "";
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(nUid);
		buff.Read(strUnioid);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(nUid);
		buff.Write(strUnioid);
		return false;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2CEReqAllAddr();
	}
};

// CenterServer to LogicManager, 返回 所有 收件地址 [2016-8-17 willing]
struct LMsgCE2LMGAllAddr : public LMsg
{
	Lint nUid;
	Lint nAddrCount;
	tUserAddrInfoVec addrInfoVec;

	LMsgCE2LMGAllAddr() : LMsg(MSG_CE_2_LMG_ALL_ADDR)
	{
		nUid = 0;
		nAddrCount = 0;
		addrInfoVec.clear();
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(nUid);
		buff.Read(nAddrCount);

		SUserAddrInfo addrInfo;

		for ( int i=0; i<nAddrCount; ++i )
		{
			addrInfo.Read(buff);

			addrInfoVec.push_back(addrInfo);
		}

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(nUid);
		buff.Write(nAddrCount);

		int nCount = (int)(addrInfoVec.size());

		for ( int i=0; i<nCount; ++i )
		{
			addrInfoVec[i].Write(buff);
		}

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCE2LMGAllAddr();
	}
};

// LogicManager to CenterServer 玩家添加地址 [2016-8-18 willing]
struct LMsgLMG2CEAddAddr : public LMsg
{
	Lint		nUid;		   // 玩家ID [2016-8-17 willing]
	Lint        nTime;         // 记录时间
	Lstring		strOpenid;     // openid
	Lstring		strUserName;   // 收件人姓名 [2016-8-17 willing]
	Lstring		strPhone;	   // 电话号码 [2016-8-17 willing]
	Lint		nZipCode;	   // 邮政编码 [2016-8-17 willing]
	Lstring		strAddr;	   // 收件地址 [2016-8-17 willing]
	Lint		nRewardid;	   // 奖励的id 
	Lint		nTypeid;	   //种类的id，比赛场id
	Lint		nArgsid;	   //参数,例如名次
	Lstring     strDesc;       //描述

	LMsgLMG2CEAddAddr():LMsg(MSG_LMG_2_CE_ADD_ADDR)
	{
		nUid = 0;
		nTime = 0;
		strOpenid = "";
		strUserName = "";
		strPhone = "";
		nZipCode = 0;
		strAddr = "";
		nRewardid = 0;
		nTypeid = 0;
		nArgsid = 0;
		strDesc = "";
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(nUid);
		buff.Read(nTime);
		buff.Read(strOpenid);
		buff.Read(strUserName);
		buff.Read(strPhone);
		buff.Read(nZipCode);
		buff.Read(strAddr);
		buff.Read(nRewardid);
		buff.Read(nTypeid);
		buff.Read(nArgsid);
		buff.Read(strDesc);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(nUid);
		buff.Write(nTime);
		buff.Write(strOpenid);
		buff.Write(strUserName);
		buff.Write(strPhone);
		buff.Write(nZipCode);
		buff.Write(strAddr);
		buff.Write(nRewardid);
		buff.Write(nTypeid);
		buff.Write(nArgsid);
		buff.Write(strDesc);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2CEAddAddr();
	}
};

// CenterServer to LogicManager, 返回地址添加的结果 [2016-8-18 willing]
struct LMsgCE2LMGAddAddrRet : public LMsg
{
	Lint nUid;
	Lint nErrorCode;

	LMsgCE2LMGAddAddrRet() : LMsg(MSG_CE_2_LMG_ADDR_ADDR_RET)
	{
		nUid = 0;
		nErrorCode = 0;
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(nUid);
		buff.Read(nErrorCode);

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(nUid);
		buff.Write(nErrorCode);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCE2LMGAddAddrRet();
	}
};

// LogicManager to CenterServer 修改已添加的地址 [2016-8-18 willing]
struct LMsgLMG2CEModifyAddr : public LMsg
{
	Lint		nUid;			// 玩家ID [2016-8-17 willing]
	Lstring		strUnioid;
	Lint		nID;			// 唯一ID [2016-8-18 willing]
	Lstring		strUserName;	// 收件人姓名 [2016-8-17 willing]
	Lstring		strPhone;			// 电话号码 [2016-8-17 willing]
	Lint		nZipCode;		// 邮政编码 [2016-8-17 willing]
	Lstring		strUserAddr;	// 收件地址 [2016-8-17 willing]

	LMsgLMG2CEModifyAddr():LMsg(MSG_LMG_2_CE_MODIFY_ADDR)
	{
		nUid = 0;
		strUnioid = "";
		nID = 0;
		strUserName = "";
		strPhone = "";
		nZipCode = 0;
		strUserAddr = "";
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(nUid);
		buff.Read(strUnioid);
		buff.Read(nID);
		buff.Read(strUserName);
		buff.Read(strPhone);
		buff.Read(nZipCode);
		buff.Read(strUserAddr);

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(nUid);
		buff.Write(strUnioid);
		buff.Write(nID);
		buff.Write(strUserName);
		buff.Write(strPhone);
		buff.Write(nZipCode);
		buff.Write(strUserAddr);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2CEModifyAddr();
	}
};

// CenterServer to LogicManager, 返回修改地址的结果 [2016-8-18 willing]
struct LMsgCE2LMGModifyAddrRet : public LMsg
{
	Lint nUid;
	Lint nErrorCode;

	LMsgCE2LMGModifyAddrRet() : LMsg(MSG_CE_2_LMG_MODIFY_ADDR_RET)
	{
		nUid = 0;
		nErrorCode = 0;
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(nUid);
		buff.Read(nErrorCode);

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(nUid);
		buff.Write(nErrorCode);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCE2LMGModifyAddrRet();
	}
};

// logicManager to CenterServer,删除地址 [2016-8-18 willing]
struct LMsgLMG2CERmvAddr : public LMsg
{
	Lint		nUid;				// 玩家ID [2016-8-17 willing]
	Lstring		strUnioid;
	Lint		nAddrID;			// 唯一ID [2016-8-18 willing]

	LMsgLMG2CERmvAddr() : LMsg(MSG_LMG_2_CE_RMV_ADDR)
	{
		nUid = 0;
		strUnioid = "";
		nAddrID = 0;
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(nUid);
		buff.Read(strUnioid);
		buff.Read(nAddrID);

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(nUid);
		buff.Write(strUnioid);
		buff.Write(nAddrID);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2CERmvAddr();
	}
};

// CenterServer to LogicManager, 删除地址的结果 [2016-8-18 willing]
struct LMsgCE2LMGRmvAddrRet : public LMsg
{
	Lint nUid;
	Lint nErrorCode;

	LMsgCE2LMGRmvAddrRet() : LMsg(MSG_CE_2_LMG_RMV_ADDR_RET)
	{
		nUid = 0;
		nErrorCode = EAAR_SUCCESS;
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(nUid);
		buff.Read(nErrorCode);

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(nUid);
		buff.Write(nErrorCode);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgCE2LMGRmvAddrRet();
	}
};


//比赛场用户数据
typedef struct SportUserInfoData
{
	Lint m_userId;          // 用户id
	Lstring	m_nike;			// 账户名 
	Lint m_sex;				// 性别 
	Lstring m_headImageUrl;	// 头像连接
	Lint m_sportId;			//比赛场id
	Lint m_rank;			//预留排名等级
	Lint m_join;			//参赛次数
	Lint m_maxRank;			//最好的名次
	Lint m_super;			//冠军次数
	Lint m_final;			//决赛次数
	Lint m_reward;			//获得奖励次数
	Lint m_totalGift;		//总礼券数 
	Lint m_totalCard;		//总房卡数
	Lint m_totalReal;		//总实物数
	Lint m_inNum;			//加入比赛次数
	Lint m_winNum;			//胜利次数
	Lint m_maxScore;		//获得的最大积分
	Lint m_joinTimesByDay;  //当天参与次数

	SportUserInfoData()
	{
		m_userId = 0;
		m_sex = 0;
		m_sportId = 0;
		m_rank = 999;
		m_join = 0;
		m_maxRank = 999;
		m_super = 0;
		m_final = 0;
		m_reward = 0;
		m_totalGift = 0;
		m_totalCard = 0;
		m_totalReal = 0;
		m_inNum = 0;
		m_winNum = 0;
		m_maxScore = 0;
		m_joinTimesByDay = 0;
	};

	virtual ~SportUserInfoData()
	{

	};
}SportUserInfoData;

typedef struct InviterUserInfoData
{
	Lint InviteeCnt;
	Lint Inviter;

	InviterUserInfoData()
	{
		Inviter = 0;
		InviteeCnt = 0;
	};

	virtual ~InviterUserInfoData()
	{
	};
}InviterUserInfoData;
//请求所有比赛场用户数据 
struct LMsgLMG2LDBAllSportUserInfoData : public LMsg
{
	LMsgLMG2LDBAllSportUserInfoData():LMsg(MSG_LMG_2_LDB_REQ_ALL_SPORT_USER_INFO_DATA)
	{
		
	}

	virtual bool Read(LBuff& buff)
	{	
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LDBAllSportUserInfoData();
	}
};


// LogicDB 向 LogicManager 返回 新创建的 比赛记录 信息 [2016-8-16 willing]
struct LMsgLDB2LMGAllSportUserInfoData : public LMsg
{
	Lint m_count;
	std::vector<SportUserInfoData>	m_userSportVec;
	LMsgLDB2LMGAllSportUserInfoData() : LMsg(MSG_LDB_2_LMG_REQ_ALL_SPORT_USER_INFO_DATA)
	{
		m_userSportVec.clear();
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_count);
		for(Lint i = 0 ; i < m_count; ++i)
		{
			SportUserInfoData info;
			buff.Read(info.m_userId);
			buff.Read(info.m_nike);
			buff.Read(info.m_sex);
			buff.Read(info.m_headImageUrl);
			buff.Read(info.m_sportId);
			buff.Read(info.m_rank);
			buff.Read(info.m_join);
			buff.Read(info.m_maxRank);
			buff.Read(info.m_super);
			buff.Read(info.m_final);
			buff.Read(info.m_reward);
			buff.Read(info.m_totalGift);
			buff.Read(info.m_totalCard);
			buff.Read(info.m_totalReal);
			buff.Read(info.m_inNum);
			buff.Read(info.m_winNum);
			buff.Read(info.m_maxScore);
			buff.Read(info.m_joinTimesByDay);
			m_userSportVec.push_back(info);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		m_count = m_userSportVec.size();
		buff.Write(m_count);
		for(Lint i = 0 ; i < m_count; ++i)
		{	
			SportUserInfoData& info = m_userSportVec[i];
			buff.Write(info.m_userId);
			buff.Write(info.m_nike);
			buff.Write(info.m_sex);
			buff.Write(info.m_headImageUrl);
			buff.Write(info.m_sportId);
			buff.Write(info.m_rank);
			buff.Write(info.m_join);
			buff.Write(info.m_maxRank);
			buff.Write(info.m_super);
			buff.Write(info.m_final);
			buff.Write(info.m_reward);
			buff.Write(info.m_totalGift);
			buff.Write(info.m_totalCard);
			buff.Write(info.m_totalReal);
			buff.Write(info.m_inNum);
			buff.Write(info.m_winNum);
			buff.Write(info.m_maxScore);
			buff.Write(info.m_joinTimesByDay);
		}
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLDB2LMGAllSportUserInfoData();
	}
};


// 插入一条玩家统计数据
struct LMsgLMG2LDBInsertSportUserInfo : public LMsg
{
	SportUserInfoData	m_userSportData;
	LMsgLMG2LDBInsertSportUserInfo() : LMsg(MSG_LMG_2_LDB_REQ_INSERT_SPORT_USER_INFO)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userSportData.m_userId);
		buff.Read(m_userSportData.m_nike);
		buff.Read(m_userSportData.m_sex);
		buff.Read(m_userSportData.m_headImageUrl);
		buff.Read(m_userSportData.m_sportId);
		buff.Read(m_userSportData.m_rank);
		buff.Read(m_userSportData.m_join);
		buff.Read(m_userSportData.m_maxRank);
		buff.Read(m_userSportData.m_super);
		buff.Read(m_userSportData.m_final);
		buff.Read(m_userSportData.m_reward);
		buff.Read(m_userSportData.m_totalGift);
		buff.Read(m_userSportData.m_totalCard);
		buff.Read(m_userSportData.m_totalReal);
		buff.Read(m_userSportData.m_inNum);
		buff.Read(m_userSportData.m_winNum);
		buff.Read(m_userSportData.m_maxScore);
		buff.Read(m_userSportData.m_joinTimesByDay);
		
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userSportData.m_userId);
		buff.Write(m_userSportData.m_nike);
		buff.Write(m_userSportData.m_sex);
		buff.Write(m_userSportData.m_headImageUrl);
		buff.Write(m_userSportData.m_sportId);
		buff.Write(m_userSportData.m_rank);
		buff.Write(m_userSportData.m_join);
		buff.Write(m_userSportData.m_maxRank);
		buff.Write(m_userSportData.m_super);
		buff.Write(m_userSportData.m_final);
		buff.Write(m_userSportData.m_reward);
		buff.Write(m_userSportData.m_totalGift);
		buff.Write(m_userSportData.m_totalCard);
		buff.Write(m_userSportData.m_totalReal);
		buff.Write(m_userSportData.m_inNum);
		buff.Write(m_userSportData.m_winNum);
		buff.Write(m_userSportData.m_maxScore);
		buff.Write(m_userSportData.m_joinTimesByDay);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LDBInsertSportUserInfo();
	}
};

//保存统计数据
struct LMsgLMG2LDBUpdateSportUserInfo : public LMsg
{
	Lint m_userId;
	Lint m_sportId;
	Lint m_type;
	Lstring m_value;

	LMsgLMG2LDBUpdateSportUserInfo() : LMsg(MSG_LMG_2_LDB_REQ_UPDATA_SPORT_USER_INFO)
	{
		
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_sportId);
		buff.Read(m_type);
		buff.Read(m_value);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_sportId);
		buff.Write(m_type);
		buff.Write(m_value);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LDBUpdateSportUserInfo();
	}
};

// LogicManager 向logicdb 插入 报名信息
struct LMsgLMG2LDBInsertSportSignInfo : public LMsg
{
	Lint	m_userId;
	Lstring m_nike;
	Lint	m_sportId;
	Lint	m_randId;
	Lint	m_SignTime;
	Lstring m_custom;

	LMsgLMG2LDBInsertSportSignInfo() : LMsg(MSG_LMG_2_LDB_REQ_INSERT_SPORT_SIGN_INFO)
	{
		 m_userId =0;
		 m_sportId =0;
		 m_randId =0;
		 m_SignTime = 0;
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_nike);
		buff.Read(m_sportId);
		buff.Read(m_randId);
		buff.Read(m_SignTime);
		buff.Read(m_custom);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_nike);
		buff.Write(m_sportId);
		buff.Write(m_randId);
		buff.Write(m_SignTime);
		buff.Write(m_custom);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LDBInsertSportSignInfo();
	}
};

// LogicManager 向logicdb 请求 删除报名信息
struct LMsgLMG2LDBDeleteSportSignInfo : public LMsg
{
	Lint	m_userId;
	Lint	m_sportId;
	Lint	m_randId;

	LMsgLMG2LDBDeleteSportSignInfo() : LMsg(MSG_LMG_2_LDB_REQ_DELETE_SPORT_SIGN_INFO)
	{
		m_userId = 0;
		m_sportId = 0;
		m_randId = 0;
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_sportId);
		buff.Read(m_randId);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_sportId);
		buff.Write(m_randId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LDBDeleteSportSignInfo();
	}
};

//请求 解散房间
//MSG_LMG_2_CE_SPORT_RESET_DESK = 6422

struct LMsgLMG2CESportResetDesk : public LMsg
{
	Lint m_uDeskid;

	LMsgLMG2CESportResetDesk() : LMsg(MSG_LMG_2_CE_SPORT_RESET_DESK)
	{
		m_uDeskid = 0;
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_uDeskid);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_uDeskid);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2CESportResetDesk();
	}
};

struct LMsgLmgr2LdbReqSelectInviterInfo : public LMsg
{
	Lint m_userId;
	Lint m_inviterId;
	Lint m_startDate;
	Lint m_endDate;
	
	LMsgLmgr2LdbReqSelectInviterInfo() : LMsg(MSG_LMG_2_LDB_REQ_SELECT_INVITER_INFO)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_inviterId);
		buff.Read(m_startDate);
		buff.Read(m_endDate);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_inviterId);
		buff.Write(m_startDate);
		buff.Write(m_endDate);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLmgr2LdbReqSelectInviterInfo();
	}
};


struct LMsgLdb2LmgrRspSelectInviterInfo : public LMsg
{
	Lint m_userId;
	Lint m_inviterId;
	Lint m_count;
	Lint m_errno;
	
	LMsgLdb2LmgrRspSelectInviterInfo() : LMsg(MSG_LDB_2_LMG_RSP_SELECT_INVITER_INFO)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_inviterId);
		buff.Read(m_count);
		buff.Read(m_errno);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_inviterId);
		buff.Write(m_count);
		buff.Write(m_errno);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLdb2LmgrRspSelectInviterInfo();
	}
};

//比赛场项目统计
struct SportItemStat
{
	Lint SportId; //比赛场配置id
	Lint QueueId; //队列id
	Lint RandId; //随机id
	Lint SignTime; //报名时间
	Lint StartTime; //比赛开始时间
	Lint SignStartDiff; //报名到开赛的时间差
	Lint MatchTime; //比赛消耗时间
	Lint SignNum; //报名人数
	Lint MatchNum; //比赛人数
	Lint RewardUserNum; //奖励人数
	Lint CustomNum[5] = {0}; //消耗数值1-5
	Lint RewardNum[5] = {0}; //奖励数值1-5

	SportItemStat():SportId(0), QueueId(0)
	{
		reset();
	}

	void reset()
	{
		RandId = 0;
		SignTime = 0;
		StartTime = 0;
		SignStartDiff = 0; 
		MatchTime = 0; 
		SignNum = 0; 
		MatchNum = 0;
		RewardUserNum = 0; 
		memset(CustomNum, 0, sizeof(CustomNum));
		memset(RewardNum, 0, sizeof(CustomNum));
	}
};

// LogicManager 向logicdb 插入 比赛项目记录
// MSG_LMG_2_LDB_REQ_INSERT_SPORT_ITEM_STAT = 15066,     // logicmanager 保持比赛项目记录信息
struct LMsgLMG2LDBInsertSportItemStat : public LMsg
{
	SportItemStat m_data;
	LMsgLMG2LDBInsertSportItemStat() : LMsg(MSG_LMG_2_LDB_REQ_INSERT_SPORT_ITEM_STAT)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_data.SportId);
		buff.Read(m_data.QueueId);
		buff.Read(m_data.RandId);
		buff.Read(m_data.SignTime);
		buff.Read(m_data.StartTime);
		buff.Read(m_data.SignStartDiff);
		buff.Read(m_data.MatchTime);
		buff.Read(m_data.SignNum);
		buff.Read(m_data.MatchNum);
		buff.Read(m_data.RewardUserNum);
		for (size_t i = 0; i < 5; ++i)
		{
			buff.Read(m_data.CustomNum[i]);
		}
		for (size_t i = 0; i < 5; ++i)
		{
			buff.Read(m_data.RewardNum[i]);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_data.SportId);
		buff.Write(m_data.QueueId);
		buff.Write(m_data.RandId);
		buff.Write(m_data.SignTime);
		buff.Write(m_data.StartTime);
		buff.Write(m_data.SignStartDiff);
		buff.Write(m_data.MatchTime);
		buff.Write(m_data.SignNum);
		buff.Write(m_data.MatchNum);
		buff.Write(m_data.RewardUserNum);
		for (size_t i = 0; i < 5; ++i)
		{
			buff.Write(m_data.CustomNum[i]);
		}
		for (size_t i = 0; i < 5; ++i)
		{
			buff.Write(m_data.RewardNum[i]);
		}
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LDBInsertSportItemStat();
	}
};

//每日统计数据
struct SportDailyStat
{
	Lint SportId;
	Lint StatTime;
	Lint UpdTime;
	Lint ReptSign;
	Lint Sign;
	Lint ReptJoin;
	Lint Join;
	Lint LoopNum;
	Lint Custom1;
	Lint Custom2;
	Lint Custom3;
	Lint Custom4;
	Lint Custom5;

	SportDailyStat():SportId(0),StatTime(0),UpdTime(0),ReptSign(0),Sign(0),ReptJoin(0),Join(0)
		,LoopNum(0),Custom1(0), Custom2(0), Custom3(0), Custom4(0), Custom5(0)
	{

	}
};


//MSG_LMG_2_LDB_REQ_INSERT_SPORT_DAILY_STAT = 15067,     // 插入每日比赛项统计
struct LMsgLMG2LDBInsertSportDailyStat : public LMsg
{
	Lint m_count;
	std::vector<SportDailyStat> m_datas;

	LMsgLMG2LDBInsertSportDailyStat() : LMsg(MSG_LMG_2_LDB_REQ_INSERT_SPORT_DAILY_STAT), m_count(0)
	{
		
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_count);
		for (size_t i = 0; i < m_count; ++i)
		{
			SportDailyStat info;
			buff.Read(info.SportId);
			buff.Read(info.StatTime);
			buff.Read(info.UpdTime);
			buff.Read(info.ReptSign);
			buff.Read(info.Sign);
			buff.Read(info.ReptJoin);
			buff.Read(info.Join);
			buff.Read(info.LoopNum);
			buff.Read(info.Custom1);
			buff.Read(info.Custom2);
			buff.Read(info.Custom3);
			buff.Read(info.Custom4);
			buff.Read(info.Custom5);
			m_datas.push_back(info);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		m_count = m_datas.size();
		buff.Write(m_count);
		for (Lint i = 0; i < m_count; ++i)
		{
			SportDailyStat& info = m_datas[i];
			buff.Write(info.SportId);
			buff.Write(info.StatTime);
			buff.Write(info.UpdTime);
			buff.Write(info.ReptSign);
			buff.Write(info.Sign);
			buff.Write(info.ReptJoin);
			buff.Write(info.Join);
			buff.Write(info.LoopNum);
			buff.Write(info.Custom1);
			buff.Write(info.Custom2);
			buff.Write(info.Custom3);
			buff.Write(info.Custom4);
			buff.Write(info.Custom5);
		}
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LDBInsertSportDailyStat();
	}
};


//MSG_LMG_2_LDB_REQ_UPDATE_SPORT_DAILY_STAT = 15068,     //更新每日比赛项统计
struct LMsgLMG2LDBUpdateSportDailyStat : public LMsg
{
	Lint m_count;
	std::vector<SportDailyStat> m_datas;

	LMsgLMG2LDBUpdateSportDailyStat() : LMsg(MSG_LMG_2_LDB_REQ_UPDATE_SPORT_DAILY_STAT), m_count(0)
	{

	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_count);
		for (size_t i = 0; i < m_count; ++i)
		{
			SportDailyStat info;
			buff.Read(info.SportId);
			buff.Read(info.StatTime);
			buff.Read(info.UpdTime);
			buff.Read(info.ReptSign);
			buff.Read(info.Sign);
			buff.Read(info.ReptJoin);
			buff.Read(info.Join);
			buff.Read(info.LoopNum);
			buff.Read(info.Custom1);
			buff.Read(info.Custom2);
			buff.Read(info.Custom3);
			buff.Read(info.Custom4);
			buff.Read(info.Custom5);
			m_datas.push_back(info);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		m_count = m_datas.size();
		buff.Write(m_count);
		for (Lint i = 0; i < m_count; ++i)
		{
			SportDailyStat& info = m_datas[i];
			buff.Write(info.SportId);
			buff.Write(info.StatTime);
			buff.Write(info.UpdTime);
			buff.Write(info.ReptSign);
			buff.Write(info.Sign);
			buff.Write(info.ReptJoin);
			buff.Write(info.Join);
			buff.Write(info.LoopNum);
			buff.Write(info.Custom1);
			buff.Write(info.Custom2);
			buff.Write(info.Custom3);
			buff.Write(info.Custom4);
			buff.Write(info.Custom5);
		}
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LDBUpdateSportDailyStat();
	}
};

////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////match 与其他 服务器协议/////////////////////////////////////////////////////////
struct LMsgM2LMGLogin :public LMsg
{
	Lint		m_id;
	Lstring		m_key;
	Lstring		m_ip;
	Lshort		m_port;
	Lint		m_firstLogin;

	LMsgM2LMGLogin() :LMsg(MSG_M_2_LMG_LOGIN), m_id(0), m_port(0), m_firstLogin(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_id);
		buff.Read(m_key);
		buff.Read(m_ip);
		buff.Read(m_port);
		buff.Read(m_firstLogin);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_id);
		buff.Write(m_key);
		buff.Write(m_ip);
		buff.Write(m_port);
		buff.Write(m_firstLogin);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgM2LMGLogin();
	}
};

struct LMsgM2CeLogin :public LMsg
{
	Lint	m_ID;//类型
	Lstring m_key;
	Lstring m_ServerName;
	Lint	m_needUserIdInfo;

	LMsgM2CeLogin() :LMsg(MSG_M_2_CE_LOGIN), m_ID(0), m_needUserIdInfo(1)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_ID);
		buff.Read(m_key);
		buff.Read(m_ServerName);
		buff.Read(m_needUserIdInfo);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_ID);
		buff.Write(m_key);
		buff.Write(m_ServerName);
		buff.Write(m_needUserIdInfo);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgM2CeLogin();
	}
};

struct LMsgM2LdbLogin : public LMsg
{
	Lstring			m_key;
	Lint			m_serverID;
	LMsgM2LdbLogin() :LMsg(MSG_M_2_LDB_LOGIN), m_serverID(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_key);
		buff.Read(m_serverID);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_key);
		buff.Write(m_serverID);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgM2LdbLogin();
	}
};

struct LMsgG2MLogin :public LMsg
{
	Lint		m_id;
	Lstring		m_key;
	Lstring		m_ip;
	Lshort		m_port;

	LMsgG2MLogin() :LMsg(MSG_G_2_M_LOGIN), m_id(0), m_port(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_id);
		buff.Read(m_key);
		buff.Read(m_ip);
		buff.Read(m_port);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_id);
		buff.Write(m_key);
		buff.Write(m_ip);
		buff.Write(m_port);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgG2MLogin();
	}
};


struct LMsgL2MLogin :public LMsg
{
	Lint		m_id;
	Lstring		m_key;
	Lstring		m_ip;
	Lshort		m_port;
	Lint		m_firstLogin;

	LMsgL2MLogin() :LMsg(MSG_L_2_M_LOGIN), m_id(0), m_port(0), m_firstLogin(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_id);
		buff.Read(m_key);
		buff.Read(m_ip);
		buff.Read(m_port);
		buff.Read(m_firstLogin);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_id);
		buff.Write(m_key);
		buff.Write(m_ip);
		buff.Write(m_port);
		buff.Write(m_firstLogin);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgL2MLogin();
	}
};

struct MatchInfo
{
	Lint			m_id;
	Lstring			m_ip;
	Lshort			m_port;
	LSocketPtr		m_sp;
	TCPClientPtr	m_client;
	Lint			m_flag;	//0,normal; -1,failover
	MatchInfo() :m_id(0), m_port(0) {}
};


struct LMsgLMG2GateMatchInfo :public LMsg
{
	Lint		m_ID;
	MatchInfo	m_match;

	LMsgLMG2GateMatchInfo() :LMsg(MSG_LMG_2_G_SYNC_MATCH), m_ID(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_ID);
		buff.Read(m_match.m_id);
		buff.Read(m_match.m_ip);
		buff.Read(m_match.m_port);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_ID);
		buff.Write(m_match.m_id);
		buff.Write(m_match.m_ip);
		buff.Write(m_match.m_port);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2GateMatchInfo();
	}
};

struct LMsgLMG2LogicMatchInfo :public LMsg
{
	Lint		m_ID;
	MatchInfo	m_match;

	LMsgLMG2LogicMatchInfo() :LMsg(MSG_LMG_2_L_SYNC_MATCH), m_ID(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_ID);
		buff.Read(m_match.m_id);
		buff.Read(m_match.m_ip);
		buff.Read(m_match.m_port);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_ID);
		buff.Write(m_match.m_id);
		buff.Write(m_match.m_ip);
		buff.Write(m_match.m_port);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2LogicMatchInfo();
	}
};

struct LMsgLMG2MUserLogin :public LMsg
{
	Lint		m_seed;
	LUser		user;

	LMsgLMG2MUserLogin() :LMsg(MSG_LMG_2_M_USER_LOGIN), m_seed(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_seed);
		user.Read(buff);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_seed);
		user.Write(buff);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2MUserLogin();
	}
};

struct LMsgLMG2MUserReLogin :public LMsg
{
	Lint	m_seed;
	Lint	m_userid;
	Lint	m_gateId;
	Luuid	m_geteUserId;
	Lstring	m_ip;
	Lstring	m_md5;

	LMsgLMG2MUserReLogin() :LMsg(MSG_LMG_2_M_USER_RELOGIN), m_seed(0), m_userid(0), m_gateId(0), m_geteUserId(Luuid_NULL)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_seed);
		buff.Read(m_userid);
		buff.Read(m_gateId);
		buff.Read(m_geteUserId);
		buff.Read(m_ip);
		buff.Read(m_md5);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_seed);
		buff.Write(m_userid);
		buff.Write(m_gateId);
		buff.Write(m_geteUserId);
		buff.Write(m_ip);
		buff.Write(m_md5);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2MUserReLogin();
	}
};


struct LMsgM2GFilterProto :public LMsg
{
	std::vector<Lint>	m_pripro; //私有的协议
	std::vector<Lint>	m_pubpro;//共有协议

	Lint                m_priproSize;
	Lint                m_pubproSize;

	LMsgM2GFilterProto() :LMsg(MSG_M_2_G_FITER_PROTO), m_priproSize(0), m_pubproSize(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_priproSize);
		buff.Read(m_pubproSize);
		m_pripro.resize(m_priproSize);
		m_pubpro.resize(m_pubproSize);
		for (size_t i = 0; i < m_priproSize; ++i)
		{
			buff.Read(m_pripro[i]);
		}

		for (size_t i = 0; i < m_pubproSize; ++i)
		{
			buff.Read(m_pubpro[i]);
		}

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_priproSize);
		buff.Write(m_pubproSize);
		for (size_t i = 0; i < m_priproSize; ++i)
		{
			buff.Write(m_pripro[i]);
		}

		for (size_t i = 0; i < m_pubproSize; ++i)
		{
			buff.Write(m_pubpro[i]);
		}
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgM2GFilterProto();
	}
};

struct SignCustomInfo
{
	Lint m_type;
	Lint m_num;
	SignCustomInfo() :m_type(0), m_num(0)
	{
	}
};

//MSG_M_2_LMG_SYN_SIGN_PLAYER_OPT = 13020,	   //请求报名和取消报名操作
struct LMsgM2LMGSynSignPlayerOpt : public LMsg
{
	Lint			m_userId;
	Lint			m_sportId;
	Lint            m_queueId;
	Lint            m_randId;
	Lint			m_opt; //0表示加入比赛，1表示退出比赛
	Lint            m_customs;
	std::vector<SignCustomInfo> m_custom;

	LMsgM2LMGSynSignPlayerOpt() :LMsg(MSG_M_2_LMG_SYN_SIGN_PLAYER_OPT), m_userId(0), m_sportId(0), m_opt(0), m_customs(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_sportId);
		buff.Read(m_queueId);
		buff.Read(m_randId);
		buff.Read(m_opt);
		buff.Read(m_customs);

		for (Lint i = 0; i < m_customs; ++i)
		{
			SignCustomInfo info;
			buff.Read(info.m_type);
			buff.Read(info.m_num);
			m_custom.push_back(info);
		}

		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_sportId);
		buff.Write(m_queueId);
		buff.Write(m_randId);
		buff.Write(m_opt);

		m_customs = m_custom.size();
		buff.Write(m_customs);
		for (Lint i = 0; i < m_customs; ++i)
		{
			buff.Write(m_custom[i].m_type);
			buff.Write(m_custom[i].m_num);
		}
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgM2LMGSynSignPlayerOpt();
	}
};

//MSG_LMG_2_M_SYN_ACK_SIGN_PLAYER_OPT = 13021,   //请求报名和取消报名操作回复
struct LMsgLMG2MSynAckSignPlayerOpt : public LMsg
{
	Lint			m_userId;
	Lint			m_sportId;
	Lint            m_queueId;
	Lint            m_randId;
	Lint			m_opt; //0表示加入比赛，1表示退出比赛
	Lint            m_optRet; //0表示可以操作，其他表示异常
	Lint            m_customs;
	std::vector<SignCustomInfo> m_custom;
	LMsgLMG2MSynAckSignPlayerOpt() :LMsg(MSG_LMG_2_M_SYN_ACK_SIGN_PLAYER_OPT), m_userId(0), m_sportId(0),
		m_queueId(0), m_randId(0), m_opt(0), m_optRet(0), m_customs(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_sportId);
		buff.Read(m_queueId);
		buff.Read(m_randId);
		buff.Read(m_opt);
		buff.Read(m_optRet);
		buff.Read(m_customs);

		for (Lint i = 0; i < m_customs; ++i)
		{
			SignCustomInfo info;
			buff.Read(info.m_type);
			buff.Read(info.m_num);
			m_custom.push_back(info);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_sportId);
		buff.Write(m_queueId);
		buff.Write(m_randId);
		buff.Write(m_opt);
		buff.Write(m_optRet);
		m_customs = m_custom.size();
		buff.Write(m_customs);
		for (Lint i = 0; i < m_customs; ++i)
		{
			buff.Write(m_custom[i].m_type);
			buff.Write(m_custom[i].m_num);
		}
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2MSynAckSignPlayerOpt();
	}
};

//MSG_M_2_LMG_ACK_SIGN_PLAYER_OPT = 13022,	   //请求报名和取消报名操作确认
struct LMsgLMG2MAckSignPlayerOpt : public LMsg
{
	Lint			m_userId;
	Lint			m_sportId;
	Lint            m_queueId;
	Lint            m_randId;
	Lint			m_opt; //0表示加入比赛，1表示退出比赛
	Lint            m_optRet; //0表示可以操作，其他表示异常
	Lint            m_customs;
	std::vector<SignCustomInfo> m_custom;
	LMsgLMG2MAckSignPlayerOpt() :LMsg(MSG_M_2_LMG_ACK_SIGN_PLAYER_OPT), m_userId(0), m_sportId(0),
		m_queueId(0), m_randId(0), m_opt(0), m_optRet(0), m_customs(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_sportId);
		buff.Read(m_queueId);
		buff.Read(m_randId);
		buff.Read(m_opt);
		buff.Read(m_optRet);
		buff.Read(m_customs);

		for (Lint i = 0; i < m_customs; ++i)
		{
			SignCustomInfo info;
			buff.Read(info.m_type);
			buff.Read(info.m_num);
			m_custom.push_back(info);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_sportId);
		buff.Write(m_queueId);
		buff.Write(m_randId);
		buff.Write(m_opt);
		buff.Write(m_optRet);
		m_customs = m_custom.size();
		buff.Write(m_customs);
		for (Lint i = 0; i < m_customs; ++i)
		{
			buff.Write(m_custom[i].m_type);
			buff.Write(m_custom[i].m_num);
		}
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2MAckSignPlayerOpt();
	}
};

//MSG_M_2_LMG_PLAYER_IN_OUT_ITEM = 13023,   //请求报名和取消报名操作回复
struct LMsgM2LMGPlayersInOutItem : public LMsg
{
	Lint			m_sportId;
	Lint            m_queueId;
	Lint            m_randId;

	Lint            m_inNum;
	Lint            m_outNum;
	std::vector<Lint> m_ins;
	std::vector<Lint> m_outs;

	LMsgM2LMGPlayersInOutItem() :LMsg(MSG_M_2_LMG_PLAYER_IN_OUT_ITEM), m_sportId(0),
		m_queueId(0), m_randId(0), m_inNum(0), m_outNum(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_sportId);
		buff.Read(m_queueId);
		buff.Read(m_randId);
		buff.Read(m_inNum);
		buff.Read(m_outNum);

		m_ins.resize(m_inNum);
		for (Lint i = 0; i < m_inNum; ++i)
		{
			SignCustomInfo info;
			buff.Read(m_ins[i]);
		}

		m_outs.resize(m_outNum);
		for (Lint i = 0; i < m_outNum; ++i)
		{
			SignCustomInfo info;
			buff.Read(m_outs[i]);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_sportId);
		buff.Write(m_queueId);
		buff.Write(m_randId);

		m_inNum = m_ins.size();
		buff.Write(m_inNum);
		m_outNum = m_outs.size();
		buff.Write(m_outNum);

		for (Lint i = 0; i < m_inNum; ++i)
		{
			buff.Write(m_ins[i]);
		}

		for (Lint i = 0; i < m_outNum; ++i)
		{
			buff.Write(m_outs[i]);
		}
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgM2LMGPlayersInOutItem();
	}
};

//MSG_M_2_LMG_PLAYER_REWARD = 13024,   //玩家的奖励
struct LMsgM2LMGPlayerReward : public LMsg
{
	Lint			m_userId;
	Lint            m_type;
	Lint            m_value;
	Lint            m_reason;
	LMsgM2LMGPlayerReward() :LMsg(MSG_M_2_LMG_PLAYER_REWARD), m_userId(0),
		m_type(0), m_value(0), m_reason(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_type);
		buff.Read(m_value);
		buff.Read(m_reason);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_type);
		buff.Write(m_value);
		buff.Write(m_reason);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgM2LMGPlayerReward();
	}
};

//MSG_M_2_LMG_REMOVE_SIGN_PLAYER = 13025,		   //删除报名的玩家
struct LMsgM2LMGRemoveSignPlayer : public LMsg
{
	Lint			m_sportId;
	Lint            m_queueId;
	Lint            m_randId;
	Lint            m_userId;

	LMsgM2LMGRemoveSignPlayer() :LMsg(MSG_M_2_LMG_REMOVE_SIGN_PLAYER), m_sportId(0),
		m_queueId(0), m_randId(0), m_userId(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_sportId);
		buff.Read(m_queueId);
		buff.Read(m_randId);
		buff.Read(m_userId);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_sportId);
		buff.Write(m_queueId);
		buff.Write(m_randId);
		buff.Write(m_userId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgM2LMGRemoveSignPlayer();
	}
};

//MSG_M_2_LMG_GET_DESK_IDS = 13026,		   //请求空闲桌子数
struct LMsgM2LMGGetDeskIds : public LMsg
{
	Lint			m_matchid;
	Lint            m_count;

	LMsgM2LMGGetDeskIds() :LMsg(MSG_M_2_LMG_GET_DESK_IDS), m_matchid(0), m_count(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_matchid);
		buff.Read(m_count);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_matchid);
		buff.Write(m_count);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgM2LMGGetDeskIds();
	}
};

//MSG_LMG_2_M_GET_DESK_IDS = 13027,		   //请求空闲桌子数回应
struct LMsgLMG2MGetDeskIds : public LMsg
{
	Lint			m_matchid;
	Lint            m_count;
	std::vector<Lint> m_data;

	LMsgLMG2MGetDeskIds() :LMsg(MSG_LMG_2_M_GET_DESK_IDS), m_matchid(0),m_count(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_matchid);
		buff.Read(m_count);

		m_data.resize(m_count);
		for (Lint i = 0; i < m_count; ++i)
		{
			buff.Read(m_data[i]);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_matchid);
		buff.Write(m_count);

		for (Lint i = 0; i < m_count; ++i)
		{
			buff.Write(m_data[i]);
		}

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2MGetDeskIds();
	}
};

//玩家登陆的基本信息
struct SynUserLoginInfo
{
	Lint        m_userId;
	Lint		m_gateId;
	Luuid		m_gateUserId;
	Lstring		m_ip;
	LUser		m_user;

	SynUserLoginInfo() :m_userId(0), m_gateId(0)
	{
	}
};


//MSG_LMG_2_M_SYN_USER_LOGIN_INFO = 13028,		   //登陆的玩家数据同步
struct LMsgLMG2MSynUserLoginInfo : public LMsg
{
	Lint			m_matchid;
	Lint            m_count;
	std::vector<SynUserLoginInfo> m_data;

	LMsgLMG2MSynUserLoginInfo() :LMsg(MSG_LMG_2_M_SYN_USER_LOGIN_INFO), m_matchid(0), m_count(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_matchid);
		buff.Read(m_count);

		m_data.resize(m_count);
		for (Lint i = 0; i < m_count; ++i)
		{
			buff.Read(m_data[i].m_userId);
			buff.Read(m_data[i].m_gateId);
			buff.Read(m_data[i].m_gateUserId);
			buff.Read(m_data[i].m_ip);
			m_data[i].m_user.Read(buff);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_matchid);
		buff.Write(m_count);

		m_count = m_data.size();
		for (Lint i = 0; i < m_count; ++i)
		{
			buff.Write(m_data[i].m_userId);
			buff.Write(m_data[i].m_gateId);
			buff.Write(m_data[i].m_gateUserId);
			buff.Write(m_data[i].m_ip);
			m_data[i].m_user.Write(buff);
		}

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2MSynUserLoginInfo();
	}
};

//MSG_LMG_2_M_SYN_LOGIC_IDS = 13029,		   //登陆的玩家数据同步
struct LMsgLMG2MSynLogicIDS : public LMsg
{
	Lint			m_matchid;
	Lint            m_count;
	std::vector <Lint> m_data;

	LMsgLMG2MSynLogicIDS() :LMsg(MSG_LMG_2_M_SYN_LOGIC_IDS), m_matchid(0), m_count(0)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_matchid);
		buff.Read(m_count);

		m_data.resize(m_count);
		for (Lint i = 0; i < m_count; ++i)
		{
			buff.Read(m_data[i]);
		}
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_matchid);
		buff.Write(m_count);

		m_count = m_data.size();
		for (Lint i = 0; i < m_count; ++i)
		{
			buff.Write(m_data[i]);
		}

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLMG2MSynLogicIDS();
	}
};

//MSG_M_2_LDB_UPDATE_DAILY_JOIN_TIMES
struct LMsgM2LDBUpdateDailyJoinTimes : public LMsg
{
	LMsgM2LDBUpdateDailyJoinTimes() :LMsg(MSG_M_2_LDB_UPDATE_DAILY_JOIN_TIMES)
	{
	}	

	virtual bool Read(LBuff& buff)
	{
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgM2LDBUpdateDailyJoinTimes();
	}
};
///////////////////////////////////////////////////////////////////////

struct LMsgLmgr2LdbReqUpdateBindTab : public LMsg
{
	Lint m_userId;
	Lint m_inviterId;

	LMsgLmgr2LdbReqUpdateBindTab() : LMsg(MSG_LMG_2_LDB_REQ_UPDATE_BIND_TABLE) {
		
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_inviterId);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_inviterId);
		return true;
	}
	
	virtual LMsg* Clone()
	{
		return new LMsgLmgr2LdbReqUpdateBindTab();
	}
};

struct LMsgLdb2LmgrRspUpdateBindTab : public LMsg
{
	Lint m_userId;
	Lint m_inviterId;
	Lint m_errno;

	LMsgLdb2LmgrRspUpdateBindTab() : LMsg(MSG_LDB_2_LMG_RSP_UPDATE_BIND_TABLE)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_inviterId);
		buff.Read(m_errno);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_inviterId);
		buff.Write(m_errno);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLdb2LmgrRspUpdateBindTab();
	}
};

struct LMsgLmgr2LdbReqSelectRewardTab : public LMsg
{
	Lint m_userId;
	Lint m_inviterId;

	LMsgLmgr2LdbReqSelectRewardTab() : LMsg(MSG_LMG_2_LDB_REQ_SELECT_REWARD_TABLE) {

	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_inviterId);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_inviterId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLmgr2LdbReqSelectRewardTab();
	}
};

struct LMsgLdb2LmgrRspSelectRewardTab : public LMsg
{
	Lint m_userId;
	Lint m_inviterId;
	Lint m_cards;
	Lint m_errno;

	LMsgLdb2LmgrRspSelectRewardTab() : LMsg(MSG_LDB_2_LMG_RSP_SELECT_REWARD_TABLE)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_inviterId);
		buff.Read(m_cards);
		buff.Read(m_errno);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_inviterId);
		buff.Write(m_cards);
		buff.Write(m_errno);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLdb2LmgrRspSelectRewardTab();
	}
};


struct LMsgLmgr2LdbReqUpdateRewardTab : public LMsg
{
	Lint m_userId;
	Lint m_inviterId;
	Lint m_cards;

	LMsgLmgr2LdbReqUpdateRewardTab() : LMsg(MSG_LMG_2_LDB_REQ_UPDATE_REWARD_TABLE) {

	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_inviterId);
		buff.Read(m_cards);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_inviterId);
		buff.Write(m_cards);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLmgr2LdbReqUpdateRewardTab();
	}
};

struct LMsgLdb2LmgrRspUpdateRewardTab : public LMsg
{
	Lint m_userId;
	Lint m_inviterId;
	Lint m_errno;

	LMsgLdb2LmgrRspUpdateRewardTab() : LMsg(MSG_LDB_2_LMG_RSP_UPDATE_REWARD_TABLE)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_inviterId);
		buff.Read(m_errno);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_inviterId);
		buff.Write(m_errno);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLdb2LmgrRspUpdateRewardTab();
	}
};

struct LMsgLmgr2LdbReqInsertRewardTab : public LMsg
{
	Lint m_userId;
	Lint m_inviterId;
	Lint m_cards;

	LMsgLmgr2LdbReqInsertRewardTab() : LMsg(MSG_LMG_2_LDB_REQ_INSERT_REWARD_TABLE) {

	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_inviterId);
		buff.Read(m_cards);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_inviterId);
		buff.Write(m_cards);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLmgr2LdbReqInsertRewardTab();
	}
};

struct LMsgLdb2LmgrRspInsertRewardTab : public LMsg
{
	Lint m_userId;
	Lint m_inviterId;
	Lint m_errno;

	LMsgLdb2LmgrRspInsertRewardTab() : LMsg(MSG_LDB_2_LMG_RSP_INSERT_REWARD_TABLE)
	{
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_userId);
		buff.Read(m_inviterId);
		buff.Read(m_errno);
		return true;
	}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_userId);
		buff.Write(m_inviterId);
		buff.Write(m_errno);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgLdb2LmgrRspInsertRewardTab();
	}
};

#endif