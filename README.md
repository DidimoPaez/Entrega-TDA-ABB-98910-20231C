# TDA ABB

## Repositorio de Dídimo Páez - 98910 - didimo_paez@hotmail.com

- Para compilar:

```bash
gcc --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g src/*.c -o ejecutable
```

- Para ejecutar:

```bash
./ejecutable
```

- Para ejecutar con valgrind:
```bash
valgrind ./ejecutable
```
---
##  Funcionamiento

- En la función "abb_recorrer" se decidió implementar el struct: vector_tope_tamanio_t vector_estructura, el cual en sus campos contendría el vector a llenar (recibido por parámetro), el valor del tope y la cantidad máxima que dicho array puede almacenar (tamanio_array); todo ello para poder reutilizar la función "abb_con_cada_elemento", la cual recorre todo el árbol con cada uno de sus elemetos según el orden previamente especificado (INOINORDEN, PREORDEN, POSTORDENRDEN), evitando de esta manera la repetición de código a través del programa.

- En la función abb_eliminar, para el caso en el que el elemento que se haya decidido extraer tuviera dos hijos, se decidió generar una función extra ("busqueda_predecesor_inorden"), que realizara dicho reacomodamiento en la posición del elemento predecesor inorden, devolviendo de esta manera al hijo izquierdo correspondiente su "rama" reacondicionada y actualizando con puntero pasado por parámetro el valor del predecesor inorden, para poder luego reemplazar dicho valor por el valor del elemento a eliminar.

En dicha función también se realiza la liberación de memoria del nodo perteneciente al predecesor inorden, para que de esta manera no se genere perdida de memoria.

- En la función "abb_insertar" se decide crear un nuevo nodo con el elemento a ingresar antes de llamar a la función recursiva haciendo: "nodo_abb_t *nuevo_nodo = nodo_crear(elemento);".

De esta manera se tiene de forma más directa el nodo para ser cargado en la respectiva finalización del llamado recursivo en el momento en el que se tenga que no hay una raiz siguiente para realizar la respectiva comparación y por lo tanto ese sea el lugar para ingresar al nuevo elemento.

- A resaltar se tiene que la mayoría de las funciones implementadas en el trabajo son de forma recursiva, y se decidieron implementar de esta manera por la manera en la que se hacen los recorridos y operaciones dentro del árbol, ya que se tiene que se debe ir desde un nodo con hojas hasta la raiz (y/o viceversa), e implementar operaciones en el medio, y simplemente señalando bien los recorridos se tendrá un manejo óptimo y claro de lo que se debe llevar a cabo; sin embargo, eso no indica que la implementación no se pueda llevar a cabo de manera iterativa, y para ello como ejemplo se decidió resolver la función "abb_buscar" de dicha forma. Sin embargo es relevante mencionar que algunas funciones como la "abb_quitar" hubiese sido mucho más compleja de implementar de manera iterativa que de forma recursiva.


## Respuestas a las preguntas teóricas

Definición de árbol:
Es un TDA (Tipo de dato abstracto), en el que se almacena determinada información de manera que cuenta con una raiz (elemento inicial), y a partir de allí se empezarán a generar diversas ramificaciones en las que se irá almacenando los demás datos; idealmente se espera que cada elemento del árbol tenga una relación lógica entre si con los demás elementos(sin embargo no es impedimento para su implementación), debiendo concordar minimamente los tipos de dato que se tienen en el mismo. De esta forma se tienen distintos tipos de árboles y todos ellos con características específicas según su sea su implementación, algunos de ellos son: arboles enearios, árboles binarios, arboles binarios de búsqueda, árboles AVL, árboles Rojo/ Negro, heap binario, árboles B, entre otros.

En cuanto a su implementación puede variar ampliamente e ir desde un vector estático, vector dinámico o implementación con nodos, cada uno con determinado beneficio según sea el tipo de árbol a implementar.

Operaciones básicas:
- Crear árbol:
    Se realizará reservando la memoria necesaria para almacenar la estructura del TDA árbol, e inicializando todos sus campos de manera apropiada.

- Insertar elemento:
    Básicamente como en todas las funciones esenciales del TDA árbol esta dependerá de la implementación que se esté ejecutando, con la cual se pueden llegar a tener complejidades por ejemplo que sean O(log(n)), como en el caso del Heap Binario (que se ingresa el elemento en el tope de elementos del árbol y dependiendo del valor del elemento el "peor caso" sería uno en el que deben de hacerse swaps hasta llegar a la raiz del árbol), sin embargo en el mejor de los casos puede llegar a ser O(1), o se puede dar el caso de tener una inserción O(log(n)).

    Según sea el tipo de árbol usado puede variar e ir desde O(n) (para un árbol sin orden específico, teniendo que recorrer todo el árbol como peor caso), u O(log(n)) en el que se puede llegar a tener este resultado si el árbol presenta un cierto tipo de orden, o incluso algunos casos especialies en los que si sólo se requiere por ejemplo obtener el valor máximo o mínimo contenido en el árbol puede llegar a ser O(1) (como es el caso del Heap Binario) 
    
