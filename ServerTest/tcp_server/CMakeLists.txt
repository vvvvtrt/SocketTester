add_library(tcp_server tcp_server.cpp tcp_server.hpp)
set_property(TARGET tcp_server PROPERTY CXX_STANDARD 20)
target_include_directories(tcp_server PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS tcp_server)
