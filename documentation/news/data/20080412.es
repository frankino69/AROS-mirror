===================
Cuadro de Situaci�n
===================

:Autor:   Paolo Besser
:Fecha:   2008-04-12

Distribuciones
--------------

Recientemente han sido lanzadas dos nuevas distribuciones de AROS:
VmwAROS LIVE! y una nueva versi�n de WinAROS. La primera es un entorno
preconfigurado (de arranque o instalable) basado en una m�quina virtual
VmwAROS; la otra es una m�quina virtual completa adaptada a QEMU,
con IDE y entorno de desarrollo actualizado. M�s detalles en nuestra
`p�gina de descargas`__. Se invita a usuarios y desarrolladores de aplicaciones
a descargarlos.

�ltimas noticias
----------------

Krysztof Smiechowicz y Alain Greppin han provisto un paquete gcc/g++ 3.3.1
de c�digo ejecutable espec�fico para i386 - basado en los parches de Fabio,
que puede descargarse desde nuestros Archivos. Obviamente, son buenas
noticias para aquellos interesados en desarrollar o adaptar software a AROS,
y no son las �nicas: en los Archivos tambi�n se encuentra la nueva versi�n
del Murks!IDE con respaldo para C++, el mejor Entorno de Desarrollo Integrado
de AROS, provisto por Krysztof Smiechowicz y Heinz-Raphael Reinke.

Tambi�n es hora de hacer grandes correcciones. Krysztof Smiechowicz ha
comenzado a revisar la completitud de las API, mientras Barry Nelson
revisaba, filtraba y comenzaba a administrar nuestro rastreador de errores.
Muchos de los errores ya corregidos han sido removidos de la lista.

Nic Andrews y Alain Greppin finalmente han implementado grub2 en AROS. Nic
tambi�n expuso una agradable `captura de pantalla`__ en Aros-Exec. Lo bueno
de esto, es que los usuarios podr�n desahacerse finalmente de las lentas
particiones FFS y cargar los archivos de sistema desde otras en SFS.
Sin embargo, no recomendamos a�n esta opci�n, debido a incompatibiliades
todav�a existentes con algunas aplicaciones AROS.

Alain Greppin ha obtenido la recompensa del AROS DHCP con su comando dhclient.
Ahora, AROS puede obtener una direcci�n IP autom�ticamente. Tambi�n adapt�
`TeXlive`__.

Tomasz Wiszkowski y Michal Schulz est�n trabajando para mejorar el ata.device.
Se ha agregado cierto respaldo inicial para algunos chipsets Serial ATA:
"Los controladores SATA que respaldan el modo de operaci�n heredado (legacy)
deber�an estar operativos (es decir que no tenemos AHCI por el momento)".

__ http://aros.sourceforge.net/download.php
__ http://i175.photobucket.com/albums/w131/Kalamatee/AROS/grub2gfx-1.jpg
__ http://www.chilibi.org/aros/texlive

