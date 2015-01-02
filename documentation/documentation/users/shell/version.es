=======
Version
=======

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <unsetenv>`_ `Next <wait>`_ 

---------------

::

 Version [<library|device|file>] [<version #>] [<revision #>] [FILE] [FULL] [RES]

Synopsis
~~~~~~~~
::


     NAME/M,MD5SUM/S,VERSION/N,REVISION/N,FILE/S,FULL/S,RES/S


Ubicaci�n
~~~~~~~~~
::


     Workbench:C


Funci�n
~~~~~~~
::


     Imprime o revisa la versi�n y la informaci�n de revisi�n de un
     archivo, biblioteca o dispositivo.
       

Entradas
~~~~~~~~
::


     NAME      -- el nombre de un archivo, biblioteca o dispositivo a 
                  revisar. Si no se especifica, se imprime la versi�n y
                  revisi�n de Kickstart.
     MD5SUM    -- FIXME what is that?
     VERSION   -- revisa la versi�n y devuelve el c�digo de error 5 
                  (advertencia) si la versi�n del archivo es menor.
     REVISION  -- revisa la revisi�n y devuelve el c�digo de error 5
                  (advertencia) si la revisi�n del archivo es menor.
     FILE      -- lee de un archivo e ignora las bibliotecas y dispositivos cargados.
     FULL      -- imprime informaci�n adicional
     RES       -- consigue la versi�n de los comandos residentes
     

