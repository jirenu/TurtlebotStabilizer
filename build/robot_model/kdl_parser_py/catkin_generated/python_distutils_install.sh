#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
    DESTDIR_ARG="--root=$DESTDIR"
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/servicerobot2/catkin_ws2/src/robot_model/kdl_parser_py"

# snsure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/servicerobot2/catkin_ws2/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/servicerobot2/catkin_ws2/install/lib/python2.7/dist-packages:/home/servicerobot2/catkin_ws2/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/servicerobot2/catkin_ws2/build" \
    "/usr/bin/python" \
    "/home/servicerobot2/catkin_ws2/src/robot_model/kdl_parser_py/setup.py" \
    build --build-base "/home/servicerobot2/catkin_ws2/build/robot_model/kdl_parser_py" \
    install \
    $DESTDIR_ARG \
    --install-layout=deb --prefix="/home/servicerobot2/catkin_ws2/install" --install-scripts="/home/servicerobot2/catkin_ws2/install/bin"
