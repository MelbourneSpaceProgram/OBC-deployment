#ifndef OBC_FRAMING_HPP
#define OBC_FRAMING_HPP

#include <Svc/FramingProtocol/FramingProtocol.hpp>
#include <Svc/FramingProtocol/DeframingProtocol.hpp>

namespace OBC_Deployment {
    
  //! \brief Implements the pure OpenLST framing protocol
  class ObcDataFraming: public FramingProtocol {
    public:

      //! Constructor
      ObcDataFraming();

      //! Implements the frame method
      void frame(
          const U8* const data, //!< The data
          const U32 size, //!< The data size in bytes
          Fw::ComPacket::ComPacketType packet_type //!< The packet type
      ) override;

    private:
      U16 m_sqnNum {0x00};
  };

  //! \brief Implements the pure OpenLST deframing protocol
  class ObcDataDeframing : public DeframingProtocol {
    public:

      //! Constructor
      ObcDataDeframing();

      //! Validates data against the stored hash value
      bool validate(
          Types::CircularBuffer& buffer, //!< The circular buffer
          U32 size //!< The data size in bytes
      );

      //! Implements the deframe method
      //! \return Status
      DeframingStatus deframe(
          Types::CircularBuffer& buffer, //!< The circular buffer
          U32& needed //!< The number of bytes needed, updated by the caller
      ) override;

  };
  
}

#endif