#ifndef _GAME_DEFINE_H_
#define _GAME_DEFINE_H_

#define BASE_CARD_COUNT 36
#define WIND_CARD_COUNT 28
#define LAI_ZI_COUNT 4
#define CARD_COUNT 136
#define MAX_HANDCARD_COUNT 13

#define ONE_DATE_SECOND 86400 // 24*60*60

enum CARD_COLOR
{
	CARD_COLOR_WAN = 1,
	CARD_COLOR_TUO = 2,
	CARD_COLOR_SUO = 3,
};

//玩家思考类型
enum THINK_OPERATOR
{
	THINK_OPERATOR_NULL = 0, 
	THINK_OPERATOR_OUT = 1,
	THINK_OPERATOR_BOMB=2,//胡
	THINK_OPERATOR_AGANG=3,//暗杠
	THINK_OPERATOR_MGANG=4,//明杠
	THINK_OPERATOR_PENG=5,//碰
	THINK_OPERATOR_CHI=6,//吃
	THINK_OPERATOR_ABU=7,//暗补
	THINK_OPERATOR_MBU=8,//明补
	THINK_OPERATOR_TING = 9, //报听
	THINK_OPERATOR_XIABU = 10, //补虾牌
	THINK_OPERATOR_ZHONGTUSIXI = 11, //中途四喜
	THINK_OPERATOR_THROWDICE = 12, //掷骰子
};
#define DESK_USER_COUNT 4	//一桌玩家数量

#define INVAILD_POS		4  //无效的位置

#define	PLAY_CARD_TIME		10  //出牌时间
#define WAIT_READY_TIME		15  //准备时间

//桌子当前状态
enum DESK_STATE
{
	DESK_FREE =		0,	//桌子空闲状态
	DESK_WAIT,			//桌子等待状态
	DESK_PLAY,			//正在游戏中
};

//牌局当前状态
enum DESK_PLAY_STATE
{
	DESK_PLAY_SELECT_PIAO,	//选择飘 状态
	DESK_PLAY_START_HU,		//起手胡状态
	DESK_PLAY_GET_CARD,		//摸牌
	DESK_PLAY_THINK_CARD,	//思考
	DESK_PLAY_END_CARD,		//海底牌
	DESK_PLAY_BAO_TING,     //报听
	DESL_PLAY_XIA_BU,       //摸到虾子后补牌
};

//家胡牌情况，0-没胡，1-自摸，2-收炮，3-点炮
enum WIN_TYPE
{
	WIN_ZIMO,		//自摸
	WIN_BOMB,		//点炮
	WIN_NONE,		//慌庄
};

//胡牌方式
enum WIN_TYPE_SUB
{
	WIN_SUB_NONE,
	WIN_SUB_ZIMO,		//自摸
	WIN_SUB_BOMB,		//收炮
	WIN_SUB_ABOMB,		//点炮

	WIN_SUB_DZIMO,		//大胡自摸
	WIN_SUB_DBOMB,		//大胡收炮
	WIN_SUB_DABOMB,		//大胡点炮  
};

