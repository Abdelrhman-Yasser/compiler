################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../NFA/NFA.cpp \
../NFA/NFABuilder.cpp 

OBJS += \
./NFA/NFA.o \
./NFA/NFABuilder.o 

CPP_DEPS += \
./NFA/NFA.d \
./NFA/NFABuilder.d 


# Each subdirectory must supply rules for building sources it contributes
NFA/%.o: ../NFA/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

