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

//���˼������
enum THINK_OPERATOR
{
	THINK_OPERATOR_NULL = 0, 
	THINK_OPERATOR_OUT = 1,
	THINK_OPERATOR_BOMB=2,//��
	THINK_OPERATOR_AGANG=3,//����
	THINK_OPERATOR_MGANG=4,//����
	THINK_OPERATOR_PENG=5,//��
	THINK_OPERATOR_CHI=6,//��
	THINK_OPERATOR_ABU=7,//����
	THINK_OPERATOR_MBU=8,//����
	THINK_OPERATOR_TING = 9, //����
	THINK_OPERATOR_XIABU = 10, //��Ϻ��
	THINK_OPERATOR_ZHONGTUSIXI = 11, //��;��ϲ
	THINK_OPERATOR_THROWDICE = 12, //������
};
#define DESK_USER_COUNT 4	//һ���������

#define INVAILD_POS		4  //��Ч��λ��

#define	PLAY_CARD_TIME		10  //����ʱ��
#define WAIT_READY_TIME		15  //׼��ʱ��

//���ӵ�ǰ״̬
enum DESK_STATE
{
	DESK_FREE =		0,	//���ӿ���״̬
	DESK_WAIT,			//���ӵȴ�״̬
	DESK_PLAY,			//������Ϸ��
};

//�ƾֵ�ǰ״̬
enum DESK_PLAY_STATE
{
	DESK_PLAY_SELECT_PIAO,	//ѡ��Ʈ ״̬
	DESK_PLAY_START_HU,		//���ֺ�״̬
	DESK_PLAY_GET_CARD,		//����
	DESK_PLAY_THINK_CARD,	//˼��
	DESK_PLAY_END_CARD,		//������
	DESK_PLAY_BAO_TING,     //����
	DESL_PLAY_XIA_BU,       //����Ϻ�Ӻ���
};

//�Һ��������0-û����1-������2-���ڣ�3-����
enum WIN_TYPE
{
	WIN_ZIMO,		//����
	WIN_BOMB,		//����
	WIN_NONE,		//��ׯ
};

//���Ʒ�ʽ
enum WIN_TYPE_SUB
{
	WIN_SUB_NONE,
	WIN_SUB_ZIMO,		//����
	WIN_SUB_BOMB,		//����
	WIN_SUB_ABOMB,		//����

	WIN_SUB_DZIMO,		//�������
	WIN_SUB_DBOMB,		//�������
	WIN_SUB_DABOMB,		//�������  
};

//���ֺ�������
enum START_HU_INFO
{
	START_HU_NULL = 0,
	START_HU_QUEYISE=1,	     //ȱһɫ
	START_HU_BANBANHU=2,	 //����
	START_HU_DASIXI=3,	     //����ϲ
	START_HU_LIULIUSHUN=4,   //����˳
	START_HU_SANTONG=5,      //��ͬ
	START_HU_JIEMEIDUI=6,    //��ö�
	START_HU_YIZHIHUA=7,	 //һ֦��
};
//�齫����
enum GameType
{
	ZhuanZhuanMajiang = 0,		//תת�齫
	TwoPeopleZhuanZhuan = 1,	//����תת
	ThreePeopleZhuanZhuan = 2,	//����תת
	ChangShaMaJiang = 3,	//��ɳ�齫
	TwoPeopleChangSha = 4,	//���˳�ɳ
	ThreePeopleChangSha = 5,	//���˳�ɳ
	HongZhongMajiang = 6,	//�����齫
	ShaoYangMajiang = 9,	//�����齫
	ChenZhouMajiang = 12,	//�����齫
	ChangDeMajiang = 15,	//�����齫
	YongZhouMajiang = 18,  //����
	XiangTanMajiang = 21,  //��̶
	YiYangMajiang = 24,    //����
	ChaoGuMajiang = 27,    //��������
	ZhuoXiaZiMajiang = 30,   //����׽Ϻ��
	HengYangMajiang = 31, //�����齫
	TuiDaoHuMaJiang = 32, //�����Ƶ���-4��
	TuiDaoHuMaJiang_3 = 33, //�����Ƶ���-3��
};
//��������
enum HU_PAI_LEIXING
{
	HU_XIAOHU = 1,				//С��
	HU_SPECIAL_XIAOQIDUI = 2,		//����С�߶�
	HU_XIAOQIDUI = 3,				//С�߶�
	HU_QINGYISE = 4,				//��һɫ
	HU_JIANGJIANGHU = 5,			//������
	HU_PENGPENGHU = 6,			//������
	HU_QUANQIUREN = 7,			//ȫ����
	HU_GANG1 = 8,					//���Ͽ���
	HU_GANG2 = 9,					//������
	HU_END1 = 10,					//������
	HU_END2 = 11,					//������
	HU_QIANGGANGHU = 12,			//������
	HU_DOUBLESPECIAL_XIAOQIDUI = 14, //˫������С��
	HU_TianHu = 15,//���
	HU_DiHu = 16,//�غ�
	HU_Qishou4Lai = 17, //�����ĸ����
	HU_WuHongZhong = 18,//û�к���
	HU_QiangGangHu2 = 19,//qiangganghu2


