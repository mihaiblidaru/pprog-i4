Para ejecutar el juego con el archchivo entrada.ent hay que desactivar las reglas del juego
ya que no hay forma de tener una lista de comandos fija para completar el juego

Para ello hemos añadido un parametro -no_rule 

Entonces para ejecutar el juego con ese archivo de entrada usas

./indiana_jones spaces.dat objects.dat links.dat player.dat -no_rule no_wait -l log.txt < entrada.ent


Si se ejecuta sin el parametro -no_rule, es posible que el juego no llegue al final porque
puede que los objetos se oculten o que algun enlace se cierre, lo que invalida la secuencia de comandos.

El parametro no_wait es para que el juego omita la intro y salte directamente al juego

