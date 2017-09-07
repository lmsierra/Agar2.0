#include "stdafx.h"
#include "ClientENet.h"
#include <Windows.h>
#include "EngineInclude.h"
#include <glfw3.h>
#include "Math.h"
#include <vector>
#include "NetMessages.h"
#include <time.h>

using namespace ENet;

void Reset();
void MovePlayer(double x, double y);
void Disconnect();

// Array con las bolitas en el juego
std::vector<Entity*> foodArray;
// Array con los jugadores externos
std::vector<Player*> playersArray;

// Player
Player* player;

CClienteENet* pClient;
CPeerENet* pPeer;

double mapWidth, mapHeight;

int _tmain(int argc, _TCHAR* argv[])
{
    srand(time(NULL));

    Screen::Instance().Open(800, 600, false);

    const Renderer renderer = Renderer::Instance();
    
    Scene* scene = new Scene();

    Camera& camera = scene->GetCamera();

    pClient = new CClienteENet();
    pClient->Init();

    pPeer = pClient->Connect("127.0.0.1", 1234, 2);

    while (Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESCAPE)) {
        glfwPollEvents();

        std::vector<CPacketENet*>  incommingPackets;
        pClient->Service(incommingPackets, 0);

        for (CPacketENet* packet : incommingPackets) {
            
            if (packet->GetType() == EPacketType::DISCONNECT) {
            
                Reset();
                return 0;
                    
            }else if (packet->GetType() == EPacketType::DATA) {
                
                char* buffer = (char*) packet->GetData();
                NetMessage m;
                m.deserialize(buffer);

                switch (m.type) {
                    case NetMessageType::MESSAGE_INIT:
                    {
                        if (!player) {
                     
                            InitMessage initMessage;
                            initMessage.deserialize(buffer);


                            player = scene->CreatePlayer();
                            player->SetId(initMessage.data.player_id);
                            player->SetX(initMessage.data.player_x);
                            player->SetY(initMessage.data.player_y);
                            player->SetSpeed(initMessage.data.player_speed);
                            player->SetWeight(initMessage.data.player_weight);

                            mapWidth  = initMessage.data.world_width;
                            mapHeight = initMessage.data.world_height;

                            camera.SetBounds(0, initMessage.data.world_width, 0, initMessage.data.world_height);
                            camera.FollowEntity(player);
                        }
                    }
                    break;
                    case NetMessageType::MESSAGE_PLAYER_JOIN:
                    {
                        if (player) {
                            
                            PlayerJoinMessage joinMessage;
                            joinMessage.deserialize(buffer);

                            PlayerJoinInfo data = joinMessage.data;

                            if (player->GetId() != data.id) {
                                Player* p = scene->CreatePlayer();
                                p->SetId(data.id);
                                p->SetX(data.x);
                                p->SetY(data.y);
                            }
                        }
                    }
                    break;
                    case NetMessageType::MESSAGE_EATEN:
                    {
                        if (player) {
                            
                            PlayerEatenMessage eatenMessage;
                            eatenMessage.deserialize(buffer);
                            PlayerEatenInfo data = eatenMessage.data;

                            if (player->GetId() == data.eaten_id) {
                                // Muerto.
                                Disconnect();
                                return 0;
                            }
                            else {
                                if (player->GetId() == data.id) {
                                    // Hemos comido al otro jugador, añadimos el peso.
                                    player->SetWeight(data.new_weight);
                                } 

                                // Otro ha muerto, borrar de la escena.
                                int pos = scene->DeletePlayer(data.eaten_id);
                                if(pos >= 0)
                                    playersArray.erase(playersArray.begin() + pos - 1);
                            }
                        }
                    }
                    break;

                    case NetMessageType::MESSAGE_SNAPSHOT:
                    {
                        SnapshotMessage snapshot;
                        snapshot.deserialize(buffer);
                        SnapshotInfo data = snapshot.data;
                       
                        for (int i = 0; i < data.num_players; i++) {
                            PlayerInfo p = data.player_info[i];
                            if (p.id == player->GetId()) {
                                player->SetWeight(p.weight);
                                player->SetSpeed(p.speed);
                                player->SetX(p.x);
                                player->SetY(p.y);
                            }
                            else {
                                bool found = false;
                                for (Player* pl : playersArray) {
                                    if (pl->GetId() == p.id) {
                                        pl->SetWeight(p.weight);
                                        pl->SetX(p.x);
                                        pl->SetY(p.y);
                                        found = true;
                                        break;
                                    }
                                }
                                if (!found) {
                                    Player* pl = scene->CreatePlayer();
                                    pl->SetWeight(p.weight);
                                    pl->SetX(p.x);
                                    pl->SetY(p.y);
                                    pl->SetId(p.id);
                                    playersArray.push_back(pl);
                                }
                            }
                        }

                        for (int i = 0; i < data.num_food; i++) {
                            EntityInfo e = data.food_info[i];
                            bool found = false;
                            for (Entity* en : foodArray) {
                                if (e.id == en->GetId()) {
                                    en->SetX(e.x);
                                    en->SetY(e.y);
                                    found = true;
                                }
                            }
                            if (!found) {
                                Entity* en = scene->CreateFood();
                                en->SetId(e.id);
                                en->SetX(e.x);
                                en->SetY(e.y);
                                foodArray.push_back(en);
                            }
                        }
                    }
                    break;

                    case NetMessageType::MESSAGE_FOOD_EATEN:
                    {
                        FoodEatenMessage message;
                        message.deserialize(buffer);
                        FoodEatenInfo data = message.data;

                        int pos = scene->DeleteFood(data.food_id);
                        if(pos >= 0)
                             foodArray.erase(foodArray.begin() + pos);

                        if (player->GetId() == data.player_id) {
                            player->SetWeight(data.new_weight);
                        }
                        else {
                            for (Player* p : playersArray) {
                                if(p->GetId() == data.player_id) {
                                    p->SetWeight(data.new_weight);
                                    break;
                                }
                            }
                        }
                    }
                    break;
                    case MESSAGE_DELETE_PLAYER:
                    {
                        DeletePlayerMessage message;
                        message.deserialize(buffer);
                        DeletePlayerInfo data = message.data;
                        int pos               = scene->DeletePlayer(data.id);
                        if (pos)
                            playersArray.erase(playersArray.begin() + pos - 1);
                    }
                    break;
                    default:
                    break;
                }

                free(buffer);
            }
        }

        double deltaTime = Screen::Instance().DeltaTime();

        renderer.Instance().Clear(0, 255, 255);

        if (player)
        {
            double x = Screen::Instance().GetMouseX() + camera.GetX();
            double y = Screen::Instance().GetMouseY() + camera.GetY();

            if (x < 0)
                x = 0;
            else if (x > mapWidth)
                x = mapWidth;

            if (y < 0)
                y = 0;
            else if (y > mapHeight)
                y = mapHeight;

            MovePlayer(x, y);
        }

        scene->Update(deltaTime);
        scene->Render();

        Screen::Instance().Refresh();
    }

    Disconnect();

    return 0;
}

void Reset()
{
    for (Player* p : playersArray)
    {
        delete p;
    }
    playersArray.clear();

    for (Entity* e : foodArray)
    {
        delete e;
    }
    foodArray.clear();

    if (player)
        delete player;
}


void MovePlayer(double x, double y)
{ 
    if (player)
    {
        player->MoveTo(x, y);
        MovePlayerInfo data;
        data.id = player->GetId();
        data.x  = x;
        data.y  = y;

        MovePlayerMessage m = MovePlayerMessage(data);
        char* buffer = (char*)malloc(32);
        int written = m.serialize(buffer);

        pClient->SendData(pPeer, buffer, written, 0, true);
        free(buffer);
    }
}


void Disconnect() {
    pClient->Disconnect(pPeer);
    Reset();
}
