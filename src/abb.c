#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct vector_tope_tamanio {
	void **array;
	size_t tope;
	size_t max_tamanio;
} vector_tope_tamanio_t;

abb_t *abb_crear(abb_comparador comparador)
{
	if (!comparador)
		return NULL;

	abb_t *abb = calloc(1, sizeof(abb_t));
	if (!abb)
		return NULL;

	abb->comparador = comparador;
	return abb;
}

/* 
*	Se devolverá un nodo inicializado en todos sus campos y cargado con el respectivo puntero al elemento pasado por parámetro.
*	Si hay algún error de ejecución se devolverá NULL.
* */
nodo_abb_t *nodo_crear(void *elemento)
{
	nodo_abb_t *nodo = calloc(1, sizeof(nodo_abb_t));
	if (!nodo)
		return NULL;

	nodo->elemento = elemento;
	return nodo;
}

/* 
*	Se devolverá la raiz completa ya con el elemento cargado en su posición adecuada, e incrementando el respectivo
*	tamaño del árbol. 
*	De haber error se devolverá NULL.
* */
nodo_abb_t *abb_insertar_rec(nodo_abb_t *raiz, abb_comparador comparador,
			     size_t *tamanio, void *elemento,
			     nodo_abb_t *nuevo_nodo)
{
	if (!comparador)
		return NULL;

	if (!raiz) {
		(*tamanio)++;
		return nuevo_nodo;
	}

	int comparacion = comparador(elemento, raiz->elemento);

	if (comparacion <= 0) {
		raiz->izquierda = abb_insertar_rec(raiz->izquierda, comparador,
						   tamanio, elemento,
						   nuevo_nodo);
	} else if (comparacion > 0)
		raiz->derecha = abb_insertar_rec(raiz->derecha, comparador,
						 tamanio, elemento, nuevo_nodo);

	return raiz;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (!arbol)
		return NULL;

	nodo_abb_t *nuevo_nodo = nodo_crear(elemento);

	arbol->nodo_raiz = abb_insertar_rec(arbol->nodo_raiz, arbol->comparador,
					    &(arbol->tamanio), elemento,
					    nuevo_nodo);

	return arbol;
}

// nodo_abb_t *abb_insertar_it(nodo_abb_t *raiz, abb_comparador comparador,
// 			    size_t *tamanio, void *elemento,
// 			    nodo_abb_t *nuevo_nodo)
// {
// 	if (!raiz) {
// 		raiz = nuevo_nodo;
// 		(*tamanio)++;
// 		return raiz;
// 	}

// 	nodo_abb_t *actual = raiz;

// 	while (actual) {
// 		int comparacion = comparador(elemento, actual->elemento);

// 		if (comparacion > 0) {
// 			if (!actual->derecha) {
// 				actual->derecha = nuevo_nodo;
// 				(*tamanio)++;
// 				actual = NULL;
// 			} else
// 				actual = actual->derecha;
// 		} else {
// 			if (!actual->izquierda) {
// 				actual->izquierda = nuevo_nodo;
// 				(*tamanio)++;
// 				actual = NULL;
// 			} else
// 				actual = actual->izquierda;
// 		}
// 	}

// 	return raiz;
// }

// abb_t *abb_insertar(abb_t *arbol, void *elemento)
// {
// 	if (!arbol)
// 		return NULL;

// 	nodo_abb_t *nuevo_nodo = nodo_crear(elemento);
// 	if (!nuevo_nodo)
// 		return NULL;

// 	arbol->nodo_raiz = abb_insertar_it(arbol->nodo_raiz, arbol->comparador,
// 					   &arbol->tamanio, elemento,
// 					   nuevo_nodo);
// 	return arbol;
// }

/* 
*	Se devuelve como puntero al respectivo predecesor indorden de la raíz pasada por parámetro, dicho elemento será el 
*	extremo derecho de dicha rama.
*	Se devolverá directamente la raiz actualizada luego de la extracción del predecesor inorden de la misma.
*	Se libera la memoria correspondiente al predecesor inorden.
* */
void *busqueda_predecesor_inorden(nodo_abb_t *raiz, void **predecesor_inorden)
{
	nodo_abb_t *izq = raiz->izquierda;
	nodo_abb_t *der = raiz->derecha;
	if (!der &&
	    !izq) { //Esto es que llegue al sucesor y no haya nodos a izquierda
		*predecesor_inorden = raiz->elemento;
		free(raiz); ////VER SI ES NECESARIO HACER FREE DE LOS ELEMENTOS DENTRO DEL NODO!!!
		return NULL;
	} else if (!der &&
		   izq) { //Esto es que llegue al sucesor haya nodos a izquierda
		*predecesor_inorden = raiz->elemento;
		free(raiz); ////VER SI ES NECESARIO HACER FREE DE LOS ELEMENTOS DENTRO DEL NODO!!!
		return (izq);
	}
	raiz->derecha = busqueda_predecesor_inorden(
		raiz->derecha,
		predecesor_inorden); //Esto es para que queden enlazados los nodos en la raiz que se pasó por parámetro
	return raiz; //Esto es para devolver los nodos en la raiz que se pasó por parámetro
}

