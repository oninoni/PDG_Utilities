#pragma once

class Mesh;
class Shader;
class ShaderHandler;

enum FaceMode {
    fM_NAM,
    fM_Vertex,
    fM_VertexTexture,
    fm_VertexNormal,
    fM_VertexTextureNormal
};

struct Image {
public:
    unsigned int width;
    unsigned int height;
    vector<unsigned char> data;
};

class RecourceLoader {
private:
    static Mesh* loadOBJ(string fileName, ShaderHandler* shaderHandler);

    static Image loadPNG(const char* filename);
public:
    static string loadShader(string fileName);

    static Mesh* loadMesh(string fileName, ShaderHandler* ShaderHandler);

    static Image loadTexture(string fileName);

    static Image getErrorImage(int height, int width);
};