	HU_13Yao = 20,
	HU_FengYiSe = 21,
	HU_QingYiSeMenQing = 22,
	HU_QingYiSeQiXiaoDui = 23,
	HU_QingYiSeDaDuiPeng = 24,
	HU_MenQing = 25,        //����
	HU_DaDuiPeng = 26,
	HU_ShaoYangQiQiaoDui = 27,		//���ɶ�
	HU_ShaoYangLongQiDui = 28,		//���߶�
	HU_ShiSanLan = 29,
	HU_QiFengDaoWei = 30,
	HU_QiQiaoDui = 31,		//���ɶ�
	HU_LongQiDui = 32,		//���߶�
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
	//��̶
	HU_MenQingPengpengHu = 43,
	HU_MenQingQingyisePengpengHu = 44,
	HU_QingyisePengpengHu = 45,

	//yiyang
	HU_THREESPECIAL_XIAOQIDUI = 46, //��������С��

	//yueyang chaogu
	HU_XIAODAO = 47,   //С��
	HU_DADAO = 48,     //��
	HU_SILIANGUAN = 49, //������

	//�����齫
	HU_PINGHU = 50, //ƽ��
	HU_QINGPINGHU = 51 //��ƽ�� 
};
//�����ɢ����
enum RESET_ROOM_TYPE
{
	RESET_ROOM_TYPE_WAIT,
	RESET_ROOM_TYPE_AGREE,
	RESET_ROOM_TYPE_REFLUSE,
};

//������ģʽ
enum MATCH_MODE_TYPE
{
	MATCH_MODE_NOMAL = 0, //����ģʽ����ʱ���㱨������
	MATCH_MODE_LOOP  = 1, //ѭ�����п������������Ϳ���
	MATCH_MODE_MAX   = 2, //���ѭ��
};

enum  PLAYTYPE
{
	PT_UNDEFINE = 0,
	PT_ZIMOHU = 1,
	PT_DIANPAOHU = 2,
	PT_KEQIANGGANG = 3,
	PT_NEEDWIND = 4,
	PT_QIXIAODUI = 5,
	PT_ZHUANGXIAN = 6,//ׯ��
	PT_ZHANIAO2 = 7,//��2��
	PT_ZHANIAO4 = 8,//��4��
	PT_ZHANIAO6 = 9,//��6��
	PT_TWOPLAYER = 10,//����
	PT_THREEPLAYER = 11,//����
	PT_HAVEWIND = 12,//����
	PT_ZHUANGCANEAT = 13,//�ɳ�
	PT_ZhaNiao_2 = 14,//ץ2�񷭱�
	PT_ZhuangXian_2 = 15,//ׯ�з���
	PT_XueZhan = 16,//Ѫս�淨
	PT_XueZhan2fan = 17,//Ѫս 2��
	PT_XueZhan4fan = 18,//Ѫս 4��
	PT_QiShouHuCountNiao = 19, //���ֺ�����
	PT_QiShouHuCountZhuang = 20,//���ֺ���ׯ��
	PT_EachDaHuCountNiao = 21, //ÿ�����������
	PT_EachDaHuCountZhuang = 22,//ÿ���������ׯ��
	PT_HongZhong2Ma = 23, //����2��
	PT_HongZhong3Ma = 24,//����3��
	PT_HongZhong4Ma = 25,//����4��

	PT_ChenZhouPiao = 26,//���� Ʈ
	PT_ChenZhouAuNiao = 27, //���� ����
	PT_ChangDeHuangZhuangHuangGang = 28,//���»�ׯ�ĸ�
	PT_ChangDeHuangZhuangNoHuangGang = 29,//���»�ׯ���ĸ�

