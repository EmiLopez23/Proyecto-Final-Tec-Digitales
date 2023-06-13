


![Austral Ingenieria](https://encrypted-tbn0.gstatic.com/images?q=tbn%3AANd9GcQooGo7vQn4t9-6Bt46qZF-UY4_QFpYOeh7kVWzwpr_lbLr5wka)


# Proyecto 34-websock

## Secciones

- [Objetivo](#objetivo)
- [Hardware](#hardware)
- [Programa](#programa)
- [platformio.ini](#platformio.ini)
- [Bibliotecas](#bibliotecas)
- [Constantes](#constantes)
- [WiFi](#wifi)
- [Links](#links)
- [Videos](#videos)

## Objetivo

>   Crear una página que se comunique por WebSockets con el ESP32  
>   Ello permite una respuesta muy rápida, lo que se demuestra con tres acciones  
>   1.- Manejar el brillo de un LED mediante un copntrol deslizante  
>   2.- Enviar un texto del ESP32 a la pagina de Web  
>   3.- Enviar un texto desde la pagina de Web al ESP32  

>   Para ello, en la página de Web se presentarán tres controles  
>   a.- Un control deslizante para modificar el brillo del LED  
>   b.- Un área que se puede cambiar de tamaño donde aparecen los textos que se escriben en la interfase serie del ESP32  
>   c.- Una área de una línea donde se puede escribir y aparece en la interfase serie del ESP32  


## Hardware

   1 LED  
   1 Resistor 220 ohm  

   Conectar Anodo de LED a GPIO "LED"  
   Conectar cátodo de LED a un extremo de resistor de 220 ohm  
   Conectar el otro extremo del resistor de 220 ohm a GND  

## Programa

   (9)  Archivo de inclusión del sistema Arduino  
   (12-14)  Archivos de inclusión de biblioteca Arduino y de bibliotecas externas  
   (16)  Archivo de inclusión de este proyecto para conexión a WiFi  
   (17)  Archivo de inclusión de página de Web _webpage.h_ (se encuentra en el mismo directorio que _main.cpp_)  

   (19-23) Comentario de constantes definidas en _platformio,ini_  
   (25-29) Constantes del módulo para trabajar con PWM  

   (31-34) Creación de objetos  (constructores)  
   (33)  _server_ objeto de tipo WebServer  
   (34)  _webSocket_ de tipo _WebSocketsServer_ operando sobre port 81  

   (40-67) _webSocketEvent_: callback function que se llama cada vez que se recibe un mensaje
   (51) Hay acción solo para _type_ de tipo _texto_  
   (53) Se analiza el _payload_ para ver si en la primera posición posee un caracter _#_
   (54-59) En ese caso, se convierte el resto del string que se encuentra en el _payload_ a _long_ y dicho valor se utiliza para ajustar el PWM que ataca el LED, aparte de imprimirlo en la interfase serie del ESP32  
   (60-65) En caso contrario, se imprime el _payload_ de longitud _length_ sobre la interfase serie del ESP32  

   (73-87) _setup_  
   (76) Inicialización de _Serial_  
   (78-79) Inicialización de PWM  
   (81) Conexión a WiFi  
   (83) Cargar la página Web  
   (84) Arrancar el servidor
   (85) Arrancar los _Web Sockets_  
   (86) Registrar la _callback function webSocketEvent_  

   (89-101) _loop_  
   (92) _array c_ de 1 posición para guardar cada caracter de _Serial_  
   (94) _webSocket.loop_: Para manejar la recepción del _broadcast_ de _webSocket_ los eventos 1 y 3 listados en _Objetivo_ de este documento, llamando a la función de _callback_ _webSocketEvent_  
   (95) _server.handleClient_ para manejar los requerimientos normales al server  
   (96) Determinar si hay un caracter en la interfase serie del ESP32 hacia la PC   
   (98) si hay, se deposita en la única posición del arreglo _c_  
   (99) y se realiza un envío por _broactast_ de dicho caracter   

## platformio.ini

   Define:  
   _LED_OFF_: Para definir si el valor para apagar el LED es _LOW_ o _HIGH_   
   _LED_: GPIO donde está conectado el LED
   _SERIAL_BAUD_: Baud rate de la conexión serie 


## Bibliotecas

   Aparte de las bibliotecas propias del sistema Arduino:  

   _WebSockets_: Biblioteca para usar Web Sockets  

## Constantes

  Las definidas en _platformio.ini_  
  Dentro de _main.cpp_ las tres constantes para manejar _PWM_

## WiFi

 Para acceso a WiFi simplificado usado en este proyecto, ver archivo _esp32wifi.md_ en este mismo directorio.  

## Links

  El siguiente link explica como funcionan los _Web Sockets_, da un ejemplo de aplicación que no es exactamente igual al que se presenta aquí pero creo que es muy claro para entender el tema.

[Shawn Hymel - Arduino WebSocket Server Using an ESP32](https://shawnhymel.com/1675/arduino-websocket-server-using-an-esp32/)

## Videos

[How to Make an Arduino WebSocket Server with an ESP32](https://www.youtube.com/watch?v=ZbX-l1Dl4N4&t=63s)