//起手胡牌类型
enum START_HU_INFO
{
	START_HU_NULL = 0,
	START_HU_QUEYISE=1,	     //缺一色
	START_HU_BANBANHU=2,	 //板板胡
	START_HU_DASIXI=3,	     //大四喜
	START_HU_LIULIUSHUN=4,   //六六顺
	START_HU_SANTONG=5,      //三同
	START_HU_JIEMEIDUI=6,    //姊妹对
	START_HU_YIZHIHUA=7,	 //一枝花
};
//麻将类型
enum GameType
{
	ZhuanZhuanMajiang = 0,		//转转麻将
	TwoPeopleZhuanZhuan = 1,	//二人转转
	ThreePeopleZhuanZhuan = 2,	//三人转转
	ChangShaMaJiang = 3,	//长沙麻将
	TwoPeopleChangSha = 4,	//二人长沙
	ThreePeopleChangSha = 5,	//三人长沙
	HongZhongMajiang = 6,	//红中麻将
	ShaoYangMajiang = 9,	//邵阳麻将
	ChenZhouMajiang = 12,	//郴州麻将
	ChangDeMajiang = 15,	//常德麻将
	YongZhouMajiang = 18,  //永州
	XiangTanMajiang = 21,  //湘潭
	YiYangMajiang = 24,    //益阳
	ChaoGuMajiang = 27,    //岳阳炒股
	ZhuoXiaZiMajiang = 30,   //岳阳捉虾子
	HengYangMajiang = 31, //衡阳麻将
	TuiDaoHuMaJiang = 32, //岳阳推倒胡-4人
	TuiDaoHuMaJiang_3 = 33, //岳阳推倒胡-3人
};
//胡牌类型
enum HU_PAI_LEIXING
{
	HU_XIAOHU = 1,				//小胡
	HU_SPECIAL_XIAOQIDUI = 2,		//豪华小七对
	HU_XIAOQIDUI = 3,				//小七对
	HU_QINGYISE = 4,				//清一色
	HU_JIANGJIANGHU = 5,			//将将胡
	HU_PENGPENGHU = 6,			//碰碰胡
	HU_QUANQIUREN = 7,			//全球人
	HU_GANG1 = 8,					//杠上开花
	HU_GANG2 = 9,					//杠上炮
	HU_END1 = 10,					//海底捞
	HU_END2 = 11,					//海底炮
	HU_QIANGGANGHU = 12,			//抢扛胡
	HU_DOUBLESPECIAL_XIAOQIDUI = 14, //双豪华七小队
	HU_TianHu = 15,//天胡
	HU_DiHu = 16,//地胡
	HU_Qishou4Lai = 17, //起手四个癞子
	HU_WuHongZhong = 18,//没有红中
	HU_QiangGangHu2 = 19,//qiangganghu2


	HU_13Yao = 20,
	HU_FengYiSe = 21,
	HU_QingYiSeMenQing = 22,
	HU_QingYiSeQiXiaoDui = 23,
	HU_QingYiSeDaDuiPeng = 24,
	HU_MenQing = 25,        //门清
	HU_DaDuiPeng = 26,
	HU_ShaoYangQiQiaoDui = 27,		//七巧对
	HU_ShaoYangLongQiDui = 28,		//龙七对
	HU_ShiSanLan = 29,
	HU_QiFengDaoWei = 30,
	HU_QiQiaoDui = 31,		//七巧对
	HU_LongQiDui = 32,		//龙七对
	HU_LonngQiaoDui = 33,
	HU_YingQiaoDui = 34,
	HU_WangDiao = 35,
	HU_WangDiaoWang = 36,
	HU_WangChuang = 37,
	HU_WangChuangWang = 38,
	HU_WangGuiWei = 39,
	HU_ShuangWangGuiWei = 40,
	HU_SiDaTianWang = 41,
	HU_QiShou4WangBa = 42,
	//湘潭
	HU_MenQingPengpengHu = 43,
	HU_MenQingQingyisePengpengHu = 44,
	HU_QingyisePengpengHu = 45,

	//yiyang
	HU_THREESPECIAL_XIAOQIDUI = 46, //三豪华七小对

	//yueyang chaogu
	HU_XIAODAO = 47,   //小刀
	HU_DADAO = 48,     //大刀
	HU_SILIANGUAN = 49, //四连冠

	//衡阳麻将
	HU_PINGHU = 50, //平胡
	HU_QINGPINGHU = 51 //青平胡 
};
//请求解散房间
enum RESET_ROOM_TYPE
{
	RESET_ROOM_TYPE_WAIT,
	RESET_ROOM_TYPE_AGREE,
	RESET_ROOM_TYPE_REFLUSE,
};

//比赛的模式
enum MATCH_MODE_TYPE
{
	MATCH_MODE_NOMAL = 0, //正常模式，定时定点报名开赛
	MATCH_MODE_LOOP  = 1, //循环队列开赛，报名够就开赛
	MATCH_MODE_MAX   = 2, //最大循环
};

