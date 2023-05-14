#include "pa2m.h"
#include "src/abb.h"
#include "src/abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>

int comparador_2(void *elemento_1, void *elemento_2)
{
	int *el_1 = elemento_1;
	int *el_2 = elemento_2;

	return (*el_1) - (*el_2);
}

void insercion_elementos(abb_t *arbol, int *vector, size_t tope)
{
	for (size_t i = 0; i < tope; i++)
		abb_insertar(arbol, vector + i);
}

void eliminar_elementos(abb_t *arbol, int *vector, size_t tope)
{
	for (size_t i = 0; i < tope; i++)
		abb_quitar(arbol, vector + i);
}

void pruebas_creacion()
{
	abb_t *arbol = abb_crear(comparador_2);
	{
		pa2m_afirmar(arbol != NULL, "Se crea un árbol no nulo");
		pa2m_afirmar(arbol->nodo_raiz == NULL,
			     "Se crea un árbol con una raiz vacia");
		pa2m_afirmar(abb_tamanio(arbol) == 0,
			     "Se crea un árbol con cero elementos");
		pa2m_afirmar(arbol->comparador != NULL,
			     "Se crea un árbol con un comparador no nulo");
	}
	abb_destruir(arbol);
}

void pruebas_insercion()
{
	{
		abb_t *arbol = abb_crear(comparador_2);

		int numeros[10] = { 2, 5, 6, 1, 0, 9, 7, 18, 3 };
		size_t tope = 9;
		insercion_elementos(arbol, numeros, tope);

		pa2m_afirmar(
			abb_tamanio(arbol) == 9,
			"La cantidad de elementos ingresados concuerda con la del tamaño del árbol");

		abb_destruir(arbol);
	}
}

bool seguir_mostrando_recorrido(void *elemento, void *elemento_nulo)
{
	printf(" %i|", *(int *)elemento);
	return true;
}

