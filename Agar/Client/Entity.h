#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "CustomTypes.h"
#include "Renderer.h"
#include "EntityInformation.h"

#define WEIGHT_DEFAULT 4

class Entity {

public:

    Entity()                            : m_x(0), m_y(0), m_weight(WEIGHT_DEFAULT), m_color(Color::RandPredefined(false)) {}
    Entity(double X, double Y)          : m_x(X), m_y(Y), m_weight(WEIGHT_DEFAULT), m_color(Color::RandPredefined(false)) {}
    Entity(double X, double Y, int32 W) : m_x(X), m_y(Y), m_weight(W),              m_color(Color::RandPredefined(false)) {}
    
    virtual void Render() const {
        Renderer::Instance().DrawEllipse(m_x, m_y, m_weight, m_weight, m_color);
    }

    virtual void Update(double deltaTime) {}

    double GetX()             const { return m_x;      }
    double GetY()             const { return m_y;      }
    uint32  GetWeight()       const { return m_weight; }
    uint32  GetId()           const { return m_id;     }
    Color  GetColor()         const { return m_color;  }
    void   SetX(double x)           { m_x = x;         }
    void   SetY(double y)           { m_y = y;         }
    void   SetId(uint32 id)         { m_id = id;       }
    void   SetWeight(uint32 w)      { m_weight = w;    }
    void   SetColor(Color c)        { m_color = c;     }
    void   AddWeight(int32 w)       { m_weight += w;   }

private:
    double m_x, m_y;
    uint32 m_id,  m_weight;
    Color  m_color;
};

#endif /* __ENTITY_H__ */