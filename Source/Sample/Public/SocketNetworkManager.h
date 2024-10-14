// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMessage.h"
#include "ProtoBufBase.h"
#include "SocketClient.h"
#include "UObject/NoExportTypes.h"
#include "SocketNetworkManager.generated.h"

/**
 * 
 */
class USocketPacketHandler;
UCLASS()
class SAMPLE_API USocketNetworkManager : public UObject
{
	GENERATED_BODY()
private:
	static USocketNetworkManager* Instance;
	UPROPERTY()
	TArray<USocketPacketHandler*> PacketHandlersArray;
	UPROPERTY()
	TArray<USocketClient*> SocketClientsArray;
	TArray<FString> ErrorMsgsArray;
public:
	static USocketNetworkManager* GetInstance();
	UGameMessage* FindPacketMessage(EMsgId InMsgId);
	void AddHandler(USocketPacketHandler* InSocketPacketHandler);
	void Connect(const EServerId InServerId) const;
	void Connect(const FString& InIP, const int32 InPort) const;
	void Connect(const int32 InServerIndex, const FString& InIP, const int32 InPort) const;
	void OnTick();
	void CloseNetwork(EServerId InServerId, ENetworkCloseReason InNetworkCloseReason = ENetworkCloseReason::None) const;
	void CloseAllNetworkSockets(const ENetworkCloseReason InNetworkCloseReason = ENetworkCloseReason::None);
	bool IsConnectedServer(const EServerId InServerId) const;
	void SendPacket(const EServerId InServerId, UProtoBufBase* InMessage);
	void SendPacketWithConnectCheck(const EServerId InServerId, UProtoBufBase* InMessage);
private:
	USocketNetworkManager();
	void CheckNetworkError();
	USocketClient* GetSocketClient(const EServerId InServerId) const;
};
