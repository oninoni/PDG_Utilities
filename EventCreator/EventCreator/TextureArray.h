#pragma once
class TextureArray {
protected:
    uint width, height, layers;
    GLenum format;

    GLuint textureID;
public:
    TextureArray(uint layers, GLenum format, int width = 0, int height = 0);
    ~TextureArray();

    void bind(uint unit);

    void loadImage(uint layer, string fileName);
};