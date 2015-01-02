================
Stav aktualizace
================

:Autor:   Paolo Besser
:Datum:   18.02.2008

Posledn� zpr�vy
---------------

Michal Schulz usilovn� pracuje na portov�n� AROSu na desku SAM440
od Acube Systems a dosahuje zaj�mav�ch `v�sledk�`__. Zde je n�kolik
slov z jeho posledn�ho p��sp�vku na `jeho blogu`__: "Rozhodl jsem se odd�lit
j�dro (a knihovny nahr�van� spole�n� s n�m) od u�ivatelsk�ho prostoru.
J�dro je nahr�no n�kde v prvn�ch 16MB pam�ti RAM a pak p�em�st�no
na virtu�ln� adresu v horn� ��sti 32-bitov�ho adresov�ho prostoru.
Bootstrap loader pracuje stejn�m zp�sobem, jak�m pracoval x86_64 bootstrap.
Cel� ��st pam�ti nahoru od j�dra je pouze pro �ten� (read-only) a cel�
��st dol� od j�dra je zapisovateln� (writable). Proto�e jsem od p��rody
zl�, moje j�dro SAM440 AROSu si bude nenasytn� br�t ve�kerou pam�
*pod* sv�m fyzick�m um�st�n�m pro sebe. Tato pam� (n�kolik megabajt�)
bude pou�ita jako m�stn� �lo�i�t� pro kernel a bude zamezeno jak�koli
form� p��stupu ze strany u�ivatele."

Nic Andrews pracuje na Wandereru, aby ho zdokonalil a opravil
n�kolik otravn�ch chyb. V sou�asn� dob� "trochu p�epracov�v�
renderovac� k�d pro t��du Wanderer iconlist. Pr�b�n�m c�lem je
umo�nit vykreslov�n� ikon/pozad� z vyrovn�vac� pam�ti tak,
�e nap��klad s pou�it�m kachlov�ho vykreslov�n� (tiled rendering) pro pozad�
iconlistu nebude zp�sobov�no znateln� blik�n� ikon, jak se to d�lo dote�".
Podrobn�j�� informace o jeho pr�ci jsou zve�ejn�ny na `jeho blogu`__.


Internet jednodu�eji
--------------------

Michael Grunditz ofici�ln� uvolnil prvn� verzi `SimpleMail`__ 0.32 beta
pro AROS Research Operating System. SimpleMail m� v�t�inu funkc�,
kter� jsou v sou�asn�ch modern�ch email klientech zapot�eb� a st�le
se d�l vyv�j�. Aktu�ln� verze m��e b�t sta�ena z `Archivu`__.

Robert Norris ud�lal zna�n� pokrok s Travellerem (jeho webov� prohl�e� pro AROS
zalo�en� na Webkitu). Aby v�echno spr�vn� fungovalo, je st�le zapot�eb�
dok�dovat n�kolik chyb�j�c�ch funkc� a knihoven, nicm�n� jeho port Cairo.library
je na dobr� cest� a celkem dob�e usp�l p�i zobrazov�n� n�kolika str�nek.
Opravdu slibn� `sn�mky obrazovky`__ byly publikov�ny na `jeho
blogu`__.


Dal�� zpr�vy
------------

Joao "Hardwired" Ralha ned�vno napsal n�kolik dobr�ch p��ru�ek pro AROS.
Nicm�n� nejsou je�t� dokon�en� a on v sou�asn� dob� hled� n�koho, kdo mu pom��e.
Dostupn� dokumenty jsou `AROS u�ivatelsk� p��ru�ka`__ (50% kompletn�ch),
`AROS p��ru�ka pro shell`__ (70%) a `AROS instala�n� p��ru�ka`__ (25%).
Autor je k dosa�en� na `jeho webu`__.

Alain Greppin naportoval TeXlive na AROS, ("bounty" dokon�eno). V�ce informac�
o tomto po�inu na `jeho webu`__.

Tomek 'Error' Wiszkowski pracuje na Frying Pan, aplikaci
pro vypalov�n� CD/DVD. Na AROS-Exec.org zve�ejnil `n�kolik sn�mk� obrazovky`__.
Verze 1.3 pro AROS (shareware) m��e b�t sta�ena z `webu
t�to aplikace`__. Aby spr�vn� fungovala, opravil tak� n�kolik chyb
v ATA rozhran� AROSu.

... a pro v�echny, kdo si toho nev�imli: souborov� syst�m AROS FFS ned�vno z�skal vlastnost
pro kontrolu a opravu integrity na vadn�ch odd�lech. U� ��dn� nepou�iteln� read-only odd�ly!


__ http://msaros.blogspot.com/2008/01/ive-promised-to-show-you-some.html
__ http://msaros.blogspot.com
__ http://kalamatee.blogspot.com/
__ http://simplemail.sourceforge.net/index.php?body=screenshots
__ http://archives.aros-exec.org/index.php?function=showfile&file=network/email/simplemail_beta_aros-i386.tgz
__ http://cataclysm.cx/2008/02/18/cow-launched
__ http://cataclysm.cx
__ http://archives.aros-exec.org/share/document/manual/aros_user_manual_version_0.56a.pdf
__ http://archives.aros-exec.org/share/document/manual/aros_shell_manual_version_0.7a.pdf
__ http://archives.aros-exec.org/share/document/manual/aros_install_manual_version_0.25a.pdf
__ http://aros-wandering.blogspot.com
__ http://www.chilibi.org/aros/texlive
__ http://aros-exec.org/modules/newbb/viewtopic.php?viewmode=flat&topic_id=2569&forum=2
__ http://www.tbs-software.com/fp/welcome.phtml
