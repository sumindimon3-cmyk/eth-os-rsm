bool timeToInput = true;
void *keyboard = nullptr;

int (*original$$get_touchCount)();
int get_touchCount() {
    ImGuiIO &io = ImGui::GetIO();

    static void *(*TouchScreenKeyboard$$Open)(il2cppString*, int, bool, bool, bool, bool, il2cppString*, int) = nullptr;
    static il2cppString *(*TouchScreenKeyboard$$get_text)(void *) = nullptr;

    if (!TouchScreenKeyboard$$Open) {
        TouchScreenKeyboard$$Open =
            (decltype(TouchScreenKeyboard$$Open)) il2cpp_get_method_offset(
                oxorany("UnityEngine.dll"), oxorany("UnityEngine"),
                oxorany("TouchScreenKeyboard"), oxorany("Open"), 8);
        TouchScreenKeyboard$$get_text =
            (decltype(TouchScreenKeyboard$$get_text)) il2cpp_get_method_offset(
                oxorany("UnityEngine.dll"), oxorany("UnityEngine"),
                oxorany("TouchScreenKeyboard"), oxorany("get_text"), 0);
    }

    if (io.WantTextInput) {
        if (timeToInput && TouchScreenKeyboard$$Open) {
            timeToInput = false;
            keyboard = TouchScreenKeyboard$$Open(
                il2cpp_string_new(""), 0, true, false, false, false, il2cpp_string_new(""), 0);
        }

        if (keyboard && TouchScreenKeyboard$$get_text) {
            if (auto mStr = TouchScreenKeyboard$$get_text(keyboard)) {
                std::string s = mStr->to_utf8();
                if (!s.empty())
                    io.AddInputCharactersUTF8(s.c_str());
            }
        }
    } else {
        timeToInput = true;
    }

    return io.WantCaptureMouse ? 0 : original$$get_touchCount();
}