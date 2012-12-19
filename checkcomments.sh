#!/bin/bash
Out="./annotations.textile"
echo -e "h1. Annotations" > "${Out}"

for f in `grep -Rl --exclude="annotations*" \/\/[A-Z]*:`
do
	echo -e "\nh2. $f\n" >> "${Out}"
	echo -e "\`\`\`" >> "${Out}"
	grep -nT -A 3 \/\/[A-Z]*: $f >> "${Out}"
	echo -e "\`\`\`" >> "${Out}"
done

