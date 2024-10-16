// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketPacketHandlerAuth.h"
#include "FGameMessageLoginRes.h"
#include "FSLoginReq.h"

TSharedPtr<FGameMessage> USocketPacketHandlerAuth::FindPacketMessage(const EMsgId InMsgId)
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
			return MakeShareable(new FGameMessageLoginRes());
			break;
		}
	}
}

void USocketPacketHandlerAuth::LoginReq(const EServerId InServerId)
{
	const TSharedPtr<FSLoginReq> LoginReq = MakeShareable(new FSLoginReq(InServerId));

	USocketNetworkManager::GetInstance()->SendPacket(InServerId, LoginReq);
}
