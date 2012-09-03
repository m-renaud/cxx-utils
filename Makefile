# Makefile to be for installing header files to appropriate directories
# $(DESTDIR) is used by Gentoo ebuild system

NAME=cxx-utils
VERSION=0.4
INSTALL_DIR=usr/local/include/mrr/

all: package

install:
	mkdir -p $(DESTDIR)/$(INSTALL_DIR)
	(find . -name '*.hxx' -print | tar --create --files-from -) | (cd $(DESTDIR)/$(INSTALL_DIR) && tar xvfp -)
#	rsync -avR --include=*.hxx --exclude=* * */* $(DESTDIR)/$(INSTALL_DIR)

package:
	rm -f ../$(NAME)-$(VERSION).tar.gz
	tar cvzf ../$(NAME)-$(VERSION).tar.gz -C ../ $(NAME)/
