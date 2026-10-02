#include "il2cpp.hpp"

namespace {
    const void *(*il2cpp_assembly_get_image)(const void *assembly);
    void *(*il2cpp_domain_get)();
    void **(*il2cpp_domain_get_assemblies)(const void *domain, size_t *size);
    const char *(*il2cpp_image_get_name)(void *image);
    void *(*il2cpp_class_from_name)(const void *image, const char *namespaze, const char *name);
    void *(*il2cpp_class_get_field_from_name)(void *klass, const char *name);
    void *(*il2cpp_class_get_method_from_name)(void *klass, const char *name, int argsCount);
    size_t (*il2cpp_field_get_offset)(void *field);
    void (*il2cpp_field_static_get_value)(void *field, void *value);
    void (*il2cpp_field_static_set_value)(void *field, void *value);
    void *(*il2cpp_array_new)(void *elementTypeInfo, size_t length);
    uint16_t *(*il2cpp_string_chars)(void *str);
    il2cppString *(*il2cpp_string_new)(const char *str);
    il2cppString *(*il2cpp_string_new_utf16)(const wchar_t *str, int32_t length);
    char *(*il2cpp_type_get_name)(void *type);
    void* (*il2cpp_method_get_param)(void *method, uint32_t index);
    void* (*il2cpp_class_get_methods)(void *klass, void* *iter);
    const char* (*il2cpp_method_get_name)(void *method);
    void *(*il2cpp_object_new)(void *klass);
	void* (*il2cpp_resolve_icall)(const char* name);
}



void il2cppModules() {
    void* handle = dlopen_ex(oxorany("libil2cpp.so"), 0);
    while (!handle) {
        handle = dlopen_ex(oxorany("libil2cpp.so"), 0);
        sleep(1);
    }

    il2cpp_assembly_get_image = (const void *(*)(const void *)) dlsym_ex(handle, oxorany("il2cpp_assembly_get_image"));
    il2cpp_domain_get = (void *(*)()) dlsym_ex(handle, oxorany("il2cpp_domain_get"));
    il2cpp_domain_get_assemblies = (void **(*)(const void* , size_t*)) dlsym_ex(handle, oxorany("il2cpp_domain_get_assemblies"));
    il2cpp_image_get_name = (const char *(*)(void *)) dlsym_ex(handle, oxorany("il2cpp_image_get_name"));
    il2cpp_class_from_name = (void* (*)(const void*, const char*, const char *)) dlsym_ex(handle, oxorany("il2cpp_class_from_name"));
    il2cpp_class_get_field_from_name = (void* (*)(void*, const char *)) dlsym_ex(handle, oxorany("il2cpp_class_get_field_from_name"));
    il2cpp_class_get_method_from_name = (void* (*)(void *, const char*, int)) dlsym_ex(handle, oxorany("il2cpp_class_get_method_from_name"));
    il2cpp_field_get_offset = (size_t (*)(void *)) dlsym_ex(handle, oxorany("il2cpp_field_get_offset"));
    il2cpp_field_static_get_value = (void (*)(void*, void *)) dlsym_ex(handle, oxorany("il2cpp_field_static_get_value"));
    il2cpp_field_static_set_value = (void (*)(void*, void *)) dlsym_ex(handle, oxorany("il2cpp_field_static_set_value"));
    il2cpp_array_new = (void *(*)(void*, size_t)) dlsym_ex(handle, oxorany("il2cpp_array_new"));
    il2cpp_string_chars = (uint16_t *(*)(void*)) dlsym_ex(handle, oxorany("il2cpp_string_chars"));
    il2cpp_string_new = (il2cppString *(*)(const char *)) dlsym_ex(handle, oxorany("il2cpp_string_new"));
    il2cpp_string_new_utf16 = (il2cppString *(*)(const wchar_t *, int32_t)) dlsym_ex(handle, oxorany("il2cpp_string_new"));
    il2cpp_type_get_name = (char *(*)(void *)) dlsym_ex(handle, oxorany("il2cpp_type_get_name"));
    il2cpp_method_get_param = (void *(*)(void *, uint32_t)) dlsym_ex(handle, oxorany("il2cpp_method_get_param"));
    il2cpp_class_get_methods = (void *(*)(void *, void **)) dlsym_ex(handle, oxorany("il2cpp_class_get_methods"));
    il2cpp_method_get_name = (const char *(*)(void *)) dlsym_ex(handle, oxorany("il2cpp_method_get_name"));
    il2cpp_object_new = (void *(*)(void *)) dlsym_ex(handle, oxorany("il2cpp_object_new"));
    il2cpp_resolve_icall = (void *(*)(const char *)) dlsym_ex(handle, oxorany("il2cpp_resolve_icall"));
    
    dlclose_ex(handle);
}

