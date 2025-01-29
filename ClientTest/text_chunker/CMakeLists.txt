add_library(text_chunker text_chunker.cpp text_chunker.hpp)
set_property(TARGET text_chunker PROPERTY CXX_STANDARD 20)
target_include_directories(text_chunker PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS text_chunker)
