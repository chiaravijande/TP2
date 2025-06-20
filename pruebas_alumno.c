#include "pa2m.h"
#include "src/cola.h"
#include "src/lista.h"
#include "src/pila.h"

void prueba_simple()
{
	int i = 5;
	int j = 16;

	pa2m_afirmar(i != j,
		     "i no es igual a j (%d != %d), como debería pasar\n", i,
		     j);

	pa2m_afirmar(2 * i == 10, "2*i es igual a 10 (%d)", 2 * i);
}

void prueba_creacion_lista()
{
	pa2m_nuevo_grupo(
		"Pruebas de creación de la lista simplemente enlazada");

	lista_t *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Se pudo crear una lista vacía");

	lista_destruir(lista);
	pa2m_afirmar(true, "Se destruyó la lista correctamente");
}

void prueba_insertar_en_lista_vacia()
{
	pa2m_nuevo_grupo("Pruebas de inserción en una lista vacía");

	lista_t *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Se pudo crear la lista");

	int uno = 1, dos = 2, tres = 3;

	pa2m_afirmar(lista_insertar(lista, &uno),
		     "Se pudo insertar el primer elemento (1)");
	pa2m_afirmar(lista_insertar(lista, &dos),
		     "Se pudo insertar el segundo elemento (2)");
	pa2m_afirmar(lista_insertar(lista, &tres),
		     "Se pudo insertar el tercer elemento (3)");

	pa2m_afirmar(lista_tamanio(lista) == 3, "La lista tiene 3 elementos");
	pa2m_afirmar(*(int *)lista_obtener_elemento(lista, 2) == 3,
		     "El último elemento es 3");

	lista_destruir(lista);
	pa2m_afirmar(true, "Se destruyó la lista correctamente");
}

void prueba_insertar_en_posicion()
{
	pa2m_nuevo_grupo("Pruebas de inserción en una posición específica");

	lista_t *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Se pudo crear una lista vacía");

	int uno = 1, dos = 2, tres = 3, cuatro = 4;

	pa2m_afirmar(lista_insertar(lista, &uno),
		     "Se pudo insertar el elemento 1 al final");
	pa2m_afirmar(lista_insertar(lista, &dos),
		     "Se pudo insertar el elemento 2 al final");

	pa2m_afirmar(lista_insertar_en_posicion(lista, 1, &tres),
		     "Se pudo insertar el elemento 3 en la posición 1");
	pa2m_afirmar(*(int *)lista_obtener_elemento(lista, 1) == 3,
		     "El elemento en la posición 1 es 3");
	pa2m_afirmar(lista_tamanio(lista) == 3,
		     "La lista tiene ahora 3 elementos");

	pa2m_afirmar(
		!lista_insertar_en_posicion(lista, 10, &cuatro),
		"No se pudo insertar en la posición 10, que excede el tamaño de "
		"la lista");
	pa2m_afirmar(
		lista_tamanio(lista) == 3,
		"La lista sigue teniendo 3 elementos después del intento fallido");

	lista_destruir(lista);
	pa2m_afirmar(true, "Se destruyó la lista correctamente");
}

void prueba_lista_tamanio()
{
	pa2m_nuevo_grupo("Pruebas de tamaño de la lista");

	// Caso 1: Lista inexistente
	lista_t *lista_inexistente = NULL;
	pa2m_afirmar(lista_tamanio(lista_inexistente) == 0,
		     "El tamaño de una lista inexistente es 0");

	// Caso 2: Lista vacía
	lista_t *lista_vacia = lista_crear();
	pa2m_afirmar(lista_tamanio(lista_vacia) == 0,
		     "El tamaño de una lista vacía es 0");

	// Caso 3: Lista con elementos
	lista_t *lista_con_elementos = lista_crear();
	int uno = 1, dos = 2, tres = 3;

	lista_insertar(lista_con_elementos, &uno);
	pa2m_afirmar(lista_tamanio(lista_con_elementos) == 1,
		     "El tamaño de la lista es 1 tras insertar un elemento");

	lista_insertar(lista_con_elementos, &dos);
	lista_insertar(lista_con_elementos, &tres);
	pa2m_afirmar(lista_tamanio(lista_con_elementos) == 3,
		     "El tamaño de la lista es 3 tras insertar tres elementos");

	// Caso 4: Destruir lista
	lista_destruir(lista_vacia);
	lista_destruir(lista_con_elementos);
	pa2m_afirmar(
		true,
		"Se destruyeron correctamente las listas utilizadas en las pruebas");
}

