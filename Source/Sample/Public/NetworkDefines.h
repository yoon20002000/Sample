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
	FNetReceiveResult() : PacketType(0)
	{
		
	}
	FNetReceiveResult(const int32 InPacketType, const TArray<uint8>& InDataArray): PacketType(InPacketType), DataArray(InDataArray)
	{
	}
};

UENUM()
enum class ENetworkCloseReason : uint16
{
	None = 0						UMETA(DisplayName="None"),
	NetworkOpenFail					UMETA(DisplayName="NetworkOpenFail"),
	TCPClientIsNull					UMETA(DisplayName="TCPClientIsNull"),
	SocketEndConnectException		UMETA(DisplayName="SocketEndConnectException"),
	OpenException					UMETA(DisplayName="OpenException"),
	PacketReadCountZero				UMETA(DisplayName="PacketReadCountZero"),
	PacketEndReadException			UMETA(DisplayName="PacketEndReadException"),
	PacketObjectDisposedException	UMETA(DisplayName="PacketObjectDisposedException"),
	PacketWriteException			UMETA(DisplayName="PacketWriteException"),
	ExitEditor						UMETA(DisplayName="ExitEditor"),
	SomeServerError					UMETA(DisplayName="SomeServerError"),
	QuitGame						UMETA(DisplayName="QuitGame"),
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

constexpr int32 GPacket_Header_Size = sizeof(uint16) + sizeof(uint16) ;
constexpr int32 GVillage_Port = 10645;
constexpr int32 GPlaza_Port = 10245;
constexpr int32 GLandMap_Port = 10445;
const FString GServer_IP = TEXT("127.0.0.1");
template<typename TEnum>
FText GetEnumDisplayName(TEnum InEnumValue)
{
	const UEnum* EnumPtr = StaticEnum<TEnum>();
	if (!EnumPtr) return FText::GetEmpty();

	return EnumPtr->GetDisplayNameTextByValue(static_cast<uint8>(InEnumValue));
}

inline EServerId GetConnectServerIdByPort(const int32 InPort)
{
	switch (InPort)
	{
	case GPlaza_Port:
		{
			return EServerId::PlazaServer;
		};
	case GVillage_Port:
		{
			return EServerId::VillageServer;
		}
	case GLandMap_Port:
	default:
		{
			return EServerId::LandMapServer;
		}
	}
}
inline int32 GetConnectServerPortByID(const EServerId InServerId)
{
	switch (InServerId)
	{
		case EServerId::PlazaServer:
			{
				return GPlaza_Port;
			}
		case EServerId::VillageServer:
			{
				return GVillage_Port;
			}
		case EServerId::LandMapServer:
		default: 
			{
				return GLandMap_Port;
			}
	}
}

/**
 * 
 */
UCLASS()
class SAMPLE_API UNetworkDefines : public UObject
{
	GENERATED_BODY()
public:
	
	
	
};
