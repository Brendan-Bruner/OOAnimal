################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main/Dragon.c \
../main/main.c 

OBJS += \
./main/Dragon.o \
./main/main.o 

C_DEPS += \
./main/Dragon.d \
./main/main.d 


# Each subdirectory must supply rules for building sources it contributes
main/%.o: ../main/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/brendan/Endeavors/OOAnimal/git/OOAnimal/OODragon/Class" -I"/home/brendan/Endeavors/OOAnimal/git/OOAnimal/OODragon/main/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


