// Contém funções de recomendação para adição e remoção de amigos.

# ifndef RECOMMENDATION_H
# define RECOMMENDATION_H

# include "socialmanager.h"

# define DEBUG_RECOMMENDATION 1

// Recomenda uma novo amigo para um usuário baseado 
int recommend_friend(GRAPH G, int id);

# endif