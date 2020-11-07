#include "../lib/my_zsh.h"

int main(int ac, char **av, char **envp)
{
        int leave = true;
        char **envp_c = malloc_env(envp);
        if (ac && av[0]) {}
        // for (int i = 0; envp[i] != NULL; i += 1)
        // {
        //         printf("%s\n", envp[i]);
        // }
        while (leave)
        {
                leave = prompt(envp_c);
        }

        clear_envp(envp_c);
        return 0;
}