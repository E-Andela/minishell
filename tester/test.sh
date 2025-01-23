#!/bin/bash

FOLDER=~/bullshit
if test -e "$FOLDER"; then
	echo "$FOLDER exists! yes baby" > /dev/null
else
	mkdir ~/bullshit
fi

rm lol 2> /dev/null
rm cat 2> /dev/null
rm test 2> /dev/null
rm NONEXISTINGFILE 2> /dev/null
rm test1 2> /dev/null

make -C .. > /dev/null 2> /dev/null

printf "\e[32mWELCOME TO THE TESTER BABY\e[0m\n\n"
printf "\e[32moutput and exit codes are expected to match.\nerror messages may differ so dont take those too serious\e[0m\n\n"
declare -i WRONG=0
err_mini=~/bullshit/err_mini
out_mini=~/bullshit/out_mini
out_bash=~/bullshit/out_bash
err_bash=~/bullshit/err_bash

print_diff () {
	printf "	mini:\n		$(cat -e "$1")\n"
	printf "	bash:\n		$(cat -e "$2")\n"
}

compare_command ()
{
	TEST="$1"
	echo -n "$TEST" | .././minishell 2>$err_mini >$out_mini
	mini_exit="$?"
	echo -n "$TEST" | bash 2>$err_bash >$out_bash
	bash_exit="$?"

	printf "\n\e[36m[$TEST];\e[0m\n"

	if (diff $out_mini $out_bash > /dev/null); then
		printf "Output: \e[32m✔\e[0m\n"
	else
	{
		((WRONG++))
		printf "Output: \e[31m✘\e[0m\n"
		print_diff $out_mini $out_bash
	}
	fi

	test1=$(tail -c 10 $err_mini)
	test2=$(tail -c 10 $err_bash)
	# printf "[$test1]\n[$test2]\n"
	if [ "$test1" = "$test2" ]; then
		printf "Error:  \e[32m✔\e[0m\n"
	else
	{
		((WRONG++))
		printf "Error:  \e[31m?\e[0m\n"
		print_diff $err_mini $err_bash
	}
	fi

	if [ "$mini_exit" -eq "$bash_exit" ]; then
		printf "Exit:   \e[32m✔\e[0m\n"
	else
	{
		((WRONG++))
		printf "Exit:   \e[31m✘\e[0m\n"
		printf "mini_output: $mini_exit\nbash_output: $bash_exit\n"
	}
	fi
	sleep 0.5
	#printf "[$TEST]:\nOutput: $output_result\nError  : $error_result\nExit   : $exit_result\n\n"
}

compare_syntax () {
	echo -n "$1" | .././minishell 2>$err_mini
	mini_exit="$?"
	echo -n "$1" | bash 2>$err_bash
	bash_exit="$?"
	mini_syn=$(head -n 1 $err_mini)
	bash_syn=$(head -n 1 $err_bash)
	printf "\n\e[36m[$1];\e[0m\n$mini_syn\n$bash_syn\n"
	if [ "$mini_exit" -eq "$bash_exit" ]; then
		printf "Exit:   \e[32m✔\e[0m\n"
	else
	{
		((WRONG++))
		printf "Exit:   \e[31m✘\e[0m\n"
		printf "mini_output: $mini_exit\nbash_output: $bash_exit\n"
	}
	fi
	sleep 0.2
	#printf "[$bash_syn]\n"
}

printf "\n\e[32mtesting syntax errors\e[0m\n"
compare_syntax "hello < |"
compare_syntax "< >"
compare_syntax "<< >>"
compare_syntax "< |"
compare_syntax "> |"
compare_syntax ") ()"
compare_syntax "| |"
compare_syntax ">>>"
compare_syntax "(| |)"

printf "\n\e[32mtesting empty input\e[0m\n"
sleep 1
compare_syntax ""
compare_syntax "	"
compare_syntax "'"
compare_syntax "\""
compare_syntax "\"\""


printf "\n\e[32mtesting basic commands\e[0m\n"
sleep 1
compare_command "ls -lah"
compare_command "cat ../Makefile"
compare_command "cat NONEXISTINNGFILE.c"
compare_command "echo "HEY" > cat"
compare_command "cd NONEXISTINGPATH"
compare_command "echo hey | echo hey | ls"
compare_command "ls -S"
compare_command "exit 92"


printf "\n\e[32mtesting redirects\e[0m\n"
sleep 1
compare_command "ls > test > test1 < test2 > test 3"
compare_command "echo >> test.sh"
compare_command "echo >> NONEXISTINGFILE"
compare_command "ls >> lol "
compare_command "echo < test.sh < test.sh < test.sh < test.sh"

printf "\n\e[32mtesting pipes\e[0m\n"
compare_command "ls | ls | ls | ls"
compare_command "echo \"hey\" | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat"
compare_command "ls | cat | cat | echo"
compare_command "echo \"hey\" | ls"
compare_command "echo \"hey\" | ls | cat | wc -l"

