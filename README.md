# kift
The jkrause elite team for voice based command and control center.

## Building PocketSphinx

To build the pocketsphinx wrapper, simply run make in the wrapper/ directory.

It should auto compile assuming the following Homebrew dependencies are installed (incomplete):

- automake
- autoconf
- swig

Please help me by finding all the missing Homebrew dependencies.

## Building Corpus for PocketSphinx

Run `make -C wrapper/ corpus` to update/create the corpus.  It will only rebuild if you change the corpus.txt file.

The corpus.txt data is ours to update and change as see fit for the building tool.

The tool uses [LMTool](http://www.speech.cs.cmu.edu/tools/lmtool-new.html) to build the language model and dictionary data.
