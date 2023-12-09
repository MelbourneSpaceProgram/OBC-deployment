// ======================================================================
// \title  CommController.cpp
// \author root
// \brief  cpp file for CommController component implementation class
// ======================================================================


#include <Components/Controllers/CommController/CommController.hpp>
#include <FpConfig.hpp>

namespace OBC {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  CommController ::
    CommController(
        const char *const compName
    ) : CommControllerComponentBase(compName)
  {

  }

  CommController ::
    ~CommController()
  {

  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void CommController ::
    SEND_CONFIG_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        const Fw::CmdStringArg& configName
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  
    const U8 mock_data[] = "mock_data";
    this->send2Framer_out (mock_data, sizeof (mock_data), Fw::ComPacket::FW_PACKET_COMMAND);
    this->log_ACTIVITY_LOW_CONFIG_ISSUED ("mock config issued");
  }

} // end namespace OBC
