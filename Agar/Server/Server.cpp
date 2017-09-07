#include "stdafx.h"
#include "ServerENet.h"
#include <Windows.h>
#include "Entity.h"
#include "Player.h"
#include "NetMessages.h"
#include "Math.h"
#include <time.h>
#include "GameConfig.h"

using namespace ENet;

void    Init();
void    Reset();
void    MovePlayer(uint32 id, double x, double y);
void    SendInitMessage(Player* player, CPeerENet* peer, int channel);
void    SendPlayerJoinMessage(Player* player, int channel);
void    SendEatenMessage(Player* eaten, Player* other);
void    SendFoodEatenMessage(Entity* food, Player* player);
void    SendDeletePlayerMessage(uint32 id);
void    SendSnapshot(CPeerENet* peer = nullptr);
void    ReplenishFood();

Player* CreatePlayer();
Entity* CreateEntity();

std::vector<Entity*> foodArray   = std::vector<Entity*>();
std::vector<Player*> playerArray = std::vector<Player*>();
CServerENet* pServer;

double playerId = 0;
double foodId   = 0;
float lastTime;

bool shouldExit  = false;
bool shouldClose = false;

BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType)
{
    if (dwCtrlType == CTRL_CLOSE_EVENT)
    {
        shouldExit = true;
        while (!shouldClose)
            Sleep(100);
        return TRUE;
    }

    return FALSE;
}

int _tmain(int argc, _TCHAR* argv[])
{
    srand(time(NULL));
    lastTime = clock();

    SetConsoleCtrlHandler(ConsoleHandlerRoutine, TRUE);

    pServer = new CServerENet();

    if (pServer->Init(1234, 5))
    {
        Init();

        float deltaTime;

        while (!shouldExit)
        {

            std::vector<CPacketENet*>  incommingPackets;
            pServer->Service(incommingPackets, 0);

            for (CPacketENet* packet : incommingPackets)
            {

                if (packet->GetType() == EPacketType::CONNECT)
                {
                    if (playerArray.size() == MAX_PLAYERS) {
                        pServer->Disconnect(packet->GetPeer());
                    } else {
                        printf("Conectando un jugador\n");
                        Player* player = CreatePlayer();
                        player->SetPeer(packet->GetPeer());
                        SendInitMessage(player, packet->GetPeer(), packet->GetChannel());
                        SendSnapshot(packet->GetPeer());
                        SendPlayerJoinMessage(player, packet->GetChannel());
                    }
                }
                else if (packet->GetType() == EPacketType::DISCONNECT)
                {
                    printf("Desconectado un jugador\n");

                    for (int i = 0; i < playerArray.size(); i++) {
                        if (playerArray[i]->GetPeer() == packet->GetPeer()) {

                            Player* p = playerArray[i];
                            uint32 id = p->GetId();
                            playerArray.erase(playerArray.begin() + i);
                            delete p;

                            SendDeletePlayerMessage(id);
                            break;
                        }
                    }
                }
                else if (packet->GetType() == EPacketType::DATA) {
                    
                    char* buffer = (char*) packet->GetData();
                    NetMessage m;
                    m.deserialize(buffer);

                    switch (m.type) {
                        case MESSAGE_MOVEMENT:
                        {
                            MovePlayerMessage mpm;
                            mpm.deserialize(buffer);
                            MovePlayer(mpm.data.id, mpm.data.x, mpm.data.y);
                        }
                        break;
                    }
                }
            }

            deltaTime = (float(clock()) - lastTime) / 1000;
            lastTime = clock();

            // Update every player in game
            for (Player* p : playerArray) {
                p->Update(deltaTime);
            }

            // Check Collisions
            for (int i = playerArray.size() - 1; i >= 0; i--) {

                bool deleted = false;
                double x1    = playerArray[i]->GetX();
                double y1    = playerArray[i]->GetY();
                double r1    = playerArray[i]->GetWeight();

                for (int j = 0; j < playerArray.size(); j++) {
                    

                    double x2 = playerArray[j]->GetX();
                    double y2 = playerArray[j]->GetY();
                    double r2 = playerArray[j]->GetWeight();

                    if (SquareDistance(x1, y1, x2, y2) < (r1 + r2) * (r1 + r2)) {
                        // Hay collision
                        if (r1 < r2) {
                            // El peso de i es menor que el de j, ergo se lo come
                            Player* p = playerArray[i];
                            playerArray[j]->AddWeight(p->GetWeight());
                            SendEatenMessage(p, playerArray[j]);
                            playerArray.erase(playerArray.begin() + i);
                            delete p;
                            deleted = true;
                        }
                    }
                }
                
                bool feed = false;
                for (int j = foodArray.size() - 1; j >= 0; j--) {

                    double x2 = foodArray[j]->GetX();
                    double y2 = foodArray[j]->GetY();
                    double r2 = foodArray[j]->GetWeight();

                    if (SquareDistance(x1, y1, x2, y2) < (r1 + r2)* (r1 + r2)) {

                        feed = true;
                        playerArray[i]->AddWeight(foodArray[j]->GetWeight());
                        SendFoodEatenMessage(foodArray[j], playerArray[i]);

                        Entity* e = foodArray[j];
                        foodArray.erase(foodArray.begin() + j);
                        delete e;
                    }
                }

                if (feed) {
                    ReplenishFood();
                }
            }

            if(playerArray.size() > 0)
                SendSnapshot();

            Sleep(50);
        }

        for (Player* p : playerArray) {
            pServer->Disconnect(p->GetPeer());
        }

        Reset();
        shouldClose = true;
    }
    else
    {
        fprintf(stdout, "Server could not be initialized.\n");
    }

    return 0;
}

