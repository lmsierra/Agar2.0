#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "CustomTypes.h"
#include "EntityInformation.h"

#define WEIGHT_DEFAULT 4

class Entity {

public:

    Entity()                             : m_x(0), m_y(0), m_weight(WEIGHT_DEFAULT) {}
    Entity(double X, double Y)           : m_x(X), m_y(Y), m_weight(WEIGHT_DEFAULT) {}
    Entity(double X, double Y, uint32 W) : m_x(X), m_y(Y), m_weight(W)              {}
    
    virtual void Update(double deltaTime) {}

    double GetX()             const { return m_x;      }
    double GetY()             const { return m_y;      }
    uint32 GetId()            const { return m_id;     }
    uint32 GetWeight()        const { return m_weight; }
    void   SetX(double x)           { m_x = x;         }
    void   SetY(double y)           { m_y = y;         }
    void   SetId(uint32 id)         { m_id = id;       }
    void   SetWeight(uint32 w)      { m_weight = w;    }
    void   AddWeight(int32 w)       { m_weight += w;   }

private:
    double m_x,  m_y;
    uint32 m_id, m_weight;
};

#endif /* __ENTITY_H__ */