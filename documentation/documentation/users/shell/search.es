======
Search
======

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <run>`_ `Next <set>`_ 

---------------

::

 Search 

Synopsis
~~~~~~~~
::


 Search [FROM] {(name | pattern} [SEARCH] (string | pattern) [ALL] 
        [NONUM] [QUIET] [QUICK] [FILE] [PATTERN] [LINES=Number]


Ubicaci�n
~~~~~~~~~
::


 Workbench:C


Funci�n
~~~~~~~
::


 Search busca en los archivos contenidos en el directorio FROM una
 cadena especificada (SEARCH); si el switch ALL est� especificado,
 tambi�n se busca en los subdirectorios del directorio FROM. Se presentan
 los nombres de todos los archivos que contienen la cadena SEARCH 
 junto con el n�mero de rengl�n donde se encuentra.
      Si se aprieta CTRL-C, se deja de buscar. CTRL-D abandonar� la
      b�squeda en el archivo actual.


Entradas
~~~~~~~~
::


 NONUM    --  no se imprimen los n�meros de rengl�n
 QUIET    --  no se muestra el nombre del archivo donde se busca
 QUICK    --  la salida es m�s compacta
 FILE     --  busca un nombre de archivo en vez de una cadena
 PATTERN  --  cuando busca usa el ###matching de patr�n
 CASE     --  cuando busca usa un ###matching de patr�n sensitivo a las may�sculas
 LINES    --  se mostrar�n los renglones posteriores al rengl�n que
              cumpla con el patr�n.


Resultado
~~~~~~~~~
::


 Si se encuentra el objeto, la bandera de condici�n es puesta a 0. De
 otro modo es puesta WARN.


