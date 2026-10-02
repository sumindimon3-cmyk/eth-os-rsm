static std::mutex toastMx;
static float toastTimer = 0.0f;
static float toastDuration = 2.5f;
static std::string toastText;
static bool toastActive = false;

void showToast(const std::string& text, float duration = 2.5f) {
    std::lock_guard<std::mutex> lk(toastMx);
    toastText = text;
    toastDuration = duration > 0.f ? duration : 0.01f;
    toastTimer = toastDuration;
    toastActive = true;
}

void renderToast() {
    std::lock_guard<std::mutex> lk(toastMx);
    if (!toastActive || toastText.empty()) return;

    ImGuiIO& io = ImGui::GetIO();
    toastTimer -= io.DeltaTime;
    if (toastTimer <= 0.f) {
        toastActive = false;
        return;
    }

    const float fade = 0.25f;
    float alpha = 1.0f, slide = 0.f;

    if (toastDuration - toastTimer < fade) {
        float t = (toastDuration - toastTimer) / fade;
        alpha = t; slide = (1.f - t) * 30.f;
    } else if (toastTimer < fade) {
        float t = (toastTimer) / fade;
        alpha = t; slide = (1.f - t) * 30.f;
    }

    ImVec2 txt = ImGui::CalcTextSize(toastText.c_str());
    ImVec2 pad = ImVec2(40.f, 25.f);
    ImVec2 size = txt + pad * 2.f;

    ImVec2 center(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.75f);
    ImVec2 min = center - size * 0.5f + ImVec2(0, slide);
    ImVec2 max = center + size * 0.5f + ImVec2(0, slide);

    ImU32 bg = ImGui::GetColorU32(ImVec4(0.1f,0.1f,0.1f,0.9f * alpha));
    ImU32 text = ImGui::GetColorU32(ImVec4(1,1,1, alpha));

    ImDrawList* dl = ImGui::GetForegroundDrawList();
    dl->AddRectFilled(min + ImVec2(2,2), max + ImVec2(2,2), IM_COL32(0,0,0,(int)(180*alpha)), 8.f);
    dl->AddRectFilled(min, max, bg, 8.f);

    ImVec2 tp = center - txt * 0.5f + ImVec2(0, slide);
    dl->AddText(tp, text, toastText.c_str());
}