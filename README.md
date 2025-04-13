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

</details>

<details>
<summary><strong>💬 Entrada/Salida Básica</strong></summary>

<br>

| Función     | Descripción                                                         | Uso común                            | Uso con código                        |
|-------------|---------------------------------------------------------------------|---------------------------------------|----------------------------------------|
| `printf`    | Imprime texto formateado a la salida estándar.                      | Mensajes de debug o salida del shell | `printf("Hola %s\n", nombre);`        |
| `write`     | Escribe directamente en un descriptor de archivo.                   | Imprimir sin usar stdio              | `write(1, "Hola\n", 5);`              |
| `perror`    | Muestra un mensaje de error basado en `errno`.                      | Reportar errores de sistema          | `perror("open");`                     |
| `strerror`  | Devuelve un string que describe un código de error.                 | Mostrar mensaje de error personalizado | `char *msg = strerror(errno);`        |

</details>

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

</details>

<details>
<summary><strong>🌱 Gestión de Procesos</strong></summary>

<br>

| Función      | Descripción                                                                | Uso común                                 | Uso con código                         |
|--------------|----------------------------------------------------------------------------|--------------------------------------------|-----------------------------------------|
| `fork()`     | Crea un nuevo proceso (hijo) idéntico al actual.                          | Ejecutar comandos creando nuevos procesos  | `pid_t pid = fork();`                  |
| `wait()`     | Espera a que cualquier proceso hijo termine.                              | Evitar procesos zombis                     | `wait(NULL);`                          |
| `waitpid()`  | Espera a que un proceso hijo específico termine.                          | Sincronizar procesos hijos individualmente | `waitpid(pid, NULL, 0);`               |
| `wait3()`    | Similar a `wait()`, pero recoge información de uso de recursos.           | Avanzado, normalmente no usado             | `wait3(NULL, 0, &usage);`              |
| `wait4()`    | Similar a `waitpid()`, también devuelve uso de recursos.                  | Poco común, útil para profiling            | `wait4(pid, NULL, 0, &usage);`         |
| `kill()`     | Envía una señal a un proceso.                                              | Terminar procesos con `SIGINT`, `SIGKILL`  | `kill(pid, SIGINT);`                   |
| `exit()`     | Termina el proceso actual y devuelve un código de salida.                 | Salir del minishell con código             | `exit(0);`                             |

</details>

<details>
<summary><strong>🧠 Señales</strong></summary>

<br>

| Función          | Descripción                                                                  | Uso común                                   | Uso con código                              |
|------------------|------------------------------------------------------------------------------|----------------------------------------------|----------------------------------------------|
| `signal()`       | Define una función para manejar una señal.                                   | Manejar Ctrl+C (SIGINT) o Ctrl+\ (SIGQUIT)  | `signal(SIGINT, handler);`                  |
| `sigaction()`    | Alternativa más robusta a `signal()` para manejar señales.                   | Control más preciso sobre señales            | `sigaction(SIGINT, &act, NULL);`            |
| `sigemptyset()`  | Inicializa una máscara de señales vacía.                                     | Preparar `sigaction`                         | `sigemptyset(&act.sa_mask);`                |
| `sigaddset()`    | Añade una señal a una máscara.                                               | Evitar interrupciones en zonas críticas      | `sigaddset(&act.sa_mask, SIGINT);`          |

</details>

<details>
<summary><strong>📂 Directorios</strong></summary>

<br>

| Función       | Descripción                                                       | Uso común                          | Uso con código                         |
|----------------|-------------------------------------------------------------------|-------------------------------------|-----------------------------------------|
| `opendir()`    | Abre un directorio y devuelve un puntero.                        | Leer contenido de directorios      | `DIR *dir = opendir(".");`             |
| `readdir()`    | Lee una entrada del directorio abierto.                          | Listar archivos como en `ls`       | `struct dirent *e = readdir(dir);`     |
| `closedir()`   | Cierra un directorio previamente abierto.                        | Liberar recursos                   | `closedir(dir);`                        |

