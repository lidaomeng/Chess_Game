#ifndef _L_CHARGE_H_
#define _L_CHARGE_H_

#include "LBuff.h"

//��������
enum CARD_TYPE
{
	CARD_TYPE_4 = 1,//4�ֿ�
	CARD_TYPE_8 = 2,//8�ֿ�
	CARD_TYPE_16 = 3,//16�ֿ�
	CARD_TYPE_32 = 4, //1�ֿ�
	CARD_TYPE_64 = 5, //2�ֿ�
};

enum CARDS_OPER_TYPE
{
	CARDS_OPER_TYPE_INIT = 0,//��������
	CARDS_OPER_TYPE_CHARGE = 1,//��ֵ�
	CARDS_OPER_TYPE_FREE_GIVE = 2,//�������
	CARDS_OPER_TYPE_CREATE_ROOM = 3,//��������۳�
	CARDS_OPER_TYPE_ACTIVE = 4,		//��ͷ���
	CARDS_OPER_TYPE_PURCHASE_GIVE = 5,	//�����������
	CARDS_OPER_TYPE_VIP_GIVE = 6,	//�������VIP��������
	CARDS_OPER_TYPE_INVITING = 7,		//��������ͷ���
	CARDS_OPER_TYPE_PLAYING = 8,	//����ƾ�����
	CARDS_OPER_TYPE_SIGN_SPORT = 9,//�����������۳��������������ý���
	CARDS_OPER_TYPE_DRAW = 10,     //�齱ʹ��
};

class LCharge
{
public:
	LCharge();
	~LCharge();

	void	Read(LBuff& buff);
	void	Write(LBuff& buff);
public:
	Lint	m_time;
	Lint	m_cardType;
	Lint	m_cardNum;
	Lint	m_type;
	Lint	m_userId;
	Lstring	m_admin;
};
#endif