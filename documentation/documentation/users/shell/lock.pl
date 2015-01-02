.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <list>`_ `Next <makedir>`_ 

---------------

Hence the
     protection will be reset (to writable) on the next system reboot.

====
Lock
====

Format
~~~~~~
::

	Lock <drive> [ON|OFF] [<passkey>]


Sk�adnia
~~~~~~~~
::

	DRIVE/A,ON/S,OFF/S,PASSKEY


�cie�ka
~~~~~~~
::

	Workbench:c


Funkcja
~~~~~~~
::

	Lock sprawi, �e okre�lone urz�dzenie lub partycja b�d� zabezpieczone
	przed zapisem lub odbezpieczone. To zabezpieczenie przed zapisem jest
	obs�ugiwane przez system plik�w woluminu. W zwi�zku z czym zapis b�dzie
	mo�liwy po ponownym restarcie.
	Jest tak�e mo�liwe podanie has�a, kt�re b�dzie chroni�o przed zmian�
	stanu. To samo has�o, kt�re zosta�o u�yte do zabezpieczenia jest u�ywane
	do odbezpieczania. Has�o mo�e mie� dowoln� d�ugo��.

	Wolumin MUSI by� urz�dzeniem lub g��wnym woluminem, a nie przypisem.


Przyk�ad
~~~~~~~~
::

     
	1.SYS:> Lock Work:

	To zablokuje przed zapisem wolumin Work, ale nie zabezpieczy go has�em.
	

	1.SYS:> Lock Work:
	1.SYS:> MakeDir Work:SomeDir
	Can't create directory Work:Test
	MakeDir: Disk is write-protected

	Wolumin jest zablokowany, wi�c nie jest mo�liwe stworzenie katalogu.
	

	1.SYS:> Lock Work: OFF

	A to go odblokuje.
	

	1.SYS:> Lock Work: MojeHaslo

	Tutaj u�ywamy has�a "MojeHaslo"


