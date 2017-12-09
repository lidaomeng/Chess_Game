#ifndef _L_MSG_H_
#define _L_MSG_H_

#include "LSocket.h"
#include "LSingleton.h"
#include "LTool.h"
#include "LLog.h"
#include "LVideo.h"
#include "defines.h"
#include "GameDefine.h"

struct LMsg;

class LMsgFactory : public LSingleton<LMsgFactory>
{
public:
	virtual bool Init();

	virtual bool Final();

	void RegestMsg(LMsg* pMsg);

	LMsg* CreateMsg(int msgId);

private:
	std::map<int,LMsg*> m_msgMap;
};


struct LMsg
{
	LMsg(int id);
	virtual~LMsg();

	LBuffPtr		GetSendBuff();
	void			WriteMsgId(LBuff& buff);
	void			ReadMsgId(LBuff& buff);

	virtual bool	Write(LBuff& buff);
	virtual bool	Write(msgpack::packer<msgpack::sbuffer>& pack);
	virtual bool	Read(LBuff& buff);
	virtual bool	Read(msgpack::object& obj);
	virtual LMsg*	Clone();
	virtual Lint	preAllocSendMemorySize();

	LBuffPtr			m_send;
	LSocketPtr			m_sp;
	Lint				m_msgId;
	bool				m_isMsgPack;
};

//客户端 服务器交互的消息
struct LMsgSC :public LMsg
{
	LMsgSC(int id) :LMsg(id)
	{
		m_isMsgPack = true;
	}
};
//玩家状态信息定义
enum LGUserMsgState
{
	LGU_STATE_IDLE,			//空闲，发到Center
	LGU_STATE_CENTER,		//玩家在大厅，发到Center
	LGU_STATE_DESK,			//玩家在桌子，发到Logic
};
//服务器端跟客户端通讯的消息号
enum LMSG_ID
{
	MSG_ERROR_MSG = 0,//错误消息

	MSG_C_2_S_MSG = 1,//客户端发给服务器
	MSG_S_2_C_MSG = 2,//服务器返回结果

	
	MSG_C_2_S_RE_LOGIN =	10, //客户端请求重连
	MSG_C_2_S_LOGIN =	11, //客户端请求登录
	MSG_S_2_C_LOGIN =	12, //服务器返回客户登录结果

	MSG_S_2_C_ITEM_INFO = 13,  //返回玩家物品信息
	MSG_S_2_C_HORSE_INFO = 14,  //跑马灯信息

	MSG_C_2_S_HEART = 15, //心跳包
	MSG_S_2_C_HEART = 16, //心跳包

	MSG_C_2_S_NOTICE = 17, //请求服务器通知
	MSG_S_2_C_NOTICE = 18, //服务器返回通知

	//vip场相关消息
	MSG_C_2_S_CREATE_ROOM = 20,//玩家请求创建房间
	MSG_S_2_C_CREATE_ROOM = 21,//玩家请求创建房间结果

	MSG_C_2_S_ADD_ROOM = 22,//玩家请求加入房间
	MSG_S_2_C_ADD_ROOM = 23,//玩家请求加入房间结果

	MSG_C_2_S_LEAVE_ROOM = 24,//玩家请求退出房间
	MSG_S_2_C_LEAVE_ROOM = 25,//玩家请求退出房间结果

	MSG_C_2_S_RESET_ROOM = 26,//申请解算房间
	MSG_S_2_C_RESET_ROOM = 27,// 服务器广播申请解算房间结果

	MSG_C_2_S_RESET_ROOM_SELECT = 28,//玩家执行申请操作
	
	MSG_S_2_C_INTO_DESK = 30,//服务器通知玩家进入桌子
	MSG_S_2_C_ADD_USER = 31,//桌子添加玩家
	MSG_S_2_C_DEL_USER = 32,//桌子删除玩家

	MSG_S_2_C_DESK_STATE = 35,//发送桌子状态

	MSG_C_2_S_READY = 36,//客户端玩家准备
	MSG_S_2_C_READY = 37,//服务器广播某个玩家准备

	MSG_S_2_C_USER_ONLINE_INFO = 40,//服务器广播玩家在线状态

	MSG_S_2_C_VIP_INFO = 41,//同步桌子信息

	MSG_S_2_C_START = 50,//服务器发送游戏开始消息
	MSG_S_2_C_GET_CARD = 51,//服务器发送玩家摸牌，准备出牌的消息
	
	MSG_C_2_S_PLAY_CARD = 52,//客户端请求出牌
	MSG_S_2_C_PLAY_CARD = 53,//服务器广播玩家出牌

	MSG_S_2_C_USER_THINK = 54,//服务器通知玩家思考

	MSG_C_2_S_USER_OPER = 55,//玩家操作结果
	MSG_S_2_C_USER_OPER = 56,//服务器广播玩家操作结果

	MSG_C_2_S_USER_SPEAK = 57,//玩家请求说话
	MSG_S_2_C_USER_SPEAK = 58,//服务器广播玩家说话

	MSG_S_2_C_GAME_OVER = 60,//服务器通知本场游戏结束

	MSG_C_2_S_USER_OUT_ROOM = 61,//玩家请求退出房间
	MSG_S_2_C_USER_OUT_ROOM = 62,//玩家退出房间结果


	MSG_S_2_C_START_HU = 65,//玩家起手胡
	MSG_C_2_S_START_HU_SELECT = 66,//玩家选择起手胡
	MSG_S_2_C_START_HU_SELECT = 67,//玩家选择起手胡结果
	
	MSG_S_2_C_GANG_RESULT = 68,//玩家杠牌结果
	MSG_S_2_C_GANG_THINK = 117,//玩家杠牌思考

	MSG_S_2_C_Piao_Select = 118,//请求玩家选择飘
	MSG_C_2_S_Piao_Select = 119,//玩家选择飘结果
	MSG_S_2_C_Piao_Count =143,//广播飘结果

	MSG_S_2_C_PLAY_DICE = 144,//广播玩家掷骰子 Add by lidm [2017-05-11] 
	MSG_C_2_S_PLAY_DICE = 145,//广播玩家掷骰子 Add by lidm [2017-05-16] 
	MSG_S_2_C_END_CARD_SELECT_TING = 74,//服务器广播海底牌选择 Add by lidm [2017-05-24] 

	MSG_S_2_C_END_CARD_SELECT = 69,//服务器广播海底牌选择
	MSG_C_2_S_END_SELECT = 70,//玩家选择结果
	MSG_S_2_C_END_GET = 71,//服务器广播玩家摸海底牌
	MSG_S_2_C_ZHA_BIRD = 72,//服务器广播扎鸟结果
	MSG_S_2_C_Wang_Ba = 73,//服务器广播王霸
	MSG_S_2_C_VIP_END = 80,//游戏结束

	MSG_C_2_S_REAL_NAME = 81, // 客户端申请实名认证 [XSea 2016.9.24]
	MSG_S_2_C_REAL_NAME = 82, // 服务器返回实名认证结果 [XSea 2016.9.24]
	MSG_C_2_S_IS_REAL_NAME = 83, // 客户端申请是否已实名认证 [XSea 2016.9.24]
	MSG_S_2_C_IS_REAL_NAME = 84, // 服务器返回是否已实名认证 [XSea 2016.9.24]

	MSG_C_2_S_VIP_LOG = 90,//玩家请求对战对账单
	MSG_S_2_C_VIP_LOG = 91,//玩家请求对战对账单结果

	MSG_C_2_S_VIDEO = 92,//玩家请求某局录像
	MSG_S_2_C_VIDEO = 93,//玩家请求某局录像

	MSG_C_2_S_ONE_VIP_LOG = 110,//玩家请求某轮对账单
	MSG_S_2_C_ONE_VIP_LOG = 111,//玩家请求某轮对账单结果

	MSG_S_2_C_ACTIVE_INFO = 94,				//通知客户端活动状态
	MSG_C_2_S_REQUEST_DRAW = 95,			//客户端请求抽卡
	MSG_S_2_C_FINISH_DRAW = 96,				//通知客户端抽卡结果
	MSG_C_2_S_WRITE_PHONE = 97,				//客户端请求写入电话
	MSG_S_2_C_WRITE_PHONE = 98,				//通知客户端写入电话结果
	MSG_C_2_S_ACTIVE_LOG = 99,				//客户端请求活动日志
	MSG_S_2_C_ACTIVE_LOG = 100,				//返馈客户端参与活动日志
	MSG_S_2_C_ACTIVE_OPEN = 101,			//通知客户端当前是否有活动
	MSG_C_2_S_ACTIVE_INFO = 102,			//客户端请求活动信息
	MSG_C_2_S_DRAW_REGBROADCAST = 220,		//客户端请求活动获奖广播信息
	MSG_S_2_C_DRAW_BROADCAST = 221,			//服务器向客户端推送活动获奖广播信息
	MSG_C_2_S_DRAW_CANCELBROADCAST = 222,	//客户端取消活动获奖广播信息
	MSG_S_2_C_DRAW_CANCELBROADCAST = 223,	//服务器返回取消活动获奖广播信息结果
	MSG_C_2_S_SHARE_DRAW = 224,            //客户端分享成功
	MSG_S_2_C_SHARE_DRAW = 225,            //服务器回复客户端分享成功

	
	MSG_C_2_S_GETGAMETYPEINFO = 103,//获取玩法信息
	MSG_S_2_C_GETGAMETYPEINFO = 104,//服务器返回玩法信息

	MSG_C_2_S_SHAREVIDEO = 105,//玩家请求查看某shareid的分享录像
	MSG_S_2_C_SHAREVIDEO = 106,//服务器返回某shareid对应的分享录像
	MSG_C_2_S_REQSHAREVIDEO = 107,//玩家请求分享某录像
	MSG_S_2_C_RETSHAREVIDEOID = 108,//服务器返回分享的id
	MSG_C_2_S_GETSHAREVIDEO = 109,//玩家通过精确的videoid查看分享的某录像

	MSG_S_2_C_USER_CHARGE_DIAMOND = 112,	// 通知客户端充值结果
	MSG_S_2_C_USER_PURCHASE = 113,			// 通知客户端购买道具结果
	MSG_S_2_C_PLAYER_TYPE =114,				// 通知客户端玩家类型
	MSG_C_2_S_CHECK_USER_QUALIFICATION = 115,	//校验用户资格请求
	MSG_S_2_C_CHECK_USER_QUALIFICATION = 116,	//校验用户资格结果
	MSG_S_2_C_NOTIFY_USER_QUALIFICATION = 146,	//通知用户符合资格

	MSG_C_2_S_COUPONS_EXCHANGE = 120,//玩家请求兑换窗口信息
	MSG_S_2_C_COUPONS_EXCHANGE = 121,//服务器返回兑换窗口信息
	MSG_C_2_S_COUPONS_EXCHANGE_RECORD = 122,//玩家请求兑换记录
	MSG_S_2_C_COUPONS_EXCHANGE_RECORD = 123,//服务器返回兑换记录
	MSG_C_2_S_GIFT_EXCHANGE = 124,//客户端请求兑换商品
	MSG_S_2_C_GIFT_EXCHANGE = 125,//服务器返回兑换商品结果
	MSG_C_2_S_GET_TASK = 126,			// 请求获取任务信息
	MSG_S_2_C_TASK_LIST = 127,			// 服务器返回任务信息
	MSG_C_2_S_RECV_TASK_REWARD = 128,	// 请求领取任务奖励
	MSG_S_2_C_RECV_TASK_REWARD = 129,	// 返回任务奖励领取结果
	MSG_C_2_S_GET_USER_INFO = 130,		// 请求获取指定玩家的信息
	MSG_S_2_C_USER_INFO = 131,			// 服务器返回玩家信息
	MSG_C_2_S_GET_INVITING_INFO = 132,	// 请求获取邀请信息
	MSG_S_2_C_INVITING_INFO = 133,		// 服务器返回邀请信息
	MSG_C_2_S_BIND_INVITER = 134,		// 请求绑定邀请人
	MSG_S_2_C_BIND_INVITER = 135,		// 服务器返回绑定邀请人结果
	MSG_C_2_S_USER_SHARED = 136,		// 玩家进行了分享
	MSG_C_2_S_REQ_LUCKY_DRAW_NUM = 137,	// 请求玩家抽奖次数
	MSG_S_2_C_LUCKY_DRAW_NUM = 138,		// 服务器推送玩家抽奖次数
	MSG_S_2_C_USER_REWARD_INFO = 139,	// 玩家获得奖励的信息
	MSG_S_2_C_REWARD_NOT_RECEIVED = 140,	// 通知玩家有奖励未领取
	MSG_C_2_S_LONGITUDE_LATITUDE = 141,		// 客户端请求同步经纬度
	MSG_S_2_C_LONGITUDE_LATITUDE = 142,		// 同步经纬度
	
	//////////////////////////////////////////////////////////////////////////
	//client 跟 server 之间消息交互
	//////////////////////////////////////////////////////////////////////////
	MSG_C_2_S_LOGIN_CENTER = 150,//客户端请求登录中心服务器
	MSG_S_2_C_LOGIN_CENTER = 150,//客户端请求登录中心服务器

	MSG_C_2_S_LOGIN_SERVER = 160,//客户端请求登录服务器
	MSG_S_2_C_LOGIN_SERVER = 160,//客户端请求登录服务器

	//比赛场协议
	MSG_S_2_C_TIPS = 170,//服务器统一推送所有提示协议
	MSG_C_2_S_VIEW_SPORT = 171,//请求 查看比赛场内容
	MSG_S_2_C_VIEW_SPORT = 172,//返回 查看比赛场内容
	MSG_C_2_S_OPTJOIN_SPORT = 173,//请求 加入或退出比赛场
	MSG_S_2_C_OPTJOIN_SPORT = 174,//返回 加入或退出比赛场
	MSG_S_2_C_SPORT_TIPS = 176,//竞技的提示
	MSG_C_2_S_SPORT_RECORD_INFO = 177,//请求比赛记录信息
	MSG_S_2_C_SPORT_RECORD_INFO = 178,//返回 请求比赛记录信息
	MSG_C_2_S_SPORT_RECORD_INFO_OPT = 179,//请求 比赛记录信息相关操作
	MSG_S_2_C_SPORT_RECORD_INFO_OPT = 180,//返回 比赛记录信息相关操作
	MSG_C_2_S_GET_PHONE_VLDCODE = 181, // 请求手机号验证
	MSG_S_2_C_GET_PHONE_VLDCODE = 182, // 返回手机号验证
	MSG_C_2_S_BIND_PHONE_NUM = 183,//请求绑定手机号
	MSG_S_2_C_BIND_PHONE_NUM = 184,//回复绑定手机号
	MSG_S_2_C_IS_BIND_PHONE_NUM = 186, //玩家扩展信息，登陆完成后会带这个消息
	MSG_S_2_C_ATTACK_MANAGED = 187,   //玩家获得托管状态和取消托管状态
	MSG_C_2_S_CANCEL_MANAGED = 188,   //请求取消托管
	MSG_S_2_C_IN_SPORT = 189,		  //告诉客户端正在比赛过程中不能加入，请等等，或取消加入比赛场（可能在加入过程中异常）
	MSG_S_2_C_SPORT_BROADCAST = 190,  //比赛场广播
	// 玩家 地址 管理 消息 通信号 200~210 [2016-8-17 willing]
	MSG_C_2_S_REQ_ALL_ADDR = 200,
	MSG_S_2_C_ALL_ADDR = 201,		// 向玩家返回所有 收件地址 [2016-8-17 willing]
	MSG_C_2_S_ADD_ADDR = 202,		// 玩家添加 收件地址 [2016-8-18 willing]
	MSG_S_2_C_ADD_ADDR_RET = 203,	// 添加地址 操作的 结果 [2016-8-18 willing]
	MSG_C_2_S_MODIFY_ADDR = 204,	// 玩家修改已经添加的地址 [2016-8-18 willing]
	MSG_S_2_C_MODIFY_ADDR_RET = 205,	// 修改地址操作返回的结果 [2016-8-18 willing]
	MSG_C_2_S_RMV_ADDR = 206,		// 删除指定的地址 [2016-8-18 willing]
	MSG_S_2_C_RMV_ADDR_RET = 207,	// 删除 操作的结果 [2016-8-18 willing]

	MSG_S_2_C_MAX = 4096, //服务器客户端之间最大消息号

	//////////////////////////////////////////////////////////////////////////
	//下面这是服务器与服务器之间的消息交互
	//////////////////////////////////////////////////////////////////////////
	//logic 跟 center 之间的交互

	MSG_L_2_CE_LOGIN = 6000, //logic登录center
	
	MSG_L_2_CE_GATE_INFO = 6002, //logic同步gate信息到center

	MSG_CE_2_L_USER_ID_INFO = 6003, //center同步玩家id信息

	MSG_CE_2_L_USER_LOGIN = 6004, //center同步玩家请求登录的消息

	MSG_L_2_CE_USER_SAVE = 6005, //logic同步玩家更新的消息

	MSG_LMG_2_CE_User_Save_PlayCount = 6408,//logicmanager同步玩家玩的局数

	MSG_L_2_CE_ROOM_SAVE = 6006, //logic同步更新room的消息

	MSG_L_2_CE_CARD_SAVE = 6007, //logic同步玩家房卡操作

	MSG_L_2_CE_USER_RELOGIN = 6008,	//玩家重新登陆

	MSG_CE_2_L_USER_RELOGIN = 6010,	//玩家重新登陆

	MSG_L_2_CE_USER_LOGIN = 6011,			//同步Center玩家当前登陆某服务器

	MSG_L_2_CE_USER_LOGOUT = 6012,			//同步Center玩家当前登出某服务器

	MSG_CE_2_L_REQ_LOG_INFO = 6013, //center发送玩家请求战绩信息			---已废

	MSG_L_2_CE_REQ_VIDEO = 6014, //logic发送玩家请求录像					---已废

	MSG_CE_2_L_REQ_VIDEO = 6015, //center发送玩家请求录像					---已废

	MSG_CE_2_L_GM_CHARGE = 6020, //center发送gm充值请求

	MSG_CE_2_L_GM_HORSE = 6021, //center发送gm跑马灯

	MSG_CE_2_L_GM_BUYINFO = 6022, //center发送gm够买提示

	MSG_CE_2_L_GM_HIDE = 6023, //center发送gmyincang

	MSG_CE_2_L_GM_TIMELIMITFREE = 6024,//center发送限免信息

	MSG_CE_2_LMG_GM_MODIFY_PLAYERTYPE = 6026,	//center发送gm修改玩家类型

	MSG_CE_2_LMG_GM_CHARGE_DIAMOND = 6027,	// center发送gm充值钻石

	MSG_CE_2_LMG_GM_PURCHASE = 6028,			// center发送gm购买道具

	MSG_LMG_2_CE_CardExchange = 6029,			// logicmananger发送房卡变化

	MSG_L_2_CE_SYN_CONFIG_INFO = 6039,       //LOGIN 同步 获得同步 信息
	MSG_CE_2_L_SYN_CONFIG_INFO = 6040,       //center 同步 config 信息

	MSG_LMG_2_CE_BREATH = 6144,				//逻辑心跳
	MSG_CE_2_LMG_BREATH = 6145,				//逻辑心跳回复

	MSG_LMG_2_CE_COUPON_CHANGED = 6401,	// logicmanager通知center玩家的礼券变化了

	MSG_CE_2_LMG_User_Gift_Info = 6402, //center发给logicmanager礼券信息和礼物信息

	MSG_LMG_2_CE_User_Coupons_Exchange_Record = 6403, //logicmanager 发给 center 礼券兑换记录

	MSG_CE_2_LMG_User_Coupons_Exchange_Record = 6404,//center 发给 logicmanager 礼券兑换记录

	MSG_LMG_2_CE_User_Coupons_Exchange_Info = 6405, //logicmanager 发给 center 礼券兑换消息

	MSG_CE_2_LMG_User_Coupons_Exchange_Info = 6406,//center 发给 logicmanager 礼券兑换结果

	MSG_LMG_2_CE_OFFLINE_USER_CARD_CHANGED = 6407, // 通知center不在线玩家房卡数量变化

	MSG_LMG_2_CE_REQ_ALL_ADDR = 6438,			// 获取所有 收件地址 [2016-8-17 willing]
	MSG_CE_2_LMG_ALL_ADDR = 6439,				// 返回所有 收件地址 [2016-8-17 willing]
	MSG_LMG_2_CE_ADD_ADDR = 6430,				// 添加地址 [2016-8-18 willing]
	MSG_CE_2_LMG_ADDR_ADDR_RET = 6431,			// 添加地址的结果 [2016-8-18 willing]
	MSG_LMG_2_CE_MODIFY_ADDR = 6432,			// 修改已有地址 [2016-8-18 willing]
	MSG_CE_2_LMG_MODIFY_ADDR_RET = 6433,		// 返回修改地址 操作的结果 [2016-8-18 willing]
	MSG_LMG_2_CE_RMV_ADDR = 6434,			// 修改已有地址 [2016-8-18 willing]
	MSG_CE_2_LMG_RMV_ADDR_RET = 6435,		// 返回修改地址 操作的结果 [2016-8-18 willing]

	MSG_LMG_2_CE_GET_PHONE_VLDCODE = 6416,		// 请求获得手机号验证码
	MSG_CE_2_LMG_GET_PHONE_VALCODE = 6417,		// 回复 获得手机号验证码
	MSG_LMG_2_CE_BIND_PHONE_NUM = 6418,		// 请求 绑定手机
	MSG_CE_2_LMG_BIND_PHONE_NUM = 6419,		// 回复 绑定手机
	MSG_LMG_2_CE_IS_BIND_PHONE_NUM = 6420,       // 请求 是否绑定手机号
	MSG_CE_2_LMG_IS_BIND_PHONE_NUM = 6421,       // 回复 是否绑定手机号
	MSG_LMG_2_CE_SPORT_RESET_DESK = 6422,       // 请求 比赛场解散房间

	MSG_LMG_2_CE_BIND_IDCARD = 6423,			//请求 绑定身份证
	MSG_CE_2_LMG_BIND_IDCARD = 6424,			//回应 绑定身份证
	MSG_LMG_2_CE_IS_BIND_IDCARD = 6425,			//请求 是否绑定身份证信息
	MSG_CE_2_LMG_IS_BIND_IDCARDE = 6426,		//回应 是否绑定身份证信息

	
	//////////////////////////////////////////////////////////////////////////
	//gete 跟 logic 之间的交互
	MSG_G_2_L_LOGIN = 7000, //gate登录logic		由LogicManager转发
	MSG_G_2_L_BREATH = 7001,			//逻辑心跳
	MSG_L_2_G_BREATH = 7002,			//逻辑心跳

