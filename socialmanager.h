#pragma once
#ifndef _SOCIALMANAGER_H_
#define _SOCIALMANAGER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SUCCESS 1
#define FAILURE 0
#define ERROR -32000
#define MAX 100

typedef struct _profile {
    char name[40];
    int age;
    char gender;
    bool single;
    char color[40], movie[40], book[40], musicgenre[40];
} PROFILE;

typedef struct _graph {
    int vertex;
    int edges;
    bool matrix[MAX][MAX];
    PROFILE* userlist[MAX];
} GRAPH;

static void *newGraph(void);
void addEdgeToGraph(GRAPH *G, int row, int col);
void removeEdgeFromGraph(GRAPH *G, int row, int col);
void putGraph(FILE* stream, GRAPH *G);
float calculateFit(PROFILE* a, PROFILE* b);

#endif

