#ifndef AI_H
#define AI_H

#include "commons.h"

//functions
inline void updateTime(void * p);
inline int attack(Entity * &monster, Player * p);


// threads
void * gameAIfn(void * p);
void * roomAIfn(void * v);

#endif