-   Extraer elemento:
    Nuevamente este dependerá del tipo de implementación llevada a cabo, con lo cual puede darse de tener una extracción que sea O(1) como en el caso de un mínimo o un máximo para un Heap Binario, un O(n) en el caso de que el árbol no presente ningún tipo de orden específico, un O(log(n)) para árboles que se encuentren ordenados.

-   Buscar elemento:
    Si el árbol no presenta ningún tipo de orden específico puede tenerse que se puede llegar a buscar en todo el árbol hasta encontrar al elemento, o de estar ordenado el árbol puede llegar a tener una complejidad O(log(n)) para el caso en el que el árbol se encuentre balanceado u O(n) si el árbol se encuentra degenerado en lista.

-   Tamaño del árbol:
    Aunque no es esencial el saber el tamaño del árbol, este resulta bastante útil para llevar a cabo diversas operaciones internas dentro del mismo árbol, como por ejemplo en el Heap binario para carcular la ubicación del ultimo nodo que tenga al menos un hijo, o mismo para llevar un control de la cantidad de los elementos contenidos en el árbol.

-   Destruir árbol:
    Según sea la implementación del TDA se puede dar que por ejemplo si se trata de un vector se puede llegar a tener una complejidad para la destrucción de O(1) siendo necesario simplemente la liberación de memoria de la primer dirección de memoria del árbol, con lo cuál se estaría liberando toda la memoria de cada posición del árbol; o en el caso de tener por ejemplo una implementación con nodos, será necesario que se libere nodo por nodo para no incurrir en pérdida de memoria, con lo cual se tendrá una complejidad que será O(n).


Definición de árbol binario (AB):
    Es un tipo de TDA árbol mediante el cual se tiene que cada ramificación generada a partir de una raíz será de dos, con lo cual se tiene la respectiva bifurcación binaria. No necesariamente puede tener un orden específico, con lo cual se tiene que la complejidad de sus operaciones variará en torno al orden que tenga el mismo y a la subsecuente implementación que se tenga.

Operaciones básicas:
-   Crear árbol:
    Se realizará reservando la memoria necesaria para almacenar la estructura del TDA árbol, e inicializando todos sus campos de manera apropiada.

-   Insertar elemento:
    Su complejidad puede llegar a ser O(1) como en el caso de un Heap Binario en el mejor de los casos, o un O(log(n)) para un árbol balanceado, o incluso O(n) si por ejemplo el árbol degeneró en lista.

-   Extraer elemento:
    Al no tener necesariamente un orden entre sus elementos se tiene que la complejidad para esta operación puede llegar a ser hasta de O(n), con lo cual se tendría que tanto para buscar como para extraer un determinado elemento puede llegar a recorrerse todo el árbol antes de encontrar o no al elemento.

-   Buscar elemento:
    Idem que para el tipo de operación anterior.

-   Tamaño del árbol.

-   Destruir árbol:
    Puede llegar a variar su complejidad según sea su implementación, siendo exactamente del mismo tipo que lo explicado anteriormente para la destrucción de un "arbol".
    

Definición de árbol binario de búsqueda (ABB):
    En este caso a diferencia que en los dos anteriores, acá se tiene que los elementos dentro del TDA conservan un tipo de oren específico, com lo cual se permite mejorar el desempeño en cuanto a complejidades dentro de sus operaciones a realizar.

    Por lo general se lleva a cabo adoptando determinadas convenciones para el desarrollo del mismo, como es el caso de que los elementos menores (o iguales), vayan a izquierda y los mayores lo hagan a derecha (o viceversa).

Operaciones básicas:
-   Crear árbol.
    Se realizará reservando la memoria necesaria para almacenar la estructura del TDA árbol, e inicializando todos sus campos de manera apropiada.

-   Insertar elemento:
    La manera de realizarla es a través de comparaciones, mediante las cuales se irá dirigiendo al elemento a su ubicación correspondiente; el lugar de inserción será siempre en una hoja del árbol.

    Se comienza buscando (comparando), por el elemento raiz y según sea la convención de mayores y menores se continuará haciendolo según corresponda ya sea con el elemento izquierdo o derecho hasta llegar a una hoja en cuyo caso se realizará la respectiva inserción dentro del árbol.
    
    En cuanto a la complejidad se tiene que esta operación es O(log(n)), y la deducción de la misma será casi análoga a la presentada en la siguiente operación (Extraer elemento).

    Acá es importante tener en cuenta (en cuanto a implementación), la convención a adoptar en caso de que un elemento a ingresar sea igual a otro ya existente en el árbol, en cuyo caso se puede elegir que el elemento se ingrese o a derecha o a izquierda del mismo, teniendo que conservar dicha convención a lo largo del programa.

