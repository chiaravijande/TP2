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

	-Se decidió modificar la función lista_sacar_elemento, ya que inicialmente contenía la condición if (!lista || !elemento) return NULL al inicio, lo que impedía procesar elementos NULL. Sin embargo, era necesario permitir que se busquen y eliminen nodos que contienen valores NULL en la lista. Por este motivo, se ajustó la condición para que sea if (!lista) return NULL, permitiendo que los nodos con valores NULL sean correctamente procesados y eliminados.


En el siguiente diagrama, se puede ver el funcionamiento de cómo se crea la lista, y su inserción de elementos:

<div align="center">
<img width="70%" src="img/funcionamiento principal de lista.png">
</div>

Este diagrama refleja a grandes rasgos lo que hacen las siguientes funciones principales:

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

En el archivo lista.c la función lista_crear solicita al heap un espacio suficiente para almacenar una estructura lista_t, esto se hace particularmente con la siguiente línea:

lista_t *lista = malloc(sizeof(lista_t));

El tamaño de este espacio se calcula con sizeof(lista_t). 
 Si la solicitud de memoria es exitosa, malloc devuelve la dirección del espacio reservado en el heap, y esta dirección se almacena en el puntero lista (ubicado en el stack).

Este proceso se puede ver en el siguiente diagrama de memoria:

<div align="center">
<img width="70%" src="img/diagrama de memoria de lista_crear.png">
</div>

					Explicación de la implementación de las funciones principales en lista.c

- lista_crear() :
  Se diseñó para inicializar correctamente una lista vacía, asegurando que esté en un estado válido antes de realizar cualquier operación sobre ella.
  Se utiliza malloc para asignar dinámicamente memoria en el heap para la estructura lista_t. Esto permite que la lista persista más allá del alcance local de la función y pueda ser utilizada en otras partes del programa.
  Si la memoria no puede ser asignada, la función retorna NULL, señalando que la creación de la lista falló. Este chequeo asegura robustez y evita problemas como accesos inválidos a memoria. En cambio, si la memoria pudo ser asignada, la función retorna un puntero a la nueva lista creada, permitiendo que el usuario o las funciones que la invoquen trabajen con una lista correctamente inicializada.

- lista_insertar() :
  Se diseñó para insertar un elemento al final de una lista simplemente enlazada. Su implementación asegura que la operación sea eficiente y adaptable, incluso cuando la lista está vacía. 
  La función verifica que la lista existe antes de continuar. Esto previene accesos inválidos a memoria y asegura robustez en caso de que el puntero sea NULL. Una vez realizada la verificación, y en caso de que la lista exista, se utiliza malloc para asignar memoria dinámica para el nodo que contendrá el nuevo elemento. Si la asignación falla (por ejemplo, por falta de memoria), la función retorna false. Luego, se configura el nuevo nodo para que almacene el elemento y apunte a NULL. Esto es esencial para que el nodo sea correctamente integrado como el último elemento de la lista.
  Si la lista está vacía, tanto primero como último se actualizan para apuntar al nuevo nodo, ya que es el único elemento de la lista.
  Si la lista ya tiene elementos, el puntero próximo del nodo que actualmente es el último se actualiza para apuntar al nuevo nodo, y el puntero ultimo de la lista se actualiza para que apunte al nuevo nodo. Después, se incrementa el contador de elementos de la lista, reflejando que ahora contiene un elemento adicional.
  Y por último, la función retorna true indicando que la operación se realizó con éxito.

-lista_insertar_en_posicion() :
  Se diseñó para insertar un elemento en una posición específica dentro de una lista simplemente enlazada, permitiendo flexibilidad para trabajar con listas dinámicas.
  Primero, se verifica que la lista exista y que la posición sea válida (dentro de los límites de la lista). Luego, se utiliza malloc para asignar espacio en el heap para un nuevo nodo. Si la reserva falla (por ejemplo, por falta de memoria), la función retorna false. El nodo se configura con el elemento proporcionado por el usuario.
  Después, se realiza la inserción en la posición especificada, según sea el caso.
  En el primer caso, donde la posición es 0, el nuevo nodo apunta al antiguo primer nodo (lista->primero) y pasa a ser el nuevo primer nodo. Si la lista estaba vacía, lista->ultimo también se actualiza para apuntar al nuevo nodo.
  En el segundo caso, donde se quiere insertar en posiciones intermedias, se recorre la lista hasta el nodo anterior a la posición de inserción. El nuevo nodo se inserta ajustando los punteros: nuevo_nodo->proximo apunta al siguiente nodo, y actual->proximo apunta al nuevo nodo.
  Y en el tercer caso, donde se quiere insertar en la última posición, se sigue los mismos pasos que el paso anterior, pero lista->ultimo se actualiza para apuntar al nuevo nodo.
  Una vez realizada la inserción, se incrementa el contador, reflejando el nuevo tamaño de la lista, y la función retorna true indicando que la inserción fue exitosa.

