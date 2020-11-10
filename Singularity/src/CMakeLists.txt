# Add subdirectories

add_subdirectory(parse)
add_subdirectory(node)
add_subdirectory(exceptions)

# Add the binary and sources
add_executable(
  ../../parser
  main.cc
)

SET(GCC_COVERAGE_LINK_FLAGS "-L/usr/lib/llvm-7/lib /usr/lib/llvm-7/lib/libLLVM-7.so -lLLVM-7")

target_link_libraries(../../parser parse node exceptions ${GCC_COVERAGE_LINK_FLAGS})