enum  PLAYTYPE
{
	PT_UNDEFINE = 0,
	PT_ZIMOHU = 1,
	PT_DIANPAOHU = 2,
	PT_KEQIANGGANG = 3,
	PT_NEEDWIND = 4,
	PT_QIXIAODUI = 5,
	PT_ZHUANGXIAN = 6,//庄闲
	PT_ZHANIAO2 = 7,//扎2鸟
	PT_ZHANIAO4 = 8,//扎4鸟
	PT_ZHANIAO6 = 9,//扎6鸟
	PT_TWOPLAYER = 10,//两人
	PT_THREEPLAYER = 11,//三人
	PT_HAVEWIND = 12,//带风
	PT_ZHUANGCANEAT = 13,//可吃
	PT_ZhaNiao_2 = 14,//抓2鸟翻倍
	PT_ZhuangXian_2 = 15,//庄闲翻倍
	PT_XueZhan = 16,//血战玩法
	PT_XueZhan2fan = 17,//血战 2番
	PT_XueZhan4fan = 18,//血战 4番
	PT_QiShouHuCountNiao = 19, //起手胡算鸟
	PT_QiShouHuCountZhuang = 20,//起手胡算庄闲
	PT_EachDaHuCountNiao = 21, //每个大胡单算鸟
	PT_EachDaHuCountZhuang = 22,//每个大胡单算庄闲
	PT_HongZhong2Ma = 23, //红中2码
	PT_HongZhong3Ma = 24,//红中3码
	PT_HongZhong4Ma = 25,//红中4码

	PT_ChenZhouPiao = 26,//郴州 飘
	PT_ChenZhouAuNiao = 27, //郴州 金鸟
	PT_ChangDeHuangZhuangHuangGang = 28,//常德荒庄荒杠
	PT_ChangDeHuangZhuangNoHuangGang = 29,//常德荒庄不荒杠

	PT_ChangDeHuangZhuangQiangGangHuCountMa = 30,//常德抢杠胡算码
	PT_ChangDeHuangZhuangQiangGangHuNoCountMa = 31,//常德抢杠胡算码
	PT_ChangDe159CountMa = 32,//常德159奖码
	PT_ChangDeHuCountMa = 33, //常德摸几奖几
	PT_GangFollowHu = 34,

	//湘潭玩法增加
	PT_ShangWang = 35,
	PT_XiaWang = 36,
	PT_XuanMei01 = 37,
	PT_XuanMei02 = 38,
	PT_XuanMei03 = 39,
	PT_XuanMei04 = 40,
	PT_XuanMei05 = 41,
	PT_XuanMei06 = 42,
	PT_XuanMei07 = 43,
	PT_XuanMei08 = 44,

	//yiyang
	PT_FEINIAO1 = 46,//飞1鸟
	PT_FEINIAO2 = 47,//飞2鸟
	PT_FEINIAO3 = 48,//飞3鸟
	PT_FEINIAO4 = 49,//飞4鸟
	PT_FEINIAO5 = 50,//飞5鸟
	PT_FEINIAO6 = 51,//飞6鸟
	PT_FEINIAO7 = 52,//飞7鸟
	PT_FEINIAO8 = 53,//飞8鸟

	PT_BAOTING = 56,
	PT_MENQING = 57,
	PT_MENQINGPENPENGHU = 58,  //门清将将胡

	PT_SHANGXIAN48 = 60,
    PT_SHANGXIAN96 = 61,

	PT_SILIANGUAN =65, //四连冠
	PT_ZHONGTUSIXI = 66,//中途四喜

	//长沙麻将增加,对应起手胡中的1-7，这里为了录像使用，否则video表需要增加字段
	PT_START_HU_QUEYISE = 71, //缺一色
	PT_START_HU_BANBANHU = 72, //板板胡
	PT_START_HU_DASIXI = 73, //大四喜
	PT_START_HU_LIULIUSHUN = 74, //六六顺
	PT_START_HU_SANTONG = 75, //三同
	PT_START_HU_JIEMEIDUI = 76, //姊妹对
	PT_START_HU_YIZHIHUA = 77, //一枝花
};

