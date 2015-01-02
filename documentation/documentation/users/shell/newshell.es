========
NewShell
========

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <makelink>`_ `Next <path>`_ 

---------------

::

 NewShell 

Synopsis
~~~~~~~~
::


     WINDOW,FROM


Ubicaci�n
~~~~~~~~~
::


     Workbench:C


Funci�n
~~~~~~~
::


     Crea un nuevo shel en una ventana de consola. Esta ventana se 
     convertir� en la ventana activa. El nuevo shell hereda la mayor�a de
     los atributos del shell padre, como el directorio actual, el tama�o
     de pila, el prompt y lo dem�s.
     Sin embargo, es completamente independiente del shell padre.
         La ventana que pertenece al nuevo shell se puede especificar
         usando la palabra clave WINDOW.


Entradas
~~~~~~~~
::


     WINDOW  --  La especificaci�n de la ventana del shell.

                 X         --  el n�mero de p�xeles desde el borde izquierdo
                               de la pantalla.
                 Y         --  el n�mero de p�xeles desde el borde superior
                               de la pantalla.
                 WIDTH     --  el ancho en p�xeles de la ventana del shell.
                 HEIGHT    --  el alto en p�xeles de la ventana del shell.
                 TITLE     --  el texto en la barra de t�tulo de la ventana
                               del shell
                 AUTO      --  la ventana aparece autom�ticamente cuando el
                               programa necesita entrada o salida.
                 ALT       --  la ventana aparece con el tama�o y la posici�n
                               especificada cuando se aprieta el gadget de aumento.
                 BACKDROP  --  la ventana es una ventana ###backdrop ???
                 CLOSE     --  incluye un gadget de cierre.
                 INACTIVE  --  la ventana no se vuelve activa cuando se abre.
                 NOBORDER  --  la ventana no tiene bordes, solamente est�n
                               disponibles los gadgets de profundidad, aumento
                               y tama�o.
                 NOCLOSE   --  la ventana no tiene el gadget de cierre.
                 NODEPTH   --  la ventana no tiene el gadget de profundidad.
                 NODRAG    --  la ventana no se puede arrastrar; implica NOCLOSE.
                 NOSIZE    --  la ventana no tiene el gadget de tama�o.
                 SCREEN    --  el nombre de la pantalla p�blica donde se abrir� la ventana.
                 SIMPLE    --  si la ventana es agrandada el texto se expande
                               para llenar el espacio disponible.
                 SMART     --  si la ventana es agrandada el texto no se expandir�.
                 WAIT      --  la ventana s�lo se puede cerrar seleccionando
                               el gadget de cierre o ingresando CTRL-\.


     FROM    --  El archivo a ejecutar antes de ###resorting a las
                 operaciones normales del shell. Si no se especifica
                 nada se usa S:Shell-Startup.


Ejemplo
~~~~~~~
::


     NewShell "CON:10/10/640/480/My own shell/CLOSE"


