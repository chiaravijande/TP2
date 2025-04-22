#include "src/cola.h"
#include "src/lista.h"
#include "src/pila.h"
#include <stdio.h>
#include <stdlib.h>

bool mostrar_int(void *elemento, void *contexto) {
  int *posicion = contexto;

  int *n = (int *)elemento;
  printf("Elemento en posicion %i: %i\n", *posicion, *n);
  (*posicion)++;
  return true;
}

int main(int argc __attribute__((unused)),
         char *argv[] __attribute__((unused))) {
  // Este es el ejemplo que armamos en clase
  // Notar que no incluye ejemplos de cola y pila
  // Si la implementaci�n es correcta, se deber�an mostrar correctamente 3 veces
  // todos los elementos de la lista en el orden en que fueron insertados

  int uno = 1;
  int dos = 2;
  int tres = 3;

  lista_t *l = lista_crear();

  lista_insertar(l, &uno);
  lista_insertar(l, &dos);
  lista_insertar(l, &tres);

  printf("Muestro los elementos usando el iterador interno:\n");
  int posicion = 0;
  lista_iterar(l, mostrar_int, &posicion);

  printf("\nMuestro los elementos usando lista_obtener_elemento:\n");
  for (size_t i = 0; i < lista_tamanio(l); i++) {
    int *n = lista_obtener_elemento(l, i);
    printf("Elemento en posicion %zu: %i\n", i, *n);
  }

  printf("\nMuestro los elementos usando el iterador externo:\n");
  posicion = 0;
  lista_iterador_t *li;
  for (li = lista_iterador_crear(l);
       lista_iterador_quedan_elementos_por_recorrer(li);
       lista_iterador_proxima_iteracion(li)) {
    int *n = lista_iterador_obtener_elemento(li);
    printf("Elemento en posicion %i: %i\n", posicion, *n);
    posicion++;
  }
  lista_iterador_destruir(li);

  lista_destruir(l);

  pila_t *pila = pila_crear();
  pila_apilar(pila, &uno);
  printf("Apilado: %i\n", uno);

  pila_apilar(pila, &dos);
  printf("Apilado: %i\n", dos);

  pila_apilar(pila, &tres);
  printf("Apilado: %i\n", tres);

  pila_destruir(pila);

  cola_t *cola = cola_crear();
  cola_encolar(cola, &uno);
  printf("Encolado: %i\n", uno);

  cola_encolar(cola, &dos);
  printf("Encolado: %i\n", dos);

  cola_encolar(cola, &tres);
  printf("Encolado: %i\n", tres);

  cola_destruir(cola);

  return 0;
}
