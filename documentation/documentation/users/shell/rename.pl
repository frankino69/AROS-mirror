.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <relabel>`_ `Next <requestchoice>`_ 

---------------


======
Rename
======

Sk�adnia
~~~~~~~~
::


	Rename [{FROM}] <nazwa> [TO|AS] <nazwa> [QUIET]

	FROM/A/M,TO=AS/A,QUIET/S


�cie�ka
~~~~~~~
::


	Workbench/c


Funkcja
~~~~~~~
::

	Zmienia nazw� obiektu. Rename mo�e by� u�yty tak jak UNIX'owy mv,
	kt�ry przenosi plik/pliki do innej lokacji na dysku.


Parametry
~~~~~~~~~
::


	FROM	--	Nazwa(y) pliku(�w) do przeniesienia. Mo�e by� podanych 
			wiele plik�w.


	TO|AS	--	Nazwa jak� chcemy przypisa� nowemu plikowi.

	QUIET	--	Brak wyj�cia do konsoli.


Wynik
~~~~~
::


	Standardowe kody b��d�w.


Przyk�ad
~~~~~~~~
::


	Rename list1.doc list2.doc listy
	
	Przenosi list1.doc i list2.doc do katalogu listy.
     

	Rename ram:a ram:b quiet
	Rename from ram:a to ram:b quiet
	Rename from=ram:a to=ram:b quiet

	Wszystkie wersje, zmiana nazwy z "a" do "b", i brak jest wyj�cia do
	konsoli(QUIET).