	MSG_G_2_L_USER_MSG = 8000, //gate转发玩家消息到logic
	MSG_L_2_G_USER_MSG = 8001, //logic转发玩家消息到gate

	MSG_G_2_L_USER_OUT_MSG = 8002, //gate转发玩家退出消息到logic
	MSG_L_2_G_USER_OUT_MSG = 8003, //logic转发玩家退出消息到gate

	MSG_L_2_G_MODIFY_USER_STATE = 8006,	//修改玩家状态 gate to logic 


//////////////////////////////////////////////////////////////////////////
//LogicManager 与 Logic
	MSG_L_2_LMG_LOGIN = 11001,				//逻辑管理登陆
	MSG_L_2_LMG_BREATH = 11002,				//逻辑心跳
	MSG_LMG_2_L_BREATH = 11003,		//逻辑心跳回复

	MSG_LMG_2_L_CREATE_DESK = 11011,		//创建房间	只有玩家不在Logic上才创建
	MSG_LMG_2_L_ADDTO_DESK = 11013,			//加入房间	只有玩家不在Logic上才加入
	MSG_LMG_2_L_USER_LOGIN = 11016,			//玩家重新登陆

	MSG_L_2_LMG_MODIFY_USER_STATE = 11017,			//修改玩家状态  logicmanager to logic
	MSG_L_2_LMG_MODIFY_USER_CARD = 11018,			//玩游戏所耗房卡
	MSG_L_2_LMG_MODIFY_USER_PLAYCOUNT = 11019,		//修改玩家把数
	MSG_L_2_LMG_RECYLE_DESKID = 11020,				//创建失败，或桌子解散时

	MSG_L_2_LMG_USER_CIRCLE_INCREASED = 11021,		//玩家又玩了一局
	MSG_L_2_LMG_USER_COMPLETE_GAME = 11022,			//玩家完成一把游戏
	MSG_L_2_LMG_SPORT_RESULT = 11031,      //比赛结果返回 
//LogicManager 与 Gate
	MSG_G_2_LMG_LOGIN = 12001,			//逻辑管理登陆
	MSG_G_2_LMG_BREATH = 12002,			//逻辑心跳
	MSG_LMG_2_G_BREATH = 12003,			//逻辑心跳
	MSG_LMG_2_G_SYNC_LOGIC = 12010,		//同步逻辑信息
	MSG_LMG_2_G_HORSE_INFO = 12011,		//跑马灯

	MSG_LMG_2_L_MATCH_ADD_DESK = 12020,		//比赛场创建房间
	
	//////////////////////////////////////////////////////////////////////////

	//match 与其他协议 LogicManager
	MSG_M_2_LMG_LOGIN = 13001,      //match 管理登陆
	MSG_M_2_CE_LOGIN = 13002,       //match 管理登陆
	MSG_M_2_LDB_LOGIN = 13003,      //match 管理登陆

	MSG_G_2_M_LOGIN = 13004,        //gate 登陆 matchserver
	MSG_L_2_M_LOGIN = 13005,        //logic 登陆 matchserver

	MSG_M_2_G_FITER_PROTO = 13006,  //match 同步 gate 过滤协议

	MSG_LMG_2_G_SYNC_MATCH = 13010,     //Logic 同步网关 MATCH信息
	MSG_LMG_2_L_SYNC_MATCH = 13011,     //Logic 同步LOGIC MATCH信息

	MSG_LMG_2_M_USER_LOGIN = 13012,     //用户登录logicmanager转发到match
	MSG_LMG_2_M_USER_RELOGIN = 13013,   //用户重新登录logicmanager转发到match

											//逻辑处理
	MSG_M_2_LMG_SYN_SIGN_PLAYER_OPT = 13020,	   //请求报名和取消报名操作
	MSG_LMG_2_M_SYN_ACK_SIGN_PLAYER_OPT = 13021,   //请求报名和取消报名操作回复
	MSG_M_2_LMG_ACK_SIGN_PLAYER_OPT = 13022,	   //请求报名和取消报名操作确认
	MSG_M_2_LMG_PLAYER_IN_OUT_ITEM = 13023,	       //比赛项目，开赛中玩家的操作
	MSG_M_2_LMG_PLAYER_REWARD = 13024,			   //玩家的奖励
	MSG_M_2_LMG_REMOVE_SIGN_PLAYER = 13025,		   //删除报名的玩家
	MSG_M_2_LMG_GET_DESK_IDS = 13026,		   //请求空闲桌子数
	MSG_LMG_2_M_GET_DESK_IDS = 13027,		   //请求空闲桌子数回应
	MSG_LMG_2_M_SYN_USER_LOGIN_INFO = 13028,   //登陆的玩家数据同步
	MSG_LMG_2_M_SYN_LOGIC_IDS = 13029,		   //同步房间id给比赛场服务器
	MSG_M_2_LDB_UPDATE_DAILY_JOIN_TIMES = 13030,//match server通知db更新每日报名次数

	//////////////////////////////////////////////////////////////////////////
	//logicmanager 和 logicdb 交互消息

	MSG_LMG_2_LDB_BREATH = 14997,	//心跳
	MSG_LDB_2_LMG_BREATH = 14998,	//心跳
	MSG_LMG_2_LDB_LOGIN = 14999,	//LogicManager 登入LogicDB

	//logic 和 logicdb 直接的消息交互
	MSG_L_2_LDB_LOGIN = 15000, //logic 登录 logicdb

	MSG_L_2_LDB_VIP_LOG = 15001,//logic 请求 vip战绩
	MSG_LDB_2_L_VIP_LOG = 15002,//logicdb 返回 vip战绩

	MSG_L_2_LDB_ONE_VIP_LOG = 15026,//logic 请求 某轮vip战绩
	MSG_LDB_2_L_ONE_VIP_LOG = 15027,//logicdb 返回 某轮vip战绩

	MSG_L_2_LDB_VIDEO  = 15003,//logic 请求 video
	MSG_LDB_2_L_VIDEO  = 15004,//logicdb 返回 video

	MSG_L_2_LDB_ROOM_SAVE = 15005, //logic同步更新room的消息
	MSG_L_2_LDB_VIDEO_SAVE = 15006, //logic同步更新video的消息

	MSG_L_2_LDB_REQ_ACTIVE = 15007,		//Logic请求活动
	MSG_LDB_2_L_REQ_ACTIVE = 15008,		//LogicDB返回请求活动
	MSG_L_2_LDB_SYC_DRAW = 15009,		//Logic请求插入抽奖信息
	MSG_LDB_2_L_SYC_DRAW = 15010,		//LogicDB返回插入抽奖信息结果	
	MSG_L_2_LDB_SYC_PHONE = 15011,		//Center返回请求活动

	MSG_LDB_2_L_LOG_INFO = 15012, //center同步未完成的桌子信息
	MSG_L_2_LDB_BREATH = 15013,	//心跳
	MSG_LDB_2_L_BREATH = 15014,	//心跳

	MSG_LMG_2_LDB_GET_GAMEFREE = 15015,//manager加载玩法限免信息
	MSG_LDB_2_LMG_GET_GAMEFREE = 15016,//manager加载玩法限免信息
	MSG_LMG_2_LDB_SAVE_GAMEFREE = 15017,//manager存储玩法限免信息

	MSG_L_2_LDB_GETSHAREVIDEOID = 15020,//logic 玩家请求分享某录像，先去sharevideo中查看是否已被分享
	MSG_L_2_LDB_GETSHAREVIDEO = 15021,//logic 玩家通过shareid来获取该分享码下的录像 在sharevideo中查询
	MSG_LDB_2_L_RETSHAREVIDEOID  = 15022,//logicdb返回某录像是否有shareid，没有则将其从video中移至sharevideo中
	MSG_LDB_2_L_RETSHAREVIDEO  = 15023,//logicdb 返回 通过shareid查询到的可能的录像
	MSG_L_2_LDB_SAVESHAREVIDEOID = 15024,//logic 请求保存某已转移到sharevideo中的某录像的shareid
	MSG_L_2_LDB_GETSHAREVIDEOBYVIDEOID = 15025, //loigc 通过精确的videoid来查找sharevideo中的对应录像

	MSG_L_2_LDB_EXEC_SQL = 15030,		// 请求logicDB执行sql语句
	MSG_LMG_2_LDB_REQ_TASK_PROGRESS = 15031,	// logicmanager请求任务进度数据
	MSG_LDB_2_LMG_REQ_TASK_PROGRESS = 15032,	// logicDB返回任务进度
	MSG_LMG_2_LDB_REQ_BINDING_RELATIONSHIPS = 15033,	// logicmanager请求邀请绑定关系信息
	MSG_LDB_2_LMG_REQ_BINDING_RELATIONSHIPS = 15034,	// logicDB返回邀请绑定关系信息
	MSG_LMG_2_LDB_INSERT_TASK_PROGRESS = 15035,			// logicmanager请求插入任务进度数据
	MSG_LDB_2_LMG_INSERT_TASK_PROGRESS = 15036,			// logicDB返回插入任务进度数据结果
	MSG_LMG_2_LDB_REQ_ACTIVE_GIFT_STOCK = 15037,		// logicmanager请求活动的奖品库存等信息
	MSG_LDB_2_LMG_ACTIVE_GIFT_STOCK = 15038,			// logicDB返回活动的奖品库存等信息
	MSG_LMG_2_LDB_REQ_LUCKY_DRAW_NUM = 15039,			// 请求玩家抽奖次数
	MSG_LDB_2_LMG_LUCKY_DRAW_NUM = 15040,				// 返回玩家抽奖次数
	MSG_LMG_2_LDB_INSERT_BINDING_RELATIONSHIP = 15041,	// 请求插入绑定关系
	MSG_LDB_2_LMG_INSERT_BINDING_RELATIONSHIP = 15042,	// 返回插入绑定关系结果

	MSG_LMG_2_LDB_REQ_MATCH_RECORD = 15051,				// logicmanager 请求 加载玩家的 比赛记录信息 [2016-8-16 willing]
	MSG_LDB_2_LMG_MATCH_RECORD = 15052,					// logicDB 返回玩家的 比赛记录信息 [2016-8-16 willing]
	MSG_LMG_2_LDB_NEW_MATCH_RECORD = 15053,				// logicmanager 请求创建一个新的比赛记录 [2016-8-16 willing]
	MSG_LDB_2_LMG_NEW_MATCH_RECORD = 15054,				// logicDB 返回 新增的比赛记录 [2016-8-16 willing]
	MSG_LMG_2_LDB_MODIFY_MATCH_RECORD = 15055,			// logicmanager 修改玩家 比赛记录 [2016-8-16 willing]
	MSG_LMG_2_LDB_RMV_MATCH_RECORD = 15056,				// logicmanager 删除 比赛记录 [2016-8-16 willing]

	MSG_LMG_2_LDB_REQ_ALL_SPORT_USER_INFO_DATA = 15058,				// logicmanager 请求所有玩家的比赛统计信息
	MSG_LDB_2_LMG_REQ_ALL_SPORT_USER_INFO_DATA = 15059,				// logicDB 返回所有玩家的比赛统计信息

	MSG_LMG_2_LDB_REQ_UPDATA_SPORT_USER_INFO = 15062,				// logicmanager 插入比赛统计信息
	MSG_LMG_2_LDB_REQ_INSERT_SPORT_SIGN_INFO = 15063,		// logicmanager 比赛报名信息添加
	MSG_LMG_2_LDB_REQ_DELETE_SPORT_SIGN_INFO = 15064,		// logicmanager 比赛报名信息删除
	MSG_LMG_2_LDB_REQ_INSERT_SPORT_USER_INFO = 15065,		// logicmanager 保存比赛统计信息
	MSG_LMG_2_LDB_REQ_INSERT_SPORT_ITEM_STAT = 15066,     // logicmanager 保存比赛项目记录信息

	MSG_LMG_2_LDB_REQ_INSERT_SPORT_DAILY_STAT = 15067,      // 插入每日比赛项统计
	MSG_LMG_2_LDB_REQ_UPDATE_SPORT_DAILY_STAT = 15068,      // 更新每日比赛项统计

	MSG_LMG_2_LDB_REQ_SELECT_INVITER_INFO	= 16066,			// logicmanager get inviter info
	MSG_LDB_2_LMG_RSP_SELECT_INVITER_INFO	= 16067,
	MSG_LMG_2_LDB_REQ_UPDATE_BIND_TABLE		= 16068,
	MSG_LDB_2_LMG_RSP_UPDATE_BIND_TABLE		= 16069,
	MSG_LMG_2_LDB_REQ_SELECT_REWARD_TABLE	= 16070,
	MSG_LDB_2_LMG_RSP_SELECT_REWARD_TABLE   = 16071,
	MSG_LMG_2_LDB_REQ_UPDATE_REWARD_TABLE	= 16072,
	MSG_LDB_2_LMG_RSP_UPDATE_REWARD_TABLE	= 16073,
	MSG_LMG_2_LDB_REQ_INSERT_REWARD_TABLE	= 16074,
	MSG_LDB_2_LMG_RSP_INSERT_REWARD_TABLE	= 16075,

	/////////////////////////////////////////////////////////////////////////
	// LoginGate与Center之间的通信
	MSG_LG_CE_USER_MSG_WRAPPER = 20000,	// logingate和center之间对用户消息的封装
	MSG_LG_2_CE_HEARTBEAT  = 20001, //gamelogin发给center heartbeat
	//////////////////////////////////////////////////////////////////////////
	MSG_S_2_S_KEEP_ALIVE = 30000,
	MSG_S_2_S_KEEP_ALIVE_ACK = 30001,
};

struct BirdInfo
{
	Lint	m_pos;
	CardValue m_card;

	MSGPACK_DEFINE(m_pos, m_card); 

	BirdInfo():m_pos(-1){}
	bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteKeyValue(pack,NAME_TO_STR(m_pos),m_pos);
		m_card.Write(pack);
		return true;
	}
};

//////////////////////////////////////////////////////////////////////////
//socket断开的消息
#define MSG_CLIENT_KICK 0x7FFFFFFF

struct LMsgKick:public LMsg
{
	LMsgKick():LMsg(MSG_CLIENT_KICK){}

	virtual LMsg* Clone()
	{
		return new LMsgKick();
	}
};

//////////////////////////////////////////////////////////////////////////
//所有socket连上的消息
#define MSG_CLIENT_IN 0x7FFFFFFE

struct LMsgIn:public LMsg
{
	LMsgIn():LMsg(MSG_CLIENT_IN){}

	virtual LMsg* Clone()
	{
		return new LMsgIn();
	}
};

//////////////////////////////////////////////////////////////////////////
//http消息号
#define MSG_HTTP 0x7FFFFFFD

struct LMsgHttp:public LMsg
{
	std::string m_head;//消息头
	std::string m_body;//消息体

	LMsgHttp():LMsg(MSG_HTTP){}

	virtual bool Write(LBuff& buff)
	{
		buff.Write(m_head);
		buff.Write(m_body);
		return true;
	}

	virtual bool Read(LBuff& buff)
	{
		buff.Read(m_head);
		buff.Read(m_body);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgHttp();
	}
};

//////////////////////////////////////////////////////////////////////////
//客户端发送消息
struct LMsgC2SMsg :public LMsgSC
{
	Lstring			m_openId;
	Lstring			m_nike;
	Lstring			m_sign;
	Lstring			m_plate;
	Lstring			m_accessToken;
	Lstring			m_refreshToken;
	Lstring			m_md5;
	Lint			m_severID;
	Lstring			m_uuid;
	Lint			m_sex;
	Lstring			m_imageUrl;
	Lstring			m_nikename;
	Lint			m_wxConfirmed = 0;
	Lstring			m_clientIp;

	LMsgC2SMsg() :LMsgSC(MSG_C_2_S_MSG)
	{
	}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, "m_openId", m_openId);
		ReadMapData(obj, "m_nike", m_nike);
		ReadMapData(obj, "m_sign", m_sign);
		ReadMapData(obj, "m_plate", m_plate);
		ReadMapData(obj, "m_accessToken", m_accessToken);
		ReadMapData(obj, "m_refreshToken", m_refreshToken);
		ReadMapData(obj, "m_md5", m_md5);
		ReadMapData(obj, "m_severID", m_severID);
		ReadMapData(obj, "m_uuid", m_uuid);
		ReadMapData(obj, "m_sex", m_sex);
		ReadMapData(obj, "m_imageUrl", m_imageUrl);
		ReadMapData(obj, "m_nikename", m_nikename);
		ReadMapData(obj, "m_wxConfirmed", m_wxConfirmed);
		ReadMapData(obj, "m_clientIp", m_clientIp);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack,15);
		WriteKeyValue(pack, "m_msgId", m_msgId);
		WriteKeyValue(pack, "m_openId", m_openId);
		WriteKeyValue(pack, "m_nike", m_nike);
		WriteKeyValue(pack, "m_sign", m_sign);
		WriteKeyValue(pack, "m_plate", m_plate);
		WriteKeyValue(pack, "m_accessToken", m_accessToken);
		WriteKeyValue(pack, "m_refreshToken", m_refreshToken);
		WriteKeyValue(pack, "m_md5", m_md5);
		WriteKeyValue(pack, "m_severID", m_severID);
		WriteKeyValue(pack, "m_uuid", m_uuid);
		WriteKeyValue(pack, "m_sex", m_sex);
		WriteKeyValue(pack, "m_imageUrl", m_imageUrl);
		WriteKeyValue(pack, "m_nikename", m_nikename);
		WriteKeyValue(pack, "m_wxConfirmed", m_wxConfirmed);
		WriteKeyValue(pack, "m_clientIp", m_clientIp);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgC2SMsg();
	}
};

//////////////////////////////////////////////////////////////////////////
//客户端发送消息
struct LMsgS2CMsg :public LMsgSC
{
	Lint			m_errorCode;//0-成功，1-服务器还没启动成功 2-uuid错误 3- 需要微信验证 4-创建角色失败 5- 在原APP未退 6-MD5校验失败
	Lint			m_seed;
	Lint			m_id;
	Lstring			m_gateIp;
	Lshort			m_gatePort;
	Lstring			m_errorMsg;	//若登陆失败，返回玩家错误原因;
	Lint            m_totalPlayNum;//玩家的把数

	LMsgS2CMsg() :LMsgSC(MSG_S_2_C_MSG), m_errorCode(0), m_seed(0), m_id(0), m_gatePort(0), m_totalPlayNum(0)
	{
	}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, "m_errorCode", m_errorCode);
		ReadMapData(obj, "m_seed", m_seed);
		ReadMapData(obj, "m_id", m_id);
		ReadMapData(obj, "m_gateIp", m_gateIp);
		ReadMapData(obj, "m_gatePort", m_gatePort);
		ReadMapData(obj, "m_errorMsg", m_errorMsg);
		ReadMapData(obj, "m_totalPlayNum", m_totalPlayNum);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 8);
		WriteKeyValue(pack, "m_msgId", m_msgId);
		WriteKeyValue(pack, "m_errorCode", m_errorCode);
		WriteKeyValue(pack, "m_seed", m_seed);
		WriteKeyValue(pack, "m_id", m_id);
		WriteKeyValue(pack, "m_gateIp", m_gateIp);
		WriteKeyValue(pack, "m_gatePort", m_gatePort);
		WriteKeyValue(pack, "m_errorMsg", m_errorMsg);
		WriteKeyValue(pack, "m_totalPlayNum", m_totalPlayNum);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgS2CMsg();
	}
};

//////////////////////////////////////////////////////////////////////////
//客户端发送心跳包
struct LMsgC2SHeart:public LMsgSC
{
	//Lint	m_time;//时间戳

	LMsgC2SHeart() :LMsgSC(MSG_C_2_S_HEART){}

	virtual bool Read(msgpack::object& obj)
	{
		//buff.Read(m_time);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 1);
		WriteKeyValue(pack, "m_msgId", m_msgId);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgC2SHeart();}
};


//////////////////////////////////////////////////////////////////////////
//服务器发送心跳包
struct LMsgS2CHeart :public LMsgSC
{
	Lint	m_time;//时间戳

	LMsgS2CHeart() :LMsgSC(MSG_S_2_C_HEART){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_msgId), m_msgId);
		ReadMapData(obj, NAME_TO_STR(m_time), m_time);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack,2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_time), m_time);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CHeart(); }
};


//////////////////////////////////////////////////////////////////////////
//客户端请求通知
struct LMsgC2SNotice :public LMsgSC
{
	
	LMsgC2SNotice() :LMsgSC(MSG_C_2_S_NOTICE){}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 1);
		WriteKeyValue(pack, "m_msgId", m_msgId);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgC2SNotice(); }
};


//////////////////////////////////////////////////////////////////////////
//服务器返回通知内容
struct Notice
{
	Lint	m_time;//时间戳
	Lstring	m_title;//标题
	Lstring m_content;//内容

	MSGPACK_DEFINE(m_time, m_title, m_content); 
};

struct LMsgS2CNotice :public LMsgSC
{
	Lint	m_count;//时间戳
	Notice	m_data[20];

	LMsgS2CNotice() :LMsgSC(MSG_S_2_C_NOTICE){}

	virtual bool Read(msgpack::object& obj)
	{
		m_count = 0;

		msgpack::object array;
		ReadMapData(obj, "array", array);
		if (array.type == MSGPACK_OBJECT_ARRAY)
		{
			for (Lsize i = 0; i < array.via.array.size; ++i)
			{
				msgpack::object pv = *(array.via.array.ptr+i);
				pv.convert(m_data[i]);
				m_count++;
			}
		}
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKey(pack, "array");
		std::vector<Notice>vce;
		for (Lint i = 0; i < m_count&&i < 20; ++i)
		{
			vce.push_back(m_data[i]);
		}
		WriteKey(pack,vce);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CNotice(); }
};

//////////////////////////////////////////////////////////////////////////
//客户端重连
struct LMsgC2SReLogin:public LMsgSC
{
	Lint	m_seed;
	Lint	m_id;
	Lstring	m_md5;

	LMsgC2SReLogin() :LMsgSC(MSG_C_2_S_RE_LOGIN){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_seed), m_seed);
		ReadMapData(obj, NAME_TO_STR(m_id), m_id);
		ReadMapData(obj, NAME_TO_STR(m_md5), m_md5);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_seed), m_seed);
		WriteKeyValue(pack, NAME_TO_STR(m_id), m_id);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgC2SReLogin();
	}
};
//////////////////////////////////////////////////////////////////////////
//客户端请求登录大厅

struct LMsgC2SLogin:public LMsgSC
{
	Lint	m_seed;
	Lint	m_id;
	Lstring	m_md5;

