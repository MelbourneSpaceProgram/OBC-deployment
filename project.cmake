# This CMake file is intended to register project-wide objects so they can be
# reused easily between deployments, but also by other projects.

add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Components/Controllers/Adapter/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Components/Controllers/PacketSender/")

add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Components/Structs/SubSystemEnum/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Components/Structs/DataPacket/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Components/Structs/AdapterPorts/")