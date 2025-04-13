# minishell
## 📁 Estructura del Proyecto

```bash
minishell/
├── Makefile
├── README.md
├── include/
│   ├── minishell.h        # Header principal
│   ├── parser.h           # Funciones de parsing
│   ├── builtins.h         # Funciones built-in
│   ├── exec.h             # Ejecución de comandos
│   └── env.h              # Manejo de variables de entorno
├── src/
│   ├── main.c             # Bucle principal
│   ├── signal.c           # Manejo de señales
│   ├── prompt.c           # Prompt y readline
│   └── utils/             # Funciones auxiliares
│       └── ft_xxx.c
├── parser/
│   ├── tokenizer.c        # Separación en tokens
│   ├── quotes.c           # Manejo de comillas
│   ├── expand.c           # Expansión de variables
│   └── parser_utils.c     # Funciones auxiliares
├── builtins/
│   ├── echo.c
│   ├── cd.c
│   ├── pwd.c
│   ├── env.c
│   ├── export.c
│   ├── unset.c
│   └── exit.c
├── exec/
│   ├── exec.c             # Ejecución de comandos
│   ├── redir.c            # Redirecciones
│   ├── pipe.c             # Ejecución con pipes
│   └── builtin_check.c    # Decide si un comando es builtin
├── libft/                 # Si usas tu propia libft
│   └── ...

## 📚 Tabla de Contenidos

- [📥 Entrada y Lectura de Comandos](#entrada-y-lectura-de-comandos)
- [💬 Entrada/Salida Básica](#entrada-salida-básica)
- [🌱 Gestión de Procesos](#gestión-de-procesos)
- [🧠 Señales](#señales)
- [📂 Directorios](#directorios)
- [📌 Variables de Entorno](#variables-de-entorno)
- [📍 Localización y Movimiento](#localización-y-movimiento)
- [⚙️ Terminal (termcap)](#terminal-termcap)
- [🔀 Duplicación y Pipes](#duplicación-y-pipes)
- [🚀 Ejecución](#ejecución)

---

<details>
<summary><strong>📥 Entrada y Lectura de Comandos</strong></summary>

<br>

| Función               | Descripción                                                                 | Uso común                                       | Uso con código                        |
|------------------------|-----------------------------------------------------------------------------|------------------------------------------------|----------------------------------------|
| `readline(prompt)`     | Muestra el prompt y lee una línea del usuario.                             | Leer comandos con edición de línea             | `char *s = readline("mini$ ");`        |
| `add_history(line)`    | Añade una línea al historial.                                               | Hacer ↑ y ↓ para ver comandos anteriores       | `if (*s) add_history(s);`              |
| `rl_clear_history()`   | Limpia el historial de readline.                                            | Al salir del shell                             | `rl_clear_history();`                  |
| `rl_on_new_line()`     | Informa a readline que empieza una nueva línea.                            | Tras Ctrl+C                                    | `rl_on_new_line();`                    |
| `rl_replace_line()`    | Reemplaza la línea actual del prompt.                                      | Borrar input tras Ctrl+C                       | `rl_replace_line("", 0);`              |
| `rl_redisplay()`       | Redibuja el prompt.                                                         | Refrescar prompt                               | `rl_redisplay();`                      |
| `isatty(fd)`           | Comprueba si `fd` es una terminal.                                          | Detectar si en modo interactivo                | `if (isatty(0))`                        |
| `ttyname(fd)`          | Devuelve el nombre del terminal asociado al descriptor.                     | Debug                                           | `char *name = ttyname(0);`             |
| `ttyslot()`            | Número de terminal usado.                                                   | Poca utilidad común                            | `int slot = ttyslot();`                |
| `ioctl(fd, req)`       | Control de bajo nivel del terminal (p. ej. tamaño).                         | Detectar tamaño de terminal                    | `ioctl(1, TIOCGWINSZ, &win);`          |

</details>

<details>
<summary><strong>💬 Entrada/Salida Básica</strong></summary>

<br>

| Función     | Descripción                                            | Uso común                          | Uso con código                      |
|--------------|--------------------------------------------------------|-------------------------------------|--------------------------------------|
| `printf`     | Imprime texto formateado.                              | Mostrar mensajes                    | `printf("Hola %s\n", nombre);`      |
| `write`      | Escribe directamente en un descriptor.                 | Salida rápida                       | `write(1, "hola\n", 5);`            |
| `perror`     | Imprime un error basado en `errno`.                    | Mostrar errores                     | `perror("open");`                   |
| `strerror`   | Devuelve string de `errno`.                            | Mensajes personalizados             | `char *msg = strerror(errno);`      |

</details>

<details>
<summary><strong>🌱 Gestión de Procesos</strong></summary>

<br>

| Función     | Descripción                                              | Uso común                           | Uso con código                      |
|--------------|----------------------------------------------------------|--------------------------------------|--------------------------------------|
| `fork`       | Crea un nuevo proceso.                                   | Crear hijos                         | `pid_t pid = fork();`               |
| `wait`       | Espera que un hijo termine.                              | Sincronización de procesos          | `wait(NULL);`                       |
| `waitpid`    | Espera por un hijo específico.                           | Controlar varios hijos              | `waitpid(pid, &status, 0);`         |
| `wait3/4`    | Como `waitpid` pero con info adicional.                  | Estadísticas (no obligatorio)       | -                                   |
| `kill`       | Enviar una señal a un proceso.                           | Terminar procesos                   | `kill(pid, SIGINT);`                |
| `exit`       | Terminar un proceso actual.                              | Finalizar minishell o un hijo       | `exit(0);`                          |

</details>

<details>
<summary><strong>🧠 Señales</strong></summary>

<br>

| Función         | Descripción                                        | Uso común                           | Uso con código                      |
|------------------|----------------------------------------------------|--------------------------------------|--------------------------------------|
| `signal`         | Establece un handler de señal.                    | Capturar Ctrl+C o Ctrl+\             | `signal(SIGINT, handler);`          |
| `sigaction`      | Más control que `signal()`.                       | Buenas prácticas                     | `sigaction(SIGINT, &sa, NULL);`     |
| `sigemptyset`    | Vacía una máscara de señales.                     | Preparar `sigaction`                | `sigemptyset(&sa.sa_mask);`         |
| `sigaddset`      | Añade señales a una máscara.                      | Bloquear señales específicas         | `sigaddset(&sa.sa_mask, SIGQUIT);`  |

</details>

<details>
<summary><strong>📂 Directorios</strong></summary>

<br>

| Función        | Descripción                                               | Uso común                          | Uso con código                        |
|-----------------|-----------------------------------------------------------|-------------------------------------|----------------------------------------|
| `opendir`       | Abre un directorio.                                       | Comandos como `ls`                 | `DIR *d = opendir(".");`             |
| `readdir`       | Lee una entrada del directorio.                           | Iterar archivos                    | `struct dirent *f = readdir(d);`     |
| `closedir`      | Cierra un directorio.                                     | Liberar recursos                   | `closedir(d);`                        |

</details>

<details>
<summary><strong>📌 Variables de Entorno</strong></summary>

<br>

| Función      | Descripción                                            | Uso común                          | Uso con código                       |
|---------------|--------------------------------------------------------|-------------------------------------|---------------------------------------|
| `getenv`      | Devuelve el valor de una variable de entorno.         | Leer PATH, HOME, etc.              | `char *p = getenv("PATH");`          |

</details>

<details>
<summary><strong>📍 Localización y Movimiento</strong></summary>

<br>

| Función       | Descripción                                        | Uso común                        | Uso con código                        |
|----------------|----------------------------------------------------|-----------------------------------|----------------------------------------|
| `getcwd`       | Obtiene el directorio actual.                     | Para `pwd`                        | `char cwd[1024]; getcwd(cwd, 1024);` |
| `chdir`        | Cambia el directorio actual.                      | Para `cd`                         | `chdir("/home");`                     |

</details>

<details>
<summary><strong>⚙️ Terminal (termcap)</strong></summary>

<br>

| Función      | Descripción                                            | Uso común                            | Uso con código                        |
|---------------|--------------------------------------------------------|---------------------------------------|----------------------------------------|
| `tgetent`     | Inicializa la información del terminal.               | Configurar termcap                   | `tgetent(NULL, getenv("TERM"));`      |
| `tgetflag`    | Devuelve si una capacidad está presente.              | Revisar flags del terminal           | `tgetflag("am");`                      |
| `tgetnum`     | Devuelve el valor numérico de una capacidad.          | Obtener tamaño, etc.                 | `tgetnum("co");`                       |
| `tgetstr`     | Devuelve string de una capacidad.                     | Para construir secuencias            | `tgetstr("cl", &area);`               |
| `tgoto`       | Posicionamiento cursor                                | Generar secuencia para moverse       | `tgoto(cm, col, row);`                |
| `tputs`       | Escribe secuencias termcap                            | Imprimir secuencia en pantalla       | `tputs(seq, 1, putchar);`             |

</details>

<details>
<summary><strong>🔀 Duplicación y Pipes</strong></summary>

<br>

| Función     | Descripción                                        | Uso común                          | Uso con código                          |
|--------------|----------------------------------------------------|-------------------------------------|------------------------------------------|
| `dup`        | Duplica un descriptor.                             | Redirecciones simples               | `int fd2 = dup(fd1);`                   |
| `dup2`       | Duplica en un descriptor específico.               | Redirección `2>`, `1>`, etc.        | `dup2(fd, STDOUT_FILENO);`             |
| `pipe`       | Crea un pipe entre procesos.                       | Comunicación con `|`                | `pipe(fd);`                             |

</details>

<details>
<summary><strong>🚀 Ejecución</strong></summary>

<br>

| Función     | Descripción                                        | Uso común                              | Uso con código                            |
|--------------|----------------------------------------------------|-----------------------------------------|--------------------------------------------|
| `access`     | Comprueba permisos sobre un archivo.               | Verificar si un binario existe         | `access(cmd, X_OK);`                      |
| `open`       | Abre un archivo.                                   | Redirecciones                          | `open("file", O_RDONLY);`                 |
| `read`       | Lee de un descriptor.                              | Leer de archivos o input               | `read(fd, buf, 32);`                      |
| `close`      | Cierra un descriptor.                              | Limpieza                               | `close(fd);`                              |
| `execve`     | Ejecuta un binario.                                | Lanzar comandos                        | `execve(path, args, env);`               |
| `stat`       | Info de archivo.                                   | Obtener permisos, tipo                 | `stat(file, &st);`                        |
| `lstat`      | Como `stat` pero sigue enlaces simbólicos.         | Verificar si es symlink                | `lstat(file, &st);`                       |
| `fstat`      | Como `stat` pero con descriptor.                   | Uso interno en pipes/redirecciones     | `fstat(fd, &st);`                         |
| `unlink`     | Borra un archivo.                                  | Comando `rm`                           | `unlink("file.txt");`                    |

</details>

