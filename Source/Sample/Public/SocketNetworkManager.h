// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMessage.h"
#include "ProtoBufBase.h"
#include "UObject/NoExportTypes.h"
#include "SocketNetworkManager.generated.h"

class USocketPacketHandlerAuth;
/**
 * 
 */
class USocketPacketHandler;
class USocketClient;
UCLASS()
class SAMPLE_API USocketNetworkManager : public UObject
{
	GENERATED_BODY()
private:
	static TObjectPtr<USocketNetworkManager> Instance;
	UPROPERTY(Transient)
	TArray<TObjectPtr<USocketPacketHandler>> PacketHandlersArray;
	UPROPERTY(Transient)
	TArray<TObjectPtr<USocketClient>> SocketClientsArray;
	TArray<FString> ErrorMsgsArray;
	TObjectPtr<USocketPacketHandlerAuth> PacketHandlerAuth;
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
	void SendPacket(const EServerId InServerId, UProtoBufBase* InMessage) const;
	void SendPacketWithConnectCheck(const EServerId InServerId, UProtoBufBase* InMessage) const;
	void SendPacketWithExitCheck(const EServerId InServerId, UProtoBufBase* InMessage) const;
	
	USocketPacketHandlerAuth* GetAuthHandler()
	{
		return PacketHandlerAuth;
	}
	
private:
	static TArray<uint8> ConvertSendBytes(const uint16 InData);
	USocketNetworkManager();
	void CheckNetworkError();
	TObjectPtr<USocketClient> GetSocketClient(const EServerId InServerId) const;
	void ExitNConnect(const FString& InIP, const int32 InPort) const;
	virtual void BeginDestroy() override;
	void Initialize();
};
