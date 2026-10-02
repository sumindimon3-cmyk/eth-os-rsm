#pragma once
#include <stdio.h>
#include <string>
#include <inttypes.h>
#include <codecvt>
#include <locale>

using namespace std;

#ifndef il2cpp
#define il2cpp

typedef void(*Il2CppMethodPointer)();

struct MethodInfo;

struct VirtualInvokeData {
    Il2CppMethodPointer methodPtr;
    const MethodInfo* method;
};

struct Il2CppType {
    void* data;
    unsigned int bits;
};

struct Il2CppClass;

struct Il2CppObject {
    Il2CppClass *klass;
    void *monitor;
};

union Il2CppRGCTXData {
    void* rgctxDataDummy;
    const MethodInfo* method;
    const Il2CppType* type;
    Il2CppClass* klass;
};

struct Il2CppClass_1 {
    void* image;
    void* gc_desc;
    const char* name;
    const char* namespaze;
    Il2CppType* byval_arg;
    Il2CppType* this_arg;
    Il2CppClass* element_class;
    Il2CppClass* castClass;
    Il2CppClass* declaringType;
    Il2CppClass* parent;
    void *generic_class;
    void* typeDefinition;
    void* interopData;
    void* fields;
    void* events;
    void* properties;
    void* methods;
    Il2CppClass** nestedTypes;
    Il2CppClass** implementedInterfaces;
    void* interfaceOffsets;
};

struct Il2CppClass_2 {
    Il2CppClass** typeHierarchy;
    uint32_t cctor_started;
    uint32_t cctor_finished;
    uint64_t cctor_thread;
    int32_t genericContainerIndex;
    int32_t customAttributeIndex;
    uint32_t instance_size;
    uint32_t actualSize;
    uint32_t element_size;
    int32_t native_size;
    uint32_t static_fields_size;
    uint32_t thread_static_fields_size;
    int32_t thread_static_fields_offset;
    uint32_t flags;
    uint32_t token;
    uint16_t method_count;
    uint16_t property_count;
    uint16_t field_count;
    uint16_t event_count;
    uint16_t nested_type_count;
    uint16_t vtable_count;
    uint16_t interfaces_count;
    uint16_t interface_offsets_count;
    uint8_t typeHierarchyDepth;
    uint8_t genericRecursionDepth;
    uint8_t rank;
    uint8_t minimumAlignment;
    uint8_t packingSize;
    uint8_t bitflags1;
    uint8_t bitflags2;
};

struct Il2CppClass {
    Il2CppClass_1 _1;
    void* static_fields;
    Il2CppRGCTXData* rgctx_data;
    Il2CppClass_2 _2;
    VirtualInvokeData vtable[255];
};

typedef int32_t il2cpp_array_size_t;
typedef int32_t il2cpp_array_lower_bound_t;
struct Il2CppArrayBounds {
    il2cpp_array_size_t length;
    il2cpp_array_lower_bound_t lower_bound;
};

struct MethodInfo {
    Il2CppMethodPointer methodPointer;
    void* invoker_method;
    const char* name;
    Il2CppClass *declaring_type;
    const Il2CppType *return_type;
    const void* parameters;
    union {
        const Il2CppRGCTXData* rgctx_data;
        const void* methodDefinition;
    };
    union {
        const void* genericMethod;
        const void* genericContainer;
    };
    int32_t customAttributeIndex;
    uint32_t token;
    uint16_t flags;
    uint16_t iflags;
    uint16_t slot;
    uint8_t parameters_count;
    uint8_t bitflags;
};

struct FieldInfo {
public:
    const char* name;
    const Il2CppType* type;
    Il2CppClass *parent;
    int32_t offset;
    uint32_t token;
};

static inline void utf8_push(std::string& out, uint32_t cp) {
    if (cp <= 0x7F) {
        out.push_back(char(cp));
    } else if (cp <= 0x7FF) {
        out.push_back(char(0xC0 | (cp >> 6)));
        out.push_back(char(0x80 | (cp & 0x3F)));
    } else if (cp <= 0xFFFF) {
        out.push_back(char(0xE0 | (cp >> 12)));
        out.push_back(char(0x80 | ((cp >> 6) & 0x3F)));
        out.push_back(char(0x80 | (cp & 0x3F)));
    } else {
        out.push_back(char(0xF0 | (cp >> 18)));
        out.push_back(char(0x80 | ((cp >> 12) & 0x3F)));
        out.push_back(char(0x80 | ((cp >> 6) & 0x3F)));
        out.push_back(char(0x80 | (cp & 0x3F)));
    }
}

static inline std::string utf16_to_utf8(std::u16string_view u16) {
    std::string out;
    out.reserve(u16.size() * 3 + 4);

    size_t i = 0, n = u16.size();
    if (n && u16[0] == 0xFEFF) { i = 1; }

    while (i < n) {
        uint16_t w1 = u16[i++];

        if (w1 < 0xD800 || w1 > 0xDFFF) {
            utf8_push(out, w1);
            continue;
        }

        if (w1 >= 0xD800 && w1 <= 0xDBFF) {
            if (i < n) {
                uint16_t w2 = u16[i];
                if (w2 >= 0xDC00 && w2 <= 0xDFFF) {
                    ++i;
                    uint32_t cp = 0x10000u + (((uint32_t(w1) - 0xD800u) << 10) | (uint32_t(w2) - 0xDC00u));
                    utf8_push(out, cp);
                    continue;
                }
            }
            utf8_push(out, 0xFFFDu);
            continue;
        }

        utf8_push(out, 0xFFFDu);
    }
    return out;
}

struct il2cppString {
    void* klass;
    void* monitor;
    int32_t length;
    char16_t firstChar;

    const char16_t* data() const { return &firstChar; }
    int32_t size16() const { return length; }

    std::u16string_view view() const {
        return std::u16string_view(data(), static_cast<size_t>(size16()));
    }

    std::string to_utf8() const {
        return utf16_to_utf8(view());
    }
};

static uintptr_t mono_address = 0;

void *il2cpp_get_image(const char *image);
void *il2cpp_get_class_type(const char *image, const char *namespaze, const char *clazz);

void il2cpp_get_static_field(const char *image, const char *namespaze, const char *clazz, const char *name, void *output);
void il2cpp_set_static_field(const char *image, const char *namespaze, const char *clazz, const char *name, void* value);

void *il2cpp_get_method_offset(const char *image, const char *namespaze, const char *clazz, const char *name, int argsCount = 0);
void *il2cpp_get_method_offset(const char *image, const char *namespaze, const char *clazz, const char *name, char** args, int argsCount);

size_t il2cpp_get_field_offset(const char *image, const char *namespaze, const char *clazz, const char *name);

unsigned long il2cpp_get_static_field_offset(const char *image, const char *namespaze, const char *clazz, const char *name);
#endif

