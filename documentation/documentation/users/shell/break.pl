.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <beep>`_ `Next <cd>`_ 

---------------


=====
Break
=====

Format
~~~~~~
::

	Break <process> [ALL|C|D|E|F]


Sk�adnia
~~~~~~~~
::

	PROCESS/N,PORT,ALL/S,C/S,D/S,E/S,F/S


�cie�ka
~~~~~~~
::

	Workbench:c


Funkcja
~~~~~~~
::

	BREAK wysy�a jeden lub wi�cej sygna��w do procesu CLI.
	Argument PROCESS okre�la numeryczn� posta� programu (ID) CLI,
	do kt�rego chcesz wys�a� sygna�.
	Komenda STATUS wy�wietli wszystkie aktualnie uruchomione procesy CLI
	wraz z identyfikatorem ID. Mo�esz tak�e poda� publiczn� nazw� portu
	i wys�a� sygna�y do tego portu.

	Mo�esz tak�e wys�a� wszystkie sygna�y w tym samym momencie, dzi�ki
	opcji ALL lub kombinacji znacznik�w CTRL-C, CTRL-D, CTRL-E i CTRL-F
	przez ich okre�lone opcje. Tylko gdy proces CLI ma okre�lone ID wtedy 
	zostanie wys�any sygna� CTRL-C.

	Efekt u�ywania komendy BREAK jest ten sam jak wybranie okna
	konsoli i wci�ni�ciu odpowiedniej kombinacji.

	Znaczenie klawiszy jest nast�puj�ce:
	CTRL-C	-	Zatrzymuje proces
	CTRL-D	-	Zatrzymuje skrypt CLI
	CTRL-E	-	Zamyka okno procesu
	CTRL-F	-	Aktywuj okno procesu

	Nie wszystkie programy reaguj� na te sygna�y, ale wi�kszo��
	powinna odpowiada� na CTRL-C.



Przyk�ad
~~~~~~~~
::

     
	1.SYS:> BREAK 1

	Wy�lij sygna� CTRL-C do procesu oznaczonego jako 1.

	1.SYS:> BREAK 4 E

	Wy�lij sygna� CTRL-E do procesu oznaczonego jako 4.


