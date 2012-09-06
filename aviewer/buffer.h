#ifndef __ID_BUF_H__
#define __ID_BUF_H__
#include <unistd.h>

class	id_buffer
{
	public:
		id_buffer(size_t);
		id_buffer(const id_buffer& x);
		id_buffer(const id_buffer* x);
		~id_buffer();
		size_t	check_size(size_t nbread);
		size_t	buf_recv(int fd, size_t nbread);
		size_t	size() const;
		size_t	capacity() const;
		size_t	space() const;
		size_t	addstr(char* str, size_t len);
		bool	empty() const;
		bool	full() const;
		bool	getchar(char* ptr);
		bool	peekchar(char* ptr, size_t index) const;
		char	getchar_nv();
		char	peekchar_nv(size_t index) const;
		char*	getline();
		char*	peekline(size_t index) const;
		char*	flush();
		void	clear();
		void	swap(id_buffer* right);
		id_buffer*	clone();
		size_t	buf_readfile(int fd, size_t nbread);
		size_t	getpos() const;
	private:
		char*	buf;
		size_t	_capacity;
		size_t	_size;
		size_t	pos;
};
#endif
