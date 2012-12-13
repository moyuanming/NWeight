################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../HCDVR.cpp 

OBJS += \
./HCDVR.o 

CPP_DEPS += \
./HCDVR.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo '正在构建文件： $<'
	@echo '正在调用： GNU C++ 编译器'
	/work/toolchain_R2_EABI/usr/bin/arm-none-linux-gnueabi-g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo '已结束构建： $<'
	@echo ' '