</details>

<details>
<summary><strong>📌 Variables de Entorno</strong></summary>

<br>

| Función     | Descripción                                               | Uso común                               | Uso con código                          |
|-------------|-----------------------------------------------------------|------------------------------------------|------------------------------------------|
| `getenv()`  | Devuelve el valor de una variable de entorno.            | Obtener `PATH`, `HOME`, `PWD`, etc.     | `char *path = getenv("PATH");`          |

</details>

<details>
<summary><strong>📍 Localización y Movimiento</strong></summary>

<br>

| Función      | Descripción                                                              | Uso común                                | Uso con código                             |
|---------------|--------------------------------------------------------------------------|-------------------------------------------|---------------------------------------------|
| `getcwd()`    | Obtiene el path del directorio actual.                                   | Implementar `pwd`                         | `char cwd[1024]; getcwd(cwd, sizeof(cwd));` |
| `chdir()`     | Cambia el directorio actual.                                              | Implementar `cd`                          | `chdir("/home/user");`                      |

</details>

<details>
<summary><strong>⚙️ Terminal (termcap)</strong></summary>

<br>

| Función       | Descripción                                                                 | Uso común                                  | Uso con código                          |
|---------------|-----------------------------------------------------------------------------|---------------------------------------------|------------------------------------------|
| `tcgetattr()` | Obtiene los atributos de la terminal.                                       | Configuración avanzada                     | `tcgetattr(STDIN_FILENO, &term);`       |
| `tcsetattr()` | Establece atributos de la terminal.                                         | Configuración avanzada                     | `tcsetattr(STDIN_FILENO, TCSANOW, &term);` |
| `tgetent()`   | Inicializa estructuras termcap desde la variable de entorno `TERM`.        | Requerido para `tgetstr` y otras funciones | `tgetent(NULL, getenv("TERM"));`        |
| `tgetflag()`  | Obtiene un flag booleano del terminal.                                     | Leer capacidades booleanas                 | `tgetflag("bs");`                        |
| `tgetnum()`   | Obtiene un valor numérico de capacidades del terminal.                    | Leer tamaño, etc.                          | `tgetnum("co");`                         |
| `tgetstr()`   | Devuelve una string de capacidad del terminal.                             | Leer secuencias de escape ANSI             | `tgetstr("cl", &area);`                  |
| `tgoto()`     | Devuelve una string para mover el cursor a una coordenada.                 | Control de cursor                          | `tgoto(cm, col, row);`                   |
| `tputs()`     | Imprime una string termcap con control de padding.                         | Ejecutar comandos termcap como limpiar     | `tputs(cl, 1, putchar);`                 |

</details>

<details>
<summary><strong>🔀 Duplicación y Pipes</strong></summary>

<br>

| Función     | Descripción                                                       | Uso común                          | Uso con código                         |
|-------------|-------------------------------------------------------------------|-------------------------------------|-----------------------------------------|
| `dup()`     | Duplica un descriptor de archivo.                                | Redireccionar entrada/salida       | `int fd_copy = dup(fd);`               |
| `dup2()`    | Duplica un descriptor a un número específico.                    | Redirección con `stdin`, `stdout`  | `dup2(fd, STDOUT_FILENO);`             |
| `pipe()`    | Crea un pipe entre dos procesos.                                 | Comunicación entre procesos        | `pipe(fd);`                            |

</details>

<details>
<summary><strong>🚀 Ejecución</strong></summary>

<br>

| Función     | Descripción                                                      | Uso común                         | Uso con código                            |
|-------------|------------------------------------------------------------------|------------------------------------|---------------------------------------------|
| `execve()`  | Ejecuta un nuevo programa reemplazando el actual.                | Ejecutar comandos externos         | `execve("/bin/ls", args, env);`             |

</details>
