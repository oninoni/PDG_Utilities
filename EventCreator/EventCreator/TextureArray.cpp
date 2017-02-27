#include "stdafx.h"

#include "RecourceLoader.h"

#include "TextureArray.h"

TextureArray::TextureArray(uint layers, GLenum format, int width, int height){
    this->width = width;
    this->height = height;
    this->layers = layers;
    this->format = format;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
    
    if(format == GL_DEPTH_COMPONENT)
       glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, format, width, height, layers, 0, format, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

TextureArray::~TextureArray() {
    glDeleteTextures(1, &textureID);
}

void TextureArray::loadImage(uint layer, string fileName) {
    Image image = RecourceLoader::loadTexture(fileName);

    if (width == 0 || height == 0) {
        if (image.width == 0 || image.height == 0) {
            cerr << "First Image read " + fileName + " has errored so default resolution of 512x512 was chosen! This will most likely create more bugs!" << endl;
            width = 512;
            height = 512;
        }
        else {
            width = image.width;
            height = image.height;
        }
        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, format, width, height, layers, 0, format, GL_UNSIGNED_BYTE, NULL);
    }

    if (image.width != width || image.height != height) {
        cerr << "Image " + fileName + "does not fit its Texture! " << endl;
        image = RecourceLoader::getErrorImage(height, width);
    }

    glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, layer, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, image.data.data());
}

void TextureArray::bind(uint unit) {
    assert(unit >= 0 && unit < 32);

    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
}