.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <addbuffers>`_ `Next <ask>`_ 

---------------


=====
Alias
=====

Sk�adnia
~~~~~~~~
::


	NAME,STRING/F


�cie�ka
~~~~~~~
::


	Workbench:c


Funkcja
~~~~~~~
::


     Alias umo�liwia Ci stworzenie alternatywnej nazwy dla innych komend DOSa.
     Je�li Alias zostanie u�yty bez parametr�w, wy�wietla aktualn� list�
     alias�w zdefiniowanych w aktywnym oknie shella.

     U�ycie pary kwadratowych nawias�w wewn�trz aliasu umo�liwia Ci
     doda� 'now�' komend� dosa z parametrami.

     Je�li nie zostan� wyspecyfikowane parametry, zostanie wy�wietlona aktualna lista alias�w.
     


Parametry
~~~~~~~~~
::


	NAME    - Nazwa do przypisania.

	STRING  - Warto�� dla NAME.


Rezultat
~~~~~~~~
::


	Standardowe kody b��d�w DOS.


Przyk�ad
~~~~~~~~
::


	Alias DF "Type [] numer"

	Wpisuj�c "DF S:Shell-Startup" w konsoli, wykonujesz komende
	"Type S:Shell-Startup numer". To dzia�anie wy�wietli zawarto��
	pliku S:Shell-Startup w konsoli z liczb� linii po lewej stronie.

     
Zobacz tak�e
~~~~~~~~~~~~
::


     Unalias


