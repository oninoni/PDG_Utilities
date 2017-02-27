#include "stdafx.h"

#include "m_matrix.h"

template <>
void m_matrix<float, 4, 4>::setTranslationMatrix(const vec3 & t, bool invert) {
    identity();
    if (invert) {
        data[0][3] = -t.x;
        data[1][3] = -t.y;
        data[2][3] = -t.z;
    }
    else {
        data[0][3] = t.x;
        data[1][3] = t.y;
        data[2][3] = t.z;
    }
}

template<>
void m_matrix<float, 4, 4>::setRotationMatrix(const vec3 & r, bool invert) {
    mat4 rx;
    mat4 ry;
    mat4 rz;

    rx.identity();
    ry.identity();
    rz.identity();
    
    vec3 derNeue = r * PI / 180.0f;

    if (invert)
        derNeue = -derNeue;

    rx[1][1] = cos(derNeue.x);
    rx[2][1] = sin(derNeue.x);
    rx[1][2] = -sin(derNeue.x);
    rx[2][2] = cos(derNeue.x);

    ry[2][2] = cos(derNeue.y);
    ry[0][2] = sin(derNeue.y);
    ry[2][0] = -sin(derNeue.y);
    ry[0][0] = cos(derNeue.y);

    rz[0][0] = cos(derNeue.z);
    rz[1][0] = sin(derNeue.z);
    rz[0][1] = -sin(derNeue.z);
    rz[1][1] = cos(derNeue.z);

    if (invert) {
        *this = rz;
        *this *= rx;
        *this *= ry;
    }
    else {
        *this = ry;
        *this *= rx;
        *this *= rz;
    }
}

template<>
void m_matrix<float, 4, 4>::setScaleMatrix(const vec3 & s, bool invert) {
    clear();

    if (invert) {
        data[0][0] = 1 / s.x;
        data[1][1] = 1 / s.y;
        data[2][2] = 1 / s.z;
    }
    else {
        data[0][0] = s.x;
        data[1][1] = s.y;
        data[2][2] = s.z;
    }

    data[3][3] = 1;

}

template<>
void m_matrix<float, 4, 4>::SetProjectionMatrix(float aspectRatio, float zNear, float zFar, float fov) {
    clear();

    fov = fov / 360.0f * PI;
    float f = cos(fov) / sin(fov);

    /*    
       -.          -.
  ======/     ======/
  /    \      /    \
  | () |      | () |
  \____/      \____/

        =====      

    */

    data[0][0] = f / aspectRatio;
    data[1][1] = f;
    data[2][2] = (zFar + zNear) / (zNear - zFar);
    data[2][3] = (2 * zFar * zNear) / (zNear - zFar);
    data[3][2] = -1;
}