/* 
*	Se extrae el elemento pasado por parámetro devolviendo la raíz principal del árbol con todo su contenido ya actualizado
*	después de dicha extracción.
*	Devuelve por parámetro el puntero al valor buscado dentro del árbol si este existe.
* */
void *abb_quitar_recursivo(nodo_abb_t *raiz, abb_comparador comparador,
			   size_t *tamanio, void *elemento, void **buscado)
{
	if (!raiz || !comparador)
		return raiz;

	nodo_abb_t *izq = raiz->izquierda;
	nodo_abb_t *der = raiz->derecha;
	int comparacion = comparador(elemento, raiz->elemento);
	if (comparacion == 0) {
		*buscado = raiz->elemento;
		if (izq && der) { //CASO CON 2 HIJOS
			void *predecesor_inorden = NULL;
			raiz->izquierda = busqueda_predecesor_inorden(
				raiz->izquierda, &predecesor_inorden);
			raiz->elemento = predecesor_inorden;
			(*tamanio)--;
			return raiz; ////VER SI ES ESTO LO QUE SE DEBE DE DEVOLVER!!!!!!!!!!
		} else { //CASO 1 HIJO O NINGUN HIJO
			free(raiz);
			(*tamanio)--;
			if (izq) {
				return izq;
			}
			return der;
		}
	} else if (comparacion < 0) {
		raiz->izquierda = abb_quitar_recursivo(raiz->izquierda,
						       comparador, tamanio,
						       elemento, buscado);
	} else
		raiz->derecha = abb_quitar_recursivo(
			raiz->derecha, comparador, tamanio, elemento, buscado);

	return raiz;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (!arbol)
		return NULL;

	void *buscado = NULL;

	arbol->nodo_raiz =
		abb_quitar_recursivo(arbol->nodo_raiz, arbol->comparador,
				     &(arbol->tamanio), elemento, &buscado);

	return buscado;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (abb_tamanio(arbol) == 0)
		return NULL;

	nodo_abb_t *actual = arbol->nodo_raiz;
	nodo_abb_t *buscado = NULL;

	while (actual) {
		int comparacion = arbol->comparador(elemento, actual->elemento);
		if (comparacion > 0) {
			actual = actual->derecha;
		} else if (comparacion < 0) {
			actual = actual->izquierda;
		} else {
			buscado = actual;
			actual = NULL;
		}
	}
	if (!buscado)
		return NULL;
	return buscado->elemento;
}

bool abb_vacio(abb_t *arbol)
{
	return (abb_tamanio(arbol) == 0);
}

size_t abb_tamanio(abb_t *arbol)
{
	if (!arbol)
		return 0;

	return arbol->tamanio;
}

void abb_destruir(abb_t *arbol)
{
	abb_destruir_todo(arbol, NULL);
}

bool abb_destruir_postorder_recursivo(nodo_abb_t *raiz,
				      void (*destructor)(void *))
{
	if (!raiz)
		return true;

	abb_destruir_postorder_recursivo(raiz->izquierda, destructor);
	abb_destruir_postorder_recursivo(raiz->derecha, destructor);

	if (destructor)
		destructor(raiz->elemento);
	free(raiz);

	return true;
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (!arbol)
		return;

	abb_destruir_postorder_recursivo(arbol->nodo_raiz, destructor);
	free(arbol);
}

