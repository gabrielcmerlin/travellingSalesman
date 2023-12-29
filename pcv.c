#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "pcv.h"

struct no_t
{
	// Informações básicas do NO
	int indice;
	NO *prox;

	// "visitado" armazena 1 caso a cidade já tenha sido visitada na rota, e 0 caso ainda não tenha sido visitada
	int visitado;

	// "distancias" armazena as distancias de uma cidade às outras
	int *distancias;
};
struct lista_pcv_t
{
	// Informações básicas da LISTA
	NO *inicio, *fim;

	// "rota_atual" armazena o trajeto feito até o momento e "distancia_atual" a distancia percorrida até o momento
	int *rota_atual;
	int distancia_atual;

	// "menor_distancia" guarda a menor distancia e "menor_rota" a rota corresponde à menor distancia
	int menor_distancia;
	int *menor_rota;
};

LISTA_PCV *lista_criar(int n)
{
	// Alocando memória para um ponteiro de lista
	LISTA_PCV *l = malloc (sizeof(LISTA_PCV));
	assert(l != NULL);

	// Inicializando as variáveis da lista
	l->inicio = NULL;
	l->fim = NULL;
	l->distancia_atual = 0;

	// Alocando memória para os vetores da lista
	l->rota_atual = malloc ((n + 1) * sizeof(int));
	l->menor_rota = malloc ((n + 1) * sizeof(int));

	return l;
}
void lista_apagar(LISTA_PCV **l)
{
	assert(l != NULL);
	NO *temp;

	// Liberando a memória dos NOs alocados na lista
	temp = (*l)->inicio;
	while (temp != NULL)
	{
		(*l)->inicio = (*l)->inicio->prox;

		free(temp->distancias);
		temp->distancias = NULL;
		
		free(temp);
		temp = (*l)->inicio;
	}
	// Liberando a memória alocada para a lista
	free((*l)->rota_atual);
	free((*l)->menor_rota);
	(*l)->fim = NULL;
	
	free(*l);
	*l = NULL;
}
void lista_inserir_no(LISTA_PCV *l, int indice, int n)
{
	// Verificando se a lista e o NO foram alocados devidamente
	assert(l != NULL);
	NO *p = malloc (sizeof(NO));
	assert(p != NULL);
	
	// Inicializando o NO
	p->indice = indice;
	p->visitado = 0;
	p->prox = NULL;
	p->distancias = calloc (n, sizeof(int));

	// Inserindo o NO na lista
	if(l->inicio == NULL)
		l->inicio = p;
	else
		l->fim->prox = p;

	// Inicializando o fim da lista e incrementando o número de cidades
	l->fim = p;
}
NO *lista_get_inicio(LISTA_PCV *l)
{
	// Retornando o NO de início da lista
	assert(l != NULL);
	return l->inicio;
}
NO *lista_get_no(LISTA_PCV *l, int indice)
{
	assert(l != NULL);
	NO *p = lista_get_inicio(l);

	// Verificando se o NO está na lista
	if(!no_verificar_existencia(l, indice))
		return NULL;
	else
	{
		// Percorrendo a lista até encontrar o NO de índice buscado
		while(p->indice != indice)
			p = p->prox;
	}
	return p;
}
bool no_verificar_existencia(LISTA_PCV *l, int indice)
{
	assert(l != NULL);
	NO *p = lista_get_inicio(l);

	// Percorrendo a lista
	while(p != NULL)
	{
		// Caso o NO seja encontrado, retorna TRUE
		if(p->indice == indice)
			return true;
		p = p->prox;
	}
	// Caso contrário, retorna FALSE
	return false;
}
void set_distancia(LISTA_PCV *l, int indice1, int indice2, int dist)
{
	assert(l != NULL);

	// Pegando os NOs correspondetes aos índices informados
	NO *p1 = lista_get_no(l, indice1);
	NO *p2 = lista_get_no(l, indice2);

	// Atribuíndo a distancia lida ao vetor de distâncias de cada NO
	p1->distancias[indice2 - 1] = dist;
	p2->distancias[indice1 - 1] = dist;
}
int no_get_distancia(NO *p1, NO *p2)
{
	// Retornando a distância de um NO ao outro
	assert(p1 != NULL);
	assert(p2 != NULL);
	return p1->distancias[no_get_indice(p2) - 1];
}
int no_get_indice(NO *p)
{
	// Retornando o índice de um NO
	assert(p != NULL);
	return p->indice;
}
int *lista_get_rota_atual(LISTA_PCV *l)
{
	// Retornando a rota atual
	assert(l != NULL);
	return l->rota_atual;
}
int *lista_get_menor_rota(LISTA_PCV *l)
{
	// Retornando a menor rota
	assert(l != NULL);
	return l->menor_rota;
}
void lista_set_rota_atual(LISTA_PCV *l, int *v, int n_cidades)
{
	// Atribuíndo um vetor ao campo de "rota_atual"
	assert(l != NULL);
	for(int i = 0; i <= n_cidades; i++)
		l->rota_atual[i] = v[i];
}
void lista_set_menor_rota(LISTA_PCV *l, int *v, int n_cidades)
{
	// Atribuíndo um vetor ao campo de "menor_rota"
	assert(l != NULL);
	for(int i = 0; i <= n_cidades; i++)
		l->menor_rota[i] = v[i];
}
int no_get_visitado(NO *p)
{
	// Retornando o status de visitado de um NO
	assert(p != NULL);
	return p->visitado;
}
void no_set_visitado(NO *p, int status)
{
	// Definindo o status de visitado de um NO
	assert(p != NULL);
	p->visitado = status;
}
int lista_get_distancia_atual(LISTA_PCV *l)
{
	// Retornando a distância atual da lista
	assert(l != NULL);
	return l->distancia_atual;
}
void lista_set_distancia_atual(LISTA_PCV *l, int dist)
{
	// Definindo a distância atual da lista
	assert(l != NULL);
	l->distancia_atual = dist;
}
int lista_get_menor_distancia(LISTA_PCV *l)
{
	// Retornando a menor distancia armazenada na lista
	assert(l != NULL);
	return l->menor_distancia;
}
void lista_set_menor_distancia(LISTA_PCV *l, int dist)
{
	// Definindo a menor distancia armazenada na lista
	assert(l != NULL);
	l->menor_distancia = dist;
}
