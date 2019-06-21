// Fila estática que não precisa shiftar. 

# ifndef QUEUE_H
# define QUEUE_H

# define MAX_QUEUE_SIZE 100

typedef struct queue Queue;

// Cria uma nova fila.
Queue *create_queue();

// Insere um elemento no final da fila.
void push_queue(Queue *q, int e);

// Remove um elemento do início da fila.
int pop_queue(Queue *q);

// Pega o tamanho da fila.
int get_size_queue(Queue *q);

# endif