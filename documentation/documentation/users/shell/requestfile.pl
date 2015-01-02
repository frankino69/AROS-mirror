.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <requestchoice>`_ `Next <run>`_ 

---------------


===========
RequestFile
===========

Sk�adnia
~~~~~~~~
::


	DRAWER,FILE/K,PATTERN/K,TITLE/K,POSITIVE/K,NEGATIVE/K,
	ACCEPTPATTERN/K,REJECTPATTERN/K,SAVEMODE/S,MULTISELECT/S,
	DRAWERSONLY/S,NOICONS/S,PUBSCREEN/K,INITIALVOLUMES/S


�cie�ka
~~~~~~~
::


	Workbench:c


Funkcja
~~~~~~~
::
	
	Tworzy okno zapytania o plik. Wybrane pliki zostan� wy�wietlone i 
	oddzielone spacjami. Je�li �aden plik nie zosta� wybrany, wtedy zostanie
	zwr�cony kod b��du 5 (WARN/Ostrze�enie).
 

Parametry
~~~~~~~~~
::

	DRAWER		--	pocz�tkowa zawarto�� pola katalogu
	FILE		--	pocz�tkowa zawarto�� pola pliku
	PATTERN		--	pocz�tkowa zawarto�� pola wzorca (np. #?.c)
	TITLE		--	tytu� okna
	POSITIVE	--	ci�g tekstowy lewego przycisku
	NEGATIVE	--	ci�g tekstowy prawego przycisku
	ACCEPTPATTERN	--	wy�wietlane pliki, kt�re pasuj� do wzorca
	REJECTPATTERN	--	pliki, kt�re pasuj� do wzorca nie s� wy�wietlane
	SAVEMODE	--	okno zapytanie zostaje uruchomione jako zapisu
	MULTISELECT	--	wi�cej ni� jeden plik mo�e by� zaznaczony
	DRAWERSONLY	--	tylko katalogi s� wy�wietlane
	NOICONS		--	ikony (#?.info) nie s� wy�wietlane
	PUBSCREEN	--	okno zapytania otwierane jest na podanym ekranie
				publicznym
	INITIALVOLUMES	--	pokazuje woluminy
     

Wynik
~~~~~
::


	Standardowe kody b��d�w.


