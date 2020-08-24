all:  compile bin 
	#executavel na pasta bin
	#Se nececitar exemplos corra make examples.
examples: exemples/carros.txt exemples/pilotos.txt
	cp exemples/*.txt bin
	#exemplos copiados para a pasta bin.
bin:
	mkdir bin/ && mv run bin/
compile:source/main.c source/campeonato.c source/corrida.c source/menus.c source/pilotos.c source/utils.c source/carros.c
	gcc source/main.c source/campeonato.c source/corrida.c source/menus.c source/pilotos.c source/utils.c source/carros.c -o run -std=c99
