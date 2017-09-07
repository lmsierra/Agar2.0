
#ifndef __ENTITY_INFORMATION_H__
#define __ENTITY_INFORMATION_H__

#include "CustomTypes.h"
#include <array>
#include "GameConfig.h"

struct EntityInfo {
    double x, y;
    int id;
    EntityInfo()                              : id(-1), x(0), y(0) {}
    EntityInfo(int _id, double _x, double _y) : id(_id), x(_x), y(_y) {}
};

struct PlayerInfo : public EntityInfo {

    unsigned int weight;
    float speed;
    PlayerInfo()                                                : EntityInfo(-1, 0, 0),    weight(0),  speed(0) {}
    PlayerInfo(int _id, double _x, double _y, int _w, float _s) : EntityInfo(_id, _x, _y), weight(_w), speed(_s) {}
};


struct InitMessageInfo {

    uint32 player_id;
    double player_x;
    double player_y;
    float player_speed;
    uint32 player_weight;
    double world_height;
    double world_width;

    InitMessageInfo() {
       player_id     = 0;
       player_x      = 0;
       player_y      = 0;
       player_weight = 0;
       player_speed = 0;
       world_height  = 0;
       world_width   = 0;
    }
};


struct MovePlayerInfo {

    double x, y;
    uint32 id;

    MovePlayerInfo() : id(0), x(0), y(0) {}
};


struct PlayerJoinInfo {
    uint32 id;
    double x, y;

    PlayerJoinInfo() : id(0), x(0), y(0) {}
};


struct PlayerEatenInfo {
    uint32 eaten_id;
    uint32 id;
    uint32 new_weight;

    PlayerEatenInfo() : eaten_id(), id(), new_weight() {}
};

struct SnapshotInfo {
    std::array<PlayerInfo, MAX_PLAYERS> player_info;
    std::array<EntityInfo, MAX_FOOD>    food_info;
    int num_players;
    int num_food;

    SnapshotInfo() {}
};

struct FoodEatenInfo {
    uint32 food_id;
    uint32 player_id;
    uint32 new_weight;

    FoodEatenInfo() : food_id(0), player_id(0), new_weight(0) {}
};


struct DeletePlayerInfo {
    uint32 id;

    DeletePlayerInfo() : id(0) {}
};

#endif /* __ENTITY_INFORMATION_H__ */