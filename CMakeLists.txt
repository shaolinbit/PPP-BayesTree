cmake_minimum_required (VERSION 2.6)
project (pppbayestree)

SET(CMAKE_INSTALL_PREFIX output)
SET(CMAKE_C_COMPILER gcc)
SET(CMAKE_CXX_COMPILER g++)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -fpic -std=c11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fpic -std=c++11")


find_package(Boost REQUIRED COMPONENTS
filesystem  
)
if(NOT Boost_FOUND)
    message("Not found Boost")
endif()

include_directories(${Boost_INCLUDE_DIRS})
message("${Boost_INCLUDE_DIRS}")
message("${Boost_LIBRARIES}")



include_directories(./configReader)
include_directories(./gnssNavigation)
include_directories(./gpstk)
include_directories(./robustModels)
include_directories(./slam)
include_directories(./utils)

aux_source_directory(. SRC_LIST)
aux_source_directory(./gnssNavigation SRC_LIST_gnssNavigation)
aux_source_directory(./configReader SRC_LIST_configReader)
aux_source_directory(./gpstk SRC_LIST_gpstk)
aux_source_directory(./robustModels SRC_LIST_robustModels)
aux_source_directory(./slam SRC_LIST_slam)
aux_source_directory(./utils SRC_LIST_utils)



include_directories(/usr/include/minisam/)

add_executable(pppbayestree ${SRC_LIST} ${SRC_LIST_gnssNavigation} ${SRC_LIST_configReader} ${SRC_LIST_gpstk} ${SRC_LIST_robustModels} ${SRC_LIST_slam} ${SRC_LIST_utils} ${Boost_LIBRARIES} /usr/lib/libminisam.so)
target_link_libraries(pppbayestree ${SRC_LIST} ${SRC_LIST_gnssNavigation} ${SRC_LIST_configReader} ${SRC_LIST_gpstk} ${SRC_LIST_robustModels} ${SRC_LIST_slam} ${SRC_LIST_utils} ${Boost_LIBRARIES} /usr/lib/libminisam.so)


