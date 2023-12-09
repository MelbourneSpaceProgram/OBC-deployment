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
  
    const U8 mock_data[10] = "mock_data";
    Fw::ComBuffer combuffer (mock_data, 10);
    this->send2Framer_out (0, combuffer, 0);
    this->log_ACTIVITY_LO_CONFIG_ISSUED ("mock config issued");
  }

} // end namespace OBC
