/*
 * This packet is a copy of wireless_ardusub::SimplePacket (wireless_ardusub
 * project)
 */

#ifndef DCCOMMS_PACKETS_VARIABLELENGTHPACKET_H_
#define DCCOMMS_PACKETS_VARIABLELENGTHPACKET_H_

#include <dccomms/dccomms.h>
#include <dccomms_packets/types.h>

using namespace dccomms;
namespace dccomms_packets {

class VariableLength2BPacket : public Packet {
public:
  VariableLength2BPacket();
  void CopyFromRawBuffer(void *buffer);
  uint8_t *GetPayloadBuffer();
  uint32_t GetPayloadSize();
  int GetPacketSize();
  void Read(Stream *comms);
  void PayloadUpdated(uint32_t payloadSize);

  bool PacketIsOk();

  void GetPayload(void *copy, int size);
  uint32_t SetPayload(uint8_t *data, uint32_t size);

  void UpdateFCS();

private:
  int MAX_PAYLOAD_SIZE, FCS_SIZE;
  static const int PRE_SIZE = 1;

  uint8_t *_pre;
  uint16_t *_payloadSize;
  uint8_t *_payload;
  uint8_t *_fcs;
  int _maxPacketSize;
  int _overheadSize;
  void _Init();
  bool _CheckFCS();
  void _SetPayloadSizeField(uint32_t payloadSize);
  uint32_t _GetPayloadSize();
};

class VariableLength2BPacketBuilder : public IPacketBuilder {
public:
  PacketPtr CreateFromBuffer(void *buffer) {
    auto pkt = CreateObject<VariableLength2BPacket>();
    pkt->CopyFromRawBuffer(buffer);
    return pkt;
  }
  PacketPtr Create() { return CreateObject<VariableLength2BPacket>(); }
};
}

#endif // DCCOMMS_PACKETS_SIMPLEPACKET_H_