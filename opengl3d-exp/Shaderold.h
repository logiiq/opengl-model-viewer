#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <cglm/cglm.h>

typedef struct Shader
{
	unsigned int id;

	mat4 proj;
	mat4 view;
	mat4 model;

	mat4 f_matrix;
} Shader_t;

Shader_t shader_new(const char *vpath, const char *fpath);

void shader_init(Shader_t *shader);

void shader_mul(Shader_t *shader);

void shader_use(const Shader_t *shader);

void shader_usei(const unsigned int shader);

void shader_set_view(Shader_t *shader, mat4 *v);

void shader_set_model(Shader_t *shader, mat4 *m);

void shader_uniform1f(const Shader_t *shader, float val, const char *uniform);

void shader_uniform_mat4fv(const Shader_t *shader, mat4 *matrix, const char *uniform);

#endif