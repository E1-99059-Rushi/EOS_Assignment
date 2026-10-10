read -p "Enter the first (source) file name: " file1
read -p "Enter the second (destination) file name: " file2

if [ ! -f "$file1" ]; then
    echo "Error: Source file '$file1' does not exist."
    exit 1
fi

tr 'a-zA-Z' 'A-Za-z' < "$file1" >> "$file2"

echo "Success: Reversed case contents of '$file1' appended to '$file2'."

