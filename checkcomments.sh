#!/bin/bash
Out="./annotations.markdown"
echo -e "Annotations\n==" > "${Out}"

for f in `grep -Rl --exclude="annotations*" \/\/[A-Z]*:`
do
	echo -e "\n$f\n--\n" >> "${Out}"
	echo -e "\`\`\`" >> "${Out}"
	grep -nT -A 3 \/\/[A-Z]*: $f >> "${Out}"
	echo -e "\`\`\`" >> "${Out}"
done

