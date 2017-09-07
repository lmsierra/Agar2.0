#ifndef __RENDERER_H__
#define __RENDERER_H__

class Renderer {
    
public:
    static const Renderer& Instance();

    virtual void SetColor(Color color = Color())                                              const;
    virtual void SetOrigin(double x, double y)                                                const;
    virtual void DrawPoint(double x, double y, Color color)                                   const;
    virtual void DrawLine(double x1, double y1, double x2, double y2, Color color)            const;
    virtual void DrawRect(double x, double y, double width, double height, Color color)       const;
    virtual void DrawEllipse(double x, double y, double xradius, double yradius, Color color) const;
    virtual void Clear(uint8 r = 0, uint8 g = 0, uint8 b = 0)                                 const;
    virtual void Clear(Color color = Color())                                                 const;

protected:
    Renderer();

private:
    static Renderer* renderer;
};

#endif /* __RENDERER_H__ */