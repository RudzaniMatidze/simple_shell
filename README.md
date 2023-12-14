# 0x16. C - Simple Shell

## Project objective:
At the end of this project, you are expected to be able to explain to anyone, without the help of Google

## Project to be done in teams of 2 people (my team: Rudzani Matidze, Evelyn Boora)

## Resources:
Read or watch:
- Unix shell
- Thompson shell
- Ken Thompson
- Everything you need to know to start coding your own shell concept page

man or help:
- sh (Run sh as well)

## compilation
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o shell
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o shell_0.3
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o shell_0.4.1
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o simple_shell

## testing

### Your shell should work like this in interactive mode:
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$

### But also in non-interactive mode:
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
