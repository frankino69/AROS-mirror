====
Else
====

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <echo>`_ `Next <endcli>`_ 

---------------

::

 Else 

Ubicaci�n
~~~~~~~~~
::


     Workbench:C


Funci�n
~~~~~~~
::


     Separa los bloques 'verdadero' y 'falso' de una sentencia SI. El bloque
     que sigue a un comando ELSE se ejecuta si la condici�n en la sentencia
     previa SI era falsa.


Ejemplo
~~~~~~~
::


     If EXISTS Sys:Devs
         Copy random.device Sys:Devs/
     Else
         Echo "Cannot find Sys:Devs"
     EndIf


Tambi�n mira
~~~~~~~~~~~~
::


     If, EndIf


