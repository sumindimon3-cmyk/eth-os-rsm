void* selectBoneByChance(void* player, int headChance, int neckChance, int hipChance) {
    int total = headChance + neckChance + hipChance;
    if (total <= 0) return BipedMap$$Head(player);
    int r = rand() % total;
    if (r < headChance) return BipedMap$$Head(player);
    if (r < headChance + neckChance) return BipedMap$$Neck(player);
    return BipedMap$$Hip(player);
}

inline Vector3 getBonePosition(void* player, int boneId) {
    if (!player) return {0,0,0};
    void* bone = nullptr;

    if (ints.silentSelected == 0) {
        switch (boneId) {
            case 0: bone = BipedMap$$Head(player); break;
            case 1: bone = BipedMap$$Neck(player); break;
            case 2: bone = BipedMap$$Hip(player);  break;
            default: bone = BipedMap$$Head(player); break;
        }
    } else {
        bone = selectBoneByChance(player, ints.headHitChance, ints.neckHitChance, ints.hipHitChance);
    }
    if (!bone) return {0,0,0};

    void* tr = Component$$get_transform(bone);
    if (!tr) return {0,0,0};

    return Transform$$get_position(tr);
}

inline bool IsVisible(Vector3 from, Vector3 to) {
  return true;
}

void *findBestTarget() {
  void *best = nullptr;
  float bestFov = 9999.0f;

  for (auto player : players) {
    if (!player || !isPlayerAlive(player))
      continue;
      
    auto cam = Camera$$get_main();
    if (!cam) continue;

    Vector3 bonePos = getBonePosition(player, ints.selectedBone);
    Vector3 screen = Camera$$WorldToScreenPoint(cam, bonePos);

    if (screen.z <= 0)
      continue;

    float dx = screen.x - (ints.glWidth / 2.0f);
    float dy = screen.y - (ints.glHeight / 2.0f);
    float dist = sqrtf(dx * dx + dy * dy);

    if (dist < bestFov && dist <= floats.silentAimFOV) {
      if (!bools.silentVisibleCheck ||
          IsVisible(Transform$$get_position(
                        Component$$get_transform(Camera$$get_main())),
                    bonePos)) {
        bestFov = dist;
        best = player;
      }
    }
  }

    return best;
}

void *(*original$$HitCaster$$CastHit)(Vector3 startPosition, Vector3 direction,
                                      void *parameters);
void *HitCaster$$CastHit(Vector3 startPosition, Vector3 direction,
                         void *parameters) {
  if (bools.silentAim && isPlayerAlive(localPlayer)) {
    void *target = findBestTarget();
    if (target) {
      Vector3 targetPos = getBonePosition(target, ints.selectedBone);
      if (targetPos != Vector3(0, 0, 0)) {
        direction = Vector3::Normalized(targetPos - startPosition);
      }
    }
  }
  return original$$HitCaster$$CastHit(startPosition, direction, parameters);
}