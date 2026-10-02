#pragma once

namespace weather {
    struct RNG {
        unsigned int x = 123456789u, y = 362436069u, z = 521288629u, w = 88675123u;
        inline unsigned int nextU32() {
            unsigned int t = x ^ (x << 11);
            x = y; y = z; z = w;
            w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
            return w;
        }
        inline float frand01() {
            return (nextU32() & 0xFFFFFF) / float(0x1000000);
        }
        inline float frand(float a, float b) {
            return a + (b - a) * frand01();
        }
        inline int irand(int a, int b) {
            return a + int(frand01() * float((b - a) + 1));
        }
    };

    struct settings {
        float intensity = 1.0f;
        float wind = 0.0f;
        float angleDeg = 12.0f;
        float alpha = 1.0f;
        int maxSnow = 400;
        int maxRain = 800;
        bool highQuality = true;
    };

    struct snowflake {
        ImVec2 pos;
        float depth;
        float radius;
        float speedY;
        float swayAmp;
        float phase;
    };

    static std::vector<snowflake> snow;
    static RNG rng_snow;

    inline void SpawnSnowflake(const ImVec2& view, snowflake& f, bool fromTop) {
        f.depth  = rng_snow.frand(0.0f, 1.0f);
        f.radius = 1.0f + 2.5f * f.depth;
        f.speedY = 25.0f + 95.0f * f.depth;
        f.swayAmp= 8.0f  + 20.0f * f.depth;
        f.phase  = rng_snow.frand(0.0f, 6.2831853f);

        float x = rng_snow.frand(0.0f, view.x);
        float y = fromTop ? -rng_snow.frand(0.0f, view.y * 0.2f) : rng_snow.frand(0.0f, view.y);
        f.pos = ImVec2(x, y);
    }

    inline void EnsureSnowCapacity(const ImVec2& view, int want) {
        if ((int)snow.size() < want) {
            size_t need = (size_t)want - snow.size();
            snow.reserve(want + 64);
            for (size_t i = 0; i < need; ++i) {
                snowflake f; SpawnSnowflake(view, f, false); snow.push_back(f);
            }
        } else if ((int)snow.size() > want) {
            snow.resize(want);
        }
    }

    inline void UpdateAndDrawSnow(const settings& set) {
        ImGuiIO& io = ImGui::GetIO();
        const ImVec2 view = io.DisplaySize;
        if (view.x <= 0 || view.y <= 0) return;

        EnsureSnowCapacity(view, std::max(0, set.maxSnow));

        ImDrawList* dl = ImGui::GetBackgroundDrawList();
        const float dt = io.DeltaTime > 0 ? io.DeltaTime : 1.0f/60.0f;
        const float swayFreq = 1.2f;
        const int circleSeg = set.highQuality ? 16 : 10;

        for (auto& f : snow) {
            f.pos.y += f.speedY * set.intensity * dt;
            float sway = std::sin(f.phase + ImGui::GetTime() * swayFreq) * f.swayAmp;
            f.pos.x += (sway + set.wind * (0.4f + 0.6f * f.depth)) * dt;
            if (f.pos.x < -10.0f) f.pos.x += view.x + 20.0f;
            if (f.pos.x > view.x + 10.0f) f.pos.x -= view.x + 20.0f;
            if (f.pos.y > view.y + 8.0f) SpawnSnowflake(view, f, true);

            float twinkle = 0.75f + 0.25f * std::sin(f.phase * 1.7f + ImGui::GetTime() * (1.0f + 2.5f*f.depth));
            unsigned char a = (unsigned char)(255.0f * set.alpha * twinkle);
            ImU32 col = IM_COL32(255, 255, 255, a);
            dl->AddCircleFilled(f.pos, f.radius, col, circleSeg);
        }
    }

    inline void OnDisplayResizeReset() {
        snow.clear();
    }
}