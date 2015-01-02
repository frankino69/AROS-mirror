.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <fault>`_ `Next <get>`_ 

---------------


========
Filenote
========

Sk�adnia
~~~~~~~~
::


	FILE/A,COMMENT,ALL/S,QUIET/S


�cie�ka
~~~~~~~
::


	Workbench:c


Funkcja
~~~~~~~
::

	Dodaje komentarz do obiektu.

	Filenote obs�uguje rekurencyjne przeszukiwanie katalog�w i dodaje 
	komentarze do ka�dego pliku/katalogu, a dzi�ki wzorcom mo�na okre�li�
	pliki.



Parametry
~~~~~~~~~
::


	FILE	-	Zawsze musi by� podane. Mo�e to by� plik z pe�n� �cie�k� 
			albo mo�e by� wzorzec.

	COMMENT	-	Tekst ASCII, kt�ry mo�e by� dodany jako komentarz do 
			obiektu.
			
			Aby stworzy� komentarz z zamkni�tymi cudzys�owami
			nale�y poprzedzi� cudzys��w gwiazdk�.

			Np.
			Filenote FILE=RAM:test.txt COMMENT=*"witaj*"

	ALL     -	Przeszukiwanie rekurencyjne.

	QUIET   -	Cisza, brak wyj�cia.


Wynik
~~~~~
::


	Standardowe kody b��d�w.


Przyk�ad
~~~~~~~~
::


	Filenote ram: witaj all

	
	Przeszukuje ca�y katalog w RAM: i dodaje "witaj" jako komentarz do
	ka�dego obiektu.


Opis
~~~~
::

	Wyj�cie z AROS'owego Filenote jest staranne i strukturalne, ni� ze
	standardowej komendy Filenote.
	
	Nie obs�uguje jeszcze wieoprzypisowo�ci.


Zobacz tak�e
~~~~~~~~~~~~
::


	dos.library/SetComment()


