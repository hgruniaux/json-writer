# Install Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/cb455a71fb23303e37ce8ee5b1cde6a2c18f66a5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(json_writer_unittest "impl.cpp" "write_null_test.cpp" "write_bool_test.cpp" "write_object_test.cpp" "write_array_test.cpp" "write_string_test.cpp" "write_number_test.cpp" "write_field_test.cpp")
target_link_libraries(json_writer_unittest GTest::gtest_main)
target_include_directories(json_writer_unittest PRIVATE "../")

# Register unit tests
include(GoogleTest)
gtest_discover_tests(json_writer_unittest)
