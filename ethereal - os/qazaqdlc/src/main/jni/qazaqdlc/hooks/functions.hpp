void *(*Camera$$get_main)();
Vector3 (*Camera$$WorldToScreenPoint)(void *_this, Vector3 value);
void *(*Component$$get_transform)(void *_this);
Vector3 (*Transform$$get_position)(void *_this);
void (*Transform$$set_position)(void *_this, Vector3 value);
Vector3 (*Transform$$get_forward)(void *_this);
void (*Transform$$set_localScale)(void *_this, Vector3 value);
bool (*Physics$$Linecast)(Vector3 start, Vector3 end, int layerMask);

void *(*PlayerController$$get_CharacterBiped)(void *_this);

void *(*PhotonPlayer$$get_Player)(void *_this); //playercontroller -> get_player()

int (*GetTeam)(void *_this); //photonplayergameextension -> getteam()
int (*GetHealth)(void *_this); //photonplayerextensions -> gethealth()
int (*GetArmor)(void *_this); //photonplayerextensions -> getarmor()

il2cppString *(*PhotonPlayer$$get_NickName)(void *_this);

void (*openURL)(il2cppString *url);