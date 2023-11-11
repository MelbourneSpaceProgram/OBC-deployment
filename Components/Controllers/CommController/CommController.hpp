// ======================================================================
// \title  CommController.hpp
// \author root
// \brief  hpp file for CommController component implementation class
// ======================================================================

#ifndef CommController_HPP
#define CommController_HPP

#include "Components/Controllers/CommController/CommControllerComponentAc.hpp"

namespace OBC {

  class CommController :
    public CommControllerComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object CommController
      //!
      CommController(
          const char *const compName /*!< The component name*/
      );

      //! Destroy object CommController
      //!
      ~CommController();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for SEND_CONFIG command handler
      //! 
      void SEND_CONFIG_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          const Fw::CmdStringArg& configName 
      );


    };

} // end namespace OBC

#endif
