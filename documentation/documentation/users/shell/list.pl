.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <lab>`_ `Next <lock>`_ 

---------------


====
List
====

Format
~~~~~~
::


	List [(dir | pattern | filename)] [ PAT (pattern)] [KEYS] [DATES]
		[NODATES] [TO (name)] [SUB (string)] [SINCE (date)] 
		[UPTO (date)] [QUICK] [BLOCK] [NOHEAD] [FILES] [DIRS] 
		[LFORMAT (string)] [ALL]
             

Szablon
~~~~~~~
::


	DIR/M,P=PAT/K,DATES/S,NODATES/S,TO/K,SUB/K,SINCE/K,UPTO/K,QUICK/S,
	BLOCK/S,NOHEAD/S,FILES/S,DIRS/S,LFORMAT/K,ALL/S


�cie�ka
~~~~~~~
::


	Workbench:C/
        

Funkcja
~~~~~~~
::

	Wy�wietla szczeg�owe informacje o obiektach w aktualnym katalogu lub
	okre�lonym.
	
	Informacja o obiekcie jest przedstawiona w nowej linii, zawieraj�c
	poni�sze dane:
	
	nazwa
	rozmiar (w bajtach)
	bity ochronne
	data oraz czas
      

Parametry
~~~~~~~~~
::


	DIR		--	Lista katalog�w. Je�li si� sko�czy�y, aktualny
				katalog zostanie wy�wietlony.
	PAT		--	Wy�wietl pliki pasuj�ce do wzorca.
	KEYS		--	Wy�wietl rozmiar bloku ka�dego obiektu.
	DATES		--	Wy�wietl dat� i czas stworzenia dla obiektu.
	NODATES		--	Nie wy�wietlaj dat.
	TO (nazwa)	--	Zapisz wyj�cie do pliku.
	SUB (ci�g)	--	Wy�wietl tylko pliki, pasuj�ce do wzorca.
	SINCE (data)	--	Wy�wietl pliki nowsze od 'data'.
	UPTO (data)	--	Wy�wietl pliki starsze od 'data'.
	QUICK		--	Wy�wietl tylko nazwy plik�w.
	BLOCK		--	Pliki s� w blokach 512 bajtowych.
	NOHEAD		--	Bez nag��wk�w.
	FILES		--	Tylko pliki.
	DIRS		--	Tylko katalogi.
	LFORMAT		--	Okre�la rodzaj wyj�cia.
	ALL		--	Zawarto�� wy�wietlana rekurencyjnie.

	Oto parametry dost�pne z LFORMAT:

	%A	--	atrybuty pliku
	%B	--	rozmiar pliku w raczej blokach ni� bajtach
	%C	--	komentarz
	%D	--	data utworzenia
	%E	--	rozszerzenie pliku
	%F	--	nazwa woluminu
	%K	--	klucz bloku
	%L	--	rozmiar pliku w bajtach
	%M	--	nazwa pliku bez rozszerzenia
	%N	--	nazwa pliku
	%P	--	�cie�ka pliku
	%S	--	zast�pione przez %N i %P; przestarza�e
	%T	--	czas utworzenia
     

Wynik
~~~~~
::


	Standardowe kody b��d�w.


Przyk�ad
~~~~~~~~
::


	1> List C:
	Directory "C:" on Wednesday 12-Dec-99
	AddBuffers                  444 --p-rwed 02-Sep-99 11:51:31
	Assign                     3220 --p-rwed 02-Sep-99 11:51:31
	Avail                       728 --p-rwed 02-Sep-99 11:51:31
	Copy                       3652 --p-rwed 02-Sep-99 11:51:31
	Delete                     1972 --p-rwed 02-Sep-99 11:51:31
	Execute                    4432 --p-rwed 02-Sep-99 11:51:31
	List                       5108 --p-rwed 02-Sep-99 11:51:31
	Installer                109956 ----rwed 02-Sep-99 11:51:31
	Which                      1068 --p-rwed 02-Sep-99 11:51:31
	9 files - 274 blocks used        
     

Zobacz tak�e
~~~~~~~~~~~~
::


	Dir


