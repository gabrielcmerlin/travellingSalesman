#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include "pcv.h"

void forca_bruta_recursao(LISTA_PCV *rota, int n_visitadas, int n_cidades, int menor_dist);
void forca_bruta(LISTA_PCV *rota, int n_cidades, int menor_dist);

#endif