#include "CustomTypes.h"
#include <stdio.h>
#include "Screen.h"
#include <math.h>

Screen* Screen::screen = NULL;

int Screen::CloseCallback() {
    Screen::Instance().opened = false;
    return GL_TRUE;
}

Screen::Screen() {
    glfwInit();
    opened = false;
}

Screen::~Screen() {
    glfwTerminate();
}

Screen& Screen::Instance() {
    if (!screen)
        screen = new Screen();
    return *screen;
}

void Screen::Open(uint16 width, uint16 height, bool fullscreen) {
    
    // Abrimos la ventana


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    
   // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, "Agar.io 2.0", (fullscreen)? glfwGetPrimaryMonitor() : nullptr, nullptr);
    if (!window)
    {
        // Window or OpenGL context creation failed
        glfwTerminate();
        return;
    }

    if (!fullscreen)
        glfwSetWindowPos(window, (GetDesktopWidth() - width) / 2, (GetDesktopHeight() - height) / 2);

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwSetWindowCloseCallback(window, GLFWwindowclosefun(CloseCallback));
    glfwSwapInterval(1);
    SetTitle("Agar.io 2.0");
    opened = true;

    // Inicializamos OpenGL
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

    // Configuramos viewport
    this->width  = width;
    this->height = height;

    glViewport(0, 0, width, height);

    // Configuramos matriz de proyeccion
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1000);

    // Configuramos matriz de modelado
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Inicializamos temporizador
    lastTime = glfwGetTime();
    elapsed = 0;
}

void Screen::Close() {
    if(window)
        glfwDestroyWindow(window);
}

void Screen::SetTitle(const String &title) {
    glfwSetWindowTitle(window, title.ToCString());
}

void Screen::Refresh() {
    glfwSwapBuffers(window);

    double mx, my;
    glfwGetCursorPos(window, &mx, &my);
    mousex = static_cast<int32>(floor(mx));
    mousey = static_cast<int32>(floor(my));

    elapsed = glfwGetTime() - lastTime;
    lastTime = glfwGetTime();
}

uint16 Screen::GetDesktopWidth() const {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    return uint16(mode->width);
}

uint16 Screen::GetDesktopHeight() const {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    return uint16(mode->height);
}

bool Screen::MouseButtonPressed(int button) const {
    return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

bool Screen::KeyPressed(int key) const {
    return glfwGetKey(window, key) == GLFW_PRESS;
}
