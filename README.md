# ArtiSendos-Esp32
Codigo para desarrollar un robot controlado por bluetooth mediante una app

## Descripción

Este repositorio contiene el código fuente para un microcontrolador ESP32. El propósito principal de este código es permitir la comunicación entre el ESP32 y una aplicación a través de Bluetooth Low Energy (BLE). Esta comunicación permite controlar dos motores integrados en un robot.

## Materiales y Requisitos

- App disponible en este repositorio llamada ArtiSendos.apk compatible con BLE
- Microcontrolador ESP32 Dev Kit V1
- Controlador de motor DRV8833
- Dos motores de 5V N20
- Un interruptor ON OFF
- Fuente de alimentacion 5V (Power Bank, o cualquier fuente regulable)

## Diagrama Eléctrico

A continuación se presenta el diagrama eléctrico del sistema. Aquí se muestran las conexiones entre el ESP32, el controlador de motor DRV8833 y los motores del robot.

![artisendos_fritzing_schematics](https://github.com/directsgg/ArtiSendos-Esp32/assets/64875759/3204f870-e92d-49c0-88e5-164b47a61457)


## Uso y pruebas

1. Carga el codigo al ESP32 (en caso de querer cambiar el nombre del dispositivo Bluetooth, todo esta documentado en el codigo).
2. Realiza las conexiones en base al esquema eléctrico.
3. Abre la aplicación, presiona el icono de Bluetooth y busca el dispositivo BLE.
4. Conéctate al ESP32.
5. Usa la aplicación para enviar comandos al ESP32 y controlar los motores del robot.

## Contribuciones

Las contribuciones son bienvenidas. Por favor, abre un problema o realiza un pull request si tienes algo que añadir.