//竞技场比赛状态
enum SportStage
{
	EM_SS_WAIT_OPEN = 0,     //等待开始
	EM_SS_WAIT_PRE = 1,      //准备预赛
	EM_SS_ON_PRE = 2,        //预赛过程
	EM_SS_ON_OVER_PRE = 3,   //等待结束预赛
	EM_SS_OVER_PRE = 4,   //结束预赛
						  //下面这个阶段根据配置循环
	EM_SS_WAIT_ADVANCE = 5, //等待进阶赛开始
	EM_SS_ON_ADVANCE = 6, //进阶赛过程
	EM_SS_ON_OVER_ADVANCE = 7, //等待进阶赛结束
	EM_SS_OVER_ADVANCE = 8, //阶赛结束
	EN_SS_OVER_SPROT = 9, //比赛结束
};

//竞技场项目,支持动态，默认20个，需要在改名字
enum SportItemType
{
	EM_SIYJ_BEGIN = 99,
	EM_SIYJ_IPHONE_ZHUANZHUAN = 100, //赢奖转转 Iphone6s 手机赛
	EM_SIYJ_FREE_MATCH = 101,		 //免费场
	EM_SIYJ_FEE_MATCH = 102,		 //收费场
	EM_SIYJ_CHRISTMAS_EVE = 103,          //
	EM_SIYJ_CHRISTMAS_DAY = 104,		     //
	EM_SIYJ_EXTERN_5 = 105,          //
	EM_SIYJ_EXTERN_6 = 106,          //
	EM_SIYJ_EXTERN_7 = 107,          //
	EM_SIYJ_EXTERN_8 = 108,         //
	EM_SIYJ_EXTERN_9 = 109,         //
	EM_SIYJ_EXTERN_10 = 110,        //
	EM_SIYJ_EXTERN_11 = 111,        //
	EM_SIYJ_EXTERN_12 = 112,        //
	EM_SIYJ_EXTERN_13 = 113,        //
	EM_SIYJ_EXTERN_14 = 114,        //
	EM_SIYJ_EXTERN_15 = 115,        //
	EM_SIYJ_EXTERN_16 = 116,        //
	EM_SIYJ_EXTERN_17 = 117,        //
	EM_SIYJ_EXTERN_18 = 118,        //
	EM_SIYJ_EXTERN_19 = 119,        //
	EM_SIYJ_EXTERN_20 = 120,        //

	EM_SIYJ_EXTERN_21 = 121,        //Add by lidm [2017-05-09]
	EM_SIYJ_EXTERN_22 = 122,        //
	EM_SIYJ_EXTERN_23 = 123,        //
	EM_SIYJ_EXTERN_24 = 124,        //
	EM_SIYJ_EXTERN_25 = 125,        //
	EM_SIYJ_EXTERN_26 = 126,        //
	EM_SIYJ_EXTERN_27 = 127,        //
	EM_SIYJ_EXTERN_28 = 128,        //
	EM_SIYJ_EXTERN_29 = 129,        //
	EM_SIYJ_EXTERN_30 = 130,        //
	EM_SIYJ_EXTERN_31 = 131,        //
	EM_SIYJ_EXTERN_32 = 132,        //
	EM_SIYJ_EXTERN_33 = 133,        //
	EM_SIYJ_EXTERN_34 = 134,        //
	EM_SIYJ_EXTERN_35 = 135,        //
	EM_SIYJ_EXTERN_36 = 136,        //
	EM_SIYJ_EXTERN_37 = 137,        //
	EM_SIYJ_EXTERN_38 = 138,        //
	EM_SIYJ_EXTERN_39 = 139,        //
	EM_SIYJ_EXTERN_40 = 140,        //
	EM_SIYJ_EXTERN_41 = 141,        //
	EM_SIYJ_EXTERN_42 = 142,        //
	EM_SIYJ_EXTERN_43 = 143,        //
	EM_SIYJ_EXTERN_44 = 144,        //
	EM_SIYJ_EXTERN_45 = 145,        //
	EM_SIYJ_EXTERN_46 = 146,        //
	EM_SIYJ_EXTERN_47 = 147,        //
	EM_SIYJ_EXTERN_48 = 148,        //
	EM_SIYJ_EXTERN_49 = 149,        //
	EM_SIYJ_EXTERN_50 = 150,        //
	EM_SIYJ_EXTERN_51 = 151,        //
	EM_SIYJ_EXTERN_52 = 152,        //
	EM_SIYJ_EXTERN_53 = 153,        //
	EM_SIYJ_EXTERN_54 = 154,        //
	EM_SIYJ_EXTERN_55 = 155,        //
	EM_SIYJ_EXTERN_56 = 156,        //
	EM_SIYJ_EXTERN_57 = 157,        //
	EM_SIYJ_EXTERN_58 = 158,        //
	EM_SIYJ_EXTERN_59 = 159,        //
	EM_SIYJ_EXTERN_60 = 160,        //

