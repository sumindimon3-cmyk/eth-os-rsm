namespace DebugMenu {
    static std::deque<std::pair<std::string,int>> debugLogs;
    static bool showDebugMenu = false;
    static int logLevel = 0;

    void AddLog(const std::string& msg, int level = 0) {
        if (level < logLevel) return;
        debugLogs.emplace_back(msg, level);
        if (debugLogs.size() > 2000) debugLogs.erase(debugLogs.begin(), debugLogs.begin() + 1000);
    }

    void Render() {
        if (!showDebugMenu) return;

        ImGui::SetNextWindowSize(ImVec2(1100, 650), ImGuiCond_FirstUseEver);
        if (ImGui::Begin(oxorany("Debug Menu"), &showDebugMenu, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar)) {

            applyAnimatedGradient();

            ImGui::BeginChild(oxorany("LogRegion"), ImVec2(1050, 480), true);
            std::string ICON_INFO = oxorany("info");
            std::string ICON_WARN = oxorany("warning");
            std::string ICON_ERR  = oxorany("error");

            for (const auto& [msg, level] : debugLogs) {
                const char* icon = ICON_INFO.c_str();
                ImVec4 col(0.8f,0.8f,0.8f,1.0f);
                if (level == 1) {
					icon = ICON_WARN.c_str();
					col = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
				} else if (level == 2) {
					icon = ICON_ERR.c_str();
					col = ImVec4(1.0f, 0.2f, 0.2f, 1.0f);
				}
                ImGui::PushStyleColor(ImGuiCol_Text, col);
                ImGui::Text(oxorany("[%s] %s"), icon, msg.c_str());
                ImGui::PopStyleColor();
            }
            ImGui::EndChild();

            ImGui::Separator();
            if (ImGui::Button(oxorany("Clear Logs"))) {
                debugLogs.clear();
                AddLog(oxorany("logs cleared"));
                showToast(oxorany("cleared logs successfully"), 3.0f);
            }
        }
        ImGui::End();
    }
}
