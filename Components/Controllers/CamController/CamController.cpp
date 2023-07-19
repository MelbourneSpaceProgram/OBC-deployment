// ======================================================================
// \title  CamController.cpp
// \author root
// \brief  cpp file for CamController component implementation class
// ======================================================================


#include <Components/Controllers/CamController/CamController.hpp>
#include <FpConfig.hpp>
#include "Os/File.hpp"

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
    CREATE_TXT_FILE_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        const Fw::CmdStringArg& message
    )
  {
    Os::File file;
    Os::File::Status status = file.open("test.txt", Os::File::OPEN_WRITE);
    if (status != Os::File::OP_OK) {
      this->log_ACTIVITY_HI_CreatedFileError(
          message,
          status
      );
      return;
    }

    NATIVE_INT_TYPE size = message.length();
    status = file.write(message.toChar(), size);

    if (status != Os::File::OP_OK) {
      this->log_ACTIVITY_HI_CreatedFileError(
          message,
          status
      );
      return;
    }

    file.~File();

    this->log_ACTIVITY_LO_CreatedFileSucceed(message);
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace OBC
