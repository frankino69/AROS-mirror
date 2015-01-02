========
SetClock
========

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <set>`_ `Next <setdefaultfont>`_ 

---------------

::

 SetClock 

Formato
~~~~~~~
::

     SetClock {LOAD|SAVE|RESET}


Synopsis
~~~~~~~~
::

     LOAD/S,SAVE/S,RESET/S


Ubicaci�n
~~~~~~~~~
::

     C:SetClock


Funci�n
~~~~~~~
::

     SetClock se puede usar para:
         o Cargar la hora desde el reloj respaldado por la bater�a,
         o Guardar la hora al reloj respaldado por la bater�a,
         o Restablecer el reloj respaldado por la bater�a.


Ejemplo
~~~~~~~
::


     SetClock LOAD

         pondr� la hora del sistema desde el reloj respaldado por la
         bater�a. En la mayor�a de los sistemas esto se har� 
         autom�ticamente durante el inicio del sistema.

     SetClock SAVE

         pondr� la hora del reloj respaldado por la bater�a de la
         hora actual del reloj del sistema.

     SetClock RESET

         restablecer� el reloj respaldado por la bater�a al valor
         del 1 de enero de 1978 00:00:00. Esto hace si tuvo un
         error y no responde a los comandos normales load y save.


Mire tambi�n
~~~~~~~~~~~~
::

     C:Date, Prefs/Time


