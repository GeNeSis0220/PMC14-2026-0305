# Plan - PMC14  Error de calibracion de un transductor 

## Que hace el programa?
Mi programa lee cierta cantidad de unidades o un grupo de unidades (las maquinas medidoras), cada una tiene su id, su nombre o etiqueta, un tipo, un valor de referencia llamado (p) y varias lecturas o muestras que son los numeros que leyo mi maquina. Para cada unidad (maquina) calcula un score que es la suma de los errores segun su tipo, y un estado, que dice si respeto el limite. Al final se imprime una linea por unidad con el id, el score y un estado,y luego las lineas con el total, el order y el find.

## Como se calcula el score?
El score es la suma de los errores de cada unidad segun su tipo.
Entonces el error es la diferencia que hay entre (p), que es mi valor de referencia y la muestra, que es el valor que mide mi maquina, sin importar que sea mayor o menor que (p). Por lo tanto cada maquina tiene un tipo, que puede ser 1 o 0. Si el tipo es 0 el score es la suma de todos los errores. Si el tipo es 1 es la suma de todos los errores al cuadrado.

## Como se calcula el estado?
Pues, el limite de error es 10.
Y si todos los numeros de la unidad son 10 o menor, el estado es 1 y si algun error es mayor de 10 el estado es 0.

## Cuando se imprime error?
Solo se imprime la palabra error sin resultados parciales como por ejemplo, si algun dato esta fuera de su rango, si hay un id repetido,si el nombre no es valido o si la entrada esta incompleta.

## Pseudocodigo de calcular
Score empieza en 0 y estado empieza en 1. Para cada lectura de la unidad calculo el error: que es la distancia entre la letura (muestra) y p (valor-referencia). Si el tipo es 0 sumo el error al score, si el tipo es 1 sumo el error al cuadrado al score y si el error es mayor de 10 el estado pasa a 0. Y devuelvo el score.