	EM_SIYJ_MAX = 161,
};

inline bool gIsMatchType(Lint type)
{
	if (type > EM_SIYJ_BEGIN && type < EM_SIYJ_MAX)
	{
		return true;
	}
	return false;
}

//竞技场提示的定义
enum SportTipsType
{
	EM_STT_PRE_MACTH = 1, //预选赛匹配对手 预选赛开赛匹配 m_id 1 m_type 为 1 m_args1 为淘汰名次
	EM_STT_PRE_MACTH_NEXT = 2, //预选赛下一轮等待 m_id 2 m_type为 2 m_args1当前积分 m_args2当前排名 m_args3胜率 m_args4前几名 m_args5 前几名的积分
	EM_STT_PRE_WAIT_OVER = 3, //预选赛等待结束 预选赛最终等待 m_id 3 m_type为 3 m_args1能晋级多少人 m_args2剩余桌子数
	EM_STT_PRE_OUT = 4, //预选赛被淘汰 m_id 4 m_type 为 4 m_args1 为名次 m_args2奖励id1 
	EM_STT_PRE_OK = 5, //预选赛晋级成功 预选赛晋级成功 m_id 5 m_type 为 5 m_args1 为名次
	EM_STT_ADVANCE_MATCH = 6, //晋级比赛等待匹配 晋级赛开赛匹配 m_id 6 m_type为6 m_args1当前积分 m_args2当前排名 m_args3胜率 m_args4前几名 m_args5 前几名的积分
	EM_STT_ADVANCE_WAIT = 7, //晋级等待结果尚未定 晋级赛下一轮等待（等待尚未确定是否晋级） m_id 7 m_type为7 m_args1本桌排名 m_args2等待剩余桌数  m_args3 淘汰人数
	EM_STT_ADVANCE_OK = 8, //晋级成功 晋级赛下一轮匹配（晋级成功）m_id 8 m_type为8 m_args1当前积分 m_args2当前排名 m_args3胜率 m_args4前几名 m_args5 前几名的积分
	EM_STT_ADVANCE_FAIL = 9, //晋级失败 晋级赛被淘汰 m_id 9 m_type为9 m_args1比赛排名 m_args2积分  m_args3奖励id1 
	EM_STT_ADVANCE_WAIT_OK = 10, //晋级等待结果已经晋级  晋级赛最终等待 m_id 10 m_type为10 m_args1剩余桌子数  m_args2 淘汰人数
	EM_STT_ADVANCE_OVER = 11, //晋级结束 晋级赛最终结果 m_id 11 m_type为11 m_args1名次 m_args2奖励id1 m_args3 当前积分
	EM_STT_SPORT_NOT_OPEN = 12, //由于条件不满足，关闭赛场: m_id 12 m_type为 12 
	EM_STT_SPORT_RESET = 13, //时间过长解散房间

	EM_STT_PLAYER_REQ_OUT = 15, //玩家请求退出比赛
	EM_STT_PLAYER_GIVEUP_MATCH = 16, //玩家自动放弃比赛
	EM_STT_CONFUPDATE_GIVEUP = 17, //资源文件更新，报名返还，请重新报名
};

