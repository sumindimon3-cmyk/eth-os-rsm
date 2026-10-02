std::vector<void *> players;

void *localPlayer = nullptr;
void *enemyPlayer = nullptr;
void *aimedPlayer = nullptr;

bool players$$find(void *player) {
  return player &&
         std::find(players.begin(), players.end(), player) != players.end();
}

void players$$clear() {
  if (!localPlayer)
    return;

  const auto localPhoton = PhotonPlayer$$get_Player(localPlayer);
  if (!localPhoton)
    return;

  players.erase(std::remove_if(players.begin(), players.end(),
                               [&](void *p) {
                                 if (!p)
                                   return true;
                                 auto photon = PhotonPlayer$$get_Player(p);
                                 if (!photon)
                                   return true;
                                 return GetTeam(photon) == GetTeam(localPhoton);
                               }),
                players.end());
}

inline bool isPlayerAlive(void *photonPlayer) {
  return (photonPlayer != nullptr && PhotonPlayer$$get_Player(photonPlayer) &&
          GetHealth(PhotonPlayer$$get_Player(photonPlayer)) > 0);
}

void (*original$$PlayerController$$Update)(void *player);
void PlayerController$$Update(void *player) {
  if (player) {
    if (isPlayerAlive(player)) {

      if (void *playerPhoton = PhotonPlayer$$get_Player(player)) {
        if (!playerPhoton) return;

        if (isLocal(playerPhoton)) {
          localPlayer = player;
        }
        
        if (GetHealth(playerPhoton) <= 0)
          return;

        if (!localPlayer)
          return;
        void *localPhoton = PhotonPlayer$$get_Player(localPlayer);
        if (!localPhoton)
          return;

        if (GetTeam(playerPhoton) != GetTeam(localPhoton)) {

          if (!players$$find(player)) {
            players.push_back(player);
          }

          enemyPlayer = player;
        }
      }
    }
    players.erase(std::remove_if(players.begin(), players.end(),
                                 [](void *p) { return !isPlayerAlive(p); }),
                  players.end());
				  
  }

  original$$PlayerController$$Update(player);
}