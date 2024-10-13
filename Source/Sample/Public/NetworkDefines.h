// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NetworkDefines.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLE_API UNetworkDefines : public UObject
{
	GENERATED_BODY()
public:
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
	enum class EServerId : uint8
	{
		PlazaServer = 0 UMETA(DisplayName="PlazaServer"),
		VillageServer = 1 UMETA(DisplayName="VillageServer"),
		LandMapServer = 2 UMETA(DisplayName="LandMapServer"),
	};
	enum class EMsgId : uint8
	{
		NONE = 0,
		S_LOGIN_REQ = 1 UMETA(DisplayName="S_LOGIN_REQ"),
		C_LOGIN_RES = 2 UMETA(DisplayName="C_LOGIN_RES"),
		///
		/// ...
		///
	};
};
