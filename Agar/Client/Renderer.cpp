#include <stdio.h>
#include <tchar.h>
#include "CustomTypes.h"
#include "Renderer.h"
#include "Math.h"
#include <glfw3.h>

#define ELLIPSEPOINTS 32

Renderer* Renderer::renderer = NULL;

Renderer::Renderer() {}

const Renderer& Renderer::Instance() { if (!renderer) renderer = new Renderer(); return *renderer; }

void Renderer::DrawPoint(double x, double y, Color color) const
{
    SetColor(color);
    GLdouble vertices[]   = {x, y};
    GLdouble texCoords[]  = {0, 0};
    glBindTexture(GL_TEXTURE_2D, 0);
    glVertexPointer(2, GL_DOUBLE, 0, vertices);
    glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
    glDrawArrays(GL_POINTS, 0, 1);
    SetColor();
}


void Renderer::SetOrigin(double x, double y) const {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(-x, -y, 0);
}


void Renderer::DrawLine(double x1, double y1, double x2, double y2, Color color) const
{
    SetColor(color);
    GLdouble vertices[]  = {x1, y1, x2, y2};
    GLdouble texCoords[] = {0, 0, 0, 0};
    glBindTexture(GL_TEXTURE_2D, 0);
    glVertexPointer(2, GL_DOUBLE, 0, vertices);
    glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
    glDrawArrays(GL_LINES, 0, 2);
    SetColor();
}


void Renderer::DrawRect(double x, double y, double width, double height, Color color) const
{
    SetColor(color);
    GLdouble vertices[]  = { x, y, x + width, y, x, y + height, x + width, y + height };
    GLdouble texCoords[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    glBindTexture(GL_TEXTURE_2D, 0);
    glVertexPointer(2, GL_DOUBLE, 0, vertices);
    glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    SetColor();
}


void Renderer::DrawEllipse(double x, double y, double xradius, double yradius, Color color) const
{
    SetColor(color);
    GLdouble vertices[ELLIPSEPOINTS * 2];
    for (uint32 i = 0; i < ELLIPSEPOINTS; i++) {
        vertices[i * 2] = x + (DegCos(i * 360.0 / ELLIPSEPOINTS) * xradius);
        vertices[i * 2 + 1] = y + (DegSin(i * 360.0 / ELLIPSEPOINTS) * yradius);
    }

    GLdouble texCoords[ELLIPSEPOINTS * 2];
    memset(texCoords, 0, ELLIPSEPOINTS * 2 * sizeof(GLdouble));

    glBindTexture(GL_TEXTURE_2D, 0);
    glVertexPointer(2, GL_DOUBLE, 0, vertices);
    glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
    glDrawArrays(GL_TRIANGLE_FAN, 0, ELLIPSEPOINTS);
    SetColor();
}

void Renderer::SetColor(Color color) const {
    glColor4ub(color.R, color.G, color.B, color.A);
}


void Renderer::Clear(uint8 r, uint8 g, uint8 b) const {
	glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Clear(Color color) const {
    Clear(color.R, color.G, color.B);
}
