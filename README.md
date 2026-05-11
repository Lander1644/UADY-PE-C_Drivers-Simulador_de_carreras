# 🏎️ Race Masters
 
> Simulador de carreras de Fórmula 1 con sistema de apuestas, desarrollado en lenguaje C.
 
**Asignatura:** Programación Estructurada — Facultad de Matemáticas, UADY  
**Semestre:** 2 · **Unidad:** 4  
**Profesor:** Rejón Herrera Emilio Gabriel  
**Equipo:** C Drivers
 
---
 
## 📋 Descripción
 
Race Masters es una aplicación de consola desarrollada en **lenguaje C estándar** que simula una temporada completa de carreras al estilo Fórmula 1. El programa cuenta con pilotos, equipos y circuitos predeterminados, y utiliza un **algoritmo estocástico** que pondera la habilidad del piloto, las condiciones climáticas y un factor de aleatoriedad para calcular los resultados de cada carrera vuelta por vuelta.
 
Además de la simulación, el programa incluye un **módulo de apuestas** con el que el usuario puede administrar un saldo virtual, apostar por su piloto favorito antes de cada carrera y ganar o perder créditos según el resultado.
 
---
 
## ✨ Funcionalidades principales
 
- 🔐 **Inicio de sesión** con nombre de usuario personalizado
- 👤 **Dos roles de usuario:** Espectador y Apostador
- 🎲 **Simulación estocástica** vuelta por vuelta con tabla de posiciones, brechas e intervalos
- 🌦️ **Condiciones climáticas variables** que afectan el rendimiento de los pilotos
- 💰 **Sistema de apuestas** con cuotas dinámicas por piloto
- 🏆 **Clasificación del campeonato** con esquema de puntuación oficial de F1 (25-18-15-12-10-8-6-4-2-1)
- 📊 **Estadísticas del campeonato** con historial de carreras anteriores
- 🔄 **Menú post-carrera** con opciones para continuar, administrar saldo, cambiar rol o salir
---
 
## 🎮 Flujo del programa
 
```
Inicio
  └─ Inicio de sesión (nombre de usuario)
       └─ Selección de rol
            ├─ Espectador ──────────────────────────────┐
            └─ Apostador                                 │
                 └─ Módulo de apuestas                   │
                      └─ Validar saldo                   │
  ┌──────────────────────────────────────────────────────┘
  └─ Simulación de carrera (bucle por vueltas)
       └─ Reporte de resultados
            └─ Menú post-carrera
                 ├─ 1) Siguiente carrera
                 ├─ 2) Administrar saldo (solo apostador)
                 ├─ 3) Cambiar rol
                 ├─ 4) Estadísticas del campeonato
                 └─ 5) Salir
```
 
---
 
## 👥 Tipos de usuario
 
| Rol | Descripción |
|-----|-------------|
| **Espectador** | Visualiza la simulación vuelta por vuelta y consulta resultados y estadísticas del campeonato. |
| **Apostador** | Tiene todas las capacidades del espectador, además de poder apostar, administrar su saldo virtual y cobrar premios. Pierde la posibilidad de apostar cuando su saldo llega a cero. |
 
---
 
## 🛠️ Requisitos del sistema
 
- Compilador **GCC** con soporte para estándar **C99 o C11**
- Compatible con **Windows**, **Linux** y **macOS**
- Sin dependencias externas
---
 
## ⚙️ Compilación y ejecución
 
### Linux / macOS
 
```bash
gcc -std=c11 -Wall -o race_masters main.c
./race_masters
```
 
### Windows (MinGW / MSYS2)
 
```bash
gcc -std=c11 -Wall -o race_masters.exe main.c
race_masters.exe
```
 
---
 
## 📁 Estructura del repositorio
 
```
PE-CDrivers-RaceMasters/
├── src/
│   ├── main.c               # Punto de entrada del programa
│   ├── simulacion.c         # Módulo de simulación de carrera
│   ├── apuestas.c           # Módulo de apuestas y saldo
│   ├── resultados.c         # Módulo de resultados y campeonato
│   └── usuarios.c           # Módulo de inicio de sesión y roles
├── include/
│   ├── simulacion.h
│   ├── apuestas.h
│   ├── resultados.h
│   └── usuarios.h
├── docs/
│   └── Propuesta_proyecto.pdf
├── README.md
└── .gitignore
```
 
---
 
## 👨‍💻 Equipo de desarrollo
 
| Nombre | GitHub |
|--------|--------|
| Álvarez Martínez Abel Israel | — |
| Mis Ramírez Elliot Gibranny | — |
| López Sansores Lander Antonio | — |
| Ruiz Verde Pedro Miguel | — |
| Salazar de la Cruz Canul Javier Adrian | — |
 
---
 
## 📐 Estándar de codificación
 
El proyecto sigue las normas **ISO/IEC 12207** e **ISO/IEC 25010**, con énfasis en:
 
- Nombres descriptivos para variables, funciones y constantes
- Modularización clara con archivos `.h` para prototipos
- Comentarios en cada función indicando propósito, parámetros y retorno
- Validación de todas las entradas del usuario
- Sin código duplicado; reutilización mediante funciones
- Inicialización de variables antes de su uso
---
 
## 📅 Proceso de desarrollo
 
El equipo trabaja en ciclos de **2 días** con las siguientes herramientas:
 
| Herramienta | Uso |
|-------------|-----|
| **Discord** | Reuniones y llamadas del equipo |
| **GitHub** | Control de versiones y avance del código |
| **Excel** | Bitácoras de aportación personal y objetivos cumplidos |
| **Google Docs** | Documentación de versiones e ideas generales |
 
### Bitácoras
- 📒 [Bitácora de trabajo personal](https://docs.google.com/spreadsheets/d/1x9SWSGfHCtuPIg9xICLFYjTXPdRkmhd_iZyVeLToSZM/edit?gid=0#gid=0)
- ✅ [Bitácora de objetivos realizados](https://docs.google.com/spreadsheets/d/1Kw2nzIVIpn9yWnEyixW0vcjmpp8BKDghEVW-hqmYg0/edit?gid=0#gid=0)
---
 
## 📄 Licencia
 
Proyecto académico — Universidad Autónoma de Yucatán · Facultad de Matemáticas · 2026
