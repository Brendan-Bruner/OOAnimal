################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main/Classes/FlameGuard.c \
../main/Classes/Whelp.c 

OBJS += \
./main/Classes/FlameGuard.o \
./main/Classes/Whelp.o 

C_DEPS += \
./main/Classes/FlameGuard.d \
./main/Classes/Whelp.d 


# Each subdirectory must supply rules for building sources it contributes
main/Classes/%.o: ../main/Classes/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/brendan/Endeavors/OOAnimal/git/OOAnimal/OODragon/main/Traits" -I"/home/brendan/Endeavors/OOAnimal/git/OOAnimal/OODragon/main/Classes/include" -I"/home/brendan/Endeavors/OOAnimal/git/OOAnimal/OODragon/Class" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


