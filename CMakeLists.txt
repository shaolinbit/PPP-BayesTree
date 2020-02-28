cmake_minimum_required (VERSION 2.6)
project (pppbayestree)

SET(CMAKE_INSTALL_PREFIX output)
SET(CMAKE_C_COMPILER gcc)
SET(CMAKE_CXX_COMPILER g++)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -fpic -std=c11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fpic -std=c++11")


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
set(HEAD_FILES_gpstk
	
)

set(HEAD_FILES_robustModels

)
set(HEAD_FILES_slam

)
set(HEAD_FILES_utils

)

aux_source_directory(. SRC_LIST)
aux_source_directory(./gnssNavigation SRC_LIST_gnssNavigation)
include_directories(/usr/include/minisam/)

add_executable(pppbayestree ${SRC_LIST} ${SRC_LIST_utils})