void pruebas_borrado()
{
	{
		abb_t *arbol = abb_crear(comparador_2);

		int numeros[9] = { 18, 20, 11, 17, 15, 16, 14, 10 };
		size_t tope = 8;
		insercion_elementos(arbol, numeros, tope);

		int elemento_borrar1 = 18;
		pa2m_afirmar(abb_buscar(arbol, &elemento_borrar1) ==
				     (void *)(numeros + 0),
			     "El elemento a borrar se encuentra en el árbol");
		void *borrado1 = abb_quitar(arbol, &elemento_borrar1);
		pa2m_afirmar(borrado1 == (void *)(numeros + 0),
			     "El elemento a borrar concuerda con el extraido");
		pa2m_afirmar(
			abb_tamanio(arbol) == 7,
			"La cantidad de elementos restantes concuerda con la del tamaño del árbol");
		pa2m_afirmar(
			abb_buscar(arbol, &elemento_borrar1) == NULL,
			"El elemento borrado ya no se encuentra más en el árbol");

		int elemento_borrar2 = 15;
		void *borrado2 = abb_quitar(arbol, &elemento_borrar2);
		pa2m_afirmar(borrado2 == (void *)(numeros + 4),
			     "El elemento a borrar concuerda con el extraido");
		pa2m_afirmar(
			abb_tamanio(arbol) == 6,
			"La cantidad de elementos restantes concuerda con la del tamaño del árbol");
		pa2m_afirmar(
			abb_buscar(arbol, &elemento_borrar2) == NULL,
			"El elemento borrado ya no se encuentra más en el árbol");

		int elemento_borrar3 = 16;
		void *borrado3 = abb_quitar(arbol, &elemento_borrar3);
		pa2m_afirmar(
			borrado3 == (void *)(numeros + 5),
			"El elemento a borrar (nodo hoja), concuerda con el extraido");
		pa2m_afirmar(
			abb_tamanio(arbol) == 5,
			"La cantidad de elementos restantes concuerda con la del tamaño del árbol");
		pa2m_afirmar(
			abb_buscar(arbol, &elemento_borrar3) == NULL,
			"El elemento borrado ya no se encuentra más en el árbol");
		abb_con_cada_elemento(arbol, POSTORDEN,
				      seguir_mostrando_recorrido, NULL);
		pa2m_afirmar(
			abb_buscar(arbol, &elemento_borrar3) !=
				(void *)(numeros + 5),
			"El elemento borrado ya no se encuentra en el árbol");

		int elemento_borrar4 = 17;
		void *borrado4 = abb_quitar(arbol, &elemento_borrar4);
		pa2m_afirmar(borrado4 == (void *)(numeros + 3),
			     "El elemento a borrar concuerda con el extraido");
		pa2m_afirmar(
			abb_tamanio(arbol) == 4,
			"La cantidad de elementos restantes concuerda con la del tamaño del árbol");

		int elemento_inexistente = 32;
		void *inexistente = abb_quitar(arbol, &elemento_inexistente);
		pa2m_afirmar(inexistente == NULL,
			     "Se intenta borrar elemento inexistente");
		pa2m_afirmar(
			abb_tamanio(arbol) == 4,
			"La cantidad de elementos restantes concuerda con la del tamaño del árbol");

		int elemento_borrar5 = 20;
		void *borrado5 = abb_quitar(arbol, &elemento_borrar5);
		pa2m_afirmar(borrado5 == (void *)(numeros + 1),
			     "El elemento a borrar concuerda con el extraido");
		pa2m_afirmar(
			abb_tamanio(arbol) == 3,
			"La cantidad de elementos restantes concuerda con la del tamaño del árbol");

		int elemento_borrar6 = 10;
		void *borrado6 = abb_quitar(arbol, &elemento_borrar6);
		pa2m_afirmar(borrado6 == (void *)(numeros + 7),
			     "El elemento a borrar concuerda con el extraido");
		pa2m_afirmar(
			abb_tamanio(arbol) == 2,
			"La cantidad de elementos restantes concuerda con la del tamaño del árbol");

		int elemento_borrar7 = 11;
		void *borrado7 = abb_quitar(arbol, &elemento_borrar7);
		pa2m_afirmar(borrado7 == (void *)(numeros + 2),
			     "El elemento a borrar concuerda con el extraido");
		pa2m_afirmar(
			abb_tamanio(arbol) == 1,
			"La cantidad de elementos restantes concuerda con la del tamaño del árbol");

		int elemento_borrar8 = 14;
		void *borrado8 = abb_quitar(arbol, &elemento_borrar8);
		pa2m_afirmar(borrado8 == (void *)(numeros + 6),
			     "El elemento a borrar concuerda con el extraido");
		pa2m_afirmar(
			abb_tamanio(arbol) == 0,
			"La cantidad de elementos restantes concuerda con la del tamaño del árbol");

		int elemento_inexistente1 = 32;
		void *inexistente1 = abb_quitar(arbol, &elemento_inexistente1);
		pa2m_afirmar(inexistente1 == NULL,
			     "No se puede borrar un arbol vacío");
		pa2m_afirmar(abb_tamanio(arbol) == 0,
			     "El árbol se encuentra vacío");

		int nuevo_elemento = 77;
		abb_insertar(arbol, &nuevo_elemento);
		pa2m_afirmar(
			abb_tamanio(arbol) == 1,
			"Se ingresa un nuevo elemento, el árbol ahora tiene un elemento");
		abb_quitar(arbol, &nuevo_elemento);
		pa2m_afirmar(
			abb_tamanio(arbol) == 0,
			"Se elimina elemento, el árbol ahora se encuentra vacío");

		abb_destruir(arbol);
	}
	{
		abb_t *arbol = abb_crear(comparador_2);
		int numeros[9] = { 1, 3, 5, 6, 7, 9 };
		size_t tope = 6;
		insercion_elementos(arbol, numeros, tope);
		int copia_numeros[9] = { 1, 3, 5, 6, 7, 9 };
		size_t tope_copia = 6;
		pa2m_afirmar(
			abb_tamanio(arbol) == tope,
			"Se ingresan elementos ordenados ascendentemente, el árbol ahora tiene la cantidad ingresada de elemento");
		eliminar_elementos(arbol, copia_numeros, tope_copia);
		pa2m_afirmar(
			abb_tamanio(arbol) == 0,
			"Se eliminan todos los elementos, el árbol ahora se encuentra vacío");
		abb_destruir(arbol);
	}
	{
		abb_t *arbol = abb_crear(comparador_2);
		int numeros[9] = { 18, 11, 7, 5, 4, 1 };
		size_t tope = 6;
		insercion_elementos(arbol, numeros, tope);
		int copia_numeros[9] = { 1, 4, 5, 7, 11, 18 };
		size_t tope_copia = 6;
		pa2m_afirmar(
			abb_tamanio(arbol) == tope,
			"Se ingresan elementos ordenados descendentemente, el árbol ahora tiene la cantidad ingresada de elemento");
		eliminar_elementos(arbol, copia_numeros, tope_copia);
		pa2m_afirmar(
			abb_tamanio(arbol) == 0,
			"Se eliminan todos los elementos, el árbol ahora se encuentra vacío");
		abb_destruir(arbol);
	}
	{
		abb_t *arbol = abb_crear(comparador_2);
		pa2m_afirmar(abb_vacio(arbol), "Se crea un árbol vacio");
		int numero = 77;
		abb_insertar(arbol, &numero);
		pa2m_afirmar(abb_tamanio(arbol) == 1,
			     "El árbol tiene ahora un elemento");
		pa2m_afirmar(!abb_vacio(arbol), "El árbol no está vacío");
		int numero_eliminar = 77;
		abb_quitar(arbol, &numero_eliminar);
		pa2m_afirmar(
			abb_vacio(arbol),
			"Se elimina el elemento, el árbol ahora se encuentra vacío");
		abb_destruir(arbol);
	}
	{
		abb_t *arbol = abb_crear(comparador_2);
		pa2m_afirmar(abb_vacio(arbol), "Se crea un árbol vacio");
		int numero = 77;
		abb_insertar(arbol, &numero);
		pa2m_afirmar(abb_tamanio(arbol) == 1,
			     "El árbol tiene ahora un elemento");
		pa2m_afirmar(!abb_vacio(arbol), "El árbol no está vacío");
		abb_quitar(arbol, &numero);
		pa2m_afirmar(
			abb_vacio(arbol),
			"Se elimina el elemento, el árbol ahora se encuentra vacío");
		abb_destruir(arbol);
	}
}

