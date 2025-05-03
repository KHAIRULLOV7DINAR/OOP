all: father son1 son2 son3

father: father.c
	gcc father.c -o father

son1: son1.c
	gcc son1.c -o son1

son2: son2.c
	gcc son2.c -o son2

son3: son3.c
	gcc son3.c -o son3

clean:
	rm -f father son1 son2 son3 signals_after_log.txt signals_after_wait_log.txt signals_before_log.txt
