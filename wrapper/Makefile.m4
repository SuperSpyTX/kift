#* ************************************************************************** */
#*                                                                            */
#*                                                        :::      ::::::::   */
#*   Makefile                                           :+:      :+:    :+:   */
#*                                                    +:+ +:+         +:+     */
#*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
#*                                                +#+#+#+#+#+   +#+           */
#*   Created: 2017/04/18 03:42:42 by jkrause           #+#    #+#             */
#*   Updated: 2017/06/11 02:45:14 by jkrause          ###   ########.fr       */
#*                                                                            */
#* ************************************************************************** */
# ----------------- Version 1.5.1 ------------------- #
divert(-1)

# ------------- Real Configuration ------------------ #
define(MK_NUM_OF_TARGETS, 1)
define(MK_FCLEAN_ON_RE, 1)
define(MK_DEBUG, 0)

define(MK_SPHINX_WRAPPER_NAME, sphinx-wrapper)
define(MK_SPHINX_WRAPPER_ISLIB, 1)
define(MK_SPHINX_WRAPPER_INCLUDE_DIRS, includes sphinxbase/include sphinxbase/include/pocketsphinx sphinxbase/include/sphinxbase)
define(MK_SPHINX_WRAPPER_SRC_DIRS, src )
define(MK_SPHINX_WRAPPER_DEBUG, 0)
define(MK_SPHINX_WRAPPER_LITE, 0)

# ------------ Automated Variables ------------------ #
define(MK_AUTO_ISLINUX, ifelse(esyscmd(uname -s | tr -d '\n'), `Darwin', 0, 1))
define(MK_AUTO_COMPILER,ifelse(MK_AUTO_ISLINUX, 1, clang, gcc))

define(MK_SPHINX_WRAPPER_AUTO_SRC_DIR, patsubst(MK_SPHINX_WRAPPER_SRC_DIRS,` ',`````,'''''))
pushdef(`MK_SPHINX_WRAPPER_AUTO_SRC_DIR', ifelse(MK_SPHINX_WRAPPER_SRC_DIRS,.,.,{MK_SPHINX_WRAPPER_AUTO_SRC_DIR}))
define(MK_SPHINX_WRAPPER_AUTO_SRC, esyscmd(sh -c 'find MK_SPHINX_WRAPPER_AUTO_SRC_DIR -type f -name "*.c" | sed -e "s/$/ \\\/g"'))
define(MK_SPHINX_WRAPPER_AUTO_SRC_DIR, patsubst(MK_SPHINX_WRAPPER_SRC_DIRS,` ',```,'''))
define(MK_SPHINX_WRAPPER_AUTO_INCLUDE_DIR, -I patsubst(MK_SPHINX_WRAPPER_INCLUDE_DIRS,` ',``` -I '''))

divert(0)
# ------------- Automated Configuration ------------- #
CFLAGS = ifelse(MK_DEBUG, 1,-g) ifelse(MK_AUTO_ISLINUX,1,-fPIC) -Wall -Werror -Wextra
SPHINX_WRAPPER_NAME = ifelse(MK_SPHINX_WRAPPER_ISLIB, 1, MK_SPHINX_WRAPPER_NAME.dylib, MK_SPHINX_WRAPPER_NAME)
CFLAGS += MK_SPHINX_WRAPPER_AUTO_INCLUDE_DIR
SPHINX_WRAPPER_SRC = MK_SPHINX_WRAPPER_AUTO_SRC
SPHINX_WRAPPER_OBJ = $(subst .c,.o, $(SPHINX_WRAPPER_SRC))

# ------------------- Targets ----------------------- #

all: sphinxbase corpus $(SPHINX_WRAPPER_NAME)

%.o: %.c
	MK_AUTO_COMPILER $(CFLAGS) -c $? -o $@

$(SPHINX_WRAPPER_NAME): $(SPHINX_WRAPPER_OBJ)
	MK_AUTO_COMPILER $(CFLAGS) -Lsphinxbase/lib -lpocketsphinx -lsphinxbase -lsphinxad -dynamiclib $(SPHINX_WRAPPER_OBJ) -o $(SPHINX_WRAPPER_NAME)

sphinxbase:
	tar -zxf pocketsphinx-5prealpha.tar.gz
	tar -zxf sphinxbase-5prealpha.tar.gz
	cd ./sphinxbase-5prealpha && ./autogen.sh --prefix=$$(echo $(PWD)/sphinxbase) && make && make install
	cd ./pocketsphinx-5prealpha && ./autogen.sh --prefix=$$(echo $(PWD)/sphinxbase) && make && make install
	rm -rf sphinxbase-5prealpha && rm -rf pocketsphinx-5prealpha

corpus: corpus.txt
	@bash corpus-update.sh

re: ifelse(MK_FCLEAN_ON_RE, 1,f)clean all dnl

clean:
	/bin/rm -f $(SPHINX_WRAPPER_OBJ)

fclean: clean
	/bin/rm -f $(SPHINX_WRAPPER_NAME)
	/bin/rm -rf corpus
