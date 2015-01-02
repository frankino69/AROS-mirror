=====
Alias
=====

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <addbuffers>`_ `Next <ask>`_ 

---------------

::

 Alias 

Synopsis
~~~~~~~~
::


     NAME,STRING/F
     NOMBRE, CADENA/F


Ubicaci�n
~~~~~~~~~
::


     Workbench:c


Funci�n
~~~~~~~
::


     Alias allows you to create an alternate name for other DOS commands.
     If Alias is used with no parameters, it will display the current
     list of Aliases defined within the current shell.
     Alias te premite crear un nombre alternativo a los comandos DOS.
     Si se usa Alias sin par�metros, mostrar� la lista actual de alias
     definidos en el shell actual.

     Usar los corchetes dentro del alias te permite proporcionar el
     'nuevo' comando dos con par�metros.

     Si no se especifican par�metros, se muestra la lista actual de alias.


Entradas
~~~~~~~~
::


     STRING  - The value of the alias NAME.
     CADENA  - El valor del alias NOMBRE.


Resultado
~~~~~~~~~

::


     Los c�digo de error DOS normales.


Ejemplo
~~~~~~~
::


     Alias DF "Type [] number"

         Al tipear "DF S:Shell-Startup" en el shell, est�s ejecutando en
         realidad el comando "Type S:Shell-Startup number". Esto mostrar�
         los contenidos del archivo S:Shell-Startup en el shell con el
         n�mero de rengl�n en el margen izquierdo.


Tambi�n mira
~~~~~~~~~~~~

::


     Unalias


