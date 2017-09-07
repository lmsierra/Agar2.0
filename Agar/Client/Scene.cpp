#include "Scene.h"
#include "CustomTypes.h"
#include "Entity.h"
#include "Player.h"
#include "Camera.h"

Scene::Scene() {
    SetBackgroundColor(Color(150, 150, 150));
}

Scene::~Scene() {
    for (int i = 0; i < LAYER_COUNT; i++) {
        for (uint32 j = 0; j < entities[i].Size(); j++) delete entities[i][j];
    }
}

Entity* Scene::CreateFood() {
    Entity* entity = new Entity();
    AddEntity(entity, Layer::LAYER_BACK);
    return entity;
}

void Scene::DeleteFood(Entity* entity) {
  
    if (!entity) return;

    entities[LAYER_BACK].Remove(entity);
    delete entity;
}

int Scene::DeleteFood(uint32 id) {
   return DeleteEntity(id, LAYER_BACK);
}

Player* Scene::CreatePlayer() {
    Player* player = new Player();
    AddEntity(player, LAYER_FRONT);
    return player;
}

void Scene::DeletePlayer(Player* player) {

    if (!player) return;

    Entity* e = static_cast<Entity*>(player);
    if (e) {
        entities[LAYER_FRONT].Remove(e);
        delete player;
    }
}


int Scene::DeletePlayer(uint32 id){
    return DeleteEntity(id, LAYER_FRONT);
}

int Scene::DeleteEntity(uint32 id, Layer layer){
    size_t size = entities[layer].Size();

    for (int i = 0; i < size; i++) {
        if (entities[layer][i]->GetId() == id) {
            Entity* e = entities[layer][i];
            entities[layer].Remove(e);
            delete e;
            return i;
        }
    }
    return -1;
}


void Scene::Update(double elapsed) {
    for (int i = 0; i < LAYER_COUNT; i++) {
        for (uint32 j = 0; j < entities[i].Size(); j++) 
            entities[i][j]->Update(elapsed);
    }
    // Actualizamos camara
    camera.Update();
}

void Scene::Render() const {
    
    Renderer::Instance().Clear(backgroundColor);
    Renderer::Instance().SetOrigin(GetCamera().GetX(), GetCamera().GetY());
       
    Renderer::Instance().SetOrigin(0, 0);
    RenderBackground();

    Renderer::Instance().SetOrigin(GetCamera().GetX(), GetCamera().GetY());
    RenderAfterBackground();

    for (int i = 0; i < LAYER_COUNT; i++) {
        RenderEntities((Layer)i);
    }
}

void Scene::RenderEntities(Layer layer) const {
    for (uint32 i = 0; i < entities[layer].Size(); i++)
        entities[layer][i]->Render();
}
