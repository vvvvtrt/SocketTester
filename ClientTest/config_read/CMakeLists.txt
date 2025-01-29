add_library(config_read config_read.cpp config_read.hpp)
set_property(TARGET config_read PROPERTY CXX_STANDARD 20)
target_include_directories(config_read PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS config_read)
