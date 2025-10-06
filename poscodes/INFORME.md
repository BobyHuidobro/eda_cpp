# Tarea 2 EDA — Ordenamiento de Códigos Postales

## Informe

> Completar los campos marcados con TODO. Mantener coherencia exacta con el código implementado.

---

## Título

**TODO:** (Ej.: Comparación Empírica de RadixSort frente a QuickSort y MergeSort en Códigos Postales de Longitud Fija)

## Autores

-   **Estudiante 1:** Nombre — Rol principal (p.ej. Implementación Radix / CountingSort)
-   **Estudiante 2:** Nombre — Rol principal (p.ej. Benchmarks / Informe)  
    **Fecha:** TODO (dd/mm/aaaa)

---

## Resumen (Abstract)

**TODO (8–12 líneas):**  
Contexto del problema, formato fijo (DDDDLL), motivación de RadixSort para dominios acotados, comparación con Quick y Merge (O(w·n) vs O(n log n)), datasets (500K, 1M, 10M), metodología (5 corridas, µ ± σ), principales hallazgos (ej. Radix supera a Quick desde 1M), conclusión sintética.

---

## 1. Introducción (10 %)

### 1.1. Contexto y Motivación

**TODO:** Explicar necesidad de ordenar masivamente códigos postales; por qué la estructura fija permite técnicas de orden lineal.

### 1.2. Problema a Resolver

**TODO:** Ordenar n códigos de formato DDDDLL en orden lexicográfico global.

### 1.3. Formato de los Datos

-   Longitud fija: 6 caracteres
    -   Posiciones 0–3: dígitos (‘0’–‘9’)
    -   Posiciones 4–5: letras (‘A’–‘Z’)
-   Ejemplos:
    ```
    2553FI, 7561PE, 7336IU, ...
    ```

### 1.4. Objetivos

-   Implementar CountingSort estable por columna usando listas/colas enlazadas (índices).
-   Construir RadixSort LSD (6 pasadas).
-   Implementar QuickSort y MergeSort como bases O(n log n).
-   Medir y comparar rendimiento (µ ± σ) en 3 escalas.

### 1.5. Organización del Documento

**TODO:** Breve mapa de secciones.

---

## 2. Desarrollo (Diseño e Implementación) (40 %)

### 2.1. Representación de los Códigos

-   Clase `Poscode` (envuelve std::string).
-   Accesos: `getData()`, `getValue(i)`.

### 2.2. Estructuras de Datos Auxiliares

-   `Node`: (int data, Node\* next) — almacena índice.
-   `Queue`: para buckets (FIFO O(1) en push/pop).
-   (Opcional) `LinkedList`, `Stack` (indicar si se usaron o quedaron sin uso directo).

### 2.3. Funciones Helper

-   `less_poscode(a,b)`: compara `a.getData() < b.getData()`.
-   `char_to_bucket(c,M)`: mapeo dígitos → 0..9; letras → 0..25.

### 2.4. CountingSort por Posición

-   Entrada: vector de `Poscode`, columna `pos`, base `M`.
-   Buckets: arreglo de M colas.
-   Distribución: insertar índice i en bucket según carácter.
-   Recolección: barrido 0..M−1 preservando orden de llegada (estabilidad).
-   Complejidad: O(n + M) ≈ O(n) (M constante pequeña: 10 o 26).
-   Justificación de almacenar índices (menor copia, O(1) en push).

### 2.5. RadixSort (LSD)

-   Orden de pasadas (derecha → izquierda):
    1. pos 5 (letra) base 26
    2. pos 4 (letra) base 26
    3. pos 3 (dígito) base 10
    4. pos 2 (dígito) base 10
    5. pos 1 (dígito) base 10
    6. pos 0 (dígito) base 10
-   Estabilidad de cada CountingSort ⇒ orden global correcto.
-   Complejidad total: O(6n) = O(n).
-   Consideraciones de implementación: buffer intermedio, no modificar colas durante iteración de buckets salvo pop controlado.

### 2.6. QuickSort

-   Estrategia: partición estilo Hoare modificada, pivote = elemento medio.
-   Eliminación de recursión de cola (tail recursion elimination) para limitar profundidad.
-   No garantiza estabilidad.
-   Complejidad: promedio O(n log n), peor caso O(n²) (mitigado por pivote medio).

### 2.7. MergeSort

-   Top-down recursivo.
-   Buffer auxiliar global (vector<Poscode>) para merges.
-   Estable: en igualdad se selecciona elemento del subarreglo izquierdo primero.
-   Optimización: salto de merge si `A[m] <= A[m+1]`.
-   Complejidad: O(n log n) tiempo, O(n) espacio.

### 2.8. Verificación de Correctitud

-   Función `is_sorted`: chequeo lineal.
-   Dataset pequeño manual (ej.: 6–12 códigos) comparado contra `std::sort`.
-   Prueba de estabilidad (duplicados) para Merge y Radix.
-   Comparación cruzada: outputs de Radix, Quick, Merge idénticos.

### 2.9. Manejo de Errores y Robustez

-   Validación de apertura de archivo en `readCodes`.
-   Consideración de líneas vacías / EOF anticipado (relleno opcional controlado).
-   Assertions (en Debug) para rangos de caracteres válidos.

