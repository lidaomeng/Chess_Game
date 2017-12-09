#include "LMsg.h"
#include "LLog.h"
#include "LMsgS2S.h"

LMsg::LMsg(int id)
:m_msgId(id), m_isMsgPack(false)
{

}

LMsg::~LMsg()
{

}

LBuffPtr LMsg::GetSendBuff()
{
	if(!m_send)
	{
		m_send.reset(new LBuff());
		if(preAllocSendMemorySize() > BUFF_SIZE)
		{
			m_send->Alloc(preAllocSendMemorySize());
		}

		if (m_isMsgPack)
		{
			msgpack::sbuffer buffer;
			msgpack::packer<msgpack::sbuffer> pac(&buffer);
			Write(pac); 

			MsgHeader header = {(unsigned short)(buffer.size()), 0, 0, 0};
			m_send->Write((char*)&header, sizeof(header));
			m_send->Write(buffer.data(), buffer.size());
		}
		else
		{
			LBuff tmpBuff;
			WriteMsgId(tmpBuff);
			Write(tmpBuff);

			MsgHeader header = {(unsigned short)(tmpBuff.Size()), 0, 0, 0};
			m_send->Write((char*)&header, sizeof(header));
			m_send->Write(tmpBuff.Data(), tmpBuff.Size());
		}
	}
	return m_send;
}

void LMsg::WriteMsgId(LBuff& buff)
{
	buff.Write(m_msgId);
}

void LMsg::ReadMsgId(LBuff& buff)
{
	buff.Write(m_msgId);
}

bool LMsg::Read(LBuff& buff)
{
	return true;
}

bool LMsg::Read(msgpack::object& pack)
{
	return true;
}

bool LMsg::Write(LBuff& buff)
{
	return true;
}

bool LMsg::Write(msgpack::packer<msgpack::sbuffer>& pack)
{
	return true;
}

LMsg* LMsg::Clone()
{
	return NULL;
}

Lint LMsg::preAllocSendMemorySize()
{
	return BUFF_SIZE;
}

