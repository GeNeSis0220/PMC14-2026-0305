# PMC14-2026-0305 - Error de calibración de un transductor

**Matrícula:** 2026-0305
**Correo:** 20260305@itla.edu.do

## Explicación del modelo

El programa lee un grupo de unidades (máquinas medidoras). Cada unidad
tiene un id, una etiqueta, un tipo, un valor de referencia p y varias
muestras. Para cada unidad calcula un score y un estado, y al final
imprime TOTAL, ORDER y FIND.

- El error de cada muestra es la distancia entre la muestra y p.
- Tipo 0: el score es la suma de los errores.
- Tipo 1: el score es la suma de los errores al cuadrado.
- Estado: 1 si todos los errores son 10 o menos, y 0 si alguno es mayor.
- Cada unidad se calcula por separado, sin arrastrar valores de la anterior.

## Decisiones

- Usé una matriz muestras[20][8] y un arreglo de registros con una
  configuración anidada (tipo y p).
- calcular devuelve el score y entrega el estado por referencia con un apuntador.
- total_rec suma los scores de forma recursiva.
- ordenar usa burbuja sobre un arreglo de índices, para conservar el orden
  original al imprimir las líneas por unidad.
- buscar usa búsqueda binaria sobre una copia ordenada por id.
- Toda la entrada se valida antes de imprimir; si algo falla, se imprime solo ERROR.

## Compilación y ejecución

Compilar:

    gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o reto

Ejecutar en Windows:

    reto.exe < caso.in

Ejecutar el banco público:

    py evaluar.py publicas.json reto.exe

## Resultados

Los 6 casos públicos pasan (Grupo 1 a 6: OK, 6 / 6).
Los archivos de entrada (.in), salida esperada (.out) y resultado
obtenido (.res) están en la carpeta pruebas/.

## Pruebas propias

- propio1: caso de borde, 8 muestras y valores en 100. Esperado: score 0, estado 1.
- propio2: q ausente (se busca el id 7 y no existe). FIND debe dar -1.
- propio3: inválido por id repetido. Debe imprimir solo ERROR.

### Fallo corregido

En propio1 el programa imprimió ERROR. La causa era que mi archivo de
entrada tenía una muestra de menos (ocho números en lugar de nueve después
del tipo: uno para p y ocho para las muestras). Agregué el número que
faltaba y el resultado coincidió con lo esperado.

## Fuentes consultadas

- Corona Nakamura, M. A. y Ancona Valdez, M. de los Á. (2011). Diseño de
  algoritmos y su codificación en lenguaje C. McGraw-Hill.
- Documentación de la biblioteca estándar de C.

## Historial de commits

| # | Hash | Avance |
|---|------|--------|
| 1 | ead5486 | Estructura inicial, interpretación y plan (reto.h, plan.md) |
| 2 | 5b71e0b | Desarrollo parcial: lectura y calcular (main.c, prueba.txt) |
| 3 | ad350eb | Pruebas, validación y revisión (main.c completo, pruebas/, evaluar.py, publicas.json) |
| 4 | (se entrega aparte) | Correcciones finales y documentación (README.md) |
