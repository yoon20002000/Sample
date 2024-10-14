// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketClient.h"

#include "GameMessage.h"
#include "GameMessageManager.h"
#include "Common/TcpListener.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NetworkDefines.h"
#include "SocketNetworkManager.h"
#include "SocketPacketHandlerAuth.h"

USocketClient::USocketClient() : SocketClient(nullptr), Listener(nullptr), ConnectedServerId(GDefault_ServerId)
{
}

bool USocketClient::Dispatch()
{
	check(SocketClient);
	if(SocketClient == nullptr)
	{
		return false;
	}

	if(ReceivedPackets.IsEmpty() == false)
	{
		FNetReceiveResult Result;
		while (ReceivedPackets.Dequeue(Result))
		{
			TObjectPtr<UGameMessage> Message = USocketNetworkManager::GetInstance()->FindPacketMessage(static_cast<EMsgId>(Result.PacketType));
			if(Message != nullptr)
			{
				Message->SetData(Result.DataArray);
				UGameMessageManager::GetInstance()->AddMessage(Message);
			}
			else
			{
				const FString ErrorMsg = FString::Format(TEXT("Type: {0}, Length: {1}"), {GetEnumDisplayName(static_cast<EMsgId>(Result.PacketType)).ToString() ,Result.DataArray.Num() });
				UKismetSystemLibrary::PrintString(GetWorld(), ErrorMsg);
				break;
			}
		}
	}
	
	return true;
}

void USocketClient::Close(const ENetworkCloseReason NetCloseReason)
{
	NetworkCloseReason = NetCloseReason;
	if(Listener != nullptr)
	{
		Listener.Reset();
	}
	
	if(SocketClient != nullptr)
	{
		SocketClient.Reset();
	}

	bIsConnected = false;
	bIsLogined = false;
}

void USocketClient::Connect(const FString& InIpAddress, const int32 InPort)
{
	FIPv4Address IPAddress;
	FIPv4Address::Parse((FString("0.0.0.0")), IPAddress);

	FIPv4Endpoint Endpoint(IPAddress, (uint16)2213);

	Listener = MakeUnique<FTcpListener>(Endpoint);

	Listener->OnConnectionAccepted().BindUObject(this, &USocketClient::OnConnectedCallback);
}

bool USocketClient::OnConnectedCallback(FSocket* InSocket, const FIPv4Endpoint& InFiPv4Endpoint)
{
	UKismetSystemLibrary::PrintString(GetWorld(), "Connected!!");

	bIsConnected = true;

	ConnectedServerId = GetServerIdByPort(InFiPv4Endpoint.Port);

	FTimerHandle WaitDisconnectHandle;
	GetWorld()->GetTimerManager().SetTimer(WaitDisconnectHandle, [this, &WaitDisconnectHandle]()
		{
			if (SocketClient == nullptr ||  IsLogined() == false || IsConnected() == false)
			{		
				GetWorld()->GetTimerManager().ClearTimer(WaitDisconnectHandle);
			}
			OnReadCallback();
		}, 0.1f, true);  
	
	USocketNetworkManager::GetInstance()->GetAuthHandler()->LoginReq(ConnectedServerId);
	
	return true;
}

void USocketClient::OnReadCallback()
{
	if(SocketClient)
	{
		if(SocketClient->GetConnectionState() == SCS_Connected)
		{
			uint32 PendingData = 0;
			if(SocketClient->HasPendingData(PendingData))
			{
				TArray<uint8> Bytes;
				Bytes.SetNum(PendingData);
				int32 BytesRead = 0;
				if(SocketClient->Recv(Bytes.GetData(), PendingData,BytesRead))
				{
					AddData(Bytes);

					while (true)
					{
						if(CanProcessPacket())
						{
							break;
						}
						
						const uint8* Pivot = Bytes.GetData();

						uint16 InComePacketSize;
						FMemory::Memcpy(&InComePacketSize, Pivot, PacketTotalSize);
						// Set Little endian 
						InComePacketSize = (InComePacketSize << BitSweepSize) | (InComePacketSize >> BitSweepSize);

						Pivot += PacketTotalSize;

						// msg id
						uint16 InComePacketID;
						FMemory::Memcpy(&InComePacketID, Pivot, PacketMsgIdSize);
						// Set Little endian
						InComePacketID = (InComePacketID << BitSweepSize) | (InComePacketID >> BitSweepSize);

						Pivot += PacketMsgIdSize;

						TArray<uint8> PacketData;
						PacketData.Append(Pivot, Bytes.Num() - PacketTotalSize - PacketMsgIdSize);

						FNetReceiveResult Packet(InComePacketSize, PacketData);

						ReceivedPackets.Enqueue(Packet);
					}
				}
				else
				{
					Close();
				}
			}
		}
		else 
		{
			Close();
		}
	}
}

void USocketClient::AddData(const TArray<uint8>& InDataBuffer)
{
	SocketBuffer.DataBuffer.Append(InDataBuffer);
	SocketBuffer.Tail += InDataBuffer.Num();
}

bool USocketClient::CanProcessPacket()
{
	uint16 PacketSize = 0;

	FMemory::Memcpy(&PacketSize,SocketBuffer.DataBuffer.GetData(),sizeof(uint16_t));
	
	return SocketBuffer.Tail >= PacketSize;
}

TArray<uint8> USocketClient::GetPacket()
{
	const int32 FrontPacketSize = SocketBuffer.FrontPacketSize;
	
	TArray<uint8> Packet;
	Packet.Reserve(FrontPacketSize);
	Packet.Append(SocketBuffer.DataBuffer.GetData(), FrontPacketSize);
	SocketBuffer.DataBuffer.RemoveAt(0, FrontPacketSize);

	SocketBuffer.Tail -= FrontPacketSize;
	return Packet;

}

void USocketClient::SendPacket(const TArray<uint8>& InData) const
{
	check(SocketClient);
	check(Listener);
	
	TArray<uint8> Bytes;
	FMemoryWriter MemoryWriter(Bytes);

	FString Message = "Send Message";
	MemoryWriter << Message;

	if(int32 BytesSent = 0; !SocketClient->Send(Bytes.GetData(), Bytes.Num(), BytesSent))
	{
		UKismetSystemLibrary::PrintString(GetWorld(), "Unable to send data");
	}
}
