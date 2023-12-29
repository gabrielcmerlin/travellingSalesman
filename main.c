// Trabalho 1 - Algorítmos e estrutura de dados 1
// ICMC -USP São Carlos - BBC, 2º semestre
// Enzo Nunes - 13671810
// Gabriel Merlin - 12544420
// Matheus Leffeck - 13673318

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "pcv.h"
#include "backtracking.h"

int main(int argc, char *argv[])
{
    char c;
    int n_cidades, index_origem, index1, index2, dist;
    int menor_dist_lida = __INT_MAX__;
    LISTA_PCV *rota = NULL;

    // Lendo o número de cidades e a cidade de origem
    scanf("%d %d", &n_cidades, &index_origem);

    // Criando uma lista ordenada e inserindo o NO de origem nela
    rota = lista_criar(n_cidades);
    lista_inserir_no(rota, index_origem, n_cidades);

    while((c = getchar()) != EOF)
    {
        // Lendo as conexões e a distância informadas
        ungetc(c, stdin);
        scanf(" %d %d %d", &index1, &index2, &dist);
        
        if(dist < menor_dist_lida)
            menor_dist_lida = dist;

        // Caso ainda não conste um NO com o índice informado na lista, criamos um novo NO
        if(!no_verificar_existencia(rota, index1))
            lista_inserir_no(rota, index1, n_cidades);
        if(!no_verificar_existencia(rota, index2))
            lista_inserir_no(rota, index2, n_cidades);

        // Atribuíndo a distância aos NOs lidos
        set_distancia(rota, index1, index2, dist);
    }

    // Procurando o melhor caminho
    forca_bruta(rota, n_cidades, menor_dist_lida);

    // Liberando a memória alocada
    lista_apagar(&rota);
    
    return 0;
}