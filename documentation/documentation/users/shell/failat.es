======
FailAt
======

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <execute>`_ `Next <fault>`_ 

---------------

::

 FailAt 

Formato
~~~~~~~
::

     FailAt <limit>


Synopsis
~~~~~~~~
::

     RCLIM/N


Ubicaci�n
~~~~~~~~~
::

     C:


Funci�n
~~~~~~~
::

     FailAt establece el l�mite para el c�digo devuelto del actual gui�n
     del shell. Si alg�n comando del gui�n devuelve un c�digo de falla
     igual o mayor que �ste el gui�n abortar�.

     Los c�digos de falla comunes son:
         0   - No hay error
         5   - Advertencia
         10  - Error
         20  - Falla

     El valor normal para el l�mite del c�digo devuelto es 10.


Ejemplo
~~~~~~~
::

     Si tenemos un gui�n con los comandos

         Copy RAM:SomeFile DF0:
         Echo "Done!"

     y el archivo RAM:SomeFile no existe, el comando Copy devolver�:

         Copy: object not found
         Copy: returned with error code 20

     y el gui�n abortar�. Sin embargo, si incluyes el comando

         FailAt 21

     entonces el gui�n se completar� porque el c�digo devuelto de Copy
     es menor que el l�mite para el c�digo devuelto.


