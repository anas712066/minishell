# Minishell

## Funciones

<details>
<summary><strong>📥 Entrada y Lectura de Comandos</strong></summary>

<br>

| Función                         | Descripción                                                                                             | Uso común                                                         | Uso con código                                                   |
|----------------------------------|---------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------|------------------------------------------------------------------|
| `readline(prompt)`              | Muestra el prompt y lee una línea de entrada del usuario. Devuelve un puntero a la línea leída.         | Leer comandos del usuario con edición de línea                    | `char *s = readline("mini$ ");`                                 |
| `add_history(line)`             | Añade la línea al historial de comandos. Útil para usar las flechas ↑ y ↓.                              | Guardar comandos ejecutados para navegación en el historial       | `if (*s) add_history(s);`                                       |
| `rl_clear_history()`            | Limpia el historial de readline liberando memoria.                                                      | Limpiar historial al salir del programa                           | `rl_clear_history();`                                           |
| `rl_on_new_line()`              | Notifica a readline que comienza una nueva línea. Útil al manejar señales.                              | Preparar readline tras una interrupción con Ctrl+C                | `rl_on_new_line();`                                             |
| `rl_replace_line(text, undo)`  | Reemplaza la línea actual por `text`. `undo` borra el historial de deshacer si es 1.                    | Borrar o reemplazar el texto actual en la línea de entrada        | `rl_replace_line("", 0);`                                       |
| `rl_redisplay()`                | Redibuja el prompt y la línea actual.                                                                   | Refrescar el prompt en pantalla tras una señal                    | `rl_redisplay();`                                               |
| `isatty(fd)`                    | Devuelve 1 si el descriptor es un terminal, 0 si no.                                                    | Comprobar si la entrada es interactiva                            | `if (isatty(STDIN_FILENO))`                                     |
| `ttyname(fd)`                   | Devuelve el nombre del terminal asociado con el descriptor.                                             | Obtener el nombre del terminal, útil para depuración              | `char *name = ttyname(0);`                                      |
| `ttyslot()`                     | Devuelve el número de terminal del proceso actual.                                                      | Rara vez usada, identificación del terminal                       | `int slot = ttyslot();`                                         |
| `ioctl(fd, request)`           | Envía comandos de control al dispositivo. Común para detectar tamaño del terminal (`TIOCGWINSZ`).       | Saber cuántas columnas tiene la terminal, útil para el layout     | `ioctl(1, TIOCGWINSZ, &w);`                                     |

<details>
<summary><strong>💬 Entrada/Salida Básica</strong></summary>

<br>

| Función       | Descripción                                                                  | Uso común                            | Uso con código                        |
|---------------|------------------------------------------------------------------------------|---------------------------------------|----------------------------------------|
| `printf`      | Imprime texto formateado a la salida estándar.                              | Mensajes de debug o salida del shell | `printf("Hola %s\n", nombre);`        |
| `write`       | Escribe directamente en un descriptor de archivo (stdout, stderr, etc.).    | Imprimir sin usar stdio              | `write(1, "Hola\n", 5);`              |
| `perror`      | Muestra un mensaje de error basado en `errno`.                              | Reportar errores de sistema          | `perror("open");`                     |
| `strerror`    | Devuelve un string que describe un código de error.                         | Mostrar mensaje de error personalizado | `char *msg = strerror(errno);`        |

<details>
<summary><strong>📁 Manejo de Archivos</strong></summary>

<br>

| Función     | Descripción                                                                 | Uso común                                     | Uso con código                                                   |
|-------------|-----------------------------------------------------------------------------|-----------------------------------------------|------------------------------------------------------------------|
| `access`    | Verifica permisos de acceso a un archivo (`F_OK`, `R_OK`, `W_OK`, `X_OK`).  | Comprobar si un archivo existe o es ejecutable | `if (access("file", F_OK) == 0) {...}`                          |
| `open`      | Abre un archivo y devuelve su descriptor.                                   | Abrir archivos para lectura o escritura        | `int fd = open("file.txt", O_RDONLY);`                          |
| `read`      | Lee datos de un descriptor de archivo.                                      | Leer contenido desde un archivo                | `read(fd, buffer, 100);`                                        |
| `close`     | Cierra un descriptor de archivo.                                             | Liberar recursos tras abrir archivos           | `close(fd);`                                                    |
| `unlink`    | Elimina un archivo del sistema de archivos.                                 | Implementar el comando `rm`                    | `unlink("file.txt");`                                           |
| `stat`      | Obtiene información del archivo (nombre, tamaño, permisos).                 | Verificar tipo de archivo o permisos           | `stat("archivo", &st);`                                        |
| `lstat`     | Igual que `stat` pero no sigue enlaces simbólicos.                          | Verificar si un archivo es un enlace simbólico | `lstat("archivo", &st);`                                       |
| `fstat`     | Igual que `stat` pero usando un descriptor de archivo.                      | Obtener info de un archivo ya abierto          | `fstat(fd, &st);`                                               |


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

🧪 Ejemplo Entrada y Lectura de Comandos

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *line;

    while (1)
    {
        line = readline("minishell$ ");
        if (!line)
            break;
        if (*line)
            add_history(line);
        printf("Leído: %s\n", line);
        free(line);
    }
    rl_clear_history();
    return 0;
}

🧪 Ejemplo práctico: Verificar si un archivo existe y leerlo

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    char buffer[101];
    int fd, bytes;

    if (access("readme.txt", F_OK) == 0)
    {
        fd = open("readme.txt", O_RDONLY);
        if (fd == -1)
            return (perror("open"), 1);
        bytes = read(fd, buffer, 100);
        if (bytes > 0)
        {
            buffer[bytes] = '\0';
            write(1, buffer, bytes);
        }
        close(fd);
    }
    else
        write(2, "Archivo no encontrado\n", 23);
    return 0;
}
