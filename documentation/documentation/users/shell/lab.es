===
Lab
===

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <join>`_ `Next <list>`_ 

---------------

::

 Lab 

Ubicaci�n
~~~~~~~~~
::


     Workbench:C


Funci�n
~~~~~~~
::


     En un archivo de gui�n declara una etiqueta. Esta etiqueta puede estar
     referida a un comando Skip.


Ejemplo
~~~~~~~
::


    If NOT EXISTS S:User-Startup
        Skip NoUserSeq
    EndIf

    FailAt 20
    Execute S:User-Startup
    Quit

    Lab NoUserSeq
    Echo "No User-Startup found"


Tambi�n vea
~~~~~~~~~~~
::


    Skip


