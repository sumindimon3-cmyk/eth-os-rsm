//wasnt tested, may not work properly

struct colorPickerExtras {
    bool showToggles = false;
    bool* rainbow = nullptr;
    bool* pulse = nullptr;
    bool* dark = nullptr;
};

static std::unordered_map<ImGuiID, ImVec4> color_backup;

bool AddColorPicker(const char* name, ImVec4& color, colorPickerExtras extras = {}, ImGuiColorEditFlags flags = 0) {
    if (flags == 0) {
        flags = ImGuiColorEditFlags_AlphaBar
              | ImGuiColorEditFlags_AlphaPreview
              | ImGuiColorEditFlags_DisplayRGB
              | ImGuiColorEditFlags_InputRGB
              | ImGuiColorEditFlags_NoSidePreview
              | ImGuiColorEditFlags_NoSmallPreview;
    }

    ImGui::PushID(name);

    const ImGuiColorEditFlags btnFlags = ImGuiColorEditFlags_AlphaPreview;
    bool open_popup = ImGui::ColorButton(oxorany("##color_btn"), color, btnFlags, ImVec2(28, 28));
    ImGui::SameLine();
    ImGui::TextUnformatted(name);

    if (open_popup) {
        ImGui::OpenPopup(oxorany("##picker_popup"));

        ImGuiID pid = ImGui::GetID(oxorany("##picker_popup"));
        color_backup[pid] = color;
    }

    bool changed = false;
    if (ImGui::BeginPopup(oxorany("##picker_popup"))) {
		applyAnimatedGradient();
		
        ImGui::SetNextItemWidth(200.0f);

        ImVec4 tmp = color;
        if (ImGui::ColorPicker4(oxorany("##picker"), reinterpret_cast<float*>(&tmp), flags)) {
            color = tmp;
            changed = true;
        }

        ImGui::SameLine();
        ImGui::BeginGroup();
        ImGui::TextUnformatted(oxorany("Current"));
        ImGui::ColorButton(oxorany("##cur"), color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40));

        ImGuiID pid = ImGui::GetID(oxorany("##picker_popup"));
        ImVec4 prev = color_backup.count(pid) ? color_backup[pid] : color;

        ImGui::TextUnformatted(oxorany("Previous"));
        if (ImGui::ColorButton(oxorany("##prev"), prev, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40))) {
            color = prev;
            changed = true;
        }

        if (extras.showToggles) {
            if (extras.rainbow) {
                ImGui::Separator();
                ImGui::Checkbox(oxorany("Rainbow"), extras.rainbow);
            }
            if (extras.pulse) {
                ImGui::Checkbox(oxorany("Pulse"), extras.pulse);
            }
            if (extras.dark) {
                ImGui::Checkbox(oxorany("Dark"), extras.dark);
            }
        }

        ImGui::Spacing();
        if (ImGui::Button(oxorany("OK"), ImVec2(80, 0))) {
            ImGui::CloseCurrentPopup();
            color_backup.erase(pid);
        }
        ImGui::SameLine();
        if (ImGui::Button(oxorany("Cancel"), ImVec2(80, 0))) {
            color = prev;
            ImGui::CloseCurrentPopup();
            color_backup.erase(pid);
            changed = true;
        }
        ImGui::EndGroup();

        ImGui::EndPopup();
    }

    ImGui::PopID();
    return changed;
}
