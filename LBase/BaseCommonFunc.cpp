#include "BaseCommonFunc.h"
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include "LMsg.h"

#if _LINUX
#include <time.h> 
#include "IPFilter.h"
static bool created = false;
static boost::mutex lock;
#else
#include <windows.h>
#endif

void DisableIP(const std::string& ip)
{
#if _LINUX
	
	if(!created)
	{
		boost::lock_guard<boost::mutex> guard(lock);
		if(!created)
		{
			if(App_IPFilter::instance()->CreateIPFilterSocket() == 0)
			{
				created = true;
				App_IPFilter::instance()->SetIPFilterServer("127.0.0.1", 30000);
			}
		}
	}

	if(created)
	{
		App_IPFilter::instance()->SendFilterIPPacket(ip);
	}

#endif
}

static unsigned short bytecrc(unsigned short sum, unsigned char data)
{
	sum ^= data;

	for(int i =0; i <= 3; i++)
	{
		if((sum & 0x01) == 0)
			sum /= 2;
		else
			sum = (sum / 2) ^ 0x70B1;
	}
	return sum;
}

unsigned short CalcChecksum (unsigned char *data, int dataSize) 
{
    unsigned short sum = 0xFFFF;
	for(int i = 0; i < dataSize; i++)
		sum = bytecrc(sum, data[i]);

	return sum;
}

bool IsValidCellphoneNo(const std::string& no)
{
	const std::string expression = "^1[3|4|5|7|8]\\d{9}$";
	boost::regex reg(expression);
	return boost::regex_match(no, reg);
	return false;
}

bool IsValidIDCard(const std::string& idcard)
{
	if (idcard.length() == 15)
	{
		const std::string expression = "^[1-9]\\d{7}((0\\d)|(1[0-2]))(([0|1|2]\\d)|3[0-1])\\d{3}$";
		boost::regex reg(expression);
		return boost::regex_match(idcard, reg);
	}

	if (idcard.length() == 18)
	{
		static const int factor[] = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2 };//加权因子 
		static const int checktable[] = { 1, 0, 10, 9, 8, 7, 6, 5, 4, 3, 2 };//校验值对应表 

		char * ID = (char *)idcard.c_str();
		int IDNum[19];
		for (int i = 0; i < 18; ++i)//相当于类型转换
			IDNum[i] = ID[i] - 48;

		int checksum = 0;
		for (int i = 0; i < 17; ++i)
			checksum += IDNum[i] * factor[i];

		int compareVal = (ID[17] == 'x' || ID[17] == 'X') ? 10 : IDNum[17];
		if (checktable[checksum % 11] == compareVal)
		{
			return true;
		}
	}
	return false;
}

Llong GetOSTickCount()
{
#if _LINUX
	struct timespec ts;  
	clock_gettime(CLOCK_MONOTONIC, &ts);  
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
#else
	return (Llong)::GetTickCount64();
#endif
}

LMsg* ParseInsideNetPacket(LBuffPtr recv, LSocketPtr s)
{
	int msgid = 0;
	recv->Read(msgid);
	LMsg* msg = LMsgFactory::Instance().CreateMsg(msgid);
	if(msg != NULL)
	{
		msg->Read(*recv.get());
		msg->m_sp = s;
	}
	else
	{
		LLOG_ERROR("ParseInsideNetPacket: error msgId=%d",msgid);
	}
	return msg;
}

Lint TransfromMsgId(Lint timestamp, Lint msgId)
{
	Lint transedMsgId = (timestamp % 10000 + 1) * msgId;
	return transedMsgId;
}

Lint InverseTransfromMsgId(Lint timestamp, Lint transedMsgId)
{
	Lint msgId = timestamp > 0 ? (transedMsgId / (timestamp % 10000 + 1)) : 0;
	return msgId;
}

std::time_t GetLastModifiedTime(const char* path)
{
	boost::system::error_code ec;
	std::time_t lastModifiedTime = boost::filesystem::last_write_time(path, ec);
	if (ec)
		lastModifiedTime = 0;
	return lastModifiedTime;
}

//字符分割
bool tokenize(const Lstring& str, std::vector<Lstring>& tokens, const Lstring& delims)
{
	tokens.clear();
	if (str.length())
	{
		Lstring::size_type lastPos = 0;
		Lstring::size_type pos;
		while ((pos = str.find_first_of(delims, lastPos)) != str.npos) {
			tokens.push_back(str.substr(lastPos, pos - lastPos));
			lastPos = pos + 1;
		}
		tokens.push_back(str.substr(lastPos));
		return true;
	}
	else
	{
		return false;
	}
}

bool safe_atoi(const Lstring &str, Lint &num) {
	std::istringstream iss(str);
	return !(iss >> num).fail();
}

bool safe_atof(const std::string &str, Lfloat &num) {
	std::istringstream iss(str);
	return !(iss >> num).fail();
}

