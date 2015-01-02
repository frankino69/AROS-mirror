.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <execute>`_ `Next <fault>`_ 

---------------


======
FailAt
======

Format
~~~~~~
::

	FailAt <limit>


Sk�adnia
~~~~~~~~
::

	RCLIM/N


�cie�ka
~~~~~~~
::

	C:


Funkcja
~~~~~~~
::

	FailAt ustawia limit kodu b��du w skrypcie. Je�li jaka� komenda zwr�ci
	kod b��du wi�kszy b�d� r�wny tej warto�ci to skrypt zostaje przerwany.

	Wsp�lne kody b��d�w:
         0   - Brak b��du
         5   - Ostrze�enie
         10  - B��d
         20  - Powa�ny b��d

	Standardowo limit wynosi 10.


Przyk�ad
~~~~~~~~
::

	Je�li mamy skrypt z komendami

         Copy RAM:PewienPlik DF0:
         Echo "Sko�czone!"

	i plik RAM:PewienPlik kt�ry nie istnieje

         Copy: object not found
         Copy: returned with error code 20

	skrypt si� zatrzyma. Ale je�li wcze�niej zadeklarujesz komende

	FailAt 21
	
	wtedy skrypt zostaje wykonywany dalej dop�ki nadal kody b��d�w b�d�
	ni�sze od limitu.



