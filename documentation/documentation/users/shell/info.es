====
Info
====

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <if>`_ `Next <join>`_ 

---------------

::

 Info 

Synopsis
~~~~~~~~
::


     DISKS/S, VOLS=VOLUMES/S, GOODONLY/S, BLOCKS/S, DEVICES/M


Ubicaci�n
~~~~~~~~~
::


     Workbench:C


Funci�n
~~~~~~~
::


 Muestra informaci�n sobre los vol�menes y los dispositivos del sistema
 de archivos. Cuando no tiene argumentos, se presenta la informaci�n
 sobre todos los dispositivos y vol�menes hallados en el sistema. Si se
 quiere solamente la informaci�n para algunos dispositivos espec�ficos,
 sus nombres deben darse como argumentos.


Entradas
~~~~~~~~
::


 DISKS     --  muestra la informaci�n sobre los dispositivos del sistema
               de archivos.
 VOLS      --  muestra la informaci�n sobre los vol�menes.
 GOODONLY  --  no muestra informaci�n sobre los malo dispositivos o
               vol�menes.
 BLOCKS    --  muestra informaci�n adicional sobre el tama�o del bloque
               y la cantidad de bloques usados.
 DEVICES   --  los nombres de los dispositivos sobre los que se informar�.


Ejemplo
~~~~~~~
::


 Info

 Unit                 Size    Used    Free Full Errs   State    Type Name
 Foreign harddisk:  964.1M  776.7M  187.4M  81%    0 read/write  OFS Workbench
 RAM:                 8.0M    7.1M    7.1M  12%    0 read/write  OFS Ram Disk


