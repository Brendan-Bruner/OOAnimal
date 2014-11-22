################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main/crow/Crow.c 

OBJS += \
./main/crow/Crow.o 

C_DEPS += \
./main/crow/Crow.d 


# Each subdirectory must supply rules for building sources it contributes
main/crow/%.o: ../main/crow/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/brendan/Endeavors/OOAnimal/git/OOAnimal/OOAnimal/main/animal" -I"/home/brendan/Endeavors/OOAnimal/git/OOAnimal/OOAnimal/main/cat" -I"/home/brendan/Endeavors/OOAnimal/git/OOAnimal/OOAnimal/main/crow" -I"/home/brendan/Endeavors/OOAnimal/git/OOAnimal/OOAnimal/main/bird" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


