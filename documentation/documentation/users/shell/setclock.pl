.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <set>`_ `Next <setdefaultfont>`_ 

---------------


========
SetClock
========

Format
~~~~~~
::

	SetClock {LOAD|SAVE|RESET}


Sk�adnia
~~~~~~~~
::

	LOAD/S,SAVE/S,RESET/S


�cie�ka
~~~~~~~
::

	C:SetClock


Funkcja
~~~~~~~
::

	SetClock mo�e by� wykorzystywany do:
		o	Wczytywania czasu z zegara sprz�towego, podtrzymywanego
			bateri�
		o	Zapisywania czasu z zegara sprz�towego, podtrzymywanego
			bateri�
		o	Resetowania czasu z zegara sprz�towego, podtrzymywanego
			bateri�


Przyk�ad
~~~~~~~~
::


	SetClock LOAD
	
	Ustawia czas ze sprz�towego zegara. W wi�kszo�ci przypadk�w jest to 
	robione automatycznie, wi�c nie ma potrzeby uruchamia� tego r�cznie,
	przydaje si� to tylko wtedy, gdy zegar, jest w rozszerzeniu, kt�re
	nie za�atwia tego samodzielnie.
	

	SetClock SAVE

	Ustawia czas z programowego zegara. Zapisuje czas do sprz�towego zegara.


	SetClock RESET
	
	Resetuje dat� do pierwszego stycznia tysi�c dziewi��set 
	siedemdziesi�tego �smego roku, a czas do godziny zero. Najcz�ciej
	wykorzystuje si� t� opcj� do naprawy zegara sprz�towego, gdy zapis i 
	odczyt nie dzia�a prawid�owo.


Zobacz tak�e
~~~~~~~~~~~~
::

	C:Date, Prefs/Time


