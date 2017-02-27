#pragma once

enum ShaderType{
    VertexShader,
    GeometryShader,
    FragmentShader,

    NUM_SHADERS
};

struct GLSLAttribute {
    GLuint location;
    GLuint size;
    GLenum type;
    int offset;
};

class Shader {
private:

    vector<GLSLAttribute> attributes;
    int stride;

    unordered_map<string, int> uniforms;
    
    GLuint program;
    GLuint shaders[NUM_SHADERS];

    void addUniform(string uniform);

    static GLuint createShader(const string& text, GLenum type);
    static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
public:
    Shader(const string& fileName, bool geometryEnabled = false);
    void bind();
    ~Shader();

    void addAttribute(string name, GLenum type, int size);
    GLSLAttribute getGLSLAttribute(int i);
    int getGLSLAttributeCount();
    int getStride();

    GLint getUniformLocation(string uniform);

    void setUniformI(string uniformLocation, int value);
    void setUniformF(string uniformLocation, float value);
    void setUniformVec3(string uniformLocation, vec3 value);
    void setUniformVec4(string uniformLocation, vec4 value);
    void setUniformMat4(string uniformLocation, mat4 value, GLboolean transpose = GL_FALSE);

    GLuint getProgramID();
};