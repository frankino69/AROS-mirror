======
Prompt
======

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <path>`_ `Next <protect>`_ 

---------------

::

 Prompt 

Synopsis
~~~~~~~~
::


     PROMPT


Ubicaci�n
~~~~~~~~~
::


     Workbench:c


Funci�n
~~~~~~~
::


     Specify the prompt for the current shell.
     Especifica el ###prompt del shell actual.


Entradas
~~~~~~~~
::


     PROMPT  --  The prompt como una cadena. Se pueden usar los siguientes
                 comandos en un tipo de estilo printf.

                 N  --  el n�mero de CLI
                 S  --  el nombre del directorio actual
                 R  --  el c�digo devuelto por la �ltima operaci�n

                 Si no se especifica ning�n prompt "%N.%S> " se usa.


Resultado
~~~~~~~~~
::


     Los c�digos devueltos DOS normales.


Ejemplo
~~~~~~~
::


     Prompt "Oepir Risti.%N> " da:

     Oepir Risti.10>      (si el n�mero de CLI era 10)


Tambi�n vea
~~~~~~~~~~~
::


     SetPrompt()


