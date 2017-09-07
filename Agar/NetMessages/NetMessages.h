#ifndef __NET_MESSAGE_H__
#define __NET_MESSAGE_H__

#include <vector>
#include "EntityInformation.h"

enum NetMessageType {
    MESSAGE_SNAPSHOT,
    MESSAGE_MOVEMENT,
    MESSAGE_PLAYER_JOIN,
    MESSAGE_EATEN,
    MESSAGE_FOOD_EATEN,
    MESSAGE_INIT,
    MESSAGE_DELETE_PLAYER,
    MESSAGE_UNKNOWN
};


struct NetMessage
{
    NetMessageType type;

    virtual int serialize(char* outBuff) { 
        *reinterpret_cast< NetMessageType*>(outBuff) = type; 
        return sizeof(NetMessage); 
    }

    virtual void deserialize(char* inBuff) {
        type = *reinterpret_cast<NetMessageType*>(inBuff);
    }
};

struct SnapshotMessage : public NetMessage {
    
    SnapshotMessage() {
        type = MESSAGE_SNAPSHOT;
        data = SnapshotInfo();
    }

    SnapshotMessage(SnapshotInfo _data) {
        type = MESSAGE_SNAPSHOT;
        data = _data;
    }


    SnapshotInfo data;
    virtual int  serialize   (char* outBuff);
    virtual void deserialize (char* inBuff);
};


struct InitMessage : public NetMessage {

    InitMessage(InitMessageInfo info) {
        type = MESSAGE_INIT;
        data = info;
    }

    InitMessage() {
        type = MESSAGE_INIT;
        data = InitMessageInfo();
    }

    InitMessageInfo data;

    virtual int  serialize   (char* outBuff);
    virtual void deserialize (char* inBuff);
};

struct MovePlayerMessage : public NetMessage {

    MovePlayerMessage() {
        type = MESSAGE_MOVEMENT;
        data = MovePlayerInfo();
    }

    MovePlayerMessage(MovePlayerInfo _data) {
        type = MESSAGE_MOVEMENT;
        data = _data;
    }

    virtual int  serialize(char* outBuff);
    virtual void deserialize(char* inBuff);

    MovePlayerInfo data;
};

struct PlayerJoinMessage : public NetMessage {
   
    PlayerJoinMessage() {
        type = MESSAGE_PLAYER_JOIN;
        data = PlayerJoinInfo();
    }

    PlayerJoinMessage(PlayerJoinInfo _data) {
        type = MESSAGE_PLAYER_JOIN;
        data = _data;
    }

    PlayerJoinInfo data;

    virtual int  serialize(char* outBuff);
    virtual void deserialize(char* inBuff);
};


struct PlayerEatenMessage : public NetMessage {
    
    PlayerEatenMessage() {
        type = MESSAGE_EATEN;
        data = PlayerEatenInfo();
    }

    PlayerEatenMessage(PlayerEatenInfo _data) {
        type = MESSAGE_EATEN;
        data = _data;
    }

    virtual int  serialize(char* outBuff);
    virtual void deserialize(char* inBuff);

    PlayerEatenInfo data;
};


struct FoodEatenMessage : public NetMessage {
        
    FoodEatenMessage() {
        type = MESSAGE_FOOD_EATEN;
        data = FoodEatenInfo();
    }

    FoodEatenMessage(FoodEatenInfo _data) {
        type = MESSAGE_FOOD_EATEN;
        data = _data;
    }

    virtual int  serialize(char* outBuff);
    virtual void deserialize(char* inBuff);

    FoodEatenInfo data;
};

struct DeletePlayerMessage : public NetMessage {
    DeletePlayerMessage() {
        type = MESSAGE_DELETE_PLAYER;
        data = DeletePlayerInfo();
    }

    DeletePlayerMessage(DeletePlayerInfo _data) {
        type = MESSAGE_DELETE_PLAYER;
        data = _data;
    }

    virtual int  serialize(char* outBuff);
    virtual void deserialize(char* inBuff);

    DeletePlayerInfo data;
};


#endif /* __NET_MESSAGE_H__ */
