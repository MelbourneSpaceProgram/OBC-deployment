set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/ObcDataFramingProtocol.cpp"  
)
# Note: supply non-explicit dependencies here
set(MOD_DEPS
   Svc/FramingProtocol
)

register_fprime_module()