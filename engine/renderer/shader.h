#ifndef SHADER_H
#define SHADER_H

typedef enum {
    UNIFORM_FLOAT,
    UNIFORM_INT,
    UNIFORM_VEC2,
    UNIFORM_VEC3,
    UNIFORM_VEC4,
    UNIFORM_MAT4,
    UNIFORM_TEXTURE
} UniformType;

typedef union {
    float float_val;
    int int_val;
    float vec2_val[2];
    float vec3_val[3];
    float vec4_val[4];
    float mat4_val[16];
    unsigned int texture_id;
} UniformValue;

#endif
