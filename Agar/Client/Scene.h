#ifndef __SCENE_H__
#define __SCENE_H__

#include "Array.h"
#include "Camera.h"

class Entity;
class Player;

class Scene {

public:
    enum Layer {
        LAYER_BACK,
        LAYER_FRONT,
        LAYER_COUNT
    };

    Scene();
    virtual ~Scene();

    virtual const Camera& GetCamera()                    const { return camera;                   }
    virtual Camera& GetCamera()                                { return camera;                   }

    virtual void SetBackgroundColor(Color color) { backgroundColor = color; }

    virtual Entity* CreateFood();
    virtual void DeleteFood(Entity* entity);
    virtual int  DeleteFood(uint32 id);

    virtual Player* CreatePlayer();
    virtual void DeletePlayer(Player* player);
    virtual int  DeletePlayer(uint32 id);

    virtual void Update(double deltaTime);
    virtual void Render() const;

protected:
    virtual int  DeleteEntity(uint32 id, Layer layer);
    virtual void RenderBackground()                        const {}
    virtual void RenderAfterBackground()                   const {}
    virtual void RenderEntities(Layer layer)               const;
    virtual void AddEntity(Entity* entity, Layer layer)          { entities[layer].Add(entity); }
    virtual const Array<Entity*>& GetEntities(Layer layer) const { return entities[layer];      }
    virtual Array<Entity*>& GetEntities(Layer layer)             { return entities[layer];      }

private:
    Camera camera;
    Color backgroundColor;

    Array<Entity*> entities[LAYER_COUNT];
};

#endif /* __SCENE_H__ */