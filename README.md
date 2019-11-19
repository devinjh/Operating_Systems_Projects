# OS Project X
By Andrew Robinson, Tristan Hess, and Devin Hopkins

# Implementing Commands
We simply created a huge if-else block. Since the commands were already parsed with the given file, we simply compared the command with the list of commands we were given. If they matched, we got the Linux command (along with any arguments that were given) and executed the Linux command, giving us the desired outcome.

Commands implemented are: C (copy), D (delete), E (echo), H (help), L (list), M (make), P (print), Q (quit), S (surf the web), W (clear the screen), and X (run a program).

# Help Function
The help function displays what each of the commands do and how to use them.

# How To Run Our Shell
To run out shell, execute:

gcc shell.c -o output

And then run:

./output

You will then be in our shell!