void prueba_obtener_elemento()
{
	pa2m_nuevo_grupo("Pruebas de obtención de elementos en la lista");

	lista_t *lista = lista_crear();
	int uno = 1, dos = 2, tres = 3;

	lista_insertar(lista, &uno);
	lista_insertar(lista, &dos);
	lista_insertar(lista, &tres);

	pa2m_afirmar(*(int *)lista_obtener_elemento(lista, 0) == 1,
		     "Se obtuvo correctamente el primer elemento (1)");
	pa2m_afirmar(*(int *)lista_obtener_elemento(lista, 1) == 2,
		     "Se obtuvo correctamente el segundo elemento (2)");
	pa2m_afirmar(*(int *)lista_obtener_elemento(lista, 2) == 3,
		     "Se obtuvo correctamente el tercer elemento (3)");
	pa2m_afirmar(lista_obtener_elemento(lista, 3) == NULL,
		     "No se pudo obtener un elemento fuera del rango");

	lista_destruir(lista);
	pa2m_afirmar(true, "Se destruyó la lista correctamente");
}

void prueba_sacar_de_posicion()
{
	pa2m_nuevo_grupo(
		"Pruebas de extracción de elementos en posiciones específicas");

	lista_t *lista = lista_crear();
	int uno = 1, dos = 2, tres = 3;

	lista_insertar(lista, &uno);
	lista_insertar(lista, &dos);
	lista_insertar(lista, &tres);

	pa2m_afirmar(*(int *)lista_sacar_de_posicion(lista, 1) == 2,
		     "Se sacó correctamente el elemento en la posición 1 (2)");
	pa2m_afirmar(lista_tamanio(lista) == 2,
		     "La lista ahora tiene 2 elementos");
	pa2m_afirmar(lista_sacar_de_posicion(lista, 5) == NULL,
		     "No se pudo sacar un elemento fuera del rango");

	lista_destruir(lista);
	pa2m_afirmar(true, "Se destruyó la lista correctamente");
}

void prueba_sacar_elemento()
{
	pa2m_nuevo_grupo("Pruebas de extracción de un elemento por su valor");

	lista_t *lista = lista_crear();
	int uno = 1, dos = 2, tres = 3, cuatro = 4;

	lista_insertar(lista, &uno);
	lista_insertar(lista, &dos);
	lista_insertar(lista, &tres);

	pa2m_afirmar(*(int *)lista_sacar_elemento(lista, &dos) == 2,
		     "Se sacó correctamente el elemento con valor 2");
	pa2m_afirmar(lista_tamanio(lista) == 2,
		     "La lista ahora tiene 2 elementos");
	pa2m_afirmar(lista_sacar_elemento(lista, &cuatro) == NULL,
		     "No se pudo sacar un elemento que no existe");

	lista_destruir(lista);
	pa2m_afirmar(true, "Se destruyó la lista correctamente");
}

void prueba_buscar_posicion()
{
	pa2m_nuevo_grupo("Pruebas de búsqueda de posición de un elemento");

	lista_t *lista = lista_crear();
	int uno = 1, dos = 2, tres = 3;

	lista_insertar(lista, &uno);
	lista_insertar(lista, &dos);
	lista_insertar(lista, &tres);

	pa2m_afirmar(lista_buscar_posicion(lista, &dos) == 1,
		     "El elemento con valor 2 está en la posición 1");
	pa2m_afirmar(lista_buscar_posicion(lista, &tres) == 2,
		     "El elemento con valor 3 está en la posición 2");
	pa2m_afirmar(lista_buscar_posicion(lista, &uno) == 0,
		     "El elemento con valor 1 está en la posición 0");
	pa2m_afirmar(lista_buscar_posicion(lista, NULL) == -1,
		     "No se pudo encontrar un elemento NULL");

	lista_destruir(lista);
	pa2m_afirmar(true, "Se destruyó la lista correctamente");
}

bool es_mayor_a(void *dato, void *umbral)
{
	return *(int *)dato > *(int *)umbral;
}

void prueba_buscar()
{
	pa2m_nuevo_grupo(
		"Pruebas de búsqueda de un elemento según un criterio");

	lista_t *lista = lista_crear();
	int uno = 1, dos = 2, tres = 3, umbral = 2, umbral_mayor = 4;

	lista_insertar(lista, &uno);
	lista_insertar(lista, &dos);
	lista_insertar(lista, &tres);

	pa2m_afirmar(*(int *)lista_buscar(lista, es_mayor_a, &umbral) == 3,
		     "Se encontró el primer elemento mayor al umbral 2");
	pa2m_afirmar(lista_buscar(lista, es_mayor_a, &umbral_mayor) == NULL,
		     "No se encontró ningún elemento mayor al umbral 4");

	lista_destruir(lista);
	pa2m_afirmar(true, "Se destruyó la lista correctamente");
}

