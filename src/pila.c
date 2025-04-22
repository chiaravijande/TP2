#include "pila.h"
#include "src/lista.h"

struct pila {
	lista_t *lista;
};

pila_t *pila_crear() {
	pila_t *pila = malloc(sizeof(pila_t));
	if (!pila) {
		return NULL;
	}

	pila->lista = lista_crear();
	if (!pila->lista) {
		free(pila);
		return NULL;
	}

	return pila;
}

bool pila_apilar(pila_t *pila, void *elemento) {
	if (!pila || !pila->lista) {
		return false;
	}

	return lista_insertar_en_posicion(pila->lista, 0, elemento);
}

void *pila_desapilar(pila_t *pila) {
	if (!pila || pila_vacia(pila)) {
		return NULL;
	}

	return lista_sacar_de_posicion(pila->lista, 0);
}

bool pila_vacia(pila_t *pila) {
	if (!pila || !pila->lista) {
		return true;
	}

	return lista_tamanio(pila->lista) == 0;
}

size_t pila_tamanio(pila_t *pila) {
	if (!pila || !pila->lista) {
		return 0;
	}

	return lista_tamanio(pila->lista);
}

void *pila_tope(pila_t *pila) {
	if (!pila || pila_vacia(pila)) {
		return NULL;
	}

	return lista_obtener_elemento(pila->lista, 0);
}

void pila_destruir(pila_t *pila) {
	if (!pila) {
		return;
	}

	lista_destruir(pila->lista);
	free(pila);
}
