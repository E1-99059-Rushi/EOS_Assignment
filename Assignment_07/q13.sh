echo "Displaying only hidden files in the current directory:"
ls -d .* 2>/dev/null | grep -v -E '^\.$|^\.\.$'

