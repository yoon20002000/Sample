// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketClient.h"

#include "Common/TcpListener.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NetworkDefines.h"

USocketClient::USocketClient() : SocketClient(nullptr), Listener(nullptr), DataBuffer(MakeUnique<UBytesBuffer>()) 
{
}

bool USocketClient::Open(const FString& InIpAddress, const int32 InPort)
{
	return true;
}

void USocketClient::Close()
{
	if(Listener != nullptr)
	{
		Listener.Reset();
	}
	
	if(SocketClient != nullptr)
	{
		SocketClient.Reset();
	}
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

	// 받아 처리하는거 넣어야됨
	// set timer로 설정 필요 예상
	// login 요청 추가 필요 
	
	return true;
}

void USocketClient::OnTick()
{
	if(SocketClient)
	{
		TArray<uint8> Bytes;
		if(SocketClient->GetConnectionState() == SCS_Connected)
		{
			uint32 PendingData = 0;
			if(SocketClient->HasPendingData(PendingData))
			{
				Bytes.SetNum(PendingData);
				int32 BytesRead = 0;
				if(SocketClient->Recv(Bytes.GetData(), PendingData,BytesRead))
				{
					DataBuffer->AddData(Bytes);

					while (true)
					{
						if(DataBuffer->CanProcessPacket())
						{
							break;
						}

						{
							const uint8* Pivot = Bytes.GetData();

							uint16 InComePacketSize;
							std::memcpy(&InComePacketSize, Pivot, PacketTotalSize);
							// Set Little indian 
							InComePacketSize = (InComePacketSize << BitSweepSize) | (InComePacketSize >> BitSweepSize);

							Pivot += PacketTotalSize;

							// msg id
							uint16 InComePacketID;
							std::memcpy(&InComePacketID, Pivot, PacketMsgIdSize);
							// Set Little indian
							InComePacketID = (InComePacketID << BitSweepSize) | (InComePacketID >> BitSweepSize);

							Pivot += PacketMsgIdSize;

							TArray<uint8> PacketData;
							PacketData.Append(Pivot, Bytes.Num() - PacketTotalSize - PacketMsgIdSize);

							FNetReceiveResult Packet(InComePacketSize, PacketData);

							ReceivedPackets.Enqueue(Packet);
						}
						
					}
				}
			}
		}
	}
}
