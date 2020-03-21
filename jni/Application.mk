# compile with stlport_static
#APP_STL := c++_static
APP_STL := stlport_static
NDK_TOOLCHAIN_VERSION := 4.9
#APP_OPTIM := release
#LIBCXX_FORCE_REBUILD := true
APP_PLATFORM := android-15

#APP_ABI := armeabi	
#选择编译两次是因为bin 只能用 armeabi-v7a编译，拷贝时bin拷贝v7版，so拷贝v5版
APP_ABI := armeabi


APP_CFLAGS   := -DLOGGER_OFF -ffunction-sections -fdata-sections  -fvisibility=hidden
APP_CPPFLAGS := $(APP_CFLAGS) -fvisibility-inlines-hidden -fpermissive -ffunction-sections -fdata-sections 
###################################


