LOCAL_PATH := $(call my-dir)

LIBS_PATH := libraries/$(TARGET_ARCH_ABI)

include $(CLEAR_VARS)
LOCAL_MODULE := libcurl
LOCAL_SRC_FILES := $(LIBS_PATH)/libcurl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libssl
LOCAL_SRC_FILES := $(LIBS_PATH)/libssl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libcrypto
LOCAL_SRC_FILES := $(LIBS_PATH)/libcrypto.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := qazaqdlc
LOCAL_ARM_MODE := arm

LOCAL_CFLAGS := \
    -w \
    -s \
    -Os \
    -fpermissive \
    -fexceptions \
    -fvisibility=hidden \
    -fomit-frame-pointer \
    -fno-stack-protector \
    -mno-unaligned-access \
    -ffunction-sections \
    -fdata-sections \
    -Wno-error=format-security

LOCAL_CPPFLAGS := \
    -std=c++17 \
    -w \
    -s \
    -Os \
    -Wall \
    -Werror \
    -fpermissive \
    -fvisibility=hidden \
    -fomit-frame-pointer \
    -fno-stack-protector \
    -mno-unaligned-access \
    -fno-rtti \
    -fno-exceptions \
    -ffunction-sections \
    -fdata-sections \
    -Wno-error=format-security

LOCAL_LDFLAGS := \
    -Wl,--gc-sections \
    -Wl,--strip-all \
    -Wl,--exclude-libs,ALL

LOCAL_LDLIBS := \
    -llog \
    -landroid \
    -lOpenSLES \
    -lEGL \
    -lGLESv2 \
    -lz

LOCAL_STATIC_LIBRARIES := \
    libcurl \
    libssl \
    libcrypto

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH) \
    $(LOCAL_PATH)/ImGui \
    $(LOCAL_PATH)/ImGui/backends \
    $(LOCAL_PATH)/Includes \
    $(LOCAL_PATH)/Utilities \
    $(LOCAL_PATH)/Includes/Fonts \
    $(LOCAL_PATH)/Includes/Fonts/raw

LOCAL_SRC_FILES := \
    qazaqdlc.cpp \
    ImGui/imgui.cpp \
    ImGui/imgui_draw.cpp \
    ImGui/imgui_demo.cpp \
    ImGui/imgui_widgets.cpp \
    ImGui/imgui_tables.cpp \
    ImGui/backends/imgui_impl_opengl3.cpp

include $(BUILD_SHARED_LIBRARY)
