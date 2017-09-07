#include "NetMessages.h"

int SnapshotMessage::serialize(char* outBuff) {

    int iBytesSerial = NetMessage::serialize(outBuff);
    outBuff += iBytesSerial;

    *reinterpret_cast<SnapshotInfo*>(outBuff) = data;
    iBytesSerial += sizeof(data);
   
    return iBytesSerial;
}

void SnapshotMessage::deserialize(char* inBuff) {

    NetMessage::deserialize(inBuff);
    //inBuff += sizeof(type);

    //SnapshotInfo i = *reinterpret_cast<SnapshotInfo*>(inBuff);

    SnapshotMessage m = *reinterpret_cast<SnapshotMessage*>(inBuff);
    data = m.data;
  }


int InitMessage::serialize(char* outBuff) {

    int iBytesSerial = NetMessage::serialize(outBuff);
    outBuff += iBytesSerial;

    *reinterpret_cast<InitMessageInfo*>(outBuff) = data;
    iBytesSerial += sizeof(InitMessageInfo);

    return iBytesSerial;
}

void InitMessage::deserialize(char* inBuff) {


    NetMessage::deserialize(inBuff);
    //inBuff += sizeof(NetMessageType);

    // Con lo anterior no me coge bien los valores ¿?¿?¿?¿?
    InitMessage m = *reinterpret_cast<InitMessage*>(inBuff);

    data = m.data;
}


int MovePlayerMessage::serialize(char* outBuff) {

    int iBytesSerial = NetMessage::serialize(outBuff);
    outBuff += iBytesSerial;

    *reinterpret_cast<MovePlayerInfo*>(outBuff) = data;
    iBytesSerial += sizeof(MovePlayerInfo);

    return iBytesSerial;
}

void MovePlayerMessage::deserialize(char* inBuff) {

    NetMessage::deserialize(inBuff);

    MovePlayerMessage m = *reinterpret_cast<MovePlayerMessage*>(inBuff);
    data = m.data;
}



int PlayerJoinMessage::serialize(char* outBuff) {

    int iBytesSerial = NetMessage::serialize(outBuff);
    outBuff += iBytesSerial;

    *reinterpret_cast<PlayerJoinInfo*>(outBuff) = data;
    iBytesSerial += sizeof(PlayerJoinInfo);

    return iBytesSerial;
}

void PlayerJoinMessage::deserialize(char* inBuff) {

    NetMessage::deserialize(inBuff);

    PlayerJoinMessage m = *reinterpret_cast<PlayerJoinMessage*>(inBuff);
    data = m.data;
}


int PlayerEatenMessage::serialize(char* outBuff) {
    int iBytesSerial = NetMessage::serialize(outBuff);
    outBuff += iBytesSerial;

    *reinterpret_cast<PlayerEatenInfo*>(outBuff) = data;
    iBytesSerial += sizeof(PlayerEatenInfo);

    return iBytesSerial;
}

void PlayerEatenMessage::deserialize(char* inBuff) {

    NetMessage::deserialize(inBuff);

    PlayerEatenMessage m = *reinterpret_cast<PlayerEatenMessage*>(inBuff);
    data = m.data;
}


int FoodEatenMessage::serialize(char* outBuff) {
    int iBytesSerial = NetMessage::serialize(outBuff);
    outBuff += iBytesSerial;

    *reinterpret_cast<FoodEatenInfo*>(outBuff) = data;
    iBytesSerial += sizeof(FoodEatenInfo);

    return iBytesSerial;
}

void FoodEatenMessage::deserialize(char* inBuff) {
    NetMessage::deserialize(inBuff);

    FoodEatenMessage m = *reinterpret_cast<FoodEatenMessage*>(inBuff);
    data = m.data;
}


int DeletePlayerMessage::serialize(char* outBuff) {
    int iBytesSerial = NetMessage::serialize(outBuff);
    outBuff += iBytesSerial;

    *reinterpret_cast<DeletePlayerInfo*>(outBuff) = data;
    iBytesSerial += sizeof(DeletePlayerInfo);

    return iBytesSerial;
}

void DeletePlayerMessage::deserialize(char* inBuff) {
    NetMessage::deserialize(inBuff);

    DeletePlayerMessage m = *reinterpret_cast<DeletePlayerMessage*>(inBuff);
    data = m.data;
}