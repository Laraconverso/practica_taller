# Threads
Lara Daniela Converso - 107632

## Diagrama

![img](/docs/diagram.png?raw=true "img")
El diagrama es una simplificación de la logica del POC de threads, las clases faltantes son acceptor, Server, Client y Enemy. 

Cada punto celeste en la lista de queues representa una queue de un jugador distinto. 

## Especificaciones
Se utilizan las bibliotecas externas sockets, threads y queue provistas por la cátedra Veiga en la materia Taller de programación I.

Autor: eldipa

Licencia: GPL v2

Referencias: 
 - https://github.com/eldipa/sockets-en-cpp
 - https://github.com/eldipa/hands-on-threads

## Justificaciones 
Para la queue única del gameloop, implemente una non-blocking queue dado que el gameloop no se debería bloquear en ningún momento y es unbounded porque no tiene un limite predeterminado de comandos a recibir por parte de los jugadores. 
Al igual que las queues asociadas a los clientes (jugadores), por las cuales se realiza el broadcast; todas estas se encuentran en una clase nombrada monitor que contiene una lista de queues de mensajes.  
