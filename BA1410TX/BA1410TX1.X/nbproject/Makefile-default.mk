#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../Project_1410/BA1410TX/BA1410TX.c ../AD5312.c ../AD9746.c ../ADF4350.c ../BA1410TX_intr.c ../BA1410TX_serial.c ../loader.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1092510196/BA1410TX.o ${OBJECTDIR}/_ext/1472/AD5312.o ${OBJECTDIR}/_ext/1472/AD9746.o ${OBJECTDIR}/_ext/1472/ADF4350.o ${OBJECTDIR}/_ext/1472/BA1410TX_intr.o ${OBJECTDIR}/_ext/1472/BA1410TX_serial.o ${OBJECTDIR}/_ext/1472/loader.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1092510196/BA1410TX.o.d ${OBJECTDIR}/_ext/1472/AD5312.o.d ${OBJECTDIR}/_ext/1472/AD9746.o.d ${OBJECTDIR}/_ext/1472/ADF4350.o.d ${OBJECTDIR}/_ext/1472/BA1410TX_intr.o.d ${OBJECTDIR}/_ext/1472/BA1410TX_serial.o.d ${OBJECTDIR}/_ext/1472/loader.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1092510196/BA1410TX.o ${OBJECTDIR}/_ext/1472/AD5312.o ${OBJECTDIR}/_ext/1472/AD9746.o ${OBJECTDIR}/_ext/1472/ADF4350.o ${OBJECTDIR}/_ext/1472/BA1410TX_intr.o ${OBJECTDIR}/_ext/1472/BA1410TX_serial.o ${OBJECTDIR}/_ext/1472/loader.o

# Source Files
SOURCEFILES=../../Project_1410/BA1410TX/BA1410TX.c ../AD5312.c ../AD9746.c ../ADF4350.c ../BA1410TX_intr.c ../BA1410TX_serial.c ../loader.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_CC="C:\PROGRA~2\PICC\CCSCON.exe"
MP_LD="C:\PROGRA~2\PICC\CCSCON.exe"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1092510196/BA1410TX.o: ../../Project_1410/BA1410TX/BA1410TX.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1092510196 
ifeq (7,1) 
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  out="${OBJECTDIR}\_ext\1092510196"  ../../Project_1410/BA1410TX/BA1410TX.c +FH +DF +CC  #__DEBUG=1 +ICD +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 
	@mv ${OBJECTDIR}/_ext/1092510196/BA1410TX.cof "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.cof" 
	@mv ${OBJECTDIR}/_ext/1092510196/BA1410TX.hex "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.hex"
else 
	${MP_CC}  out=""${OBJECTDIR}\_ext\1092510196"" ../../Project_1410/BA1410TX/BA1410TX.c +EXPORT +FH +DF +CC  #__DEBUG=1 +ICD +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 +EXPORTD="${OBJECTDIR}/_ext/1092510196"  
	
endif 
	
${OBJECTDIR}/_ext/1472/AD5312.o: ../AD5312.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
ifeq (7,1) 
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  out="${OBJECTDIR}\_ext\1472"  ../AD5312.c +FH +DF +CC  #__DEBUG=1 +ICD +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 
	@mv ${OBJECTDIR}/_ext/1472/AD5312.cof "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.cof" 
	@mv ${OBJECTDIR}/_ext/1472/AD5312.hex "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.hex"
else 
	${MP_CC}  out=""${OBJECTDIR}\_ext\1472"" ../AD5312.c +EXPORT +FH +DF +CC  #__DEBUG=1 +ICD +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 +EXPORTD="${OBJECTDIR}/_ext/1472"  
	
endif 
	
${OBJECTDIR}/_ext/1472/AD9746.o: ../AD9746.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
ifeq (7,1) 
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  out="${OBJECTDIR}\_ext\1472"  ../AD9746.c +FH +DF +CC  #__DEBUG=1 +ICD +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 
	@mv ${OBJECTDIR}/_ext/1472/AD9746.cof "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.cof" 
	@mv ${OBJECTDIR}/_ext/1472/AD9746.hex "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.hex"
else 
	${MP_CC}  out=""${OBJECTDIR}\_ext\1472"" ../AD9746.c +EXPORT +FH +DF +CC  #__DEBUG=1 +ICD +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 +EXPORTD="${OBJECTDIR}/_ext/1472"  
	
endif 
	
${OBJECTDIR}/_ext/1472/ADF4350.o: ../ADF4350.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
ifeq (7,1) 
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  out="${OBJECTDIR}\_ext\1472"  ../ADF4350.c +FH +DF +CC  #__DEBUG=1 +ICD +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 
	@mv ${OBJECTDIR}/_ext/1472/ADF4350.cof "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.cof" 
	@mv ${OBJECTDIR}/_ext/1472/ADF4350.hex "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.hex"