bool mostrar_elemento(void *elemento, void *contexto)
{
	printf("Elemento: %i\n", *(int *)elemento);
	int *contador = contexto;
	(*contador)++;
	return true;
}

void prueba_iterar()
{
	pa2m_nuevo_grupo("Pruebas de iteración sobre la lista");

	lista_t *lista = lista_crear();
	int uno = 1, dos = 2, tres = 3, contador = 0;

	lista_insertar(lista, &uno);
	lista_insertar(lista, &dos);
	lista_insertar(lista, &tres);

	pa2m_afirmar(lista_iterar(lista, mostrar_elemento, &contador) == 3,
		     "Se iteraron correctamente los 3 elementos de la lista");

	lista_destruir(lista);
	pa2m_afirmar(true, "Se destruyó la lista correctamente");
}

void prueba_pila_crear()
{
	pa2m_nuevo_grupo("Pruebas de creación de la pila");

	pila_t *pila = pila_crear();
	pa2m_afirmar(pila != NULL, "Se pudo crear una pila vacía");
	pa2m_afirmar(pila_vacia(pila),
		     "La pila está vacía después de ser creada");

	pila_destruir(pila);
	pa2m_afirmar(true, "Se destruyó la pila correctamente");
}

void prueba_pila_apilar()
{
	pa2m_nuevo_grupo("Pruebas de apilar elementos en la pila");

	pila_t *pila = pila_crear();
	pa2m_afirmar(pila != NULL, "Se pudo crear una pila vacía");

	int uno = 1, dos = 2, tres = 3;

	pa2m_afirmar(pila_apilar(pila, &uno),
		     "Se pudo apilar el primer elemento (1)");
	pa2m_afirmar(pila_apilar(pila, &dos),
		     "Se pudo apilar el segundo elemento (2)");
	pa2m_afirmar(pila_apilar(pila, &tres),
		     "Se pudo apilar el tercer elemento (3)");
	pa2m_afirmar(!pila_vacia(pila),
		     "La pila no está vacía después de apilar elementos");
	pa2m_afirmar(pila_tamanio(pila) == 3,
		     "La pila tiene 3 elementos después de apilar");

	pila_destruir(pila);
	pa2m_afirmar(true, "Se destruyó la pila correctamente");
}

void prueba_pila_desapilar()
{
	pa2m_nuevo_grupo("Pruebas de desapilar elementos de la pila");

	pila_t *pila = pila_crear();
	pa2m_afirmar(pila != NULL, "Se pudo crear una pila vacía");

	int uno = 1, dos = 2, tres = 3;

	pila_apilar(pila, &uno);
	pila_apilar(pila, &dos);
	pila_apilar(pila, &tres);

	pa2m_afirmar(*(int *)pila_desapilar(pila) == 3,
		     "Se desapiló el elemento 3 (último apilado)");
	pa2m_afirmar(*(int *)pila_desapilar(pila) == 2,
		     "Se desapiló el elemento 2");
	pa2m_afirmar(*(int *)pila_desapilar(pila) == 1,
		     "Se desapiló el elemento 1");
	pa2m_afirmar(pila_desapilar(pila) == NULL,
		     "No se pudo desapilar de una pila vacía");
	pa2m_afirmar(
		pila_vacia(pila),
		"La pila está vacía después de desapilar todos los elementos");

	pila_destruir(pila);
	pa2m_afirmar(true, "Se destruyó la pila correctamente");
}

void prueba_pila_vacia()
{
	pa2m_nuevo_grupo("Pruebas para pila_vacia");

	pila_t *pila = pila_crear();
	pa2m_afirmar(pila_vacia(pila),
		     "La pila está vacía después de ser creada");

	int uno = 1;
	pila_apilar(pila, &uno);
	pa2m_afirmar(!pila_vacia(pila),
		     "La pila no está vacía después de apilar un elemento");

	pila_desapilar(pila);
	pa2m_afirmar(
		pila_vacia(pila),
		"La pila está vacía después de desapilar el único elemento");

	pila_destruir(pila);
	pa2m_afirmar(true, "Se destruyó la pila correctamente");
}

