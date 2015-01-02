=====================================
�nnu ett (ej kalender) �r i �terblick
=====================================

:F�rfattare:   Neil Cafferkey
:Datum:        2012-10-21

�nnu ett �r har passerat. Ett �r av programmering ist�llet f�r
nyhetsuppdatering och ytterligare en samling h�jdpunkter att f�rmedla.

Ny Webbl�sare
-------------

AROS anv�ndbarhet tog ett stort steg framm�t i.o.m. att den modernare och
webbstandard-kompatibla Odyssey Web Browser (OWB) portades till AROS. Baserad
p� WebKit-motorn, inkluderar Odyssey en JIT Javaskript kompilator och har st�d
f�r surfning via flikar, HTML5, CSS, SVG och SSL. Odyssey erbjuder �ven med
sitt grafiska anv�ndar gr�nssnitt (GUI), hantering av bokm�rken, historik,
l�senordshantering med mera.


Plattformar
-----------

Supporten f�r ARM-arkitekturen har fortsatt att mogna och variera sig, via
nattliga uppdateringar s� finns det numera Linux-underbyggda AROS ARM system
tillg�ngliga. Ett speciellt intresse finns i att anv�nda AROS p� ARM-baserade
Raspberry Pi system, vilket nu b�rjar bli m�jligt d� en Linux-underst�dd
AROSvariant har b�rjat se dagens ljus f�r just detta system.

Vidare s� har arbetet med andra plattformar f�r AROS fortsatt. Den
windows-underbyggda versionen har f�tt ett antal programfel �tg�rdade och �r
numera betydligt stabilare, samtidigt som kompatibiliteten med original-Amigan
har fortsatt att f�rb�ttrats.


N�tverk
-------

Tr�dl�s n�tverks hantering har mognat i.o.m. tv� nya WPA-kompatibla
drivrutiner. Den ena f�r Realtek RTL8187B-baserade USB-n�tverkskort. Den andra
�r en uppdaterad version av Prism-II-drivrutinen, som var den f�rsta
drivrutinen f�r tr�dl�sa n�tverk redan 2005. Ett grafik baserat hj�lpmedel f�r
att skanna och ansluta till tr�dl�sa n�tverk har ocks� sett dagens ljus under
�ret.

Mobilt bredband �r numera betydligt enklare att konfigurera och anv�nda. Fler
USB-enheter och telefoner st�ds. AROS kan numera hantera delade SMB enheter.
Dock begr�nsas detta till �ldre windows och linux versioner samt NAS enheter.


Andra f�rb�ttringar
-------------------

Begynnande skrivarst�d har initierats till AROS. Komponenter till dom nya
strukturerna inkluderar ett grafiskt gr�nssnitt, en postscript-skrivarerutin
samt flera traditionella tillbeh�r som t.ex. en grafisk fildump och en
Printfiles-funktion. Utskrifter kan omdirigeras till USB, Parallell eller
Serieport eller alternativt till en fil.

V�r Intel GMA drivrutin har f�tt 3D support f�r vissa chip-revisioner, dock
har GMA h�rdvaran begr�nsade m�jligheter j�mf�rt med modernare nVidia och
AMD-kort. M�nga �ldre spel (av vilka flera har portats p� senare tid) fungerar
dock bra. Vi har ocks� f�tt en OpenGL-drivrutin till Linux-underbyggda
3D-grafik-system och en uppdaterad nVidia drivrutin.

Utbudet av ljud drivrutiner tillg�ngliga f�r AROS har f�rb�ttrats, bl.a. med
drivrutiner till ES137x och CMI8738 ljud-chippen. Den f�rstn�mnda �r speciellt
intressant d� den erbjuder utg�ende ljud under VMWare. V�r HD Audio drivrutin
har ocks� f�tt en bredare kompatibilitet vad g�ller ljud�tergivning och
inspelnings l�gen.

F�rb�ttringar har gjorts g�llande disk�tkomst fr�n AROS. Vi har nu en
AHCI-drivrutin som tillhandah�ller grundl�ggande SATA-tj�nster p� flera
moderna maskiner. Till�ggas kan �ven att standard windows-partitoner nu kan
l�sas tack vare en tidig version av en NTFS hanterare och skrivhastigheten
till FAT-partitoner har f�rb�ttrats. Nya open source CD-br�nnar-programmet
Frying Pan �r nu en standard komponent i AROS.

Sist men inte minst ledde v�rt "papercuts" initiativ till att m�nga mindre
men irriterande programfel har r�ttats till i hela AROS systemet.


Vidare utveckling
-----------------

AROS har nu f�tt sin f�rsta utg�va f�r original (MC680x0) Amiga-plattformar,
`AROS Vision`__. S�v�l som till AROS-systemet sj�lvt, AROS Vision inkluderar m�nga
fritt distribuerbara 3:e-parts-AmigaOS-systemkomponenter och applikationer.

En annan ny AROS utg�va �r `AEROS`__, som riktar sig till att kombinera det
b�sta fr�n AROS och Linux i en v�l samansvetsad milj�. F�r nuvarande finns
versioner f�r x86 och ARM baserade system.

__ http://www.natami-news.de/html/aros_vision.html
__ http://www.aeros-os.org/
