// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketClient.h"

#include "Common/TcpListener.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "Kismet/KismetSystemLibrary.h"

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
					// 여기에 내 버퍼 일단 넣고
					FString Message = "";
					FMemoryReader MemoryReader(Bytes);
					MemoryReader << Message;

					while (true)
					{
						// 처리 가능한지 확인 해서
						if(true)
						{
							// 다 못받은 거면 나머지 받을 때 까지 대기
							break;
						}

						// 이후 데이터 처리
						

						// 데이터 처리 하다가 에러나는거 어떻게 처리할 지 고민 해야 됨.
					}
				}
			}
		}
	}
}
