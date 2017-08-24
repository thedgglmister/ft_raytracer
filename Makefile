NAME = rt

SRCDIR = srcs

OBJDIR = objs

LIBDIR = libs

INCLUDESDIR = includes

SRCS = $(wildcard $(SRCDIR)/*.c)

OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

LIBS = -L $(LIBDIR)/minilibx_macos -lmlx -L $(LIBDIR)/libft -lft

INCLUDES = -I $(LIBDIR)/minilibx_macos -I $(LIBDIR)/libft/includes -I $(INCLUDESDIR)

FRAMEWORKS = -framework OpenGL -framework AppKit

all: $(NAME)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c 
	@gcc -Wall -Werror -Wextra -c $< $(INCLUDES) -o $@

$(NAME): $(OBJS)
	@make -C $(LIBDIR)/minilibx_macos
	@make -C $(LIBDIR)/libft
	@gcc $(OBJS) $(LIBS) $(FRAMEWORKS) -o $(NAME)

.PHONY: clean 
clean:
	@make clean -C $(LIBDIR)/minilibx_macos
	@make clean	-C $(LIBDIR)/libft
	@rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	@make fclean -C $(LIBDIR)/minilibx_macos
	@make fclean -C $(LIBDIR)/libft
	@rm -f $(NAME)

.PHONY: re
re: fclean all
