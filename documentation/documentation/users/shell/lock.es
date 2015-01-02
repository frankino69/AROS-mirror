====
Lock
====

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <list>`_ `Next <makedir>`_ 

---------------

::

 Lock 

Formato
~~~~~~~
::

     Lock <drive> [ON|OFF] [<passkey>]


Synopsis
~~~~~~~~
::

     DRIVE/A,ON/S,OFF/S,PASSKEY


Ubicaci�n
~~~~~~~~~
::

     Workbench:c


Funci�n
~~~~~~~
::

     LOCK har� que el dispositivo o la partici�n especificada
     sea protegido o habilitado para escribir. Esta protecci�n contra 
     la escritura es una protecci�n por software que es manejada por el
     sistema de archivo del volumen. Por esto que la protecci�n ser�
     reset [restablecida] (a escribible) en el siguiente arranque
     del sistema.

     Es posible especificar un passkey opcional que se puede usar para
     proteger el bloqueo. El mismo passkey que se use para bloquear
     el volumen se debe usar para desbloquearlo. El passkey puede ser
     de cualquier cantidad de caracteres.

     El volumen dado DEBE ser el nombre de dispositivo o el del volumen
     ra�z, no una asignaci�n (assign).


Ejemplo
~~~~~~~
::

     
     1.SYS:> Lock Work:

         Esto bloquear� el volumen llamado Work: sin un ###passkey.

     1.SYS:> Lock Work:
     1.SYS:> MakeDir Work:SomeDir
     Can't create directory Work:Test
     MakeDir: Disk is write-protected

         El volumen Work: est� bloqueado, as� que es imposible crear
         un directorio.

     1.SYS:> Lock Work: OFF

         Esto desbloquear� el volumen Work:

     1.SYS:> Lock Work: MyPassword

         Esto bloquear� Work: con el passkey "MyPassword"


