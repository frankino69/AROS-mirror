================
Stav aktualizace
================

:Autor:   Paolo Besser
:Datum:   15.11.2007

Posledn� zpr�vy
---------------

AROS se v posledn�ch t�dnech do�kal mnoha vylep�en� a tak� opraven�
spousty chyb. Pro p�edstavu, Neil Cafferkey opravil n�kolik z�va�n�ch
chyb v jeho milovan�m `AROS Instal�toru`__; Nic Andrews pracoval na sv�m
ovlada�i s�ov� karty RTL8139; Robert Norris opravil chybu v hl�en�
o souboru, kter� bylo p�edt�m �patn� nastaveno. Ale to byly jmenov�ny
pouze t�i. 

Robert Norris p�idal SDL ovlada� pro linux host�c� AROS. D�ky tomu
si m��e� vytvo�it hostovan� AROS, kter� nevy�aduje X server
(te� u� Xka nemus� instalovat). Teoreticky by to mohlo pomoci
s hostov�n�m na ostatn�ch platform�ch (kdekoli, kde je SDL), i kdy� je to trochu
pomalej�� ne� s X serverem.

Matthias Rustler naportoval ptplay.library pro AROS. Tato knihovna
p�ev�d� Protracker moduly do zvukov�ch vzork�. D�le tak� naportoval
jednoduch� p�ehr�va� - ShellPlayer. Tyto budou v no�n�ch
sestaven�ch, v �upl�ku Extras/MultiMedia/Audio.

Matthias Rustler tak� vytvo�il po��te�n� port `Wazp3D`__ od Alaina Thelliera 
pro AROS. Wazp3D je knihovna, kter� by m�la b�t kompatibiln�
se slavnou knihovnou Warp3D.library pro AmigaOS 68040. Portov�n�
3D Amiga her na AROS by m�lo b�t jednodu���. Wazp3D m��e tak� pracovat jako
softwarov� renderer, kter� klame ostatn� aplikace t�m, �e se tv��� jako
3D hardwarov� ovlada�.

Michal Schulz u�inil n�kolik velk�ch krok� vp�ed s jeho
`x86-64`__ portem AROSu. Den 64 bitov�ho AROSu je st�le bl�.
Michal tak� p�idal podporu SSE instrukc�.

Petr Nov�k p�elo�il `aros.org do �e�tiny`__.


__ http://aros-exec.org/modules/newbb/viewtopic.php?topic_id=2319
__ http://ftp.ticklers.org/pub/aminet/driver/video/Wazp3D.readme
__ http://msaros.blogspot.com/2007/10/very-close.html
__ http://www.aros.org/cs


