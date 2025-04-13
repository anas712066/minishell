# minishell

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
