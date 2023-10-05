# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 21:19:38 by jungmiho          #+#    #+#              #
#    Updated: 2023/10/05 22:53:10 by jungmiho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



# 프로그램 이름
NAME = pipex

# 컴파일러 설정
CC = cc
CFLAGS = -Wall -Wextra -Werror

# 디버깅 옵션 추가
ifdef DEBUG
	CFLAGS += -g -O0 -fsanitize=address,undefined
else
	CFLAGS += -O2
endif

# 일반 소스파일
SRCS = ft_split.c libft.c handle_cmd.c handle_exeve.c

# 보너스 활성화 여부에 따라 main 파일 선택
ifdef BONUS
	SRCS += main_bonus.c
else
	SRCS += main.c
endif

# 오브젝트 파일
OBJS = $(SRCS:.c=.o)

# 규칙 정의
.PHONY: all clean fclean re bonus

# 기본 빌드 규칙
all : $(NAME)

# 빌드 규칙
$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# .c에서 .o로 변환
.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

# 오브젝트 파일과 의존성 파일 삭제
clean:
	rm -f $(OBJS)

# 모든 파일 삭제
fclean : clean
	rm -f $(NAME)

# 다시 빌드
re : fclean all

# 보너스 빌드
bonus:
	make BONUS=1 all