else 
	${MP_CC}  out=""${OBJECTDIR}\_ext\1472"" ../ADF4350.c +EXPORT +FH +DF +CC  #__DEBUG=1 +ICD +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 +EXPORTD="${OBJECTDIR}/_ext/1472"  
	
endif 
	
${OBJECTDIR}/_ext/1472/BA1410TX_intr.o: ../BA1410TX_intr.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
ifeq (7,1) 
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  out="${OBJECTDIR}\_ext\1472"  ../BA1410TX_intr.c +FH +DF +CC  #__DEBUG=1 +ICD +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 
	@mv ${OBJECTDIR}/_ext/1472/BA1410TX_intr.cof "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.cof" 
	@mv ${OBJECTDIR}/_ext/1472/BA1410TX_intr.hex "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.hex"
else 
	${MP_CC}  out=""${OBJECTDIR}\_ext\1472"" ../BA1410TX_intr.c +EXPORT +FH +DF +CC  #__DEBUG=1 +ICD +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 +EXPORTD="${OBJECTDIR}/_ext/1472"  
	
endif 
	
${OBJECTDIR}/_ext/1472/BA1410TX_serial.o: ../BA1410TX_serial.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
ifeq (7,1) 
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  out="${OBJECTDIR}\_ext\1472"  ../BA1410TX_serial.c +FH +DF +CC  #__DEBUG=1 +ICD +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 
	@mv ${OBJECTDIR}/_ext/1472/BA1410TX_serial.cof "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.cof" 
	@mv ${OBJECTDIR}/_ext/1472/BA1410TX_serial.hex "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.hex"
else 
	${MP_CC}  out=""${OBJECTDIR}\_ext\1472"" ../BA1410TX_serial.c +EXPORT +FH +DF +CC  #__DEBUG=1 +ICD +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 +EXPORTD="${OBJECTDIR}/_ext/1472"  
	
endif 
	
${OBJECTDIR}/_ext/1472/loader.o: ../loader.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
ifeq (7,1) 
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  out="${OBJECTDIR}\_ext\1472"  ../loader.c +FH +DF +CC  #__DEBUG=1 +ICD +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 
	@mv ${OBJECTDIR}/_ext/1472/loader.cof "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.cof" 
	@mv ${OBJECTDIR}/_ext/1472/loader.hex "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.hex"
else 
	${MP_CC}  out=""${OBJECTDIR}\_ext\1472"" ../loader.c +EXPORT +FH +DF +CC  #__DEBUG=1 +ICD +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 +EXPORTD="${OBJECTDIR}/_ext/1472"  
	
endif 
	
else
${OBJECTDIR}/_ext/1092510196/BA1410TX.o: ../../Project_1410/BA1410TX/BA1410TX.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1092510196 
ifeq (7,1) 
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  out="${OBJECTDIR}\_ext\1092510196"  ../../Project_1410/BA1410TX/BA1410TX.c +FH +DF +CC +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 
	@mv ${OBJECTDIR}/_ext/1092510196/BA1410TX.cof "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.cof" 
	@mv ${OBJECTDIR}/_ext/1092510196/BA1410TX.hex "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.hex"
else 
	${MP_CC}  out=""${OBJECTDIR}\_ext\1092510196"" ../../Project_1410/BA1410TX/BA1410TX.c +EXPORT +FH +DF +CC +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 +EXPORTD="${OBJECTDIR}/_ext/1092510196"  
	
endif 
	
${OBJECTDIR}/_ext/1472/AD5312.o: ../AD5312.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
ifeq (7,1) 
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  out="${OBJECTDIR}\_ext\1472"  ../AD5312.c +FH +DF +CC +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 
	@mv ${OBJECTDIR}/_ext/1472/AD5312.cof "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.cof" 
	@mv ${OBJECTDIR}/_ext/1472/AD5312.hex "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.hex"
else 
	${MP_CC}  out=""${OBJECTDIR}\_ext\1472"" ../AD5312.c +EXPORT +FH +DF +CC +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 +EXPORTD="${OBJECTDIR}/_ext/1472"  
	
endif 
	
${OBJECTDIR}/_ext/1472/AD9746.o: ../AD9746.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
ifeq (7,1) 
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  out="${OBJECTDIR}\_ext\1472"  ../AD9746.c +FH +DF +CC +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 
	@mv ${OBJECTDIR}/_ext/1472/AD9746.cof "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.cof" 
	@mv ${OBJECTDIR}/_ext/1472/AD9746.hex "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.hex"
