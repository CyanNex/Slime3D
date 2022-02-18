#pragma once

#include <pch.h>

struct tLine
{
    float fX1;
    float fY1;
    float fX2;
    float fY2;
};

struct tRectangle
{
    glm::vec2 aVertices[4];
};

class cCollisionHelper
{
public:
    // Transform a rectangle with a given transformation matrix
    static tRectangle TransformRectangle(const tRectangle& tRectangle, const glm::mat4& tMatrix, bool bXZ = true);

    // Returns true if two rectangles collide
    static bool Collides(const tRectangle& tRectangleA, const tRectangle& tRectangleB);

    static bool CollidesWithPoint(const tRectangle& tRectangle, const glm::vec2& tPoint);

    // Returns true if the rectangle collides with the line
    static bool CollidesWithLine(const tRectangle& tRectangle, const tLine& tLine);

    // Returns true if the two lines intersect
    static bool LinesIntersect(const tLine& tLineA, const tLine& tLineB);
};
