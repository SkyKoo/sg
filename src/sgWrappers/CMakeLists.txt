INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(./sgLogger)
INCLUDE_DIRECTORIES(./sgConfig)

# library
SET(SGWRAPPERS_LIB sgException.cc
                   sgGlobalFunWrappers.cc
                   sgMutex.cc
                   sgThread.cc
                   sgIPC.cc
                   sgTypeCast.cc
                   sgTime.cc
                   sgRedis/sgRedis.cc
                   sgRedis/sgKeys.cc
                   sgRedis/sgStrings.cc
                   sgLogger/sgLog4cplus.cc
                   sgLogger/sgStreamLogger.cc
                   sgConfig/sgConfig.cc
                   sgNet/sgIPv4Address.cc
                   sgNet/sgAbstractSocket.cc)
ADD_LIBRARY(_sgWrappers SHARED ${SGWRAPPERS_LIB})

TARGET_LINK_LIBRARIES(_sgWrappers pthread log4cplus hiredis)

# execute
#SET(EXECUTABLE_OUTPUT_PATH ${LINUX_SRV_OUTPUT_PATH})
#SET(SGWRAPPERS_SRC sgWrappers_main.cc
#                   sgGlobalFunWrappers.cc
#                   sgException.cc
#                   sgMutex.cc
#                   sgThread.cc
#                   sgIPC.cc
#                   sgIPv4Address.cc
#                   sgAbstractSocket.cc
#                   sgTypeCast.cc
#                   sgTime.cc
#                   sgLogger/sgLog4cplus.cc
#                   sgLogger/sgStreamLogger.cc
#                   sgConfig/sgConfig.cc)
#ADD_EXECUTABLE(sgWrappers ${SGWRAPPERS_SRC})

#TARGET_LINK_LIBRARIES(sgWrappers pthread log4cplus)
