¡Claro! Aquí tienes un README completo en formato Markdown para tu proyecto de **Generador y Solucionador de Laberintos en C++**. He incluido secciones típicas como descripción, características, compilación, uso, ejemplos y créditos, junto con algunos emojis para hacerlo más visual y amigable:

---

```markdown
# 🏰 Generador y Solucionador de Laberintos en C++

Este proyecto en C++ permite generar y resolver laberintos de manera interactiva o mediante parámetros de entrada. Utiliza algoritmos clásicos como **DFS (búsqueda en profundidad)** para generar el laberinto, y **BFS (búsqueda en anchura)** para encontrar la ruta óptima desde la entrada hasta la salida.

---

## 🚀 Características

- ✨ **Generación aleatoria de laberintos** con estructuras realistas y ramificadas.
- 🧠 **Resolución automática** utilizando algoritmo BFS para encontrar el camino más corto.
- ⚙️ **Configuración personalizada** de dimensiones por consola o mediante argumentos.
- ⌛ **Mide el rendimiento** de generación y resolución (en milisegundos).
- 🎨 **Visualización gráfica por consola** usando emojis:
  - `🚶` Entrada
  - `🏁` Salida
  - `🔥` Camino óptimo
  - `🧱` Muros
  - `🟩` Camino libre

---

## 🧩 ¿Cómo funciona?

- El laberinto se genera con **muros (`#`) y caminos (`.`)**.
- Se utiliza **DFS recursivo** para crear pasajes en el laberinto, asegurando caminos variados.
- Luego, se usa **BFS** para encontrar el camino más corto desde la entrada hasta la salida.
- El resultado se muestra gráficamente en la consola.

---

## 🛠️ Compilación

Puedes compilar el proyecto con cualquier compilador de C++ moderno (compatible con C++11 o superior). Por ejemplo:

```bash
g++ -std=c++11 -o laberinto laberinto.cpp
```

---

## ▶️ Uso

### 🔹 Modo Interactivo (sin parámetros):

```bash
./laberinto
```

Te permitirá elegir entre dimensiones personalizadas o usar las predeterminadas (33x33).

### 🔹 Modo Automático (con dimensiones):

```bash
./laberinto [filas] [columnas]
```

Ejemplo:

```bash
./laberinto 25 45
```

---

## 📸 Ejemplo de salida

```
 🏰 GENERADOR Y SOLUCIONADOR DE LABERINTOS 🏰
==================================================
📏 Dimensiones configuradas: 33x33

🔄 Generando laberinto...
✅ Laberinto generado en 10.23 ms

📍 Laberinto generado:
🚶🟩🧱🧱🧱🧱...
🧱🧱🧱🧱🧱...

🔍 Resolviendo laberinto con algoritmo BFS...
✅ Laberinto resuelto en 3.87 ms

🗺️  Laberinto con solución:
🚶🔥🔥🧱🧱...
🧱🧱🔥🧱...

🎯 ¡Laberinto resuelto! 🎯
🚶 Entrada | 🔥 Camino óptimo | 🏁 Meta

📊 ESTADÍSTICAS DE RENDIMIENTO 📊
========================================
🏗️  Tiempo generación: 10.23 ms
🔍 Tiempo resolución: 3.87 ms
⏱️  Tiempo total: 14.10 ms
📐 Dimensiones: 33x33 (1089 celdas)
🛤️  Longitud camino óptimo: 91 pasos
```

---

## 📦 Dependencias

- Ninguna dependencia externa.
- Usa solo bibliotecas estándar de C++:
  - `<iostream>`, `<vector>`, `<random>`, `<ctime>`, `<queue>`, `<map>`, `<chrono>`, etc.

---

## 📚 Estructura del Código

- `main()` — Punto de entrada: configuración, generación, resolución y visualización.
- `generar_laberinto()` — Usa DFS para generar el laberinto.
- `resolver_laberinto()` — Usa BFS para hallar la solución.
- `mostrar_laberinto_simple()` — Imprime el laberinto sin solución.
- `mostrar_estadisticas_rendimiento()` — Imprime datos de rendimiento.

---

## ✍️ Autor

- 👤 **Manu**
- 🛠️ Proyecto escrito completamente en C++ con 💙
- 📅 Año: 2025

---

## 📄 Licencia

Este proyecto es de código abierto. Puedes usarlo, modificarlo o distribuirlo libremente.

---

¡Disfruta creando y resolviendo laberintos! 🔄🚶🔥🏁
```

---

Si tienes un nombre para el repositorio o quieres traducirlo al inglés, ¡puedo ayudarte también! ¿Deseas que agregue una imagen de ejemplo o un GIF del laberinto en ejecución?
