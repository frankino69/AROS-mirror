================
Stav aktualizace
================

:Autor:   Paolo Besser a Saimon69
:Datum:   18.07.2008

Posledn� aktualizace
--------------------

Omlouv�me se, �e "Stav aktualizace" p�i�el tak pozd�, ale AROS t�m
velmi tvrd� pracuje "under the hood", aby p�inesl lep��
opera�n� syst�m. N�e je spousta zaj�mav�ch novinek, o kter�ch se mluv�.

Stanislaw Szymczyk dokon�il port linuxem hostovan� verze
na platformu x86-64, a ��asn� pom�h� samokompilov�n� AROSu
portov�n�m pot�ebn�ch n�stroj�. Ten posledn� byl abc-shell a
dosahuje neuv��iteln�ch v�sledk�.

Krzysztof Smiechowicz kontroluje �plnost AROS API, aby bylo
mo�n� sledovat kompatibilitu s AmigaOS a stav cel�ho projektu.
V�sledky si m��e� kdykoli prohl�dnout na na�� aktualizovan� `stavov� str�nce`__.

Pavel Fedin skv�le vylep�il funk�nost HDToolBox: odd�l nyn� m��e b�t
p�em�st�n, �i mu m��e b�t zm�n�na velikost. Tyto nov� funkce v�ak st�le
pot�ebuj� testov�n�. Pavel tak� naportoval BHFormat a zprovoznil
ve Wandereru form�tov�n� disk�.

Pavel Fedin, Krzysztof Smiechowicz a Tomasz Wiszkowski tak� tvrd�
pracuj� na na�ich ata.device a s ATAPI souvisej�c�ch souborech, aby se
zbavili probl�m� s kompatibilitou, kter� znemo��uj� AROSu na n�kter�ch
konfigurac�ch spr�vn� bootovat.

Michal Schulz st�le pracuje na portov�n� AROSu na SAM440EP.
Ned�vno vydal prvn� pracovn� `beta verzi`__, vlastn�ci SAMu si ji mohou
vyzkou�et sami. Nezkou�ejte ji na jin�ch PPC architektur�ch,
nebude fungovat.

Gianfranco Gignina pomohl naj�t a opravit hodn� chyb v Zune,
a za�al pracovat na p�enositeln� a v�ce nez�visl� verzi
Wandereru. C�lem projektu je umo�nit jednodu��� portov�n� Wandereru
i na ostatn� AmigaOS platformy.

M�me tu novou, velmi cennou implementaci jazyka E na AROS:
je to `PortablE`__ a ur�it� stoj� za vyzkou�en�!

Nick Andrews p�e ovlada� pro s�ovou kartu Intel Gigabit E1000 na AROS, kter�
umo�n� p�ipojen� k s�ti velk�mu mno�stv� z�kladn�ch desek, na nich� je tato
karta integrov�na.

Paolo Besser vydal novou verzi jeho distribuce VmwAROS 0.8b,
kter� p�in�� lep�� vzhled a kompatibilitu.
Stejn� jako v minulosti, VmwAROS je k dispozici ve dvou verz�ch:
`live CD`__, kter� b�� na x86 hardwaru a m��e b�t
nainstalov�no na pevn� disk, a `virtu�ln� prost�ed�`__ pro
VMware.

__ http://aros.sourceforge.net/it/introduction/status/everything.php
__ http://msaros.blogspot.com/2008/05/try-it-yourself.html
__ http://cshandley.co.uk/portable
__ http://live.vmwaros.org
__ http://ve.vmwaros.org

