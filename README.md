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

### 🧪 Ejemplo práctico: Verificar si un archivo existe y leerlo

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
```
<details>
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

### 🧪 Ejemplo práctico: Verificar si un archivo existe y leerlo

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
```
