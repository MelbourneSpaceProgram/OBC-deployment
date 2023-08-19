#include "ObcDataFramingProtocol.hpp"
#include <FpConfig.hpp>
#include "Utils/Hash/Hash.hpp"

namespace OBC_Deployment {

ObcDataFraming::ObcDataFraming(): FramingProtocol() {}

ObcDataDeframing::ObcDataDeframing(): DeframingProtocol() {}

void ObcDataFraming::frame (const U8* const data, const U32 size, Fw::ComPacket::ComPacketType packet_type) {
    U16 syncHeader = OpenLstHeader::START_WORD;
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

DeframingProtocol::DeframingStatus ObcDataDeframing::deframe(Types::CircularBuffer& ring, U32& needed) {
    FW_ASSERT(m_interface != nullptr);
    // Check for header or ask for more data
    if (ring.get_allocated_size() < OpenLstHeader::SIZE) {
        needed = OpenLstHeader::SIZE;
        return DeframingProtocol::DEFRAMING_MORE_NEEDED;
    }

    // Read start value from header
    U8 start0, start1;
    Fw::SerializeStatus status = ring.peek(start0, 0);
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);
    Fw::SerializeStatus status = ring.peek(start1, sizeof(U8)); //read 2nd byte
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);

    U16 start = start0 << 8;
    start = start | start1;
    if (start != OpenLstHeader::START_WORD) {
        // Start word must be valid
        return DeframingProtocol::DEFRAMING_INVALID_FORMAT;
    }

    // Read length from header
    U8 length;
    status = ring.peek(length, 2*sizeof(U8)); //read 3rd byte
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);
    needed = (sizeof(OpenLstHeader::START_WORD) + sizeof(length) + length);

    //check frame size
    if (needed > ring.get_capacity()) {
        // Frame size is too large for ring buffer
        return DeframingProtocol::DEFRAMING_INVALID_SIZE;
    }
    // Check for enough data to deserialize everything;
    // otherwise break and wait for more.
    else if (ring.get_allocated_size() < needed) {
        return DeframingProtocol::DEFRAMING_MORE_NEEDED;
    }

    //Skip checksum, OpenLst has no checksum

    Fw::Buffer buffer = m_interface->allocate(size);

    // Some allocators may return buffers larger than requested.
    // That causes issues in routing; adjust size.
    FW_ASSERT(buffer.getSize() >= size);
    buffer.setSize(size);
    status = ring.peek(buffer.getData(), size, 3*sizeof(U8)); //read the rest after 3rd byte
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);
    m_interface->route(buffer);
    return DeframingProtocol::DEFRAMING_STATUS_SUCCESS;

}

}