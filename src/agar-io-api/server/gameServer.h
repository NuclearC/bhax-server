//imports (duh)
#include "playerTracker.h"

class GameServer {
    //logging
    Logger gameServerLog;

    //Startup
    bool run         = true;
    int lastNodeId   = 1;
    int lastPlayerId = 1;
    playerTracker clients[0]; //Unsure if this is right
    int socketCount  = 0;


    int currentFood  = 0; //probs wont be used for the bots gamemode


    std::time_t startTime = std::time(0); //server start time
    int stopDateTime = 0;
    int updateTime   = 0;
    int updateTimeAvg= 0;

    int tickCounter  = 0;
public:
    void start();
};

void GameServer::start () {
    gameServerLog.set_name("GameServer");
    gameServerLog.log(4, "Starting gameserver");
}