printf "\n\e[32mextra tests liath:\e[0m\n"
compare_syntax "echo bonjour | |"
compare_syntax "|"
compare_syntax "echo >	"
compare_command "echo -n -n -nnnn -nnnnm"
compare_command "cat /dev/random | head -n 1 | cat -e"
compare_command "unset var1"
compare_command "export \"\""
compare_command "unset \"\""
compare_command "$"
compare_command "not_cmd bonjour > salut"
compare_command "cat Makefile | grep pr | head -n 5 | cat test "
compare_command "cat Makefile | grep pr | head -n 5 | hello"
compare_syntax "echo bonjour >>> test"
compare_syntax "echo bonjour > > out"
compare_command "echo bonjour > \$test "
compare_command "file_name_in_current_dir"
compare_command "cd ../../../../../.."
compare_command "pwd"
compare_syntax "coyotte > < \" \""
compare_command "cat | cat | cat | ls "
compare_command "\$bla "
compare_command "export var ="cat Makefile | grep >""
compare_command "export "test=ici"=coucou"
compare_command "c\$var Makefile "
compare_command "\$LESS\$VAR"
compare_command "/bin/echo bonjour"
compare_command "not_cmd"
compare_command "minishell "
compare_command "cat diufosgid "
compare_command "cd"
compare_command "cd ."
compare_command "cd /"
compare_command "pwd a"
compare_command "pwd a b c d"
compare_command "export LOL=lala ROR=rara"
compare_command "unset LOL ROR"
compare_command "export \"HI= hi\""
compare_command "export \"HI =hi\""
compare_command "/bin/ls"
compare_command "l^Ds"
compare_syntax "| echo"
compare_command "sort | ls "
compare_syntax "cat < >"
compare_syntax "cat < <"
compare_syntax "cat > >"
compare_syntax "cat > <"
compare_command "echo \$?"
compare_command "echo \"sr\*\""
compare_command "echo abc"
compare_command "echo \"xyz\""
compare_command "echo \"xyz\"'123'"
compare_command "echo a\"x\"y\"z\"a        ijk"
compare_command "echo '123'"
compare_command "echo xyz'123'xyz"
compare_command "echo 'x'\$HOME'x'"
compare_command "echo 'x'~'x'"
compare_command "echo"
compare_command "echo '\"/home/araiva\"'"
compare_command "echo \"'/home/araiva'\""
compare_command "echo 0"
compare_command "echo abc\$HOME"
compare_command "echo abc\$HOMEde"
compare_command "echo \"abc\$HOMEde\""
compare_command "echo 'abc\$HOMEde'"
compare_command "echo abc0de"
compare_command "echo \"abc0de\""
compare_command "echo 'abc0de'"
compare_command "echo \"10\"\"20\"\"30\""
compare_command "echo \"10\"20\"30\""
compare_command "echo '10''20''30'"
compare_command "echo '10'20'30'"
compare_command "echo 10\"20\"'30'"
compare_command "echo 10\"20     \"'30     '"
compare_command "echo 10 \"20     \"'30     '"
compare_command "echo 10    \"20     \"'30     '"
compare_command "echo 10    \"20     \" '30     '"
compare_command "echo 10    \"20     \"     '30     '"
compare_command "echo \"\$HOME\" '\$HOME'"
compare_command "echo fin"
compare_command "echo test > file test1"
compare_command "echo 2 >> out1 > out2"
compare_command "echo 2 > out1 >> out2"
compare_command "echo bonjour > \$test		"
compare_command "echo \$HOME"
compare_command "echo \"\$HOME\""
compare_command "echo '\$HOME'"
compare_syntax "echo hudifg d | | hugdfihd"
compare_command "echo"
compare_command "echo simple"
compare_command "echo -n simple"
compare_command "echo ''"
compare_command "echo \"\""
compare_command "echo \"\n \n \n\""
compare_command "echo x > redirect1 | echo"
compare_command "cat redirect1"
compare_command "rm redirect1 | echo"
compare_command "> log echo coucou"
compare_command "> a ls > b < Makefile"
compare_command "echo > a Hello World!"
compare_command "> a echo Hello World!"
compare_command "cat < Makefile | grep gcc > output"
compare_command "Documents/github/minishell_2"
compare_command "\"\""
compare_syntax ">>>"
compare_syntax "<<<"
compare_command "cd \$HOME/Documents"
compare_command "cat Makefile | grep pr | head -n 5 | cd test "
compare_command "cat < test "
compare_command "cd no_file"
compare_command "cd a b c d"
compare_command "sleep 5 | > \$BLABLABLALALAL"
compare_command "ls |> hoi"

compare_command "echo \$USERS"
compare_command "echo \"\$USERS\""
compare_command "echo '\$USERS'"
compare_syntax "\$USERS"
compare_syntax "\"\$USERS\""
compare_syntax "'\$USERS'"

# # wrong:
# printf "\n\e[32mWRONG tests:\e[0m\n"
# compare_syntax ") ()"
# compare_syntax "	"
# compare_command "cat /dev/random | head -n 1 | cat -e"
# compare_command "rm redirect1 | echo"




rm -rf ~/bullshit
rm lol 2> /dev/null
rm cat 2> /dev/null
rm test 2> /dev/null
rm NONEXISTINGFILE 2> /dev/null
rm test1 2> /dev/null
rm a 2> /dev/null
rm b 2> /dev/null
rm file 2> /dev/null
rm log 2> /dev/null
rm out1 2> /dev/null
rm out2 2> /dev/null
rm output 2> /dev/null
rm salut 2> /dev/null
rm hoi 2> /dev/null

if [ "$WRONG" -eq 0 ]; then
	printf "\nALL TESTS PASSED\n"
else
	printf "\nTEST FAILED ON "$WRONG" MISTAKES!\n"
fi

# # $OLDPWD leaks

































