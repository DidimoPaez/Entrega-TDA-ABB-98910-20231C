#include "pa2m.h"
#include "src/abb.h"
#include "src/abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct elemento {
	int clave;
	char contenido[10];
} elemento_t;

int comparador_1 (void * elemento_1, void * elemento_2)
{
	elemento_t *el_1 = elemento_1;
	elemento_t *el_2 = elemento_2;

	return (el_1->clave - el_2->clave);
}

elemento_t *crear_elemento(int clave)
{
	elemento_t *elemento = (elemento_t *)malloc(sizeof(elemento_t));
	if (elemento)
		elemento->clave = clave;
	return elemento;
}

void destruir_elemento(elemento_t *elemento)
{
	free(elemento);
}

int comparador_2 (void * elemento_1, void * elemento_2)
{
	int *el_1 = elemento_1;
	int *el_2 = elemento_2;

	return (*el_1) - (*el_2);
}



void pruebas_creacion ()
{
	abb_t *arbol = abb_crear (comparador_1);
	{
		pa2m_afirmar(arbol != NULL, "Se crea un árbol no nulo");
		pa2m_afirmar(arbol->nodo_raiz == NULL, "Se crea un árbol con una raiz vacia");
		pa2m_afirmar(abb_tamanio(arbol) == 0, "Se crea un árbol con cero elementos");
		pa2m_afirmar(arbol->comparador != NULL, "Se crea un árbol con un comparador no nulo");
	}
}

// bool mostrar_arbol(void* elemento_arbol, void * sin_elemento)
// {
	
// }
void pruebas_insercion ()
{
	{
		abb_t *arbol = abb_crear (comparador_2);

		int numeros[10] = {2,5,6,1,0,9,7,18,3};
		for(int i = 0; i < 9;i++){
			abb_insertar(arbol, numeros + i);
		}

		pa2m_afirmar(abb_tamanio(arbol) == 9, "La cantidad de elementos ingresados concuerda con la del tamaño del árbol");

		printf("CANTIDAD DE ELEMENTOS ARBOL: %li\n", abb_tamanio(arbol));
		printf("ELEMENTO ARBOL: %i\n", *(int *)arbol->nodo_raiz->elemento);

		// int numero1 = 3;
		// int numero2 = 4;
		// int numero3 = 2;
		// int numero4 = 5;
		// abb_insertar(arbol, &numero1);
		// abb_insertar(arbol, &numero2);
		// abb_insertar(arbol, &numero3);
		// abb_insertar(arbol, &numero4);

		

		// pa2m_afirmar(arbol->tamanio == 4, "La cantidad de elementos ingresados concuerda con la del tamaño del árbol");

		// printf("CANTIDAD DE ELEMENTOS ARBOL: %li\n", arbol->tamanio);
		// printf("ELEMENTO ARBOL: %i\n", *(int *)arbol->nodo_raiz->elemento);

	}

}

void pruebas_borrado ()
{
	{
		abb_t *arbol = abb_crear (comparador_2);

		int numeros[10] = {2,5,6,1,0,9,7,18,3};
		for(int i = 0; i < 9;i++){
			abb_insertar(arbol, numeros + i);
		}
		int elemento_borrar = 6;
		void * borrado = abb_quitar(arbol, &elemento_borrar);
		pa2m_afirmar(borrado == (void *)(numeros + 2), "El elemento a borrar concuerda con el extraido");
		pa2m_afirmar(abb_tamanio(arbol) == 8, "La cantidad de elementos restantes concuerda con la del tamaño del árbol");
	}
}
int main()
{
	pa2m_nuevo_grupo(
		"\n======================== PRUEBAS CREAR ARBOL ========================");
	pruebas_creacion();

	pa2m_nuevo_grupo(
		"\n======================== PRUEBAS INSERTAR EN ARBOL ========================");
	pruebas_insercion();

	pa2m_nuevo_grupo(
		"\n======================== PRUEBAS BORRAR DE ARBOL ========================");
	pruebas_borrado();

	return pa2m_mostrar_reporte();
}
