#!/bin/bash
# Corpus updater using CMU LMTool
# http://www.speech.cs.cmu.edu/tools/lmtool-new.html
# Requires cURL (sorry logan)

echo -e "[*] Sending corpus to LMTool..."
URL1=$(curl -X POST -vF 'corpus=@corpus.txt' -F 'formtype=simple' http://www.speech.cs.cmu.edu/cgi-bin/tools/lmtool/run 2>&1 | grep -E "^< Location: " | sed -e 's/^< Location: //g')
URL1=${URL1%$'\r'}
echo -e "[*] Retrieving results..."
URL2=$(curl -L $URL1 2>/dev/null | grep -oE '<a href="http://www.speech.cs.cmu.edu/tools/product/(.+)\.tgz">' | grep -oE '"(.+)"' | sed -e 's/"//g');
curl $URL2 2>/dev/null > corpus.tgz
echo -e "[*] Rebuilding model_v2 directory...";
rm -rf model_v2; mkdir model_v2;
echo -e "[*] Extracting archive..."
mv corpus.tgz model_v2; cd model_v2; tar -zxvf corpus.tgz >/dev/null 2>&1;
mv *.lm corpus.lm; mv *.dic corpus.dic; mv *.vocab corpus.vocab;
echo -e "[*] Compiling language model..."
../sphinxbase/bin/sphinx_lm_convert -i corpus.lm -o corpus.lm.bin 2>/dev/null >/dev/null;
echo -e "[*] Updated successfully"
