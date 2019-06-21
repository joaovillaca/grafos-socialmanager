#pragma once
#include <socialmanager.h>

static void *newGraph(void) {

    GRAPH *G = malloc(sizeof(GRAPH));
    if(G == NULL) return NULL;
    G->vertex = 0;
    G->edges = 0;
    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            G->matrix[i][j] = 0;
        }
    }
    return G;
}

void addEdgeToGraph(GRAPH *G, int row, int col) {

    if(G->matrix[row][col] == 0 || G->matrix[col][row] == 0) {
        G->matrix[row][col] = 1;
        G->matrix[col][row] = 1;
        G->edges++;
    }
}

void removeEdgeFromGraph(GRAPH *G, int row, int col) {

    if(G->matrix[row][col] == 1 || G->matrix[col][row] == 1) {
        G->matrix[row][col] = 0;
        G->matrix[col][row] = 0;
        G->edges--;
    }
}

void putGraph(FILE *stream, GRAPH *G) {

    if(stream == NULL) stream = stdout;
    if(G == NULL) {
        fputs(stream, "nil");
        return
    }
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            fprintf(stream, "%d ", G->matrix[i][j]);
        }
        fprintf(stream, "\n");
    }
}

float calculateFit(PROFILE *a, PROFILE *b) {

    float fit = 0;

    if(!memcmp(a.color, b.color, strlen(a.color))){
        fit = fit + 0.2;
    }
    if(!memcmp(a.movie, b.movie, strlen(a.movie))){
        fit = fit + 0.2;
    }
    if(!memcmp(a.book, b.book, strlen(a.book))){
        fit = fit + 0.2;
    }
    if(!memcmp(a.musicgenre, b.musicgenre, strlen(a.musicgenre))){
        fit = fit + 0.2;
    }

    float aux;
    int dif = a.age - b.age;

    if(dif > 0){
        aux = (float)dif/(float)a.age;
    } else {
        dif = -dif;
        aux = (float)dif/(float)b.age;
    }

    fit = fit + 0.2 * aux;
    return fit;
}

void putDatabase(FILE *stream, GRAPH *G) {

    if(G == NULL) return;
    if(stream == NULL) stream = stdout;

    PROFILE *current = G->userlist;
    for(int i = 0; i < G->vertex; i++) {
        fprintf(stream, "User <%s> data:\n", current->name);
        fprintf(stream, "\tGender: %c\n", current->gender);
        fprintf(stream, "\tAge: %d\n", current->age);
        fprintf(stream, "\tIs single?: %s\n", current->single ? 1 : "yes" ? "no");
        fprintf(stream, "\t-- Favorite tags:\n");
        fprintf(stream, "\tColor: %s\n", current->color);
        fprintf(stream, "\tBook: %s\n", current->book);
        fprintf(stream, "\tMovie: %s\n", current->movie);
        fprintf(stream, "\tMusic genre: %s\n", current->musicgenre);
    }
}

static void *searchInGraph(GRAPH *G, char* username) {

    PROFILE *found = NULL;

    for(int i = 0; i < G->vertex; i++) {
        if(!memcmp(username, G->userlist[i].name, strlen(username))) {
            found = G->userlist[i];
            break;
        }
    }
    return found;
}

void cutEdgeFromGraph(GRAPH *G, PROFILE* a, PROFILE* b) {

    int counter;
}































