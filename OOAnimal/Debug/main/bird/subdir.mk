################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main/bird/Bird.c 

OBJS += \
./main/bird/Bird.o 

C_DEPS += \
./main/bird/Bird.d 


# Each subdirectory must supply rules for building sources it contributes
main/bird/%.o: ../main/bird/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/brendan/AlbertaSat/firmware/prototypes/git/OOAnimal/OOAnimal/main/animal" -I"/home/brendan/AlbertaSat/firmware/prototypes/git/OOAnimal/OOAnimal/main/cat" -I"/home/brendan/AlbertaSat/firmware/prototypes/git/OOAnimal/OOAnimal/main/crow" -I"/home/brendan/AlbertaSat/firmware/prototypes/git/OOAnimal/OOAnimal/main/bird" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


