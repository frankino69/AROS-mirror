================
Stav aktualizace
================

:Autor:   Paolo Besser
:Datum:   12.04.2008

Distribuce
----------

Ned�vno byly vyd�ny dv� AROS distribuce. VmwAROS LIVE! a
nov� verze WinAROS. Prvn� je bootovateln� a instalovateln�
p�edkonfigufovan� prost�ed� zalo�en� na VmwAROS virtu�ln�m stroji,
druh� je QEMU uzp�soben� kompletn� virtu�ln� stroj s IDE a
aktualizovan�m v�vojov�m prost�ed�m. Podrobn�j�� informace jsou dostupn� na na��
`download str�nce`__. Vyz�v�me u�ivatele a v�voj��e aplikac�, aby si
tyto distribuce st�hli.

Posledn� zpr�vy
---------------

Krysztof Smiechowicz a Alain Greppin poskytli ve�ejnosti bin�rn�
bal��ek gcc/g++ 3.3.1 pro architekturu i386 - zalo�en� na Fabiov�ch
oprav�ch, ke sta�en� z Archivu. To je samoz�ejm� dobr� zpr�va pro
v�echny, kdo se zaj�maj� o v�voj a portov�n� softwaru na AROS,
ale nen� jedinou: v Archivu m��e� naj�t tak� novou verzi Murks!IDE
s podporou pro C++ - nejlep�� integrovan� v�vojov� prost�ed� pro AROS,
kter� n�m p�inesli Krysztof Smiechowicz a Heinz-Raphael Reinke.

Nastal tak� �as na proveden� velk�ch oprav. Krysztof Smiechowicz za�al
p�ezkoum�vat �plnost API, zat�mco Barry Nelson prozkoumal, prot��dil a
za�al spravovat n� bug tracker. V�t�ina z u� opraven�ch chyb byla
odstran�na ze seznamu.

Nic Andrews a Alain Greppin kone�n� implementovali grub2 do AROSu.
Nic tak� na Aros-Exec uk�zal `sn�mek obrazovky`__. Skv�lou zpr�vou je,
�e u�ivatel� se mohou kone�n� zbavit pomal�ch FFS odd�l� a spou�t�t
syst�mov� soubory z SFS odd�l�. Tato mo�nost je�t� nen� doporu�ov�na, proto�e
st�le existuj� ur�it� nedostatky v kompatibilit� s n�kter�mi AROS
aplikacemi.

Alain Greppin dokon�il AROS DHCP "bounty" s p��kazem dhclient.
AROS te� m��e z�skat IP adresu automaticky. Tak� naportoval
`TeXlive`__.

Tomasz Wiszkowski a Michal Schulz pracuj� na zdokonalen� ata.device.
Byla p�id�na po��te�n� podpora pro n�kter� chipsety Serial ATA:
"SATA �adi�e podporuj�c� re�im d�d�n� operac� (legacy operation mode) by nyn� m�ly b�t
funk�n� (ale to neznamen�, �e bychom z�skali podporu AHCI)".

__ http://aros.sourceforge.net/download.php
__ http://i175.photobucket.com/albums/w131/Kalamatee/AROS/grub2gfx-1.jpg
__ http://www.chilibi.org/aros/texlive

