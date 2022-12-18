#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdlib.h>
#include <glad/glad.h>

typedef unsigned int texture_t;

texture_t texture_new(const char *path, int flip, GLint type);

void texture_use(const texture_t t);

#endif