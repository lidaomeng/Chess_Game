#ifndef __BaseCommonFunc_h
#define __BaseCommonFunc_h

#include <string>
#include "LBase.h"
#include "LMsg.h"

void			DisableIP(const std::string& ip);

unsigned short CalcChecksum(unsigned char *data, int dataSize);

bool			IsValidCellphoneNo(const std::string& no);

bool			IsValidIDCard(const std::string& idcard);

Llong			GetOSTickCount();

LMsg*			ParseInsideNetPacket(LBuffPtr recv, LSocketPtr s);

Lint			TransfromMsgId(Lint timestamp, Lint msgId);
Lint			InverseTransfromMsgId(Lint timestamp, Lint transedMsgId);

std::time_t		GetLastModifiedTime(const char* path);

bool			tokenize(const Lstring& str, std::vector<Lstring>& tokens, const Lstring& delims);

bool			safe_atoi(const Lstring &str, Lint &num);

bool			safe_atof(const std::string &str, Lfloat &num);

#endif		// __BaseCommonFunc_h