void pruebas_iterador()
{
	{
		abb_t *arbol = abb_crear(comparador_2);

		int numeros[3] = { 2, 3, 1 };
		size_t tope = 3;
		insercion_elementos(arbol, numeros, tope);

		size_t elementos_recorridos = abb_con_cada_elemento(
			arbol, POSTORDEN, seguir_mostrando_recorrido, NULL);
		pa2m_afirmar(
			elementos_recorridos == abb_tamanio(arbol),
			"Cantidad de elementos recorridos iterador concuerda con tamaño del árbol y tipo de recorrido.");
		abb_destruir(arbol);
	}
}

void pruebas_llenado_array()
{
	{
		abb_t *arbol = abb_crear(comparador_2);

		int numeros[5] = { 4, 2, 3, 1, 5 };
		size_t tope_numeros = 5;
		insercion_elementos(arbol, numeros, tope_numeros);

		size_t max_tamanio1 = 3;
		int *vector1[max_tamanio1];
		size_t cant_elementos_ingresados1 = abb_recorrer(
			arbol, INORDEN, (void **)vector1, max_tamanio1);

		pa2m_afirmar(
			max_tamanio1 == cant_elementos_ingresados1,
			"La cantidad de elementos ingresados es el máximo tamaño del vector");

		size_t max_tamanio2 = 10;
		int *vector2[max_tamanio2];
		size_t cant_elementos_ingresados2 = abb_recorrer(
			arbol, INORDEN, (void **)vector2, max_tamanio2);

		pa2m_afirmar(
			cant_elementos_ingresados2 == abb_tamanio(arbol),
			"La cantidad de elementos ingresados es la canatidad máxima del árbol y según el orden definido");

		size_t max_tamanio3 = 0;
		int *vector3[max_tamanio3];
		size_t cant_elementos_ingresados3 = abb_recorrer(
			arbol, INORDEN, (void **)vector3, max_tamanio3);

		pa2m_afirmar(
			cant_elementos_ingresados3 == 0,
			"No se puede ingresar elementos en un vector de tamaño cero");

		abb_destruir(arbol);
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

	pa2m_nuevo_grupo(
		"\n======================== PRUEBAS ITERADOR DE ARBOL ========================");
	pruebas_iterador();

	pa2m_nuevo_grupo(
		"\n======================== PRUEBAS LLENADO ARRAY ========================");
	pruebas_llenado_array();

	return pa2m_mostrar_reporte();
}
