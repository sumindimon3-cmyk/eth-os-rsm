struct animations {
    float value = 0.0f;
    float vel = 0.0f;
    float stiffness = 200.0f;
    float damping = 30.0f;
    bool useSpring = true;

    void Update(float dt, float target) {
        if (useSpring) {
            float k = stiffness;
            float c = damping;

            float acc = k * (target - value) - c * vel;
            vel += acc * dt;
            value += vel * dt;

            if (fabsf(vel) < 0.001f && fabsf(target - value) < 0.001f) {
                value = target;
                vel = 0.0f;
            }
        } else {

            float t = 1.0f - powf(0.001f, dt);
            value = value + (target - value) * t;
        }
    }
};

static float LerpF(float a, float b, float t) {
    return a + (b - a) * t;
}

static float EaseOutCubic(float t) {
    t = t - 1.0f; return t * t * t + 1.0f;
}

static float EaseInOutQuad(float t) {
    return t<0.5f ? 2*t*t : -1+(4-2*t)*t;
}

static ImU32 LerpCol(ImU32 a, ImU32 b, float t) {
    ImVec4 ca = ImGui::ColorConvertU32ToFloat4(a);
    ImVec4 cb = ImGui::ColorConvertU32ToFloat4(b);
    ImVec4 c  = ImVec4(
        ImLerp(ca.x, cb.x, t),
        ImLerp(ca.y, cb.y, t),
        ImLerp(ca.z, cb.z, t),
        ImLerp(ca.w, cb.w, t)
    );
    return ImGui::ColorConvertFloat4ToU32(c);
}

struct GUIAnimState {
    animations openAlpha;
    animations popScale;
    animations tabSlide;
    float time = 0.0f;
    int currentTab = 1;
    int prevTab = 1;
    animations hoverIcon[8];
    animations buttonPulse;
    int targetTab = 1;
    float slideProg = 0.0f;
    float alpha = 1.0f;
} anim;

void initAnimations() {
    anim.openAlpha.value = 0.0f;
    anim.openAlpha.useSpring = true;
    anim.openAlpha.stiffness = 90.0f;
    anim.openAlpha.damping = 18.0f;

    anim.popScale.value = 0.9f;
    anim.popScale.useSpring = true;
    anim.popScale.stiffness = 50.0f;
    anim.popScale.damping = 12.0f;

    anim.tabSlide.value = 0.0f;
    anim.tabSlide.useSpring = false;

    for (int i=0;i<8;i++){
        anim.hoverIcon[i].value = 0.0f;
        anim.hoverIcon[i].useSpring = true;
        anim.hoverIcon[i].stiffness = 120.0f;
        anim.hoverIcon[i].damping = 18.0f;
    }
    anim.buttonPulse.value = 0.0f;
    anim.buttonPulse.useSpring = false;
}

static float gradientOffset = 0.0f;

void applyAnimatedStrips() {
    ImDrawList* bg = ImGui::GetBackgroundDrawList();
    ImGuiIO& io = ImGui::GetIO();

    ImVec2 s(0,0), e((float)ints.glWidth, (float)ints.glHeight);

    gradientOffset += (io.DeltaTime > 0 ? io.DeltaTime : 1.f/60.f) * 0.03f;
    if (gradientOffset > 1.0f) gradientOffset -= 1.0f;

    for (int i=0;i<40;i++){
        float nx = fmodf((float)i*0.127f + gradientOffset*2.0f, 1.0f);
        float x = s.x + nx * (e.x - s.x);
        int a = (int)((20 + 20 * sinf(anim.time*1.2f + i)) * floats.GUIalpha);
        bg->AddLine(ImVec2(x, s.y), ImVec2(x+30.0f, e.y), IM_COL32(255,255,255, a), 0.6f);
    }
}

void AddRectOutline(ImDrawList* draw, ImVec2 tl, ImVec2 br, ImU32 col, float rounding, float thickness) {
    draw->AddRect(tl, br, IM_COL32(0,0,0,200), rounding, 0, thickness+2.0f);
    draw->AddRect(tl, br, col, rounding, 0, thickness);
}

