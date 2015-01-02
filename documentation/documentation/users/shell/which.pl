.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <wait>`_ `Next <why>`_ 

---------------


=====
Which
=====

Sk�adnia
~~~~~~~~
::


	FILE/A, NORES/S, RES/S, ALL/S


�cie�ka
~~~~~~~
::


	Workbench:C


Funkcja
~~~~~~~
::

	Znajduje i wypisuje lokalizacj� do okre�lonego programu lub katalogu.
	Programy rezydentne s� oznaczone jako RESIDENT, je�li nie to s� 
	oznaczone jak wewn�trzne INTERNAL.
	
	Which przeszukuje rezydentn� list�, aktualny katalog, �cie�ki 
	wyszukiwania i przypis C:. Je�li obiekt nie zosta� znaleziony, wtedy
	zostanie wys�any kod b��du 5, lecz �aden b��d nie zostanie wy�wietlony.


Parametry
~~~~~~~~~
::


	FILE	--	obiekt do wyszukania
	NORES	--	nie zawieraj pr. rezydentnych w wyniku
	RES	--	tylko rezydentne
	ALL	--	szukaj we wszystkich lokalizacjach dla FILE, to 
			spowoduje, �e zostanie wyszukiwane we wszystkich 
			dost�pnych lokalizacjach, mo�e to spowodowa�, �e po 
			kilka razy wy�wietli po�o�enie tego samego obiektu, np.
			obiekt wyst�puje w aktualnym katalogu i przypisie C:
			
