.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <setdefaultfont>`_ `Next <setkeyboard>`_ 

---------------


======
Setenv
======

Sk�adnia
~~~~~~~~
::


	NAME,SAVE/S,STRING/F


�cie�ka
~~~~~~~
::


	Workbench:c


Funkcja
~~~~~~~
::


	Ustawia globaln� warto�� z aktualnego Shell. Te warto�ci mog� by� 
	osi�galne z ka�dego programu.
	
	Te warto�ci nie s� zapisywane w ENVARC:, w zwi�zku z tym zostaj� one
	zachowywane na konkretn� sesj� systemu operacyjnego, po ponownym 
	uruchomieniu s� wymazywane. Gdy u�yta zostaje opcja SAVE, wtedy warto��
	zostaje zapisywana tak�e w ENVARC:
	
	Je�li brak parametr�w, aktualna lista parametr�w globalnych zostaje 
	wy�wietlona.


Parametry
~~~~~~~~~
::


	NAME	-	Nazwa globalnej zmiennej.

	SAVE	-	Zapisz warto�� w ENVARC:

	STRING	-	Warto�� dla globalnej zmiennej NAME.


Wynik
~~~~~
::

	Standardowe kody b��d�w.


Przyk�ad
~~~~~~~~
::


	Setenv EDITOR Ed
	
	Ka�dy program korzystaj�cy z warto�ci EDITOR, b�dzie m�g� pobra� nazw�
	edytora tekstowego, kt�rego u�ytkownik b�dzie chcia� u�ywa�.


Zobacz tak�e
~~~~~~~~~~~~
::


	Getenv, Unsetenv


