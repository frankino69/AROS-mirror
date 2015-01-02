==
If
==

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <getenv>`_ `Next <info>`_ 

---------------

::

 If 

Synopsis
~~~~~~~~
::


     NOT/S,WARN/S,ERROR/S,FAIL/S,,EQ/K,GT/K,GE/K,VAL/S,EXISTS/K


Ubicaci�n
~~~~~~~~~
::


     Workbench:C


Funci�n
~~~~~~~
::


     Ejecuta todos los comandos en un bloque si la condici�n dada es
     verdadera (Un bloque es una sucesi�n de l�neas de comandos
     terminada con un comando ELSE o ENDIF). Por cada comando IF debe
     haber un ENDIF correspondiente.
     Si la condici�n es false, la ejecuci�n de comandos saltar� al
     correspondiente comando ELSE o ENDIF.


Entradas
~~~~~~~~
::


     NOT               --  Niega el valor de la condici�n.

     WARN              --  Es verdadero si el c�digo devuelto anterior
                           fue igual o mayor que 5.
     ERROR             --  Es verdadero si el c�digo devuelto anterior
                           fue igual o mayor que 10.
     FAIL              --  Es verdadero si el c�digo devuelto anterior
                           fue igual o mayor que 20.

     EQ, GE, GT        --  Es verdadero si el primer valor es igual,
                           igual o mayor, o mayor que el segundo valor
                           respectivamente.

     VAL               --  Indica que la comparaci�n deber�a tratar a las
                           cadenas como valores num�ricos.

     EXISTS  <cadena>  --  Es verdadero si existe el archivo o directorio
                           <cadena>.



Ejemplo
~~~~~~~
::


     If 500 GT 200 VAL
         echo "500 is greater than 200"
     Else
         If EXISTS S:User-Startup
             echo "User-Startup script found in S:"
             Execute S:User-Startup
         EndIf
     EndIf


Notas
~~~~~
::


     ERROR y FAIL solamente ser�n apropiados si el nivel de falla del
     gui�n es puesto mediante FailAt (el nivel de falla normal es 10 y si
     alg�n c�digo devuelto iguala o supera este valor, el gui�n abortar�).


Vea tambi�n
~~~~~~~~~~~
::


     Else, EndIf, FailAt