enum SportUserInfoOpearateType
{
	EM_SPORT_UserId = 0,       //用户id
	EM_SPORT_Nike,		  //账户名 
	EM_SPORT_Sex,		  //性别 
	EM_SPORT_HeadImageUrl,		  //头像连接
	EM_SPORT_Sportid,		  //比赛场id
	EM_SPORT_Rank,		  //预留排名等级
	EM_SPORT_Join,		  //参赛次数
	EM_SPORT_MaxRank,		  //最好的名次
	EM_SPORT_Super,		  //冠军次数
	EM_SPORT_Final,		  //决赛次数
	EM_SPORT_Reward,		  //获得奖励次数
	EM_SPORT_TotalGift,		  //总礼券数
	EM_SPORT_TotalCard,		  //总房卡数 
	EM_SPORT_TotalReal,		  //总实物数
	EM_SPORT_InNum,		  //加入比赛次数
	EM_SPORT_WinNum,		  //胜利次数
	EM_SPORT_MaxScore,		  //获得的最大积分
	EM_SPORT_JoinTimesByDay,//每天统计报名次数
};

//SportItem  操作的值类型
enum EMSptItemOptValueType
{
	EMSptItemOpt_SportId, 
	EMSptItemOpt_QueueId,
	EMSptItemOpt_RandId,
	EMSptItemOpt_SignTime,
	EMSptItemOpt_StartTime,
	EMSptItemOpt_SignStartDiff,
	EMSptItemOpt_MatchTime,
	EMSptItemOpt_SignNum,
	EMSptItemOpt_MatchNum,
	EMSptItemOpt_RewardUserNum,
	EMSptItemOpt_CustomNum1,
	EMSptItemOpt_CustomNum2,
	EMSptItemOpt_CustomNum3,
	EMSptItemOpt_CustomNum4,
	EMSptItemOpt_CustomNum5,
	EMSptItemOpt_RewardNum1,
	EMSptItemOpt_RewardNum2,
	EMSptItemOpt_RewardNum3,
	EMSptItemOpt_RewardNum4,
	EMSptItemOpt_RewardNum5,
};

