ImColor outlineColor = ImColor(255, 255, 255, 255);
ImColor innerColor = ImColor(0, 0, 0, 200);

void _ESP() {
  if (bools.ESP && !players.empty()) {

    ImDrawList *draw = ImGui::GetBackgroundDrawList();

    for (void *player : players) {
      if (!player)
        continue;

      if (!isPlayerAlive(player))
        continue;

      Vector3 pos = Transform$$get_position(Component$$get_transform(player));
      Vector3 screenLower = Camera$$WorldToScreenPoint(Camera$$get_main(), pos);
      Vector3 screenUpper = Camera$$WorldToScreenPoint(
          Camera$$get_main(), pos + Vector3(0, 1.9f, 0));

      if (screenUpper.z <= 1.0f)
        continue;

      int height = screenUpper.y - screenLower.y;
      int width = height * 0.6f;

      ImVec2 topLeft(screenUpper.x - width / 2,
                     ints.glHeight - screenUpper.y);
      ImVec2 bottomRight(screenUpper.x + width / 2,
                         ints.glHeight - screenUpper.y + height);
      ImVec2 centerBottom(ints.glWidth / 2, ints.glHeight);
      ImVec2 foot(screenLower.x, ints.glHeight - screenLower.y);

      if (bools.TracerESP) {
        switch (ints.line_position) {
        case 0: {
          ImVec2 fromCenter(ints.glWidth / 2, 0);
          ImVec2 to(screenUpper.x, ints.glHeight - screenUpper.y);
          draw->AddLine(fromCenter, to, outlineColor, 2.5f);
          draw->AddLine(fromCenter, to, innerColor, 1.0f);
          break;
        }

        case 1: {
          ImVec2 fromMid(ints.glWidth / 2, ints.glHeight / 2);
          ImVec2 to(screenUpper.x, ints.glHeight - screenUpper.y);
          draw->AddLine(fromMid, to, outlineColor, 2.5f);
          draw->AddLine(fromMid, to, innerColor, 1.0f);
          break;
        }

        case 2: {
          ImVec2 fromBottom(ints.glWidth / 2, ints.glHeight);
          ImVec2 to(screenLower.x, ints.glHeight - screenLower.y);
          draw->AddLine(fromBottom, to, outlineColor, 2.5f);
          draw->AddLine(fromBottom, to, innerColor, 1.0f);
          break;
        }
        }
      }

      if (bools.BoxESP) {
        draw->AddRect(topLeft, bottomRight, innerColor, 2.0f, ImDrawFlags_None,
                      3.0f);
        draw->AddRect(topLeft, bottomRight, outlineColor, 2.0f,
                      ImDrawFlags_None, 1.5f);
      }

      if (bools.HealthESP) {
        int health = GetHealth(PhotonPlayer$$get_Player(player));
        if (health < 0)
          health = 0;
        if (health > 100)
          health = 100;

        float healthRatio = health / 100.0f;
        float barHeight = height * healthRatio;
        float barWidth = 1.75f * floats.dpiScale;

        ImVec2 barTopLeft(topLeft.x - barWidth -
                              3.0f * floats.dpiScale,
                          bottomRight.y - barHeight);
        ImVec2 barBottomRight(topLeft.x - 3.0f * floats.dpiScale,
                              bottomRight.y);

        draw->AddRectFilled(
            ImVec2(barTopLeft.x - 1.0f, barTopLeft.y - 1.0f),
            ImVec2(barBottomRight.x + 1.0f, barBottomRight.y + 1.0f),
            IM_COL32(0, 0, 0, 255));

        draw->AddRectFilled(barTopLeft, barBottomRight,
                            IM_COL32(255, 255, 255, 255));
      }

      if (bools.ArmorESP) {
        int armor = GetArmor(PhotonPlayer$$get_Player(player));
        if (armor < 0)
          armor = 0;
        if (armor > 100)
          armor = 100;

        float armorRatio = armor / 100.0f;
        float barHeight = height * armorRatio;
        float barWidth = 1.75f * floats.dpiScale;

        ImVec2 barTopLeft(bottomRight.x + 3.0f * floats.dpiScale,
                          bottomRight.y - barHeight);
        ImVec2 barBottomRight(bottomRight.x + barWidth +
                                  3.0f * floats.dpiScale,
                              bottomRight.y);

        draw->AddRectFilled(
            ImVec2(barTopLeft.x - 1.0f, barTopLeft.y - 1.0f),
            ImVec2(barBottomRight.x + 1.0f, barBottomRight.y + 1.0f),
            IM_COL32(0, 0, 0, 255));

        draw->AddRectFilled(barTopLeft, barBottomRight,
                            IM_COL32(255, 255, 255, 255));
      }

      if (bools.DistanceESP) {
        float dist =
            Vector3::Distance(Transform$$get_position(
                                  Component$$get_transform(Camera$$get_main())),
                              pos);
        char buffer[64];
        sprintf(buffer, oxorany("%.1fm"), dist);

        ImVec2 textSize = ImGui::CalcTextSize(buffer);
        ImVec2 textPos(screenLower.x - textSize.x / 2,
                       ints.glHeight - screenLower.y +
                           5);
        ImU32 black = IM_COL32(0, 0, 0, 255);

        draw->AddText(ImVec2(textPos.x - 1, textPos.y), black, buffer);
        draw->AddText(ImVec2(textPos.x + 1, textPos.y), black, buffer);
        draw->AddText(ImVec2(textPos.x, textPos.y - 1), black, buffer);
        draw->AddText(ImVec2(textPos.x, textPos.y + 1), black, buffer);

        draw->AddText(textPos, IM_COL32(255, 255, 255, 255), buffer);
        draw->AddText(textPos, IM_COL32(255, 255, 255, 255), buffer);
      }
    }
  }
}
