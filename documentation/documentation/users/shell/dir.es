===
Dir
===

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <delete>`_ `Next <echo>`_ 

---------------

::

 Dir [(dir | pattern)] [OPT A | I | D | F] [ALL] [DIRS] [FILES] [INTER]

Synopsis
~~~~~~~~
::


 DIR,OPT/K,ALL/S,DIRS/S,FILES/S,INTER/S


Ubicaci�n
~~~~~~~~~
::


 Workbench:C


Funci�n
~~~~~~~
::


 DIR muestra cada archivo y directorio contenido en el directorio
 actual o en el especificado. Se listan primero los directorios,
 despu�s en orden alfab�tico, los archivos en dos columnas. Con la 
 combinaci�n CTRL-C se aborta el listado.



Entradas
~~~~~~~~
::


 ALL    --  Muestra todos los subdirectorios y sus archivos de manera
            recursiva.
 DIRS   --  Muestra �nicamente los directorios.
 FILES  --  Muestra solamente los archivos.
 INTER  --  Ingresa al modo interactivo.

            El modo de listado interactivo se detiene despu�s de cada
            nombre para mostrar un signo de interrogaci�n para que 
            puedas escribir alg�n comando. Estos comandos son:

            Return      --  Contin�a con el siguiente archivo o directorio.
            E/ENTER     --  Ingresa al directorio.
            DEL/DELETE  --  Borra el archivo o el directorio vac�o.
            C/COM       --  Hace que el archivo o el directorio sea la
                            entrada de un comando DOS (que es especificado 
                            despu�s de la C o de COM o m�s tarde por separado).
            Q/QUIT      --  Sale del modo interactivo.
            B/BACK      --  Retrocede un nivel de directorio.


