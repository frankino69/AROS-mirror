=============
Status Update
=============

:Author:   Paolo Besser
:Date:     2007-04-05

Skinnable Wanderer
------------------

Ha sido dado otro importante paso en la personalizaci�n de AROS. 
Darius Brewka y Georg Steger han a�adido un nuevo sistema de decoraci�n
al Wanderer, que le permite al usuario editar y cambiar los temas.
Como un ejemplo se us� el tema ICE de Damir Sijakovic que ahora es el
tema predeterminado de las nightly builds de AROS. Mira en esta
captura de pantalla (`a tama�o completo`__): 

.. image:: /images/20070405.jpeg
   :alt: AROS decorated desktop
   :align: center

�No es bonita? Como sea, intentamos hacer que AROS tenga m�s estilo
y sea agradable de ver. As� que cualquier contribuci�n art�stica
(temas, �conos, wallpapers, gadgets y cosas como �sas) es muy
bien recibida. Para informaci�n adicional, por favor mira en 
`AROS-Exec`__.


Incre�bles noticias
-------------------

Michal Schulz est� trabajando en el controlador de teclado para
su pila USB. Ha enviado una versi�n inicial que deber�a funcionar
casi bien (o sea, deber�a manejar las teclas correctamente aunque
los LEDs no andan). Recuerda que AROS todav�a es compatible
solamente con los controladores USB UHCI en esta etapa.

El sistema de archivos SFS ahora se compila autom�ticamente. Esto
permite que los usuarios monten y usen las particiones SFS de 
una manera f�cil y segura. Pavel Fedin ha actualizado el comando
format para manejar los diferentes sistemas de archivos. Para
formatear una partici�n SFS, deber�as crear con HDToolBox, 
cambia su tipo a SFS y ejecuta este comando del shell:

  FORMAT DRIVE=DH1: NAME=MyVolume

Advierte que GRUB todav�a no puede arrancar AROS de SFS. Por esto
tienes que crear una peque�a partici�n FFS (o EXT3, o FAT) para 
poner el n�cleo y los archivos de arranque y deja que GRUB haga
su trabajo.

Pavel tambi�n est� trabajando en un nuevo sistema de archivo
de CD llamado CDVDFS, que en este momento soporta los CD y DVD
con las extensiones Joliet. Ser� puesto en las nocturnas tan
pronto que sean corregidos algunos errores.

Matthias Rustler ha actualizado AROS LUA a la versi�n 5.1.2.
`Aqu�`__ est� una lista de los errores reparados. Matthias
tambi�n ha creado un nuevo commodity DepthMenu. Cuando el usuario
aprieta el bot�n derecho del rat�n en el gadget profundidad
(es el gadget en el extremo derecho de una ventana), abre
un men� emergente con todas las ventanas abiertas, permitiendo
una selecci�n m�s r�pida.

Staf Verhaegen ha mejorado el soporte para los guiones ARexx/Regina.
Hay un nuevo comando rx en AROS, que espera en el CLI para ejecutar
todos tus guiones ARexx.

Gracias a Bernd Roesch, Zune ahora puede usar las im�genes MUI4
(los archivos .mim). Pavel Fedin ha arreglado un cuelgue en la
clase pendisplay que ocurr�a cuando no hab�a pinceles libres
en la pantalla. Paolo Besser ha agregado otros �conos Gorilla.


__ http://aros-exec.org/modules/xcgal/displayimage.php?pid=239
__ http://aros-exec.org/modules/news/article.php?storyid=227
__ http://www.lua.org/bugs.html#5.1.1