	PT_ChangDeHuangZhuangQiangGangHuCountMa = 30,//�������ܺ�����
	PT_ChangDeHuangZhuangQiangGangHuNoCountMa = 31,//�������ܺ�����
	PT_ChangDe159CountMa = 32,//����159����
	PT_ChangDeHuCountMa = 33, //������������
	PT_GangFollowHu = 34,

	//��̶�淨����
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
	PT_FEINIAO1 = 46,//��1��
	PT_FEINIAO2 = 47,//��2��
	PT_FEINIAO3 = 48,//��3��
	PT_FEINIAO4 = 49,//��4��
	PT_FEINIAO5 = 50,//��5��
	PT_FEINIAO6 = 51,//��6��
	PT_FEINIAO7 = 52,//��7��
	PT_FEINIAO8 = 53,//��8��

	PT_BAOTING = 56,
	PT_MENQING = 57,
	PT_MENQINGPENPENGHU = 58,  //���彫����

	PT_SHANGXIAN48 = 60,
    PT_SHANGXIAN96 = 61,

	PT_SILIANGUAN =65, //������
	PT_ZHONGTUSIXI = 66,//��;��ϲ

	//��ɳ�齫����,��Ӧ���ֺ��е�1-7������Ϊ��¼��ʹ�ã�����video����Ҫ�����ֶ�
	PT_START_HU_QUEYISE = 71, //ȱһɫ
	PT_START_HU_BANBANHU = 72, //����
	PT_START_HU_DASIXI = 73, //����ϲ
	PT_START_HU_LIULIUSHUN = 74, //����˳
	PT_START_HU_SANTONG = 75, //��ͬ
	PT_START_HU_JIEMEIDUI = 76, //��ö�
	PT_START_HU_YIZHIHUA = 77, //һ֦��
};

//����������״̬
enum SportStage
{
	EM_SS_WAIT_OPEN = 0,     //�ȴ���ʼ
	EM_SS_WAIT_PRE = 1,      //׼��Ԥ��
	EM_SS_ON_PRE = 2,        //Ԥ������
	EM_SS_ON_OVER_PRE = 3,   //�ȴ�����Ԥ��
	EM_SS_OVER_PRE = 4,   //����Ԥ��
						  //��������׶θ�������ѭ��
	EM_SS_WAIT_ADVANCE = 5, //�ȴ���������ʼ
	EM_SS_ON_ADVANCE = 6, //����������
	EM_SS_ON_OVER_ADVANCE = 7, //�ȴ�����������
	EM_SS_OVER_ADVANCE = 8, //��������
	EN_SS_OVER_SPROT = 9, //��������
};

//��������Ŀ,֧�ֶ�̬��Ĭ��20������Ҫ�ڸ�����
enum SportItemType
{
	EM_SIYJ_BEGIN = 99,
	EM_SIYJ_IPHONE_ZHUANZHUAN = 100, //Ӯ��תת Iphone6s �ֻ���
	EM_SIYJ_FREE_MATCH = 101,		 //��ѳ�
	EM_SIYJ_FEE_MATCH = 102,		 //�շѳ�
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

//��������ʾ�Ķ���
enum SportTipsType
{
	EM_STT_PRE_MACTH = 1, //Ԥѡ��ƥ����� Ԥѡ������ƥ�� m_id 1 m_type Ϊ 1 m_args1 Ϊ��̭����
	EM_STT_PRE_MACTH_NEXT = 2, //Ԥѡ����һ�ֵȴ� m_id 2 m_typeΪ 2 m_args1��ǰ���� m_args2��ǰ���� m_args3ʤ�� m_args4ǰ���� m_args5 ǰ�����Ļ���
	EM_STT_PRE_WAIT_OVER = 3, //Ԥѡ���ȴ����� Ԥѡ�����յȴ� m_id 3 m_typeΪ 3 m_args1�ܽ��������� m_args2ʣ��������
	EM_STT_PRE_OUT = 4, //Ԥѡ������̭ m_id 4 m_type Ϊ 4 m_args1 Ϊ���� m_args2����id1 
	EM_STT_PRE_OK = 5, //Ԥѡ�������ɹ� Ԥѡ�������ɹ� m_id 5 m_type Ϊ 5 m_args1 Ϊ����
	EM_STT_ADVANCE_MATCH = 6, //���������ȴ�ƥ�� ����������ƥ�� m_id 6 m_typeΪ6 m_args1��ǰ���� m_args2��ǰ���� m_args3ʤ�� m_args4ǰ���� m_args5 ǰ�����Ļ���
	EM_STT_ADVANCE_WAIT = 7, //�����ȴ������δ�� ��������һ�ֵȴ����ȴ���δȷ���Ƿ������ m_id 7 m_typeΪ7 m_args1�������� m_args2�ȴ�ʣ������  m_args3 ��̭����
	EM_STT_ADVANCE_OK = 8, //�����ɹ� ��������һ��ƥ�䣨�����ɹ���m_id 8 m_typeΪ8 m_args1��ǰ���� m_args2��ǰ���� m_args3ʤ�� m_args4ǰ���� m_args5 ǰ�����Ļ���
	EM_STT_ADVANCE_FAIL = 9, //����ʧ�� ����������̭ m_id 9 m_typeΪ9 m_args1�������� m_args2����  m_args3����id1 
	EM_STT_ADVANCE_WAIT_OK = 10, //�����ȴ�����Ѿ�����  ���������յȴ� m_id 10 m_typeΪ10 m_args1ʣ��������  m_args2 ��̭����
	EM_STT_ADVANCE_OVER = 11, //�������� ���������ս�� m_id 11 m_typeΪ11 m_args1���� m_args2����id1 m_args3 ��ǰ����
	EM_STT_SPORT_NOT_OPEN = 12, //�������������㣬�ر�����: m_id 12 m_typeΪ 12 
	EM_STT_SPORT_RESET = 13, //ʱ�������ɢ����

