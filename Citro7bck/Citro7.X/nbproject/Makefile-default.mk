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
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Citro7.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Citro7.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c pragma_config.c UART.c I2C.c Timers.c TOF.c ADC.c Freescale_Cam.c Gestion_I2C.c Gestion_IO.c Interpreteur.c Led_SPI_Handler.c Lidar.c Log_File.c Motor_Master.c Motor_Out.c Pragma_Config.c SPI_Low_Handler.c Servos.c Std_Com.c Test_Funcs.c UART_Cmd.c UART_Lidar.c interrupts.c user.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/pragma_config.o ${OBJECTDIR}/UART.o ${OBJECTDIR}/I2C.o ${OBJECTDIR}/Timers.o ${OBJECTDIR}/TOF.o ${OBJECTDIR}/ADC.o ${OBJECTDIR}/Freescale_Cam.o ${OBJECTDIR}/Gestion_I2C.o ${OBJECTDIR}/Gestion_IO.o ${OBJECTDIR}/Interpreteur.o ${OBJECTDIR}/Led_SPI_Handler.o ${OBJECTDIR}/Lidar.o ${OBJECTDIR}/Log_File.o ${OBJECTDIR}/Motor_Master.o ${OBJECTDIR}/Motor_Out.o ${OBJECTDIR}/Pragma_Config.o ${OBJECTDIR}/SPI_Low_Handler.o ${OBJECTDIR}/Servos.o ${OBJECTDIR}/Std_Com.o ${OBJECTDIR}/Test_Funcs.o ${OBJECTDIR}/UART_Cmd.o ${OBJECTDIR}/UART_Lidar.o ${OBJECTDIR}/interrupts.o ${OBJECTDIR}/user.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/pragma_config.o.d ${OBJECTDIR}/UART.o.d ${OBJECTDIR}/I2C.o.d ${OBJECTDIR}/Timers.o.d ${OBJECTDIR}/TOF.o.d ${OBJECTDIR}/ADC.o.d ${OBJECTDIR}/Freescale_Cam.o.d ${OBJECTDIR}/Gestion_I2C.o.d ${OBJECTDIR}/Gestion_IO.o.d ${OBJECTDIR}/Interpreteur.o.d ${OBJECTDIR}/Led_SPI_Handler.o.d ${OBJECTDIR}/Lidar.o.d ${OBJECTDIR}/Log_File.o.d ${OBJECTDIR}/Motor_Master.o.d ${OBJECTDIR}/Motor_Out.o.d ${OBJECTDIR}/Pragma_Config.o.d ${OBJECTDIR}/SPI_Low_Handler.o.d ${OBJECTDIR}/Servos.o.d ${OBJECTDIR}/Std_Com.o.d ${OBJECTDIR}/Test_Funcs.o.d ${OBJECTDIR}/UART_Cmd.o.d ${OBJECTDIR}/UART_Lidar.o.d ${OBJECTDIR}/interrupts.o.d ${OBJECTDIR}/user.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/pragma_config.o ${OBJECTDIR}/UART.o ${OBJECTDIR}/I2C.o ${OBJECTDIR}/Timers.o ${OBJECTDIR}/TOF.o ${OBJECTDIR}/ADC.o ${OBJECTDIR}/Freescale_Cam.o ${OBJECTDIR}/Gestion_I2C.o ${OBJECTDIR}/Gestion_IO.o ${OBJECTDIR}/Interpreteur.o ${OBJECTDIR}/Led_SPI_Handler.o ${OBJECTDIR}/Lidar.o ${OBJECTDIR}/Log_File.o ${OBJECTDIR}/Motor_Master.o ${OBJECTDIR}/Motor_Out.o ${OBJECTDIR}/Pragma_Config.o ${OBJECTDIR}/SPI_Low_Handler.o ${OBJECTDIR}/Servos.o ${OBJECTDIR}/Std_Com.o ${OBJECTDIR}/Test_Funcs.o ${OBJECTDIR}/UART_Cmd.o ${OBJECTDIR}/UART_Lidar.o ${OBJECTDIR}/interrupts.o ${OBJECTDIR}/user.o