	LMsgC2SLogin() :LMsgSC(MSG_C_2_S_LOGIN){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_seed), m_seed);
		ReadMapData(obj, NAME_TO_STR(m_id), m_id);
		ReadMapData(obj, NAME_TO_STR(m_md5), m_md5);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_seed), m_seed);
		WriteKeyValue(pack, NAME_TO_STR(m_id), m_id);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgC2SLogin();
	}
};

//////////////////////////////////////////////////////////////////////////
//返回玩家登陆结果消息
struct LMsgS2CLogin:public LMsgSC
{
	Lint		m_errorCode;//登录错误码，0-登录成功,1-帐号未注册，2-帐号已登录，3-未知错误
	Lint		m_id;
	Lstring		m_unionId;
	Lstring		m_nike;
	Lint		m_exp;
	Lint		m_sex;
	Lstring		m_face;//
	Lstring		m_provice;
	Lstring		m_city;
	Lstring		m_ip;
	Lstring		m_playerType;
	Lint		m_new;//0-不是，1-是
	Lint		m_card1;//新手奖励房卡1
	Lint		m_card2;//新手奖励房卡2
	Lint		m_card3;//新手奖励房卡3
	Lint		m_state;//0-进入大厅，1-进入桌子
	Lstring		m_buyInfo;//够买信息
	Lint		m_hide;//购买隐藏0-隐藏 1- 不隐藏
	Lint		m_gm;//0-不是，1-是GM
	Lint		m_serverTime;
	LMsgS2CLogin() :LMsgSC(MSG_S_2_C_LOGIN){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_errorCode), m_errorCode);
		ReadMapData(obj, NAME_TO_STR(m_id), m_id);
		ReadMapData(obj, NAME_TO_STR(m_unionId), m_unionId);
		ReadMapData(obj, NAME_TO_STR(m_nike), m_nike);
		ReadMapData(obj, NAME_TO_STR(m_exp), m_exp);
		ReadMapData(obj, NAME_TO_STR(m_sex), m_sex);
		ReadMapData(obj, NAME_TO_STR(m_face), m_face);
		ReadMapData(obj, NAME_TO_STR(m_provice), m_provice);
		ReadMapData(obj, NAME_TO_STR(m_city), m_city);
		ReadMapData(obj, NAME_TO_STR(m_playerType), m_playerType);
		ReadMapData(obj, NAME_TO_STR(m_ip), m_ip);
		ReadMapData(obj, NAME_TO_STR(m_new), m_new);
		ReadMapData(obj, NAME_TO_STR(m_card1), m_card1);
		ReadMapData(obj, NAME_TO_STR(m_card2), m_card2);
		ReadMapData(obj, NAME_TO_STR(m_card3), m_card3);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack,21);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_errorCode), m_errorCode);
		WriteKeyValue(pack, NAME_TO_STR(m_id), m_id);
		WriteKeyValue(pack, NAME_TO_STR(m_unionId), m_unionId);
		WriteKeyValue(pack, NAME_TO_STR(m_nike), m_nike);
		WriteKeyValue(pack, NAME_TO_STR(m_exp), m_exp);
		WriteKeyValue(pack, NAME_TO_STR(m_sex), m_sex);
		WriteKeyValue(pack, NAME_TO_STR(m_face), m_face);
		WriteKeyValue(pack, NAME_TO_STR(m_provice), m_provice);
		WriteKeyValue(pack, NAME_TO_STR(m_city), m_city);
		WriteKeyValue(pack, NAME_TO_STR(m_playerType), m_playerType);
		WriteKeyValue(pack, NAME_TO_STR(m_ip), m_ip);
		WriteKeyValue(pack, NAME_TO_STR(m_new), m_new);
		WriteKeyValue(pack, NAME_TO_STR(m_card1), m_card1);
		WriteKeyValue(pack, NAME_TO_STR(m_card2), m_card2);
		WriteKeyValue(pack, NAME_TO_STR(m_card3), m_card3);
		WriteKeyValue(pack, NAME_TO_STR(m_state), m_state);
		WriteKeyValue(pack, NAME_TO_STR(m_buyInfo), m_buyInfo);
		WriteKeyValue(pack, NAME_TO_STR(m_hide), m_hide);
		WriteKeyValue(pack, NAME_TO_STR(m_gm), m_gm);
		WriteKeyValue(pack, NAME_TO_STR(m_serverTime), m_serverTime);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgS2CLogin();}
};

//////////////////////////////////////////////////////////////////////////
//服务器返回玩家物品信息
struct LMsgS2CItemInfo:public LMsgSC
{
	Lint	m_card1;
	Lint	m_card2;
	Lint	m_card3;
	Lint	m_diamondNum;

	LMsgS2CItemInfo() :LMsgSC(MSG_S_2_C_ITEM_INFO){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_card1), m_card1);
		ReadMapData(obj, NAME_TO_STR(m_card2), m_card2);
		ReadMapData(obj, NAME_TO_STR(m_card3), m_card3);
		ReadMapData(obj, NAME_TO_STR(m_diamondNum), m_diamondNum);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 5);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_card1), m_card1);
		WriteKeyValue(pack, NAME_TO_STR(m_card2), m_card2);
		WriteKeyValue(pack, NAME_TO_STR(m_card3), m_card3);
		WriteKeyValue(pack, NAME_TO_STR(m_diamondNum), m_diamondNum);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgS2CItemInfo();}
};

//////////////////////////////////////////////////////////////////////////
//服务器返回跑马灯信息
struct LMsgS2CHorseInfo :public LMsgSC
{
	Lstring	m_str;

	LMsgS2CHorseInfo() :LMsgSC(MSG_S_2_C_HORSE_INFO){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_str), m_str);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_str), m_str);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CHorseInfo(); }
};

//////////////////////////////////////////////////////////////////////////
//服务器返回玩家进入桌子
struct LMsgS2CIntoDesk:public LMsgSC
{
	Lint			m_deskId;
	Lint			m_pos;	//我的位置，0-3 分别代表东，南，西，北
	Lint			m_ready;//我是否准备，0-未准备，1-已经准备
	Lint			m_score;//我的积分
	Lint			m_flag;//0-只能自摸，1-可以收炮，2-可以抢杠
	Lint			m_maxCircle;//最大局数
	
	Lint			m_rank; //玩家比赛等级
	Lint			m_overScore; //淘汰积分
	Lint            m_sportId; //比赛id
	Lint            m_process; //比赛进程 0 就是 淘汰赛阶段 1 定局积分 第一阶段 2 定局积分第二阶段 3 定局积分最后阶段

	std::vector<Lint>	m_playtype;
	std::vector<Lint>	m_playtype_starthu;

	LMsgS2CIntoDesk():LMsgSC(MSG_S_2_C_INTO_DESK){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_deskId), m_deskId);
		ReadMapData(obj, NAME_TO_STR(m_pos), m_pos);
		ReadMapData(obj, NAME_TO_STR(m_ready), m_ready);
		ReadMapData(obj, NAME_TO_STR(m_score), m_score);
		ReadMapData(obj, NAME_TO_STR(m_state), m_flag);
		ReadMapData(obj, NAME_TO_STR(m_maxCircle), m_maxCircle);
		ReadMapData(obj, NAME_TO_STR(m_rank), m_rank);
		ReadMapData(obj, NAME_TO_STR(m_overScore), m_overScore);
		ReadMapData(obj, NAME_TO_STR(m_playtype), m_playtype);
		ReadMapData(obj, NAME_TO_STR(m_sportId), m_sportId);
		ReadMapData(obj, NAME_TO_STR(m_process), m_process);
		ReadMapData(obj, NAME_TO_STR(m_playtype_starthu), m_playtype_starthu);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 13);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_deskId), m_deskId);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);
		WriteKeyValue(pack, NAME_TO_STR(m_ready), m_ready);
		WriteKeyValue(pack, NAME_TO_STR(m_score), m_score);
		WriteKeyValue(pack, NAME_TO_STR(m_state), m_flag);
		WriteKeyValue(pack, NAME_TO_STR(m_maxCircle), m_maxCircle);
		WriteKeyValue(pack, NAME_TO_STR(m_rank), m_rank);
		WriteKeyValue(pack, NAME_TO_STR(m_overScore), m_overScore);
		WriteKeyValue(pack, NAME_TO_STR(m_playtype), m_playtype);
		WriteKeyValue(pack, NAME_TO_STR(m_sportId), m_sportId);
		WriteKeyValue(pack, NAME_TO_STR(m_process), m_process);
		WriteKeyValue(pack, NAME_TO_STR(m_playtype_starthu), m_playtype_starthu);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgS2CIntoDesk();}
};

//////////////////////////////////////////////////////////////////////////
//服务器返回桌子添加一个玩家
struct LMsgS2CDeskAddUser:public LMsgSC
{
	Lint			m_userId;
	Lstring			m_nike;//玩家昵称
	Lstring			m_face;//玩家图形，为空就为默认图形
	Lint			m_sex;//玩家性别
	Lint			m_pos;	//位置，0-3 分别代表东，南，西，北
	Lint			m_ready;//0-未准备，1-已准备
	Lint			m_score;//玩家积分
	Lstring			m_ip;

	LMsgS2CDeskAddUser() :LMsgSC(MSG_S_2_C_ADD_USER){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_userId), m_userId);
		ReadMapData(obj, NAME_TO_STR(m_nike), m_nike);
		ReadMapData(obj, NAME_TO_STR(m_face), m_face);
		ReadMapData(obj, NAME_TO_STR(m_sex), m_sex);
		ReadMapData(obj, NAME_TO_STR(m_pos), m_pos);
		ReadMapData(obj, NAME_TO_STR(m_ready), m_ready);
		ReadMapData(obj, NAME_TO_STR(m_score), m_score);
		ReadMapData(obj, NAME_TO_STR(m_ip), m_ip);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 9);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_userId), m_userId);
		WriteKeyValue(pack, NAME_TO_STR(m_nike), m_nike);
		WriteKeyValue(pack, NAME_TO_STR(m_face), m_face);
		WriteKeyValue(pack, NAME_TO_STR(m_sex), m_sex);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);
		WriteKeyValue(pack, NAME_TO_STR(m_ready), m_ready);
		WriteKeyValue(pack, NAME_TO_STR(m_score), m_score);
		WriteKeyValue(pack, NAME_TO_STR(m_ip), m_ip);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgS2CDeskAddUser();}
};

//////////////////////////////////////////////////////////////////////////
//服务器返回删除玩家
struct LMsgS2CDeskDelUser:public LMsgSC
{
	Lint			m_pos;//删除玩家位置 如果pos == 我的位置，代表我自己被踢出桌子，把桌子其他人清掉

	LMsgS2CDeskDelUser() :LMsgSC(MSG_S_2_C_DEL_USER){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_pos), m_pos);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgS2CDeskDelUser();}
};

//////////////////////////////////////////////////////////////////////////
//客户端请求推出房间
struct LMsgC2SLeaveDesk:public LMsgSC
{
	Lint			m_pos;//我的位置

	LMsgC2SLeaveDesk() :LMsgSC(MSG_C_2_S_LEAVE_ROOM){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_pos), m_pos);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgC2SLeaveDesk();}
};

//////////////////////////////////////////////////////////////////////////
//服务器返回结果
struct LMsgS2CLeaveDesk:public LMsgSC
{
	Lint			m_errorCode;//0-成功，1-失败

	LMsgS2CLeaveDesk() :LMsgSC(MSG_S_2_C_LEAVE_ROOM){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_errorCode), m_errorCode);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_errorCode), m_errorCode);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgS2CLeaveDesk();}
};

//////////////////////////////////////////////////////////////////////////
//客户端申请解算房间
struct LMsgC2SResetDesk:public LMsgSC
{
	Lint	m_pos;//位置
	LMsgC2SResetDesk():LMsgSC(MSG_C_2_S_RESET_ROOM){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_pos), m_pos);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgC2SResetDesk();}
};

//////////////////////////////////////////////////////////////////////////
struct LMsgS2CResetDesk:public LMsgSC
{
	Lint					m_errorCode;//0-等待操作中，1-未开始直接解算，2-三个人同意，解算成功，3-时间到，解算成功，4-有一个人拒绝，解算失败
	Lint					m_time;//倒计时
	Lstring					m_applay;//申请的玩家
	Lstring					m_refluse;//拒绝的玩家,有一个玩家拒绝，则解算房间失败
	Lint					m_flag;//0-等待我同意或者拒绝，1-我已经同意或者拒绝                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
	std::vector<Lstring>	m_agree;//同意的玩家
	std::vector<Lstring>	m_wait;//等待操作的玩家
	

	LMsgS2CResetDesk() :LMsgSC(MSG_S_2_C_RESET_ROOM){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_errorCode), m_errorCode);
		ReadMapData(obj, NAME_TO_STR(m_flag), m_flag);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 8);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_errorCode), m_errorCode);
		WriteKeyValue(pack, NAME_TO_STR(m_time), m_time);
		WriteKeyValue(pack, NAME_TO_STR(m_apply), m_applay);
		WriteKeyValue(pack, NAME_TO_STR(m_flag), m_flag);
		
		WriteKey(pack,"m_agree");
		WriteKey(pack, m_agree);

		WriteKey(pack,"m_refuse");
		WriteKey(pack,m_refluse);

		WriteKey(pack, "m_wait");
		WriteKey(pack, m_wait);

		return true;
	}

	virtual LMsg* Clone(){return new LMsgS2CResetDesk();}
};

//////////////////////////////////////////////////////////////////////////
//客户端同意或者拒绝操作
struct LMsgC2SSelectResetDesk:public LMsgSC
{
	Lint	m_pos;//位置
	Lint	m_flag;//1-同意，2-拒绝
	LMsgC2SSelectResetDesk():LMsgSC(MSG_C_2_S_RESET_ROOM_SELECT){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_pos), m_pos);
		ReadMapData(obj, NAME_TO_STR(m_flag), m_flag);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);
		WriteKeyValue(pack, NAME_TO_STR(m_flag), m_flag);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgC2SSelectResetDesk();}
};

//////////////////////////////////////////////////////////////////////////
//服务器发送桌子状态，这个消息主要用于重连用
struct LMsgS2CDeskState:public LMsgSC
{
	Lint		m_state;//当前桌子状态 1-等待，2-游戏中，会有后面的数据
	Lint		m_time;//倒计时
	Lint		m_flag;//0-等待别人，1-该我出牌，2-该我思考
	Lint		m_zhuang;//庄的位置
	Lint		m_dCount;//桌面剩余的牌
	Lint		m_pos;//我的位置
	Lint		m_cardCount[4];//0-3号玩家手上的牌数量
	Lint        m_score[4];
	Lint		m_user_count;
	Lint		m_myPos;
	//我手上的牌
	CardValue	m_cardValue[14];

	//碰的牌
	Lint		m_pCount[4];
	CardValue	m_pCard[4][20];

	//暗杠的牌
	Lint		m_aCount[4];
	CardValue	m_aCard[4][20];

	//明杠的牌
	Lint		m_mCount[4];
	CardValue	m_mCard[4][20];

	//出出去的牌
	Lint		m_oCount[4];
	CardValue	m_oCard[4][25];

	//吃的牌
	Lint		m_eCount[4];
	CardValue	m_eCard[4][20];

	CardValue   m_WangbaCard;

	bool m_ShangWang;
	bool m_XiaWang;

	bool m_isBaoTing;

	LMsgS2CDeskState() :LMsgSC(MSG_S_2_C_DESK_STATE), m_ShangWang(false), m_XiaWang(false), m_isBaoTing(false){
		memset(m_score,0,sizeof(m_score));
		memset(m_cardCount,0,sizeof(m_cardCount));
		memset(m_pCount,0,sizeof(m_pCount));
		memset(m_aCount,0,sizeof(m_aCount));
		memset(m_mCount,0,sizeof(m_mCount));
		memset(m_oCount,0,sizeof(m_oCount));
		memset(m_eCount,0,sizeof(m_eCount));
		memset(&m_WangbaCard, 0, sizeof(m_WangbaCard));
		m_user_count=0;
	}
	

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_pos), m_pos);
		ReadMapData(obj, NAME_TO_STR(m_state), m_state);
		ReadMapData(obj, NAME_TO_STR(m_flag), m_flag);
		ReadMapData(obj, NAME_TO_STR(m_zhuang), m_zhuang);
		ReadMapData(obj, NAME_TO_STR(m_dCount), m_dCount);
		//ReadMapData(obj, NAME_TO_STR(m_myPos), m_myPos);

		msgpack::object array;
		ReadMapData(obj, NAME_TO_STR(m_myCard), array);
		if (array.type == MSGPACK_OBJECT_ARRAY)
		{
			m_cardCount[m_pos] = array.via.array.size;
			for (Lsize i = 0; i < array.via.array.size; ++i)
			{
				msgpack::object& pv = *(array.via.array.ptr + i);
				pv.convert(m_cardValue[i]);
			}
		}
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 14+5*m_user_count);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_state), m_state);

		WriteKeyValue(pack, NAME_TO_STR(m_flag), m_flag);
		WriteKeyValue(pack, NAME_TO_STR(m_zhuang), m_zhuang);
		WriteKeyValue(pack, NAME_TO_STR(m_dCount), m_dCount);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);
		WriteKeyValue(pack, NAME_TO_STR(m_ShangWang), m_ShangWang);
		WriteKeyValue(pack, NAME_TO_STR(m_XiaWang), m_XiaWang);
		WriteKeyValue(pack, NAME_TO_STR(m_isBaoTing), m_isBaoTing);
		m_WangbaCard.Write(pack);
 		std::vector<CardValue> vec;
		WriteKey(pack, "m_CardCount");
		std::vector<Lint> veci;
		for (Lint i = 0; i < m_user_count; ++i)
		{
			veci.push_back(m_cardCount[i]);
		}
		WriteKey(pack,veci);

		WriteKey(pack, "m_myCard");
		vec.clear();
		for (Lint i = 0; i < m_cardCount[m_myPos]; ++i)
		{
			vec.push_back(m_cardValue[i]);
		}
		WriteKey(pack,vec);

		WriteKey(pack, "m_score");
		veci.clear();
		for (Lint i = 0; i < m_user_count; ++i)
		{
			veci.push_back(m_score[i]);
		}
		WriteKey(pack,veci);

 		for (Lint i = 0; i < m_user_count; ++i)
 		{
			char name[32];
			sprintf(name,"m_pCard%d",i);
 			WriteKey(pack, name);
 			vec.clear();
 			for (Lint j = 0; j < m_pCount[i]; j+=3)
 			{
 				vec.push_back(m_pCard[i][j]);
 			}
 			WriteKey(pack,vec);
 		}

		for (Lint i = 0; i < m_user_count; ++i)
		{
			char name[32];
			sprintf(name,"m_aCard%d",i);
			WriteKey(pack, name);
			vec.clear();
			for (Lint j = 0; j < m_aCount[i]; j+=4)
			{
				vec.push_back(m_aCard[i][j]);
			}
			WriteKey(pack,vec);
		}

		for (Lint i = 0; i < m_user_count; ++i)
		{
			char name[32];
			sprintf(name,"m_mCard%d",i);
			WriteKey(pack, name);
			vec.clear();
			for (Lint j = 0; j < m_mCount[i]; j+=4)
			{
				vec.push_back(m_mCard[i][j]);
			}
			WriteKey(pack,vec);
		}

		for (Lint i = 0; i < m_user_count; ++i)
		{
			char name[32];
			sprintf(name, "m_oCard%d", i);
			WriteKey(pack, std::string(name));
			vec.clear();
			for (Lint j = 0; j < m_oCount[i]; ++j)
			{
				vec.push_back(m_oCard[i][j]);
			}
			WriteKey(pack,vec);
		}
		for (Lint i = 0; i < m_user_count; ++i)
		{
			char name[32];
			sprintf(name, "m_eCard%d", i);
			WriteKey(pack, std::string(name));
			vec.clear();
			for (Lint j = 0; j < m_eCount[i]; ++j)
			{
				vec.push_back(m_eCard[i][j]);
			}
			WriteKey(pack,vec);
		}
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CDeskState(); }
};


//////////////////////////////////////////////////////////////////////////
//客户端请求准备
struct LMsgC2SUserReady:public LMsgSC
{
	Lint m_pos;

	LMsgC2SUserReady() :LMsgSC(MSG_C_2_S_READY){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_pos), m_pos);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgC2SUserReady();}
};

//////////////////////////////////////////////////////////////////////////
//服务器返回玩家准备
struct LMsgS2CUserReady:public LMsgSC
{
	Lint			m_pos;//准备玩家的位置

	LMsgS2CUserReady() :LMsgSC(MSG_S_2_C_READY){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_pos), m_pos);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgS2CUserReady();}
};


//////////////////////////////////////////////////////////////////////////
//服务器返回玩家准备
struct LMsgS2CUserOnlineInfo:public LMsgSC
{
	Lint			m_flag;//0-掉线了，1-回来了
	Lint			m_pos;//
	Lstring			m_ip;

	LMsgS2CUserOnlineInfo() :LMsgSC(MSG_S_2_C_USER_ONLINE_INFO){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_pos), m_pos);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 4);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);
		WriteKeyValue(pack, NAME_TO_STR(m_flag), m_flag);
		WriteKeyValue(pack, NAME_TO_STR(m_ip), m_ip);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CUserOnlineInfo(); }
};
//////////////////////////////////////////////////////////////////////////
//服务器广播游戏开始

struct LMsgS2CPlayStart:public LMsgSC
{
	Lint		m_zhuang;
	Lint		m_dCount;//桌面剩余的牌	
	Lint		m_cardCount[4];//0-3号玩家手上的牌数量
	Lint		m_pos;
	std::vector<Lint> m_score;
	//我手上的牌
	CardValue	m_cardValue[14];

	LMsgS2CPlayStart() :LMsgSC(MSG_S_2_C_START){}

	virtual bool Read(msgpack::object& obj)
	{
		msgpack::object array;
 		ReadMapData(obj, NAME_TO_STR(m_myCard), array);
 		if (array.type == MSGPACK_OBJECT_ARRAY)
 		{
 			//m_cardCount[0] = array.via.array.size;
 			for (Lsize i = 0; i < array.via.array.size; ++i)
 			{
 				msgpack::object& pv = *(array.via.array.ptr + i);
 				pv.convert(m_cardValue[i]);
 			}
 		}

		msgpack::object array1;
		ReadMapData(obj, NAME_TO_STR(m_CardCount), array1);
		if (array1.type == MSGPACK_OBJECT_ARRAY)
		{
			for (Lsize i = 0; i < array1.via.array.size; ++i)
			{
				msgpack::object& pv = *(array1.via.array.ptr + i);
				pv.convert(m_cardCount[i]);
			}
		}

		ReadMapData(obj, NAME_TO_STR(m_zhuang), m_zhuang);
		ReadMapData(obj, NAME_TO_STR(m_dCount), m_dCount);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 6);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_score), m_score);

		WriteKey(pack, "m_myCard");
		std::vector<CardValue>vce;
		for (Lint i = 0; i < m_cardCount[m_pos]; ++i)
		{
			vce.push_back(m_cardValue[i]);
		}
 		WriteKey(pack,vce);

		WriteKey(pack, "m_CardCount");
		std::vector<Lint>vcei;
		for(Lint i = 0 ; i < 4;++i)
		{
			vcei.push_back(m_cardCount[i]);
		}
		WriteKey(pack,vcei);

		WriteKeyValue(pack, NAME_TO_STR(m_dCount),m_dCount);
		WriteKeyValue(pack, NAME_TO_STR(m_zhuang), m_zhuang);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgS2CPlayStart();}
};

