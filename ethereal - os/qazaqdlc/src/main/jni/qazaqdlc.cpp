#include "includes.hpp"

std::string menuTitle = oxorany("qazaqdlc os");
std::string menuDesc = oxorany("");

JNIEnv* env;

#define UI_TEXT(id) ImGui::Text(oxorany(id))
#define UI_CHECKBOX(id, v) ImGui::Checkbox(oxorany(id), v)
#define UI_SLIDERFLOAT(id, v, min, max) ImGui::SliderFloat(oxorany(id), v, min, max)
#define UI_SLIDERINT(id, v, min, max) ImGui::SliderInt(oxorany(id), v, min, max)
#define UI_HEADER(id) ImGui::CollapsingHeader(oxorany(id))
#define UI_BUTTON(id) ImGui::Button(oxorany(id))
#define UI_COMBO(id, ...) ImGui::Combo(oxorany(id), __VA_ARGS__)

#include "qazaqdlc/colorpicker.hpp"
#include "qazaqdlc/animations.cpp"

static void UpdateOpenClose()
{
    ImGuiIO& io = ImGui::GetIO();
    const float dt = (io.DeltaTime > 0 ? io.DeltaTime : 1.f/60.f);

    const float targetAlpha = bools.isGUIopened ? 1.0f : 0.0f;
    anim.openAlpha.Update(dt, targetAlpha);
    anim.popScale.Update(dt, bools.isGUIopened ? 1.0f : 0.0f);
    anim.time += dt;

    floats.GUIalpha = anim.openAlpha.value;
}

static void GUI() {
    if (anim.openAlpha.value <= 0.01f) return;
    
	ImGui::SetNextWindowBgAlpha(anim.openAlpha.value);
    ImGui::SetNextWindowSize(ImVec2(1100 * anim.popScale.value, 630 * anim.popScale.value), ImGuiCond_Always);
	
    startAnimations();
    applyAnimatedStrips();

    ImGui::Begin(oxorany("GUI"), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus);

    RectangleShadowSettings shadowSettings;
    
    shadowSettings.rectSize = ImVec2(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
    
    shadowSettings.sigma = 30;
    shadowSettings.padding = ImVec2(0, 0);
    shadowSettings.rectPos = shadowSettings.padding;
    shadowSettings.rings = 15;
    shadowSettings.spacingBetweenRings = 5;
    shadowSettings.samplesPerCornerSide = 20;
    shadowSettings.spacingBetweenSamples = 15;
    shadowSettings.shadowColor = ImColor(255, 255, 255, 255);
    shadowSettings.shadowSize = ImVec2(15, 15);

	drawRectangleShadowVerticesAdaptive(shadowSettings);
	
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(ints.glWidth, ints.glHeight), ImColor(0, 0, 0, ints.backgroundTransparency), 0, 0);

	applyAnimatedGradient();
	
    ImVec2 cursorposition = ImGui::GetCursorPos();
    ImVec2 windowposition = ImGui::GetWindowPos();
    
    cursorposition.x += windowposition.x;
    cursorposition.y += windowposition.y;
    
    ImDrawList *windowDrawList = ImGui::GetWindowDrawList();

    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
        
    ImGui::PushFont(MontserratFontLarge);
        
    ImGui::Text(menuTitle.c_str());
    
    ImGui::PopFont();
        
    ImGui::PushFont(MontserratFontMedium);
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(150, 150, 150, 255));
          
    ImGui::Text(menuDesc.c_str());
    
    ImGui::PopStyleColor();
    ImGui::PopFont();
        
    ImGui::PopStyleVar(5);
        
    ImGui::Spacing();
    ImGui::Separator();
      
    ImGui::BeginChild(oxorany("##leftChild"), ImVec2(ImGui::GetWindowSize().x / 9.916f, ImGui::GetContentRegionAvail().y), false, ImGuiWindowFlags_NoScrollbar);
    
    if (AnimatedIconButton(0, ICON_FA_CROSSHAIRS, Icons, ImVec2(100,100)))
    	onTabChanged(1);

	if (AnimatedIconButton(1, ICON_FA_EYE_LOW_VISION, Icons, ImVec2(100,100)))
    	onTabChanged(2);

	if (AnimatedIconButton(2, ICON_FA_GUN, Icons, ImVec2(100,100)))
    	onTabChanged(3);

	if (AnimatedIconButton(3, ICON_FA_GEAR, Icons, ImVec2(100,100)))
    	onTabChanged(4);
    
    ImGui::EndChild();
	
    {
        ImGui::SameLine(0);
        ImGui::SameLine();
    }
    
    ImGui::BeginChild(oxorany("##rightChild"), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));
    
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
        
    ImGui::PopStyleVar(5);
    ImGui::Spacing();
	
	drawTabArea();

    ImGui::EndChild();
	ImGui::End();
}

