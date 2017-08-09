execute_process(COMMAND "/home/servicerobot2/catkin_ws2/build/robot_model/kdl_parser_py/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/servicerobot2/catkin_ws2/build/robot_model/kdl_parser_py/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
