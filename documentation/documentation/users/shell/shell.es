=====
Shell
=====

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <setkeyboard>`_ `Next <skip>`_ 

---------------

::

 Shell 

Synopsis
~~~~~~~~
::


     COMMAND/K/F,FROM


Ubicaci�n
~~~~~~~~~
::


     Workbench:C


Funci�n
~~~~~~~
::


     Inicia un shell (interactivo o en segundo plano).


Entradas
~~~~~~~~
::


     COMMAND  --  la l�nea de comandos a ejecutar

     FROM     --  gui�n a llamar antes de la interacci�n del usuario.



Ejemplo
~~~~~~~
::


     shell FROM S:Startup-Sequence

     Inicia un shell y ejecuta el gui�n de inicio.


Notas
~~~~~
::


 El archivo de gui�n no es un gui�n en sentido estricto (ya que no podr�as
 usar ning�n .key, .bra o .ket ni cosas similares).


Mira tambi�n
~~~~~~~~~~~~
::


 Execute, NewShell


