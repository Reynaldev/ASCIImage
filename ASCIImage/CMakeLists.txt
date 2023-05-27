# CMakeList.txt : CMake project for ASCIImage, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (main "Main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET main PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

# Set OpenCVConfig.cmake Search Directory
set( OpenCV_DIR )
if( NOT CMAKE_CL_64 )
  set( OpenCV_DIR "C:/Users/Rey/vcpkg/installed/x64-windows/share/opencv" )
else()
  set( OpenCV_DIR "C:/Users/Rey/vcpkg/installed/x64-windows/share/opencv" )
endif()

# Find Package
find_package( OpenCV REQUIRED )

if( OpenCV_FOUND )
  # Additional Include Directories
  include_directories( ${OpenCV_INCLUDE_DIRS} )

  # Additional Library Directories
  link_directories( ${OpenCV_LIB_DIR} )

  # Additional Dependencies
  target_link_libraries( main ${OpenCV_LIBS} )
endif()