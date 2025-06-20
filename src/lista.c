#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
	void *dato;
	struct nodo *proximo;
} nodo_t;

struct lista {
	nodo_t *primero;
	nodo_t *ultimo;
	size_t cantidad;
};

struct lista_iterador {
	lista_t *lista;
	nodo_t *nodo_actual;
};

lista_t *lista_crear()
{
	lista_t *lista = malloc(sizeof(lista_t));
	if (!lista) {
		return NULL;
	}

	lista->primero = NULL;
	lista->ultimo = NULL;
	lista->cantidad = 0;

	return lista;
}

size_t lista_tamanio(lista_t *lista)
{
	if (!lista)
		return 0;

	return lista->cantidad;
}

bool lista_insertar(lista_t *lista, void *elemento)
{
	if (!lista)
		return false;

	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
	if (!nuevo_nodo)
		return false;

	nuevo_nodo->dato = elemento;
	nuevo_nodo->proximo = NULL;

	if (lista->cantidad == 0) {
		lista->primero = nuevo_nodo;
		lista->ultimo = nuevo_nodo;
	} else {
		lista->ultimo->proximo = nuevo_nodo;
		lista->ultimo = nuevo_nodo;
	}

	lista->cantidad++;
	return true;
}

bool lista_insertar_en_posicion(lista_t *lista, int posicion, void *elemento)
{
	if (!lista)
		return false;
	if (posicion < 0 || (size_t)posicion > lista->cantidad)
		return false;

	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
	if (!nuevo_nodo)
		return false;

	nuevo_nodo->dato = elemento;

	if (posicion == 0) {
		nuevo_nodo->proximo = lista->primero;
		lista->primero = nuevo_nodo;
		if (lista->cantidad == 0)
			lista->ultimo = nuevo_nodo;
	} else {
		nodo_t *actual = lista->primero;
		for (int i = 0; i < posicion - 1; i++) {
			actual = actual->proximo;
		}

		nuevo_nodo->proximo = actual->proximo;
		actual->proximo = nuevo_nodo;

		if ((size_t)posicion == lista->cantidad)
			lista->ultimo = nuevo_nodo;
	}

	lista->cantidad++;
	return true;
}

void *lista_obtener_elemento(lista_t *lista, int posicion)
{
	if (!lista || posicion < 0 || (size_t)posicion >= lista->cantidad) {
		return NULL;
	}

	nodo_t *actual = lista->primero;
	for (int i = 0; i < posicion; i++) {
		actual = actual->proximo;
	}

	return actual->dato;
}

void *lista_sacar_de_posicion(lista_t *lista, int posicion)
{
	if (!lista || posicion < 0 || (size_t)posicion >= lista->cantidad) {
		return NULL;
	}

	nodo_t *nodo_a_eliminar;
	void *elemento;

	if (posicion == 0) {
		nodo_a_eliminar = lista->primero;
		elemento = nodo_a_eliminar->dato;

		lista->primero = nodo_a_eliminar->proximo;
		if (lista->cantidad == 1)
			lista->ultimo = NULL;
	} else {
		nodo_t *actual = lista->primero;
		for (int i = 0; i < posicion - 1; i++) {
			actual = actual->proximo;
		}

		nodo_a_eliminar = actual->proximo;
		elemento = nodo_a_eliminar->dato;

		actual->proximo = nodo_a_eliminar->proximo;
		if ((size_t)posicion == lista->cantidad - 1)
			lista->ultimo = actual;
	}

	free(nodo_a_eliminar);
	lista->cantidad--;

	return elemento;
}

void *lista_sacar_elemento(lista_t *lista, void *elemento)
{
	if (!lista) {
		return NULL;
	}

	nodo_t *nodo_a_eliminar = NULL;
	void *dato = NULL;

	if (lista->cantidad == 0) {
		return NULL;
	}

	if (lista->primero->dato == elemento) {
		nodo_a_eliminar = lista->primero;
		dato = nodo_a_eliminar->dato;

		lista->primero = nodo_a_eliminar->proximo;
		if (lista->cantidad == 1)
			lista->ultimo = NULL;
	} else {
		nodo_t *actual = lista->primero;
		while (actual->proximo && actual->proximo->dato != elemento) {
			actual = actual->proximo;
		}

		if (!actual->proximo) {
			return NULL;
		}

		nodo_a_eliminar = actual->proximo;
		dato = nodo_a_eliminar->dato;

		actual->proximo = nodo_a_eliminar->proximo;
		if (!actual->proximo)
			lista->ultimo = actual;
	}

	free(nodo_a_eliminar);
	lista->cantidad--;

	return dato;
}

int lista_buscar_posicion(lista_t *lista, void *elemento)
{
	if (!lista || lista->cantidad == 0) {
		return -1;
	}

	nodo_t *actual = lista->primero;
	int posicion = 0;

	while (actual) {
		if (actual->dato == elemento) {
			return posicion;
		}
		actual = actual->proximo;
		posicion++;
	}

	return -1;
}

void *lista_buscar(lista_t *lista, bool (*criterio)(void *, void *),
		   void *contexto)
{
	if (!lista || !criterio) {
		return NULL;
	}

	nodo_t *actual = lista->primero;

	while (actual) {
		if (criterio(actual->dato, contexto)) {
			return actual->dato;
		}
		actual = actual->proximo;
	}

	return NULL;
}

int lista_iterar(lista_t *lista, bool (*f)(void *, void *), void *contexto)
{
	if (!lista || !f) {
		return 0;
	}

	nodo_t *actual = lista->primero;
	int invocaciones = 0;
	bool funcion_verdadera = true;

	while (actual && funcion_verdadera) {
		if (!f(actual->dato, contexto)) {
			funcion_verdadera = false;
		}
		invocaciones++;
		actual = actual->proximo;
	}

	return invocaciones;
}

void lista_destruir(lista_t *lista)
{
	if (!lista)
		return;

	nodo_t *actual = lista->primero;
	while (actual) {
		nodo_t *siguiente = actual->proximo;
		free(actual);
		actual = siguiente;
	}

	free(lista);
}

struct lista_iterador *lista_iterador_crear(lista_t *lista)
{
	if (!lista) {
		return NULL;
	}

	struct lista_iterador *iterador = malloc(sizeof(struct lista_iterador));
	if (!iterador) {
		return NULL;
	}

	iterador->lista = lista;
	iterador->nodo_actual = lista->primero;

	return iterador;
}

bool lista_iterador_quedan_elementos_por_recorrer(
	struct lista_iterador *iterador)
{
	if (!iterador || !iterador->nodo_actual) {
		return false;
	}

	return true;
}

void lista_iterador_proxima_iteracion(struct lista_iterador *iterador)
{
	if (!iterador || !iterador->nodo_actual) {
		return;
	}

	iterador->nodo_actual = iterador->nodo_actual->proximo;
}

void *lista_iterador_obtener_elemento(struct lista_iterador *iterador)
{
	if (!iterador || !iterador->nodo_actual) {
		return NULL;
	}

	return iterador->nodo_actual->dato;
}

void lista_iterador_destruir(struct lista_iterador *iterador)
{
	if (!iterador) {
		return;
	}

	free(iterador);
}
