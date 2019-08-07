gcc main.c -o minishell

# It doesn't work, the shell never gives back the hand.
#result=$(./minishell <<EFO
#  ls
#  exit
#EFO
#)
#
#echo "$result"
#

result=$(./minishell <<< printf "ls\nexit"
)

echo "$result"