void* il2cpp_get_image(const char *image) {
    size_t size;
    void **assemblies = il2cpp_domain_get_assemblies(il2cpp_domain_get(), &size);
    for(int i = 0; i < size; ++i) {
        void *img = (void *)il2cpp_assembly_get_image(assemblies[i]);

        const char *img_name = il2cpp_image_get_name(img);

        if (strcmp(img_name, image) == 0) {
            return img;
        }
    }
    return 0;
}

void* il2cpp_get_class_type(const char *image, const char *namespaze, const char *clazz) {
    static std::map<std::string, void *> cache;

    std::string s = image;
    s += namespaze;
    s += clazz;

    if (cache.count(s) > 0)
        return cache[s];

    void *img = il2cpp_get_image(image);
    if (!img)
        return 0;

    void *klass = il2cpp_class_from_name(img, namespaze, clazz);
    if (!klass)
        return 0;

    cache[s] = klass;
    return klass;
}

void il2cpp_get_static_field_value(const char *image, const char *namespaze, const char *clazz, const char *name, void *output) {
    void *img = il2cpp_get_image(image);
    if (!img)
        return;
    void *klass = il2cpp_get_class_type(image, namespaze, clazz);
    if (!klass)
        return;

    void *field = il2cpp_class_get_field_from_name(klass, name);
    if (!field)
        return;

    il2cpp_field_static_get_value(field, output);
}

void il2cpp_set_static_field_value(const char *image, const char *namespaze, const char *clazz, const char *name, void* value) {
    void *img = il2cpp_get_image(image);
    if (!img)
        return;
    void *klass = il2cpp_get_class_type(image, namespaze, clazz);
    if (!klass)
        return;

    void *field = il2cpp_class_get_field_from_name(klass, name);
    if (!field)
        return;

    il2cpp_field_static_set_value(field, value);
}

void* il2cpp_get_method_offset(const char *image, const char *namespaze, const char *clazz, const char *name, int argsCount) {
    void *img = il2cpp_get_image(image);
    if (!img)
        return 0;

    void *klass = il2cpp_get_class_type(image, namespaze, clazz);
    if (!klass)
        return 0;

    void **method = (void**)il2cpp_class_get_method_from_name(klass, name, argsCount);
    if (!method)
        return 0;
 
    return *method;
}

void* il2cpp_get_method_offset(const char *image, const char *namespaze, const char *clazz, const char *name, char** args, int argsCount) {
    void *img = il2cpp_get_image(image);
    if (!img)
        return 0;

    void *klass = il2cpp_get_class_type(image, namespaze, clazz);
    if (!klass)
        return 0;

    void *iter = 0;

    int score = 0;

    void **method = (void**) il2cpp_class_get_methods(klass, &iter);
    while (method) {
        const char *fname = il2cpp_method_get_name(method);
        if (strcmp(fname, name) == 0) {
            for (int i = 0; i < argsCount; i++) {
                void *arg = il2cpp_method_get_param(method, i);
                if (arg) {
                    const char *tname = il2cpp_type_get_name(arg);
                    if (strcmp(tname, args[i]) == 0) {
                        score++;
                    } else {
                        score = 0;
                        goto skip;
                    }
                }
            }
        }
        skip:

        if (score == argsCount)
            return *method;

        method = (void **) il2cpp_class_get_methods(klass, &iter);
    }
    return 0;
}

size_t il2cpp_get_field_offset(const char *image, const char *namespaze, const char *clazz, const char *name) {
    void *img = il2cpp_get_image(image);
    if (!img)
        return -1;
    
    void *klass = il2cpp_get_class_type(image, namespaze, clazz);
    if (!klass)
        return -1;

    void *field = il2cpp_class_get_field_from_name(klass, name);
    if (!field)
        return -1;
        
    auto result = il2cpp_field_get_offset(field);

    return result;
}

unsigned long il2cpp_get_static_field_offset(const char *image, const char *namespaze, const char *clazz, const char *name) {
    void *img = il2cpp_get_image(image);
    if (!img)
        return -1;
    
    void *klass = il2cpp_get_class_type(image, namespaze, clazz);
    if (!klass) 
        return -1;
        

    FieldInfo *field = (FieldInfo*)il2cpp_class_get_field_from_name(klass, name);
    if (!field) 
        return -1;

    return (unsigned long)((uint64_t)field->parent->static_fields + field->offset);
}

bool assemblies_loaded() {
    size_t size;
    void** assemblies = il2cpp_domain_get_assemblies(il2cpp_domain_get(), &size);
    return (size != 0 && assemblies != 0);
}