void prueba_pila_tamanio()
{
	pa2m_nuevo_grupo("Pruebas para pila_tamanio");

	pila_t *pila = pila_crear();
	pa2m_afirmar(pila_tamanio(pila) == 0,
		     "El tamaño de la pila es 0 después de ser creada");

	int uno = 1, dos = 2, tres = 3;

	pila_apilar(pila, &uno);
	pa2m_afirmar(pila_tamanio(pila) == 1,
		     "El tamaño de la pila es 1 después de apilar un elemento");

	pila_apilar(pila, &dos);
	pila_apilar(pila, &tres);
	pa2m_afirmar(
		pila_tamanio(pila) == 3,
		"El tamaño de la pila es 3 después de apilar tres elementos");

	pila_desapilar(pila);
	pa2m_afirmar(
		pila_tamanio(pila) == 2,
		"El tamaño de la pila es 2 después de desapilar un elemento");

	pila_destruir(pila);
	pa2m_afirmar(true, "Se destruyó la pila correctamente");
}

void prueba_pila_tope()
{
	pa2m_nuevo_grupo("Pruebas para pila_tope");

	pila_t *pila = pila_crear();
	pa2m_afirmar(pila_tope(pila) == NULL,
		     "El tope de una pila vacía es NULL");

	int uno = 1, dos = 2;

	pila_apilar(pila, &uno);
	pa2m_afirmar(*(int *)pila_tope(pila) == 1,
		     "El tope de la pila es 1 después de apilar 1");

	pila_apilar(pila, &dos);
	pa2m_afirmar(*(int *)pila_tope(pila) == 2,
		     "El tope de la pila es 2 después de apilar 2");

	pila_desapilar(pila);
	pa2m_afirmar(
		*(int *)pila_tope(pila) == 1,
		"El tope de la pila vuelve a ser 1 después de desapilar 2");

	pila_desapilar(pila);
	pa2m_afirmar(pila_tope(pila) == NULL,
		     "El tope de una pila vacía vuelve a ser NULL");

	pila_destruir(pila);
	pa2m_afirmar(true, "Se destruyó la pila correctamente");
}

void prueba_pila_destruir()
{
	pa2m_nuevo_grupo("Pruebas para pila_destruir");

	pila_t *pila = pila_crear();
	pa2m_afirmar(pila != NULL, "Se pudo crear una pila vacía");

	int uno = 1, dos = 2, tres = 3;
	pila_apilar(pila, &uno);
	pila_apilar(pila, &dos);
	pila_apilar(pila, &tres);

	pa2m_afirmar(pila_tamanio(pila) == 3,
		     "La pila tiene 3 elementos antes de destruirla");

	pila_destruir(pila);
	pa2m_afirmar(true, "Se destruyó la pila correctamente");
}

void prueba_cola_crear()
{
	pa2m_nuevo_grupo("Pruebas de creación de la cola");

	cola_t *cola = cola_crear();
	pa2m_afirmar(cola != NULL, "Se pudo crear una cola vacía");
	pa2m_afirmar(cola_vacia(cola),
		     "La cola está vacía después de ser creada");

	cola_destruir(cola);
	pa2m_afirmar(true, "Se destruyó la cola correctamente");
}

void prueba_cola_encolar()
{
	pa2m_nuevo_grupo("Pruebas de encolar elementos en la cola");

	cola_t *cola = cola_crear();
	pa2m_afirmar(cola != NULL, "Se pudo crear una cola vacía");

	int uno = 1, dos = 2, tres = 3;

	pa2m_afirmar(cola_encolar(cola, &uno),
		     "Se pudo encolar el primer elemento (1)");
	pa2m_afirmar(cola_encolar(cola, &dos),
		     "Se pudo encolar el segundo elemento (2)");
	pa2m_afirmar(cola_encolar(cola, &tres),
		     "Se pudo encolar el tercer elemento (3)");
	pa2m_afirmar(!cola_vacia(cola),
		     "La cola no está vacía después de encolar elementos");
	pa2m_afirmar(cola_tamanio(cola) == 3,
		     "La cola tiene 3 elementos después de encolar");

	cola_destruir(cola);
	pa2m_afirmar(true, "Se destruyó la cola correctamente");
}

void prueba_cola_desencolar()
{
	pa2m_nuevo_grupo("Pruebas de desencolar elementos de la cola");

	cola_t *cola = cola_crear();
	pa2m_afirmar(cola != NULL, "Se pudo crear una cola vacía");

	int uno = 1, dos = 2, tres = 3;

	cola_encolar(cola, &uno);
	cola_encolar(cola, &dos);
	cola_encolar(cola, &tres);

	pa2m_afirmar(*(int *)cola_desencolar(cola) == 1,
		     "Se desencoló el elemento 1 (primer encolado)");
	pa2m_afirmar(*(int *)cola_desencolar(cola) == 2,
		     "Se desencoló el elemento 2");
	pa2m_afirmar(*(int *)cola_desencolar(cola) == 3,
		     "Se desencoló el elemento 3");
	pa2m_afirmar(cola_desencolar(cola) == NULL,
		     "No se pudo desencolar de una cola vacía");
	pa2m_afirmar(
		cola_vacia(cola),
		"La cola está vacía después de desencolar todos los elementos");

	cola_destruir(cola);
	pa2m_afirmar(true, "Se destruyó la cola correctamente");
}

