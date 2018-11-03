# Sistema de alerta temprana de desbordamientos de ríos

## Descripción
La idea de este proyecto es implementar un sistema automatizado de alerta temprana que en ​real time ​permita tener un vistazo de la situacion del río.

Consta de la implementación (simplificada) de los dos softwares implicados: un ​conector​ que (junto a su sensor) realiza las mediciones y un servidor​ que consolide los datos de múltiples conectores y resuelva las consultas de los clientes externos​ del sistema.

El sistema cuenta con varios sensores a lo largo del río, distribuidos en secciones, para la medición del nivel y caudal del agua.
La información de los sensores será procesada localmente y luego enviada a una central.

## Motivación

El presente proyecto fue elaborado como trabajo práctico académico para la materia Taller de Programación I de la Facultad de Ingeniería de la Universidad de Buenos Aires. El mismo, se desarrolló durante el segundo cuatrimestre del año 2015.

## Compilación:

Desde la consola de linux, una vez dentro de la carpeta **source**, ejecutar la siguiente instrucción:
```
make -f Makefile_client_server
```
Si se desean eliminar los archivos generados por dicho Makefile, se debe ejecutar:
```
make -f Makefile_client_server clean
```
## Modo de uso:

Consultar **enunciado_alerta_desbordamiento_rios.pdf**

## Autor
   - Lautaro Ezequiel Rinaldi.