- lista_obtener_elemento() :
  Se creó para recuperar un elemento almacenado en una lista simplemente enlazada en una posición específica.
  Primero, se verifica que la lista exista y que la posición proporcionada sea válida. En caso de que alguna de las dos afirmaciones sean falsas, la función retorna NULL. 
  Para el recorrido, se inicia con el primer nodo (lista->primero) y un bucle recorre la lista avanzando a través del puntero proximo en cada iteración, hasta alcanzar la posición deseada. Una vez alcanzado el nodo en la posición deseada, la función retorna el contenido del campo dato del nodo.

- lista_sacar_de_posicion() :
  Está diseñada para eliminar un nodo de la lista en una posición específica y devolver su valor.
  Primero, se verifica que la lista exista y que la posición proporcionada sea válida. Si alguna de estas condiciones no se cumple, se retorna NULL, indicando que no se puede eliminar el elemento.
  Si el nodo a eliminar es el primero, el puntero primero de la lista se actualiza para apuntar al siguiente nodo, y si el nodo eliminado era el único en la lista, ultimo también se actualiza a NULL. 
  Si el nodo a eliminar está en otras posiciones, un bucle recorre la lista hasta el nodo anterior a la posición deseada. El puntero proximo del nodo anterior se actualiza para saltar el nodo a eliminar, conectándolo con el siguiente. Y si el nodo eliminado era el último, ultimo se actualiza para apuntar al nuevo último nodo.
  Luego, el nodo eliminado se libera para evitar fugas de memoria, y el tamaño de la lista se decrementa, reflejando el cambio en su estructura.
  Finalmente, la función retorna el valor almacenado en el nodo eliminado, permitiendo que sea reutilizado por el usuario.

- lista_sacar_elemento() :
  Se diseñó para eliminar de una lista simplemente enlazada un nodo que contiene un valor específico.
  Primero, la función verifica que la lista existe y que contiene elementos antes de intentar realizar la operación. Si cualquiera de estas condiciones falla, se retorna NULL, indicando que el nodo no pudo ser eliminado.
  Si el nodo a eliminar es el primero de la lista, el puntero lista->primero se actualiza para apuntar al siguiente nodo (nodo_a_eliminar->proximo). Si el nodo eliminado era el único en la lista, el puntero lista->ultimo también se actualiza a NULL.
  Luego, se recorre la lista desde el primer nodo hasta el último en busca del nodo que contiene el dato igual a elemento. Si el nodo no se encuentra, la función retorna NULL.
  Una vez encontrado el nodo, se desconecta de la lista ajustando los punteros: el puntero proximo del nodo anterior (actual) se actualiza para saltar el nodo a eliminar y apuntar al siguiente. Si el nodo eliminado era el último, lista->ultimo se actualiza para apuntar al nuevo último nodo.
  El nodo eliminado se libera para evitar fugas de memoria,y el contador lista->cantidad se decrementa, reflejando correctamente el nuevo tamaño de la lista.
  Por último, la función retorna el valor almacenado en el nodo eliminado, permitiendo su reutilización o análisis por parte del usuario.

- lista_buscar_posicion() :
  Se diseñó para encontrar la posición de un elemento en una lista simplemente enlazada. Devuelve un índice basado en cero si el elemento existe o -1 si no está presente. La función verifica que la lista existe y no está vacía antes de comenzar la búsqueda, retornando -1 si alguna de estas condiciones no se cumple.
  Luego, se comienza la búsqueda desde el primer nodo, usando el puntero lista->primero, y se inicializa la variable posicion en 0 para registrar el índice del nodo actual durante la iteración.
  Para el recorrido, se utiliza un bucle while para recorrer cada nodo de la lista hasta encontrar el elemento o llegar al final de la lista. En cada iteración, se compara actual->dato con el elemento buscado.
  Si coinciden, se retorna el valor de posicion, indicando el índice del nodo donde se encontró el elemento. Si no coinciden, se avanza al siguiente nodo (actual = actual->proximo) y se incrementa la posición (posicion++).