//////////////////////////////////////////////////////////////////////////
//服务器广播玩家摸牌

struct ThinkData
{
	Lint	m_type;
	std::vector<CardValue> m_card;

	MSGPACK_DEFINE(m_type, m_card); 
};

struct LMsgS2COutCard:public LMsgSC
{
	Lint		m_pos;//当前出牌中的玩家
	Lint		m_time;//出牌倒计时
	Lint		m_deskCard;//桌面剩余的牌
	Lint		m_flag;//当前是否需要摸牌，0-需要，1-不需要
	Lint		m_gang;//是否杠过，0-没有，1-杠过
	Lint		m_end;//是否海底 0-不是，1-是
	CardValue	m_curCard;//摸上来的牌，这个只有 m_pos == mypos m_flag == 0 的时候才有

	std::vector<ThinkData> m_think;//思考的内容


	LMsgS2COutCard() :LMsgSC(MSG_S_2_C_GET_CARD){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_msgId), m_msgId);
		ReadMapData(obj, NAME_TO_STR(m_pos), m_pos);
		ReadMapData(obj, NAME_TO_STR(m_time), m_time);
		ReadMapData(obj, NAME_TO_STR(m_dCount), m_deskCard);
		m_curCard.Read(obj);
		ReadMapData(obj, NAME_TO_STR(m_flag), m_flag);
		ReadMapData(obj, NAME_TO_STR(m_think), m_think);
		ReadMapData(obj, NAME_TO_STR(m_gang), m_gang);
		ReadMapData(obj, NAME_TO_STR(m_end), m_end);
		//
		/*msgpack::object array1;
		ReadMapData(obj, NAME_TO_STR(m_think), array1);
		if (array1.type == MSGPACK_OBJECT_ARRAY)
		{
			for (Lsize i = 0; i < array1.via.array.size; ++i)
			{
				ThinkData v;
				msgpack::object& pv = *(array1.via.array.ptr + i);
				pv.convert(v);
				m_think.push_back(v);
			}
		}*/
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 10);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);
		WriteKeyValue(pack, NAME_TO_STR(m_time), m_time);
		WriteKeyValue(pack, NAME_TO_STR(m_dCount), m_deskCard);
		m_curCard.Write(pack);
		WriteKeyValue(pack, NAME_TO_STR(m_flag), m_flag);
		WriteKeyValue(pack, NAME_TO_STR(m_think), m_think);
		WriteKeyValue(pack, NAME_TO_STR(m_gang), m_gang);
		WriteKeyValue(pack, NAME_TO_STR(m_end), m_end);

		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2COutCard(); }
};

//////////////////////////////////////////////////////////////////////////
//客户端摸牌后的操作
struct LMsgC2SUserPlay:public LMsgSC
{
	ThinkData m_thinkInfo;

	LMsgC2SUserPlay() :LMsgSC(MSG_C_2_S_PLAY_CARD){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_type), m_thinkInfo.m_type);

		msgpack::object array;
		ReadMapData(obj, NAME_TO_STR(m_think), array);
		if (array.type == MSGPACK_OBJECT_ARRAY)
		{
			Lint m_count = array.via.array.size;
			for (Lsize i = 0; i < array.via.array.size; ++i)
			{
				CardValue v;
				msgpack::object& obj =  *(array.via.array.ptr+i);
				obj.convert(v);
				m_thinkInfo.m_card.push_back(v);
			}
		}
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_type), m_thinkInfo.m_type);
		WriteKeyValue(pack, NAME_TO_STR(m_think), m_thinkInfo.m_card);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgC2SUserPlay();}
};

//TuiDaoHu
struct LMsgC2SThrowDice :public LMsgSC
{
	ThinkData m_think;

	LMsgC2SThrowDice() :LMsgSC(MSG_C_2_S_PLAY_DICE) {}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_type), m_think.m_type);

		msgpack::object array;
		ReadMapData(obj, NAME_TO_STR(m_think), array);
		if (array.type == MSGPACK_OBJECT_ARRAY)
		{
			Lint m_count = array.via.array.size;
			for (Lsize i = 0; i < array.via.array.size; ++i)
			{
				CardValue v;
				msgpack::object& obj = *(array.via.array.ptr + i);
				obj.convert(v);
				m_think.m_card.push_back(v);
			}
		}
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_type), m_think.m_type);
		WriteKeyValue(pack, NAME_TO_STR(m_think), m_think.m_card);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgC2SThrowDice(); }
};

//////////////////////////////////////////////////////////////////////////
//服务器返回操作结果
struct LMsgS2CUserPlay:public LMsgSC
{
	Lint		m_errorCode;
	Lint		m_flag;////0-自摸，1-出牌,2-暗牌,3-明杠(自己碰过之后)
	Lint		m_pos;//出牌玩家的位置
	ThinkData	m_card;
	std::vector<Lint>	m_hu;
	Lint		m_cardCount;			//手牌数量
	std::vector<CardValue> m_cardValue;	//推倒的手牌
	CardValue m_huCard;					//自摸胡的那张牌
	LMsgS2CUserPlay() :LMsgSC(MSG_S_2_C_PLAY_CARD){
	m_errorCode = 0;
	m_flag = 0;
	m_pos = 0;
	m_card.m_card.clear();
	m_hu.clear();
	m_cardCount = 0;
	m_cardValue.clear();
	}

	virtual bool Read(msgpack::object& obj)
	{
		/*ReadMapData(obj, NAME_TO_STR(m_errorCode), m_errorCode);
		ReadMapData(obj, NAME_TO_STR(m_flag), m_flag);
		ReadMapData(obj, NAME_TO_STR(m_pos), m_pos);*/

		ReadMapData(obj, NAME_TO_STR(m_msgId), m_msgId);
		ReadMapData(obj, NAME_TO_STR(m_errorCode), m_errorCode);
		ReadMapData(obj, NAME_TO_STR(m_type), m_card.m_type);
		ReadMapData(obj, NAME_TO_STR(m_pos), m_pos);

		msgpack::object array;
		ReadMapData(obj, NAME_TO_STR(m_think), array);
		if (array.type == MSGPACK_OBJECT_ARRAY)
		{
			Lint m_count = array.via.array.size;
			for (Lsize i = 0; i < array.via.array.size; ++i)
			{
				CardValue v;
				msgpack::object& obj =  *(array.via.array.ptr+i);
				obj.convert(v);
				m_card.m_card.push_back(v);
			}
		}

		ReadMapData(obj, NAME_TO_STR(m_hu), array);
		if (array.type == MSGPACK_OBJECT_ARRAY)
		{
			Lint m_count = array.via.array.size;
			for (Lsize i = 0; i < array.via.array.size; ++i)
			{
				Lint v;
				msgpack::object& obj =  *(array.via.array.ptr+i);
				obj.convert(v);
				m_hu.push_back(v);
			}
		}

		ReadMapData(obj, NAME_TO_STR(m_cardCount), m_cardCount);
		ReadMapData(obj, NAME_TO_STR(m_cardValue), array);
		if (array.type == MSGPACK_OBJECT_ARRAY)
		{
			Lint m_count = array.via.array.size;
			for (Lsize i = 0; i < array.via.array.size; ++i)
			{
				CardValue v;
				msgpack::object& obj =  *(array.via.array.ptr+i);
				obj.convert(v);
				m_cardValue.push_back(v);
			}
		}

		m_huCard.Read(obj);

		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 10);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_errorCode), m_errorCode);
		WriteKeyValue(pack, NAME_TO_STR(m_type), m_card.m_type);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);
		WriteKeyValue(pack, NAME_TO_STR(m_think), m_card.m_card);
		WriteKeyValue(pack, NAME_TO_STR(m_hu), m_hu);
		WriteKeyValue(pack, NAME_TO_STR(m_cardCount), m_cardCount);
		WriteKeyValue(pack, NAME_TO_STR(m_cardValue), m_cardValue);
		m_huCard.Write(pack);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgS2CUserPlay();}
};

//////////////////////////////////////////////////////////////////////////
//服务器发送玩家思考信息

struct LMsgS2CThink:public LMsgSC
{
	Lint				m_time;//思考倒计时
	Lint				m_flag;//0-等待其他玩家思考中，1-当前我正在思考
	CardValue			m_card;
	std::vector<ThinkData>	m_think;


	LMsgS2CThink() :LMsgSC(MSG_S_2_C_USER_THINK){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_msgId), m_msgId);
		ReadMapData(obj, NAME_TO_STR(m_time), m_time);
		ReadMapData(obj, NAME_TO_STR(m_flag), m_flag);
		ReadMapData(obj, NAME_TO_STR(m_think), m_think);
		m_card.Read(obj);
		//
		msgpack::object array1;
		ReadMapData(obj, NAME_TO_STR(m_think), array1);
		if (array1.type == MSGPACK_OBJECT_ARRAY)
		{
			for (Lsize i = 0; i < array1.via.array.size; ++i)
			{
				ThinkData v;
				msgpack::object& pv = *(array1.via.array.ptr + i);
				pv.convert(v);
				m_think.push_back(v);
			}
		}
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 6);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_time), m_time);
		WriteKeyValue(pack, NAME_TO_STR(m_flag), m_flag);
		WriteKeyValue(pack, NAME_TO_STR(m_think), m_think);
		m_card.Write(pack);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgS2CThink();}
};

//////////////////////////////////////////////////////////////////////////
//客户端发送思考操作结果
struct LMsgC2SUserOper:public LMsgSC
{
	ThinkData m_think; 
	//Lint m_think;//思考结果0-过，1-胡，2-杠，3-碰,4-补

	LMsgC2SUserOper() :LMsgSC(MSG_C_2_S_USER_OPER){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_type), m_think.m_type);

		msgpack::object array;
		ReadMapData(obj, NAME_TO_STR(m_think), array);
		if (array.type == MSGPACK_OBJECT_ARRAY)
		{
			Lint m_count = array.via.array.size;
			for (Lsize i = 0; i < array.via.array.size; ++i)
			{
				CardValue v;
				msgpack::object& obj =  *(array.via.array.ptr+i);
				obj.convert(v);
				m_think.m_card.push_back(v);
			}
		}
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_type), m_think.m_type);
		WriteKeyValue(pack, NAME_TO_STR(m_think), m_think.m_card);

		return true;
	}


	virtual LMsg* Clone(){return new LMsgC2SUserOper();}
};

//////////////////////////////////////////////////////////////////////////
//服务广播操作结果
struct LMsgS2CUserOper:public LMsgSC
{
	Lint		m_errorCode;//0-成功，1-失败
	Lint		m_pos;//pos=我自己的时候，需要根据类型响应不同的操作
	ThinkData	m_think; 
	CardValue	m_card; //玩家碰，杠，胡的张牌
	CardValue   m_hucard2;//胡两张时第二张牌
	std::vector<Lint>	m_hu;
	Lint		m_cardCount;			//手牌数量
	std::vector<CardValue> m_cardValue;	//推倒的手牌
	LMsgS2CUserOper() :LMsgSC(MSG_S_2_C_USER_OPER){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_errorCode), m_errorCode);
		ReadMapData(obj, NAME_TO_STR(m_pos), m_pos);
		ReadMapData(obj, NAME_TO_STR(m_think), m_think);
		m_card.Read(obj);
		ReadMapData(obj, NAME_TO_STR(m_hu), m_hu);
		ReadMapData(obj, NAME_TO_STR(m_cardCount), m_cardCount);
		ReadMapData(obj, NAME_TO_STR(m_cardValue), m_cardValue);
		ReadMapData(obj, NAME_TO_STR(m_hucard2_number), m_hucard2.m_number);
		ReadMapData(obj, NAME_TO_STR(m_hucard2_color), m_hucard2.m_color);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 11);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_errorCode), m_errorCode);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);
		WriteKeyValue(pack, NAME_TO_STR(m_think), m_think);
		m_card.Write(pack);
		WriteKeyValue(pack, NAME_TO_STR(m_hu), m_hu);
		WriteKeyValue(pack, NAME_TO_STR(m_cardCount), m_cardCount);
		WriteKeyValue(pack, NAME_TO_STR(m_cardValue), m_cardValue)
		WriteKeyValue(pack, NAME_TO_STR(m_hucard2_number), m_hucard2.m_number);
		WriteKeyValue(pack, NAME_TO_STR(m_hucard2_color), m_hucard2.m_color);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgS2CUserOper();}
};

//////////////////////////////////////////////////////////////////////////
//服务器广播游戏结束
struct LMsgS2CGameOver:public LMsgSC
{
	Lint		m_result;//0-自摸，1-点炮，2-慌庄
	Lint		m_win[4];//4家胡牌情况，0-没胡，1-自摸，2-收炮，3-点炮 7-抢杠胡 8-杠上炮 9-杠上花 10-杠上开花点杠包赔
	Lint		m_score[4];//东 南 西 北 各家输赢积分，这里需要更新玩家积分
	Lint		m_agang[4];//暗杠数量
	Lint		m_mgang[4];//明杠数量
	Lint		m_dmgang[4];//被点杠数量
	Lint		m_dgang[4];//点杠数量
	Lint		m_zhongtusixi[4];//中途四喜
	std::vector<Lint>		m_startHu[4];//起手胡牌
	std::vector<Lint>		m_hu[4];//胡牌的数组
	
	//四家手上的牌
	Lint		m_count[4];
	CardValue	m_card[4][14];

	std::vector<CardValue> m_hucards[4];	//胡的牌
	Lint		m_end;
	std::vector<BirdInfo>	m_bird_infos;	//鸟牌

	Lint		m_user_count;

	CardValue   m_WangbaCard;
	bool        m_isBaoTing[4];
	LMsgS2CGameOver() :LMsgSC(MSG_S_2_C_GAME_OVER){
		memset(m_win,0,sizeof(m_win));
		memset(m_score,0,sizeof(m_score));
		memset(m_agang,0,sizeof(m_agang));
		memset(m_mgang,0,sizeof(m_mgang));
		memset(m_dmgang, 0, sizeof(m_dmgang));
		memset(m_dgang,0,sizeof(m_dgang));
		memset(m_zhongtusixi,0,sizeof(m_zhongtusixi));
		memset(m_count,0,sizeof(m_count));
		memset(&m_WangbaCard, 0, sizeof(m_WangbaCard));
		m_user_count =0;
		for (int i = 0; i < 4; ++i)
		{
			m_isBaoTing[i] = false;
		}

	}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 29+m_user_count);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_result), m_result);
		WriteKeyValue(pack, NAME_TO_STR(m_end), m_end);
		WriteKeyValue(pack, "m_isBaoTing0", m_isBaoTing[0]);
		WriteKeyValue(pack, "m_isBaoTing1", m_isBaoTing[1]);
		WriteKeyValue(pack, "m_isBaoTing2", m_isBaoTing[2]);

		WriteKeyValue(pack, "m_isBaoTing3", m_isBaoTing[3]);
		m_WangbaCard.Write(pack);
		WriteKey(pack, "m_win");
		std::vector<Lint> veci;
		for (Lint i = 0; i < m_user_count; ++i)
		{
			veci.push_back(m_win[i]);
		}
		WriteKey(pack,veci);

		for(Lint i = 0 ; i < m_user_count; ++i)
		{
			char name[32];
			sprintf_s(name,sizeof(name),"m_hu%d",i+1);
			WriteKey(pack, name);
			WriteKey(pack,m_hu[i]);
		}

		WriteKey(pack, "m_zhongtusixi");
		veci.clear();
		for (Lint i = 0; i < m_user_count; ++i)
		{
			veci.push_back(m_zhongtusixi[i]);
		}
		WriteKey(pack, veci);

		WriteKey(pack, "m_agang");
		veci.clear();
		for (Lint i = 0; i < m_user_count; ++i)
		{
			veci.push_back(m_agang[i]);
		}
		WriteKey(pack,veci);

		WriteKeyValue(pack, NAME_TO_STR(m_startHu0), m_startHu[0]);
		WriteKeyValue(pack, NAME_TO_STR(m_startHu1), m_startHu[1]);
		WriteKeyValue(pack, NAME_TO_STR(m_startHu2), m_startHu[2]);
		WriteKeyValue(pack, NAME_TO_STR(m_startHu3), m_startHu[3]);

		WriteKey(pack, "m_mgang");
		veci.clear();
		for (Lint i = 0; i < m_user_count; ++i)
		{
			veci.push_back(m_mgang[i]);
		}
		WriteKey(pack,veci);
		
		WriteKey(pack, "m_dmgang");
		veci.clear();
		for (Lint i = 0; i < m_user_count; ++i)
		{
			veci.push_back(m_dmgang[i]);
		}
		WriteKey(pack, veci);


		WriteKey(pack, "m_dgang");
		veci.clear();
		for (Lint i = 0; i < m_user_count; ++i)
		{
			veci.push_back(m_dgang[i]);
		}
		WriteKey(pack,veci);

		WriteKey(pack, "m_score");
		veci.clear();
		for (Lint i = 0; i < m_user_count; ++i)
		{
			veci.push_back(m_score[i]);
		}
		WriteKey(pack,veci);

		WriteKey(pack, "array0");
		std::vector<CardValue> vec;
		for (Lint i = 0; i < m_count[0]; ++i)
		{
			vec.push_back(m_card[0][i]);
		}
		WriteKey(pack, vec);

		WriteKey(pack, "array1");
		vec.clear();
		for (Lint i = 0; i < m_count[1]; ++i)
		{
			vec.push_back(m_card[1][i]);
		}
		WriteKey(pack, vec);

		WriteKey(pack, "array2");
		vec.clear();
		for (Lint i = 0; i < m_count[2]; ++i)
		{
			vec.push_back(m_card[2][i]);
		}
		WriteKey(pack, vec);

		WriteKey(pack, "array3");
		vec.clear();
		for (Lint i = 0; i < m_count[3]; ++i)
		{
			vec.push_back(m_card[3][i]);
		}
		WriteKey(pack, vec);

		WriteKeyValue(pack, NAME_TO_STR(m_hucards1), m_hucards[0]);
		WriteKeyValue(pack, NAME_TO_STR(m_hucards2), m_hucards[1]);
		WriteKeyValue(pack, NAME_TO_STR(m_hucards3), m_hucards[2]);
		WriteKeyValue(pack, NAME_TO_STR(m_hucards4), m_hucards[3]);

		WriteKeyValue(pack, NAME_TO_STR(m_bird_infos), m_bird_infos);

		return true;
	}

	virtual LMsg* Clone(){return new LMsgS2CGameOver();}
};


//////////////////////////////////////////////////////////////////////////
//客户端请求退出房间
struct LMsgC2SUserOutRoom:public LMsgSC
{
	Lint m_pos;//准备玩家的位置

	LMsgC2SUserOutRoom():LMsgSC(MSG_C_2_S_USER_OUT_ROOM){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_pos), m_pos);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);

		return true;
	}

	virtual LMsg* Clone(){return new LMsgC2SUserOutRoom();}
};

//////////////////////////////////////////////////////////////////////////
//服务返回退出结果
struct LMsgS2CUserOutRoom:public LMsgSC
{
	Lint		m_errorCode;//0-成功，1-失败
	Lint		m_pos;
	
	LMsgS2CUserOutRoom():LMsgSC(MSG_S_2_C_USER_OUT_ROOM){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_pos), m_pos);
		ReadMapData(obj, NAME_TO_STR(m_errorCode), m_errorCode);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);
		WriteKeyValue(pack, NAME_TO_STR(m_errorCode), m_errorCode);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgS2CUserOutRoom();}
};


//////////////////////////////////////////////////////////////////////////
//服务器发送起手胡消息

struct StartHuInfo
{
	Lint	m_type;
	std::vector<CardValue> m_card;

	MSGPACK_DEFINE(m_type, m_card); 
};

struct LMsgS2CUserStartHu:public LMsgSC
{
	std::vector<StartHuInfo> m_card;

	LMsgS2CUserStartHu():LMsgSC(MSG_S_2_C_START_HU){}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_card), m_card);

		return true;
	}

	virtual LMsg* Clone(){return new LMsgS2CUserStartHu();}
};

//////////////////////////////////////////////////////////////////////////
//服务返回退出结果
struct LMsgC2SUserStartHuSelect:public LMsgSC
{
	Lint		m_type;
	std::vector<CardValue> m_card;

	LMsgC2SUserStartHuSelect():LMsgSC(MSG_C_2_S_START_HU_SELECT){}

	virtual bool Read(msgpack::object& obj)
	{

		ReadMapData(obj, NAME_TO_STR(m_type), m_type);
		//ReadMapData(obj, NAME_TO_STR(m_card), m_card);
		msgpack::object array;
		ReadMapData(obj, NAME_TO_STR(m_card), array);
		if (array.type == MSGPACK_OBJECT_ARRAY)
		{
			Lint m_count = array.via.array.size;
			for (Lsize i = 0; i < array.via.array.size; ++i)
			{
				CardValue v;
				msgpack::object& obj =  *(array.via.array.ptr+i);
				obj.convert(v);
				m_card.push_back(v);
			}
		}
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		return true;
	}

	virtual LMsg* Clone(){return new LMsgC2SUserStartHuSelect();}
};

//////////////////////////////////////////////////////////////////////////
//服务广播玩家操作
struct LMsgS2CUserStartHuSelect:public LMsgSC
{
	Lint		m_pos;
	Lint		m_type;
	std::vector<CardValue> m_card;

	LMsgS2CUserStartHuSelect():LMsgSC(MSG_S_2_C_START_HU_SELECT){}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 4);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_type), m_type);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);
		WriteKeyValue(pack, NAME_TO_STR(m_card), m_card);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgS2CUserStartHuSelect();}
};

//////////////////////////////////////////////////////////////////////////
//玩家杠牌
struct LMsgS2CUserGangCard:public LMsgSC
{
	Lint		m_pos;
	Lint		m_flag;//0-没有自摸，1-自摸
	std::vector<CardValue> m_card;

