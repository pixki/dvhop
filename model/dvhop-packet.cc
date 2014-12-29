#include "dvhop-packet.h"
#include "ns3/packet.h"
#include "ns3/address-utils.h"

namespace ns3
{
  namespace dvhop
  {

    NS_OBJECT_ENSURE_REGISTERED (FloodingHeader);

    FloodingHeader::FloodingHeader()
    {
    }

    FloodingHeader::FloodingHeader(uint32_t xPos, uint32_t yPos, uint16_t seqNo, uint16_t hopCount, Ipv4Address beacon)
    {
      m_xPos     = xPos;
      m_yPos     = yPos;
      m_seqNo    = seqNo;
      m_hopCount = hopCount;
      m_beaconId = beacon;
    }

    TypeId
    FloodingHeader::GetTypeId ()
    {
      static TypeId tid = TypeId("ns3::dvhop::FloodingHeader")
          .SetParent<Header> ()
          .AddConstructor<FloodingHeader>();
      return tid;
    }

    TypeId
    FloodingHeader::GetInstanceTypeId () const
    {
      return GetTypeId ();
    }

    uint32_t
    FloodingHeader::GetSerializedSize () const
    {
      return 16; //Total number of bytes when serialized
    }

    void
    FloodingHeader::Serialize (Buffer::Iterator start) const
    {
      start.WriteU32 (m_xPos);
      start.WriteU32 (m_yPos);
      start.WriteU16 (m_seqNo);
      start.WriteU16 (m_hopCount);
      WriteTo(start, m_beaconId);
    }

    uint32_t
    FloodingHeader::Deserialize (Buffer::Iterator start)
    {
      Buffer::Iterator i = start;
      m_xPos = i.ReadU32 ();
      m_yPos = i.ReadU32 ();
      m_seqNo = i.ReadU16 ();
      m_hopCount = i.ReadU16 ();
      ReadFrom (i, m_beaconId);

      //Validate the readed bytes match the serialized size
      uint32_t dist = i.GetDistanceFrom (start);
      NS_ASSERT (dist == GetSerializedSize () );
      return dist;
    }

    void
    FloodingHeader::Print (std::ostream &os) const
    {
      os << "Beacon: " << m_beaconId << " ,hopCount: " << m_hopCount;

    }

    std::ostream &
    operator<< (std::ostream &os, FloodingHeader const &h)
    {
      h.Print (os);
      return os;
    }



  }
}
