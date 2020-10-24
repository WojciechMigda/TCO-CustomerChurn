set( CMAKE_CXX_STANDARD 17 )

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package( Tsetlini 0.0.9 REQUIRED )

set(APP main)
add_executable( ${APP} "src/dummy.cpp" )
target_sources( ${APP} PRIVATE
  "src/main.cpp"
  "src/train.cpp"
  "src/infer.cpp"
  "src/read_csv.cpp"
  "src/parse_line.cpp"
  "src/data_tools.cpp"
  "src/json_io.cpp"
  "src/columns.cpp"
  "src/filesystem.cpp"
)

include_directories( "src" )
include_directories( ${Tsetlini_INCLUDE_DIR} )
include_directories(
  "$<TARGET_PROPERTY:clipp,MY_INCLUDE_DIRS>" )
include_directories(
  "$<TARGET_PROPERTY:json,MY_INCLUDE_DIRS>" )
include_directories(
  "$<TARGET_PROPERTY:fmt,MY_INCLUDE_DIRS>" )
include_directories(
  "$<TARGET_PROPERTY:dbg,MY_INCLUDE_DIRS>" )
include_directories(
  "$<TARGET_PROPERTY:spdlog,MY_INCLUDE_DIRS>" )

target_link_libraries( ${APP} ${Tsetlini_LIBRARY} stdc++fs )
