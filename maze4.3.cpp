#include <iostream>   // Para imprimir y leer en consola (std::cout, std::cin, std::endl)
#include <vector>     // Para usar vectores (arreglos dinámicos que se agrandan automáticamente)
#include <random>     // Para generar números aleatorios modernos, más seguros y precisos que rand()
#include <ctime>      // Para obtener el tiempo actual (por ejemplo, como semilla para aleatoriedad con srand())
#include <algorithm>  // Para usar funciones como sort(), shuffle(), find(), etc. sobre colecciones como vector
#include <queue>      // Para usar colas (queue FIFO) o colas de prioridad (priority_queue), útiles en IA y pathfinding
#include <map>        // Para usar mapas (diccionarios ordenados): pares clave-valor como en Python
#include <chrono>     // Para medir el tiempo que tarda algo en ejecutarse con precisión (milisegundos, microsegundos)
#include <iomanip>    // Para dar formato a la salida en consola (decimales, espacios, alineación, etc.)
#include <limits>     // Para obtener los valores máximos o mínimos posibles de tipos de datos (ej: INT_MAX, INT_MIN)


// Dimensiones del laberinto (configurables)
int LAB_WIDTH = 33;
int LAB_HEIGHT = 33;

// Representación del laberinto: '#' = muro, '.' = camino
std::vector<std::vector<char>> maze;

// Generador de números aleatorios
std::mt19937 random_engine(std::time(nullptr));

// Estructura para representar una posición
struct Posicion {
    int x, y;
    bool operator<(const Posicion& other) const {
        return std::tie(x, y) < std::tie(other.x, other.y);
    }
    bool operator==(const Posicion& other) const {
        return x == other.x && y == other.y;
    }
};

// Verifica si una coordenada está dentro del área válida del laberinto (sin bordes)
bool es_posicion_valida(int x, int y) {
    return x > 0 && x < LAB_WIDTH - 1 && y > 0 && y < LAB_HEIGHT - 1;
}

// Algoritmo DFS recursivo para tallar caminos en el laberinto
void tallar_camino(int x_actual, int y_actual, int dx_prev = 0, int dy_prev = 0, int pasos_rectos = 0) {
    maze[y_actual][x_actual] = '.';  // Convertir a camino

    // Direcciones posibles: arriba, abajo, izquierda, derecha (con paso doble para dejar muros entre caminos)
    std::vector<std::pair<int, int>> direcciones = {{0, -2}, {0, 2}, {-2, 0}, {2, 0}};
    std::shuffle(direcciones.begin(), direcciones.end(), random_engine);

    for (auto [dx, dy] : direcciones) {
        int x_siguiente = x_actual + dx;
        int y_siguiente = y_actual + dy;
        int x_medio = x_actual + dx / 2;
        int y_medio = y_actual + dy / 2;

        if (es_posicion_valida(x_siguiente, y_siguiente) && maze[y_siguiente][x_siguiente] == '#') {
            bool misma_direccion = (dx == dx_prev && dy == dy_prev);
            if (misma_direccion && pasos_rectos > 2) continue;  // Evita pasadizos muy rectos y largos

            maze[y_medio][x_medio] = '.';  // Abrir muro entre actual y siguiente
            tallar_camino(x_siguiente, y_siguiente, dx, dy, misma_direccion ? pasos_rectos + 1 : 1);
        }
    }
}

// Genera el laberinto con una entrada y una salida conectadas
void generar_laberinto() {
    // Inicializar el laberinto con muros
    maze = std::vector<std::vector<char>>(LAB_HEIGHT, std::vector<char>(LAB_WIDTH, '#'));
    
    tallar_camino(1, 1);
    maze[0][1] = '.';                       // Entrada (esquina superior izquierda)
    maze[LAB_HEIGHT - 1][LAB_WIDTH - 2] = '.';  // Salida (esquina inferior derecha)
}

