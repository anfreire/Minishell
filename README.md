# ༼つಠ益ಠ༽つ   **Minishell** 	୧༼ಠ益ಠ༽୨

## -> = Next Command

- [ ] Comandos com pipe (env | grep A=2) não termina a execução.
- [ ] Leaks (parsing_allocs.c) ⤵ ###
- (./minishell -> ./minishell -> exit -> exit)
- (echo -n teste -> exit)
- (echo teste >> 1.txt -> exit
- (^C ->  ^C   ->   exit)
Observação:
Visto o comportamento da execução do comando em cima consegui concluir que não era o exit que estava a causar problema, mas sim o ^C, porque se manda-se dois ^C obtinha (Direct leak of X byte(s) in 2 object(s)), e se envia-se dois SIGINT, obtinha 3 e por ai consecutivamente.
Com isto conclui-se que tinha alguma relação. Mas qual era o comportamento dos sinais?
Uma linha vazia....
Portanto a razão dos problema, neste caso foi a razão da linha vazia, que não necessitava de nenhum tipod e processamneto nem de alocação.
- [ ] O SEGV não se deve ao / no final da string. já foi removido e continua a dar....                        
