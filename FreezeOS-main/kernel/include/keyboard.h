#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

typedef void (*keyboardCallback)(char);

void keyboard_init();
void keyboard_bind(keyboardCallback callback);

#endif