// Algoritmo BFS para encontrar la ruta más corta
std::vector<Posicion> resolver_laberinto() {
    Posicion inicio = {1, 0};  // Entrada
    Posicion fin = {LAB_WIDTH - 2, LAB_HEIGHT - 1};  // Salida
    
    std::queue<Posicion> cola;
    std::map<Posicion, Posicion> padres;  // Para reconstruir el camino
    std::map<Posicion, bool> visitado;
    
    cola.push(inicio);
    visitado[inicio] = true;
    
    // Direcciones: arriba, abajo, izquierda, derecha
    std::vector<std::pair<int, int>> direcciones = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    
    while (!cola.empty()) {
        // Tomamos la posición actual de la cola
        // y la sacamos de la cola
        Posicion actual = cola.front();
        cola.pop();
        
        if (actual == fin) {
            // Reconstruimos el camino desde el final hasta el inicio, usando el mapa de padres
            std::vector<Posicion> camino;
            Posicion pos = fin;
            // Agregamos la posición final al camino
            while (!(pos == inicio)) {
                
                camino.push_back(pos);
                pos = padres[pos];
            }
            camino.push_back(inicio);
            
            std::reverse(camino.begin(), camino.end());
            return camino;
        }
        // Exploramos en todas las direcciones posibles
        for (auto [dx, dy] : direcciones) {
            int nx = actual.x + dx;
            int ny = actual.y + dy;
            Posicion siguiente = {nx, ny};
            
            // Verificar límites y que sea camino libre
            if (nx >= 0 && nx < LAB_WIDTH && ny >= 0 && ny < LAB_HEIGHT && 
                maze[ny][nx] == '.' && !visitado[siguiente]) {
                
                visitado[siguiente] = true;
                padres[siguiente] = actual;
                cola.push(siguiente);
            }
        }
    }
    
    return {};  // No se encontró solución
}

// Función para validar y ajustar dimensiones
void configurar_dimensiones(int ancho, int alto) {
    // Asegurar que las dimensiones sean impares (para el algoritmo de generación)
    LAB_WIDTH = (ancho % 2 == 0) ? ancho + 1 : ancho;
    LAB_HEIGHT = (alto % 2 == 0) ? alto + 1 : alto;
    
    // Dimensiones mínimas para un laberinto funcional
    if (LAB_WIDTH < 5) LAB_WIDTH = 5;
    if (LAB_HEIGHT < 5) LAB_HEIGHT = 5;
    
    std::cout << "📏 Dimensiones configuradas: " << LAB_WIDTH << "x" << LAB_HEIGHT << std::endl;
}