- lista_buscar() :
  Se diseñó para encontrar la posición de un elemento en una lista simplemente enlazada. Devuelve un índice basado en cero si el elemento existe o -1 si no está presente. La función verifica que la lista existe y no está vacía antes de comenzar la búsqueda, y si alguna de las condiciones no se cumple, se retorna -1 indicando que el elemento no se encuentra en la lista. Se comienza la búsqueda desde el primer nodo, usando el puntero lista->primero, y se inicializa la variable posicion en 0 para registrar el índice del nodo actual durante la iteración. Se utiliza un bucle while para recorrer cada nodo de la lista hasta encontrar el elemento o llegar al final de la lista. En cada iteración, se compara actual->dato con el elemento buscado. Si coinciden, se retorna el valor de posicion, indicando el índice del nodo donde se encontró el elemento. Si no coinciden, se avanza al siguiente nodo (actual = actual->proximo) y se incrementa la posición (posicion++). Si el bucle finaliza sin encontrar el elemento, significa que este no está presente en la lista.

- lista_iterar() :
  Está diseñada para recorrer una lista simplemente enlazada y aplicar una función proporcionada por el usuario a cada elemento. Permite detener la iteración si la función del usuario devuelve false, haciendo que su diseño sea adaptable y versátil. La función verifica que la lista exista (lista != NULL) y que se haya proporcionado una función válida para aplicar (f != NULL). Si alguna de estas condiciones no se cumple, la función retorna 0, indicando que no se realizó ninguna iteración.
  Luego, se inicializa el puntero actual para empezar desde el primer nodo (lista->primero). La variable invocaciones comienza en 0 y lleva el conteo de las veces que se invocó la función proporcionada por el usuario. La variable funcion_verdadera comienza en true y se usa para detener la iteración cuando la función f devuelve false.
  Se itera con un ciclo while: el bucle continúa mientras haya nodos en la lista (actual != NULL) y la función f devuelva true en sus evaluaciones. El puntero actual se mueve al siguiente nodo en cada iteración (actual = actual->proximo), y la variable invocaciones se incrementa en cada paso para reflejar el número total de evaluaciones realizadas.
  Una vez que la iteración se detiene, ya sea porque no hay más nodos o porque la función f devolvió false, se retorna el total de veces que se llamó la función proporcionada (invocaciones).

- lista_destruir() :
  Se diseñó para liberar toda la memoria asociada a una lista simplemente enlazada, asegurando que no queden referencias a nodos o estructuras en el heap. Su implementación tiene como objetivo prevenir fugas de memoria, y garantizar un manejo correcto de recursos.
  Primero, la función verifica si el puntero lista es NULL antes de realizar cualquier operación. Si la lista no existe, no hay nada que destruir, por lo que simplemente retorna. Esto previene accesos inválidos a memoria y errores de ejecución.
  Si la lista existe, se utiliza un bucle para recorrer la lista desde el primer nodo (lista->primero) hasta el último. En cada iteración: se guarda el puntero al siguiente nodo (siguiente = actual->proximo), se libera la memoria del nodo actual (free(actual)) y el puntero actual avanza al siguiente nodo (actual = siguiente). Este enfoque asegura que cada nodo es liberado individualmente, evitando que queden bloques de memoria no utilizados en el heap.
  Una vez que todos los nodos de la lista han sido liberados, se libera la memoria asociada a la estructura lista_t. Esto marca el final de la operación de destrucción, asegurando que no queden referencias a la lista en memoria.

- lista_iterador_crear() :
  Tiene como objetivo inicializar un iterador que permita recorrer una lista simplemente enlazada de manera controlada y personalizada por el usuario. A diferencia de los iteradores internos, que recorren automáticamente la lista bajo control de la propia estructura, un iterador externo permite al usuario decidir cuándo avanzar, detenerse, o realizar acciones personalizadas en cada nodo. A su vez, el diseño permite iterar sobre la lista de diferentes maneras sin modificar la implementación de la lista misma.
  Luego, sus funciones relacionadas se encargan de realizar las siguientes acciones:

    Recorrido controlado: El bucle controla explícitamente el recorrido usando:
	lista_iterador_quedan_elementos_por_recorrer() para verificar si hay más elementos.
	lista_iterador_proxima_iteracion() para avanzar al siguiente nodo.

	Acceso al elemento actual: lista_iterador_obtener_elemento() permite acceder al dato del nodo actual.

	Liberación del iterador: Una vez finalizado el recorrido, el iterador se libera con lista_iterador_destruir().
  

En el siguiente diagrama, se ve cómo se crea una pila reutilizando la función de lista_crear() y cómo se apilan sus elementos reutilizando la función de lista_insertar_en_posicion():

<div align="center">
<img width="70%" src="img/funcionamiento de crear y apilar en pila.png">
</div>

Este diagrama refleja a grandes rasgos lo que hacen las siguientes funciones principales:

pila_t *pila_crear()
{
	pila_t *pila = malloc(sizeof(pila_t));
	if (!pila) {
		return NULL;
	}

	pila->lista = (lista_t *)lista_crear();
	if (!pila->lista) {
		free(pila);
		return NULL;
	}

	return pila;
}

