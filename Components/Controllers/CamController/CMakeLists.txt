####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
####

set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/CamController.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/CamController.cpp"
)

# Uncomment and add any modules that this component depends on, else
# they might not be available when cmake tries to build this component.

# set(MOD_DEPS

# )

register_fprime_module()

# Retrieve the name of the module that converts the root path of your project to a underscore, i.e. Fw/Types becomes Fw_Types.
get_module_name("${CMAKE_CURRENT_LIST_DIR}")

# Tell the compiler the path to the library header file.
include_directories("/workspaces/OBC-deployment/curl-7.59.0/include")
target_link_libraries(${MODULE_NAME} PUBLIC "/workspaces/OBC-deployment/curl-7.59.0/lib/libcurl.a")