=====
Avail
=====

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <assign>`_ `Next <beep>`_ 

---------------

::

 Avail [CHIP | FAST | TOTAL | FLUSH] [H | HUMAN]

Synopsis
~~~~~~~~
::


     CHIP/S, FAST/S, TOTAL/S, FLUSH/S, H=HUMAN/S        


Ubicaci�n
~~~~~~~~~
::


     Workbench:C


Funci�n
~~~~~~~
::


     Hace un resumen del uso y disponibilidad de la memoria del sistema.
     Para liberar la memoria no usada que todav�a puede ser asignada
     (bibliotecas, dispositivos, fuentes y dem�s presente en la memoria
     pero que no est� en uso actual), use la opci�n FLUSH.


Entradas
~~~~~~~~
::


     CHIP   --  muestra solamente la memoria "chip".
     FAST   --  muestra solamente la memoria "r�pida".
     TOTAL  --  muestra informaci�n sobre la memoria sin considerar el tipo.
     FLUSH  --  retira las cosas innecesarias residentes en la memoria.
     HUMAN  --  muestra valores m�s legibles (Gigabytes como "G",
                Megabytes como "M", Kilobytes como "K").


Notas
~~~~~
::


     Las memorias "chip" y "r�pida" est�n asociadas con la computadora
     Amiga y no se aplican a tu plataforma de hardware.


