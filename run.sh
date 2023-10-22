
g++ -o t tictactoe.c

if [ -f tictactoe_log.txt ]; then
    rm tictactoe_log.txt
    echo "Log file removed"
else
    echo "Log file not found"
fi

for i in {1..20}; do
    echo "Running program - Iteration $i"
    ./t
done