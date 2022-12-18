#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

void input_init(void);

void input_process(void);

const float *get_m_off(void);

const float *get_m_pos(void);

#endif