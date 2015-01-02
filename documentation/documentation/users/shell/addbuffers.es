==========
AddBuffers
==========

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Next <alias>`_ 

---------------

::

 AddBuffers (drive) [(N)]
 AddBuffers (unidad) [(N)]

Synopsis
~~~~~~~~
::


     DRIVE/A, BUFFERS/N
     UNIDAD/A, B�FERES/N


Ubicaci�n
~~~~~~~~~
::


     Workbench:C


Funci�n
~~~~~~~
::


     Agrega b�feres a la lista de b�feres disponibles de una unidad
     espec�fica. Agregar b�feres acelera el acceso al disco pero tiene
     el inconveniente de usar memoria del sistema (512 bytes por b�fer).
     Especificar un n�mero negativo resta b�feres de la unidad.
         Si se especifica solamente el argumento UNIDAD, se muestra la
     cantidad de b�feres para esa unidad sin cambiar la asignaci�n de
     b�feres. 


Entradas
~~~~~~~~

::


     UNIDAD   --  la unidad a alterar su asignaci�n de b�feres.
     B�FERES  --  la cantidad de b�feres a agregar (o quitar en caso de
                  que sea un n�mero negativo) a la unidad.


