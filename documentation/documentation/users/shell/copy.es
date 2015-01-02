====
Copy
====

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <changetaskpri>`_ `Next <date>`_ 

---------------

::

 Copy 

Synopsis
~~~~~~~~
::


     FROM/M, TO, ALL/S, QUIET/S, BUF=BUFFER/K/N, CLONE/S, DATES/S, NOPRO/S,
     COM=COMMENT/S, NOREQ/S,

     PAT=PATTERN/K, DIRECT/S,SILENT/S, ERRWARN/S, MAKEDIR/S, MOVE/S,
     DELETE/S, HARD=HARDLINK/S, SOFT=SOFTLINK/S, FOLNK=FORCELINK/S,
     FODEL=FORCEDELETE/S, FOOVR=FORCEOVERWRITE/S, DONTOVR=DONTOVERWRITE/S,
     FORCE/S


Ubicaci�n
~~~~~~~~~
::


     Workbench:C


Funci�n
~~~~~~~
::


     Crea copias id�nticas de uno o m�s archivos.


Entradas
~~~~~~~~
::


     FROM      --  muchos archivos de entrada.
     TO        --  archivo o directorio de destino.
     ALL       --  incluir los subdirectorios.
     QUIET     --  suprimir todas las salidas y los requesters.
     BUFFER    --  tama�o del b�fer para el b�fer de copia en
                   bloques de 512 bytes (por omisi�n 1024 (= 512K))
     CLONE     --  copiar los comentarios, los bits de protecci�n y las fechas tambi�n.
     DATES     --  copiar las fechas.
     NOPRO     --  no copiar los bits de protecci�n.
     COMMENT   --  copiar los comentarios de archivo.
     NOREQ     --  suprimir los requesters.

     PATTERN   --  el patr�n que los nombres de archivo deben respetar.
     DIRECT    --  modo s�lo copia: copia el archivo sin hacer pruebas u opciones.
     VERBOSE   --  muestra m�s informaci�n de salida.
     ERRWARN   --  no continuar si falla un archivo.
     MAKEDIR   --  producir directorios.
     MOVE      --  borrar el archivo fuente despu�s de una copia exitosa.
     DELETE    --  no copiar, sino borrar el archivo.
     HARDLINK  --  hacer un hardlink al archivo fuente en lugar de copiar.
     SOFTLINK  --  hacer un softlink al archivo fuente en vez de copiar.
     FOLNK     --  hacer tambi�n v�nculos a los directorios.
     FODEL     --  borrar tambi�n los archivos protegidos.
     FOOVR     --  tambi�n sobreescribir los archivos protegidos.
     DONTOVR   --  nunca sobreescribir el archivo de destino.
     FORCE     --  NO USE �STE. Solamente para compatibilidad en la llamada.


 Descripciones m�s detalladas:

 FROM:
 El(los) archivo(s) de origen. Para los directorios, todos los archivos contenidos
 son archivos de origen. Puede tener patrones normales.

 TO:
 El archivo de destino o para muchos or�genes, el directorio de destino. Se crea
 el directorio de destino (inclu�dos todos los directorios padres necesarios).
 

 ALL:
 Revisa los directorios recursivamente.

 QUIET:
 La copia es completamente silenciosa. Realmente no hay ninguna salida, �tampoco
 requesters para discos faltantes u otros problemas!

 BUF=BUFFER:
 Especifica el n�mero de b�feres de 512 bytes a copiar. Por omisi�n son 200
 b�feres [100KB de memoria]. La cantidad m�nima es 1 pero no deber�a ser usado.

 PAT=PATTERN:
 PATTERN permite especificar un patr�n normal dos, todos los archivos tienen
 que cumplirlo. Esto es �til con la opci�n ALL.

 Ejemplo:
 Cuando quieras borrar todos los archivos .info en un �rbol de directorio,
 necesitar�s esta opci�n: Copy DELETE #? ALL PATH #?.info

 CLONE:
 El comentario de archivo, la fecha y los bits de protecci�n de los archivos
 de origen se copian al archivo o directorio de destino.

 DATES:
 La informaci�n de fecha del origen se copia al destino.

 NOPRO:
 Los bits de protecci�n de los or�genes NO se copian. Entonces el destino
 tiene los bits por omisi�n [rwed].

 COM=COMMENT:
 El comentario de archivo se copia al destino.

 NOREQ:
 No se muestran las peticiones normales dos,
 cuando ocurre un error.


 DIRECT:
 Ciertos dispositivos no permiten algunos de los tipos de peticiones de
 paquetes usados por DOS. Esta opci�n es realmente un comando f�cil de
 copia, que solamente abre los or�genes y destino directamente sin
 ninguna prueba ni verificaci�n.
 Las opciones ALL, PAT, CLONE, DATES, NOPRO, COM, MAKEDIR, MOVE, DELETE, HARD,
 SOFT, FOLNK, FODEL, FOOVR, DONTOVR y los archivos m�ltiples de entrada no
 se pueden especificar junto con DIRECT. Esta opci�n necesita un archivo de
 entrada y uno de salida.
 Cuando quieras borrar un softlink, que ya no apunta a un archivo v�lido,
 necesitar�s tambi�n esta opci�n.
 Ejemplo de uso: 'Copy DIRECT texto PRT:' para imprimir un archivo
 llamado texto. - COPY maneja bastantes casos como �ste de modo autom�tico,
 pero quiz�s a veces se necesite esta opci�n.

 VERBOSE:
 Copy proporciona salida informativa adicional.

 ERRWARN:
 Copy conoce y devuelve tres tipos de errores de la biblioteca dos.library:
 5   WARN    El procesamiento de un archivo fall�, Copy salta este
             archivo y contin�a con el siguiente.
 10  ERROR   Fall� la creaci�n de un directorio u ocurri� alg�n otro
             error grave. Copy termina despu�s del aviso.
 20  FAIL    Pas� un error realmente grave (no hay memoria, fall� Examine...)
             Copy termina despu�s del aviso.
 Cuando se usa la opci�n ERRWARN, el resultado 5 (WARN) se vuelve el resultado
 10 (ERROR). As� que Copy aborta cada vez un error sucede.

 MAKEDIR:
 Todos los nombres especificados en el campo FROM se toman como directorios, los 
 que se deben crear.

 MOVE:
 Los archivos no se copian, sino que se mueven (o renombran). Esto significa que
 despu�s de una operaci�n mover el origen no existe m�s.

 DELETE:
 �Esto no copia nada, sino que borra los archivos de origen!

 HARD=HARDLINK:
 En vez de copiar los archivos, se crea un hard link. Esto solamente
 funciona cuando el destino est� en el mismo dispositivo que el origen.

 SOFT=SOFTLINK:
 En vez de copiar directorios, se crea un soft link. Estos v�nculos se
 usan tambi�n entre diferentes dispositivos. Los soft links se crean
 solamente para los directorios. Se saltan los archivos. La opci�n
 FORCELINK es siempre puesta a verdadera.
 NOTA: Los softlinks no est�n oficialmente soportados por el OS y
 pueden ser peligrosos. �Yo sugiero que no uses esta opci�n! Mira en la
 descripci�n de abajo.

 FOLNK=FORCELINK:
 Cuando es posible la vinculaci�n de directorios, se necesita esta opci�n.
 Mira en la secci�n "About links" si hay problemas.

 FODEL=FORCEDELETE:
 Cuando est� habilitada esta opci�n, los archivos tambi�n se borrar aunque
 est�n protegidos de ser borrados.

 FOOVR=FORCEOVERWRITE:
 Cuando est� habilitada esta opci�n, los archivos tambi�n se sobreescriben
 aunque est�n protegidos contra la sobreescritura.

 DONTOVR=DONTOVERWRITE:
 Esta opci�n evita sobreescribir los archivos de destino.



Mira tambi�n
~~~~~~~~~~~~

::


     Delete, Rename, MakeDir, MakeLink


