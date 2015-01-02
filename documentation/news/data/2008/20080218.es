===================
Cuadro de Situaci�n
===================

:Autor:   Paolo Besser
:Fecha:   2008-02-18

�ltimas noticias
----------------

Michal Schulz est� trabajando a pleno en la adaptaci�n de AROS a la placa
SAM440 de Acube Systems, y ha obtenido `resultados`__ interesantes. He aqu�
algunas palabras publicadas en `su blog`__: "He decidido separar el n�cleo
(y las bibliotecas que se cargan con �l) del espacio del usuario. El n�cleo
se carga en alg�n lugar de los primeros 16MB de RAM y luego es reubicado
a la direcci�n virtual en lo m�s alto del espacio de memoria de 32 bits.
El cargador funciona de manera similar a como lo hac�a el de x86_64. Pone
todas las secciones exclusivamente de lectura (read-only) por encima de la
base del n�cleo, y todas las secciones de escritura por debajo de la misma.
Dado que soy malvado por naturaleza, mi n�cleo de AROS para SAM440 acapara
toda la memoria *debajo* de su ubicaci�n f�sica para s� mismo. Esta memoria
(unos pocos megas) es utilizada como un dep�sito local para el n�cleo y queda
exclu�do de cualquier tipo de acceso desde modo de usuario".

Nic Andrews est� trabajando en Wanderer, para mejorarlo y arreglar algunos
errores molestos. Actualmente est� "trabajando a los ponchazos en reescribir
el c�digo de presentaci�n de la clase iconlist de Wanderer. El objetivo a
corto plazo es permitir que las ventanas conserven la presentaci�n de �conos y
fondo para que, por ejemplo, el uso de presentaci�n en mosaico para fondos de
iconlist no produzca un notorio parpadeo como lo hace ahora". En `su blog`__
puede encontrarse informaci�n m�s detallada sobre su trabajo.

Internet f�cil
--------------

Michael Grunditz ha lanzado oficialmente sus primeras betas de `SimpleMail`__ 0.32
para AROS. SimpleMail cuenta con la mayor�a de las caracter�sticas necesarias
para un cliente de correo electr�nico moderno, y sigue creciendo. La adaptaci�n
a AROS se encuentra en la secci�n `Archives`__.

Robert Norris hizo montones de avances con su Traveller, su navegador basado
en Webkit. Para hacerlo funcionar, a�n le quedan por escribir algunas
opciones y bibliotecas. Sin embargo, su adaptaci�n de Cairo.library est� bien
encaminada y ha logrado presentar mayormente de manera correcta algunas
p�ginas web. Una `captura de pantalla`__ prometedora se public� fue publicada
en `su blog`__.

Otras novedades
---------------

Recientemente, Jo�o "Hardwired" Ralha ha escrito varios buenos manuales para AROS.
Sin embargo, a�n no est�n terminados y actualmente anda buscando ayuda.
Los documentos disponibles son el `AROS User Manual`__ (50% completo), el
`AROS Shell Manual`__ (70%) y el `AROS Install Manual`__ (25%). Se puede contactar
al autor en `su p�gina`__.

Alain Greppin ha obtenido una recompensa, adaptando TeXlive a AROS. M�s informaci�n
sobre el tema en `su p�gina`__.

Tomek 'Error' Wiszkowski ha estado trabajando en Frying Pan, una aplicaci�n para
quemar CD/DVD. Public� `algunas capturas de pantalla`__ en AROS-Exec.org.
La version 1.3 para AROS (shareware) se puede descargar desde la `p�gina de aplicaciones`__.
Para hacerlo funcionar, tambi�n corrigi� algunos errores en ATA device de AROS.

...y, para aquellos que se lo hayan perdido: el sistema de archivos AROS FFS
recientemente incorpor� una rutina de validaci�n adecuada. �Se acabaron las
particiones de sistema inutilizables!

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
