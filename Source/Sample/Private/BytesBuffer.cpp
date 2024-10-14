// Fill out your copyright notice in the Description page of Project Settings.


#include "BytesBuffer.h"

UBytesBuffer::UBytesBuffer() : Tail(0), FrontPacketSize(0)
{
}

void UBytesBuffer::AddData(const TArray<uint8>& InData)
{
	const int32 DataSize = InData.Num();

	DataBuffer.Append(InData.GetData(), DataSize);

	Tail += DataSize;
}

bool UBytesBuffer::CanProcessPacket()
{
	uint16 PacketSize = 0;
	std::memcpy(&PacketSize, DataBuffer.GetData(), sizeof(uint16_t));
	return Tail >= PacketSize;
}

TArray<uint8> UBytesBuffer::GetPacket()
{
	TArray<uint8> Packet;
	Packet.Reserve(FrontPacketSize);

	Packet.Append(DataBuffer.GetData(), FrontPacketSize);
	DataBuffer.RemoveAt(0, FrontPacketSize);

	Tail -= FrontPacketSize;
	return Packet;
}
