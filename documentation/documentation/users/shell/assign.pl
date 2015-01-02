.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <ask>`_ `Next <avail>`_ 

---------------


======
Assign
======

Sk�adnia
~~~~~~~~
::


	NAME, TARGET/M, LIST/S, EXISTS/S, DISMOUNT/S, DEFER/S, PATH/S, ADD/S,
	REMOVE/S, VOLS/S, DIRS/S, DEVICES/S


�cie�ka
~~~~~~~
::


	Workbench:C


Funkcja
~~~~~~~
::
	ASSIGN tworzy odno�nik do pliku lub katalogu. Odno�nik jest
	logiczn� nazw� dysku, co sprawia, �e bardzo wygodnie mo�na
	przypisa� obiekty u�ywaj�c przypis�w zamiast �cie�ek do tych
	katalog�w.
	
	Je�li argumenty NAME i TARGET s� podane, ASSIGN przypisze
	logiczn� nazw� do okre�lonej �cie�ki. Je�li NAME jest ju� przypisane
	do pliku lub katalogu to nowy przypis zmieni poprzedni� �cie�k�.
	Dwukropek musi by� podany po argumencie NAME.

	Je�li tylko argument NAME jest podany, to ka�de przypisanie do
	tego NAME jest usuwane. Je�li brak jest argument�w, to zostan�
	wy�wietlone wszystkie przypisy.
	


Parametry
~~~~~~~~~
::


	NAME		--	nazwa, kt�ra powinna by� przypisana do pliku lub katalogu
	TARGET		--	jeden lub wi�cej katalog�w podanych jako �cie�ka
	LIST		--	lista wszystkich stworzonych przypis�w
	EXISTS		--	je�li nazwa NAME ju� wyst�puje, to zostanie zwr�cony kod WARN
	DISMOUNT	--	usu� wolumin lub nazw� urz�dzenia NAME z dos listy
	DEFER		--	stw�rz przypis do nieistniej�cej (w chwili tworzenia) �cie�ki
	PATH		--	stw�rz przypis do nieistniej�cej (w chwili tworzenia) �cie�ki	
	ADD		--	dodaje kolejn� �cie�k� do nazwy przypisu NAME
	REMOVE		--	usuwa przypis
	VOLS		--	wy�wietla przypisane woluminy
	DIRS		--	wy�wietla przypisane katalogi
	DEVICES		--	wy�wietla przypisane urz�dzenia
     


