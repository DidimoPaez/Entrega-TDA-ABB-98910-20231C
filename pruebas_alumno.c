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

		int numeros[9] = {18,20,11,17,15,16,14,10}; 
		for(int i = 0; i < 8;i++){
			abb_insertar(arbol, numeros + i);
		}
		int elemento_borrar1 = 18;
		void * borrado1 = abb_quitar(arbol, &elemento_borrar1);
		pa2m_afirmar(borrado1 == (void *)(numeros + 0), "El elemento a borrar concuerda con el extraido");
		pa2m_afirmar(abb_tamanio(arbol) == 7, "La cantidad de elementos restantes concuerda con la del tamaño del árbol");
		// pa2m_afirmar(abb_buscar(arbol, elemento_borrar1) == (void *)(numeros + 2), "El elemento borrado ya no se encuentra más en el árbol");
		int elemento_borrar2 = 15;
		void * borrado2 = abb_quitar(arbol, &elemento_borrar2);
		pa2m_afirmar(borrado2 == (void *)(numeros + 4), "El elemento a borrar concuerda con el extraido");
		pa2m_afirmar(abb_tamanio(arbol) == 6, "La cantidad de elementos restantes concuerda con la del tamaño del árbol");
		// pa2m_afirmar(abb_buscar(arbol, elemento_borrar2) == (void *)(numeros + 2), "El elemento borrado ya no se encuentra más en el árbol");

		int elemento_borrar3 = 16;
		void * borrado3 = abb_quitar(arbol, &elemento_borrar3);
		pa2m_afirmar(borrado3 == (void *)(numeros + 5), "El elemento a borrar concuerda con el extraido");
		pa2m_afirmar(abb_tamanio(arbol) == 5, "La cantidad de elementos restantes concuerda con la del tamaño del árbol");
		// pa2m_afirmar(abb_buscar(arbol, elemento_borrar3) == (void *)(numeros + 2), "El elemento borrado ya no se encuentra más en el árbol");
		
		int elemento_borrar4 = 17;
		void * borrado4 = abb_quitar(arbol, &elemento_borrar4);
		pa2m_afirmar(borrado4 == (void *)(numeros + 3), "El elemento a borrar concuerda con el extraido");
		pa2m_afirmar(abb_tamanio(arbol) == 4, "La cantidad de elementos restantes concuerda con la del tamaño del árbol");
		// pa2m_afirmar(abb_buscar(arbol, elemento_borrar4) == (void *)(numeros + 2), "El elemento borrado ya no se encuentra más en el árbol");

		int elemento_inexistente = 32;
		void * inexistente = abb_quitar(arbol, &elemento_inexistente);
		pa2m_afirmar(inexistente == NULL, "Se intenta borrar elemento inexistente");
		pa2m_afirmar(abb_tamanio(arbol) == 4, "La cantidad de elementos restantes concuerda con la del tamaño del árbol");
		
		// int elementos_restantes[4];
		// elementos_restantes[0] = numeros[1];
		// elementos_restantes[1] = numeros[7];
		// elementos_restantes[2] = numeros[2];
		// elementos_restantes[3] = numeros[6];

		// int elementos_borrar[4] = {20, 10, 11, 14};
		// void * elemento_borrado = NULL;
		// for(int i = 0; i < 4; i++){
		// 	elemento_borrado = abb_quitar(arbol, elementos_borrar + i);
		// 	printf("A BORRAR: %i | EXTRAIDO: %i", *(elementos_restantes + i), *(int *)elemento_borrado);
		// 	pa2m_afirmar(elemento_borrado == (void *)(elementos_restantes + i), "El elemento a borrar concuerda con el extraido");
		// 	pa2m_afirmar(abb_tamanio(arbol) == (3 - i), "La cantidad de elementos restantes concuerda con la del tamaño del árbol");
		// }

		int elemento_borrar5 = 20;
		void * borrado5 = abb_quitar(arbol, &elemento_borrar5);
		pa2m_afirmar(borrado5 == (void *)(numeros + 1), "El elemento a borrar concuerda con el extraido");
		pa2m_afirmar(abb_tamanio(arbol) == 3, "La cantidad de elementos restantes concuerda con la del tamaño del árbol");
		
		int elemento_borrar6 = 10;
		void * borrado6 = abb_quitar(arbol, &elemento_borrar6);
		pa2m_afirmar(borrado6 == (void *)(numeros + 7), "El elemento a borrar concuerda con el extraido");
		pa2m_afirmar(abb_tamanio(arbol) == 2, "La cantidad de elementos restantes concuerda con la del tamaño del árbol");
		
		int elemento_borrar7 = 11;
		void * borrado7 = abb_quitar(arbol, &elemento_borrar7);
		pa2m_afirmar(borrado7 == (void *)(numeros + 2), "El elemento a borrar concuerda con el extraido");
		pa2m_afirmar(abb_tamanio(arbol) == 1, "La cantidad de elementos restantes concuerda con la del tamaño del árbol");
		
		int elemento_borrar8 = 14;
		void * borrado8 = abb_quitar(arbol, &elemento_borrar8);
		pa2m_afirmar(borrado8 == (void *)(numeros + 6), "El elemento a borrar concuerda con el extraido");
		pa2m_afirmar(abb_tamanio(arbol) == 0, "La cantidad de elementos restantes concuerda con la del tamaño del árbol");
		
		int elemento_inexistente1 = 32;
		void * inexistente1 = abb_quitar(arbol, &elemento_inexistente1);
		pa2m_afirmar(inexistente1 == NULL, "No se puede borrar un arbol vacío");
		pa2m_afirmar(abb_tamanio(arbol) == 0, "El árbol se encuentra vacío");
	}
}

bool seguir_mostrando_recorrido(void *elemento, void* elemento_nulo)
{
	printf(" %i|", *(int *)elemento);
	return true;
}


void pruebas_iterador()
{
	{	
		abb_t *arbol = abb_crear (comparador_2);

		int numeros[3] = {2, 3, 1}; 
		for(int i = 0; i < 3;i++){
			abb_insertar(arbol, numeros + i);
		}

		size_t elementos_recorridos = abb_con_cada_elemento(arbol, POSTORDEN,seguir_mostrando_recorrido, NULL);
		pa2m_afirmar(elementos_recorridos == abb_tamanio(arbol), "Cantidad de elementos recorridos iterador concuerda con tamaño del árbol y tipo de recorrido.");




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

	// pa2m_nuevo_grupo(
	// 	"\n======================== PRUEBAS BORRAR DE ARBOL ========================");
	// pruebas_borrado();

	pa2m_nuevo_grupo(
		"\n======================== PRUEBAS ITERADOR DE ARBOL ========================");
	pruebas_iterador();

	return pa2m_mostrar_reporte();
}
