################################################################################
# �Զ����ɵ��ļ�����Ҫ�༭��
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
	@echo '���ڹ����ļ��� $<'
	@echo '���ڵ��ã� GNU C++ ������'
	/work/toolchain_R2_EABI/usr/bin/arm-none-linux-gnueabi-g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo '�ѽ��������� $<'
	@echo ' '


