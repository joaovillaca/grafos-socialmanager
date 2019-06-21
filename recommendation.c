// Contém funções de recomendação para adição e remoção de amigos.

# include "queue.h"
# include "socialmanager.h"

# include <stdlib.h>

// Realiza uma bfs no grafo a partir de um nó s.
int *bfs(int s, GRAPH *G) {

    Queue *q = create_queue();
    if(q == NULL) return NULL;

    int *dist = malloc(G->vertex * sizeof(int));
    if(dist == NULL) { // Verifica se a memória foi alocada com sucessor, retorna um erro caso contrário.
        return NULL;
    }
    memset(dist, -1, sizeof(int) * G->vertex);

    dist[s] = 0;
    push_queue(q, s);

    while (get_size_queue(q) > 0) {

        int u = pop_queue(q);
        
        for(int v = 0; v < G->vertex; v++) {

            if(G->matrix[u][v] == 1 && dist[v] == -1) {

                dist[v] = dist[u] + 1;
                push_queue(q, v);

            }
        }
    }

    return dist;

}

// Recomenda um novo amigo para um usuário baseado no fit, na distância entre amigos em comum e na proximidade dos amigos em comum.
int recommend_friend(GRAPH *G, int id) {

    // Fator de por quanto a distância entre usuarios deve reduzir no fator de recomendação.
    const float distFactor = 0.2f;
    // Fator de quanto o fit de amigos em comum deve influenciar no fator de recomendação.
    const float commonFactor = 0.05f;

    // Calcula a quantos amigos de distância os outros usuários estão do usuário inicial.
    int *dist = bfs(id, G);

    // DEBUG: Printa o resultado da BFS.
    # if DEBUG_RECOMMENDATION 1
    for(int i = 0; i < G->vertex; i++) printf("%d ", dist[i]);
    putchar('\n');
    # endif

    // Guarda o fator de recomendação e o id do melhor usuário para recomendar como amigo.
    float maxRecmn = -1;
    int maxId = -1;

    // Calcula o fator de recomendação para todos os possíveis usuários.
    for(int i = 0; i < G->vertex; i++) {

        if(G->matrix[id][i] == 0 && i != id && dist[i] >= 1) { // Caso os usuários ainda não sejam amigos,
                                                            // e eles tenham alguma forma de se conhever através de amigos em comum,
                                                            // calcula o fit dividido pela distância.

            // Calcula um bonus para o fator baseando no número de amigos em comum diretos e considerando o fit entre as partes como um multiplicador.
            float common_friends = 0;
            for(int j = 0; j < G->vertex; j++) {

                if(G->matrix[id][j] == 1 && G->matrix[i][j] == 0 && i != j && id != j)
                    common_friends += (calculateFit(G->userlist[id], G->userlist[j]) + calculateFit(G->userlist[i], G->userlist[j])) / 2.0f;

            }
    
            // Calcula o fator de recomendação.
            float recmn = (calculateFit(G->userlist[id], G->userlist[i]) + (common_friends * commonFactor)) / (1 + (distFactor * (float)dist[i]));

            // DEBUG:
             # if DEBUG_RECOMMENDATION 1
            printf("%f ", recmn);
            # endif

            if(recmn > maxRecmn) { // Atualiza o melhor candidato a amigo se necessário.
                maxRecmn = recmn;
                maxId = i;
            }
        }

    }

    // Libera a memória.
    free(dist);

    return maxId; // Retorna o id do usuário com o fit mais alto relativo a quantidade de amigos de distância. Retorna -1 se nenhum candidato válido
                  // for encontrado.


}

// Recomenda que um usuário defaça uma amizade caso ela não seja verdadeira.
int recommend_unfriend(GRAPH *G, int id) {

    // Fator de quanto o fit de amigos em comum deve influenciar no fator de recomendação.
    const float commonFactor = 0.05f;

    
    // Guarda o fator de recomendação e o id do melhor usuário para recomendar como inimigo.
    float maxRecmn = -1;
    int maxId = -1;

    // Calcula o fator de recomendação para todos os possíveis usuários.
    for(int i = 0; i < G->vertex; i++) {

        if(G->matrix[id][i] == 1 && i != id) { // Caso os usuários sejam amigos calcula o fit.

            /// Calcula um bonus para o fator baseando no número de amigos em comum diretos e considerando o fit entre as partes como um multiplicador.
            float common_friends = 0;
            for(int j = 0; j < G->vertex; j++) {

                if(G->matrix[id][j] == 1 && G->matrix[i][j] == 0 && i != j && id != j)
                    common_friends += (calculateFit(G->userlist[id], G->userlist[j]) + calculateFit(G->userlist[i], G->userlist[j])) / 2.0f;

            }
    
            // Calcula o fator de recomendação.
            float recmn = 1.0 / (0.0001 + calculateFit(G->userlist[id], G->userlist[i]) + (common_friends * commonFactor)); // Um valor pequeno é adicionado para
                                                                                                                            // impedir divisões por 0.

            // DEBUG:
             # if DEBUG_RECOMMENDATION 1
            printf("%f ", recmn);
            # endif

            if(recmn > maxRecmn) { // Atualiza o melhor candidato a amigo se necessário.
                maxRecmn = recmn;
                maxId = i;
            }
        }

    }

    return maxId; // Retorna o id do usuário com o fit mais alto relativo a quantidade de amigos de distância. Retorna -1 se nenhum candidato válido
                  // for encontrado.


}