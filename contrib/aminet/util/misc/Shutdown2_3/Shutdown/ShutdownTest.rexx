/* Test der shutdown.library */

/* Wird m�chten �ber Funktionsergebnisse informiert werden. */

options results

/* Fall noch nicht aktiv, wird versucht die shutdown.library einzubinden. */

if ~show('l',"shutdown.library") then do
   call addlib 'shutdown.library',0,-30,0
end

/* Die einzige zur Verf�gung stehende Funktion wird aufgerufen und
 * wenn m�glich das Ergebnis ausgegeben.
 */

say shutdown(immediately)
