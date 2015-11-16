cmake_minimum_required(VERSION 2.8.3)

# Add external data from midas
list(APPEND ExternalData_URL_TEMPLATES
"http://slicer.kitware.com/midas3/api/rest?method=midas.bitstream.download&checksum=%(hash)"
)

# Set the data
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Data)
set(sphere DATA{${SOURCE_DIR}/sphereExpectedResult.vtk})
set(condyle DATA{${SOURCE_DIR}/Condyle_PointToPoint.vtk})

# Include directories
include_directories( ${CMAKE_SOURCE_DIR})

# Link directories
link_directories(${CMAKE_BINARY_DIR}/lib)


# Test of the class ShapePopulationBase
add_executable(Test_ShapePopulationBase mainTestShapePopulationBase.cxx testShapePopulationBase.cxx)
target_link_libraries(Test_ShapePopulationBase ShapePopulationViewerLib)
ExternalData_add_test(
        MY_DATA
        NAME testShapePopulationBase
        COMMAND $<TARGET_FILE:Test_ShapePopulationBase> ${sphere} ${condyle}
)



# Test for the command --help
add_test(
        NAME PrintHelp
        COMMAND $<TARGET_FILE:ShapePopulationViewer> --help
)

ExternalData_Add_Target(MY_DATA)
