.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <date>`_ `Next <dir>`_ 

---------------


======
Delete
======

Sk�adnia
~~~~~~~~
::

 
	Delete { (name | pattern) } [ALL] [QUIET] [FORCE]


�cie�ka
~~~~~~~
::


	Workbench/c


Funkcja
~~~~~~~
::

	Usuwa pliki i katalogi. Mo�esz usuwa� kilka plik�w i katalog�w, 
	okre�laj�c je osobno lub poprzez u�ycie wzorc�w. Aby anulowa�
	usuwanie, po prostu wci�nij CTRL-C. Komenda poinformuje u�ytkownika
	je�li ten usuwa pliki z bitami ochronnymi.
	Delete nie mo�e usuwa� katalog�w, kt�re nie s� puste, chyba, �e opcja
	ALL jest za��czona. Aby powstrzyma� wy�wietlanie usuwanych plik�w nale�y
	u�y� opcji QUIET. Je�li bit ochronny jest zniesiony dla pliku
	lub katalogu wtedy nie mo�e zosta� on usuni�ty, ale mo�na wymusi�
	usuni�cie dzi�ki podaniu opcji FORCE.



Parametry
~~~~~~~~~
::


	FILE/M/A  --  pliki lub katalogi do usuni�cia (mog� zawiera� wzorce)
	ALL/S     --  rekurencyjne usuwanie katalog�w
	QUIET/S   --  nie wy�wietlaj, kt�re obiekty s� usuwane
	FORCE/S   --  usu� obiekty, nawet wtedy, gdy s� chronione


Przyk�ad
~~~~~~~~
::


	Delete RAM:T/#? ALL FORCE

	Usuwa wszystkie obiekty rekurencyjnie (ALL) z RAM:T/ i nie zwraca uwagi 
	na bity ochrony (FORCE).
