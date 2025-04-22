<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA LISTA/PILA/COLA

## Repositorio de Chiara Vijande - 111771 - cvijande@fi.uba.ar

- Para compilar:

gcc -o tp2 tp2.c src/lista.c src/pila.c src/cola.c -I. -I./src -lm

gcc -o pruebas_alumno pruebas_alumno.c src/lista.c src/pila.c src/cola.c -
I. -I./src -lm

- Para ejecutar:

 ./tp2

./pruebas

- Para ejecutar con valgrind:

valgrind --leak-check=full --track-origins=yes ./tp2

valgrind --leak-check=full --track-origins=yes ./pruebas
---
##  Funcionamiento

Este trabajo práctico implementa 3 estructuras de datos: lista simplemente enlazada, pila y cola. Todas las estructuras se desarrollan siguiendo las restricciones especificadas en el enunciado, y particularmente, las implementaciones de apilar, desapilar, tope, encolar, desencolar y frente, cumplen con los criterios de eficiencia requeridos: tener omplejidad O(1). Además, la pila y la cola reutilizan la implementación de la lista, fomentando modularidad y simplicidad en el diseño.

El programa permite interactuar con estas estructuras mediante ejemplos sencillos y pruebas concretas que verifican su correcto funcionamiento. Para validar la memoria dinámica utilizada, el TP se ejecuta con Valgrind, confirmando la ausencia de pérdidas de memoria.

-Lista simplemente enlazada:
La lista es la base para las implementaciones de pila y cola, y está diseñada para almacenar elementos de forma dinámica mediante nodos. Cada nodo almacena un puntero al dato y otro al siguiente nodo, permitiendo un acceso secuencial eficiente.

	Decisiones tomadas:
	-Se optó por una implementación dinámica de nodos para garantizar que la lista pueda crecer o decrecer en tamaño según las necesidades del programa.

	-Las funciones como lista_crear, lista_insertar, lista_sacar_de_posicion, lista_tamanio y lista_destruir ofrecen la base para realizar operaciones eficientes.


En el siguiente diagrama, se puede ver el funcionamiento de cómo se crea la lista, y su inserción de elementos:

<div align="center">
<img width="70%" src="img/funcionamiento principal de lista.png">
</div>

Este diagrama refleja a grandes rasgos lo que hacen las siguientes funciones principales:

lista_t *lista_crear() {
  lista_t *lista = malloc(sizeof(lista_t));
  if (!lista) {
    return NULL;
  }

  lista->primero = NULL;
  lista->ultimo = NULL;
  lista->cantidad = 0;

  return lista;
}