void prueba_cola_vacia()
{
	pa2m_nuevo_grupo("Pruebas para cola_vacia");

	cola_t *cola = cola_crear();
	pa2m_afirmar(cola_vacia(cola),
		     "La cola está vacía después de ser creada");

	int uno = 1;
	cola_encolar(cola, &uno);
	pa2m_afirmar(!cola_vacia(cola),
		     "La cola no está vacía después de encolar un elemento");

	cola_desencolar(cola);
	pa2m_afirmar(
		cola_vacia(cola),
		"La cola está vacía después de desencolar el único elemento");

	cola_destruir(cola);
	pa2m_afirmar(true, "Se destruyó la cola correctamente");
}

void prueba_cola_tamanio()
{
	pa2m_nuevo_grupo("Pruebas para cola_tamanio");

	cola_t *cola = cola_crear();
	pa2m_afirmar(cola_tamanio(cola) == 0,
		     "El tamaño de la cola es 0 después de ser creada");

	int uno = 1, dos = 2;

	cola_encolar(cola, &uno);
	pa2m_afirmar(
		cola_tamanio(cola) == 1,
		"El tamaño de la cola es 1 después de encolar un elemento");

	cola_encolar(cola, &dos);
	pa2m_afirmar(
		cola_tamanio(cola) == 2,
		"El tamaño de la cola es 2 después de encolar dos elementos");

	cola_desencolar(cola);
	pa2m_afirmar(
		cola_tamanio(cola) == 1,
		"El tamaño de la cola es 1 después de desencolar un elemento");

	cola_destruir(cola);
	pa2m_afirmar(true, "Se destruyó la cola correctamente");
}

void prueba_cola_frente()
{
	pa2m_nuevo_grupo("Pruebas para cola_frente");

	cola_t *cola = cola_crear();
	pa2m_afirmar(cola_frente(cola) == NULL,
		     "El frente de una cola vacía es NULL");

	int uno = 1, dos = 2;

	cola_encolar(cola, &uno);
	pa2m_afirmar(*(int *)cola_frente(cola) == 1,
		     "El frente de la cola es 1 después de encolar 1");

	cola_encolar(cola, &dos);
	pa2m_afirmar(
		*(int *)cola_frente(cola) == 1,
		"El frente de la cola sigue siendo 1 después de encolar 2");

	cola_desencolar(cola);
	pa2m_afirmar(*(int *)cola_frente(cola) == 2,
		     "El frente de la cola es ahora 2 después de desencolar 1");

	cola_destruir(cola);
	pa2m_afirmar(true, "Se destruyó la cola correctamente");
}

void prueba_cola_destruir()
{
	pa2m_nuevo_grupo("Pruebas para cola_destruir");

	cola_t *cola = cola_crear();
	pa2m_afirmar(cola != NULL, "Se pudo crear una cola vacía");

	int uno = 1, dos = 2;
	cola_encolar(cola, &uno);
	cola_encolar(cola, &dos);

	pa2m_afirmar(cola_tamanio(cola) == 2,
		     "La cola tiene 2 elementos antes de destruirla");

	cola_destruir(cola);
	pa2m_afirmar(true, "Se destruyó la cola correctamente");
}

int main()
{
	pa2m_nuevo_grupo("============== ??? ===============");
	printf("Pruebas de lista\n");
	prueba_simple();
	prueba_creacion_lista();
	prueba_insertar_en_lista_vacia();
	prueba_insertar_en_posicion();
	prueba_obtener_elemento();
	prueba_sacar_de_posicion();
	prueba_sacar_elemento();
	prueba_buscar_posicion();
	prueba_buscar();
	prueba_iterar();
	printf("Pruebas de pila\n");
	prueba_pila_crear();
	prueba_pila_apilar();
	prueba_pila_desapilar();
	prueba_pila_vacia();
	prueba_pila_tamanio();
	prueba_pila_tope();
	prueba_pila_destruir();
	printf("Pruebas de cola");
	prueba_cola_crear();
	prueba_cola_encolar();
	prueba_cola_desencolar();
	prueba_cola_vacia();
	prueba_cola_tamanio();
	prueba_cola_frente();
	prueba_cola_destruir();

	return pa2m_mostrar_reporte();
}
