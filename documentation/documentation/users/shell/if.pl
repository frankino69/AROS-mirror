.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <getenv>`_ `Next <info>`_ 

---------------


==
If
==

Sk�adnia
~~~~~~~~
::


	NOT/S,WARN/S,ERROR/S,FAIL/S,,EQ/K,GT/K,GE/K,VAL/S,EXISTS/K


�cie�ka
~~~~~~~
::


	Workbench:C


Funkcja
~~~~~~~
::

	Uruchamia sekwencj� komend wydanych po sobie, je�li warto�� jest true.
	(sekwencja nast�puj�ca po If to linie komend zako�czone Else lub EndIf).
	Dla ka�dej komendy If musi by� EndIf. Je�li jednak stan jest false to
	wtedy wykonywanie przeskoczy do Else lub EndIf.


Parametry
~~~~~~~~~
::


	NOT		--	neguje warto�� stanu

	WARN		--	True je�li warto�� jest wi�ksza b�d� r�wna 5.
	ERROR		--	True je�li warto�� jest wi�ksza b�d� r�wna 10.
	FAIL		--	True je�li warto�� jest wi�ksza b�d� r�wna 20.

	EQ, GE, GT	--	True je�li pierwsza warto�� jest r�wna, wi�ksza
				lub r�wna kolejno wi�ksza od drugiej.

	VAL		--	Wskazuje, �e por�wnanie powinno zmienia� ci�gi
				w warto�ci numeryczne.

	EXISTS <ci�g>	--	True je�li obiekt <ci�g> wyst�puje.



Przyk�ad
~~~~~~~~
::


     If 500 GT 200 VAL
         echo "500 to wi�cej ni� 200"
     Else
         If EXISTS S:User-Startup
             echo "Skrypt User-Startup znaleziony w S:"
             Execute S:User-Startup
         EndIf
     EndIf


Opis
~~~~
::

	ERROR oraz FAIL b�dzie odpowiednie dopiero wtedy je�li poziom b��du
	jest ustawiony przez FailAt (normalnie stopie� ten wynosi 10, i je�li
	jaki� b��d przekroczy lub b�dzie r�wny tej warto�ci, to skrypt zostanie
	przerwany).


Zobacz tak�e
~~~~~~~~~~~~
::


     Else, EndIf, FailAt