### 2.10. Complejidad y Uso de Memoria

-   Radix: buffer + nodos temporales (6 \* n asignaciones efímeras).
-   Quick: in-place (stack O(log n)).
-   Merge: buffer n + stack O(log n).
-   Discusión del impacto de `new/delete` en CountingSort.

### 2.11. Ejecución / Uso de los Programas

Ejemplo de compilación (CMake):

```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j
```

Ejemplo de uso de benchmark:

```
./bench ../poscodes/codes_500K.txt 500000 5
```

Parámetros: `<ruta_archivo> <n> <runs>`.

---

## 3. Resultados Experimentales y Discusión (40 %)

### 3.1. Entorno Experimental

-   CPU: **TODO** (modelo, núcleos/hilos).
-   RAM: **TODO** GB.
-   Sistema Operativo: **TODO** (versión).
-   Compilador: **TODO** (clang++ / g++ versión).
-   Flags: `-O3 -DNDEBUG -march=native` (indicar si usados).
-   Tiempo medido: solo fase de ordenamiento (excluir lectura) — **TODO confirmar**.

### 3.2. Metodología

-   5 corridas por algoritmo y tamaño.
-   Reporte: µ (promedio) ± σ (desviación estándar poblacional).
-   Misma entrada base copiada para cada corrida de cada algoritmo.
-   Validación post-orden: `is_sorted == true`.

### 3.3. Tabla de Resultados

(Completar con valores reales)

| Tamaño | Radix (ms) | Quick (ms) | Merge (ms) |
| ------ | ---------: | ---------: | ---------: |
| 500K   |  µr1 ± σr1 |  µq1 ± σq1 |  µm1 ± σm1 |
| 1M     |  µr2 ± σr2 |  µq2 ± σq2 |  µm2 ± σm2 |
| 10M    |  µr3 ± σr3 |  µq3 ± σq3 |  µm3 ± σm3 |

(Opcional añadir columna “Speedup” vs uno de referencia.)

### 3.4. Análisis Comparativo

**TODO:**

-   Relación de crecimiento observada: Radix ~ lineal; Quick/Merge ~ n log n.
-   Puntos donde Radix supera a Quick/Merge (ej.: a partir de 1M).
-   Comportamiento de σ: estabilidad en tiempos (cuál es más consistente).

### 3.5. Influencia de la Implementación

**TODO:**

-   Costo de asignaciones dinámicas en CountingSort (60M para 10M elementos en 6 pasadas).
-   Efecto de la estabilidad (Radix y Merge) vs Quick.
-   Impacto del buffer único de Merge.
-   Posible penalización de Radix en tamaños pequeños por constante alta.

### 3.6. Limitaciones y Consideraciones

**TODO:**

-   No se implementó pool de nodos (posible optimización).
-   No se midió memoria pico exacta (si aplica).
-   Un solo hardware (no hay variación arquitectural).
-   Quick no protegido contra peores casos con datos adversos (sin median-of-three, etc.).

### 3.7. Observaciones Adicionales (Opcional)

**TODO:** Cualquier comportamiento inesperado, anomalías, profiling rápido, etc.

---

## 4. Conclusiones (10 %)

**TODO (5–10 líneas):**

-   Síntesis: Radix válido / más eficiente a gran escala (o no, según datos).
-   Confirmación de O(w·n) vs O(n log n) empírica.
-   Estabilidad: cuándo importa.
-   Recomendaciones prácticas (cuándo usar cada algoritmo).
-   Posibles mejoras futuras puntuales.

---

## 5. Referencias (Opcional)

-   Cormen et al. (CLRS) — CountingSort, RadixSort, QuickSort, MergeSort.
-   Apuntes del curso EDA (2025).
-   (Añadir otras solo si realmente fueron consultadas y permitidas.)

---

## Apéndices (Opcional)

### A. Fragmentos de Código Clave

(Pegar solo si se solicita — evitar redundancia con repositorio.)

### B. Ejemplo de Salida de bench

```
Archivo: codes_500K.txt
Tamaño: 500000
Runs: 5
Radix Sort:  XXXX ± YY ms
QuickSort :  XXXX ± YY ms
MergeSort :  XXXX ± YY ms
```

### C. Fórmulas Usadas

Promedio:  
µ = (Σ ti)/k  
Desviación estándar (poblacional):  
σ = sqrt( Σ (ti − µ)² / k )

### D. Verificación is_sorted (pseudocódigo)

```
for i in 1..n-1:
  if A[i-1] > A[i]: return false
return true
```

---

## Checklist de Consistencia (Antes de Entregar)

-   [ ] Abstract contiene resultados clave.
-   [ ] Orden de pasadas de Radix detallado correctamente.
-   [ ] Tabla µ ± σ completa y cifras coherentes con texto.
-   [ ] Hardware y flags descritos.
-   [ ] Se explica por qué CountingSort es estable y O(n).
-   [ ] Se menciona costo de new/delete (Radix) y buffer (Merge).
-   [ ] Conclusiones se basan en datos, no en suposiciones.
-   [ ] Sin contradicciones entre secciones.
-   [ ] Ortografía revisada.
