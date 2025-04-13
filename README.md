## Minishell

# Funciones
<details> <summary><strong>📥 Entrada y Lectura de Comandos</strong></summary>

  | Función             | Uso                                                                 |
|---------------------|----------------------------------------------------------------------|
| `readline`          | Leer línea con prompt, permite historial y edición                   |
| `add_history`       | Añadir línea al historial de readline                                |
| `rl_clear_history`  | Limpiar historial de readline                                        |
| `rl_on_new_line`    | Notifica a readline que comienza una nueva línea                     |
| `rl_replace_line`   | Reemplaza el contenido actual de la línea                            |
| `rl_redisplay`      | Redibuja la línea actual (útil con señales)                          |
| `isatty`            | Comprueba si un descriptor es un terminal                           |
| `ttyname`           | Devuelve el nombre del terminal asociado a un descriptor             |
| `ttyslot`           | Obtiene el número de terminal asociado                               |
| `ioctl`             | Control de dispositivos, útil para gestionar terminales              |

</details> <details> <summary><strong>💬 Entrada/Salida Básica</strong></summary>

  | Función    | Uso                                      |
|------------|-------------------------------------------|
| `write`    | Escribir en un descriptor (stdout, stderr)|
| `printf`   | Imprimir con formato                      |
| `perror`   | Imprimir mensaje de error con `errno`     |
| `strerror` | Convertir `errno` a string explicativa    |

</details> <details> <summary><strong>📁 Sistema de Archivos</strong></summary>

  | Función   | Uso                                                  |
|-----------|-------------------------------------------------------|
| `open`    | Abrir archivos                                        |
| `read`    | Leer archivos o entrada                               |
| `close`   | Cerrar archivos                                       |
| `access`  | Comprobar permisos de archivos                        |
| `unlink`  | Eliminar un archivo                                   |
| `stat`    | Obtener información de un archivo                     |
| `lstat`   | Como `stat`, pero sin seguir enlaces simbólicos       |
| `fstat`   | Como `stat`, pero desde descriptor de archivo         |
| `opendir` | Abrir un directorio                                   |
| `readdir` | Leer entradas de un directorio                        |
| `closedir`| Cerrar un directorio                                  |
| `getcwd`  | Obtener el directorio actual                          |
| `chdir`   | Cambiar de directorio                                 |

</details> <details> <summary><strong>👨‍👧‍👦 Gestión de Procesos</strong></summary>

  | Función    | Uso                                                 |
|------------|------------------------------------------------------|
| `fork`     | Crear un nuevo proceso hijo                          |
| `execve`   | Ejecutar un nuevo programa                           |
| `wait`     | Esperar a que termine un hijo                        |
| `waitpid`  | Esperar a un hijo específico                         |
| `wait3`    | Igual que `wait`, pero con más info (uso de recursos)|
| `wait4`    | Como `wait3`, pero permite más control               |
| `exit`     | Terminar el proceso actual                           |
| `kill`     | Enviar señales a un proceso                          |

</details> <details> <summary><strong>🔀 Pipes y Redirección</strong></summary>

  | Función  | Uso                                        |
|----------|---------------------------------------------|
| `dup`    | Duplicar un descriptor de archivo           |
| `dup2`   | Duplicar y redirigir un descriptor          |
| `pipe`   | Crear un pipe (comunicación entre procesos) |

</details> <details> <summary><strong>🧠 Señales</strong></summary>

  | Función        | Uso                                               |
|----------------|----------------------------------------------------|
| `signal`       | Establecer un manejador de señales                 |
| `sigaction`    | Manejador de señales avanzado                      |
| `sigemptyset`  | Inicializar un conjunto de señales vacío           |
| `sigaddset`    | Añadir señales a un conjunto                       |


</details> <details> <summary><strong>🌎 Variables de Entorno</strong></summary>

  | Función  | Uso                                      |
|----------|-------------------------------------------|
| `getenv` | Obtener el valor de una variable de entorno |

</details> <details> <summary><strong>🖥️ Control de la Terminal (Termcap)</strong></summary>

  | Función     | Uso                                                   |
|-------------|--------------------------------------------------------|
| `tcgetattr` | Obtener atributos de la terminal                       |
| `tcsetattr` | Establecer atributos de la terminal                    |
| `tgetent`   | Cargar la base de datos termcap                        |
| `tgetflag`  | Leer flags del terminal (de termcap)                   |
| `tgetnum`   | Obtener valores numéricos del terminal (termcap)       |
| `tgetstr`   | Obtener cadenas del terminal (termcap)                 |
| `tgoto`     | Posicionar el cursor                                   |
| `tputs`     | Imprimir secuencias de control del terminal            |

</details> <details> <summary><strong>🛠️ Utilidades de Memoria</strong></summary>

  | Función | Uso                                 |
|--------|--------------------------------------|
| `malloc` | Reservar memoria dinámica          |
| `free`   | Liberar memoria                     |

</details>
