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
#include <ctime>
#include <sstream>
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
    TAKE_PHOTO_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    const char* CAM_API_URL = "192.168.0.97:6001/capturedImage.jpg";
    std::stringstream ss;
    std::time_t timestamp = std::time(nullptr);
    ss << timestamp;
    std::string filename = "capturedImages/" + ss.str() + ".jpg";

    FILE *file = fopen(filename.c_str(), "wb");
    if (!file) {
      this->log_ACTIVITY_HI_OpenFileError();
      return;
    }
    
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, file); 
      curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
      curl_easy_setopt(curl, CURLOPT_URL, CAM_API_URL);
      
      /* Perform the request, res will get the return code */
      res = curl_easy_perform(curl);
      /* Check for errors */
      if(res != CURLE_OK) {
        this->log_ACTIVITY_HI_TakePhotoError();
        std::cout << res << std::endl;
        return;
      }
        
    }
    /* always cleanup */
    curl_easy_cleanup(curl);
    fclose(file);

    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace OBC
