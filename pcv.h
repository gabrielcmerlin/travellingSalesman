#ifndef PCV_H
#define PCV_H

#include <stdbool.h>

typedef struct no_t NO;
typedef struct lista_pcv_t LISTA_PCV;

LISTA_PCV *lista_criar();
void lista_apagar(LISTA_PCV **l);
void lista_inserir_no(LISTA_PCV *l, int indice, int n);
NO *lista_get_inicio(LISTA_PCV *l);
NO *lista_get_no(LISTA_PCV *l, int indice);
bool no_verificar_existencia(LISTA_PCV *l, int indice);
void set_distancia(LISTA_PCV *l, int indice1, int indice2, int dist);
int no_get_distancia(NO *p1, NO *p2);
int no_get_indice(NO *p);
void lista_printar(LISTA_PCV *l);
int *lista_get_rota_atual(LISTA_PCV *l);
int *lista_get_menor_rota(LISTA_PCV *l);
void lista_set_rota_atual(LISTA_PCV *l, int *v, int n_cidades);
void lista_set_menor_rota(LISTA_PCV *l, int *v, int n_cidades);
int no_get_visitado(NO *p);
void no_set_visitado(NO *p, int status);
void lista_set_menor_distancia(LISTA_PCV *l, int dist);
int lista_get_menor_distancia(LISTA_PCV *l);
void lista_set_distancia_atual(LISTA_PCV *l, int dist);
int lista_get_distancia_atual(LISTA_PCV *l);


#endif