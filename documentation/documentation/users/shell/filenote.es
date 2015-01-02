========
Filenote
========

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <fault>`_ `Next <get>`_ 

---------------

::

 Filenote 

Synopsis
~~~~~~~~
::


     FILE/A,COMMENT,ALL/S,QUIET/S


Ubicaci�n
~~~~~~~~~
::


     Workbench:c


Funci�n
~~~~~~~
::


     Agrega un comentario a un archivo o directorio.

     Filenote permite una revisi�n recursiva de todos los directorios 
     agregando comentarios a cada archivo/directorio si encuentra que 
     cumple el patr�n de archivo especificado.


Entradas
~~~~~~~~
::


     FILE    - Siempre se debe especificar. Puede ser un nombre de archivo
               con la ruta completa o un patr�n de archivo que debe ser 
               satisfecho.

     COMMENT - La cadena ASCII que se agregar� como un comentario al 
               archivo(s)/directorio(s) especificado.

               Para proporcionar un comentario que incluye comillas, se
               las debe preceder con un asterisco.

                 i.e. Filenote FILE=RAM:test.txt COMMENT=*"hello*"

     ALL     - Par�metro booleano. Si se especifica, Filenote revisa 
               los directorios que satisfacen el patr�n especificado,
               recursivamente.

     QUIET   - Par�metro booleano. Si se especifica, no se enviar� ning�n
               texto de diagn�stico a stdout.


Resultado
~~~~~~~~~
::


     Los c�digos de regreso DOS normales.


Ejemplo
~~~~~~~
::


     Filenote ram: hello all

         Recurses through each directory in RAM: adding "hello" as a
         filenote to each file/directory.
         Pasa recursivamente por cada directorio en RAM: agregando
         "hello" como filenote a cada archivo/directorio.


Notas
~~~~~
::


     Output from AROS' Filenote is more neat and structured than the
     standard Filenote command.
     La salida del Filenote de AROS es m�s ###neat y estructurada que
     la del comando Filenote normal.

     Does not yet support multi-assigns.
     Todav�a no soporta multiasignaciones.


Tambi�n vea
~~~~~~~~~~~
::


     dos.library/SetComment()


