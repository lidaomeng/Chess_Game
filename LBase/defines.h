#ifndef __defines_h_
#define __defines_h_

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

enum ErrorCode
{
	ErrorNone = 0,
	UserNotExist = 1,
	TaskNotExist = 2,
	ExceedMaximum = 3,
	AlreadyBinded = 4,
	NotQualified = 5,
	TaskNotFinished = 6,
	Expired = 7,
	BindingSelf = 8,
	Unknown = 100
};

enum CouponChangedReason
{
	ReasonNone = 0,
	PlayingGame = 1,
	UserShared = 2,
	LuckyDraw = 3,
	BindingInviter = 4,
	ExchangeGift = 5,
	CCSportReward = 6
};

typedef boost::uuids::uuid					Luuid;

typedef boost::hash<boost::uuids::uuid>		LuuidHasher;

#define Luuid2String						boost::uuids::to_string

#define Luuid_NULL				boost::uuids::nil_generator()()


#endif	// __defines_h_
