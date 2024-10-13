// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BytesBuffer.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "UObject/NoExportTypes.h"
#include "SocketClient.generated.h"

class FTcpListener;
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
	TUniquePtr<UBytesBuffer> DataBuffer;
	const size_t PacketTotalSize = sizeof(uint16);
	const size_t PacketMsgIdSize = sizeof(uint16);
	unsigned long long BitSweepSize = sizeof(uint8);
	TQueue<FNetReceiveResult> ReceivedPackets;
	
public:
	bool Open(const FString& InIpAddress, const int32 InPort);
	void Close();
private:
	void Connect(const FString& InIpAddress, const int32 InPort);
	bool OnConnectedCallback(FSocket* InSocket, const FIPv4Endpoint& InFiPv4Endpoint);
	void OnTick();
};
