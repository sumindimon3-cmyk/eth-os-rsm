void RenderTabPage(int tabIndex) {
    switch (tabIndex) {
        case 1: {
            if (UI_HEADER("Silent Aim")) {
                UI_CHECKBOX("Activate Silent Aim", &bools.silentAim);
                if (bools.silentAim) {
                    UI_CHECKBOX("draw FOV", &bools.silentFOV);
                    UI_SLIDERFLOAT("FOV Size", &floats.silentAimFOV, 0.f, 400.f);

                    ImGui::SameLine();
                    
                    AddColorPicker("     ", *(ImVec4*)&colors::silentColor);

                    UI_COMBO("FOV Shape", &ints.silentType, chars::silentShapes, IM_ARRAYSIZE(chars::silentShapes));
                    UI_COMBO("Aiming Mode", &ints.silentSelected, chars::silentTypes, IM_ARRAYSIZE(chars::silentTypes));
                    if (ints.silentSelected == 0) {
                        UI_COMBO("Target Bone", &ints.selectedBone, chars::silentSelectedBone, IM_ARRAYSIZE(chars::silentSelectedBone));
                    } else {
                        UI_SLIDERINT("Head Hit Chance", &ints.headHitChance, 0, 100);
                        UI_SLIDERINT("Neck Hit Chance", &ints.neckHitChance, 0, 100);
                        UI_SLIDERINT("Hips Hit Chance", &ints.hipHitChance, 0, 100);
                    }
                }
            }
        } break;
        case 2: {
            if (UI_HEADER("ESP")) {
                UI_CHECKBOX("Activate ESP", &bools.ESP);
                if (bools.ESP) {
                    UI_CHECKBOX("ESP Box", &bools.BoxESP);
                    UI_CHECKBOX("ESP Health", &bools.HealthESP);
                    UI_CHECKBOX("ESP Armor", &bools.ArmorESP);
                    UI_CHECKBOX("ESP Distance", &bools.DistanceESP);
                    UI_CHECKBOX("ESP Line", &bools.TracerESP);
                    if (bools.TracerESP) UI_COMBO("Line Position", &ints.line_position, chars::line_position, IM_ARRAYSIZE(chars::line_position));
                }
            }
        } break;
        case 3: {
        
        } break;
        case 4: {
            if (UI_HEADER("Menu")) {
                UI_CHECKBOX("Snow", &bools.snowflakes);
                UI_SLIDERINT("Background Transparency", &ints.backgroundTransparency, 0, 255);
                UI_CHECKBOX("Debug Menu", &DebugMenu::showDebugMenu);
            }
        } break;
    }
}