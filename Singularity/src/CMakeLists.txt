# Add subdirectories

add_subdirectory(parse)
add_subdirectory(node)

# Add the binary and sources
add_executable(
  ../../parser
  main.cc
)

target_link_libraries(../../parser parse node)
