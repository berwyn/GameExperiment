#include <vector>

namespace Game::Scene3D
{
    template <class T>
    struct Vec3
    {
        T x, y, z;
    };

    template <class T>
    union Vec4
    {
        inline Vec4() { x = y = z = w = 0; }
        inline Vec4(T _x, T _y, T _z, T _w)
        {
            x = _x;
            y = _y;
            z = _z;
            w = _w;
        }

        struct { T x, y, z, w; };
        struct { T r, g, b, a; };
    };

    struct Vertex
    {
        inline Vertex() : color(), normal(), position() {}
        Vec4<float> color;
        Vec4<float> normal;
        Vec4<float> position;
    };

    struct Model
    {
        inline Model() : vertices() {}
        std::vector<Vertex> vertices;
    };
}