	LMsgS2CUserGangCard():LMsgSC(MSG_S_2_C_GANG_RESULT){}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 4);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_flag), m_flag);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);
		WriteKeyValue(pack, NAME_TO_STR(m_card), m_card);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgS2CUserGangCard();}
};

struct gang_think{
	CardValue m_gang_card;//杠出的牌
	std::vector<ThinkData> m_think;//思考
	MSGPACK_DEFINE(m_gang_card, m_think); 
};

//////////////////////////////////////////////////////////////////////////
//玩家杠牌思考
struct LMsgS2CUserGangThinkCard:public LMsgSC
{
	Lint		m_pos;
	CardValue	m_gang;
	std::vector<gang_think> m_card;

	LMsgS2CUserGangThinkCard():LMsgSC(MSG_S_2_C_GANG_THINK),m_pos(0){}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 4);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);
		WriteKeyValue(pack, NAME_TO_STR(m_gang), m_gang);
		WriteKeyValue(pack, NAME_TO_STR(m_card), m_card);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgS2CUserGangThinkCard();}
};

//玩家飘思考
struct LMsgS2CPiaoSelect :public LMsgSC
{
	LMsgS2CPiaoSelect() :LMsgSC(MSG_S_2_C_Piao_Select){}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 1);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CPiaoSelect(); }
};

//玩家飘思考
struct LMsgC2SPiaoSelect :public LMsgSC
{
	Lint m_position;
	Lint m_piao_count;
	LMsgC2SPiaoSelect() :LMsgSC(MSG_C_2_S_Piao_Select), m_position(0),m_piao_count(0) {}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_piao_count), m_piao_count);
		ReadMapData(obj, NAME_TO_STR(m_position), m_position);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		return true;
	}

	virtual LMsg* Clone() { return new LMsgC2SPiaoSelect(); }
};


//玩家飘思考
struct LMsgS2CPiaoCount:public LMsgSC
{
	std::vector<Lint> m_piao;
	LMsgS2CPiaoCount():LMsgSC(MSG_S_2_C_Piao_Count) {}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_piao), m_piao);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CPiaoCount(); }
};



//////////////////////////////////////////////////////////////////////////
//服务器广播玩家选择海底牌
struct LMsgS2CUserEndCardSelect:public LMsgSC
{
	Lint		m_pos;
	Lint		m_time;

	LMsgS2CUserEndCardSelect():LMsgSC(MSG_S_2_C_END_CARD_SELECT){}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);
		WriteKeyValue(pack, NAME_TO_STR(m_time), m_time);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgS2CUserEndCardSelect();}
};

//服务器广播玩家选择海底牌 //Add by lidm for TuiDaoHu[2017-05-11]
struct LMsgS2CUserEndCardSelect_Ting :public LMsgSC
{
	Lint		m_pos;
	Lint		m_time;
	bool		m_ting;

	LMsgS2CUserEndCardSelect_Ting() :LMsgSC(MSG_S_2_C_END_CARD_SELECT_TING) {}//74

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 4);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);
		WriteKeyValue(pack, NAME_TO_STR(m_time), m_time);
		WriteKeyValue(pack, NAME_TO_STR(m_ting), m_ting);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CUserEndCardSelect_Ting(); }
};

//Add by lidm [2017-05-11]
//////////////////////////////////////////////////////////////////////////
//服务器广播玩家掷骰子
struct LMsgS2CUserPlayDice :public LMsgSC
{
	Lint		m_seed1;
	Lint		m_seed2;
	Lint		m_position;

	LMsgS2CUserPlayDice() :LMsgSC(MSG_S_2_C_PLAY_DICE) {}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 4);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_seed1), m_seed1);
		WriteKeyValue(pack, NAME_TO_STR(m_seed2), m_seed2);
		WriteKeyValue(pack, NAME_TO_STR(m_position), m_position);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CUserPlayDice(); }
};

//////////////////////////////////////////////////////////////////////////
//客户的选择海底
struct LMsgC2SUserEndCardSelect:public LMsgSC
{
	Lint		m_flag;//0-不要，1-要

	LMsgC2SUserEndCardSelect():LMsgSC(MSG_C_2_S_END_SELECT){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_flag), m_flag);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		return true;
	}

	virtual LMsg* Clone(){return new LMsgC2SUserEndCardSelect();}
};


//////////////////////////////////////////////////////////////////////////
//服务器广播玩家摸海底
struct LMsgS2CUserEndCardGet:public LMsgSC
{
	Lint		m_pos;	//位置
	Lint		m_flag;//是否自摸 0-没有，1-自摸
	CardValue	m_card;

	LMsgS2CUserEndCardGet():LMsgSC(MSG_S_2_C_END_GET){}

	virtual bool Read(msgpack::object& obj)
	{
		//ReadMapData(obj, NAME_TO_STR(m_flag), m_flag);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 5);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);
		WriteKeyValue(pack, NAME_TO_STR(m_flag), m_flag);
		m_card.Write(pack);
		return true;
	}

	virtual LMsg* Clone(){return new LMsgS2CUserEndCardGet();}
};

//////////////////////////////////////////////////////////////////////////
//客户端请求说话
struct LMsgC2SUserSpeak:public LMsgSC
{
	Lint		m_type;//说话类型，0-表情，1-语音,2-文字
	Lint		m_id;	//表情id
	Lstring		m_musicUrl; //语音地址链接
	Lstring		m_msg;//聊天文字

	LMsgC2SUserSpeak() :LMsgSC(MSG_C_2_S_USER_SPEAK){ }

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_type), m_type);
		ReadMapData(obj, NAME_TO_STR(m_id), m_id);
		ReadMapData(obj, NAME_TO_STR(m_musicUrl), m_musicUrl);
		ReadMapData(obj, NAME_TO_STR(m_msg), m_msg);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 5);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_type), m_type);
		WriteKeyValue(pack, NAME_TO_STR(m_id), m_id);
		WriteKeyValue(pack, NAME_TO_STR(m_musicUrl), m_musicUrl);
		WriteKeyValue(pack, NAME_TO_STR(m_msg), m_msg);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgC2SUserSpeak(); }
};

//////////////////////////////////////////////////////////////////////////
//活动协议
struct LMsgS2CActiveOpen:public LMsgSC
{
	Lint		m_activeID;			//活动ID

	LMsgS2CActiveOpen() :LMsgSC(MSG_S_2_C_ACTIVE_OPEN), m_activeID(0){ }

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_activeID), m_activeID);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_activeID), m_activeID);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CActiveOpen(); }
};

struct LMsgC2SActiveInfoRequest:public LMsgSC
{
	Lint		m_activeID;			//活动ID

	LMsgC2SActiveInfoRequest() :LMsgSC(MSG_C_2_S_ACTIVE_INFO){ }

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_activeID), m_activeID);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_activeID), m_activeID);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgC2SActiveInfoRequest(); }
};

struct GiftBasicInfo
{
	Lint		m_type;
	Lint		m_count;
	Lstring		m_name;
	Lstring		m_iconId;

	MSGPACK_DEFINE(m_type, m_count, m_name, m_iconId);

	GiftBasicInfo()
	{
		m_type = 0;
		m_count = 0;
	}


	bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 4);
		WriteKeyValue(pack, NAME_TO_STR(m_type), m_type);
		WriteKeyValue(pack, NAME_TO_STR(m_count), m_count);
		WriteKeyValue(pack, NAME_TO_STR(m_name), m_name);
		WriteKeyValue(pack, NAME_TO_STR(m_iconId), m_iconId);
		return true;
	}
};

struct DrawBroadcastInfo
{
	Lstring		m_userID;
	Lstring		m_prizeName;

	MSGPACK_DEFINE(m_userID, m_prizeName);

	bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_userID), m_userID);
		WriteKeyValue(pack, NAME_TO_STR(m_prizeName), m_prizeName);
		return true;
	}
};

struct LMsgS2CActiveInfo:public LMsgSC
{
	Lint						m_activeID;			//活动ID
//	std::vector<GiftBasicInfo>	m_gifts;			//本次活动奖品的基本信息

	Lint						m_activeLogId;
	Lint						m_RewardID;			//1，2，3，4
	Lint						m_LastJoinDate;		//日期
	Lint						m_NeedPhoneNum; 	//0不需要   1需要留电话 2分享

	std::vector<DrawBroadcastInfo>	m_BroadcastInfos;

	LMsgS2CActiveInfo() :LMsgSC(MSG_S_2_C_ACTIVE_INFO), m_activeID(0), m_activeLogId(0), m_RewardID(0), m_LastJoinDate(0), m_NeedPhoneNum(0){ }

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_activeID), m_activeID);
//		ReadMapData(obj, NAME_TO_STR(m_gifts), m_gifts);
		ReadMapData(obj, NAME_TO_STR(m_activeLogId), m_activeLogId);
		ReadMapData(obj, NAME_TO_STR(m_RewardID), m_RewardID);
		ReadMapData(obj, NAME_TO_STR(m_LastJoinDate), m_LastJoinDate);
		ReadMapData(obj, NAME_TO_STR(m_NeedPhoneNum), m_NeedPhoneNum);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 7);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_activeID), m_activeID);
/*
		WriteKey(pack, NAME_TO_STR(m_gifts));
		WriteArray(pack, m_gifts.size());
		for (int i = 0; i < m_gifts.size(); i++)
			m_gifts[i].Write(pack);*/
		WriteKeyValue(pack, NAME_TO_STR(m_activeLogId), m_activeLogId);
		WriteKeyValue(pack, NAME_TO_STR(m_RewardID), m_RewardID);
		WriteKeyValue(pack, NAME_TO_STR(m_LastJoinDate), m_LastJoinDate);
		WriteKeyValue(pack, NAME_TO_STR(m_NeedPhoneNum), m_NeedPhoneNum);

		WriteKey(pack, NAME_TO_STR(m_BroadcastInfos));
		WriteArray(pack, m_BroadcastInfos.size());
		for (int i = 0; i < m_BroadcastInfos.size(); i++)
			m_BroadcastInfos[i].Write(pack);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CActiveInfo(); }
};

struct LMsgC2SRequestDraw:public LMsgSC
{
	Lint		m_activeID;			//活动ID
	LMsgC2SRequestDraw() :LMsgSC(MSG_C_2_S_REQUEST_DRAW){ }

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_activeID), m_activeID);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_activeID), m_activeID);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgC2SRequestDraw(); }
};


struct LMsgC2SDrawRegBroadcast:public LMsgSC
{
	Lint						m_activeID;

	LMsgC2SDrawRegBroadcast() :LMsgSC(MSG_C_2_S_DRAW_REGBROADCAST) { }

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_activeID), m_activeID);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_activeID), m_activeID);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgC2SDrawRegBroadcast(); }
};

struct LMsgC2SDrawCancelBroadcast :public LMsgSC
{
	Lint						m_activeID;

	LMsgC2SDrawCancelBroadcast() :LMsgSC(MSG_C_2_S_DRAW_CANCELBROADCAST) { }

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_activeID), m_activeID);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_activeID), m_activeID);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgC2SDrawCancelBroadcast(); }
};

struct LMsgS2CDrawBroadcast :public LMsgSC
{
	Lint						m_activeID;
	Lint                        m_type;
	std::vector<DrawBroadcastInfo>  m_DrawBroadcastInfos;

	LMsgS2CDrawBroadcast() :LMsgSC(MSG_S_2_C_DRAW_BROADCAST), m_activeID(0), m_type(0) { }

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_activeID), m_activeID);
		ReadMapData(obj, NAME_TO_STR(m_type), m_type);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 4);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_activeID), m_activeID);
		WriteKeyValue(pack, NAME_TO_STR(m_type), m_type);
		WriteKey(pack, NAME_TO_STR(m_DrawBroadcastInfos));
		WriteArray(pack, m_DrawBroadcastInfos.size());
		for (int i = 0; i < m_DrawBroadcastInfos.size(); i++)
			m_DrawBroadcastInfos[i].Write(pack);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CDrawBroadcast(); }
};

struct LMsgS2CDrawCancelBroadcast :public LMsgSC
{
	Lint						m_activeID;
	Lint                        m_errorCode;

	LMsgS2CDrawCancelBroadcast() :LMsgSC(MSG_S_2_C_DRAW_CANCELBROADCAST), m_activeID(0), m_errorCode(0) { }

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_activeID), m_activeID);
		ReadMapData(obj, NAME_TO_STR(m_errorCode), m_errorCode);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_activeID), m_activeID);
		WriteKeyValue(pack, NAME_TO_STR(m_errorCode), m_errorCode);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CDrawCancelBroadcast(); }
};

struct LMsgC2SShareDraw : public LMsgSC          //客户端请求分享成功，m_msgId = 224
{
	Lint		m_activeLogId;		// 指定抽奖记录ID
	Lint		m_activeID;		//活动ID

	LMsgC2SShareDraw() :LMsgSC(MSG_C_2_S_SHARE_DRAW) { }

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_activeID), m_activeID);
		ReadMapData(obj, NAME_TO_STR(m_activeLogId), m_activeLogId);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_activeID), m_activeID);
		WriteKeyValue(pack, NAME_TO_STR(m_activeLogId), m_activeLogId);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgC2SShareDraw(); }

};

struct LMsgS2CShareDraw :public LMsgSC         //服务器回复分享成功，m_msgId = 225
{
	Lint		m_activeLogId;		// 指定抽奖记录ID
	Lint		m_activeID;		//活动ID
	Lint		m_errorCode;		//0:成功，1：没有此中奖纪录，2：抽奖活动不匹配

	LMsgS2CShareDraw() :LMsgSC(MSG_S_2_C_SHARE_DRAW) { }

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_activeID), m_activeID);
		ReadMapData(obj, NAME_TO_STR(m_activeLogId), m_activeLogId);
		ReadMapData(obj, NAME_TO_STR(m_errorCode), m_errorCode);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 4);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_activeID), m_activeID);
		WriteKeyValue(pack, NAME_TO_STR(m_activeLogId), m_activeLogId);
		WriteKeyValue(pack, NAME_TO_STR(m_errorCode), m_errorCode);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CShareDraw(); }
};

struct LMsgS2CFinishDraw:public LMsgSC
{
	Lint		m_activeID;			//活动ID
	Lint		m_errorCode;			//错误码
	Lint		m_RewardID;			//1，2，3，4
	Lint		m_date;;			//1，2，3，4
	Lint		m_NeedPhoneNum;		//是否需要电话
	LMsgS2CFinishDraw() :LMsgSC(MSG_S_2_C_FINISH_DRAW), m_activeID(0), m_RewardID(0), m_date(0), m_NeedPhoneNum(0){ }

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_activeID), m_activeID);
		ReadMapData(obj, NAME_TO_STR(m_RewardID), m_RewardID);
		ReadMapData(obj, NAME_TO_STR(m_errorCode), m_errorCode);
		ReadMapData(obj, NAME_TO_STR(m_date), m_date);
		ReadMapData(obj, NAME_TO_STR(m_NeedPhoneNum), m_NeedPhoneNum);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 6);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_activeID), m_activeID);
		WriteKeyValue(pack, NAME_TO_STR(m_RewardID), m_RewardID);
		WriteKeyValue(pack, NAME_TO_STR(m_errorCode), m_errorCode);
		WriteKeyValue(pack, NAME_TO_STR(m_date), m_date);
		WriteKeyValue(pack, NAME_TO_STR(m_NeedPhoneNum), m_NeedPhoneNum);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CFinishDraw(); }
};

struct LMsgC2SWritePhone : public LMsgSC
{
	Lint		m_activeLogId;		// 0:最新抽奖记录，>0指定抽奖记录
	Lint		m_activeID;			//活动ID
	Lstring		m_phoneNum;		//日期
	LMsgC2SWritePhone() :LMsgSC(MSG_C_2_S_WRITE_PHONE), m_activeLogId(0), m_activeID(0)
	{ 
	}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_activeLogId), m_activeLogId);
		ReadMapData(obj, NAME_TO_STR(m_activeID), m_activeID);
		ReadMapData(obj, NAME_TO_STR(m_phoneNum), m_phoneNum);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 4);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_activeLogId), m_activeLogId);
		WriteKeyValue(pack, NAME_TO_STR(m_activeID), m_activeID);
		WriteKeyValue(pack, NAME_TO_STR(m_phoneNum), m_phoneNum);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgC2SWritePhone(); }
};


struct LMsgS2CWritePhone:public LMsgSC
{
	Lint		m_activeLogId;		// 指定抽奖记录ID
	Lint		m_activeID;		//活动ID
	Lint		m_errorCode;		//0:成功，1：没有此中奖纪录，2：抽奖活动不匹配，3：手机号码格式不符
	Lstring		m_PhoneNum;			//电话
	LMsgS2CWritePhone() :LMsgSC(MSG_S_2_C_WRITE_PHONE), m_activeLogId(0), m_activeID(0), m_errorCode(0){ }

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_activeLogId), m_activeLogId);
		ReadMapData(obj, NAME_TO_STR(m_activeID), m_activeID);
		ReadMapData(obj, NAME_TO_STR(m_errorCode), m_errorCode);
		ReadMapData(obj, NAME_TO_STR(m_PhoneNum), m_PhoneNum);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 5);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_activeLogId), m_activeLogId);
		WriteKeyValue(pack, NAME_TO_STR(m_activeID), m_activeID);
		WriteKeyValue(pack, NAME_TO_STR(m_errorCode), m_errorCode);
		WriteKeyValue(pack, NAME_TO_STR(m_PhoneNum), m_PhoneNum);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CWritePhone(); }
};

struct LMsgC2SActiveLog:public LMsgSC
{
	Lint		m_activeID;		//活动ID

	LMsgC2SActiveLog() :LMsgSC(MSG_C_2_S_ACTIVE_LOG){ }

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_activeID), m_activeID);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_activeID), m_activeID);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgC2SActiveLog(); }
};
struct LActiveInfo
{
	Lint	m_id;
	Lint	m_rewardID;
	Lint	m_date;
	Lstring	m_phoneNum;
	Lint    m_state;     ////1等待分享，2等待输入手机号，3领取完成
	MSGPACK_DEFINE(m_id, m_rewardID, m_date,m_phoneNum, m_state);
	LActiveInfo()
	{
		m_id = 0;
		m_rewardID = 0;
		m_date = 0;
		m_state = 0;
	}

	bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_id), m_id);
		ReadMapData(obj, NAME_TO_STR(m_rewardID), m_rewardID);
		ReadMapData(obj, NAME_TO_STR(m_date), m_date);
		ReadMapData(obj, NAME_TO_STR(m_phoneNum), m_phoneNum);
		ReadMapData(obj, NAME_TO_STR(m_state), m_state);
		return true;
	}

	bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteKeyValue(pack, NAME_TO_STR(m_id), m_id);
		WriteKeyValue(pack, NAME_TO_STR(m_rewardID), m_rewardID);
		WriteKeyValue(pack, NAME_TO_STR(m_date), m_date);
		WriteKeyValue(pack, NAME_TO_STR(m_phoneNum), m_phoneNum);
		WriteKeyValue(pack, NAME_TO_STR(m_state), m_state);
		return true;
	}
};
struct LMsgS2CDrawInfo:public LMsgSC
{
	Lint		m_activeID;			//活动ID
	std::vector<LActiveInfo>	m_DrawInfo;
	LMsgS2CDrawInfo() :LMsgSC(MSG_S_2_C_ACTIVE_LOG), m_activeID(0){ }

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_activeID), m_activeID);
		ReadMapData(obj, NAME_TO_STR(m_DrawInfo), m_DrawInfo);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_activeID), m_activeID);
		WriteKeyValue(pack, NAME_TO_STR(m_DrawInfo), m_DrawInfo);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CDrawInfo(); }
};


//////////////////////////////////////////////////////////////////////////
//服务广播操作结果
struct LMsgS2CUserSpeak:public LMsgSC
{
	Lint		m_userId;//说话人id
	Lint		m_pos;//说话人的位置
	Lint		m_type;//说话类型
	Lint		m_id;//类型id
	Lstring		m_musicUrl;//语音url链接
	Lstring		m_msg;//聊天文字

	LMsgS2CUserSpeak() :LMsgSC(MSG_S_2_C_USER_SPEAK){ }

	
	virtual bool Read(msgpack::object& obj)
	{
		//ReadMapData(obj, NAME_TO_STR(m_pos), m_pos);
		//ReadMapData(obj, NAME_TO_STR(m_errorCode), m_errorCode);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 7);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_userId), m_userId);
		WriteKeyValue(pack, NAME_TO_STR(m_pos), m_pos);
		WriteKeyValue(pack, NAME_TO_STR(m_type), m_type);
		WriteKeyValue(pack, NAME_TO_STR(m_id), m_id);
		WriteKeyValue(pack, NAME_TO_STR(m_musicUrl), m_musicUrl);
		WriteKeyValue(pack, NAME_TO_STR(m_msg), m_msg);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CUserSpeak(); }
};


//////////////////////////////////////////////////////////////////////////
//客户端请求创建桌子
struct LMsgC2SCreateDesk :public LMsgSC
{
	Lint		m_flag;//房间类型，1-2圈，2-四圈，3-8圈
	Lstring		m_secret;//房间密码，如果为空，服务器会随机一个密码
	Lint		m_gold;//房间抵住，单位元，最低为1元，最多不能超过100
	Lint		m_state;//玩法规则 0 转转   1 长沙
	Lint		m_robotNum;		// 0,不加机器人，1，2，3加机器人数量
	CardValue	m_cardValue[136];
	std::vector<Lint>	m_playtype;	//玩法
	std::vector<Lint>	m_playtype_starthu;//起手胡类型
	LMsgC2SCreateDesk() :LMsgSC(MSG_C_2_S_CREATE_ROOM){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_flag), m_flag);
		ReadMapData(obj, NAME_TO_STR(m_secret), m_secret);
		ReadMapData(obj, NAME_TO_STR(m_gold), m_gold);
		ReadMapData(obj, NAME_TO_STR(m_state), m_state);
		ReadMapData(obj, NAME_TO_STR(m_robotNum), m_robotNum);
		msgpack::object array;
		ReadMapData(obj, NAME_TO_STR(m_cardValue), array);
		if (array.type == MSGPACK_OBJECT_ARRAY)
		{
			for (Lsize i = 0; i < array.via.array.size && i < 136; ++i)
			{
				msgpack::object& pv = *(array.via.array.ptr + i);
				pv.convert(m_cardValue[i]);
			}
		}
		ReadMapData(obj, NAME_TO_STR(m_playtype), array);
		if (array.type == MSGPACK_OBJECT_ARRAY)
		{
			Lint m_count = array.via.array.size;
			for (Lsize i = 0; i < array.via.array.size; ++i)
			{
				Lint v;
				msgpack::object& obj =  *(array.via.array.ptr+i);
				obj.convert(v);
				m_playtype.push_back(v);
			}
		}
		ReadMapData(obj, NAME_TO_STR(m_playtype_starthu), array);
		if (array.type == MSGPACK_OBJECT_ARRAY)
		{
			for (Lsize i = 0; i < array.via.array.size; ++i)
			{
				Lint v;
				msgpack::object& obj = *(array.via.array.ptr + i);
				obj.convert(v);
				m_playtype_starthu.push_back(v);
			}
		}
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 7);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_flag), m_flag);
		WriteKeyValue(pack, NAME_TO_STR(m_secret), m_secret);
		WriteKeyValue(pack, NAME_TO_STR(m_gold), m_gold);
		WriteKeyValue(pack, NAME_TO_STR(m_state), m_state);
		WriteKeyValue(pack, NAME_TO_STR(m_robotNum), m_robotNum);
		WriteKeyValue(pack, NAME_TO_STR(m_playtype), m_playtype);
		WriteKeyValue(pack, NAME_TO_STR(m_playtype_starthu), m_playtype_starthu);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgC2SCreateDesk(); }
};

