/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exeve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:52:02 by jungmiho          #+#    #+#             */
/*   Updated: 2023/10/05 22:52:17 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execve_first_cmd(int *pipe_fd, char *path, char **cmd, char *file)
{
	int	infile_fd;  // 변경된 변수명

	close(pipe_fd[READ]);		// 읽기용 파이프 닫기
	dup2(pipe_fd[WRITE], STDOUT_FILENO);	// 쓰기용 파이프를 표준 출력에 복사
	close(pipe_fd[WRITE]);		// 원본 쓰기용 파이프 닫기

	infile_fd = open(file, O_RDONLY);  // 입력 파일을 읽기 전용으로 열기
	if (infile_fd == -1)  // 파일 열기 실패 시
	{
		perror("open");
		exit(1);  // 프로그램 종료
	}
	dup2(infile_fd, STDIN_FILENO);  // 입력 파일 디스크립터를 표준 입력에 복사  // 인파일의 내용을 읽는다! 표준 입력이 아니라!
	close(infile_fd);  // 원본 입력 파일 디스크립터 닫기
	if (execve(path, cmd, NULL) == -1)
	{
		perror("execve");
		exit(1);
	}
}

void	execve_second_cmd(int *pipe_fd, char *path, char **cmd, char *outfile)
{
	int	out_fd;

	close(pipe_fd[WRITE]);	// 쓰기용 파이프를 닫는다.
	out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd == -1)  // 파일 열기에 실패하면
	{
		exit(1);  // 프로그램을 종료한다.
	}
	dup2(out_fd, STDOUT_FILENO);  // 출력 파일 디스크립터를 표준 출력에 복사한다.
	close(out_fd);  // 출력 파일 디스크립터를 닫는다.

	dup2(pipe_fd[READ], STDIN_FILENO);  // 읽기용 파이프를 표준 입력에 복사한다.
	close(pipe_fd[READ]);  // 원본 읽기용 파이프를 닫는다.

	//execve(path, cmd, NULL);  // 새로운 프로세스를 실행한다.
	if (execve(path, cmd, NULL) == -1)
	{
		perror("execve");
		exit(1);  // 실패 시 오류 메시지 출력 후 종료
	}
}