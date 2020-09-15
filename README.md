# minimalist-shell

> minimalist-shell is as its name says a minimalistic unix shell, which includes all the basic features of a shell, that is to say some built-ins (cd, setenv, unsetenv), all the basic comands using PATH env variable (ls, tree, pwd), redirections and pipes, and a basic error handling. You can find the evolved version of this project here: link.

# Installation, compilation and utilization
#### Installation
After cloning the repository, you have nothing else to install since it is in C and without external libraries !
    
#### Compilation
Compilation of binary using Makefile:
```
make
```

#### Utilization
Launch the shell
```
./mysh
```

# Full Example

```
./mysh
{chetrit@chetrit PSU_minishell2_2019}$ ls
include  Makefile  mysh  src
{chetrit@chetrit PSU_minishell2_2019}$ ls | grep mysh
mysh
{chetrit@chetrit PSU_minishell2_2019}$ cat Makefile > toto ; ls
include  Makefile  mysh  src  toto
{chetrit@chetrit PSU_minishell2_2019}$ cat toto | grep USER
USER = Chetrit
{chetrit@chetrit PSU_minishell2_2019}$ command_that_doesn't_exists
command_that_doesn't_exists: Command not found.
{chetrit@chetrit PSU_minishell2_2019}$ exit
```

>Don't worry, the shell makes a complete copy of your actual environment when launching it, which means you can mess up with your environnement without taking any risks !
