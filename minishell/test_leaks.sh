#!/bin/bash

BIN=./bin/minishell
SUPP_FILE=./valgrind.supp
LOG_FILE=leaks_report.txt

COMMANDS=(
    "echo hello"
    "pwd"
    "export VAR=test"
    "echo \$VAR"
    "unset VAR"
    "env"
    "cd .."
    "echo test > out.txt"
    "cat < out.txt"
    "ls | wc"
    "cat << EOF\nHello\nEOF"
    "invalidcommand"
    "echo \$?"
    "exit"
    "cd doesnotexist"
    "export VAR=1 VAR2=2"
    "ls | cat | grap ."
)

echo "Running valgrind leak tests..." > "$LOG_FILE"
echo "------------------------------------" >> "$LOG_FILE"

for cmd in "${COMMANDS[@]}"; do
    echo "--- Testing: $cmd ---" | tee -a "$LOG_FILE"

    echo -e "$cmd\nexit" | valgrind \
        --leak-check=full \
        --show-leak-kinds=all \
        --track-origins=yes \
        --suppressions="$SUPP_FILE" \
        "$BIN" 2>&1 | tee -a "$LOG_FILE"

    echo -e "\n-------------------------------\n" >> "$LOG_FILE"
done

echo "✅ Test terminé. Résultats dans $LOG_FILE"
