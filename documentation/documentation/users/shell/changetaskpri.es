=============
ChangeTaskPri
=============

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <cd>`_ `Next <copy>`_ 

---------------

::

 ChangeTaskPri 

Formato
~~~~~~~
::

     ChangeTaskPri <priority> [ PROCESS <process number> ]


Synopsis
~~~~~~~~
::

     PRI=PRIORITY/A/N,PROCESS/K/N


Location
~~~~~~~~
::

     Workbench:c


Funci�n
~~~~~~~
::

     El comando ChangeTaskPri se usa para cambiar la prioridad de
     ejecuci�n actual de una tarea. Como AROS es un sistema operativo
     multitarea, puedes determinar qu� tarea recibe m�s tiempo de CPU
     cambiando su prioridad.

     El valor de |priority| puede variar entre -128 y 127; sin embargo,
     los valores superiores a 4 no se recomiendan porque pueden hacer
     que la tarea interfiera con procesos vitales del sistema. Valores
     m�s altos le dar�n a la tarea una mayor prioridad de la CPU.

     Puedes usaar el comando Status para examinar la lista de las Tareas
     que se est�n ejecutando junto con sus n�meros de proceso.


Ejemplo
~~~~~~~
::

     
     1.SYS:> ChangeTaskPri 1 Process 1

         Establece la prioridad del proceso actual a 1.

     1.SYS:> ChangeTaskPri 1

         Tambi�n establece la prioridad del proceso actual a 1.


Mira tambi�n
~~~~~~~~~~~~
::

     Status


