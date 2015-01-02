=============
Status Update
=============

:Author:   Paolo Besser
:Date:     2007-11-15

�ltimas noticias
----------------

AROS tuvo bastantes correcciones y mejoras en las recientes semanas.
Por ejemplo, Neil Cafferkey corrigi� algunos importantes fallos en su
amado `AROS Installer`__; Nic Andrews trabaj� en su controlador de 
red RTL8139; y Robert Norris arregl� las notificaciones de archivo,
que antes romp�an las preferencias; s�lo para nombrar tres. 

Robert Norris a�adi� un controlador SDL para el AROS alojado en Linux.
Esto te permite armar un AROS alojado que no necesite de X (incluso ya 
no tienes que instalarlo para armar AROS). En teor�a esto podr�a ayudar
para tener la versi�n alojada funcionando en otras plataforma (donde 
exista SDL), aunque es un poco m�s lento que el controlador de X.

Matthias Rustler pas� la ptplay.library a AROS. Esta biblioteca reproduce
los m�dulos de Protracker como muestras de sonido. Tambi�n pas� a
ShellPlayer, que es un reproductor de ejemplo. Ambos traspasos estar�n
en las nightly builds, en el caj�n Extras/Multimedia/Audio.

Matthias tamb�en acaba de hacer un puerto preliminar del `Wazp3D`__
de Alain Thellier para AROS. Se trata de una biblioteca pensada 
para ser compatible con la famosa Warp3D.library de AmigaOS 68040,
y hace m�s f�cil pasar algunos juegos tridimensionales de Amiga a
AROS. Wazp3D tambi�n puede funcionar como un renderer por software,
enga�ando a las aplicaciones que buscan un controlador de hardware 3D.

Michal Schulz di� otros grandes pasos con su puerto `x86-64`__ de AROS.
Se acerca el d�a de AROS 64 bits. Mientras tanto, Michal agreg�
el soporte a las instrucciones SSE.

Petr Novak tradujo `aros.org al checo`__.


__ http://aros-exec.org/modules/newbb/viewtopic.php?topic_id=2319
__ http://ftp.ticklers.org/pub/aminet/driver/video/Wazp3D.readme
__ http://msaros.blogspot.com/2007/10/very-close.html
__ http://www.aros.org/cs