	EM_STT_PLAYER_REQ_OUT = 15, //��������˳�����
	EM_STT_PLAYER_GIVEUP_MATCH = 16, //����Զ���������
	EM_STT_CONFUPDATE_GIVEUP = 17, //��Դ�ļ����£����������������±���
};

enum SportUserInfoOpearateType
{
	EM_SPORT_UserId = 0,       //�û�id
	EM_SPORT_Nike,		  //�˻��� 
	EM_SPORT_Sex,		  //�Ա� 
	EM_SPORT_HeadImageUrl,		  //ͷ������
	EM_SPORT_Sportid,		  //������id
	EM_SPORT_Rank,		  //Ԥ�������ȼ�
	EM_SPORT_Join,		  //��������
	EM_SPORT_MaxRank,		  //��õ�����
	EM_SPORT_Super,		  //�ھ�����
	EM_SPORT_Final,		  //��������
	EM_SPORT_Reward,		  //��ý�������
	EM_SPORT_TotalGift,		  //����ȯ��
	EM_SPORT_TotalCard,		  //�ܷ����� 
	EM_SPORT_TotalReal,		  //��ʵ����
	EM_SPORT_InNum,		  //�����������
	EM_SPORT_WinNum,		  //ʤ������
	EM_SPORT_MaxScore,		  //��õ�������
	EM_SPORT_JoinTimesByDay,//ÿ��ͳ�Ʊ�������
};

//SportItem  ������ֵ����
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
	bool H_Xuezhan;//Ѫս
	bool H_ZhuangXian_2;//ׯ�з���
	bool H_ZhaNiao_2;//���񷭱�
	bool H_CanEat;//תת�ɳ�
	bool H_HaveWind;//����
	bool H_ThreePlayer;//3���淨
	bool H_TwoPlayer;//2���淨
	Lint I_ZhaNiao;//��N��
	bool H_ZhuangXian;//ׯ��
	bool H_Xiaoqidui;//С�߶�
	bool H_HongZhongLaiZi;//�������
	bool H_DianPao;//���ں�
	bool H_ZiMo;//����
	Lint H_XueZhanFan; //Ѫս����
	bool H_QiShouHuCountNiao;
	bool H_QiShouHuCountZhuang; 
	bool H_EachDaHuCountNiao ;
	bool H_EachDaHuCountZhuang ;
	bool H_ChenZhouPiao;
	bool H_ChenZhouAuNiao;
	bool H_ChangDeHuangGang;//���»ĸ�
	bool H_ChangDeQiangGangHuCountMa;//���� ���ܺ�����
	bool H_ChangDeHuCountMa;
	bool H_GangFollowHu;
	bool H_ShangWang;    
	bool H_XiaWang;
	Lint I_XuanMei;         //ѡ������
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
		H_ChangDeHuangGang = false;  //���� ��ׯ�ĸ�
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

