set(file "/home/servicerobot2/catkin_ws2/build/phidgets_drivers/libphidget21/EP_libphidget21-prefix/src/libphidget_2.1.8.20151217.tar.gz")
message(STATUS "verifying file...
     file='${file}'")
set(expect_value "818ab2ff1de92ed9568a206e0e89657f")
file(MD5 "${file}" actual_value)
if("${actual_value}" STREQUAL "${expect_value}")
  message(STATUS "verifying file... done")
else()
  message(FATAL_ERROR "error: MD5 hash of
  ${file}
does not match expected value
  expected: ${expect_value}
    actual: ${actual_value}
")
endif()