bool pila_apilar(pila_t *pila, void *elemento)
{
	if (!pila || !pila->lista) {
		return false;
	}

	return lista_insertar_en_posicion(pila->lista, 0, elemento);
}

					Explicación de la implementación de las funciones principales en pila.c

- pila_crear():
  Inicializa una nueva pila vacía, reutilizando la estructura de datos de una lista simplemente enlazada para implementar el almacenamiento y manejo de elementos.
  Primero, se utiliza malloc para asignar memoria en el heap para una nueva estructura pila_t. Si la asignación falla, se retorna NULL, indicando que no se pudo crear la pila. 
  Luego, como una pila necesita una estructura para almacenar sus elementos, una lista simplemente enlazada (lista_t) se reutiliza para ese propósito. Si la creación de la lista falla, se libera la memoria de la pila y se retorna NULL. Si todo es exitoso, la función retorna el puntero a la pila creada.

- pila_apilar():
  Reutiliza lista_insertar_en_posicion para agregar un elemento en la posición 0 de la lista. Las inserciones en el inicio de una lista simplemente enlazada ocurren en tiempo constante O(1), ya que no dependen del tamaño de la lista.

- pila_desapilar():
  Reutiliza lista_sacar_de_posicion para eliminar el elemento en la posición 0. La eliminación en la posición 0 no requiere recorrer la lista, por lo que ocurre en tiempo constante O(1).

- pila_vacia():
  Reutiliza lista_tamanio(), y verifica si la lista asociada tiene tamaño 0.

- pila_tamanio():
  También reutiliza lista_tamanio(), para poder devolver el tamaño de la lista.

- pila_tope():
  Reutiliza lista_obtener_elemento para acceder al elemento en la posición 0 sin modificar la lista. Nuevamente, acceder al primer nodo de la lista ocurre en O(1) ya que no se necesita recorrer la lista.

- pila_destruir():
  Destruye la lista subyacente y luego libera la memoria de la pila, reutilizando lista_destruir().

En el siguiente diagrama, se ve cómo se crea una cola reutilizando la función de lista_crear() y cómo se encolan sus elementos reutilizando la función de lista_insertar():

<div align="center">
<img width="70%" src="img/funcionamiento de crear y encolar en cola.png">
</div>

Este diagrama refleja a grandes rasgos lo que hacen las siguientes funciones principales:

cola_t *cola_crear()
{
	cola_t *cola = malloc(sizeof(cola_t));
	if (!cola) {
		return NULL;
	}

	cola->lista = (lista_t *)lista_crear();
	if (!cola->lista) {
		free(cola);
		return NULL;
	}

	return cola;
}

bool cola_encolar(cola_t *cola, void *elemento)
{
	if (!cola || !cola->lista) {
		return false;
	}

	return lista_insertar(cola->lista, elemento);
}

					Explicación de la implementación de las funciones principales en cola.c

- cola_crear():
  Está diseñada para inicializar una nueva cola vacía, reutilizando la estructura de datos de una lista simplemente enlazada como base para su funcionamiento. Se utiliza malloc para reservar memoria en el heap para una nueva estructura cola_t. Si la asignación de memoria falla, se retorna NULL, indicando que no se pudo crear la cola.		
  Luego, si la creación de la lista falla, se libera la memoria de la cola y se retorna NULL.	
  Finalmente, si todo se ejecutó correctamente, se retorna el puntero a la cola creada.

- cola_encolar():
  Reutiliza la función lista_insertar, que agrega un elemento al final de la lista. Y gracias al puntero ultimo de la lista, insertar al final se realiza en O(1).

- *cola_desencolar():
  Reutiliza lista_sacar_de_posicion para eliminar el elemento en la posición 0 (al inicio de la lista).Eliminar el primer nodo de la lista ocurre en O(1), ya que no se tiene que recorrer la lista.

- cola_vacia():
  Se reutiliza la función lista_tamanio() para verificar si la lista asociada tiene tamaño 0.

- cola_tamanio():
  Devuelve el tamaño de la lista asociada reutilizando la función lista_tamanio().

- *cola_frente():
  Reutiliza lista_obtener_elemento para acceder al elemento en la posición 0 (al inicio de la lista) sin modificarla. También la operación ocurre en O(1), debido a que no tiene que recorrer la lista.

- cola_destruir():
  Destruye la lista subyacente, reutilizando lista_destruir, y luego libera la memoria de la cola.

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

En este diagrama se ve de forma clara cuáles son sus diferencias:

  <div align="center">
<img width="70%" src="img/diferencias entre iterador interno y externo.png">
</div>