# Source Files
SOURCEFILES=main.c pragma_config.c UART.c I2C.c Timers.c TOF.c ADC.c Freescale_Cam.c Gestion_I2C.c Gestion_IO.c Interpreteur.c Led_SPI_Handler.c Lidar.c Log_File.c Motor_Master.c Motor_Out.c Pragma_Config.c SPI_Low_Handler.c Servos.c Std_Com.c Test_Funcs.c UART_Cmd.c UART_Lidar.c interrupts.c user.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Citro7.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128GP804
MP_LINKER_FILE_OPTION=,--script=p33FJ128GP804.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/8c0360fdeda818a3d5a9beccd721452989364ccb .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pragma_config.o: pragma_config.c  .generated_files/flags/default/fe06a73d04f19c99415fe25fdf492d5b36874274 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pragma_config.o.d 
	@${RM} ${OBJECTDIR}/pragma_config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pragma_config.c  -o ${OBJECTDIR}/pragma_config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pragma_config.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/UART.o: UART.c  .generated_files/flags/default/12236394739f67dd0f5bab848e9ed180fc12ba77 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART.o.d 
	@${RM} ${OBJECTDIR}/UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UART.c  -o ${OBJECTDIR}/UART.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/UART.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/I2C.o: I2C.c  .generated_files/flags/default/69c42fad7bc8d20e7c6022d4497218229118213c .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2C.o.d 
	@${RM} ${OBJECTDIR}/I2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2C.c  -o ${OBJECTDIR}/I2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/I2C.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Timers.o: Timers.c  .generated_files/flags/default/b862df89c31d936fe558fed4d85f6f92169df1af .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Timers.o.d 
	@${RM} ${OBJECTDIR}/Timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Timers.c  -o ${OBJECTDIR}/Timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Timers.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/TOF.o: TOF.c  .generated_files/flags/default/ed647810cec9fe847ff22305726057144d1253bd .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TOF.o.d 
	@${RM} ${OBJECTDIR}/TOF.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  TOF.c  -o ${OBJECTDIR}/TOF.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/TOF.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ADC.o: ADC.c  .generated_files/flags/default/a3be9a3dfc71ac25674658089b89403640fc971d .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ADC.o.d 
	@${RM} ${OBJECTDIR}/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ADC.c  -o ${OBJECTDIR}/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ADC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Freescale_Cam.o: Freescale_Cam.c  .generated_files/flags/default/12234daa4703234b01c872c2301fd1f948b4264c .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Freescale_Cam.o.d 
	@${RM} ${OBJECTDIR}/Freescale_Cam.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Freescale_Cam.c  -o ${OBJECTDIR}/Freescale_Cam.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Freescale_Cam.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Gestion_I2C.o: Gestion_I2C.c  .generated_files/flags/default/ff9828f14c3eade5b3bcbf9ce663071c0e354676 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Gestion_I2C.o.d 
	@${RM} ${OBJECTDIR}/Gestion_I2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Gestion_I2C.c  -o ${OBJECTDIR}/Gestion_I2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Gestion_I2C.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Gestion_IO.o: Gestion_IO.c  .generated_files/flags/default/b037bff6847b9e3e4158218728132b73d171c247 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Gestion_IO.o.d 
	@${RM} ${OBJECTDIR}/Gestion_IO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Gestion_IO.c  -o ${OBJECTDIR}/Gestion_IO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Gestion_IO.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Interpreteur.o: Interpreteur.c  .generated_files/flags/default/47645966ffd963b9eec1ba7d1bdb580fde52579 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Interpreteur.o.d 
	@${RM} ${OBJECTDIR}/Interpreteur.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Interpreteur.c  -o ${OBJECTDIR}/Interpreteur.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Interpreteur.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Led_SPI_Handler.o: Led_SPI_Handler.c  .generated_files/flags/default/76d0411d64fbd6c5ee582d75dfe069dbc2681872 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Led_SPI_Handler.o.d 
	@${RM} ${OBJECTDIR}/Led_SPI_Handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Led_SPI_Handler.c  -o ${OBJECTDIR}/Led_SPI_Handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Led_SPI_Handler.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Lidar.o: Lidar.c  .generated_files/flags/default/d96616be87665d325969b2fa115df521345b499f .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Lidar.o.d 
	@${RM} ${OBJECTDIR}/Lidar.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Lidar.c  -o ${OBJECTDIR}/Lidar.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Lidar.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Log_File.o: Log_File.c  .generated_files/flags/default/92f10fcaa944f54179ee2ec3845c0a224b180252 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Log_File.o.d 
	@${RM} ${OBJECTDIR}/Log_File.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Log_File.c  -o ${OBJECTDIR}/Log_File.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Log_File.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Motor_Master.o: Motor_Master.c  .generated_files/flags/default/57339b5d990e9af4718655200dfb3eb816ed107d .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Motor_Master.o.d 
	@${RM} ${OBJECTDIR}/Motor_Master.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Motor_Master.c  -o ${OBJECTDIR}/Motor_Master.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Motor_Master.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Motor_Out.o: Motor_Out.c  .generated_files/flags/default/5cbb5009753d37bab9a632286a5a0bb691c018b3 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Motor_Out.o.d 
	@${RM} ${OBJECTDIR}/Motor_Out.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Motor_Out.c  -o ${OBJECTDIR}/Motor_Out.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Motor_Out.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Pragma_Config.o: Pragma_Config.c  .generated_files/flags/default/a4f515cb4e4573925357a8d2341010c3ef351d2e .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Pragma_Config.o.d 
	@${RM} ${OBJECTDIR}/Pragma_Config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Pragma_Config.c  -o ${OBJECTDIR}/Pragma_Config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Pragma_Config.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/SPI_Low_Handler.o: SPI_Low_Handler.c  .generated_files/flags/default/8d477545e51ac5e4afa5fb566d95ce9165cf2590 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SPI_Low_Handler.o.d 
	@${RM} ${OBJECTDIR}/SPI_Low_Handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SPI_Low_Handler.c  -o ${OBJECTDIR}/SPI_Low_Handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/SPI_Low_Handler.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Servos.o: Servos.c  .generated_files/flags/default/be482b167fc7b6fca911f863ea7708bbf0da0275 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Servos.o.d 
	@${RM} ${OBJECTDIR}/Servos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Servos.c  -o ${OBJECTDIR}/Servos.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Servos.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Std_Com.o: Std_Com.c  .generated_files/flags/default/304c69de5624dd043d871495b84c67c5f3bd9ebf .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Std_Com.o.d 
	@${RM} ${OBJECTDIR}/Std_Com.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Std_Com.c  -o ${OBJECTDIR}/Std_Com.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Std_Com.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Test_Funcs.o: Test_Funcs.c  .generated_files/flags/default/dbf78e1af5c07a819d713b5b7b7bf05bf2198024 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Test_Funcs.o.d 
	@${RM} ${OBJECTDIR}/Test_Funcs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Test_Funcs.c  -o ${OBJECTDIR}/Test_Funcs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Test_Funcs.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/UART_Cmd.o: UART_Cmd.c  .generated_files/flags/default/ec580873f74f02ecf046a1fa5faa14c01e28da21 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART_Cmd.o.d 
	@${RM} ${OBJECTDIR}/UART_Cmd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UART_Cmd.c  -o ${OBJECTDIR}/UART_Cmd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/UART_Cmd.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/UART_Lidar.o: UART_Lidar.c  .generated_files/flags/default/7ccf0e92a7e8c1b1e2f422b8dc1df1472c13d74c .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART_Lidar.o.d 
	@${RM} ${OBJECTDIR}/UART_Lidar.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UART_Lidar.c  -o ${OBJECTDIR}/UART_Lidar.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/UART_Lidar.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/interrupts.o: interrupts.c  .generated_files/flags/default/1ddde29e58845983ae9d85906431a8abf87bb8b2 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts.o.d 
	@${RM} ${OBJECTDIR}/interrupts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  interrupts.c  -o ${OBJECTDIR}/interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/interrupts.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/user.o: user.c  .generated_files/flags/default/d4993fad441356a7e0aac697a8e8dc3dba7cb5fd .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/user.o.d 
	@${RM} ${OBJECTDIR}/user.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  user.c  -o ${OBJECTDIR}/user.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/user.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/9c5443cc07e64796a9bdf765c7813420d570eef8 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pragma_config.o: pragma_config.c  .generated_files/flags/default/800c8a451e7442caf4735afb14dd89611837209c .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pragma_config.o.d 
	@${RM} ${OBJECTDIR}/pragma_config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pragma_config.c  -o ${OBJECTDIR}/pragma_config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pragma_config.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/UART.o: UART.c  .generated_files/flags/default/bd68448cb93d778647fef52d8c088e78c0391361 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART.o.d 
	@${RM} ${OBJECTDIR}/UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UART.c  -o ${OBJECTDIR}/UART.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/UART.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/I2C.o: I2C.c  .generated_files/flags/default/2ae3d377a78e451b13e14a4c620cec01a09df242 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2C.o.d 
	@${RM} ${OBJECTDIR}/I2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2C.c  -o ${OBJECTDIR}/I2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/I2C.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Timers.o: Timers.c  .generated_files/flags/default/3a5ec08cbfe2a830b58ad9751d5560b86dba17ad .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Timers.o.d 
	@${RM} ${OBJECTDIR}/Timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Timers.c  -o ${OBJECTDIR}/Timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Timers.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/TOF.o: TOF.c  .generated_files/flags/default/adc317f198aeb7aeffb8a14a9b6204c24f145f0b .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TOF.o.d 
	@${RM} ${OBJECTDIR}/TOF.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  TOF.c  -o ${OBJECTDIR}/TOF.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/TOF.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ADC.o: ADC.c  .generated_files/flags/default/ef3c55ca012f6d2218b05670b4f492916786b8c2 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ADC.o.d 
	@${RM} ${OBJECTDIR}/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ADC.c  -o ${OBJECTDIR}/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ADC.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Freescale_Cam.o: Freescale_Cam.c  .generated_files/flags/default/d34b76aab524a144231d453e34e2133453d9ef3a .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Freescale_Cam.o.d 
	@${RM} ${OBJECTDIR}/Freescale_Cam.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Freescale_Cam.c  -o ${OBJECTDIR}/Freescale_Cam.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Freescale_Cam.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Gestion_I2C.o: Gestion_I2C.c  .generated_files/flags/default/c97c0e130d9cbf40e42d4c77b0501e3a8caeca96 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Gestion_I2C.o.d 
	@${RM} ${OBJECTDIR}/Gestion_I2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Gestion_I2C.c  -o ${OBJECTDIR}/Gestion_I2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Gestion_I2C.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Gestion_IO.o: Gestion_IO.c  .generated_files/flags/default/875d0ffdf58a82b90e90c0eceaaee812cc1aba56 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Gestion_IO.o.d 
	@${RM} ${OBJECTDIR}/Gestion_IO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Gestion_IO.c  -o ${OBJECTDIR}/Gestion_IO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Gestion_IO.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Interpreteur.o: Interpreteur.c  .generated_files/flags/default/cb15acd3b7a13abe346db27d3bf97fc9f705d2b2 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Interpreteur.o.d 
	@${RM} ${OBJECTDIR}/Interpreteur.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Interpreteur.c  -o ${OBJECTDIR}/Interpreteur.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Interpreteur.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Led_SPI_Handler.o: Led_SPI_Handler.c  .generated_files/flags/default/ad043fcbfe45e03ea70c0b67a49a027d5a7f92c4 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Led_SPI_Handler.o.d 
	@${RM} ${OBJECTDIR}/Led_SPI_Handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Led_SPI_Handler.c  -o ${OBJECTDIR}/Led_SPI_Handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Led_SPI_Handler.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Lidar.o: Lidar.c  .generated_files/flags/default/2cc3fefef64bda11ff2f78e02714fbe8c72d06ec .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Lidar.o.d 
	@${RM} ${OBJECTDIR}/Lidar.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Lidar.c  -o ${OBJECTDIR}/Lidar.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Lidar.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Log_File.o: Log_File.c  .generated_files/flags/default/99fdeddd6e25c68b8663c2cbf97c827ad566564 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Log_File.o.d 
	@${RM} ${OBJECTDIR}/Log_File.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Log_File.c  -o ${OBJECTDIR}/Log_File.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Log_File.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Motor_Master.o: Motor_Master.c  .generated_files/flags/default/3a3d8955671f043c7f564a4e1969a9ea5f8cd370 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Motor_Master.o.d 
	@${RM} ${OBJECTDIR}/Motor_Master.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Motor_Master.c  -o ${OBJECTDIR}/Motor_Master.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Motor_Master.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Motor_Out.o: Motor_Out.c  .generated_files/flags/default/6162afe43184c632bb6e9c4050db4ecfefe52eae .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Motor_Out.o.d 
	@${RM} ${OBJECTDIR}/Motor_Out.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Motor_Out.c  -o ${OBJECTDIR}/Motor_Out.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Motor_Out.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Pragma_Config.o: Pragma_Config.c  .generated_files/flags/default/ae144272b0a094dcac4b14b71918d2061b43cf05 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Pragma_Config.o.d 
	@${RM} ${OBJECTDIR}/Pragma_Config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Pragma_Config.c  -o ${OBJECTDIR}/Pragma_Config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Pragma_Config.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/SPI_Low_Handler.o: SPI_Low_Handler.c  .generated_files/flags/default/1bf67fb4793b5b61b31fe3e68c55da47069f5278 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SPI_Low_Handler.o.d 
	@${RM} ${OBJECTDIR}/SPI_Low_Handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SPI_Low_Handler.c  -o ${OBJECTDIR}/SPI_Low_Handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/SPI_Low_Handler.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Servos.o: Servos.c  .generated_files/flags/default/dbcb4ab5439e4593ea84201ee5fb2e7a5fb2ab99 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Servos.o.d 
	@${RM} ${OBJECTDIR}/Servos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Servos.c  -o ${OBJECTDIR}/Servos.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Servos.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Std_Com.o: Std_Com.c  .generated_files/flags/default/ba9cd18b9f6ca0afb7ac950cb81ff9ec51391dd1 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Std_Com.o.d 
	@${RM} ${OBJECTDIR}/Std_Com.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Std_Com.c  -o ${OBJECTDIR}/Std_Com.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Std_Com.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Test_Funcs.o: Test_Funcs.c  .generated_files/flags/default/1505478d2441e2ce009187c71ade0dda8583546b .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Test_Funcs.o.d 
	@${RM} ${OBJECTDIR}/Test_Funcs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Test_Funcs.c  -o ${OBJECTDIR}/Test_Funcs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Test_Funcs.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/UART_Cmd.o: UART_Cmd.c  .generated_files/flags/default/e818c4f0c6bd7e2e609fe13aed1bab64151a8fc3 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART_Cmd.o.d 
	@${RM} ${OBJECTDIR}/UART_Cmd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UART_Cmd.c  -o ${OBJECTDIR}/UART_Cmd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/UART_Cmd.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/UART_Lidar.o: UART_Lidar.c  .generated_files/flags/default/a9cfffd82151d8eecdfa2ae67a7c247a255facf .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART_Lidar.o.d 
	@${RM} ${OBJECTDIR}/UART_Lidar.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UART_Lidar.c  -o ${OBJECTDIR}/UART_Lidar.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/UART_Lidar.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/interrupts.o: interrupts.c  .generated_files/flags/default/1b3fc15c036ad272c13b4df866d873ad3ccffd37 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts.o.d 
	@${RM} ${OBJECTDIR}/interrupts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  interrupts.c  -o ${OBJECTDIR}/interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/interrupts.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/user.o: user.c  .generated_files/flags/default/168dba1aabb071650888657e5cb0ca967ba21cf8 .generated_files/flags/default/3b176172aa40d8cd20560e3072b4d3db73d8a093
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/user.o.d 
	@${RM} ${OBJECTDIR}/user.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  user.c  -o ${OBJECTDIR}/user.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/user.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Citro7.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/Citro7.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/Citro7.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/Citro7.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}/xc16-bin2hex ${DISTDIR}/Citro7.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
