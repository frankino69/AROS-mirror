.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <cd>`_ `Next <copy>`_ 

---------------


=============
ChangeTaskPri
=============

Format
~~~~~~
::

	ChangeTaskPri <priority> [ PROCESS <process number> ]


Sk�adnia
~~~~~~~~
::

	PRI=PRIORITY/A/N,PROCESS/K/N


�cie�ka
~~~~~~~
::

	Workbench:c


Funkcja
~~~~~~~
::

	Komenda ChangeTaskPri jest u�ywana do zmiany aktualnego priorytetu
	zadania. Jako, �e AROS jest wielozadaniowym systemem operacyjnym,
	mo�esz okre�li� kt�re zadanie b�dzie pobiera�o wi�cej mocy procesora,
	poprzez zmian� jego priorytetu.

	Warto�� priorytetu mo�e by� w granicach od -128 do 127, jednak
	warto�ci wi�ksze od 4 nie s� zalecane, jako �e mog� one zak��ca�
	wa�ne procesy systemowe. Wi�ksza warto�� daje procesowi wi�ksze
	zasoby procesora CPU.

	Mo�esz u�ywa� komendy STATUS, aby sprawdzi� list� zada�, kt�re s�
	uruchomione i ich numery proces�w.
	

Przyk�ad
~~~~~~~~
::

     
	1.SYS:> ChangeTaskPri 1 Process 1

	Ustawia proces 1 na priorytet 1.

	1.SYS:> ChangeTaskPri 1

        Aktualny proces ustawia na priorytet 1.


Zobacz tak�e
~~~~~~~~~~~~
::

     Status


