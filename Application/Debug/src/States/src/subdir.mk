################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/States/src/StandBy.c \
../src/States/src/State.c 

OBJS += \
./src/States/src/StandBy.o \
./src/States/src/State.o 

C_DEPS += \
./src/States/src/StandBy.d \
./src/States/src/State.d 


# Each subdirectory must supply rules for building sources it contributes
src/States/src/%.o: ../src/States/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/brendan/AlbertaSat/firmware/prototypes/git/satellite-reaper/Application/src/States/include" -I"/home/brendan/AlbertaSat/firmware/prototypes/git/satellite-reaper/Application/src/Satellite/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