//////////////////////////////////////////////////////////////////////////
//玩家请求创建桌子结果
struct LMsgS2CCreateDeskRet :public LMsgSC
{
	Lint		m_errorCode;//0-成功，1-房卡不够，2-其他未知错误  4 没有logicserv可以分配 3创建失败，请重新创建
	Lint		m_deskId;//桌子id

	LMsgS2CCreateDeskRet() :LMsgSC(MSG_S_2_C_CREATE_ROOM){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_errorCode), m_errorCode);
		ReadMapData(obj, NAME_TO_STR(m_deskId), m_deskId);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_errorCode), m_errorCode);
		WriteKeyValue(pack, NAME_TO_STR(m_deskId), m_deskId);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CCreateDeskRet(); }
};


//////////////////////////////////////////////////////////////////////////
//客户端加入桌子
struct LMsgC2SAddDesk :public LMsgSC
{
	Lint		m_deskId;//桌子id

	LMsgC2SAddDesk() :LMsgSC(MSG_C_2_S_ADD_ROOM){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_deskId), m_deskId);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_deskId), m_deskId);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgC2SAddDesk(); }
};

//////////////////////////////////////////////////////////////////////////
//玩家请求加入桌子结果
struct LMsgS2CAddDeskRet :public LMsgSC
{
	Lint		m_errorCode;//0-成功，1-人已满,2-房间不存在,3-未知错误
	Lint		m_deskId;//桌子号码
	
	LMsgS2CAddDeskRet() :LMsgSC(MSG_S_2_C_ADD_ROOM){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_errorCode), m_errorCode);
		ReadMapData(obj, NAME_TO_STR(m_deskId), m_deskId);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_errorCode), m_errorCode);
		WriteKeyValue(pack, NAME_TO_STR(m_deskId), m_deskId);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CAddDeskRet(); }
};


//////////////////////////////////////////////////////////////////////////
//vip比赛结束
struct LMsgS2CVipEnd :public LMsgSC
{
	Lint	m_id[4];//玩家id
	Lstring	m_nike[4];//游戏玩家昵称
	Lint	m_gold[4];//输赢积分总数
	Lint	m_zimo[4];//自摸次数
	Lint	m_bomb[4];//放炮次数
	Lint	m_win[4];//收炮次数
	Lint	m_mgang[4];//明杠次数
	Lint	m_agang[4];//暗杠的次数

	Lint	m_dzimo[4];//大胡自摸次数
	Lint	m_dbomb[4];//大胡放炮次数
	Lint	m_dwin[4];//大胡收炮次数


	LMsgS2CVipEnd() :LMsgSC(MSG_S_2_C_VIP_END){}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 12);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		
		WriteKey(pack,"m_nike");
		std::vector<Lstring>vecs;
		for(Lint i = 0; i < 4; ++i)
		{
			vecs.push_back(m_nike[i]);
		}
		WriteKey(pack,vecs);

		WriteKey(pack,"m_id");
		std::vector<Lint>veci;
		for(Lint i = 0; i < 4; ++i)
		{
			veci.push_back(m_id[i]);
		}
		WriteKey(pack,veci);

		WriteKey(pack,"m_gold");
		veci.clear();
		for(Lint i = 0; i < 4; ++i)
		{
			veci.push_back(m_gold[i]);
		}
		WriteKey(pack,veci);

		WriteKey(pack,"m_zimo");
		veci.clear();
		for(Lint i = 0; i < 4; ++i)
		{
			veci.push_back(m_zimo[i]);
		}
		WriteKey(pack,veci);

		WriteKey(pack,"m_bomb");
		veci.clear();
		for(Lint i = 0; i < 4; ++i)
		{
			veci.push_back(m_bomb[i]);
		}
		WriteKey(pack,veci);

		WriteKey(pack,"m_win");
		veci.clear();
		for(Lint i = 0; i < 4; ++i)
		{
			veci.push_back(m_win[i]);
		}
		WriteKey(pack,veci);

		WriteKey(pack,"m_mgang");
		veci.clear();
		for(Lint i = 0; i < 4; ++i)
		{
			veci.push_back(m_mgang[i]);
		}
		WriteKey(pack,veci);

		WriteKey(pack,"m_agang");
		veci.clear();
		for(Lint i = 0; i < 4; ++i)
		{
			veci.push_back(m_agang[i]);
		}
		WriteKey(pack,veci);

		WriteKey(pack,"m_dzimo");
		veci.clear();
		for(Lint i = 0; i < 4; ++i)
		{
			veci.push_back(m_dzimo[i]);
		}
		WriteKey(pack,veci);

		WriteKey(pack,"m_dbomb");
		veci.clear();
		for(Lint i = 0; i < 4; ++i)
		{
			veci.push_back(m_dbomb[i]);
		}
		WriteKey(pack,veci);

		WriteKey(pack,"m_dwin");
		veci.clear();
		for(Lint i = 0; i < 4; ++i)
		{
			veci.push_back(m_dwin[i]);
		}
		WriteKey(pack,veci);

		return true;
	}


	virtual LMsg* Clone(){ return new LMsgS2CVipEnd(); }
};


struct VipLogItemInfo
{
	Lstring m_id;
	Lint m_time;
	Lint m_userid[4];
	Lstring m_nike[4];
	Lint m_score[4];
	Lint m_reset;//是否解散
	Lint m_deskId;//是否解散
	Lint m_user_count;
	VipLogItemInfo():m_time(0),m_reset(0),m_deskId(0),m_user_count(0){
		memset(m_userid,0,sizeof(m_userid));
		memset(m_score,0,sizeof(m_score));
	}

};

struct VipLog
{
	Lint	m_time;
	Lstring	m_videoId;
	Lint	m_score[4];
	VipLog():m_time(0){
		memset(m_score,0,sizeof(m_score));
	}
};

//////////////////////////////////////////////////////////////////////////
//客户端请求玩家对账单
struct LMsgC2SVipLog :public LMsgSC
{
	Lint		m_time;//id
	Lint		m_userId;//请求某个玩家的战绩
	
	LMsgC2SVipLog() :LMsgSC(MSG_C_2_S_VIP_LOG){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_time), m_time);
		ReadMapData(obj, NAME_TO_STR(m_userId), m_userId);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_time), m_time);
		WriteKeyValue(pack, NAME_TO_STR(m_userId), m_userId);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgC2SVipLog(); }
};

//服务器返回玩家对账单
struct LMsgS2CVipLog:public LMsgSC
{
	Lint				m_size;//长度
	VipLogItemInfo		m_info[10];//log信息

	LMsgS2CVipLog() :LMsgSC(MSG_S_2_C_VIP_LOG){}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);

		WriteKey(pack,"m_data");
		WriteArray(pack,m_size);
		for(Lint i = 0 ; i < m_size; ++i)
		{
			WriteMap(pack,5);
			WriteKeyValue(pack,"m_id",m_info[i].m_id);
			WriteKeyValue(pack,"m_time",m_info[i].m_time);
			//WriteKeyValue(pack,"m_reset",m_info[i].m_reset);
			WriteKeyValue(pack,"m_deskId",m_info[i].m_deskId);

			std::vector<Lstring> vecs;
			std::vector<Lint>veci/*,vec*/;
			for(Lint j = 0 ; j < m_info[i].m_user_count; ++j)
			{
				vecs.push_back(m_info[i].m_nike[j]);
				veci.push_back(m_info[i].m_score[j]);
			}

			WriteKey(pack,"m_nike");
			WriteKey(pack,vecs);

			WriteKey(pack,"m_score");
			WriteKey(pack,veci);
		}
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CVipLog(); }
};

//客户端请求某轮对账单
struct LMsgC2SOneVipLog :public LMsgSC
{
	Lstring		m_log_id;//请求某logid的对账单
	Lint		m_userId;

	LMsgC2SOneVipLog() :LMsgSC(MSG_C_2_S_ONE_VIP_LOG),m_userId(0){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_id), m_log_id);
		ReadMapData(obj, NAME_TO_STR(m_userId), m_userId);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		return true;
	}
	virtual LMsg* Clone(){ return new LMsgC2SOneVipLog(); }
};

//服务器返回玩家某轮对账单
struct LMsgS2COneVipLog:public LMsgSC
{
	Lint	m_size;
	VipLog	m_videos[16];
	Lint	m_user_count;

	LMsgS2COneVipLog() :LMsgSC(MSG_S_2_C_ONE_VIP_LOG),m_user_count(0){}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);

		WriteKey(pack,"m_match");
		WriteArray(pack,m_size);
		for(Lint k = 0 ; k < m_size; ++k)
		{
			WriteMap(pack,3);
			WriteKeyValue(pack,"m_time",m_videos[k].m_time);
			WriteKeyValue(pack,"m_videoId",m_videos[k].m_videoId);

			std::vector<Lint> vec;
			for(Lint n = 0 ; n < m_user_count; ++n)
			{
				vec.push_back(m_videos[k].m_score[n]);
			}
			WriteKey(pack,"m_score");
			WriteKey(pack,vec);
		}
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2COneVipLog(); }
};

//客户端请求录像
struct LMsgC2SVideo :public LMsgSC
{
	Lstring		m_videoId;//id

	LMsgC2SVideo() :LMsgSC(MSG_C_2_S_VIDEO){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_videoId), m_videoId);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_videoId), m_videoId);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgC2SVideo(); }
};

//////////////////////////////////////////////////////////////////////////
//vip对账结果

struct LMsgS2CVideo:public LMsgSC
{
	VideoLog		m_video;//log信息
	Lint			m_sex[4];
	Lstring			m_nike[4];
	Lstring			m_imageUrl[4];
	Lint			m_zhuang;
	Lint			m_deskId;
	Lint			m_curCircle;
	Lint			m_maxCircle;
	Lint			m_flag;
	Lint			m_score[4];
	Lint			m_user_count;
	LMsgS2CVideo() :LMsgSC(MSG_S_2_C_VIDEO),m_user_count(4){
		
	}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 14+m_user_count);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);

		WriteKeyValue(pack, NAME_TO_STR(m_zhuang), m_zhuang);
		WriteKeyValue(pack, NAME_TO_STR(m_deskId), m_deskId);
		WriteKeyValue(pack, NAME_TO_STR(m_curCircle), m_curCircle);
		WriteKeyValue(pack, NAME_TO_STR(m_maxCircle), m_maxCircle);
		WriteKeyValue(pack, NAME_TO_STR(m_state), m_flag);

		std::vector<Lint>vecid;
		std::vector<Lint>vecsex;
		std::vector<Lint>vecscore;
		std::vector<Lstring>vecnike;
		std::vector<Lstring>vecurl;

		for(Lint i = 0 ; i < m_user_count; ++i)
		{
			vecid.push_back(m_video.m_userId[i]);
			vecnike.push_back(m_nike[i]);
			vecsex.push_back(m_sex[i]);
			vecurl.push_back(m_imageUrl[i]);
			vecscore.push_back(m_score[i]);
		}

		WriteKey(pack,"m_score");
		WriteKey(pack,vecscore);

		WriteKey(pack,"m_userid");
		WriteKey(pack,vecid);

		WriteKey(pack,"m_nike");
		WriteKey(pack, vecnike);

		WriteKey(pack, "m_sex");
		WriteKey(pack, vecsex);

		WriteKey(pack, "m_imageUrl");
		WriteKey(pack, vecurl);

		WriteKey(pack,"m_time");
		WriteKey(pack,m_video.m_time);

		WriteKey(pack,"m_oper");
		WriteKey(pack,m_video.m_oper);

		WriteKey(pack,"m_playtype");
		WriteKey(pack,m_video.m_playType);

		for(Lint i = 0 ; i < m_user_count; ++i)
		{
			std::stringstream ss ;
			ss << "m_card" << i;
			WriteKey(pack,ss.str());
			WriteKey(pack,m_video.m_handCard[i]);
		}

		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CVideo(); }
};

//////////////////////////////////////////////////////////////////////////
//同步vip房间信息
struct LMsgS2CVipInfo :public LMsgSC
{
	Lint			m_curCircle;//当前局数
	Lint			m_curMaxCircle;//最大局数

	LMsgS2CVipInfo() :LMsgSC(MSG_S_2_C_VIP_INFO){}

	virtual bool Read(msgpack::object& obj)
	{
		//ReadMapData(obj, NAME_TO_STR(m_errorCode), m_errorCode);
		//ReadMapData(obj, NAME_TO_STR(m_deskId), m_deskId);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_curCircle), m_curCircle);
		WriteKeyValue(pack, NAME_TO_STR(m_curMaxCircle), m_curMaxCircle);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CVipInfo(); }
};


//服务器广播玩家扎鸟信息
struct LMsgS2CZhaBirdShow:public LMsgSC
{
	Lint    m_type;  //0:扎鸟 1:飞鸟
	Lint	m_end_pos;	
	std::vector<BirdInfo>	m_bird_infos;	//鸟牌

	LMsgS2CZhaBirdShow():LMsgSC(MSG_S_2_C_ZHA_BIRD),m_end_pos(0),m_type(0){}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 4);
		WriteKeyValue(pack, NAME_TO_STR(m_type), m_type);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_end_pos), m_end_pos);
		WriteKeyValue(pack, NAME_TO_STR(m_bird_infos), m_bird_infos);
		
		
		return true;
	}

	virtual LMsg* Clone(){return new LMsgS2CZhaBirdShow();}
};

//服务器广播王霸牌信息
struct LMsgS2CWangBa :public LMsgSC
{
	CardValue m_Wang_Ba;	//王霸牌

	bool m_ShangWang;
	bool m_XiaWang;

	LMsgS2CWangBa() :LMsgSC(MSG_S_2_C_Wang_Ba), m_ShangWang(false), m_XiaWang(false) {}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 5);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_ShangWang), m_ShangWang);
		WriteKeyValue(pack, NAME_TO_STR(m_XiaWang), m_XiaWang);
		m_Wang_Ba.Write(pack);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CWangBa(); }
};

//请求玩法信息
struct LMsgC2SReqGameTypeInfo : public LMsgSC
{
	LMsgC2SReqGameTypeInfo() :LMsgSC(MSG_C_2_S_GETGAMETYPEINFO) {}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		return true;
	}

	virtual LMsg* Clone() { return new LMsgC2SReqGameTypeInfo(); }
};

struct GameTypeInfo {
	Lint m_id;//玩法id
	bool m_timeLimitFree;//是否限免
	Lint m_timeLimitStart;//限免开始时间（m_timeLimitFree为true时有效）
	Lint m_timeLimitEnd;//限免结束时间（m_timeLimitFree为true时有效）
	GameTypeInfo():m_id(0), m_timeLimitFree(false), m_timeLimitStart(0), m_timeLimitEnd(0) {}

	MSGPACK_DEFINE(m_id, m_timeLimitFree, m_timeLimitStart, m_timeLimitEnd);
	void	Read(LBuff& buff) {
		buff.Read(m_id);
		buff.Read(m_timeLimitFree);
		buff.Read(m_timeLimitStart);
		buff.Read(m_timeLimitEnd);
	}
	void	Write(LBuff& buff) {
		buff.Write(m_id);
		buff.Write(m_timeLimitFree);
		buff.Write(m_timeLimitStart);
		buff.Write(m_timeLimitEnd);
	}

	bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack,4);
		WriteKeyValue(pack, NAME_TO_STR(m_id), m_id);
		WriteKeyValue(pack, NAME_TO_STR(m_timeLimitFree), m_timeLimitFree);
		WriteKeyValue(pack, NAME_TO_STR(m_timeLimitStart), m_timeLimitStart);
		WriteKeyValue(pack, NAME_TO_STR(m_timeLimitEnd), m_timeLimitEnd);
		return true;
	}
};

//服务器返回玩法信息
struct LMsgS2CGameTypeInfo : public LMsgSC
{
	std::vector<GameTypeInfo> m_gameTypeInfos;//玩法信息

	LMsgS2CGameTypeInfo() :LMsgSC(MSG_S_2_C_GETGAMETYPEINFO) {}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);

		WriteKey(pack, NAME_TO_STR(m_gameTypeInfos));
		WriteArray(pack, m_gameTypeInfos.size());
		for (Lint i = 0; i < m_gameTypeInfos.size(); i++)
		{
			m_gameTypeInfos[i].Write(pack);
		}
		return true;
	}
};

struct LMsgC2SCheckUserQualification : public LMsgSC
{
	Lstring m_unionId;
	Lint m_type;//1,给代理投票

	LMsgC2SCheckUserQualification(): LMsgSC(MSG_C_2_S_CHECK_USER_QUALIFICATION) {}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_unionId), m_unionId)
		ReadMapData(obj, NAME_TO_STR(m_type), m_type)
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		return true;
	}

	virtual LMsg* Clone() { return new LMsgC2SCheckUserQualification(); }
};

struct LMsgS2CCheckUserQualification :public LMsgSC
{
	Lstring m_unionId;
	Lint m_type;
	Lint m_errorCode;//0.成功，1.类型不支持，2.不是老用户，3.参与把数不够

	LMsgS2CCheckUserQualification() :LMsgSC(MSG_S_2_C_CHECK_USER_QUALIFICATION) {}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 4);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_unionId), m_unionId);
		WriteKeyValue(pack, NAME_TO_STR(m_type), m_type);
		WriteKeyValue(pack, NAME_TO_STR(m_errorCode), m_errorCode);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CCheckUserQualification(); }
};

struct LMsgS2CNotifyUserQualification :public LMsgSC
{
	std::vector<Lint> m_type;//活动类型1.代理招募

	LMsgS2CNotifyUserQualification() :LMsgSC(MSG_S_2_C_NOTIFY_USER_QUALIFICATION) {}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_type), m_type);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CNotifyUserQualification(); }
};

//玩家通过精确的videoid查看分享的某录像
struct LMsgC2SGetShareVideo :public LMsgSC
{
	Lstring		m_videoId;//id

	LMsgC2SGetShareVideo() :LMsgSC(MSG_C_2_S_GETSHAREVIDEO){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_videoId), m_videoId);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_videoId), m_videoId);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgC2SGetShareVideo(); }
};

//玩家请求查看某shareid的分享录像
struct LMsgC2SShareVideo :public LMsgSC
{
	Lint		m_shareID;//id

	LMsgC2SShareVideo() :LMsgSC(MSG_C_2_S_SHAREVIDEO),m_shareID(0){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_shareID), m_shareID);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_shareID), m_shareID);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgC2SShareVideo(); }
};

//玩家请求分享某录像
struct LMsgC2SReqShareVideo :public LMsgSC
{
	Lstring		m_videoid;//id

	LMsgC2SReqShareVideo() :LMsgSC(MSG_C_2_S_REQSHAREVIDEO){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_videoId), m_videoid);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_videoid), m_videoid);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgC2SReqShareVideo(); }
};

//服务器返回分享的id
struct LMsgS2CRetShareVideoId :public LMsgSC
{
	Lint		m_errorId;//0成功 1失败
	Lint		m_shareId;//id

	LMsgS2CRetShareVideoId() :LMsgSC(MSG_S_2_C_RETSHAREVIDEOID),m_errorId(0),m_shareId(0){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_errorId), m_errorId);
		ReadMapData(obj, NAME_TO_STR(m_shareId), m_shareId);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_errorId), m_errorId);
		WriteKeyValue(pack, NAME_TO_STR(m_shareId), m_shareId);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CRetShareVideoId(); }
};


struct S2CShareVideo{
	Lstring	m_videoId;
	Lint	m_time;
	Lstring	m_userNike[4];
	Lint	m_score[4];
	Lint    m_user_count;
	S2CShareVideo():m_time(0),m_user_count(0){
		memset(m_score,0,sizeof(m_score));
	}
};

//服务器返回某shareid对应的分享录像
struct LMsgS2CShareVideo:public LMsgSC
{
	Lint		m_count;
	Lint		m_errorId;//0失败 1成功
	std::vector<S2CShareVideo> m_vec_share_video;

	LMsgS2CShareVideo() :LMsgSC(MSG_S_2_C_SHAREVIDEO),m_errorId(0),m_count(0){}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_errorId), m_errorId);

		WriteKey(pack,"m_data");
		WriteArray(pack,m_count);

		for(Lint i = 0 ; i < m_count; ++i)
		{
			WriteMap(pack,4);
			WriteKeyValue(pack, NAME_TO_STR(m_videoId),m_vec_share_video[i].m_videoId);
			WriteKeyValue(pack, NAME_TO_STR(m_time), m_vec_share_video[i].m_time);
			std::vector<Lint> vecscore;
			std::vector<Lstring> vecnike;
			for(Lint n = 0 ; n < m_vec_share_video[i].m_user_count; ++n)
			{
				vecnike.push_back(m_vec_share_video[i].m_userNike[n]);
				vecscore.push_back(m_vec_share_video[i].m_score[n]);
			}

			WriteKey(pack,"m_score");
			WriteKey(pack,vecscore);

			WriteKey(pack,"m_nike");
			WriteKey(pack, vecnike);
		}

		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CShareVideo(); }
};

struct LMsgS2CUserChargeDiamond : public LMsgSC
{
	Lint		m_error;			// 0-success, 1-failed

	LMsgS2CUserChargeDiamond() :LMsgSC(MSG_S_2_C_USER_CHARGE_DIAMOND),m_error(0){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_error), m_error);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_error), m_error);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CUserChargeDiamond(); }
};

struct LMsgS2CUserPurchase :public LMsgSC
{
	Lint		m_error;			// 0-success, 1-failed
	Lint		m_itemId;			// 道具Id

