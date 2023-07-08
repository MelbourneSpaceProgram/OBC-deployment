// ======================================================================
// \title  CamController.cpp
// \author root
// \brief  cpp file for CamController component implementation class
// ======================================================================


#include <Components/Controllers/CamController/CamController.hpp>
#include <FpConfig.hpp>
#include "Os/FileSystem.hpp"

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
        const Fw::CmdStringArg& dirName
    )
  {
    const Os::FileSystem::Status status =
      Os::FileSystem::createDirectory(dirName.toChar());
      if (status == Os::FileSystem::OP_OK) {
        this->log_ACTIVITY_LO_CREATED_DIR(dirName);
        this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
      }

    
  }

} // end namespace OBC
