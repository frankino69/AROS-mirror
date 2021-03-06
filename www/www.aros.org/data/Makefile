
BASEDIR=$(shell cd .. ; pwd)
-include .Makefile.inc

# Tools
SED = sed
RM = rm -f
CP = cp
NOP = true # A command which does nothing
ALLOW_READ = chmod -R a+rX,go-w
MKDIR = mkdir -p

# Collect files
DEVPICS := $(subst $(BINDIR)/developers/,$(HTMLDIR)/pics/developers/,$(wildcard $(BINDIR)/developers/*.*))
SCREENSHOTS := $(subst $(BINDIR)/screenshots/,$(SCREENSHOTDIR)/,$(wildcard $(BINDIR)/screenshots/*.* $(BINDIR)/screenshots/[0-9]*/*.* $(BINDIR)/screenshots/[0-9]*/README))
SCREENSHOTDIRS := $(subst $(BINDIR)/screenshots/,$(SCREENSHOTDIR)/,$(wildcard $(BINDIR)/screenshots/[0-9]*))

all : setup makedirs pics gen-html apache.conf
	@$(NOP)

setup : config.py

# Run gensite if .stamp is missing or if one of the source files
# is newer.
gen-html : config.py
	python gensite

apache.conf : genconf apache.conf.in site.conf
	./genconf apache.conf.in $@
	@echo "Please read the instructions at the beginning of apache.conf"
	@echo "to change the config of Apache accordingly."

site.conf : site.conf.in
	@if [ ! -f "$@" ]; then \
	    echo "Copy site.conf.in to site.conf and modify site.conf" ; \
	    echo "to suit your setup." ; \
	else \
	    echo "site.conf.in has changed. Please update site.conf." ; \
	fi
	@exit 1

ifdef GNUPLOT
pics : config.py $(HTMLDIR)/aros_size.png $(HTMLDIR)/contrib_size.png $(DEVPICS) $(SCREENSHOTS)

$(HTMLDIR)/%_size.png : %.size size2plot.py
	python size2plot.py $(subst _size.png,,$@) $<
ifdef CONVERT
	$(CONVERT) $@ $(basename $@).jpg
	$(CONVERT) $(subst _size.png,_allsize.png,$@) $(subst _size.png,_allsize.jpg,$@)
endif
else
pics :
	@$(NOP)
endif

makedirs :
	@$(MKDIR) $(HTMLDIR)/pics/developers $(HTMLDIR)/pics/screenshots \
	    $(SCREENSHOTDIRS)

$(HTMLDIR)/pics/developers/% : $(BINDIR)/developers/%
	$(CP) $< $@
	$(ALLOW_READ) $@

$(HTMLDIR)/pics/screenshots/% : $(BINDIR)/screenshots/%
	$(CP) $< $@
	$(ALLOW_READ) $@

compileall:
	@python -c "import compileall; compileall.compile_dir('.',0)"

clean :
	$(RM) size2plot.gp $(HTMLDIR)/plot.pbm apache.conf.in \
	    *.pyc .Makefile.inc config.py

.Makefile.inc : site.conf
	$(SED) -e 's;\$$\([a-zA-Z_]*\);$$(\1);' site.conf > $@

config.py : site.conf
	$(SED) -e 's;\([a-zA-Z_]*=\)\(.*$$\);\1"\2";' site.conf > $@

lxr :
	echo $(BASEDIR)
	$(RM) -rf $(BASEDIR)/lxr/source
	$(MKDIR) $(BASEDIR)/lxr/source/include
	$(CP) -r $(AROSDIR)/bin/*/AROS/Include/* $(BASEDIR)/lxr/source/include/
	$(CP) -r $(AROSDIR)/config $(AROSDIR)/rom $(AROSDIR)/workbench \
		$(BASEDIR)/lxr/source
	$(ALLOW_READ) $(BASEDIR)/lxr/source
	find $(BASEDIR)/lxr/source -name CVS -prune -exec $(RM) -rf "{}" \;
	cd $(BASEDIR)/lxr ; ./bin/genxref $(BASEDIR)/lxr/source
	$(ALLOW_READ) $(BASEDIR)/lxr/fileidx $(BASEDIR)/lxr/xref
