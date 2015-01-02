======
Assign
======

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <ask>`_ `Next <avail>`_ 

---------------

::

 Assign [(name):] [{(target)}] [LIST] [EXISTS] [DISMOUNT] [DEFER]
 Assign [(nombre):] [{(objetivo)}] [LISTA] [EXISTE] [DESMONTAR] [DEFERIR]

Synopsis
~~~~~~~~
::


     NAME, TARGET/M, LIST/S, EXISTS/S, DISMOUNT/S, DEFER/S, PATH/S, ADD/S,
     REMOVE/S, VOLS/S, DIRS/S, DEVICES/S


Ubicaci�n
~~~~~~~~~
::


     Workbench:C


Funci�n
~~~~~~~
::


     ASSIGN crea una referencia a un archivo o directorio. La referencia
     es un nombre de dispositivo l�gico, lo que lo hace muy conveniente
     para especificar objetos asignados usando la referencia en vez de 
     su ruta.

     Si se dan los argumentos NOMBRE y OBJETIVO, ASSIGN asigna el nombre
     l�gico dado al objetivo especificado. Si el NOMBRE dado ya fue
     asignado a un archivo o directorio, el nuevo objetivo reemplaza al
     anterior. Se debe incluir el caracter : despu�s del argumento
     NOMBRE.

     Si solamente se da el argumento NOMBRE, se quita cualquier asignaci�n
     a ese NOMBRE. Si no se da ning�n argumento, se listan todas 
     las asignaciones l�gicas hechas.


Entradas
~~~~~~~~
::


     NOMBRE    --  el nombre que se deber�a asignar a un archivo o directorio.
     OBJETIVO  --  un o m�s archivos o directorios a ser asignados el NOMBRE.
     EXISTS    --  si el NOMBRE ya fue asignado, pone a bandera de condici�n WARN
                   (advertir).
     DISMOUNT  --  quita el NOMBRE de volumen o dispositivo de la lista dos.
     DEFER     --  hace un ASSIGN a una ruta o directorio que no necesita
                   existir en el momento de la asignaci�n. La primera vez que
                   el NOMBRE es referenciado, el NOMBRE es ###bound al objeto.
     PATH      --  ruta a asignar con una asignaci�n ###non-binding. Esto
                   significa que la asignaci�n es reevaluada cada vez que
                   se hace una referencia a NOMBRE. Igual que para DEFER, la
                   ruta no tiene que existir cuando el comando ASSIGN es ejecutado.
     ADD       --  agrega otro objeto a NOMBRE sin reemplazar el previo
                   (multiasignaci�n).
     REMOVE    --  quita un ASSIGN.
     VOLS      --  muestra los vol�menes asignados si est� en modo LIST.
     DIRS      --  muestra los directorios asignados si est� en modo LIST.
     DEVICES   --  muestra los dispositivos asignados si est� en modo LIST.
     

