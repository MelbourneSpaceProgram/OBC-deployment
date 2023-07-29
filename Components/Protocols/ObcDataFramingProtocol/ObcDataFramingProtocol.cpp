#include "ObcDataFramingProtocol.hpp"
#include <FpConfig.hpp>
#include "Utils/Hash/Hash.hpp"

namespace OBC_Deployment {

ObcDataFraming::ObcDataFraming(): FramingProtocol() {}

ObcDataDeframing::ObcDataDeframing(): DeframingProtocol() {}

void ObcDataFraming::frame (const U8* const data, const U32 size, Fw::ComPacket::ComPacketType packet_type) {
    U32 syncHeader = 0x2269;
    U8 length = size; //Number of bytes that comes after B0-B2, see Ricardo. J. Fig. 2
    U32 total_size = sizeof (syncHeader) + sizeof (length) + length;

    U8 hwIdLsb = 0x0; //TODO: hard-coded HWID LSB
    U8 hwIdMsb = 0x0; //TODO: hard-coded HWID MSB
    U8 sqnNumLsb = m_sqnNum & 0x0f; //bitwise AND to take LSB
    U8 sqnNumMsb = (m_sqnNum & 0xf0) >> 4; //take MSB
    m_sqnNum++;

    U8 dest = 0x0; //TODO: hard-coded DEST field
    U8 cmdNum = 0x0; //TODO: how is this determined?

    // now fill these fields in
    Fw::Buffer buffer = m_interface->allocate (total_size);
    Fw::SerializeBufferBase& serializer = buffer.getSerializeRepr();

    Fw::SerializeStatus status;
    status = serializer.serialize (syncHeader);
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);

    status = serializer.serialize (length);
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);

    status = serializer.serialize (hwIdLsb);
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);

    status = serializer.serialize (hwIdMsb);
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);

    status = serializer.serialize (sqnNumLsb);
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);

    status = serializer.serialize (sqnNumMsb);
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);

    status = serializer.serialize (dest);
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);

    status = serializer.serialize(data, size, true);  // Serialize without length
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);

    //send
    buffer.setSize (total_size);
    m_interface->send (buffer);
}

bool ObcDataDeframing::validate(Types::CircularBuffer& ring, U32 size) {

}

DeframingProtocol::DeframingStatus FprimeDeframing::deframe(Types::CircularBuffer& ring, U32& needed) {

}

}