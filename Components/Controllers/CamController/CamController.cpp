// ======================================================================
// \title  CamController.cpp
// \author root
// \brief  cpp file for CamController component implementation class
// ======================================================================


#include <Components/Controllers/CamController/CamController.hpp>
#include <FpConfig.hpp>

namespace OBC {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  CamController ::
    CamController(
        const char *const compName
    ) : CamControllerComponentBase(compName)
  {

  }

  CamController ::
    ~CamController()
  {

  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void CamController ::
    CREATE_DIR_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        const Fw::CmdStringArg& dir_name
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace OBC