else 
	${MP_CC}  out=""${OBJECTDIR}\_ext\1472"" ../AD9746.c +EXPORT +FH +DF +CC +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 +EXPORTD="${OBJECTDIR}/_ext/1472"  
	
endif 
	
${OBJECTDIR}/_ext/1472/ADF4350.o: ../ADF4350.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
ifeq (7,1) 
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  out="${OBJECTDIR}\_ext\1472"  ../ADF4350.c +FH +DF +CC +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 
	@mv ${OBJECTDIR}/_ext/1472/ADF4350.cof "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.cof" 
	@mv ${OBJECTDIR}/_ext/1472/ADF4350.hex "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.hex"
else 
	${MP_CC}  out=""${OBJECTDIR}\_ext\1472"" ../ADF4350.c +EXPORT +FH +DF +CC +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 +EXPORTD="${OBJECTDIR}/_ext/1472"  
	
endif 
	
${OBJECTDIR}/_ext/1472/BA1410TX_intr.o: ../BA1410TX_intr.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
ifeq (7,1) 
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  out="${OBJECTDIR}\_ext\1472"  ../BA1410TX_intr.c +FH +DF +CC +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 
	@mv ${OBJECTDIR}/_ext/1472/BA1410TX_intr.cof "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.cof" 
	@mv ${OBJECTDIR}/_ext/1472/BA1410TX_intr.hex "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.hex"
else 
	${MP_CC}  out=""${OBJECTDIR}\_ext\1472"" ../BA1410TX_intr.c +EXPORT +FH +DF +CC +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 +EXPORTD="${OBJECTDIR}/_ext/1472"  
	
endif 
	
${OBJECTDIR}/_ext/1472/BA1410TX_serial.o: ../BA1410TX_serial.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
ifeq (7,1) 
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  out="${OBJECTDIR}\_ext\1472"  ../BA1410TX_serial.c +FH +DF +CC +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 
	@mv ${OBJECTDIR}/_ext/1472/BA1410TX_serial.cof "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.cof" 
	@mv ${OBJECTDIR}/_ext/1472/BA1410TX_serial.hex "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.hex"
else 
	${MP_CC}  out=""${OBJECTDIR}\_ext\1472"" ../BA1410TX_serial.c +EXPORT +FH +DF +CC +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 +EXPORTD="${OBJECTDIR}/_ext/1472"  
	
endif 
	
${OBJECTDIR}/_ext/1472/loader.o: ../loader.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
ifeq (7,1) 
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  out="${OBJECTDIR}\_ext\1472"  ../loader.c +FH +DF +CC +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 
	@mv ${OBJECTDIR}/_ext/1472/loader.cof "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.cof" 
	@mv ${OBJECTDIR}/_ext/1472/loader.hex "dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.hex"
else 
	${MP_CC}  out=""${OBJECTDIR}\_ext\1472"" ../loader.c +EXPORT +FH +DF +CC +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F45K22=1 +EXPORTD="${OBJECTDIR}/_ext/1472"  
	
endif 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
ifeq (7,1) 
	
else 
	${MP_LD}   out="dist/${CND_CONF}/${IMAGE_TYPE}"  +FH +DF +CC LINK=BA1410TX1.X.${IMAGE_TYPE}.hex=${OBJECTDIR}/_ext/1092510196/BA1410TX.o,${OBJECTDIR}/_ext/1472/AD5312.o,${OBJECTDIR}/_ext/1472/AD9746.o,${OBJECTDIR}/_ext/1472/ADF4350.o,${OBJECTDIR}/_ext/1472/BA1410TX_intr.o,${OBJECTDIR}/_ext/1472/BA1410TX_serial.o,${OBJECTDIR}/_ext/1472/loader.o +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P
	
endif 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/BA1410TX1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
ifeq (7,1) 
	
else 
	${MP_LD}   out="dist/${CND_CONF}/${IMAGE_TYPE}"  +FH +DF +CC LINK=BA1410TX1.X.${IMAGE_TYPE}.hex=${OBJECTDIR}/_ext/1092510196/BA1410TX.o,${OBJECTDIR}/_ext/1472/AD5312.o,${OBJECTDIR}/_ext/1472/AD9746.o,${OBJECTDIR}/_ext/1472/ADF4350.o,${OBJECTDIR}/_ext/1472/BA1410TX_intr.o,${OBJECTDIR}/_ext/1472/BA1410TX_serial.o,${OBJECTDIR}/_ext/1472/loader.o +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P
	
endif 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
