#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "pcv.h"

void forca_bruta_recursao(LISTA_PCV *rota, int n_visitadas, int n_cidades, int menor_dist)
{
	// "origem" armazena o primeiro NO da lista e "no_atual" o último NO visitada na recursão
	int *rota_atual = lista_get_rota_atual(rota);
	int *menor_rota = lista_get_menor_rota(rota);
	NO *origem = lista_get_inicio(rota);
	NO *no_atual = lista_get_no(rota, rota_atual[n_visitadas - 1]);


	if((lista_get_distancia_atual(rota) + menor_dist) > lista_get_menor_distancia(rota))
		return;
	
	// Caso todos os NOs tenham sido visitados
	if (n_visitadas == n_cidades && no_get_distancia(origem, no_atual) != 0)
	{
		// A última cidade da rota é a cidade de origem
		rota_atual[n_cidades] = no_get_indice(origem);

		// Adicionando a distância do NO atual até a origem do caminho
		lista_set_distancia_atual(rota, lista_get_distancia_atual(rota) + no_get_distancia(no_atual, origem));

		// Caso a distância da rota analisada seja menor que a menor distância até o momento
		if (lista_get_distancia_atual(rota) < lista_get_menor_distancia(rota))
		{
			// Atribuindo os dados do caminho realizado ao menor caminho
			lista_set_menor_distancia(rota, lista_get_distancia_atual(rota));
			lista_set_menor_rota(rota, rota_atual, n_cidades);
		}

		// Subtraindo o valor da distancia entre a ultima cidade e a cidade de origem
		lista_set_distancia_atual(rota, lista_get_distancia_atual(rota) - no_get_distancia(no_atual, origem));
		
		// Encerrando a recursão
		return;
	}
	for (int j = 1; j <= n_cidades; j++)
	{
		// "prox_no" corresponde à próxima cidade da recursão
		// e "distancia" à distância do NO atual ao próximo NO ainda não visitado
		NO *prox_no = lista_get_no(rota, j);
		int distancia = no_get_distancia(no_atual, prox_no);

		// Se o próximo NO ainda não foi visitado,
		// há conexão de um NO ao outro, e o próximo NO não for a origem
		if (!no_get_visitado(prox_no) && (distancia != 0) && (prox_no != origem))
		{
			// Adicionando a distância de um NO ao outro
			lista_set_distancia_atual(rota, lista_get_distancia_atual(rota) + distancia);

			// Apontando o próximo NO como visitado
			no_set_visitado(prox_no, 1);

			// Inserindo o índice do próximo NO no caminho realizado
			rota_atual[n_visitadas] = j;

			// Chamando a recursão novamente
			forca_bruta_recursao(rota, n_visitadas + 1, n_cidades, menor_dist);

			// Reinicializando os dados da lista após a recursão
			no_set_visitado(prox_no, 0);

			lista_set_distancia_atual(rota, lista_get_distancia_atual(rota) 
									- no_get_distancia(prox_no, lista_get_no(rota, rota_atual[n_visitadas - 1])));
		}
	}
}
void forca_bruta(LISTA_PCV *rota, int n_cidades, int menor_dist)
{
	assert(rota != NULL);
	int *rota_atual = lista_get_rota_atual(rota);

	// Inicializando os dados da lista para realizar a recursão:
	// A menor distância recebe INT_MAX
	lista_set_menor_distancia(rota, __INT_MAX__);

	// O primeiro elemento do vetor da rota recebe o índice da origem
	rota_atual[0] = no_get_indice(lista_get_inicio(rota));

	// Chamando a recursão
	clock_t inicio = clock();
	forca_bruta_recursao(rota, 1, n_cidades, menor_dist);
	clock_t final = clock();
	printf("Tempo de backtracking: %lf\n", (final - inicio) / (double) CLOCKS_PER_SEC);

	int *menor_rota = lista_get_menor_rota(rota);

	// Imprimindo a menor rota encontrada
	for (int i = 0; i <= n_cidades; i++)	
		printf("%d ", menor_rota[i]);
	printf("\n");
}