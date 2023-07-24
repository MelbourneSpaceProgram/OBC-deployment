// ======================================================================
// \title  CamController.hpp
// \author root
// \brief  hpp file for CamController component implementation class
// ======================================================================

#ifndef CamController_HPP
#define CamController_HPP

#include "Components/Controllers/CamController/CamControllerComponentAc.hpp"

namespace OBC {

  class CamController :
    public CamControllerComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object CamController
      //!
      CamController(
          const char *const compName /*!< The component name*/
      );

      //! Destroy object CamController
      //!
      ~CamController();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for TAKE_PHOTO command handler
      //! 
      void TAKE_PHOTO_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );


    };

} // end namespace OBC

#endif