void Init() {

    for (int i = 0; i < MAX_FOOD; i++) {
        CreateEntity();
    }
}

void Reset() {

    for (Player* p : playerArray)
        delete p;

    playerArray.clear();

    for (Entity* e : foodArray)
        delete e;

    foodArray.clear();
}


Player* CreatePlayer() {

    Player* player = new Player(rand() % MAP_WIDTH, rand() % MAP_HEIGHT);
    player->SetId(playerId);
    playerArray.push_back(player);
    ++playerId;

    return player;
}

Entity* CreateEntity() {
    Entity* entity = new Entity(rand() % MAP_WIDTH, rand() % MAP_HEIGHT);
    entity->SetId(foodId);
    foodArray.push_back(entity);
    ++foodId;

    return entity;
}


void MovePlayer(uint32 id, double x, double y) {
    for(Player* p : playerArray) {
        if (p->GetId() == id) {

            if (x < 0)
                x = 0;
            else if (x > MAP_WIDTH)
                x = MAP_WIDTH;
            if (y < 0)
                y = 0;
            else if (y > MAP_HEIGHT)
                y = MAP_HEIGHT;

            p->MoveTo(x, y);
        }
    }
}


void SendPlayerJoinMessage(Player* player, int channel) {

    char* buffer = (char*)malloc(32);

    PlayerJoinInfo joinData;
    joinData.id = player->GetId();
    joinData.x = player->GetX();
    joinData.y = player->GetY();

    PlayerJoinMessage joinMsg = PlayerJoinMessage(joinData);
    int written = joinMsg.serialize(buffer);
    pServer->SendAll(buffer, written, channel, true);

    free(buffer);
}

void SendInitMessage(Player* player, CPeerENet* peer, int channel) {
    char* buffer = (char*) malloc(56);

    InitMessageInfo data;
    data.player_id     = player->GetId();
    data.player_weight = player->GetWeight();
    data.player_x      = player->GetX();
    data.player_y      = player->GetY();
    data.player_speed  = player->GetSpeed();
    data.world_width   = MAP_WIDTH;
    data.world_height  = MAP_HEIGHT;

    InitMessage m = InitMessage(data);
    int written = m.serialize(buffer);

    pServer->SendData(peer, buffer, written, channel, true);

    free(buffer);
}


void SendEatenMessage(Player* eaten, Player* other) {
    char* buffer = (char*)malloc(32);

    PlayerEatenInfo data;
    data.eaten_id   = eaten->GetId();
    data.id         = other->GetId();
    data.new_weight = other->GetWeight();

    PlayerEatenMessage m = PlayerEatenMessage(data);
    int written = m.serialize(buffer);

    pServer->SendAll(buffer, written, 0, true);

    free(buffer);
}


void SendSnapshot(CPeerENet* peer) {

    std::vector<PlayerInfo> piArray = std::vector<PlayerInfo>();
    std::vector<EntityInfo> eiArray = std::vector<EntityInfo>();
    
    for (Player* p : playerArray) {
        PlayerInfo pi;
        pi.id     = p->GetId();
        pi.x      = p->GetX();
        pi.y      = p->GetY();
        pi.weight = p->GetWeight();
        pi.speed  = p->GetSpeed();

        piArray.push_back(pi);
    }

    for (Entity* e : foodArray) {
        EntityInfo ei;
        ei.id = e->GetId();
        ei.x  = e->GetX();
        ei.y  = e->GetY();

        eiArray.push_back(ei);
    }

    SnapshotInfo data;
    std::copy(piArray.begin(), piArray.end(), data.player_info.begin());
    std::copy(eiArray.begin(), eiArray.end(), data.food_info.begin());

    data.num_players = playerArray.size();
    data.num_food    = foodArray.size();

    SnapshotMessage m = SnapshotMessage(data);
    char* buffer = (char*)malloc(1600);
    int written = m.serialize(buffer);

    if (peer)
        pServer->SendData(peer, buffer, written, 0, true);
    else
        pServer->SendAll(buffer, written, 0, false);

    free(buffer);
}

void SendFoodEatenMessage(Entity* food, Player* player) {

    FoodEatenInfo data;
    data.food_id    = food->GetId();
    data.player_id  = player->GetId();
    data.new_weight = player->GetWeight();

    char* buffer = (char*) malloc(32);

    FoodEatenMessage m = FoodEatenMessage(data);
    int written     = m.serialize(buffer);

    pServer->SendAll(buffer, written, 0, true);
    free(buffer);
}


void ReplenishFood() {
   
    for (int i = foodArray.size(); i < MAX_FOOD; i++) {
        CreateEntity();
    }

}

void SendDeletePlayerMessage(uint32 id) {

    DeletePlayerInfo data;
    data.id = id;

    DeletePlayerMessage m = DeletePlayerMessage(data);
    char* buffer = (char*)malloc(12);
    int written = m.serialize(buffer);

    pServer->SendAll(buffer, written, 0, true);
    free(buffer);
}