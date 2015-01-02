===========
RequestFile
===========

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <requestchoice>`_ `Next <run>`_ 

---------------

::

 RequestFile 

Synopsis
~~~~~~~~
::


     DRAWER,FILE/K,PATTERN/K,TITLE/K,POSITIVE/K,NEGATIVE/K,
     ACCEPTPATTERN/K,REJECTPATTERN/K,SAVEMODE/S,MULTISELECT/S,
     DRAWERSONLY/S,NOICONS/S,PUBSCREEN/K,INITIALVOLUMES/S


Ubicaci�n
~~~~~~~~~
::


     Workbench:c


Funci�n
~~~~~~~
::

 
     Crea un requester de archivo. Los archivos seleccionados se mostrar�n
     separados por espacios. Si no se selecciona ning�n archivo el 
     c�digo devuelto es 5 (advertencia).
 

Entradas
~~~~~~~~
::

     DRAWER          -- el contenido inicial del campo caj�n
     FILE            -- el contenido inicial del campo archivo
     PATTERN         -- el contenido del campo patr�n (p.e. #?.c)
     TITLE           -- el t�tulo del cuadro de di�logo
     POSITIVE        -- la cadena para el bot�n izquierdo
     NEGATIVE        -- la cadena para el bot�n derecho
     ACCEPTPATTERN   -- solamente se muestran los archivos con igual patr�n
     REJECTPATTERN   -- no se muestran los archivos que satisfacen el patr�n
     SAVEMODE        -- el requester se presenta como un requester guardar
     MULTISELECT     -- se puede seleccionar m�s de un archivo
     DRAWERSONLY     -- solamente se presentan los cajones
     NOICONS         -- no se muestran los archivos de �cono (#?.info)
     PUBSCREEN       -- el requester se abre en la pantalla p�blica dada
     INITIALVOLUMES  -- muestra los vol�menes
     

Resultado
~~~~~~~~~
::


     Los c�digos de error DOS normales.


