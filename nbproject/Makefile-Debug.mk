#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/PSOThread.o \
	${OBJECTDIR}/src/PSO_Interface.o \
	${OBJECTDIR}/src/Scanner.o \
	${OBJECTDIR}/src/UserInterface.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/pso.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=`pkg-config --cflags gtkmm-2.4` `pkg-config --libs gtkmm-2.4` 
CXXFLAGS=`pkg-config --cflags gtkmm-2.4` `pkg-config --libs gtkmm-2.4` 

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pso_cpp

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pso_cpp: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pso_cpp ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/PSOThread.o: src/PSOThread.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtkmm-2.4 -include /usr/include/glibmm-2.4/glibmm.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/PSOThread.o src/PSOThread.cpp

${OBJECTDIR}/src/PSO_Interface.o: src/PSO_Interface.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtkmm-2.4 -include /usr/include/glibmm-2.4/glibmm.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/PSO_Interface.o src/PSO_Interface.cpp

${OBJECTDIR}/src/Scanner.o: src/Scanner.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtkmm-2.4 -include /usr/include/glibmm-2.4/glibmm.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Scanner.o src/Scanner.cpp

${OBJECTDIR}/src/UserInterface.o: src/UserInterface.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtkmm-2.4 -include /usr/include/glibmm-2.4/glibmm.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/UserInterface.o src/UserInterface.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtkmm-2.4 -include /usr/include/glibmm-2.4/glibmm.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/pso.o: src/pso.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtkmm-2.4 -include /usr/include/glibmm-2.4/glibmm.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/pso.o src/pso.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pso_cpp

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
