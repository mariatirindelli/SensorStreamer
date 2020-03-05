# CMakeList.txt: progetto CMake per SensorStreamer. Includere l'origine e definire
# qui la logica specifica del progetto.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1)

if (NOT DAQmx_DIR)
message("****")
set(DAQmx_DIR "" CACHE STRING "")
endif()

project("SimpleIgtLinkStreamer"
        DESCRIPTION "OpenIgtLink streamer for F/T ATI Sensor")

# Adding the 
find_library(aticonvert64 
			NAMES aticonvert64
			PATHS ${DAQmx_DIR}
			PATH_SUFFIXES lib
			REQUIRED)

find_library(NIDAQmx64 
			NAMES NIDAQmx64
			PATHS ${DAQmx_DIR}
			PATH_SUFFIXES lib
			REQUIRED)

find_package(OpenIGTLink REQUIRED)

message( "Found aticonvert64 in:  ${aticonvert64}")
message( "Found NIDAQmx64 in:  ${NIDAQmx64}")
message( "Found OpenIgtLink in:  ${OpenIGTLink}")

file(GLOB_RECURSE  PR_SOURCES "include/*.h" "include/*.hpp" "src/*.cpp")

add_executable(${PROJECT_NAME} ${PR_SOURCES})


target_include_directories(${PROJECT_NAME} PRIVATE
  include
  ${DAQmx_DIR}
  ${OpenIGTLink_INCLUDE_DIRS}
  )


target_link_libraries(${PROJECT_NAME} ${aticonvert64} ${NIDAQmx64} OpenIGTLink)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "config.json" DESTINATION bin)
install(FILES "FT28270.cal" DESTINATION bin)


#set(YOUR_LIBRARIES "")
#find_path(DAQmx_INCLUDE_DIR "")

# searching for library file
#find_library(DAQmx_LIBRARY "")

#if (DAQmx_INCLUDE_DIR AND DAQmx_LIBRARY)
    # you may need that if further action in your CMakeLists.txt depends
    # on detecting your library
#    set(DAQmx_FOUND TRUE)

    # you may need that if you want to conditionally compile some parts
    # of your code depending on library availability
#    add_definitions(-DHAVE_DAQmx=1)

    # those two, you really need
#    include_directories(${DAQmx_INCLUDE_DIR})
#    set(YOUR_LIBRARIES ${YOUR_LIBRARIES} ${SIFTGPU_LIBRARY})
#endif ()

#message( "Trace for YOUR_LIBRARIES variable: ${YOUR_LIBRARIES}")

# Aggiungere l'origine all'eseguibile di questo progetto.

# TODO: Aggiungere i test e, se necessario, installare le destinazioni.