static void renderer() {
    ImGuiIO& io = ImGui::GetIO();
    
    static weather::settings sSet;
    sSet.highQuality = true;
    sSet.intensity = 1.0f;
    sSet.wind = 50.0f;

    sSet.maxSnow = 420;
    sSet.maxRain = 0;
    
    if (bools.isGUIopened && bools.snowflakes) weather::UpdateAndDrawSnow(sSet);
    
	ImGui::SetNextWindowSize(ImVec2(150, 150));
    ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 0.0f);
    ImGui::Begin(oxorany("GUI Button"), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
       
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 0);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 0);

	applyAnimatedGradient();
	
    if (ImGui::Button(oxorany("MENU"), ImVec2(100, 100))) bools.isGUIopened = !bools.isGUIopened;
	
	ImGui::End();
    
	if (bools.silentFOV) {
    ImGui::Begin(oxorany("silentFOV"), nullptr,
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoFocusOnAppearing |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoMouseInputs
    );

    ImVec2 center(ints.glWidth / 2, ints.glHeight / 2);
    ImU32 color = ImGui::ColorConvertFloat4ToU32(ImVec4(colors::silentColor));
	float outlineThickness = 1.5f;
	
    switch (ints.silentType) {
        case 0:
			ImGui::GetForegroundDrawList()->AddCircle(center, floats.silentAimFOV + outlineThickness, IM_COL32(0, 0, 0, 255), 0);
            ImGui::GetForegroundDrawList()->AddCircle(center, floats.silentAimFOV, color, 0);
            break;
		
        case 1:
			ImGui::GetForegroundDrawList()->AddCircle(center, floats.silentAimFOV + outlineThickness, IM_COL32(0, 0, 0, 255), 6);
            ImGui::GetBackgroundDrawList()->AddCircle(center, floats.silentAimFOV, color, 6);
            break;
        case 2:
			ImGui::GetForegroundDrawList()->AddCircle(center, floats.silentAimFOV + outlineThickness, IM_COL32(0, 0, 0, 255), 4);
            ImGui::GetBackgroundDrawList()->AddCircle(center, floats.silentAimFOV, color, 4);
            break;
        case 3: 
            break;
        
        case 4:
			ImGui::GetForegroundDrawList()->AddCircle(center, floats.silentAimFOV + outlineThickness, IM_COL32(0, 0, 0, 255), 2);
            ImGui::GetBackgroundDrawList()->AddCircle(center, floats.silentAimFOV, color, 2);
            break;			
    }

        ImGui::End();
    }
}

