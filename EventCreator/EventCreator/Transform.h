#pragma once

class Transform {
private:
    vec3 d_forward;
    bool forwardHasChanged;

    vec3 d_left;
    bool leftHasChanged;

    vec3 d_up;
    bool upHasChanged;

    vec3 t_translation;
    bool translationHasChanged;
    mat4 translationMatrix;
    mat4 translationMatrixInverse;

    //vec3 t_rotation;
    Quaternion t_rotation;
    bool rotationHasChanged;
    mat4 rotationMatrix;
    mat4 rotationMatrixInverse;

    vec3 t_scale;
    bool scaleHasChanged;
    mat4 scaleMatrix;
    mat4 scaleMatrixInverse;

    vec3 t_offset;
    bool offsetHasChanged;
    mat4 offsetMatrix;
    mat4 offsetMatrixInverse;

    bool hasChanged;
    mat4 transformationMatrix;
    mat4 transformationMatrixInverse;
public:
    Transform();
    ~Transform();

    mat4 getTransformationMatrix(bool inverted = false);

    vec3 getTranslation() const;
    void setTranslation(vec3 t);
    void setTranslation(float x, float y, float z);

    Quaternion& getRotation();
    void setRotation(Quaternion r);
    void setRotation(float x, float y, float z, float w);

    vec3 getScale() const;
    void setScale(vec3 s);
    void setScale(float x, float y, float z);

    vec3 getOffset() const;
    void setOffset(vec3 s);
    void setOffset(float x, float y, float z);

    vec3 getForward();
    vec3 getLeft();
    vec3 getUp();

    __declspec(property(get = getTranslation, put = setTranslation)) vec3 position;
    __declspec(property(get = getRotation, put = setRotation)) Quaternion rotation;
    __declspec(property(get = getScale, put = setScale)) vec3 scale;
    __declspec(property(get = getOffset, put = setOffset)) vec3 offset;
};