bool lista_insertar(lista_t *lista, void *elemento) {
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

bool lista_insertar_en_posicion(lista_t *lista, int posicion, void *elemento) {
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

En el siguiente diagrama, se ve cómo se crea una pila reutilizando la función de lista_crear() y cómo se apilan sus elementos reutilizando la función de lista_insertar_en_posicion():

<div align="center">
<img width="70%" src="img/funcionamiento de crear y apilar en pila.png">
</div>

Este diagrama refleja a grandes rasgos lo que hacen las siguientes funciones principales:

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

En el siguiente diagrama, se ve cómo se crea una cola reutilizando la función de lista_crear() y cómo se encolan sus elementos reutilizando la función de lista_insertar():

<div align="center">
<img width="70%" src="img/funcionamiento de crear y encolar en cola.png">
</div>

Este diagrama refleja a grandes rasgos lo que hacen las siguientes funciones principales:

cola_t *cola_crear() {
  cola_t *cola = malloc(sizeof(cola_t));
  if (!cola) {
    return NULL;
  }

  cola->lista = lista_crear();
  if (!cola->lista) {
    free(cola);
    return NULL;
  }

  return cola;
}

bool cola_encolar(cola_t *cola, void *elemento) {
  if (!cola || !cola->lista) {
    return false;
  }

  return lista_insertar(cola->lista, elemento);
}

## Respuestas a las preguntas teóricas

											¿Qué es una lista?
Una lista es una estructura de datos abstracta que organiza elementos en una secuencia lineal. Cada elemento de la lista tiene una posición definida y puede ser accedido o manipulado dependiendo del tipo de lista y su implementación. Las listas son muy flexibles y permiten operaciones como:

Inserción de elementos.

Eliminación de elementos.

Recorrido para buscar o procesar elementos.

Existen distintos tipos de listas dependiendo de cómo se almacenan los datos y cómo están enlazados, como listas simplemente enlazadas, doblemente enlazadas y circulares:

-Lista simplemente enlazadas:

Es una estructura lineal donde los elementos (o nodos) están conectados mediante punteros. Cada nodo contiene dos partes:

Dato: El valor almacenado (puede ser un entero, una estructura, etc.).

Enlace: Un puntero que conecta el nodo con el siguiente en la secuencia.

Características:
El primer nodo se llama cabeza.

El último nodo apunta a NULL, indicando el final de la lista.

Solo permite recorrer la lista en una dirección (de la cabeza al último nodo).

Diagrama de su estructura:

<div align="center">
<img width="70%" src="img/listas simplemente enlazadas.png">
</div>

-Lista doblemente enlazada:

es similar a la lista simplemente enlazada, pero cada nodo contiene un enlace al nodo siguiente y otro al nodo anterior.

Características:
Los nodos tienen dos enlaces:

Siguiente: Apunta al nodo que sigue en la secuencia.

Anterior: Apunta al nodo previo en la secuencia.

Permite recorrer la lista en ambas direcciones (hacia adelante o hacia atrás).

Diagrama de su estructura:

<div align="center">
<img width="70%" src="img/lista doblemente enlazada.png">
</div>


								Ventajas y desventajas de cada una
-Lista Enlazada:
	Ventajas:

	Uso de memoria reducido.
	Inserción y eliminación eficientes en posiciones intermedias o al inicio.

	Desventajas:

	No permite recorrer hacia atrás.
	El acceso a elementos es secuencial (no hay índices como en los arrays).

Lista Doblemente Enlazada:
	Ventajas:

	Permite recorrer en ambas direcciones.
	Facilita la eliminación de nodos sin tener que recorrer toda la lista.

	Desventajas:

	Mayor uso de memoria debido al segundo puntero.
	Inserción y eliminación son más costosas porque se deben ajustar 2 punteros.

-Lista circular:
Es una lista enlazada (simple o doble) en la que el último nodo apunta al primero, creando un ciclo.

Características:
No tiene un nodo final que apunte a NULL.

Es útil para implementar estructuras como colas circulares.

Puede ser simplemente enlazada o doblemente enlazada.

Maneras de implementarla:

Lista circular simplemente enlazada:

El puntero siguiente del último nodo apunta al primer nodo.

Diagrama de su estructura:

<div align="center">
<img width="70%" src="img/lista circular simplemente enlazada.png">
</div>


Lista circular doblemente enlazada:

El puntero siguiente del último nodo apunta al primero.

El puntero anterior del primer nodo apunta al último.

Diagrama de su estructura:

<div align="center">
<img width="70%" src="img/lista circular doblemente enlazada.png">
</div>

								Diferencia de funcionamiento entre cola y pila.

Una cola funciona siguiendo el principio FIFO (First In, First Out), lo que quiere decir que el primer elemento en entrar es el primero en salir.
  Por su parte, una pila sigue el principio LIFO (Last In, First Out), o sea, el último elemento en entrar es el primero en salir.

  En este diagrama se ve de forma clara cuáles son sus diferencias:

  <div align="center">
<img width="70%" src="img/diferencia de funcionamiento entre cola y pila.png">
</div>

  								Diferencia entre un iterador interno y uno externo.

Un iterador interno controla la iteración desde dentro de la estructura de datos, lo que significa que es la propia estructura la que define cómo recorrer sus elementos. El usuario no tiene control directo sobre el proceso de iteración, pero simplemente proporciona una función de callback para ejecutar alguna acción en cada elemento a medida que se va iterando. 
  Por su parte, un iterador externo permite al usuario controlar explícitamente el proceso de iteración. El iterador externo es un objeto que el usuario manipula directamente, decidiendo cuándo y cómo avanzar entre los elementos.





