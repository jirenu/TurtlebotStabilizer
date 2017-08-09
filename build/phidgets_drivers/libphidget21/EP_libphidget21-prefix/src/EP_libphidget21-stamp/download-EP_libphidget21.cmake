message(STATUS "downloading...
     src='https://www.phidgets.com/downloads/libraries/libphidget_2.1.8.20151217.tar.gz'
     dst='/home/servicerobot2/catkin_ws2/build/phidgets_drivers/libphidget21/EP_libphidget21-prefix/src/libphidget_2.1.8.20151217.tar.gz'
     timeout='none'")




file(DOWNLOAD
  "https://www.phidgets.com/downloads/libraries/libphidget_2.1.8.20151217.tar.gz"
  "/home/servicerobot2/catkin_ws2/build/phidgets_drivers/libphidget21/EP_libphidget21-prefix/src/libphidget_2.1.8.20151217.tar.gz"
  SHOW_PROGRESS
  EXPECTED_HASH;MD5=818ab2ff1de92ed9568a206e0e89657f
  # no TIMEOUT
  STATUS status
  LOG log)

list(GET status 0 status_code)
list(GET status 1 status_string)

if(NOT status_code EQUAL 0)
  message(FATAL_ERROR "error: downloading 'https://www.phidgets.com/downloads/libraries/libphidget_2.1.8.20151217.tar.gz' failed
  status_code: ${status_code}
  status_string: ${status_string}
  log: ${log}
")
endif()

message(STATUS "downloading... done")
