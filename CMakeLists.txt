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


set(HEAD_FILES_configReader
	./configReader/ConfDataReader.hpp
)
set(HEAD_FILES_gnssNavigation
	./gnssNavigation/FolderUtils.h
	./gnssNavigation/GnssBetweenFactor.h
	./gnssNavigation/GnssData.h
	./gnssNavigation/GnssPostfit.h
	./gnssNavigation/gnssStateVec.h
	./gnssNavigation/GnssTools.h
	./gnssNavigation/nonBiasStates.h
	./gnssNavigation/PhaseFactor
	./gnssNavigation/PhysicalConstants.h
	./gnssNavigation/PseudorangeFactor.h

)

include_directories(./gpstk)

set(HEAD_FILES_robustModels
./robustModels/PseudorangeMaxMix.h
./robustModels/PseudorangeSwitchFactor

)
set(HEAD_FILES_slam
./slam/dataset.h

)
set(HEAD_FILES_utils
./utils/csv.h
./utils/CSVParser.h
)

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


