
fLook="$1"


echo "
/* auto header for [ $fLook ] */
"

bat "$fLook" | \
	grep -e "^struct" -e "^void" -e "^int" -e "^char" | \
	grep -v 'int main' | grep '){' | tr '{' ';' | \
	bat --style=plain --language c
echo "
"
