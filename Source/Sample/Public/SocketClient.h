// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IMessage.h"
#include "NetworkDefines.h"
#include "SocketNetworkManager.h"
#include "Common/TcpListener.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "UObject/NoExportTypes.h"
#include "SocketClient.generated.h"
class USocketNetworkManager;
/**
 * 
 */
UCLASS()
class SAMPLE_API USocketClient : public UObject
{
	GENERATED_BODY()
public:
	USocketClient();
private:
	TUniquePtr<FSocket> SocketClient;
	TUniquePtr<FTcpListener> Listener;
	const uint32 BufferSize = 1024 * 8 * 2;
	UPROPERTY()
	FBytesBuffer SocketBuffer;
	const size_t PacketTotalSize = sizeof(uint16);
	const size_t PacketMsgIdSize = sizeof(uint16);
	unsigned long long BitSweepSize = sizeof(uint8);
	TQueue<FNetReceiveResult> ReceivedPackets;
	EServerId ConnectedServerId;
	bool bIsConnected = false;
	bool bIsLogined = false;
	ENetworkCloseReason NetworkCloseReason = ENetworkCloseReason::None;
	TSharedPtr<IMessage> ReserveMessage;
public:
	void Connect(const FString& InIpAddress, const int32 InPort);
	void SendPacket(const TArray<uint8>& InData) const;
	bool Dispatch();
	void Close(const ENetworkCloseReason NetCloseReason = ENetworkCloseReason::None);
	bool IsConnected() const
	{
		return bIsConnected;
	}
	bool IsLogined() const
	{
		return bIsLogined;
	}
	void SetLogin(bool InbIsLogin)
	{
		if(bIsLogined !=InbIsLogin)
		{
			bIsLogined = InbIsLogin;
			if(InbIsLogin == true && ReserveMessage.IsValid() == true)
			{
				USocketNetworkManager::GetInstance()->SendPacket(ConnectedServerId, ReserveMessage);
				ReserveMessage = nullptr;
			}
		}
	}
	EServerId GetConnectedServerId() const
	{
		return ConnectedServerId;
	}
	ENetworkCloseReason GetNetworkCloseReason() const
	{
		return NetworkCloseReason;
	}
	void SetReserveMessage(const TSharedPtr<IMessage>& InMessage)
	{
		ReserveMessage = InMessage;	
	}
private:
	bool OnConnectedCallback(FSocket* InSocket, const FIPv4Endpoint& InFiPv4Endpoint);
	void OnReadCallback();
	void AddData(const TArray<uint8>& InDataBuffer);
	bool CanProcessPacket();
	TArray<uint8> GetPacket();
};
