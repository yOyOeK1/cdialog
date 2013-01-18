
fLook="$1"


echo "/* file: [ $fLook ] */"

bat "$fLook" | \
	grep -e "^cn" -e "^cm" -e "^struct" -e "^void" -e "^bool" -e "^long" -e "^int" -e "^char" | \
	grep -v 'int main' | grep -v "^ " | grep -v "^	" | grep -v "^\n" | grep '){' | tr '{' ';' | \
	bat --style=plain --language c
