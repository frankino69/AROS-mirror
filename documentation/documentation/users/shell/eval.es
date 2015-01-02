====
Eval
====

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <endskip>`_ `Next <execute>`_ 

---------------

::

 Eval 

Synopsis
~~~~~~~~
::


     VALUE1/A,OP,VALUE2/M,TO/K,LFORMAT/K


Ubicaci�n
~~~~~~~~~
::


     Workbench:C


Funci�n
~~~~~~~
::


     Eval�a una expresi�n entera e imprime el resultado. El resultado se
     escribe a la salida est�ndar si no se usa el par�metro TO en cuyo caso
     el resultado se imprime a un archivo. Usando el par�metro LFORMAT,
     es posible controlar c�mo se escribe el resultado. Los n�meros que
     tienen el prefijo 0x o el #x son interpretados como hexadecimales,
     y aqu�llos con el prefijo # o 0 se interpretan como octales. Los 
     caracteres alfab�ticos se indican por signo ap�strofo (') previo, y
     se eval�an igual que su equivalente ASCII.


Entradas
~~~~~~~~
::


     VALUE1,
     OP,
     VALUE2      --  La expresi�n a evaluar. Est�n soportados los siguientes
                     operadores:

                     Operator              Symbols
                     ----------------------------------
                     addition              +
                     subtraction           -
                     multiplication        *
                     division              /
                     modulo                mod, M, m, %
                     bitwise and           &
                     bitwise or            |
                     bitwise not           ~
                     left shift            lsh, L, l
                     right shift           rsh, R, r
                     negation               -
                     exclusive or          xor, X, x
                     bitwise equivalence   eqv, E, e
                     
                     Operador              S�mbolos
                     -------------------------------------
                     suma                  +
                     resta                 -
                     producto              *
                     cociente              /
                     resto                 mod, M, m %
                     and entre bits        &
                     or entre bits         |
                     shift a la izq.       lsh, L, l
                     shift a la der.       rsh, R, r
                     negaci�n              -
                     o exclusivo           xor, X, x
                     equivalencia de bits  eqv, E, e

      TO         --  Archivo en donde escribir el resultado
      LFORMAT    --  Como printf especifica qu� escribir.
                     Los par�metros posibles son:
                     
                     %x  --  salida hexadecimal
                     %o  --  salida octal
                     %n  --  salida decimal
                     %c  --  salida de caracter (el caracter ASCII
                             correspondiente al valor del resultado).
                             
                     Especificando *n en la cadena LFORMAT, se a�ade
                     un retorno de carro a la salida.


