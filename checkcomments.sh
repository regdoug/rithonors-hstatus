#!/bin/bash
Out="./annotations.textile"
echo -e "h1. Annotations" > "${Out}"

for f in `grep -Rl \/\/[A-Z]*:`
do
	echo -e "h2. $f" >> "${Out}"
	echo -e "\`\`\`php" >> "${Out}"
	grep -nT -A 3 \/\/[A-Z]*: $f >> "${Out}"
	echo -e "\`\`\`" >> "${Out}"
done

