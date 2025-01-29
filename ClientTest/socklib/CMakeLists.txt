add_library(socklib socklib.cpp socklib.hpp)
set_property(TARGET socklib PROPERTY CXX_STANDARD 20)
target_include_directories(socklib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS socklib)