/* 
*	Se recorre el árbol de forma: raiz (implementado la función correspondiente a su elemento), nodo izquierdo y luego 
*	nodo derecho.
*	Se devuelve true o false según lo especificado en la función pasada por parámetro, o true en caso de haber recorrido todo
* 	el álbol sin error.
* */
bool abb_recorrer_predorder_recursivo(nodo_abb_t *raiz,
				      bool (*funcion)(void *, void *),
				      void *aux, size_t *contador)
{
	if (!raiz)
		return true;

	(*contador)++;
	if (!funcion(raiz->elemento, aux))
		return false;

	bool continuar_recorrido = abb_recorrer_predorder_recursivo(
		raiz->izquierda, funcion, aux, contador);
	if (!continuar_recorrido)
		return false;

	return abb_recorrer_predorder_recursivo(raiz->derecha, funcion, aux,
						contador);

	// return true;		////VER SI ESTE "return" DEBERÍA DE IR
}

/* 
*	Se recorre el árbol de forma: nodo izquierdo, raiz (implementado la función correspondiente a su elemento) y luego nodo 
*	derecho.
*	Se devuelve true o false según lo especificado en la función pasada por parámetro, o true en caso de haber recorrido todo
* 	el álbol sin error.
* */
bool abb_recorrer_inorder_recursivo(nodo_abb_t *raiz,
				    bool (*funcion)(void *, void *), void *aux,
				    size_t *contador)
{
	if (!raiz)
		return true;

	bool continuar_recorrido = abb_recorrer_inorder_recursivo(
		raiz->izquierda, funcion, aux, contador);
	if (!continuar_recorrido)
		return false;

	(*contador)++;
	if (!funcion(raiz->elemento, aux))
		return false;

	return abb_recorrer_inorder_recursivo(raiz->derecha, funcion, aux,
					      contador);

	// return true;		////VER SI ESTE "return" DEBERÍA DE IR
}

/* 
*	Se recorre el árbol de forma: nodo izquierdo (implementado la función correspondiente a su elemento), 
*	nodo derecho(implementado la función correspondiente a su elemento), y luego raiz.
*	Se devuelve true o false según lo especificado en la función pasada por parámetro, o true en caso de haber recorrido todo
* 	el álbol sin error.
* */
bool abb_recorrer_postorder_recursivo(nodo_abb_t *raiz,
				      bool (*funcion)(void *, void *),
				      void *aux, size_t *contador)
{
	if (!raiz)
		return true;

	bool continuar_recorrido = abb_recorrer_postorder_recursivo(
		raiz->izquierda, funcion, aux, contador);
	if (!continuar_recorrido)
		return false;

	continuar_recorrido = abb_recorrer_postorder_recursivo(
		raiz->derecha, funcion, aux, contador);
	if (!continuar_recorrido)
		return false;

	(*contador)++;
	if (!funcion(raiz->elemento,
		     aux)) ////ANALIZAR BIEN ESTE CASO, SI ES QUE NECESITA COLARSE DE NUEVO LA FUNCION EN OTRO LUGAR
		return false;

	return continuar_recorrido;
}

/* 
*	Se recibe una estructura con un vector vacío, su respectivo tope y la cantidad máxima de elementos a almacenar en el mismo.
*	Se llena el vector con el elemento pasado por parámetro y se actualiza el respectivo tope.
*	Se devuelve true en caso de que se haya podido cargar el elemento y su tope, o false en caso de que ya se haya completado la 
*	cantidad total de elementos.
 */
bool llenar_array(void *elemento, void *vector_estructura)
{
	vector_tope_tamanio_t *vector_struct = vector_estructura;

	if (vector_struct->tope >= vector_struct->max_tamanio)
		return false;

	vector_struct->array[vector_struct->tope] = elemento;
	(vector_struct->tope)++;

	return true;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (!arbol || !funcion) ////ver si la funcion puede ser NULL
		return 0;

	size_t contador = 0;
	switch (recorrido) {
	case (PREORDEN):
		abb_recorrer_predorder_recursivo(arbol->nodo_raiz, funcion, aux,
						 &contador);
		break;
	case (INORDEN):
		abb_recorrer_inorder_recursivo(arbol->nodo_raiz, funcion, aux,
					       &contador);
		break;
	case (POSTORDEN):
		abb_recorrer_postorder_recursivo(arbol->nodo_raiz, funcion, aux,
						 &contador);
		break;
	default:
		break;
	}

	return contador;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (!arbol || !array || tamanio_array == 0)
		return 0;

	vector_tope_tamanio_t vector_estructura = {
		.tope = 0, .max_tamanio = tamanio_array
	};
	vector_estructura.array = array;

	abb_con_cada_elemento(arbol, recorrido, llenar_array,
			      &vector_estructura);

	return vector_estructura.tope;
}
