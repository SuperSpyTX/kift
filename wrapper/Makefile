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

# ------------- Automated Configuration ------------- #
CFLAGS =   -Wall -Werror -Wextra
SPHINX_WRAPPER_NAME = sphinx-wrapper.dylib
CFLAGS += -I includes -I sphinxbase/include -I sphinxbase/include/pocketsphinx -I sphinxbase/include/sphinxbase
SPHINX_WRAPPER_SRC = src/wrapper.c \

SPHINX_WRAPPER_OBJ = $(subst .c,.o, $(SPHINX_WRAPPER_SRC))

# ------------------- Targets ----------------------- #

all: sphinxbase corpus $(SPHINX_WRAPPER_NAME)

%.o: %.c
	gcc $(CFLAGS) -c $? -o $@

$(SPHINX_WRAPPER_NAME): $(SPHINX_WRAPPER_OBJ)
	gcc $(CFLAGS) -Lsphinxbase/lib -lpocketsphinx -lsphinxbase -lsphinxad -dynamiclib $(SPHINX_WRAPPER_OBJ) -o $(SPHINX_WRAPPER_NAME)

sphinxbase:
	tar -zxf pocketsphinx-5prealpha.tar.gz
	tar -zxf sphinxbase-5prealpha.tar.gz
	cd ./sphinxbase-5prealpha && ./autogen.sh --prefix=$$(echo $(PWD)/sphinxbase) && make && make install
	cd ./pocketsphinx-5prealpha && ./autogen.sh --prefix=$$(echo $(PWD)/sphinxbase) && make && make install
	rm -rf sphinxbase-5prealpha && rm -rf pocketsphinx-5prealpha

corpus: corpus.txt
	@bash corpus-update.sh

re: fclean all 
clean:
	/bin/rm -f $(SPHINX_WRAPPER_OBJ)

fclean: clean
	/bin/rm -f $(SPHINX_WRAPPER_NAME)
	/bin/rm -rf corpus
