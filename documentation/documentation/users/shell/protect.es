=======
Protect
=======

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <prompt>`_ `Next <quit>`_ 

---------------

::

 Protect 

Synopsis
~~~~~~~~
::


     FILE/A,FLAGS,ADD/S,SUB/S,ALL/S,QUIET/S


Ubicaci�n
~~~~~~~~~
::


     Workbench:c


Funci�n
~~~~~~~
::


     Agrega o quita los bits de protecci�n de un archivo o directorio.
     
     Protect permite el uso de revisiones recursivas de directorio y
     pattern matching para proteger muchas archivos/directorios
     de una vez.


Entradas
~~~~~~~~
::


     FILE   --  Un archivo , un directorio o un patr�n a ###match.
     FLAGS  --  Una o m�s de las siguientes banderas:


                 S - Gui�n
                 P - Puro
                 A - Archivo
                 R - Leer
                 W - Escribir
                 E - Ejecutar
                 D - Borrar

     ADD    --  Permite que se pongan los bits; de esto, es permitido.
     SUB    --  Permite que los bits sean limpiados y por esto no permitido.
     ALL    --  Permite una revisi�n recursiva del volumen/directorio.
     QUIET  --  Suprime cualquier salida al shell.


Resultado
~~~~~~~~~
::


     Standard DOS return codes.
     Los c�digos devueltos DOS normales.


Ejemplo
~~~~~~~
::


     Protect ram: e add all

         Revisa recursivamente el volumen ram y agrega el bit de ejecutable.


Vea tambi�n
~~~~~~~~~~~
::


     dos.library/SetProtection()


