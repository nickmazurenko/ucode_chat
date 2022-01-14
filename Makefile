# NAME = send_image_client
# # CFLAGS = -std=c11 $(addprefix -W, all extra error pedantic) -g
# CFLAGS = -std=c11 -g
# COMP = clang

# SRCDIR = src
# INCDIR = inc
# OBJDIR = obj




# INCS = $(wildcard $(INCDIR)/*.h)
# SRCS = $(wildcard $(SRCDIR)/*.c)
# OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:%.c=%.o)))

# all: install

# install: $(LMXA) $(NAME)

# $(NAME): $(OBJS)
# 	@clang $(CFLAGS) $(OBJS) -L$(LMXDIR) -lmx -o $@

# $(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCS)
# 	@clang $(CFLAGS) -c $< -o $@ -I$(INCDIR) -I$(LMXINC)

# $(OBJS): | $(OBJDIR)

# $(OBJDIR):
# 		@mkdir -p $@

# $(LMXA):
# 		@make -sC $(LMXDIR)

# clean:
# 	@rm -rf $(OBJDIR)

# uninstall: clean
# 	@make -sC $(LMXDIR) $@
# 	@rm -rf $(OBJDIR)
# 	@rm -rf $(NAME)

# reinstall: uninstall install


LMXDIR = libmx
LMXA := $(LMXDIR)/libmx.a

MODELDIR = model
MODELA  := $(MODELDIR)/libmodel.a

NETWORKDIR = network
NETWORKA  := $(NETTWORKDIR)/libnetwork.a

CJSONDIR  = cjson
CJSONA   := $(CJSONDIR)/libcjson.a

SERVERDIR = server
SERVER = uchat_server

CLIENTDIR = client
CLIENT = uchat

all: install

install:
		if [ -f $(LMXA) ]; then echo "libmx exists" ; else make -sC $(LMXDIR); fi
		@make -sC $(NETWORKDIR) reinstall
		@make -sC $(MODELDIR)   reinstall
		@make -sC $(CJSONDIR)
		@make -sC $(SERVERDIR)
		@make -sC $(CLIENTDIR)
		
#model and protocol

$(LMXA):
		@make -sC $(LMXDIR)

$(SERVER):
		@make -sC $(SERVERDIR)

$(CLIENT):
		@make -sC $(CLIENTDIR)

uninstall:
	@make -sC $(CLIENTDIR) $@
	@make -sC $(SERVERDIR) $@
	@make -sC $(LMXDIR) $@
	@make -sC $(NETWORKDIR) $@
	@make -sC $(MODELDIR) $@
	@make -sC $(CJSONDIR) $@


reinstall: uninstall install
