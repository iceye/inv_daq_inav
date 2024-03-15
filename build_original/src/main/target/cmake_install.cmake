# Install script for directory: /Users/sandro.bottoni/Projects/Experiment/inav/src/main/target

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "arm-none-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/AIKONF4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/AIRBOTF4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/AIRBOTF7/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/ALIENFLIGHTF4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/ALIENFLIGHTNGF7/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/ANYFC/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/ANYFCF7/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/ANYFCM7/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/AOCODARCF405AIO/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/AOCODARCF4V2/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/AOCODARCF722AIO/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/AOCODARCF7DUAL/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/AOCODARCF7MINI/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/AOCODARCH7DUAL/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/ASGARD32F4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/ASGARD32F7/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/ATOMRCF405NAVI/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/ATOMRCF405NAVI_DELUX/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/ATOMRCF405V2/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/AXISFLYINGF7PRO/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/BEEROTORF4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/BETAFLIGHTF4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/BETAFPVF435/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/BETAFPVF722/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/BLACKPILL_F411/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/BLUEJAYF4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/CLRACINGF4AIR/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/COLIBRI/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/DAKEFPVF405/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/DAKEFPVF722/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/DALRCF405/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/DALRCF722DUAL/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/F4BY/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FF_F35_LIGHTNING/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FF_FORTINIF4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FF_PIKOF4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FIREWORKSV2/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FISHDRONEF4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FLASHHOBBYF405/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FLASHHOBBYF722/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FLYCOLORF7MINI/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FLYWOOF405PRO/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FLYWOOF405S_AIO/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FLYWOOF411/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FLYWOOF745/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FLYWOOF7DUAL/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FOXEERF405/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FOXEERF722DUAL/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FOXEERF722V4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FOXEERF745AIO/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FOXEERH743/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FRSKYF4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FRSKYPILOT/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FRSKY_ROVERF7/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/FURYF4OSD/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/GEPRCF405/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/GEPRCF405_BT_HD/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/GEPRCF722/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/GEPRCF722_BT_HD/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/GEPRC_F722_AIO/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/HAKRCF405D/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/HAKRCF405V2/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/HAKRCF411D/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/HAKRCF722V2/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/HAKRCKD722/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/HGLRCF722/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/IFLIGHTF4_SUCCEXD/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/IFLIGHTF4_TWING/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/IFLIGHTF7_TWING/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/IFLIGHT_BLITZ_ATF435/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/IFLIGHT_BLITZ_F722/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/IFLIGHT_BLITZ_F7_AIO/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/IFLIGHT_BLITZ_F7_PRO/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/IFLIGHT_H743_AIO_V2/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/IFLIGHT_JBF7PRO/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/INNOVAVIONICSH743_3_1_1/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/JHEH7AIO/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/JHEMCUF405/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/JHEMCUF722/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/KAKUTEF4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/KAKUTEF7/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/KAKUTEF7MINIV3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/KAKUTEH7/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/KAKUTEH7WING/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/KROOZX/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/MAMBAF405US/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/MAMBAF405_2022A/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/MAMBAF722/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/MAMBAF722_2022A/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/MAMBAF722_WING/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/MAMBAF722_X8/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/MAMBAH743/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/MATEKF405/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/MATEKF405CAN/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/MATEKF405SE/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/MATEKF405TE/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/MATEKF411/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/MATEKF411SE/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/MATEKF411TE/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/MATEKF722/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/MATEKF722PX/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/MATEKF722SE/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/MATEKF765/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/MATEKH743/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/NEUTRONRCF435MINI/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/NEUTRONRCF435SE/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/NEUTRONRCF435WING/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/NEUTRONRCH7BT/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/NOX/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/OMNIBUSF4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/OMNIBUSF7/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/OMNIBUSF7NXT/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/PIXRACER/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/REVO/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/RUSH_BLADE_F7/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/SAGEATF4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/SDMODELH7V1/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/SITL/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/SKYSTARSF405HD/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/SKYSTARSF722HD/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/SKYSTARSH743HD/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/SPARKY2/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/SPEDIXF405/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/SPEDIXF722/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/SPEEDYBEEF4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/SPEEDYBEEF405MINI/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/SPEEDYBEEF405V3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/SPEEDYBEEF405V4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/SPEEDYBEEF405WING/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/SPEEDYBEEF7/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/SPEEDYBEEF745AIO/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/SPEEDYBEEF7MINI/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/SPEEDYBEEF7V2/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/SPEEDYBEEF7V3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/SPRACINGF4EVO/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/SPRACINGF7DUAL/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/TMOTORF7/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/TMOTORF7V2/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/YUPIF4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/YUPIF7/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/sandro.bottoni/Projects/Experiment/inav/build/src/main/target/ZEEZF7/cmake_install.cmake")
endif()