	LMsgS2CUserPurchase()
		:LMsgSC(MSG_S_2_C_USER_PURCHASE), m_error(0), m_itemId(0){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_error), m_error);
		ReadMapData(obj, NAME_TO_STR(m_itemId), m_itemId);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_error), m_error);
		WriteKeyValue(pack, NAME_TO_STR(m_itemId), m_itemId);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CUserPurchase(); }
};

struct LMsgS2CPlayerType :public LMsgSC
{
	Lstring		m_playerType;

	LMsgS2CPlayerType() :LMsgSC(MSG_S_2_C_PLAYER_TYPE){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_playerType), m_playerType);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_playerType), m_playerType);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CPlayerType(); }
};

//用户查看礼券兑换
struct LMsgC2SCouponsExchange:public LMsgSC
{
	Lint m_userId;
	LMsgC2SCouponsExchange() :LMsgSC(MSG_C_2_S_COUPONS_EXCHANGE),m_userId(0){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_userId), m_userId);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgC2SCouponsExchange(); }
};

struct gift_info{
	Lint	m_giftId; //1:iphone 2:100元话费
	Lint	m_couponsNeedCount;

	void	Read(LBuff& buff){
		buff.Read(m_giftId);
		buff.Read(m_couponsNeedCount);
	}
	void	Write(LBuff& buff){
		buff.Write(m_giftId);
		buff.Write(m_couponsNeedCount);
	}

	MSGPACK_DEFINE(m_giftId,m_couponsNeedCount);
};

//服务器返回 礼券兑换
struct LMsgS2CCouponsExchange:public LMsgSC
{
	Lint		m_CouponsCount;//礼券数量
	std::vector<gift_info> m_giftInfo;

	LMsgS2CCouponsExchange():LMsgSC(MSG_S_2_C_COUPONS_EXCHANGE),m_CouponsCount(0){}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_CouponsCount), m_CouponsCount);
		WriteKeyValue(pack, NAME_TO_STR(m_giftInfo), m_giftInfo);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CCouponsExchange(); }
};

//客户端请求兑换记录
struct LMsgC2SCouponsExchangeRecord:public LMsgSC
{
	Lint		m_userId;
	LMsgC2SCouponsExchangeRecord():LMsgSC(MSG_C_2_S_COUPONS_EXCHANGE_RECORD),m_userId(0){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_userId), m_userId);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgC2SCouponsExchangeRecord(); }
};

struct gift_exchange_record
{
	Lint m_giftId;
	Lint m_coupons_need;
	Lint m_time;
	Lint m_state;
	Lstring m_phoneNum;
	MSGPACK_DEFINE(m_giftId,m_coupons_need,m_time,m_state,m_phoneNum); 
	void	Read(LBuff& buff){
		buff.Read(m_giftId);
		buff.Read(m_coupons_need);
		buff.Read(m_time);
		buff.Read(m_state);
		buff.Read(m_phoneNum);
	}
	void	Write(LBuff& buff){
		buff.Write(m_giftId);
		buff.Write(m_coupons_need);
		buff.Write(m_time);
		buff.Write(m_state);
		buff.Write(m_phoneNum);
	}
};
//服务器返回兑换记录
struct LMsgS2CCouponsExchangeRecord:public LMsgSC
{
	std::vector<gift_exchange_record> m_record;
	LMsgS2CCouponsExchangeRecord():LMsgSC(MSG_S_2_C_COUPONS_EXCHANGE_RECORD){}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_record), m_record);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CCouponsExchangeRecord(); }
};
	
//客户端请求兑换商品
struct LMsgC2SGiftExchange:public LMsgSC
{
	Lint m_giftId;
	Lstring m_phoneNum;
	Lstring m_receiverName;
	Lstring m_receiverAddress;
	LMsgC2SGiftExchange():LMsgSC(MSG_C_2_S_GIFT_EXCHANGE){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_giftId), m_giftId);
		ReadMapData(obj, NAME_TO_STR(m_phoneNum), m_phoneNum);
		ReadMapData(obj, NAME_TO_STR(m_receiverName), m_receiverName);
		ReadMapData(obj, NAME_TO_STR(m_receiverAddress), m_receiverAddress);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgC2SGiftExchange(); }
};

//服务器返回兑换商品结果
struct LMsgS2CGiftExchange:public LMsgSC
{
	Lint m_errorId; //0：失败 1：成功
	Lint m_giftId;
	Lint m_CouponsCount;
	LMsgS2CGiftExchange():LMsgSC(MSG_S_2_C_GIFT_EXCHANGE),m_CouponsCount(0),m_errorId(0){}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_errorId), m_errorId);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 4);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_errorId), m_errorId);
		WriteKeyValue(pack, NAME_TO_STR(m_giftId), m_giftId);
		WriteKeyValue(pack, NAME_TO_STR(m_CouponsCount), m_CouponsCount);
		return true;
	}

	virtual LMsg* Clone(){ return new LMsgS2CGiftExchange(); }
};

struct LMsgC2SGetTask :public LMsgSC
{
	Lint		m_taskId;	// 0xffff:all tasks, otherwise, the task specified by task id

	LMsgC2SGetTask() : LMsgSC(MSG_C_2_S_GET_TASK), m_taskId(-1) {}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_taskId), m_taskId);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_taskId), m_taskId);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgC2SGetTask; }
};

struct TaskBasicInfo
{
	Lint		m_id;				// 任务id
	Lstring		m_description;		// 任务描述
	Lint		m_curProgress;		// 完成量
	Lint		m_total;			// 任务总量
	Lint		m_recvedReward;		// 是否领取奖励,非0：没有领取，0：已经领取
	Lint		m_remainingTime;	// 距离下次任务开始的剩余时间

	bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 6);
		WriteKeyValue(pack, NAME_TO_STR(m_id), m_id);
		WriteKeyValue(pack, NAME_TO_STR(m_desc), m_description);
		WriteKeyValue(pack, NAME_TO_STR(m_cur), m_curProgress);
		WriteKeyValue(pack, NAME_TO_STR(m_total), m_total);
		WriteKeyValue(pack, NAME_TO_STR(m_recvedReward), m_recvedReward);
		WriteKeyValue(pack, NAME_TO_STR(m_remainingTime), m_remainingTime);
		return true;
	}
};

struct LMsgS2CTaskList : public LMsgSC
{
	std::vector<TaskBasicInfo>		m_tasks;

	LMsgS2CTaskList() : LMsgSC(MSG_S_2_C_TASK_LIST) {}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKey(pack, NAME_TO_STR(m_tasks));
		WriteArray(pack, m_tasks.size());
		for (Lsize i = 0; i < m_tasks.size(); i++)
			m_tasks[i].Write(pack);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CTaskList; }
};

struct LMsgC2SRecvTaskReward : public LMsgSC
{
	Lint		m_taskId;

	LMsgC2SRecvTaskReward() : LMsgSC(MSG_C_2_S_RECV_TASK_REWARD), m_taskId(-1) {}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_taskId), m_taskId);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_taskId), m_taskId);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgC2SRecvTaskReward; }
};

struct Reward
{
	Lint	m_type;
	Lint	m_count;
};

struct LMsgS2CRecvTaskReward : public LMsgSC
{
	Lint			m_taskId;
	ErrorCode		m_error;
	Reward			m_reward;

	LMsgS2CRecvTaskReward() : LMsgSC(MSG_S_2_C_RECV_TASK_REWARD){}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_error), (Lint)m_error);
		WriteKey(pack, NAME_TO_STR(m_reward));
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_type), m_reward.m_type);
		WriteKeyValue(pack, NAME_TO_STR(m_count), m_reward.m_count);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgS2CRecvTaskReward;
	}
};

struct LMsgC2SGetUserInfo : public LMsgSC
{
	Lint		m_userId;

	LMsgC2SGetUserInfo() : LMsgSC(MSG_C_2_S_GET_USER_INFO), m_userId(-1) {}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_userId), m_userId);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_userId), m_userId);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgC2SGetUserInfo; }
};

struct UserBasicInfo
{
	Lint		m_id;
	Lstring		m_unionId;
	Lstring		m_nickName;
	Lstring		m_headImgUrl;

	bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 4);
		WriteKeyValue(pack, NAME_TO_STR(m_id), m_id);
		WriteKeyValue(pack, NAME_TO_STR(m_unionId), m_unionId);
		WriteKeyValue(pack, NAME_TO_STR(m_nickName), m_nickName);
		WriteKeyValue(pack, NAME_TO_STR(m_headImgUrl), m_headImgUrl);
		return true;
	}
};

struct LMsgS2CUserInfo : public LMsgSC
{
	ErrorCode			m_error;
	UserBasicInfo		m_user;

	LMsgS2CUserInfo() : LMsgSC(MSG_S_2_C_USER_INFO) {}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_error), (Lint)m_error);
		WriteKey(pack, NAME_TO_STR(m_user));
		m_user.Write(pack);

		return true;
	}

	virtual LMsg* Clone() {return new LMsgS2CUserInfo;}
};

struct LMsgC2SGetInvitingInfo : public LMsgSC
{
	LMsgC2SGetInvitingInfo() : LMsgSC(MSG_C_2_S_GET_INVITING_INFO) {}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 1);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgC2SGetInvitingInfo; }
};

//#define NUM_MAX_INVITEE		20
#define NUM_MAX_INVITEE			100000
#define NUM_MAX_INVITEE_PER_DAY			10 //modify by lidm

struct InviteeInfo
{
	UserBasicInfo		m_info;
	Lint				m_taskFinished;		// 被邀请者任务是否完成，0：没有完成，非0：完成

	bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 5);
		WriteKeyValue(pack, NAME_TO_STR(m_id), m_info.m_id);
		WriteKeyValue(pack, NAME_TO_STR(m_unionId), m_info.m_unionId);
		WriteKeyValue(pack, NAME_TO_STR(m_nickName), m_info.m_nickName);
		WriteKeyValue(pack, NAME_TO_STR(m_headImgUrl), m_info.m_headImgUrl);
		WriteKeyValue(pack, NAME_TO_STR(m_taskFinished), m_taskFinished);
		return true;
	}
};

struct LMsgS2CInvitingInfo : public LMsgSC
{
	Reward						m_reward;
	UserBasicInfo				m_inviter;
	Luint						m_externfee;
	std::vector<InviteeInfo>	m_invitees;

	LMsgS2CInvitingInfo() : LMsgSC(MSG_S_2_C_INVITING_INFO) { m_externfee = 0; }

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 5);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_externfee), m_externfee);

		WriteKey(pack, NAME_TO_STR(m_reward));
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_type), m_reward.m_type);
		WriteKeyValue(pack, NAME_TO_STR(m_count), m_reward.m_count);

		WriteKey(pack, NAME_TO_STR(m_inviter));
		m_inviter.Write(pack);

		WriteKey(pack, NAME_TO_STR(m_invitees));
		WriteArray(pack, m_invitees.size());

		for (int i = 0; i < m_invitees.size(); i++)
			m_invitees[i].Write(pack);

		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CInvitingInfo; }
};

struct LMsgC2SBindInviter : public LMsgSC
{
	Lint				m_inviterId;
	LMsgC2SBindInviter() : LMsgSC(MSG_C_2_S_BIND_INVITER) {}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_inviterId), m_inviterId);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_inviterId), m_inviterId);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgC2SBindInviter; }
};

struct LMsgS2CBindInviter : public LMsgSC
{
	ErrorCode			m_error;
	UserBasicInfo		m_inviter;

	LMsgS2CBindInviter() : LMsgSC(MSG_S_2_C_BIND_INVITER) {}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_error), (Lint)m_error);
		WriteKey(pack, NAME_TO_STR(m_inviter));
		m_inviter.Write(pack);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CBindInviter; }
};

struct LMsgC2SUserShared : public LMsgSC
{
	LMsgC2SUserShared() : LMsgSC(MSG_C_2_S_USER_SHARED) {}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 1);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgC2SUserShared; }
};

struct LMsgC2SReqLuckyDrawNum : public LMsgSC
{
	LMsgC2SReqLuckyDrawNum() : LMsgSC(MSG_C_2_S_REQ_LUCKY_DRAW_NUM) {}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 1);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgC2SReqLuckyDrawNum; }
};

struct LMsgS2CLuckyDrawNum : public LMsgSC
{
	Lint	m_drawNum;

	LMsgS2CLuckyDrawNum() : LMsgSC(MSG_S_2_C_LUCKY_DRAW_NUM) {}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_drawNum), m_drawNum);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CLuckyDrawNum; }
};

struct LMsgS2CUserRewardInfo : public LMsgSC
{
	Reward		m_reward;

	LMsgS2CUserRewardInfo() : LMsgSC(MSG_S_2_C_USER_REWARD_INFO) {}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKey(pack, NAME_TO_STR(m_reward));
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_type), m_reward.m_type);
		WriteKeyValue(pack, NAME_TO_STR(m_count), m_reward.m_count);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CUserRewardInfo; }
};

struct LMsgS2CRewardNotReceived : public LMsgSC
{
	LMsgS2CRewardNotReceived() : LMsgSC(MSG_S_2_C_REWARD_NOT_RECEIVED) {}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CRewardNotReceived; }
};

/////////////////////////////////////////////////////////////////////////////

//请求获得手机号验证码
//MSG_C_2_S_GET_PHONE_VLDCODE = 181;

struct LMsgC2SGetPhoneVldCode : public LMsgSC
{
	Lstring	m_phoneNum;  //手机号
	Lint    m_type;      //0 为只获得验证码，1 手机号绑定模块
	LMsgC2SGetPhoneVldCode() : LMsgSC(MSG_C_2_S_GET_PHONE_VLDCODE), m_type(0){}
	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_phoneNum), m_phoneNum);
		ReadMapData(obj, NAME_TO_STR(m_type), m_type);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_phoneNum), m_phoneNum);
		WriteKeyValue(pack, NAME_TO_STR(m_type), m_type);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgC2SGetPhoneVldCode();
	}
};

//回复 获得手机号验证码
//MSG_S_2_C_GET_PHONE_VLDCODE = 182;

struct LMsgS2CGetPhoneVldCode : public LMsgSC
{
	Lstring	m_resCode;       //验证的返回的结果 "ok" 表示成功 其他异常 
	LMsgS2CGetPhoneVldCode() : LMsgSC(MSG_S_2_C_GET_PHONE_VLDCODE) {}
	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_resCode), m_resCode);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_resCode), m_resCode);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgS2CGetPhoneVldCode();
	}
};

//请求 绑定手机
//MSG_C_2_S_BIND_PHONE_NUM = 183;

struct LMsgC2SBindPhoneNum : public LMsgSC
{
	Lstring	m_phoneNum;     //手机号
	Lstring m_vldCode;   //校验码

	LMsgC2SBindPhoneNum() : LMsgSC(MSG_C_2_S_BIND_PHONE_NUM) {}
	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_phoneNum), m_phoneNum);
		ReadMapData(obj, NAME_TO_STR(m_vldCode), m_vldCode);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_phoneNum), m_phoneNum);
		WriteKeyValue(pack, NAME_TO_STR(m_vldCode), m_vldCode);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgC2SBindPhoneNum();
	}
};

//回复 绑定手机
//MSG_S_2_C_BIND_PHONE_NUM = 184;

struct LMsgS2CBindPhoneNum : public LMsgSC
{
	Lstring	m_resCode;        //验证的返回的结果 "ok" 表示成功 其他异常 

	LMsgS2CBindPhoneNum() : LMsgSC(MSG_S_2_C_BIND_PHONE_NUM) {}
	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_resCode), m_resCode);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_resCode), m_resCode);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgS2CBindPhoneNum();
	}
};

//玩家扩展信息，登陆完成后会带这个消息
//MSG_S_2_C_IS_BIND_PHONE_NUM = 186;

struct LMsgS2CIsBindPhoneNum : public LMsgSC
{
	Lint	m_isBindPhoneNum;        //0 表示尚未绑定 1表示已经绑定手机号

	LMsgS2CIsBindPhoneNum() : LMsgSC(MSG_S_2_C_IS_BIND_PHONE_NUM), m_isBindPhoneNum(0) {}
	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_isBindPhoneNum), m_isBindPhoneNum);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_isBindPhoneNum), m_isBindPhoneNum);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgS2CIsBindPhoneNum();
	}
};

// 客户端申请实名认证 [XSea 2016.9.24]
struct LMsgC2SRealName :public LMsgSC
{
	Lstring		m_NameStr; // 姓名
	Lstring		m_IDNumberStr; // 身份证号

	LMsgC2SRealName() :LMsgSC(MSG_C_2_S_REAL_NAME) {}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_NameStr), m_NameStr);
		ReadMapData(obj, NAME_TO_STR(m_IDNumberStr), m_IDNumberStr);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		return true;
	}

	virtual LMsg* Clone() { return new LMsgC2SRealName(); }
};

// 服务器返回实名认证结果 [XSea 2016.9.24]
struct LMsgS2CRealName :public LMsgSC
{
	Lint m_nResult; // 结果 0=成功,其他=异常

	LMsgS2CRealName() :LMsgSC(MSG_S_2_C_REAL_NAME) {}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_nResult), m_nResult);

		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CRealName(); }
};

// 客户端申请是否已实名认证 [XSea 2016.9.24]
struct LMsgC2SIsRealName :public LMsgSC
{
	LMsgC2SIsRealName() :LMsgSC(MSG_C_2_S_IS_REAL_NAME) {}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		return true;
	}

	virtual LMsg* Clone() { return new LMsgC2SIsRealName(); }
};

// 服务器返回是否已实名认证 [XSea 2016.9.24]
struct LMsgS2CIsRealName :public LMsgSC
{
	Lint m_nResult; // 结果 0=尚未绑定, 1=已绑定

	LMsgS2CIsRealName() :LMsgSC(MSG_S_2_C_IS_REAL_NAME) {}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_nResult), m_nResult);

		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CIsRealName(); }
};

/////////////////////////////////////////比赛场协议内容/////////////////////////////
//服务器统一推送所有提示协议
//MSG_S_2_C_TIPS = 170,

struct LMsgS2CTips : public LMsgSC
{
	Lint	m_id;   //提示内容id
	Lint    m_type; //类型 默认是0
	Lint    m_args1; //提示参数 目前距离开赛的秒数

	LMsgS2CTips() : LMsgSC(MSG_S_2_C_TIPS),m_id(0),m_type(0),m_args1(0) {}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_id), m_id);
		ReadMapData(obj, NAME_TO_STR(m_type), m_type);
		ReadMapData(obj, NAME_TO_STR(m_args1), m_args1);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 4);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_id), m_id);
		WriteKeyValue(pack, NAME_TO_STR(m_type), m_type);
		WriteKeyValue(pack, NAME_TO_STR(m_args1), m_args1);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CTips; }
};


//请求 查看比赛场内容
//MSG_C_2_S_VIEW_SPORT = 171,
struct LMsgC2SViewSport : public LMsgSC
{
	Lint		m_id; //赛场主页 id

	LMsgC2SViewSport() : LMsgSC(MSG_C_2_S_VIEW_SPORT), m_id(-1) {}
	
	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_id), m_id);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_id), m_id);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgC2SViewSport; }
};

//比赛项目数据
struct SportItemData
{
	Lint	m_id; //赛场内容id
	Lint    m_inNum; //参赛人数  0就是正在结算
	Lint    m_time; //开赛倒计时秒数，0表示比赛中
	Lint    m_sign; //0尚未加入，1已经加入
	Lint    m_timeidx; //时间显示索引
	Lstring m_rule_title; //规则标题
	Lint	m_predictWaitTime;//预计等待开赛时间
	Lint	m_remainFreeTimes;//剩余免费报名次数
	
	MSGPACK_DEFINE(m_id, m_inNum, m_time, m_sign, m_timeidx, m_rule_title, m_predictWaitTime, m_remainFreeTimes);
	SportItemData()
	{
		m_id = 0;
		m_inNum = 0;
		m_time = 0;
		m_sign = 0;
		m_predictWaitTime = 0;
		m_remainFreeTimes = -1;
	}
	bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 8);
		WriteKeyValue(pack, NAME_TO_STR(m_id), m_id);
		WriteKeyValue(pack, NAME_TO_STR(m_inNum), m_inNum);
		WriteKeyValue(pack, NAME_TO_STR(m_time), m_time);
		WriteKeyValue(pack, NAME_TO_STR(m_sign), m_sign);
		WriteKeyValue(pack, NAME_TO_STR(m_timeidx), m_timeidx);
		WriteKeyValue(pack, NAME_TO_STR(m_rule_title), m_rule_title);
		WriteKeyValue(pack, NAME_TO_STR(m_predictWaitTime), m_predictWaitTime);
		WriteKeyValue(pack, NAME_TO_STR(m_remainFreeTimes), m_remainFreeTimes);
		return true;
	}
};

//返回 查看比赛场内容
//MSG_S_2_C_VIEW_SPORT = 172,

struct LMsgS2CViewSport : public LMsgSC
{
	Lint	m_recordCout;   //新纪录数
	Lint    m_servertime;   //服务器时间
	std::vector<SportItemData> m_items;//比赛项目数据

	LMsgS2CViewSport() : LMsgSC(MSG_S_2_C_VIEW_SPORT) {}
	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 4);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_recordCout), m_recordCout);
		WriteKeyValue(pack, NAME_TO_STR(m_servertime), m_servertime);
		WriteKey(pack, NAME_TO_STR(m_items));

		WriteArray(pack, m_items.size());
		for (Lsize i = 0; i < m_items.size(); ++i)
			m_items[i].Write(pack);

		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CViewSport; }
};

//请求 加入或退出比赛场
//MSG_C_2_S_OPTJOIN_SPORT = 173,

struct LMsgC2SOptJoinSport : public LMsgSC
{
	Lint		m_id; //赛场内容 id
	Lint        m_opt; //0表示加入比赛，1表示退出比赛

	LMsgC2SOptJoinSport() : LMsgSC(MSG_C_2_S_OPTJOIN_SPORT), m_id(-1),m_opt(0) {}
	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_id), m_id);
		ReadMapData(obj, NAME_TO_STR(m_opt), m_opt);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_id), m_id);
		WriteKeyValue(pack, NAME_TO_STR(m_opt), m_opt);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgC2SOptJoinSport; }
};


//返回 加入或退出比赛场
//MSG_S_2_C_OPTJOIN_SPORT = 174,

struct LMsgS2COptJoinSport : public LMsgSC
{
	Lint	m_retCode;   //0表示成功，1房卡不够，2尚未到时间，3，不在参加比赛中，不能取消 4已经报名，5同步桌子数，6报名超过限制  7 资源文件或配置文件正在更新中不能报名
	Lint    m_inNum;     //该条项目参赛的人数
	Lint    m_sportId;	 //比赛场id
	Lint	m_predictWaitTime;
	Lint	m_remainFreeTimes;
	Lint	m_needUpdate;//1表示需要刷新m_remainFreeTimes
	
