void installHooks() {
    try {
        void *Camera$$get_main$$offset = il2cpp_get_method_offset(oxorany("UnityEngine.dll"), oxorany("UnityEngine"), oxorany("Camera"), oxorany("get_main"), 0);
        if (Camera$$get_main$$offset) {
            Camera$$get_main = (void *(*)())Camera$$get_main$$offset;
            DebugMenu::AddLog(oxorany("Camera::get_main method found"));
        } else DebugMenu::AddLog(oxorany("Camera::get_main method not found!"), 2);

        void *Camera$$WorldToScreenPoint$$offset = il2cpp_get_method_offset(oxorany("UnityEngine.dll"), oxorany("UnityEngine"), oxorany("Camera"), oxorany("WorldToScreenPoint"), 1);
        if (Camera$$WorldToScreenPoint$$offset) {
            Camera$$WorldToScreenPoint = (Vector3(*)(void *, Vector3))Camera$$WorldToScreenPoint$$offset;
            DebugMenu::AddLog(oxorany("Camera::WorldToScreenPoint method found"));
        } else DebugMenu::AddLog(oxorany("Camera::WorldToScreenPoint method not found!"), 2);

        void *Component$$get_transform$$offset = il2cpp_get_method_offset(oxorany("UnityEngine.dll"), oxorany("UnityEngine"), oxorany("Component"), oxorany("get_transform"), 0);
        if (Component$$get_transform$$offset) {
            Component$$get_transform = (void *(*)(void *))Component$$get_transform$$offset;
            DebugMenu::AddLog(oxorany("Component::get_transform method found"));
        } else DebugMenu::AddLog(oxorany("Component::get_transform method not found!"), 2);

        void *Transform$$get_position$$offset = il2cpp_get_method_offset(oxorany("UnityEngine.dll"), oxorany("UnityEngine"), oxorany("Transform"), oxorany("get_position"), 0);
        if (Transform$$get_position$$offset) {
            Transform$$get_position = (Vector3(*)(void *))Transform$$get_position$$offset;
            DebugMenu::AddLog(oxorany("Transform::get_position method found"));
        } else DebugMenu::AddLog(oxorany("Transform::get_position method not found!"), 2);

        void *Transform$$set_position$$offset = il2cpp_get_method_offset(oxorany("UnityEngine.dll"), oxorany("UnityEngine"), oxorany("Transform"), oxorany("set_position"), 1);
        if (Transform$$set_position$$offset) {
            Transform$$set_position = (void (*)(void *, Vector3))Transform$$set_position$$offset;
            DebugMenu::AddLog(oxorany("Transform::set_position method found"));
        } else DebugMenu::AddLog(oxorany("Transform::set_position method not found!"), 2);

        void *Transform$$get_forward$$offset = il2cpp_get_method_offset(oxorany("UnityEngine.dll"), oxorany("UnityEngine"), oxorany("Transform"), oxorany("get_forward"), 0);
        if (Transform$$get_forward$$offset) {
            Transform$$get_forward = (Vector3(*)(void *))Transform$$get_forward$$offset;
            DebugMenu::AddLog(oxorany("Transform::get_forward method found"));
        } else DebugMenu::AddLog(oxorany("Transform::get_forward method not found!"), 2);

        void *Transform$$set_localScale$$offset = il2cpp_get_method_offset(oxorany("UnityEngine.dll"), oxorany("UnityEngine"), oxorany("Transform"), oxorany("set_localScale"), 1);
        if (Transform$$set_localScale$$offset) {
            Transform$$set_localScale = (void (*)(void *, Vector3))Transform$$set_localScale$$offset;
            DebugMenu::AddLog(oxorany("Transform::set_localScale method found"));
        } else DebugMenu::AddLog(oxorany("Transform::set_localScale method not found!"), 2);

        void *Physics$$Linecast$$offset = il2cpp_get_method_offset(oxorany("UnityEngine.PhysicsModule.dll"), oxorany("UnityEngine"), oxorany("Physics"), oxorany("Linecast"), 3);
        if (Physics$$Linecast$$offset) {
            Physics$$Linecast = (bool (*)(Vector3, Vector3, int))Physics$$Linecast$$offset;
            DebugMenu::AddLog(oxorany("Physics::Linecast method found"));
        } else DebugMenu::AddLog(oxorany("Physics::Linecast method not found!"), 2);

        void *PlayerController$$get_CharacterBiped$$offset = il2cpp_get_method_offset(oxorany("Assembly-CSharp.dll"), oxorany("Axlebolt.Standoff.Player"), oxorany("PlayerController"), oxorany("get_CharacterBiped"), 0);
        if (PlayerController$$get_CharacterBiped$$offset) {
            PlayerController$$get_CharacterBiped = (void *(*)(void *))PlayerController$$get_CharacterBiped$$offset;
            DebugMenu::AddLog(oxorany("PlayerController::get_CharacterBiped method found"));
        } else DebugMenu::AddLog(oxorany("PlayerController::get_CharacterBiped method not found!"), 2);

        void *PhotonPlayer$$get_Player$$offset = il2cpp_get_method_offset(oxorany("Assembly-CSharp.dll"), oxorany("Axlebolt.Standoff.Player"), oxorany("PlayerController"), oxorany("get_Player"), 0);
        if (PhotonPlayer$$get_Player$$offset) {
            PhotonPlayer$$get_Player = (void *(*)(void *))PhotonPlayer$$get_Player$$offset;
            DebugMenu::AddLog(oxorany("PlayerController::get_Player method found"));
        } else DebugMenu::AddLog(oxorany("PlayerController::get_Player method not found!"), 2);

        void *GetTeam$$offset = il2cpp_get_method_offset(oxorany("Assembly-CSharp.dll"), oxorany(""), oxorany("DJKLKEANGFB"), oxorany("BGGFGOEMHHN"), 1);
        if (GetTeam$$offset) {
            GetTeam = (int (*)(void *))GetTeam$$offset;
            DebugMenu::AddLog(oxorany("PhotonPlayerGameExtension::GetTeam method found"));
        } else DebugMenu::AddLog(oxorany("PhotonPlayerGameExtension::GetTeam method not found!"), 2);

        void *GetHealth$$offset = il2cpp_get_method_offset(oxorany("Assembly-CSharp.dll"), oxorany(""), oxorany("HGAPMOIDLHN"), oxorany("NEJKLFFCGDL"), 1);
        if (GetHealth$$offset) {
            GetHealth = (int (*)(void *))GetHealth$$offset;
            DebugMenu::AddLog(oxorany("PhotonPlayerExtensions::GetHealth method found"));
        } else DebugMenu::AddLog(oxorany("PhotonPlayerExtensions::GetHealth method not found!"), 2);

        void *GetArmor$$offset = il2cpp_get_method_offset(oxorany("Assembly-CSharp.dll"), oxorany(""), oxorany("HGAPMOIDLHN"), oxorany("HEFFPMGLIGG"), 1);
        if (GetArmor$$offset) {
            GetArmor = (int (*)(void *))GetArmor$$offset;
            DebugMenu::AddLog(oxorany("PhotonPlayerExtensions::GetArmor method found"));
        } else DebugMenu::AddLog(oxorany("PhotonPlayerExtensions::GetArmor method not found!"), 2);

        void *PhotonPlayer$$get_NickName$$offset = il2cpp_get_method_offset(oxorany("Assembly-CSharp.dll"), oxorany(""), oxorany("PhotonPlayer"), oxorany("get_NickName"), 0);
        if (PhotonPlayer$$get_NickName$$offset) {
            PhotonPlayer$$get_NickName = (il2cppString * (*)(void *)) PhotonPlayer$$get_NickName$$offset;
            DebugMenu::AddLog(oxorany("PhotonPlayer::get_NickName method found"));
        } else DebugMenu::AddLog(oxorany("PhotonPlayer::get_NickName method not found!"), 2);

        void *openURL$$offset = il2cpp_resolve_icall(oxorany("UnityEngine.Application::OpenURL"));
        if (openURL$$offset) {
            openURL = (void (*)(il2cppString *))openURL$$offset;
        }

        void *HitCaster_CastHit_offset = il2cpp_get_method_offset(oxorany("Assembly-CSharp.dll"), oxorany(""), oxorany("CACKIIGNALL"), oxorany("KHIEKOEMLKG"), 3);
        if (HitCaster_CastHit_offset) {
            a64h((void *)HitCaster_CastHit_offset, (void *)HitCaster$$CastHit, (void **)&original$$HitCaster$$CastHit);
            DebugMenu::AddLog(oxorany("HitCaster::CastHit method found"));
        } else DebugMenu::AddLog(oxorany("HitCaster::CastHit method not found!"), 2);

        void *PlayerController_Update_offset = il2cpp_get_method_offset(oxorany("Assembly-CSharp.dll"), oxorany("Axlebolt.Standoff.Player"), oxorany("PlayerController"), oxorany("Update"), 0);
        if (PlayerController_Update_offset) {
            a64h((void *)PlayerController_Update_offset, (void *)PlayerController$$Update, (void **)&original$$PlayerController$$Update);
            DebugMenu::AddLog(oxorany("PlayerController::Update method found"));
        } else DebugMenu::AddLog(oxorany("PlayerController::Update method not found!"), 2);

        void *Input_get_touchCount_offset = il2cpp_get_method_offset(oxorany("UnityEngine.dll"), oxorany("UnityEngine"), oxorany("Input"), oxorany("get_touchCount"), 0);
        if (Input_get_touchCount_offset) {
            a64h((void *)Input_get_touchCount_offset, (void *)get_touchCount, (void **)&original$$get_touchCount);
            DebugMenu::AddLog(oxorany("Input::get_touchCount method found"));
        } else DebugMenu::AddLog(oxorany("Input::get_touchCount method not found!"), 2);

        DebugMenu::AddLog(oxorany("job finished"), 1);
    } catch (...) {
        DebugMenu::AddLog(oxorany("crashed in attempt to hook"), 2);
    }
}
