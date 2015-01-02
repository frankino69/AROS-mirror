.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <changetaskpri>`_ `Next <date>`_ 

---------------


====
Copy
====

Sk�adnia
~~~~~~~~
::


	FROM/M, TO, ALL/S, QUIET/S, BUF=BUFFER/K/N, CLONE/S, DATES/S, NOPRO/S,
	COM=COMMENT/S, NOREQ/S,

	PAT=PATTERN/K, DIRECT/S,SILENT/S, ERRWARN/S, MAKEDIR/S, MOVE/S,
	DELETE/S, HARD=HARDLINK/S, SOFT=SOFTLINK/S, FOLNK=FORCELINK/S,
	FODEL=FORCEDELETE/S, FOOVR=FORCEOVERWRITE/S, DONTOVR=DONTOVERWRITE/S,
	FORCE/S


�cie�ka
~~~~~~~
::


	Workbench:C


Funkcja
~~~~~~~
::


	Tworzy kopie jednego lub wielu plik�w w drugi lub wiele plik�w.


Parametry
~~~~~~~~~
::


	FROM	--	wej�cie wieloplikowe
	TO	--	docelowy plik lub katalog
	ALL	--	oznacza, �e katalogi s� kopiowane rekurencyjnie
	QUIET	--	tryb cichy, brak wyj�cia na konsole
	BUFFER	--	rozmiar bufora dla COPY (bufor = 512bajty, 
			standardowo 1024 (= 512K))
	CLONE	--	tryb klonowania, wszystkie pliki s� wiernymi kopiami
	DATES	--	kopiuj daty w tym czas
	NOPRO	--	pomi� kopiowanie bit�w ochronnych
	COMMENT	--	kopiuj komentarz
	NOREQ	--	blokuje zapytania
	PATTERN	--	wywi�rcze kopiowanie plik�w, poprzez podanie wzorca
	DIRECT	--	kopiowanie bezpo�rednie, bez test�w
	VERBOSE	--	tryb gadatliwy, podaje wi�cej szczeg��w
	ERRWARN	--	przerwij, gdy kopiowanie zawiedzie
	MAKEDIR	--	tw�rz katalogi
	MOVE	--	tryb przenoszenia, usuwa �r�d�owe pliki
	DELETE	--	tryb usuwania, nie kopiuje, tylko usuwa
	HARDLINK--	stw�rz twarde po��czenie, zamiast kopiuj
	SOFTLINK--	stw�rz mi�kkie po��czenie, zamiast kopiuj
	FOLNK	--	linki tak�e dla katalog�w
	FODEL	--	usu� pliki chronione
	FOOVR	--	nadpisuj chronione pliki
	DONTOVR	--	nie nadpisuj
	FORCE	--	NIE U�YWAJ. Tylko w celach kompatybilno�ci


 Bardziej szczeg�owe opisy:

 FROM:
 Pliki �r�d�owe. Dla katalog�w, zawieraj�ce pliki to pliki �r�d�owe. Mog� u�ywa�
 standardowych wzorc�w.

 TO:
 Plik docelowy lub wiele �r�de� dla docelowego katalogu. Docelowe katalogi s�
 tworzone (zawieraj�ce wszystkie potrzebne nadrz�dne katalogi).

 ALL:
 Kopiuje katalogi rekurencyjnie.

 QUIET:
 Tryb cichy, �adne informacje nie b�d� przekazywanem ani nawet zapytania.

 BUF=BUFFER:
 Okre�la liczb� 512 bajtowych bufor�w dla kopiowania. Standardowo jest to 200
 [100KB pami�ci]. Jeden bufor to minimalny rozmiar, lecz nie powinien by� 
 wykorzystywany.

 PAT=PATTERN:
 PATTERN okre�la rodzaj plik�w, b�d� katalog�w, dzi�ki standardowym dos wzorcom.
 Ta opcja jest u�yteczna z ALL.

	Przyk�ad:
	Gdy potrzebujesz usun�� wszystkie pliki z rozszerzeniem info to mo�esz 
	u�y� tego przyk�adu : Copy DELETE #? ALL PAT #?.info

 CLONE:
 Pliki zostan� sklonowane, to znaczy, �e czas, data, bity ochronne i komentarz
 b�dzie taki sam w pliku �r�d�owym, jak i w docelowym.

 DATES:
 Informacja o dacie zostanie skopiowana do obiektu docelowego.

 NOPRO:
 �adne bity ochrony nie zostan� skopiowane do docelowego obiektu, b�d� mia�y
 standardowe bity Odczytu[r], Zapisu[w], Wykonywania[e] i Usuni�cia[d] [rwed].

 COM=COMMENT:
 Komentarz pliku zostanie skopiowany.

 NOREQ:
 �adne dos standardowe zapytania nie zostan� wy�wietlone, b�d� pomijane.


 DIRECT:
 Niekt�re urz�dzenia nie obs�uguj� (typu DOS) pakiet�w zapyta�. Ta opcja to jest
 tak naprawd� prostym kopiowaniem, bez sprawdzania, tylko bezpo�rednie 
 kopiowanie.
 Opcje ALL, PAT, CLONE, DATES, NOPRO, COM, MAKEDIR, MOVE, DELETE, HARD,
 SOFT, FOLNK, FODEL, FOOVR, DONTOVR i wielo�r�d�owe kopiowanie nie mo�e by� 
 u�yte wraz z DIRECT, ta opcja wymaga jednego pliku �r�d�owego i jednego 
 docelowego obiektu.
 Gdy chcesz usun�� po��czenie mi�kkie, kt�re ju� nie wskazuje na istniej�cy
 plik, b�dziesz potrzebowa� tej opcji.

	Przyk�ad: 'Copy DIRECT text PRT:' aby wydrukowa� plik nazwany "text".
	COPY automatycznie zajmuje si� takimi przypadkami, lecz mo�e to Ci si�
	kiedy� przyda�.

 VERBOSE:
 Tryb gadatliwy, dodatkowe informacje o kopiowaniu s� podawane.

 ERRWARN:
 COPY rozpoznaje trzy rodzaje kod�w b��du:
 5   WARN    Ostrze�enie, komenda pomija plik i kontynuuje kopiowanie.
 10  ERROR   B��d, tworzenie obiektu si� nie powiod�o.
 20  FAIL    Powa�ny b��d, brak pami�ci, uszkodzenie systemu, komenda
            przerywa swoje dzia�anie.

 Gdy opcja ERRWARN jest u�ywana, wtedy Ostrze�enie (WARN) otrzymuje stopie� B��du
 (ERROR). Wi�c dzia�anie w ka�dym z tych przypadk�w jest zaka�czane.
		
 MAKEDIR:
 Wszystkie �r�d�a zostaj� wzi�te jako nazwy katalog�w i stworzone w �cie�ce 
 docelowej.

 MOVE:
 Przenoszenie, zamiast pliki kopiowa� COPY je po prostu przenosi.

 DELETE:
 Ta opcja jest bardzo niebezpieczna, zamiast pliki kopiowa� s� one usuwane!

 HARD=HARDLINK:
 Podczas kopiowania obiekty s� dowi�zywane jako po��czenie twarde. Dzia�a tylko
 wtedy, gdy �r�d�o i docelowa �cie�ka s� na tym samym dysku.
 Gdy opcja ALL jest za��czona, to katalogi s� tworzone rekurencyjnie, 
 w przeciwnym razie kopiowane s� tylko katalogi.

 SOFT=SOFTLINK:
 Podczas kopiowania katalog�w, po��czenie mi�kkie jest tworzone. Te linki mog�
 by� u�ywane tak�e pomi�dzy dwoma r�nymi dyskami. Mi�kkie po��czenia mog� by�
 tworzone tylko dla katalog�w, pliki s� pomijane. Opcja FORCELINK jest zawsze
 ustawiona jako prawda (true).
 OPIS:   Po��czenia mi�kkie nie s� wspierane przez system i mog� by�
        niebezpieczne. Sugeruj� ich nie u�ywa�!

 FOLNK=FORCELINK:
 Gdy po��czenie powinno by� mo�liwe, to ta opcja jest wymagana. Zobacz sekcj�
 "About links" dla prawdopodobnych b��d�w.

 FODEL=FORCEDELETE:
 Usuwanie zamiast kopiowania, ale wraz z pomijaniem bit�w ochronnych.

 FOOVR=FORCEOVERWRITE:
 Nadpisywanie, nawet gdy pliki s� chronione to zostaj� nadpisane.

 DONTOVR=DONTOVERWRITE:
 Ta opcja chroni przed nadpisywaniem.



Zobacz tak�e
~~~~~~~~~~~~
::


     Delete, Rename, MakeDir, MakeLink


