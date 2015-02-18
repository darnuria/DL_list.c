NAME = libdl_list.a
SRCDIR = ./
OBJDIR = ./obj
LDFLAGS =
SRC = DL_list.c
INCDIR = -I./
CFLAGS = -W -Wall -Wextra -Werror -pedantic -pedantic-errors -std=c11

ifeq ($(RELEASE),yes)
	CC = gcc
	CFLAGS += -O3
else
	CC = clang
	CFLAGS += -ggdb -g3 -fstack-protector-all -Wshadow -Wunreachable-code \
			  -Wstack-protector -pedantic-errors -O0 -W -Wundef \
			  -Wfatal-errors -Wstrict-prototypes -Wmissing-prototypes \
			  -Wwrite-strings -Wunknown-pragmas \
			  -Wold-style-definition -Wfloat-equal \
			  -Wpointer-arith -Wnested-externs -Wstrict-overflow=5 \
			  -Wno-missing-field-initializers -Wswitch-default -Wswitch-enum \
			  -Wbad-function-cast -Wredundant-decls
endif

OBJS = $(SRC:.c=.o)
OBJS_PREF = $(addprefix $(OBJDIR)/, $(OBJS))
LD = $(CC)

all: objdir $(NAME)

objdir:
	@mkdir -p $(OBJDIR)

build_dep:
	make re ${ARGS}-C my_stdext

$(NAME): $(OBJS_PREF)
	echo "Linking $@."
	ar rcs $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	echo "Compiling $@ into $<"
	$(CC) $(CFLAGS) $(INCDIR) -o $@ -c $<

test: all
	gcc $(CFLAGS) -I. -o run_test test.c libdl_list.a

clean:
	rm -f $(OBJS_PREF)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all

