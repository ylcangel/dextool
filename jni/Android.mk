# @desc: dextool
# @author: AngelToms
# @date: 2014/12/06
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE            :=  dextool
#LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES += $(LOCAL_PATH)/

LOCAL_SRC_FILES         :=  main.cpp	\
							DexUtil.cpp	\
							Leb128.cpp	\
							descriptors_names.cpp
							

LOCAL_LDLIBS 		:= -llog

LOCAL_CFLAGS += -fPIE 
LOCAL_LDFLAGS += -fPIE -pie 
#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_EXECUTABLE)
