void *BipedMap$$Head(void *_this) {
    if (!_this) return nullptr;
    auto biped = PlayerController$$get_CharacterBiped(_this);
    if (!biped) return nullptr;
    return *(void **)((uint64_t)biped + il2cpp_get_field_offset(oxorany("Assembly-CSharp.dll"), oxorany("Axlebolt.Standoff.Player"), oxorany("BipedMap"), oxorany("Head")));
}

void *BipedMap$$Neck(void *_this) {
    if (!_this) return nullptr;
    auto biped = PlayerController$$get_CharacterBiped(_this);
    if (!biped) return nullptr;
    return *(void **)((uint64_t)biped + il2cpp_get_field_offset(oxorany("Assembly-CSharp.dll"), oxorany("Axlebolt.Standoff.Player"), oxorany("BipedMap"), oxorany("Neck")));
}

void *BipedMap$$Hip(void *_this) {
    if (!_this) return nullptr;
    auto biped = PlayerController$$get_CharacterBiped(_this);
    if (!biped) return nullptr;
    return *(void **)((uint64_t)biped + il2cpp_get_field_offset(oxorany("Assembly-CSharp.dll"), oxorany("Axlebolt.Standoff.Player"), oxorany("BipedMap"), oxorany("Hip")));
}

bool isLocal(void *_this) {
  if (!_this) return false;
  return *(bool *)((uint64_t)_this + oxorany(0x28));
}