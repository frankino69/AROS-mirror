.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <endskip>`_ `Next <execute>`_ 

---------------


====
Eval
====

Sk�adnia
~~~~~~~~
::


	VALUE1/A,OP,VALUE2/M,TO/K,LFORMAT/K


�cie�ka
~~~~~~~
::


	Workbench:C


Funkcja
~~~~~~~
::
	
	Oblicza warto�ci liczbowe i wy�wietla wynik. Wynik jest wy�wietlany na
	standardowe wyj�cie, je�li argument TO nie jest podany, kt�ry zapisuje
	wyj�cie do pliku. Dzi�ki LFORMAT mo�liwe jest okre�lenie rodzaju 
	wyj�cia. Liczby oznaczone 0x lub #x s� rozumiane jako hex, a te # lub 0,
	jako �semkowe. Znaki alfabetu s� rozpoznawane przez znak apostrofy
	('), i s� obliczane jak ich oznaczenia w ASCII.


Parametry
~~~~~~~~~
::


	VALUE1,
	OP,
	VALUE2      --  Wyra�enie do obliczenia, oto dozwolone operatory:

		Operator              Symbol
		----------------------------------
		dodawanie		+
		odejmowanie		-
		mno�enie		*
		dzielenie		/
		modu�			mod, M, m, %
		logiczne i		&
		logiczne lub		|
		zaprzeczenie logiczne	~
		lewy shift		lsh, L, l
		prawy shift		rsh, R, r
		warto�� ujemna		-
		alternatywa roz��czna	xor, X, x
		***warto�� bitu		eqv, E, e

	TO          --  Plik w kt�rym zostanie zapisane wyj�cie
	LFORMAT     --  Rodzaje parametr�w takie jak w printf().
			Oto mo�liwe opcje:
                      
			%x  --  wyj�cie hex
			%o  --  wyj�cie �semkowe
			%n  --  wyj�cie dziesi�tne
			%c  --  wyj�cie znakowe (znak ANSI)
                             
			Ustawiaj�c *n w LFORMAT, nowa linia b�dzie utoworzona.