	LMsgS2COptJoinSport() : LMsgSC(MSG_S_2_C_OPTJOIN_SPORT),m_predictWaitTime(0), m_remainFreeTimes(-1), m_needUpdate(0){}
	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_retCode), m_retCode);
		ReadMapData(obj, NAME_TO_STR(m_inNum), m_inNum);
		ReadMapData(obj, NAME_TO_STR(m_sportId), m_sportId);
		ReadMapData(obj, NAME_TO_STR(m_predictWaitTime), m_predictWaitTime);
		ReadMapData(obj, NAME_TO_STR(m_remainFreeTimes), m_remainFreeTimes);
		ReadMapData(obj, NAME_TO_STR(m_needUpdate), m_needUpdate);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 7);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_retCode), m_retCode);
		WriteKeyValue(pack, NAME_TO_STR(m_inNum), m_inNum);
		WriteKeyValue(pack, NAME_TO_STR(m_sportId), m_sportId);
		WriteKeyValue(pack, NAME_TO_STR(m_predictWaitTime), m_predictWaitTime);
		WriteKeyValue(pack, NAME_TO_STR(m_remainFreeTimes), m_remainFreeTimes);
		WriteKeyValue(pack, NAME_TO_STR(m_needUpdate), m_needUpdate);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2COptJoinSport; }
};


//竞技的提示
//MSG_S_2_C_SPORT_TIPS = 176,

//例子说明:
//如果m_id 为0表示通知，数据变化；客户端可以以m_type 作为类型替换数值
//打立出局被淘汰：m_type 为0 m_args1 为名次
//打立出局对手匹配：m_type为1 m_args1当前积分 m_args2当前排名 m_args3胜率 m_args4前50名积分
//打立出局最后结束等待：m_type为2 m_args1定局积分名次 m_args2剩余桌子数
//定局积分成功提示：m_type为3 m_args1比赛排名 m_args2积分 
//定局积分失败提示：m_type为4 m_args1比赛排名 m_args2积分 m_args3胜率 m_args4即将进入的阶段 
//定局积分赛等待结果已经定局积分提示：m_type为5 m_args1本桌排名 m_args2等待剩余桌数  
//定局积分赛等待结果未定定局积分提示：m_type为6 m_args1本桌排名 m_args2等待剩余桌数 
//定局积分比赛等待结束：m_type为7 m_args1剩余桌子数 
//定局积分比赛结束：m_type为8 m_args1名次 m_args2奖励id1 m_args3奖励id2 m_args4奖励id3 m_args5奖励id4

struct LMsgS2CSportTips : public LMsgSC
{
	Lint	m_id;    //提示内容id，0表示通知
	Lint	m_type;  //提示类型，0预选被淘汰，1打立出局结束；2比赛结束，等待其他桌子结束，
	Lint    m_sportId; //比赛场id
	Lint    m_args1; //预定义参数 如果：type为1，剩余的桌子数
	Lint    m_args2; //预定义参数	
	Lint    m_args3; //预定义参数
	Lint    m_args4; //预定义参数
	Lint    m_args5; //预定义参数
	
	LMsgS2CSportTips() : LMsgSC(MSG_S_2_C_SPORT_TIPS) {}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_id), m_id);
		ReadMapData(obj, NAME_TO_STR(m_type), m_type);
		ReadMapData(obj, NAME_TO_STR(m_sportId), m_sportId);
		ReadMapData(obj, NAME_TO_STR(m_args1), m_args1);
		ReadMapData(obj, NAME_TO_STR(m_args2), m_args2);
		ReadMapData(obj, NAME_TO_STR(m_args3), m_args3);
		ReadMapData(obj, NAME_TO_STR(m_args4), m_args4);
		ReadMapData(obj, NAME_TO_STR(m_args5), m_args5);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 9);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_id), m_id);
		WriteKeyValue(pack, NAME_TO_STR(m_type), m_type);
		WriteKeyValue(pack, NAME_TO_STR(m_sportId), m_sportId);
		WriteKeyValue(pack, NAME_TO_STR(m_args1), m_args1);
		WriteKeyValue(pack, NAME_TO_STR(m_args2), m_args2);
		WriteKeyValue(pack, NAME_TO_STR(m_args3), m_args3);
		WriteKeyValue(pack, NAME_TO_STR(m_args4), m_args4);
		WriteKeyValue(pack, NAME_TO_STR(m_args5), m_args5);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CSportTips; }
};


//请求比赛记录信息
//MSG_C_2_S_SPORT_RECORD_INFO = 177,

struct LMsgC2SSportRecordInfo : public LMsgSC
{
	Lint		m_pageindex; //第几条记录，往后10条
	Lint		m_sportId;//比赛id

	LMsgC2SSportRecordInfo() : LMsgSC(MSG_C_2_S_SPORT_RECORD_INFO), m_pageindex(0),m_sportId(0) {}
	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_pageindex), m_pageindex);
		ReadMapData(obj, NAME_TO_STR(m_sportId), m_sportId);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_pageindex), m_pageindex);
		WriteKeyValue(pack, NAME_TO_STR(m_sportId), m_sportId);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgC2SSportRecordInfo; }
};


//比赛记录信息项目
struct SportRecordInfoItemData
{
	Lstring	m_id;  //记录id
	Lint m_sportId; //比赛id
	Lint m_time; //记录时间
	Lint m_tipsId; //记录内容,0 啥也没有，1不用填信息领取，2 需要填写信息
	Lint m_rewardid; //赛场奖励 的id
	Lint m_read; //读取标识 0 尚未读取 1 已读
	Lint m_draw; //领取标识 如果m_rewardid 不为0 0 尚未领取 1 已经领取
	Lint m_rank; //排名
	Lint m_share; //是否已分享 0未分享 1已分享
	Lint m_groupid; //0表示没有分组

	MSGPACK_DEFINE(m_id,m_sportId,m_time,m_tipsId,m_rewardid,m_read,m_draw,m_rank,m_share, m_groupid);
	SportRecordInfoItemData()
	{
		m_sportId = 0;
		m_time = 0;
		m_tipsId = 0;
		m_rewardid = 0;
		m_read = 0;
		m_draw = 0;
		m_rank = 0;
		m_share = 0;
		m_groupid = 0;
	}

	bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 10);
		WriteKeyValue(pack, NAME_TO_STR(m_id), m_id);
		WriteKeyValue(pack, NAME_TO_STR(m_sportId), m_sportId);
		WriteKeyValue(pack, NAME_TO_STR(m_time), m_time);
		WriteKeyValue(pack, NAME_TO_STR(m_tipsId), m_tipsId);
		WriteKeyValue(pack, NAME_TO_STR(m_rewardid), m_rewardid);
		WriteKeyValue(pack, NAME_TO_STR(m_read), m_read);
		WriteKeyValue(pack, NAME_TO_STR(m_draw), m_draw);
		WriteKeyValue(pack, NAME_TO_STR(m_rank), m_rank);
		WriteKeyValue(pack, NAME_TO_STR(m_share), m_share);
		WriteKeyValue(pack, NAME_TO_STR(m_groupid), m_groupid);
		return true;
	}

};

//返回 请求比赛记录信息
//MSG_S_2_C_SPORT_RECORD_INFO = 178,
struct LMsgS2CSportRecordInfo : public LMsgSC
{
	Lint    m_pageindex;  //第几条记录，往后10条
	Lint	m_totolnum;   //记录总数
	std::vector<SportRecordInfoItemData> m_items;//项目数据
	Lint	m_sportId;
	
	LMsgS2CSportRecordInfo() : LMsgSC(MSG_S_2_C_SPORT_RECORD_INFO),m_pageindex(0), m_totolnum(0), m_sportId(0) {}
	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_pageindex), m_pageindex);
		ReadMapData(obj, NAME_TO_STR(m_totolnum), m_totolnum);
		ReadMapData(obj, NAME_TO_STR(m_items), m_items);
		
		msgpack::object array1;
		ReadMapData(obj, NAME_TO_STR(m_items), array1);
		if (array1.type == MSGPACK_OBJECT_ARRAY)
		{
			for (Lsize i = 0; i < array1.via.array.size; ++i)
			{
				SportRecordInfoItemData v;
				msgpack::object& pv = *(array1.via.array.ptr + i);
				pv.convert(v);
				m_items.push_back(v);
			}
		}
		
		ReadMapData(obj, NAME_TO_STR(m_sportId), m_sportId);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 5);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_pageindex),m_pageindex);
		WriteKeyValue(pack, NAME_TO_STR(m_totolnum), m_totolnum);
		WriteKey(pack, NAME_TO_STR(m_items));

		WriteArray(pack, m_items.size());
		for (Lsize i = 0; i < m_items.size(); ++i)
		{
			m_items[i].Write(pack);
		}

		WriteKeyValue(pack, NAME_TO_STR(m_sportId), m_sportId);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CSportRecordInfo; }
};

//请求 比赛记录信息相关操作
//MSG_C_2_S_SPORT_RECORD_INFO_OPT = 179,
//说明：m_id 必须带上
//m_opt 0删除该条记录,其他不用填写
//m_opt 1读取记录，其他不用填写
//m_opt 2领取 如果是填写信息领取，所有字段必须填写；分享领取，不必须填写get
struct LMsgC2SSportRecordInfoOpt : public LMsgSC
{
	Lstring	m_id;  //记录id
	Lint    m_opt; //操作内容：0删除该条记录 1读取记录，2领取(分享领取和填写信息完领取)
	Lstring m_phone; //手机号
	Lstring m_name;  //名字
	Lstring m_address; //地址
	Lint 	m_code; //验证码

	LMsgC2SSportRecordInfoOpt() : LMsgSC(MSG_C_2_S_SPORT_RECORD_INFO_OPT),m_opt(-1){}
	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_id), m_id);
		ReadMapData(obj, NAME_TO_STR(m_opt), m_opt);
		ReadMapData(obj, NAME_TO_STR(m_phone), m_phone);
		ReadMapData(obj, NAME_TO_STR(m_name), m_name);
		ReadMapData(obj, NAME_TO_STR(m_address), m_address);
		ReadMapData(obj, NAME_TO_STR(m_code), m_code);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 6);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_id), m_id);
		WriteKeyValue(pack, NAME_TO_STR(m_opt), m_opt);
		WriteKeyValue(pack, NAME_TO_STR(m_phone), m_phone);
		WriteKeyValue(pack, NAME_TO_STR(m_name), m_name);
		WriteKeyValue(pack, NAME_TO_STR(m_address), m_address);
		WriteKeyValue(pack, NAME_TO_STR(m_code), m_code);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgC2SSportRecordInfoOpt; }
};

//返回 比赛记录信息相关操作
//MSG_S_2_C_SPORT_RECORD_INFO_OPT = 180,

struct LMsgS2CSportRecordInfoOpt : public LMsgSC
{
	Lstring	m_id;        //记录id
	Lint	m_rescode;   //结果码 0表示成功，其他为其他异常
	
	LMsgS2CSportRecordInfoOpt() : LMsgSC(MSG_S_2_C_SPORT_RECORD_INFO_OPT) {}
	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_id), m_id);
		ReadMapData(obj, NAME_TO_STR(m_rescode), m_rescode);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_id), m_id);
		WriteKeyValue(pack, NAME_TO_STR(m_rescode), m_rescode);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CSportRecordInfoOpt; }
};

/////////////////////////////////////////比赛场协议内容/////////////////////////////

// 客户端请求所有收件地址 [2016-8-17 willing]
struct LMsgC2SReqAllAddr : public LMsgSC
{
	LMsgC2SReqAllAddr() : LMsgSC(MSG_C_2_S_REQ_ALL_ADDR)
	{

	}

	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 1);
		WriteKeyValue(pack, "m_msgId", m_msgId);
		return true;
	}

	virtual LMsg* Clone() { return new LMsgC2SReqAllAddr(); }
};

// 地址信息 [2016-8-17 willing]
struct SUserAddrInfo
{
	Lint		nID;			// 唯一ID [2016-8-17 willing]
	Lstring		strUserName;	// 收件人姓名 [2016-8-17 willing]
	Lstring		strPhone;			// 电话号码 [2016-8-17 willing]
	Lint		nZipCode;		// 邮政编码 [2016-8-17 willing]
	Lstring		strUserAddr;	// 收件地址 [2016-8-17 willing]

	MSGPACK_DEFINE(nID,strUserName,strPhone,nZipCode,strUserAddr); 

	void	Read(LBuff& buff)
	{
		buff.Read(nID);
		buff.Read(strUserName);
		buff.Read(strPhone);
		buff.Read(nZipCode);
		buff.Read(strUserAddr);
	}

	void	Write(LBuff& buff)
	{
		buff.Write(nID);
		buff.Write(strUserName);
		buff.Write(strPhone);
		buff.Write(nZipCode);
		buff.Write(strUserAddr);
	}
};
typedef std::vector<SUserAddrInfo>	tUserAddrInfoVec;

// 向客户端返回所有 收件地址 [2016-8-17 willing]
struct LMsgS2CAllAddr : public LMsgSC
{
	Lint nAddrCount;
	tUserAddrInfoVec addrInfoVec;

	LMsgS2CAllAddr() : LMsgSC(MSG_S_2_C_ALL_ADDR)
	{
		nAddrCount = 0;
		addrInfoVec.clear();
	}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(nAddrCount), nAddrCount);
		ReadMapData(obj, NAME_TO_STR(addrInfoVec), addrInfoVec);

		msgpack::object array1;
		ReadMapData(obj, NAME_TO_STR(addrInfoVec), array1);
		if (array1.type == MSGPACK_OBJECT_ARRAY)
		{
			for (Lsize i = 0; i < array1.via.array.size; ++i)
			{
				SUserAddrInfo v;
				msgpack::object& pv = *(array1.via.array.ptr + i);
				pv.convert(v);
				addrInfoVec.push_back(v);
			}
		}

		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 3);

		WriteKeyValue(pack, NAME_TO_STR(m_msgId),m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(nAddrCount),nAddrCount);
		WriteKeyValue(pack, NAME_TO_STR(addrInfoVec),addrInfoVec);

		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CAllAddr(); }
};

// 添加 收件地址 [2016-8-17 willing]
struct LMsgC2SAddAddr : public LMsgSC
{
	Lstring		strUserName;	// 收件人姓名 [2016-8-17 willing]
	Lstring		strPhone;			// 电话号码 [2016-8-17 willing]
	Lint		nZipCode;		// 邮政编码 [2016-8-17 willing]
	Lstring		strUserAddr;	// 收件地址 [2016-8-17 willing]

	LMsgC2SAddAddr() : LMsgSC(MSG_C_2_S_ADD_ADDR)
	{
		strUserName = "";
		strPhone = "";
		nZipCode = 0;
		strUserAddr = "";
	}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(strUserName),strUserName);
		ReadMapData(obj, NAME_TO_STR(strPhone),strPhone);
		ReadMapData(obj, NAME_TO_STR(nZipCode),nZipCode);
		ReadMapData(obj, NAME_TO_STR(strUserAddr),strUserAddr);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack,5);

		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(strUserName), strUserName);
		WriteKeyValue(pack, NAME_TO_STR(strPhone), strPhone);
		WriteKeyValue(pack, NAME_TO_STR(nZipCode), nZipCode);
		WriteKeyValue(pack, NAME_TO_STR(strUserAddr), strUserAddr);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgC2SAddAddr();
	}
};

// 玩家添加 收件地址的 结果 [2016-8-18 willing]
enum E_ADD_ADDR_RET
{
	EAAR_SUCCESS,			// 成功 [2016-8-18 willing]
	EAAR_NAME_LEN,			// 名称太长 [2016-8-18 willing]
	EAAR_ADDR_LEN,			// 地址太长 [2016-8-18 willing]
	EAAR_NOT_USER,			// 玩家不存在 [2016-8-18 willing]
	EAAR_MAX_ADDR_COUNT,	// 地址数量已达到上限 [2016-8-18 willing]
	EAAR_DB_SAVE,			// 存库时出错 [2016-8-18 willing]
	EAAR_MODIFY_ADDR,		// 修改地址时出错 [2016-8-18 willing]
	EAAR_ADDR_NOT_EXIST,	// 地址不存在 [2016-8-18 willing]
	EAAR_PHONE_LEN,			// 电话号码太长 [2016-8-18 willing]
};
struct LMsgS2CAddAddrRet : public LMsgSC
{
	Lint	nErrorCode;
	LMsgS2CAddAddrRet(): LMsgSC(MSG_S_2_C_ADD_ADDR_RET)
	{
		nErrorCode = 0;
	}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(nErrorCode), nErrorCode);

		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(nErrorCode), nErrorCode);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgS2CAddAddrRet();
	}
};

// 玩家修改 已经添加的地址 [2016-8-18 willing]
struct LMsgC2SModifyAddr : public LMsgSC
{
	Lint		nID;			// 唯一ID [2016-8-18 willing]
	Lstring		strUserName;	// 收件人姓名 [2016-8-18 willing]
	Lstring		strPhone;			// 电话号码 [2016-8-18 willing]
	Lint		nZipCode;		// 邮政编码 [2016-8-18 willing]
	Lstring		strUserAddr;	// 收件地址 [2016-8-18 willing]

	LMsgC2SModifyAddr() : LMsgSC(MSG_C_2_S_MODIFY_ADDR)
	{
		nID = 0;
		strUserName = "";
		strPhone = "";
		nZipCode = 0;
		strUserAddr = "";
	}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(nID), nID);
		ReadMapData(obj, NAME_TO_STR(strUserName), strUserName);
		ReadMapData(obj, NAME_TO_STR(strPhone), strPhone);
		ReadMapData(obj, NAME_TO_STR(nZipCode), nZipCode);
		ReadMapData(obj, NAME_TO_STR(strUserAddr), strUserAddr);

		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 6);

		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(nID), nID);
		WriteKeyValue(pack, NAME_TO_STR(strUserName), strUserName);
		WriteKeyValue(pack, NAME_TO_STR(strPhone), strPhone);
		WriteKeyValue(pack, NAME_TO_STR(nZipCode), nZipCode);
		WriteKeyValue(pack, NAME_TO_STR(strUserAddr), strUserAddr);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgC2SModifyAddr();
	}
};

// 玩家修改 已经添加地址的 操作结果 [2016-8-18 willing]
struct LMsgS2CModifyAddrRet : public LMsgSC
{
	Lint nErrorCode;

	LMsgS2CModifyAddrRet() : LMsgSC(MSG_S_2_C_MODIFY_ADDR_RET)
	{
		nErrorCode = EAAR_SUCCESS;
	}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(nErrorCode), nErrorCode);

		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);

		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(nErrorCode), nErrorCode);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgS2CModifyAddrRet();
	}
};

// 客户端请求删除 已有地址 [2016-8-18 willing]
struct LMsgC2SRmvAddr : public LMsgSC
{
	Lint nAddrID;		// 数据库中的唯一ID [2016-8-18 willing]

	LMsgC2SRmvAddr() : LMsgSC(MSG_C_2_S_RMV_ADDR)
	{
		nAddrID = 0;
	}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(nAddrID), nAddrID);

		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);

		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(nAddrID), nAddrID);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgC2SRmvAddr();
	}
};

// 返回删除地址操作的结果 [2016-8-18 willing]
struct LMsgS2CRmvAddrRet : public LMsgSC
{
	Lint nErrorCode;

	LMsgS2CRmvAddrRet() : LMsgSC(MSG_S_2_C_RMV_ADDR_RET)
	{
		nErrorCode = EAAR_SUCCESS;
	}

	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(nErrorCode), nErrorCode);

		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);

		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(nErrorCode), nErrorCode);

		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgS2CRmvAddrRet();
	}
};


/////////////////////////////////////////////////////////////////////////////

// 托管状态产生和取消托管都会发这个消息
//MSG_S_2_C_ATTACK_MANAGED = 187;

struct LMsgS2CAttachManaged : public LMsgSC
{
	Lint m_managed; //1 为托管状态， 0为不托管状态    
	LMsgS2CAttachManaged() : LMsgSC(MSG_S_2_C_ATTACK_MANAGED), m_managed(0){ }
	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_managed), m_managed);
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 2);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_managed), m_managed);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgS2CAttachManaged();
	}
};


// 客户端取消托管状态
//MSG_C_2_S_CANCEL_MANAGED = 188;

struct LMsgC2SCancelManaged : public LMsgSC
{
	LMsgC2SCancelManaged() : LMsgSC(MSG_C_2_S_CANCEL_MANAGED) {}
	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 1);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgC2SCancelManaged();
	}
};

//告诉客户端正在比赛过程中不能加入，请等等，或取消加入比赛场（可能在加入过程中异常）
//MSG_S_2_C_IN_SPORT = 189,		 
struct LMsgS2CInSport : public LMsgSC
{   
	LMsgS2CInSport() : LMsgSC(MSG_S_2_C_IN_SPORT){ }
	virtual bool Read(msgpack::object& obj)
	{
		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 1);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		return true;
	}

	virtual LMsg* Clone()
	{
		return new LMsgS2CInSport();
	}
};
//比赛场广播
//MSG_S_2_C_SPORT_BROADCAST = 190,

struct LMsgS2CSportBroadcast : public LMsgSC
{
	Lint	m_retCode;   //0表示成功，1房卡不够，2尚未到时间，3，不在参加比赛中，不能取消 4已经报名，5同步桌子数，6报名超过限制  7 资源文件或配置文件正在更新中不能报名
	Lint    m_inNum;     //该条项目参赛的人数
	Lint    m_sportId;	 //比赛场id

	LMsgS2CSportBroadcast() : LMsgSC(MSG_S_2_C_SPORT_BROADCAST) {}
	virtual bool Read(msgpack::object& obj)
	{
		ReadMapData(obj, NAME_TO_STR(m_retCode), m_retCode);
		ReadMapData(obj, NAME_TO_STR(m_inNum), m_inNum);
		ReadMapData(obj, NAME_TO_STR(m_sportId), m_sportId);

		return true;
	}

	virtual bool Write(msgpack::packer<msgpack::sbuffer>& pack)
	{
		WriteMap(pack, 4);
		WriteKeyValue(pack, NAME_TO_STR(m_msgId), m_msgId);
		WriteKeyValue(pack, NAME_TO_STR(m_retCode), m_retCode);
		WriteKeyValue(pack, NAME_TO_STR(m_inNum), m_inNum);
		WriteKeyValue(pack, NAME_TO_STR(m_sportId), m_sportId);

		return true;
	}

	virtual LMsg* Clone() { return new LMsgS2CSportBroadcast; }
};
#endif