static void styleForGUI() {
    ImGuiStyle &style = ImGui::GetStyle();

    style.GrabRounding = 5.0f;

    style.WindowMinSize = ImVec2(0,0);
    style.ScrollbarSize = 14.0f;
    style.ButtonTextAlign = ImVec2(0.5, 0.5);
    style.WindowTitleAlign = ImVec2(0.5, 0.5);
    style.WindowBorderSize = 2.0f;
    style.WindowRounding = 6.0f;
    style.FrameRounding = 3.0f;
    style.ScrollbarRounding = 4.0f;

    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.85f);
    style.Colors[ImGuiCol_Border] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.000f, 0.260f, 0.619f, 0.400f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(24/255.0f, 24/255.0f, 24/255.0f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(190/255.0f, 190/255.0f, 190/255.0f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImColor(190/255.0f, 190/255.0f, 190/255.0f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(16/255.0f, 16/255.0f, 16/255.0f, 1.00f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.00f);
	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(30/255.0f, 30/255.0f, 30/255.0f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(28/255.0f, 28/255.0f, 28/255.0f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(28/255.0f, 28/255.0f, 28/255.0f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(36/255.0f, 36/255.0f, 36/255.0f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(40/255.0f, 40/255.0f, 40/255.0f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(40/255.0f, 40/255.0f, 40/255.0f, 1.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(30/255.0f, 30/255.0f, 30/255.0f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(28/255.0f, 28/255.0f, 28/255.0f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(28/255.0f, 28/255.0f, 28/255.0f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(30/255.0f, 30/255.0f, 30/255.0f, 1.00f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(28/255.0f, 28/255.0f, 28/255.0f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(28/255.0f, 28/255.0f, 28/255.0f, 1.00f);
    style.Colors[ImGuiCol_Tab] = ImLerp(style.Colors[ImGuiCol_Header], style.Colors[ImGuiCol_TitleBgActive], 0.80f);
    style.Colors[ImGuiCol_TabHovered] = style.Colors[ImGuiCol_HeaderHovered];
    style.Colors[ImGuiCol_TabActive] = ImLerp(style.Colors[ImGuiCol_HeaderActive], style.Colors[ImGuiCol_TitleBgActive], 0.60f);
    style.Colors[ImGuiCol_TabUnfocused] = ImLerp(style.Colors[ImGuiCol_Tab], style.Colors[ImGuiCol_TitleBg], 0.80f); 
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImLerp(style.Colors[ImGuiCol_TabActive], style.Colors[ImGuiCol_TitleBg], 0.40f);   
}

static void Init() {
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    
    ImGuiIO& io = ImGui::GetIO();

    io.DisplaySize = ImVec2((float) ints.glWidth, (float) ints.glHeight);
    
    ImGui_ImplOpenGL3_Init(oxorany("#version 300 es"));
	
	styleForGUI();
	initAnimations();
	
	io.Fonts->AddFontFromMemoryTTF(&MontserratFont, sizeof MontserratFont, 30.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
		
    ImGuiStyle &style = ImGui::GetStyle();
    
    style.FrameRounding = 3.0f;
    style.GrabRounding = 3.0f;
	    
    MontserratFontLarge = io.Fonts->AddFontFromMemoryTTF(&MontserratFontBig, sizeof MontserratFontBig, 70.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
    MontserratFontMedium = io.Fonts->AddFontFromMemoryTTF(MontserratFontMed, sizeof MontserratFontMed, 40.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
        
    RobotoRegular = io.Fonts->AddFontFromMemoryTTF(&MontserratFont, sizeof MontserratFont, 30.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
    
    ImFontConfig font_cfg;  
    font_cfg.MergeMode = true;
    
    static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0x0 };
	
	Icons = io.Fonts->AddFontFromMemoryTTF(FontAwesome6, sizeof FontAwesome6, 30.0f, &font_cfg, icon_ranges);

	floats.dpiScale = 1.1f;
    
    ImGui::GetStyle().ScaleAllSizes(3.0f * floats.dpiScale);
  
}

EGLBoolean (*original$$eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean hook$$eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &ints.glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &ints.glHeight);

    if (!bools.inited) {
        Init();
        bools.inited = true;
    }
	
    ImGuiIO &io = ImGui::GetIO();

    ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();
    
    UpdateOpenClose(); 
	
	GUI();
	DebugMenu::Render();
	
	if (bools.ESP && isPlayerAlive(localPlayer) && isPlayerAlive(enemyPlayer)) _ESP();
		
	renderer();
    renderToast();
	
	ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    return original$$eglSwapBuffers(dpy, surface);
}

static void hook() { installHooks(); }

static void Initializer() { 
	do {
		sleep(1);
	} while (!isLibraryInitialized(oxorany("libil2cpp.so")));
	
	if (isLibraryInitialized(oxorany("libil2cpp.so"))) {
			
	il2cppModules();
	
    void* _eglSwapBuffers = getFunctionAddress(oxorany("libEGL.so"), oxorany("eglSwapBuffers"));
		
    if (_eglSwapBuffers) a64h((void *) _eglSwapBuffers, (void *) hook$$eglSwapBuffers, (void **)& original$$eglSwapBuffers);  

	sleep(5);
	
	if (assemblies_loaded()) {
		std::thread(hook).detach();
		DebugMenu::AddLog(oxorany("hook called"));
	} else DebugMenu::AddLog(oxorany("failed to hook!"), 2);
  } 
	
}

JavaVM* j_vm;
jobject g_context;

jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {

	vm->GetEnv((void **) &env, JNI_VERSION_1_6);
	
	j_vm = vm;
	
	std::thread(Initializer).detach();
	
	registerNativesHook$$Install(env);

	return JNI_VERSION_1_6;
}
