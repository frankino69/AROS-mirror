.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <join>`_ `Next <list>`_ 

---------------


===
Lab
===

�cie�ka
~~~~~~~
::


	Workbench:C


Funkcja
~~~~~~~
::


	Deklaruje etykiet� w pliku skryptowym. Ta etykieta mo�e by� wykorzystana
	z komend� Skip.
	

Przyk�ad
~~~~~~~~
::


	If NOT EXISTS S:User-Startup
	Skip BrakSekwencjiUzytkownika
	EndIf

	FailAt 20
	Execute S:User-Startup
	Quit

	Lab BrakSekwencjiUzytkownika
	Echo "Brak User-Startup"


Zobacz tak�e
~~~~~~~~~~~~
::


	Skip


