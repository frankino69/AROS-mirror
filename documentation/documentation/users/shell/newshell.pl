.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <makelink>`_ `Next <path>`_ 

---------------


========
NewShell
========

Sk�adnia
~~~~~~~~
::


	WINDOW,FROM


�cie�ka
~~~~~~~
::


	Workbench:C


Funkcja
~~~~~~~
::

	Tworzy nowe okno CLI w nowym oknie konsoli. To okno stanie si� aktywne.
	Nowe CLI dziedziczy wi�kszo�� atrybut�w poprzedniej konsoli jak aktualny
	katalog, rozmiar stosu, lini� polece� i inne. Jednak kolejne okno jest
	niezale�ne od poprzedniego.
	Okno nale��ce do nowej konsoli mo�e by� okre�lone dzi�ki s�owu 
	kluczowemu WINDOW.
	


Parametr
~~~~~~~~
::


	WINDOW	--	Okre�lenie okna konsoli

	X	--	liczba pikseli od lewej kraw�dzi ekranu                                
	Y	--	liczba pikseli od g�rnej kraw�dzi ekranu
	WIDTH	--	szeroko�� okna konsoli
	HEIGHT	--	wysoko�� okna konsoli
	TITLE	--	tekst, kt�ry pokazuje si� w pasku tytu�owym
	AUTO	--	okno automatycznie si� pojawia, gdy program potrzebuje
			wyj�cia lub wej�cia
	ALT	--	okno uruchamia si� o okre�lonym rozmiarze i pozycji, gdy
			przycisk powi�kszania zostanie wci�ni�ty
	BACKDROP--	okno bez ramek
	CLOSE	--	za��cza przycisk wyj�cia
	INACTIVE--	okno nie jest aktywowane przy uruchomieniu
	NOBORDER--	okno bez ramek, tylko p. rozmiaru, g��bi i powi�kszania 
			s� dost�pne
	NOCLOSE	--	okno nie posiada p. zamykania
	NODEPTH	--	okno nie posiada p. g��bi
	NODRAG	--	okno nie mo�e by� przemieszczane; za��cza NOCLOSE
	NOSIZE	--	okno nie posiada przycisku rozmiaru
	SCREEN	--	nazwa ekranu publicznego, na kt�rym ma by� otworzone 
			okno
	SIMPLE	--	tekst nie zostaje usuni�ty po zmianie rozmiaru
	SMART	--	tekst jest wymazywany przy zmianie rozmiaru
	WAIT	--	okno mo�e zosta� zamkni�te po wci�ni�ciu p. zamykania
			lub po kombinacji CTRL-\
	FROM	--	plik do wykonania przed uruchomieniem konsoli,je�li nic
			nie jest podane to S:Shell-Startup zostaje wykonany


Przyk�ad
~~~~~~~~
::


	NewShell "CON:10/10/640/480/Moja w�asna konsola/CLOSE"


