################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main/Classes/Dragon.c \
../main/Classes/FlameGuard.c 

OBJS += \
./main/Classes/Dragon.o \
./main/Classes/FlameGuard.o 

C_DEPS += \
./main/Classes/Dragon.d \
./main/Classes/FlameGuard.d 


# Each subdirectory must supply rules for building sources it contributes
main/Classes/%.o: ../main/Classes/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/brendan/Endeavors/OOAnimal/git/OOAnimal/OODragon/main/Traits" -I"/home/brendan/Endeavors/OOAnimal/git/OOAnimal/OODragon/main/Classes/include" -I"/home/brendan/Endeavors/OOAnimal/git/OOAnimal/OODragon/Class" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


