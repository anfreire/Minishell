## ༼つಠ益ಠ༽つ   **Minishell** 	୧༼ಠ益ಠ༽୨


- [ ]  Corrigir Exit Status (g_exit) → exit_minishell.c
- [X]  CD   (SEGV) não se deve ao / no final da string. já foi removido e continua a dar.... 
> ORIGEM:
> free_cmds
> 
> while (data->paths.path_cmd[++i])
> 
> free(data->paths.path_cmd[i]);
- [X]  Export tem que ser o pai, não está a funcionar
- [X]  CD tem que ser o Pai, não está a funcionar
- [X] LEAKS
- [ ]  Comando (env |   grep  teste) não termina execução....
