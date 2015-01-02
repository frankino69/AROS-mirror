.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Next <alias>`_ 

---------------


==========
AddBuffers
==========

Sk�adnia
~~~~~~~~
::


	DRIVE/A, BUFFERS/N


�cie�ka
~~~~~~~
::


	Workbench:C


Funkcja
~~~~~~~
::

	Dodaje bufory do listy dost�pnych bufor�w dla okre�lonego
	dysku. Dodawanie bufor�w przy�piesza dost�p do dysku, ale
	zwi�ksza ilo�� zaj�tej pami�ci systemowej (512 bajt�w na
	bufor). Okre�laj�c negatywn� liczb� bufor�w zmniejsza si�
	liczb� bufor�w dysku.
		Je�li podany jest tylko argument DRIVE, to zostanie
	podana liczba bufor�w dysku, bez zmiany jego warto�ci.



Parametry
~~~~~~~~~
::


	DRIVE	--	parametr okre�laj�cy nazw� dysku
	BUFFERS	--	liczba dodawanych bufor�w (lub odejmowanych
			w przypadku ujemnej warto�ci) dysku