//////////////////////////////////////////////////////////////////////////
bool LMsgFactory::Init()
{
	Final();

	RegestMsg(new LMsgIn());
	RegestMsg(new LMsgKick());
	RegestMsg(new LMsgHttp());

	RegestMsg(new LMsgC2SMsg());
	RegestMsg(new LMsgS2CMsg());

	RegestMsg(new LMsgC2SHeart());
	RegestMsg(new LMsgS2CHeart());
	RegestMsg(new LMsgC2SNotice());
	RegestMsg(new LMsgS2CNotice());

	RegestMsg(new LMsgC2SReLogin());
	RegestMsg(new LMsgC2SLogin());
	RegestMsg(new LMsgS2CLogin());
	RegestMsg(new LMsgL2CeSaveCardInfo());
	RegestMsg(new LMsgL2CeUserServerLogin());
	RegestMsg(new LMsgL2CeUserServerLogout());

	RegestMsg(new LMsgS2CItemInfo());
	RegestMsg(new LMsgS2CHorseInfo());

	RegestMsg(new LMsgS2CIntoDesk());
	RegestMsg(new LMsgS2CDeskAddUser());
	RegestMsg(new LMsgS2CDeskDelUser());
	RegestMsg(new LMsgC2SSelectResetDesk());
	RegestMsg(new LMsgS2CResetDesk());
	RegestMsg(new LMsgC2SResetDesk());

	RegestMsg(new LMsgS2CDeskState());

	RegestMsg(new LMsgC2SUserReady());
	RegestMsg(new LMsgS2CUserReady());

	RegestMsg(new LMsgS2CPlayStart());
	RegestMsg(new LMsgS2COutCard());
	RegestMsg(new LMsgC2SUserPlay());
	RegestMsg(new LMsgS2CUserPlay());
	RegestMsg(new LMsgS2CThink());
	RegestMsg(new LMsgC2SUserOper());
	RegestMsg(new LMsgC2SThrowDice());//TuiDaoHu
	RegestMsg(new LMsgS2CUserOper());
	RegestMsg(new LMsgS2CGameOver());

	RegestMsg(new LMsgS2CUserStartHu());
	RegestMsg(new LMsgC2SUserStartHuSelect());
	RegestMsg(new LMsgS2CUserStartHuSelect());

	RegestMsg(new LMsgS2CUserGangCard());
	RegestMsg(new LMsgS2CUserEndCardSelect());
	RegestMsg(new LMsgC2SUserEndCardSelect());
	RegestMsg(new LMsgS2CUserEndCardGet());

	RegestMsg(new LMsgS2CPiaoSelect());
	RegestMsg(new LMsgC2SPiaoSelect());

	RegestMsg(new LMsgC2SUserOutRoom());
	RegestMsg(new LMsgS2CUserOutRoom());

	RegestMsg(new LMsgC2SLeaveDesk());
	RegestMsg(new LMsgS2CLeaveDesk());

	RegestMsg(new LMsgC2SUserSpeak());
	RegestMsg(new LMsgS2CUserSpeak());

	RegestMsg(new LMsgC2SCreateDesk());
	RegestMsg(new LMsgS2CCreateDeskRet());

	RegestMsg(new LMsgC2SAddDesk());
	RegestMsg(new LMsgS2CAddDeskRet());

	
	RegestMsg(new LMsgS2CVipEnd());
	RegestMsg(new LMsgC2SVipLog());
	RegestMsg(new LMsgS2CVipLog());

	RegestMsg(new LMsgC2SVideo());
	RegestMsg(new LMsgS2CVideo());
	RegestMsg(new LMsgC2SCancelManaged());

	RegestMsg(new LMsgS2CUserChargeDiamond());
	RegestMsg(new LMsgS2CUserPurchase());

	RegestMsg(new LMsgS2CPlayerType());

	RegestMsg(new LMsgL2CeLogin());
	RegestMsg(new LMsgL2CeGateInfo());
	RegestMsg(new LMsgCe2LUserLogin());
	RegestMsg(new LMsgCe2LUserIdInfo());

	RegestMsg(new LMsgG2LLogin());
	RegestMsg(new LMsgG2LUserMsg());
	RegestMsg(new LMsgL2GUserMsg());
	RegestMsg(new LMsgL2CeSaveUser());
	RegestMsg(new LMsgL2CeSaveLogItem());
	RegestMsg(new LMsgLMG2CeCouponChanged);
	
	RegestMsg(new LMsgCe2LGMCharge());
	RegestMsg(new LMsgCe2LGMHorse());
	RegestMsg(new LMsgCe2LGMBuyInfo());
	RegestMsg(new LMsgCe2LGMHide());
	RegestMsg(new LMsgCe2LGMModifyPlayerType());
	RegestMsg(new LMsgCe2LGMChargeDiamond());
	RegestMsg(new LMsgCe2LGMPurchase());

	RegestMsg(new LMsgG2LUserOutMsg());
	RegestMsg(new LMsgL2GUserOutMsg());

	//抽奖活动
	RegestMsg(new LMsgL2LDBReqActive());
	RegestMsg(new LMsgLDB2LActiveInfo());
	RegestMsg(new LMsgL2LDBSyncDraw());
	RegestMsg(new LMsgLDB2LSyncDraw);
	RegestMsg(new LMsgL2LDBSyncPhone());
	RegestMsg(new LMsgS2CActiveInfo());
	RegestMsg(new LMsgC2SRequestDraw());
	RegestMsg(new LMsgS2CFinishDraw());
	RegestMsg(new LMsgC2SWritePhone());
	RegestMsg(new LMsgS2CWritePhone());
	RegestMsg(new LMsgC2SActiveLog());
	RegestMsg(new LMsgS2CDrawInfo());
	RegestMsg(new LMsgS2CActiveOpen());
	RegestMsg(new LMsgC2SActiveInfoRequest());
	RegestMsg(new LMsgC2SDrawCancelBroadcast());
	RegestMsg(new LMsgS2CDrawCancelBroadcast());
	RegestMsg(new LMsgS2CDrawBroadcast());
	RegestMsg(new LMsgC2SShareDraw());
	RegestMsg(new LMsgS2CShareDraw());

	
	RegestMsg(new LMsgL2LdbLogin());
	RegestMsg(new LMsgL2LDBSaveLogItem());
	RegestMsg(new LMsgL2LDBSaveVideo());
	RegestMsg(new LMsgL2LBDReqVipLog());
	RegestMsg(new LMsgLBD2LReqVipLog());
	RegestMsg(new LMsgL2LDBReqVideo());
	RegestMsg(new LMsgLDB2LReqVideo());

	RegestMsg(new LMsgL2CeUerReLogin());
	RegestMsg(new LMsgCe2LUserReLogin());
			
	RegestMsg(new LMsgLDB2LLogInfo());
	RegestMsg(new LMsgS2CZhaBirdShow());
	RegestMsg(new LMsgS2CWangBa());
	RegestMsg(new LMsgC2SShareVideo());
	RegestMsg(new LMsgS2CShareVideo());

	RegestMsg(new LMsgC2SReqShareVideo());
	RegestMsg(new LMsgS2CRetShareVideoId());
	RegestMsg(new LMsgL2LDBGGetShareVideoId());
	RegestMsg(new LMsgL2LDBGetShareVideo());
	RegestMsg(new LMsgLDB2LRetShareVideoId());
	RegestMsg(new LMsgLDB2LRetShareVideo());
	RegestMsg(new LMsgL2LDBSaveShareVideoId());
	RegestMsg(new LMsgC2SGetShareVideo());
	RegestMsg(new LMsgL2LDBGetSsharedVideo());

	RegestMsg(new LMsgLMG2GateLogicInfo());
	RegestMsg(new LMsgL2LMGLogin());
	RegestMsg(new LMsgLMG2GHorseInfo());
	RegestMsg(new LMsgLMG2LLogin());
	RegestMsg(new LMsgL2LMGModifyUserState());
	RegestMsg(new LMsgL2GModifyUserState());
	RegestMsg(new LMsgLMG2LCreateDesk());
	RegestMsg(new LMsgLMG2LAddToDesk());
	RegestMsg(new LMsgL2LMGModifyCard());
	RegestMsg(new LMsgL2LMGModifyPlayCount());
	RegestMsg(new LMsgG2LMGLogin());
	RegestMsg(new LMsgL2LMGRecyleDeskID());
	RegestMsg(new LMsgLMG2LdbLogin());
	RegestMsg(new LMsgG2LHEARTBEAT());
	RegestMsg(new LMsgL2GHEARTBEAT_BACK());
	RegestMsg(new LMsgG2LMGHEARTBEAT());
	RegestMsg(new LMsgLMG2GHEARTBEAT_BACK());
	RegestMsg(new LMsgL2LMGHEARTBEAT());
	RegestMsg(new LMsgLMG2LHEARTBEAT_BACK());
	RegestMsg(new LMsgL2LDBHEARTBEAT());
	RegestMsg(new LMsgLDB2LHEARTBEAT_BACK());
	RegestMsg(new LMsgLMG2LDBHEARTBEAT());
	RegestMsg(new LMsgLDB2LMGHEARTBEAT_BACK());
	RegestMsg(new LMsgLMG2CEHEARTBEAT());
	RegestMsg(new LMsgCE2LMGHEARTBEAT_BACK());
	RegestMsg(new LMsgC2SOneVipLog());
	RegestMsg(new LMsgS2COneVipLog());
	RegestMsg(new LMsgL2LBDReqOneVipLog());
	RegestMsg(new LMsgLBD2LReqOneVipLog());
	RegestMsg(new LMsgS2CUserGangThinkCard());
	RegestMsg(new LMsgC2SCouponsExchange());
	RegestMsg(new LMsgS2CCouponsExchange());
	RegestMsg(new LMsgC2SCouponsExchangeRecord());
	RegestMsg(new LMsgS2CCouponsExchangeRecord());
	RegestMsg(new LMsgCE2LMGUserGiftInfo());
	RegestMsg(new LMsgLMG2CEUserCouponsExchangeRecord());
	RegestMsg(new LMsgC2SGiftExchange());
	RegestMsg(new LMsgCE2LMGUserCouponsExchangeRecord());
	RegestMsg(new LMsgLMG2CEUserCouponsExchangeInfo());
	RegestMsg(new LMsgS2CGiftExchange());
	RegestMsg(new LMsgL2CeSynConfigInfo());
	RegestMsg(new LMsgCe2LSynConfigInfo());

	//玩家任务和推荐
	RegestMsg(new LMsgC2SGetTask);
	RegestMsg(new LMsgS2CTaskList);
	RegestMsg(new LMsgC2SRecvTaskReward);
	RegestMsg(new LMsgS2CRecvTaskReward);
	RegestMsg(new LMsgC2SGetUserInfo);
	RegestMsg(new LMsgS2CUserInfo);
	RegestMsg(new LMsgC2SGetInvitingInfo);
	RegestMsg(new LMsgS2CInvitingInfo);
	RegestMsg(new LMsgC2SBindInviter);
	RegestMsg(new LMsgS2CBindInviter);
	RegestMsg(new LMsgC2SUserShared);
	RegestMsg(new LMsgL2LDBExecSql);
	RegestMsg(new LMsgLMG2LDBReqTaskProgress);
	RegestMsg(new LMsgLDB2LMGTaskProgress);
	RegestMsg(new LMsgLMG2LDBReqBindingRelationships);
	RegestMsg(new LMsgLDB2LMGBindingRelationships);
	RegestMsg(new LMsgLMG2LDBInsertTaskProgress);
	RegestMsg(new LMsgLDB2LMGInsertTaskProgress);
	RegestMsg(new LMsgL2LMGUserCircleIncreased);
	RegestMsg(new LMsgLMG2LDBReqActiveGiftStock);
	RegestMsg(new LMsgLDB2LMGActiveGiftStock);
	RegestMsg(new LMsgLMG2LDBReqLuckyDrawNum);
	RegestMsg(new LMsgLDB2LMGLuckyDrawNum);
	RegestMsg(new LMsgC2SReqLuckyDrawNum);
	RegestMsg(new LMsgS2CLuckyDrawNum);
	RegestMsg(new LMsgLMG2CeOfflineUserCardChanged);
	RegestMsg(new LMsgLMG2LDBInsertBindingRelationship);
	RegestMsg(new LMsgLDB2LMGInsertBindingRelationship);
	RegestMsg(new LMsgL2LMGUserCompleteGame);
	
	RegestMsg(new LMsgLGCEUserMsgWrapper);
	RegestMsg(new LMsgLG2CEHeartBeat);
	RegestMsg(new LMsgLMG2CeCardExchange);

	RegestMsg(new LMsgS2SKeepAlive);
	RegestMsg(new LMsgS2SKeepAliveAck);
	RegestMsg(new LMsgLMG2CeSaveUserPlayCount);

	RegestMsg(new LMsgC2SGetPhoneVldCode);
	RegestMsg(new LMsgS2CGetPhoneVldCode);
	RegestMsg(new LMsgC2SBindPhoneNum);
	RegestMsg(new LMsgS2CBindPhoneNum);
	RegestMsg(new LMsgS2CIsBindPhoneNum);
	RegestMsg(new LMsgLMG2CEGetPhoneVldCode);
	RegestMsg(new LMsgCE2LMGGetPhoneVldCode);
	RegestMsg(new LMsgLMG2CEBindPhoneNum);
	RegestMsg(new LMsgCE2LMGBindPhoneNum);
	RegestMsg(new LMsgLMG2CEIsBindPhoneNum);
	RegestMsg(new LMsgCE2LMGIsBindPhoneNum);

	RegestMsg(new LMsgLMG2CEBindIDCard);
	RegestMsg(new LMsgCE2LMGBindBindIDCard);
	RegestMsg(new LMsgLMG2CEIsBindIDCard);
	RegestMsg(new LMsgCE2LMGIsBindIDCard);

	RegestMsg(new LMsgLmgr2LdbReqSelectInviterInfo);
	RegestMsg(new LMsgLdb2LmgrRspSelectInviterInfo);
	RegestMsg(new LMsgLmgr2LdbReqUpdateBindTab);
	RegestMsg(new LMsgLdb2LmgrRspUpdateBindTab);
	RegestMsg(new LMsgLmgr2LdbReqSelectRewardTab);
	RegestMsg(new LMsgLdb2LmgrRspSelectRewardTab);
	RegestMsg(new LMsgLmgr2LdbReqUpdateRewardTab);
	RegestMsg(new LMsgLdb2LmgrRspUpdateRewardTab);
	RegestMsg(new LMsgLmgr2LdbReqInsertRewardTab);
	RegestMsg(new LMsgLdb2LmgrRspInsertRewardTab);
	
	//// 客户端申请实名认证 [XSea 2016.9.24]
	//RegestMsg(new LMsgC2SRealName);
	//// 服务器返回实名认证结果 [XSea 2016.9.24]
	//RegestMsg(new LMsgS2CRealName);
	//// 客户端申请是否已实名认证 [XSea 2016.9.24]
	//RegestMsg(new LMsgC2SIsRealName);
	//// 服务器返回是否已实名认证 [XSea 2016.9.24]
	//RegestMsg(new LMsgS2CIsRealName);
	
	//比赛内容
	RegestMsg(new LMsgS2CTips);
	RegestMsg(new LMsgC2SViewSport);
	RegestMsg(new LMsgS2CViewSport);
	RegestMsg(new LMsgC2SOptJoinSport);
	RegestMsg(new LMsgS2COptJoinSport);
	RegestMsg(new LMsgS2CSportTips);
	RegestMsg(new LMsgC2SSportRecordInfo);
	RegestMsg(new LMsgS2CSportRecordInfo);
	RegestMsg(new LMsgC2SSportRecordInfoOpt);
	RegestMsg(new LMsgS2CSportRecordInfoOpt);
	RegestMsg(new LMsgL2LMGSportResult);

	RegestMsg(new LMsgLMG2LDBReqMatchRecord);
	RegestMsg(new LMsgLDB2LMGMatchRecord);
	RegestMsg(new LMsgLMG2LDBCreateNewMatchRecord);
	RegestMsg(new LMsgLDB2LMGCreateNewMatchRecord);
	RegestMsg(new LMsgLDB2LMGModifyMatchRecord);
	RegestMsg(new LMsgLMG2LDBRmvMatchRecord);
	RegestMsg(new LMsgLMG2CEAddAddr);
	RegestMsg(new LMsgS2CUserOnlineInfo);

	RegestMsg(new LMsgLMG2LDBInsertSportSignInfo);
	RegestMsg(new LMsgLMG2LDBDeleteSportSignInfo);
	RegestMsg(new LMsgLMG2LDBUpdateSportUserInfo);
	RegestMsg(new LMsgLMG2LDBInsertSportUserInfo);
	RegestMsg(new LMsgLDB2LMGAllSportUserInfoData);
	RegestMsg(new LMsgLMG2LDBAllSportUserInfoData);
	RegestMsg(new LMsgLMG2CESportResetDesk);
	RegestMsg(new LMsgS2CUserRewardInfo);
	RegestMsg(new LMsgS2CVipInfo);
	RegestMsg(new LMsgS2CAttachManaged);
	RegestMsg(new LMsgS2CInSport);
	RegestMsg(new LMsgLMG2LMatchAddDesk);
	RegestMsg(new LMsgLMG2LDBInsertSportItemStat);
	RegestMsg(new LMsgLMG2LDBInsertSportDailyStat);
	RegestMsg(new LMsgLMG2LDBUpdateSportDailyStat);

	RegestMsg(new LMsgM2LMGLogin);
	RegestMsg(new LMsgM2CeLogin);
	RegestMsg(new LMsgM2LdbLogin);
	RegestMsg(new LMsgG2MLogin);
	RegestMsg(new LMsgL2MLogin);
	RegestMsg(new LMsgLMG2GateMatchInfo);
	RegestMsg(new LMsgLMG2LogicMatchInfo);
	RegestMsg(new LMsgLMG2MUserLogin);
	RegestMsg(new LMsgLMG2MUserReLogin);
	RegestMsg(new LMsgM2GFilterProto);
	RegestMsg(new LMsgM2LMGSynSignPlayerOpt);
	RegestMsg(new LMsgLMG2MSynAckSignPlayerOpt);
	RegestMsg(new LMsgLMG2MAckSignPlayerOpt);
	RegestMsg(new LMsgM2LMGPlayersInOutItem);
	RegestMsg(new LMsgM2LMGPlayerReward);
	RegestMsg(new LMsgM2LMGRemoveSignPlayer);
	RegestMsg(new LMsgM2LMGGetDeskIds);
	RegestMsg(new LMsgLMG2MGetDeskIds);
	RegestMsg(new LMsgLMG2MSynUserLoginInfo);
	RegestMsg(new LMsgLMG2MSynLogicIDS);
	RegestMsg(new LMsgM2LDBUpdateDailyJoinTimes);
	RegestMsg(new LMsgS2CSportBroadcast);

	//限免
	RegestMsg(new LMsgCe2LGMTimeLimitFree);
	RegestMsg(new LMsgLMG2LdbSaveGameTypeFree);
	RegestMsg(new LMsgLMG2LdbGetGameTypeFree);
	RegestMsg(new LMsgLdb2LMGGetGameTypeFree);
	RegestMsg(new LMsgC2SReqGameTypeInfo);
	RegestMsg(new LMsgS2CGameTypeInfo);

	//用户资格校验
	RegestMsg(new LMsgC2SCheckUserQualification);
	RegestMsg(new LMsgS2CCheckUserQualification);
	RegestMsg(new LMsgS2CNotifyUserQualification);
	
	return true;
}

bool LMsgFactory::Final()
{
	std::map<int,LMsg*>::iterator it = m_msgMap.begin();
	for(;it != m_msgMap.end();++it)
	{
		delete it->second;
	}
	return true;
}

void LMsgFactory::RegestMsg(LMsg* pMsg)
{
	std::map<int,LMsg*>::iterator it = m_msgMap.find(pMsg->m_msgId);
	if(it != m_msgMap.end())
	{
		LLOG_INFO("LMsgFactory::RegestMsg msg already existed msgId:%d",pMsg->m_msgId);
	}
	else
	{
		m_msgMap[pMsg->m_msgId] = pMsg;
	}
}

LMsg* LMsgFactory::CreateMsg(int msgId)
{
	std::map<int,LMsg*>::iterator it = m_msgMap.find(msgId);
	if(it == m_msgMap.end())
	{
		//LLOG_INFO("LMsgFactory::CreateMsg msg not exiset msgId:%d",msgId);
		return NULL;
	}
	else
	{
		return it->second->Clone();
	}
}
