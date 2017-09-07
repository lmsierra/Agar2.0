#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "String.h"
#include <glfw3.h>

class Screen
{

public:
    static Screen& Instance();

    // Pantalla
    virtual void   Open(uint16 width, uint16 height, bool fullscreen);
    virtual void   Close();
    virtual void   SetTitle(const String& title);
    virtual void   Refresh();
    virtual bool   IsOpened()                    const { return opened && glfwWindowShouldClose(window) == 0; }
    virtual uint16 GetWidth()                    const { return width;  }
    virtual uint16 GetHeight()                   const { return height; }
    virtual uint16 GetDesktopWidth()             const;
    virtual uint16 GetDesktopHeight()            const;

    // Temporizador
    double DeltaTime()                           const { return elapsed; }

    // Input
    virtual int32 GetMouseX()                    const { return mousex; }
    virtual int32 GetMouseY()                    const { return mousey; }
    virtual bool  MouseButtonPressed(int button) const;
    virtual bool  KeyPressed(int key)            const;

protected:
    Screen();
    virtual ~Screen();

private:
    static Screen* screen;

    bool        opened;
    uint16      width, height;
    int32       mousex, mousey;
    double      lastTime;
    double      elapsed;

    GLFWwindow* window;

    static int CloseCallback();
};

#endif /* __SCREEN_H__ */