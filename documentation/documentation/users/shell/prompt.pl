.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <path>`_ `Next <protect>`_ 

---------------


======
Prompt
======

Sk�adnia
~~~~~~~~
::


	PROMPT


�cie�ka
~~~~~~~
::


	Workbench:c


Funkcja
~~~~~~~
::


	Okre�la lini� komend dla konkretnego CLI.


Parametry
~~~~~~~~~
::


		PROMPT	--	Ci�g kt�rym okre�la si� wygl�d CLI, oto
				przy�adowe argumenty:

		N	--	numer cli
		S	--	nazwa aktualnego katalogu
		R	--	kod b��du

	Je�li PROMPT nie jest okre�lone to "%N.%S> " jest u�ywane za domy�lne.


Wynik
~~~~~
::


	Standardowe kody b��d�w.


Przyk�ad
~~~~~~~~
::


	Prompt "Tu Camelek!.%N> "	daje:

	Tu Camelek!.10>			(je�li numer CLI by� 10)


Zobacz tak�e
~~~~~~~~~~~~
::


	SetPrompt()


