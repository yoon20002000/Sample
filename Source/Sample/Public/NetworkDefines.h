// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NetworkDefines.generated.h"

USTRUCT()
struct FNetReceiveResult
{
	GENERATED_BODY()
public:
	int32 PacketType;
	TArray<uint8> DataArray;
public:
	FNetReceiveResult(const int32 InPacketType, const TArray<uint8>& InDataArray): PacketType(InPacketType), DataArray(InDataArray)
	{
	}
};

UENUM()
enum class ENetworkCloseReason : uint16
{
	None = 0,
	NetworkOpenFail,
	TCPClientIsNull,
	SocketEndConnectException,
	OpenException,

	PacketReadCountZero,
	PacketEndReadException,
	PacketObjectDisposedException,
	PacketWriteException,
	ExitEditor,
	OtherServerError,

	QuitGame,
};
UENUM()
enum class EServerId : uint8
{
	PlazaServer = 0 UMETA(DisplayName="PlazaServer"),
	VillageServer = 1 UMETA(DisplayName="VillageServer"),
	LandMapServer = 2 UMETA(DisplayName="LandMapServer"),
};
UENUM()
enum class EMsgId : uint8
{
	None = 0,
	S_Login_Req = 1 UMETA(DisplayName="S_Login_Req"),
	C_Login_Res = 2 UMETA(DisplayName="C_Login_Res"),
	///
	/// ...
	///
};


/**
 * 
 */
UCLASS()
class SAMPLE_API UNetworkDefines : public UObject
{
	GENERATED_BODY()
public:
	
	
	
};
