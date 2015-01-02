=============
Status Update
=============

:Author:   Paolo Besser
:Date:     2007-03-21

Soporte USB preliminar
----------------------

El Dr. Michal Schulz acaba de hacer un env�o preliminar de la 
pila USB de AROS, que permite el uso de un rat�n USB y la 
creaci�n de los fundamentos para agregar el soporte, subsecuentemente,
para otros dispositivos. Por favor advierte que este software
est� en etapa pre-alpha, lo que significa que solamente tienen
soporte los controladores UHCI de USB 1.1 por ahora, y quiz�s
no funcionen correctamente con tu placa madre. Lo siguiente a
desarrollar son las extensiones a la clase USBHID, que permitan
el uso de tabletas gr�ficas y teclados USB con AROS, y el
soporte de los controladores OHCI. Debemos avisar que el
soporte para los controladores EHCI de USB 2.0 no est�n
definidos en la recompensa en que trabaja Michal.
Para mejorar la funcionalidad y la compatibilidad, se necesita
una enorme prueba beta. As� que animamos a todos los 
suficientemente valientes para que nos ayuden, descargando
las nightly builds de los d�as que vienen e informen de
cualquier problema que encuentren. Para activar la pila entera
en las m�quinas UHCI, el comando es::

  C:Loadresource DRIVERS:uhci.hidd


Otras noticias
--------------

Nic Andrews ha mejorado ligeramente la AROSTCP, d�ndonos una
mejor (y m�s compatible) pila de red. Tambi�n se hizo el trabajo
de reparaci�n en el controlador del VIA Rhine y se agreg� una prueba 
RTL8139.

Pavel Fedin est� todav�a trabajando en los modos VESA mejorados:
"Arreglado el c�digo de conmutaci�n del modo VESA. Se quit� la
paleta est�tica, ya no es necesaria. Los colores del puntero del
rat�n en las pantallas de 16 y 256 colores est�n fijos". Tambi�n
repar� la inicializaci�n de algunas viejas tarjetas con unas
BIOS defectuosas. Adem�s incorpor� el dispositivo (device)
Trackdisk de MorphOS. Un nuevo programa pref para Trackdisk
permite el modo 'sin-apretar' (no-click) de la unidad de disquete
sin agregar argumentos a la l�nea de comandos del n�cleo en GRUB.