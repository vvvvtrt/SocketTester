# CMakeList.txt: проект CMake для ServerTest; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin.dbg)

project ("ServerTest")
add_subdirectory(config_read)
add_subdirectory(tcp_server)

add_executable (ServerTest "main.cpp")
target_link_libraries(ServerTest config_read)
target_link_libraries(ServerTest tcp_server)
# Добавьте источник в исполняемый файл этого проекта.

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ServerTest PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
