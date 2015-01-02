.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <rename>`_ `Next <requestfile>`_ 

---------------


=============
RequestChoice
=============

Sk�adnia
~~~~~~~~
::


	TITLE/A,BODY/A,GADGETS/A/M,PUBSCREEN/K


�cie�ka
~~~~~~~
::


	Workbench:c


Funkcja
~~~~~~~
::

	Pozwala na u�ycie EasyRequest() w skryptach AmigaDOS.


Parametry
~~~~~~~~~
::


	TITLE		- Tytu� okna zapytania.

	BODY		- Tekst wy�wietlany w oknie zapytania.

	GADGETS		- Tekst dla przycisk�w.

	PUBSCREEN	- Nazwa ekranu publicznego na kt�rym si� uruchomi.


Wynik
~~~~~
::


	Standardowe kody b��du.


Przyk�ad
~~~~~~~~
::

	RequestChoice "To jest tytu�" "To jest*Nopis" Dobra|Poniechaj
	
	Tutaj wszystko m�wi za siebie, opr�cz "*N". To jest odpowiednik
	'\n' w j�zyku C, �eby wstawi� now� lini�. Okno zapytania zostanie
	otworzone w Workbench Screen.


	RequestChoice Title="Kolejny tytu�" Body="A to jest*Nkolejny opis"
	Gadgets=Dobra|Poniechaj PubScreen=DOPUS.1

	To robi dok�adnie to samo, ale na ekranie publicznym Directory Opus.


Opis
~~~~
::

	Aby umie�ci� now� lini� nale�y w opisie wstawi� *n lub *N .
	
	Aby umie�cic cudzys��w nale�y u�y� *" .
	
	Szablon CLI daje GADGETS opcje jako ALWAYS; jest to odmienne od 
	orginalnego programu. Dzi�ki temu nie musimy sprawdza�, czy gad�et 
	zosta� podany.


Zobacz tak�e
~~~~~~~~~~~~
::


	intuition.library/EasyRequest(), intuition.library/EasyRequestArgs()