// Nueva función simplificada para solicitar dimensiones
void solicitar_dimensiones_por_input() {
    int opcion;
    std::cout << "\n🎛️  OPCIONES DE CONFIGURACIÓN:\n";
    std::cout << "1. Configurar dimensiones personalizadas\n";
    std::cout << "2. Usar dimensiones por defecto (33x33)\n";
    std::cout << "Selecciona una opción (1-2): ";
    
    while (!(std::cin >> opcion) || opcion < 1 || opcion > 2) {
        std::cout << "❌ Opción inválida. Por favor ingresa 1 o 2: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    switch (opcion) {
        case 1: {
            int filas, columnas;
            std::cout << "Ingresa el número de filas (mínimo 5): ";
            while (!(std::cin >> filas) || filas < 5) {
                std::cout << "❌ Número de filas inválido. Ingresa un número mayor o igual a 5: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            
            std::cout << "Ingresa el número de columnas (mínimo 5): ";
            while (!(std::cin >> columnas) || columnas < 5) {
                std::cout << "❌ Número de columnas inválido. Ingresa un número mayor o igual a 5: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            
            configurar_dimensiones(columnas, filas);
            break;
        }
        case 2:
            std::cout << "📝 Usando dimensiones por defecto: " << LAB_WIDTH << "x" << LAB_HEIGHT << "\n";
            break;
    }
}

// Función para mostrar solo el laberinto sin solución
void mostrar_laberinto_simple() {
    for (int y = 0; y < LAB_HEIGHT; ++y) {
        for (int x = 0; x < LAB_WIDTH; ++x) {
            // Inicio del laberinto
            if (x == 1 && y == 0) {
                std::cout << "🚶";  // Persona en la entrada
            }
            // Final del laberinto
            else if (x == LAB_WIDTH - 2 && y == LAB_HEIGHT - 1) {
                std::cout << "🏁";  // Meta
            }
            // Resto del laberinto
            else {
                std::cout << (maze[y][x] == '#' ? "🧱" : "🟩");
            }
        }
        std::cout << '\n';
    }
}

// Función para mostrar información de rendimiento (sin eficiencia)
void mostrar_estadisticas_rendimiento(double tiempo_generacion, double tiempo_resolucion, 
                                    const std::vector<Posicion>& solucion) {
    std::cout << "\n📊 ESTADÍSTICAS DE RENDIMIENTO 📊\n";
    std::cout << std::string(40, '=') << "\n";
    std::cout << "🏗️  Tiempo generación: " << tiempo_generacion << " ms\n";
    std::cout << "🔍 Tiempo resolución: " << tiempo_resolucion << " ms\n";
    std::cout << "⏱️  Tiempo total: " << (tiempo_generacion + tiempo_resolucion) << " ms\n";
    std::cout << "📐 Dimensiones: " << LAB_WIDTH << "x" << LAB_HEIGHT 
              << " (" << (LAB_WIDTH * LAB_HEIGHT) << " celdas)\n";
    std::cout << "🛤️  Longitud camino óptimo: " << solucion.size() << " pasos\n";
}



int main(int argc, char* argv[]) {
    std::cout << "\n 🏰 GENERADOR Y SOLUCIONADOR DE LABERINTOS 🏰\n";
    std::cout << std::string(50, '=') << "\n";
    
    // Configurar dimensiones según los parámetros
    if (argc == 3) {
        // Modo: programa filas columnas
        int filas = std::atoi(argv[1]);
        int columnas = std::atoi(argv[2]);
        
        if (filas > 0 && columnas > 0) {
            configurar_dimensiones(columnas, filas);
        } else {
            std::cout << "❌ Parámetros inválidos. Deben ser números positivos.\n";
            return 1;
        }
    } else if (argc == 1) {
        // Modo interactivo
        solicitar_dimensiones_por_input();
    } else {
        std::cout << "❌ Uso: " << argv[0] << " [filas] [columnas] o ejecutar sin parámetros para modo interactivo.\n";
        return 1;
    }
    
    std::cout << "\n🔄 Generando laberinto...\n";
    
    // Medir tiempo de generación
    auto inicio_generacion = std::chrono::high_resolution_clock::now();
    generar_laberinto();
    auto fin_generacion = std::chrono::high_resolution_clock::now();
    
    double tiempo_generacion = std::chrono::duration<double, std::milli>(
        fin_generacion - inicio_generacion).count();
    
    std::cout << "✅ Laberinto generado en " << tiempo_generacion << " ms\n\n";
    std::cout << "📍 Laberinto generado:\n";
    mostrar_laberinto_simple();
    
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "🔍 Resolviendo laberinto con algoritmo BFS...\n";
    
    // Medir tiempo de resolución
    auto inicio_resolucion = std::chrono::high_resolution_clock::now();
    std::vector<Posicion> solucion = resolver_laberinto();
    auto fin_resolucion = std::chrono::high_resolution_clock::now();
    
    double tiempo_resolucion = std::chrono::duration<double, std::milli>(
        fin_resolucion - inicio_resolucion).count();
    
    std::cout << "✅ Laberinto resuelto en " << tiempo_resolucion << " ms\n\n";
    
    if (!solucion.empty()) {
        // Mostrar laberinto con solución
        // Crear mapa de posiciones de la solución para búsqueda rápida
        std::map<Posicion, bool> es_solucion;
        for (const auto& pos : solucion) {
            es_solucion[pos] = true;
        }
        
        std::cout << "🗺️  Laberinto con solución:\n";
        for (int y = 0; y < LAB_HEIGHT; ++y) {
            for (int x = 0; x < LAB_WIDTH; ++x) {
                Posicion pos_actual = {x, y};
                
                // Inicio del laberinto
                if (x == 1 && y == 0) {
                    std::cout << "🚶";  // Persona en la entrada
                }
                // Final del laberinto
                else if (x == LAB_WIDTH - 2 && y == LAB_HEIGHT - 1) {
                    std::cout << "🏁";  // Meta
                }
                // Camino de la solución
                else if (es_solucion[pos_actual] && maze[y][x] == '.') {
                    std::cout << "🔥";  // Antorcha marcando el camino
                }
                // Muro
                else if (maze[y][x] == '#') {
                    std::cout << "🧱";  // Ladrillo
                }
                // Camino libre
                else {
                    std::cout << "🟩";  // Césped
                }
            }
            std::cout << '\n';
        }
        
        std::cout << "\n🎯 ¡Laberinto resuelto! 🎯\n";
        std::cout << "🚶 Entrada | 🔥 Camino óptimo | 🏁 Meta\n";
        
        // Mostrar estadísticas de rendimiento
        mostrar_estadisticas_rendimiento(tiempo_generacion, tiempo_resolucion, solucion);
    } else {
        std::cout << "❌ No se pudo encontrar una solución al laberinto.\n";
    }
    
    return 0;
}