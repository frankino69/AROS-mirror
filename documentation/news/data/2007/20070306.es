=============
Status Update
=============

:Author:   Paolo Besser
:Date:     2007-03-06

�Habemus DOSpackets!
--------------------

Robert Norris hizo el env�o preliminar del sistema de paquetes de
AROS a nuestro dep�sito, adem�s de un manejador del sistema de archivos
FAT. Aqu� est� lo que dijo:

"packet.handler es un sistema de archivos "proxy" de estilo AROS que tiene
la responsabilidad principal de tomar FSA/IOFileSys, convertirlos a DosPackets
y enviarlos al manejador basado en paquetes.

Lo importante a resaltar del packet.handler es que est� dise�ado para imitar
el ambiente de manejadores del AmigaOS tanto como es posible, a fin de 
disminuir la cantidad del trabajo necesario para transferir un sistema de archivos.

fat.handler es un manejador FAT12/16/32. Es de solo-lectura, y a�n tiene algunos
errores, pero demuestra el concepto. Queda bastante trabajo por hacer antes de 
que considere terminada la recompensa. Los comentarios son bienvenidos."

El soporte de DOSPackets y el solo-lectura de FAT deber�a estar disponible en las
venideras nightly builds.

Otras noticias
--------------

Pavel Fedin a�adi� el soporte de VESA v1.2, permitiendo que m�s (y viejas)
placas de video sean compatibles con AROS. Tambi�n agreg� el cambio del
modo VESA al bootstrap, haciendo al hidd menos dependiente del GRUB arreglado.

Neil Cafferkey repar� el soporte de 64 bits del disco. Ahora la partici�n
de arranque puede tener m�s de 4GB de espacio.

Hogne Titlestad present� la versi�n 0.3.2 de su asombroso programa de pintura
`Lunapaint`__, que tiene una herramienta de texto. `Aqu�`__ puedes verlo en una nueva
captura de pantalla.

El `KGB Archiver`__ de Tomasz Pawlak ha sido pasado a AROS por FOrest. Lo hallar�s
en los `Archives`__. Advierte que todav�a no ha tenido mucha prueba.

__ http://www.sub-ether.org/lunapaint/
__ http://www.sub-ether.org/lunapaint/upload/032.jpg
__ http://www.aros.ppa.pl/images/photoalbum/48.jpg
__ http://archives.aros-exec.org