struct PlayTypeInfo
{
	bool H_Xuezhan;//血战
	bool H_ZhuangXian_2;//庄闲翻倍
	bool H_ZhaNiao_2;//扎鸟翻倍
	bool H_CanEat;//转转可吃
	bool H_HaveWind;//带风
	bool H_ThreePlayer;//3人玩法
	bool H_TwoPlayer;//2人玩法
	Lint I_ZhaNiao;//扎N鸟
	bool H_ZhuangXian;//庄闲
	bool H_Xiaoqidui;//小七对
	bool H_HongZhongLaiZi;//红中癞子
	bool H_DianPao;//点炮胡
	bool H_ZiMo;//自摸
	Lint H_XueZhanFan; //血战番数
	bool H_QiShouHuCountNiao;
	bool H_QiShouHuCountZhuang; 
	bool H_EachDaHuCountNiao ;
	bool H_EachDaHuCountZhuang ;
	bool H_ChenZhouPiao;
	bool H_ChenZhouAuNiao;
	bool H_ChangDeHuangGang;//常德荒杠
	bool H_ChangDeQiangGangHuCountMa;//常德 抢杠胡奖码
	bool H_ChangDeHuCountMa;
	bool H_GangFollowHu;
	bool H_ShangWang;    
	bool H_XiaWang;
	Lint I_XuanMei;         //选美数量
	Lint I_FeiNiao;
	bool H_BAOTING;
	bool H_MENQING;
	bool H_MENQINGPENGPENGHU;
	Lint I_ScoreLimit;
	bool H_SILIANGUAN;
	bool H_ZHONGTUSIXI;
	PlayTypeInfo() :H_QiShouHuCountNiao(false), H_QiShouHuCountZhuang(false), H_EachDaHuCountNiao(false), H_EachDaHuCountZhuang(false), H_Xuezhan(false), \
		H_ZhuangXian_2(false), H_ZhaNiao_2(false), H_CanEat(false), H_HaveWind(false), H_ThreePlayer(false), H_TwoPlayer(false), I_ZhaNiao(0), H_ZhuangXian(false), \
		H_Xiaoqidui(false), H_HongZhongLaiZi(false), H_DianPao(false), H_ZiMo(false), H_XueZhanFan(2), H_ChenZhouPiao(false), H_ChenZhouAuNiao(false), \
		H_ChangDeHuangGang(false), H_ChangDeQiangGangHuCountMa(false), H_ChangDeHuCountMa(false), H_GangFollowHu(false), H_ShangWang(false), H_XiaWang(false), \
		I_XuanMei(0), I_FeiNiao(0), H_BAOTING(false), H_MENQING(false), H_MENQINGPENGPENGHU(false), I_ScoreLimit(0), H_SILIANGUAN(false), H_ZHONGTUSIXI(false)
	{
	}
	void clear() {
		H_QiShouHuCountNiao=false ; 
		H_QiShouHuCountZhuang=false ;
		H_EachDaHuCountNiao=false ; 
		H_EachDaHuCountZhuang=false ; 
		H_Xuezhan=false ; 
		H_ZhuangXian_2=false ;
		H_ZhaNiao_2=false ; 
		H_CanEat=false ; 
		H_HaveWind=false ; 
		H_ThreePlayer=false ; 
		H_TwoPlayer=false ; 
		I_ZhaNiao=0 ; 
		H_ZhuangXian=false ; 
		H_Xiaoqidui=false ; 
		H_HongZhongLaiZi=false ;
		H_DianPao=false ;
		H_ZiMo=false ; 
		H_XueZhanFan = 2;
		H_ChenZhouPiao = false;
		H_ChenZhouAuNiao= false;
		H_ChangDeHuangGang = false;  //常德 荒庄荒杠
		H_ChangDeQiangGangHuCountMa = false;
		H_ChangDeHuCountMa = false;
		H_GangFollowHu = false;
		H_ShangWang = false;
		H_XiaWang = false;
		I_XuanMei = 0;
		I_FeiNiao = 0;
		H_BAOTING = false;
		H_MENQING = false;
		H_MENQINGPENGPENGHU = false;
		I_ScoreLimit = 0;
		H_SILIANGUAN = false;
		H_ZHONGTUSIXI = false;
	}
	void init_playtype_info(std::vector<Lint>& l_play_type)
	{
		for(int x=0;x<l_play_type.size();x++)
		{
			switch(l_play_type[x])
			{
			case PT_ZIMOHU:
				H_ZiMo=true;
				break;
			case PT_DIANPAOHU:
				H_DianPao=true;
				break;
			case PT_NEEDWIND:
				H_HongZhongLaiZi=true;
				break;
			case PT_QIXIAODUI:
				H_Xiaoqidui=true;
				break;
			case PT_ZHUANGXIAN:
				H_ZhuangXian=true;
				break;
			case PT_ZHANIAO2:
				I_ZhaNiao=2;
				break;
			case PT_ZHANIAO4:
				I_ZhaNiao=4;
				break;
			case PT_ZHANIAO6:
				I_ZhaNiao=6;
				break;
			case PT_TWOPLAYER:
				H_TwoPlayer=true;
				break;
			case PT_THREEPLAYER:
				H_ThreePlayer=true;
				break;
			case PT_HAVEWIND:
				H_HaveWind=true;
				break;
			case PT_ZHUANGCANEAT:
				H_CanEat=true;
				break;
			case PT_ZhaNiao_2:
				{
					I_ZhaNiao=2;
					H_ZhaNiao_2=true;
					break;
				}
			case PT_ZhuangXian_2:
				H_ZhuangXian_2=true;
				break;
			case PT_XueZhan:
				H_Xuezhan=true;
				break;
			case PT_XueZhan2fan:
				H_XueZhanFan=2;
				break;
			case PT_XueZhan4fan:
				H_XueZhanFan=4;
				break;
			case PT_QiShouHuCountNiao:
				H_QiShouHuCountNiao=true;
				break;
			case PT_QiShouHuCountZhuang:
				H_QiShouHuCountZhuang=true;
				break;
			case PT_EachDaHuCountNiao:
				H_EachDaHuCountNiao=true;
				break;
			case PT_EachDaHuCountZhuang:
				H_EachDaHuCountZhuang=true;
				break;
			case PT_HongZhong2Ma:
				I_ZhaNiao=2;
				break;
			case PT_HongZhong3Ma:
				I_ZhaNiao=3;
				break;
			case PT_HongZhong4Ma:
				I_ZhaNiao=4;
				break;
			case PT_ChenZhouAuNiao:
				H_ChenZhouAuNiao = true;
				break;
			case PT_ChenZhouPiao:
				H_ChenZhouPiao = true;
				break;
			case PT_ChangDeHuangZhuangHuangGang:
				H_ChangDeHuangGang = true;
				break;
			case PT_ChangDeHuangZhuangNoHuangGang:
				H_ChangDeHuangGang = false;
				break;
			case PT_ChangDeHuangZhuangQiangGangHuCountMa:
				H_ChangDeQiangGangHuCountMa = true;
				break;
			case PT_ChangDeHuangZhuangQiangGangHuNoCountMa:
				H_ChangDeQiangGangHuCountMa = false;
				break;
			case PT_ChangDeHuCountMa:
				H_ChangDeHuCountMa = true;
				break;
			case PT_GangFollowHu:
				H_GangFollowHu = true;
				break;
			case PT_ShangWang:
				H_ShangWang = true;
				break;
			case PT_XiaWang:
				H_XiaWang = true;
				break;
			case PT_XuanMei01:
				I_XuanMei = 1;
				break;
			case PT_XuanMei02:
				I_XuanMei = 2;
				break;
			case PT_XuanMei03:
				I_XuanMei = 3;
				break;
			case PT_XuanMei04:
				I_XuanMei = 4;
				break;
			case PT_XuanMei05:
				I_XuanMei = 5;
				break;
			case PT_XuanMei06:
				I_XuanMei = 6;
				break;
			case PT_FEINIAO1:
				I_FeiNiao = 1;
				break;
			case PT_FEINIAO2:
				I_FeiNiao = 2;
				break;
			case PT_FEINIAO3:
				I_FeiNiao = 3;
				break;
			case PT_FEINIAO4:
				I_FeiNiao = 4;
				break;
			case PT_FEINIAO5:
				I_FeiNiao = 5;
				break;
			case PT_FEINIAO6:
				I_FeiNiao = 6;
				break;
			case PT_BAOTING:
				H_BAOTING = true;
				break;
			case PT_MENQING:
				H_MENQING = true;
				break;
			case PT_MENQINGPENPENGHU:
				H_MENQINGPENGPENGHU = true;
				break;
			case PT_SHANGXIAN48:
				I_ScoreLimit = 48;
				break;
			case PT_SHANGXIAN96:
				I_ScoreLimit = 96;
				break;
			case PT_SILIANGUAN:
				H_SILIANGUAN = true;
				break;
			case PT_ZHONGTUSIXI:
				H_ZHONGTUSIXI = true;
				break;
			}		
		}		
	}
};	

struct ThrowDice
{
	Lint m_seed1;
	Lint m_seed2;
	Lint m_pos;
	bool m_needGetCard;
	bool m_gang;
	bool m_needThink;
	bool m_canhu;
	bool m_bu;
	bool m_first_think;
	bool m_gang_reconn;

	ThrowDice() :m_seed1(0), m_seed2(0), m_pos(0), m_needGetCard(false), m_gang(false), m_needThink(false), m_canhu(false), m_bu(false), m_first_think(false), m_gang_reconn(false)
	{}

	void clear()
	{
		m_seed1 = 0;
		m_seed2 = 0;
		m_pos = 0;
		m_needGetCard = false;
		m_gang = false;
		m_needThink = false;
		m_canhu = false;
		m_bu = false;
		m_first_think = false;
	}
};
#endif			

