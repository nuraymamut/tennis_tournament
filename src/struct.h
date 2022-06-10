#ifndef STRUCT_H_
#define STRUCT_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Player{
                           char *last_name;
                           char *first_name;
                           int score;
                      }Player;

typedef struct Country{
                          char *name;
                          int nr_players;
                          int global_score;
                          Player *players;
                      }Country;
typedef Country data;
typedef Player data1;

#endif