-   Extraer elemento:
    La extracción puede realizarse de cualquier posición del árbol, desde la raiz o cualquiera de los hijos. La manera de realizarse será siguiendo un criterio de búsqueda mediante el cual se va comparando el elemento (comenzando seiempre por la raiz) a eliminar con el elemento que se va "leyendo" actualmente, de esta forma se sabrá en qué sentido irá la busqueda y la subsequente comparación hasta encontrar al respectivo elemento o hasta llegar a una hoja del árbol, caso en el cual no se habrá encontrado el elemento.

    La complejidad de esta operación se tiene que es O(log(n)), pues al estar ordenado siempre se tendrá que en cada nivel del árbol se encontrará descartando la mitad de elementos posibles de busqueda a partir de dicha posición. Lo anterior se puede deducir a partir del teorema maestro (T(n) = A * T(n/B) + f(n)), en el que la operacion recursiva de busqueda del elemento se realiza una vez que se compara al elemento buscado con el elemento actual del árbol (A = 1), luego, en cada llamado recursivo lo que se tiene es que la muestra actual de elementos a evaluar se verá disminuida a la mitad debido al resultado de la comparación(B = 2), dado el caso que el elemento actual no sea el búscado, y en cuanto al f(n) se presenta que se realizan operaciones como la comparación que es O(1) al ser un resultado casi directo o las operaciones de movimiento del hijo izquierdo o derecho(de tenerlo, y según la convención adoptada para el predecesor/sucesor inorden) al momento de extraer al predecesor/sucesor inorden, que también sería O(1), con lo cual el teorema maestro quedaría de la forma:

                                        T(n) = 1 * T(n/2) + O(1)

    Se observa que la parte recursiva tiene mayor relevancia que la parte iterativa (T(n/2) > O(1)), por ende la operación de eliminación para el ABB será  O(log(n)).

    Acá es importante tener en cuenta (en cuanto a implementación), la convención a adoptar en caso de que la raiz a extraer tenga uno o dos hijos (si se adopta predecesor o sucesor inorden, para el caso de una implementación con nodos).

-   Buscar elemento:
    Al igual que en las anteriores operaciones se realiza un método comparativo, de hecho la operación eliminar elemento sigue un criterio de búsqueda para saber si el elemento a eliminar existe o no dentro del árbol. De esta forma se comienza buscando (comparando), por el elemento raiz y según sea la convención de mayores y menores se continuará haciendolo según corresponda ya sea con el elemento izquierdo o derecho hasta encontrar al elemento buscado o hasta llegar a una hoja en cuyo caso no existirá el elemento dentro del árbol.

-   Tamaño del árbol.

-   Destruir árbol:
    Puede llegar a variar su complejidad según sea su implementación, siendo exactamente del mismo tipo que lo explicado anteriormente para la destrucción de un "arbol".
    En el presente trabajo se realiza una implementación para el árbol (AB), con nodos, para lo cual se hace uso del recorrido POSTORDEN para realizar la destrucción tanto de los nodos como de los elementos dentro de los mismos(de ser necesario), debido a que con dicho recorrido se tiene que primero se va a la extrema izquierda del árbol (de existir el mismo) y se empieza a eliminar dicho nodo, luego se eliminará al "hermano derecho" de este (de tenerlo), siguiendo por eliminar al "padre" de ambos nodos, lo cual garantiza una especie de borrado desde el "final" o parte extrema inferior hasta la raiz del árbol, así no se genera pérdidad de memoria de ningún tipo; y por último se destruirá el árbol.




En la imagen anterior se puede ver que para encontrar un elemento en un árbol binario de búsqueda si se sigue su criterio de orden es totalmente eficiente en la tarea con respecto a un árbol binario que no maneje ningún orden específico, ya que como el peor de los casos se debería recorrer todo el árbol para definir si se encontró o no el elemento buscado, en cambio para el binario (si se encuentra balanceado), se tiene que como máximo se deberá de recorrer la cantidad máxima de niveles para definir si se encontró o no el elemento en la estructura.

- CONSULTA:

Por qué si se quiere probar la función "abb_recorrer" y se le pasa un vector de punteros declarado e inicializado de la siguiente manera: "int **vector = NULL;", cuando se desea compilar el programa cae en seg fault? en cambio cuando se declara el vector de forma:
"int *vector[];", se compila y ejecuta sin problema? es debido a la inicialización del vector en NULL con la primera forma? y de qué otra forma se podría declarar el vector usando la nomenclatura de punteros?