bool AnimatedIconButton(int idx, const char* label, ImFont* iconsFont, ImVec2 size) {
    ImGuiIO& io = ImGui::GetIO();
    const float dt = io.DeltaTime > 0 ? io.DeltaTime : 1.f/60.f;

    ImGui::PushID(idx);

    ImGui::InvisibleButton(oxorany("##icon"), size);
    const bool clicked = ImGui::IsItemClicked();
    const bool hovered = ImGui::IsItemHovered();
    const bool active  = ImGui::IsItemActive();

    ImVec2 min = ImGui::GetItemRectMin();
    ImVec2 max = ImGui::GetItemRectMax();
    ImVec2 center = ImVec2((min.x+max.x)*0.5f, (min.y+max.y)*0.5f);

    anim.hoverIcon[idx].Update(dt, hovered ? 1.0f : 0.0f);
    const float hoverT = anim.hoverIcon[idx].value;
    const float alpha  = (0.6f + 0.4f * hoverT) * floats.GUIalpha;

    const ImU32 cIdle   = IM_COL32(30, 30, 30,  (int)(255*alpha));
    const ImU32 cHover  = IM_COL32(50, 50, 50,  (int)(255*alpha));
    const ImU32 cActive = IM_COL32(75, 75, 75,  (int)(255*alpha));

    ImU32 bgCol = LerpCol(cIdle, cHover, hoverT);
    if (active) bgCol = LerpCol(bgCol, cActive, 0.65f);

    ImDrawList* draw = ImGui::GetWindowDrawList();
    const float scale = 1.0f + 0.08f * hoverT;
    ImVec2 half = ImVec2((size.x*0.5f)*scale, (size.y*0.5f)*scale);
    ImVec2 tl = ImVec2(center.x - half.x, center.y - half.y);
    ImVec2 br = ImVec2(center.x + half.x, center.y + half.y);

    draw->AddRectFilled(ImVec2(tl.x+2, tl.y+2), ImVec2(br.x+2, br.y+2), IM_COL32(0,0,0,(int)(100*alpha)), 12.0f);
    draw->AddRectFilled(tl, br, bgCol, 10.0f);
    draw->AddRect(tl, br, IM_COL32(0,0,0,(int)(200*alpha)), 10.0f, 0, 1.5f);

    ImGui::PushFont(iconsFont);
    ImVec2 txtSize = ImGui::CalcTextSize(label);
    ImVec2 textPos = ImVec2(center.x - txtSize.x/2.0f, center.y - txtSize.y/2.0f);
    ImU32 iconCol = IM_COL32(230, 232, 237, (int)(255*alpha));
	
    draw->AddText(iconsFont, ImGui::GetFontSize()+6.0f, ImVec2(textPos.x+1,textPos.y), IM_COL32(0,0,0,(int)(140*alpha)), label);
    draw->AddText(iconsFont, ImGui::GetFontSize()+6.0f, textPos, iconCol, label);
    ImGui::PopFont();

    ImGui::PopID();
    return clicked;
}

struct PageSwitch {
    int from = 1;
    int to = 1;
    float t = 1.0f;
    float speed = 6.0f;
    int dir = 1;
    void Start(int f, int n) {
		from = f;
		to = n;
		t = 0.0f;
		dir = (n > f) ? +1 : -1;
	}
	
    bool Active() const {
		return t < 1.0f;
	}
    float Update(float dt){
		t = ImClamp(t + dt * speed, 0.f, 1.f);
		return EaseOutCubic(t);
	}
} g_page;

void onTabChanged(int newTab) {
    if (anim.targetTab != newTab) {
        g_page.Start(anim.currentTab, newTab);
        anim.targetTab = newTab;
    }
}

float updateTabProgress(float& prog, float dt) {
    prog += dt * 3.0f;
    if (prog > 1.0f) prog = 1.0f;
    return EaseOutCubic(prog);
}

#include "interface.hpp"

static void DrawPageChild(const char* id, int tab, ImVec2 pos, ImVec2 size, float alpha) {
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
    ImGui::SetCursorScreenPos(pos);
    ImGui::BeginChild(id, size, false,
        ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground);
    RenderTabPage(tab);
    ImGui::EndChild();
    ImGui::PopStyleVar();
}

void startAnimations() {
    float dt = ImGui::GetIO().DeltaTime;
    anim.time += dt;
    anim.buttonPulse.Update(dt, (sinf(anim.time*2.0f) * 0.5f + 0.5f) * 0.8f);
}

void drawTabArea() {
    ImGuiIO& io = ImGui::GetIO();
    const float dt = (io.DeltaTime > 0 ? io.DeltaTime : 1.f/60.f);
    const float k  = g_page.Update(dt);
	
    ImVec2 pos  = ImGui::GetCursorScreenPos();
    ImVec2 size = ImGui::GetContentRegionAvail();

    if (g_page.Active()) {
        const float w = size.x;
        ImVec2 fromPos = ImVec2(pos.x - g_page.dir * w * k,       pos.y);
        ImVec2 toPos   = ImVec2(pos.x + g_page.dir * w * (1.f-k), pos.y);

        DrawPageChild(oxorany("##page_from"), g_page.from, fromPos, size, 1.f - k);
        DrawPageChild(oxorany("##page_to"),   g_page.to,   toPos,   size, k);

        if (k >= 1.0f) anim.currentTab = anim.targetTab;
    } else {
        anim.currentTab = anim.targetTab;
        DrawPageChild(oxorany("##page"), anim.currentTab, pos, size, 1.f);
    }
}
