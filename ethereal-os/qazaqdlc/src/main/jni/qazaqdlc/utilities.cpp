bool isLibraryInitialized(const char* library) {
    FILE* f = fopen(oxorany("/proc/self/maps"), oxorany("rt"));
    if (!f) return false;

    char line[512];
    bool found = false;
    while (fgets(line, sizeof(line), f)) {
        if (strstr(line, library)) {
            found = true;
            break;
        }
    }
    fclose(f);
    return found;
}

uint64_t stringToOffset(const char* s) {
    errno = 0;
    char* end = nullptr;
    unsigned long long v = strtoull(s, &end, 0);
    return (uint64_t)v;
}

uint64_t string2Offset(const char* s) {
    return stringToOffset(s);
}

void* getFunctionAddress(const char* library, const char* symbol) {
    void* handle = dlopen_ex(library, RTLD_LAZY);
    
    if (!handle) return nullptr;

    void* address = dlsym_ex(handle, symbol);
    
    if (!address) {
        dlclose_ex(handle);
        return nullptr;
    }

    return address;
}

void applyAnimatedGradient() {
    ImGuiIO& io = ImGui::GetIO();
    
    ImVec2 window_size = ImGui::GetWindowSize();
    ImVec2 window_pos = ImGui::GetWindowPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    ImVec2 rect_min = window_pos;
    ImVec2 rect_max = ImVec2(window_pos.x + window_size.x, window_pos.y + window_size.y);

    float time = ImGui::GetTime();
    float speed = 0.7f;

    auto animatedColor = [&](float offset) -> ImU32 {
        float r = sinf(time * speed + offset) * 0.5f + 0.5f;
		float minGray = 0.1f;
		float maxGray = 0.2f;
		float finalGray = minGray + (maxGray - minGray) * r;
		int finalGrayInt = (int)(finalGray * 255);
		return IM_COL32(finalGrayInt, finalGrayInt, finalGrayInt, 255);
    };

    ImU32 color_top_left     = animatedColor(0.0f);
    ImU32 color_top_right    = animatedColor(1.0f);
    ImU32 color_bottom_left  = animatedColor(2.0f);
    ImU32 color_bottom_right = animatedColor(3.0f);

    draw_list->AddRectFilledMultiColor(
        rect_min, rect_max,
        color_top_left, color_top_right,
        color_bottom_left, color_bottom_right
    );

    ImU32 shine_left  = IM_COL32(255,255,255,16);
    ImU32 shine_right = IM_COL32(255,255,255,4);

    ImVec2 shine_top    = ImVec2(window_pos.x, window_pos.y);
    ImVec2 shine_bottom = ImVec2(window_pos.x + window_size.x, window_pos.y + 12);

    draw_list->AddRectFilledMultiColor(
        shine_top, shine_bottom,
        shine_left, shine_right,
        shine_left, shine_right
    );

    ImU32 border = IM_COL32(0, 0, 0, 140);
    draw_list->AddRect(rect_min, rect_max, border, 6.0f, 0, 1.2f);
}