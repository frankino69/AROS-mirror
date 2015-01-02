====
Date
====

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <copy>`_ `Next <delete>`_ 

---------------

::

 Date [<day>] [<date>] [<time>] [TO | VER <filename>]

Synopsis
~~~~~~~~
::


     DAY,DATE,TIME,TO=VER/K


Ubicaci�n
~~~~~~~~~
::


     Workbench:C


Funci�n
~~~~~~~
::


     Muestra o pone la hora y/o fecha del sistema.


Entradas
~~~~~~~~
::


     DAY  -- pone la fecha por nombre (lunes, martes, ..., ma�ana, ayer)
     DATE -- pone la fecha con el formato DD--MMM--YY.
             Para MMM ya sea el n�mero o las tres primeras letras del
             mes en ingl�s.
     TIME -- pone la hora con el formato HH:MM:SS
     TO   -- la salida es enviada a un archivo.


Ejemplo
~~~~~~~
::


     date 2-feb-06
     date 21:10


