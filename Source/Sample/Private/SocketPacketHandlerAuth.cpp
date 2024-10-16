// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketPacketHandlerAuth.h"
#include "GameMessageLoginRes.h"
#include "SLoginReq.h"

TSharedPtr<GameMessage> USocketPacketHandlerAuth::FindPacketMessage(const EMsgId InMsgId)
{
	switch (InMsgId)
	{
	case EMsgId::None:
	default:
		{
			UE_LOG(LogTemp, Error, TEXT("Not valid msgId : %s"), *GetEnumDisplayName(InMsgId).ToString());
			return nullptr;
		}
	case EMsgId::C_Login_Res:
		{
			return MakeShareable(new GameMessageLoginRes());
			break;
		}
	}
}

void USocketPacketHandlerAuth::LoginReq(const EServerId InServerId)
{
	const TSharedPtr<SLoginReq> LoginReq = MakeShareable(new SLoginReq(InServerId));

	USocketNetworkManager::GetInstance()->SendPacket(InServerId, LoginReq);
}
