// ======================================================================
// \title  CamController.cpp
// \author root
// \brief  cpp file for CamController component implementation class
// ======================================================================


#include <Components/Controllers/CamController/CamController.hpp>
#include <FpConfig.hpp>
#include "Os/File.hpp"
#include "Fw/Logger/Logger.hpp"

#include <iostream>
// #include <stdio.h>
#include <curl/curl.h>

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
    // Os::File file;
    // Os::File::Status status = file.open("capturedImage.png", Os::File::OPEN_WRITE);
    // if (status != Os::File::OP_OK) {
    //   this->log_ACTIVITY_HI_CreatedFileError(
    //       message,
    //       status
    //   );
    //   return;
    // }

    FILE *file = fopen("capturedImage.jpg", "wb");
    if (!file) {
      Fw::Logger::logMsg("File cannot be opened");
    }
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, file); 
      curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
      curl_easy_setopt(curl, CURLOPT_URL, "192.168.0.97:6001/capturedImage.jpg");
      
      /* Perform the request, res will get the return code */
      res = curl_easy_perform(curl);
      /* Check for errors */
      if(res != CURLE_OK) {
        // this->log_ACTIVITY_HI_CreatedFileError(
        //   message,
          
        // );
        std::cout << res << std::endl;
        return;
      }
        
    }
    /* always cleanup */
    curl_easy_cleanup(curl);
    fclose(file);

    // file.~File();

    this->log_ACTIVITY_LO_CreatedFileSucceed(message);
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace OBC
