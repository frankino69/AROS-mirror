# $Date: 2011-07-16 19:39:22 +0200 (Sa, 16. Jul 2011) $
# $Revision: 787 $
##############################################################################

include $(TOPLEVEL)/config.mk
include $(TOPLEVEL)/rules.mk

##############################################################################

SCALOS_LOCALE	= $(OBJDIR)/Delete_Locale.h

CFLAGS += -D SCALOSLOCALE=$(SCALOS_LOCALE)

##############################################################################
# Check gcc

ifeq ($(MACHINE), ppc-morphos)

###############################################################################
# MorphOS

INCLUDES	+= 	#

LFLAGS	+=	#


else
ifeq ($(MACHINE), ppc-amigaos)

###############################################################################
# AmigaOS4

INCLUDES	+= 	#

LFLAGS	+=	#


else
ifeq ($(MACHINE), i386-aros)

###############################################################################
# i386-aros

INCLUDES	+= 	-DMUI_OBSOLETE

LFLAGS	+=	-lmui -larossupport -lintuition

else

###############################################################################
# AmigaOS

INCLUDES	+= 	#

LFLAGS	+=	-lauto

endif
endif
endif
