#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"

id_buffer::id_buffer(size_t size)
{
	this->buf = new char[size];
	memset(this->buf, 0 , size);
	this->_capacity = size;
	this->_size = 0;
	this->pos = 0;
}

id_buffer::id_buffer(const id_buffer& b)
{
	size_t	j;

	j = 0;
	this->_capacity = b._capacity;
	this->pos = b.pos;
	this->_size = b._size;
	this->buf = new char[b._capacity];
	while (j < b._size)
	{
		this->buf[j] = b.buf[j];
		j ++;
	}
}

id_buffer::id_buffer(const id_buffer* b)
{
	size_t	j;

	j = 0;
	this->_capacity = b->_capacity;
	this->pos = b->pos;
	this->_size = b->_size;
	this->buf = new char[b->_capacity];
	while (j < b->_size)
	{
		this->buf[j] = b->buf[j];
		j ++;
	}
}

id_buffer::~id_buffer()
{
	delete[] this->buf;
}

size_t	id_buffer::buf_recv(int fd, size_t nbread)
{
	int	nb;

	nb = 0;
	if (nbread > 0 && nbread < this->space())
	{
		nb = recv(fd, this->buf + this->_size, nbread , 0);
		if (nb < 0)
			perror("readfile eror:\n");
		this->_size = this->_size + nb;
		return (nb);
	}
	return (0);
}

size_t	id_buffer::buf_readfile(int fd, size_t nbread)
{
	int	nb;

	nb = 0;
	if (nbread > 0 && nbread <= this->space())
	{
		nb = read(fd, this->buf + this->_size, nbread);
		if (nb < 0)
			perror("readfile eror:\n");
		this->_size = this->_size + nb;
		return (nb);
	}
	return (0);
}

size_t	id_buffer::size() const
{
	return (this->_size);
}

size_t	id_buffer::capacity() const
{
	return (this->_capacity);
}

size_t	id_buffer::space() const
{
	return (this->_capacity - this->_size);
}

bool	id_buffer::empty() const
{
	if (this->pos == 0)
		return (true);
	else
		return  (false);
}

bool	id_buffer::full() const
{
	if (this->pos == this->_capacity)
		return (true);
	else
		return  (false);
}

size_t	id_buffer::addstr(char* str, size_t len)
{
	size_t	n_caract_write;
	size_t	i;

	i = 0;
	n_caract_write = 0;
	while (i < len && this->_size + len <= this->_capacity)
	{
		this->buf[this->_size] = str[i];
		n_caract_write = n_caract_write + 1;
		i = i + 1;
		this->_size = this->_size + 1;
	}
	return (n_caract_write);
}

bool	id_buffer::getchar(char* c)
{
	if (this->_size >= 1)
	{
		*c = this->buf[this->_size];
		this->_size = this->_size - 1;
		return (1);
	}
	else
		*c = 0;
	return (0);
}

char	id_buffer::getchar_nv()
{
	char	c;

	c = this->buf[this->_size];
	this->_size = this->_size - 1;
	if (this->_size == 0)
		c = 0;
	return (c);
}

bool	id_buffer::peekchar(char* ptr, size_t index) const
{
	if (this->_size >= 1)
		*ptr = this->buf[index];
	else
		*ptr = 0;
	return (0);
}

char	id_buffer::peekchar_nv(size_t index) const
{
	if (this->_size >= 1)
		return (this->buf[index]);
	else
		return (0);
}

char*	id_buffer::getline()
{
	size_t	i;
	int	j;
	int	k;
	bool	find;
	char*	ptr = new char[_size + 1];

	find = false;
	j = 0;
	i = 0;
	while (i < _size)
	{
		if (buf[i] == '\n' || buf[i] =='\0')
		{
			ptr[i] = buf[i];
			i++;
			ptr[i] = '\0';
			find = true;
			break;
		}
		ptr[i] = this->buf[i];
		i ++;
	}
	if (find)
	{
		k = i;
		while (i < _size)
		{
			buf[j] = buf[i];
			i ++;
			j ++;
		}
		_size = _size - k;
		buf[j] = '\0';
		return (ptr);
	}
	else
	{
		delete[] ptr;
		return (0);
	}
}

char*	id_buffer::peekline(size_t index) const
{
	size_t	i;
	int	j;
	bool	find;
	char*	ptr = new char[this->_size + 1];
 
	find = false;
	i = index;
	j = 0;
	while (i <= this->_size)
	{
		if (this->buf[i] == '\n' || this->buf[i] == '\0')
		{
			find = true;
			break;
		}
		ptr[j] = this->buf[i];
		i ++;
		j ++;
	}
	if (find)
		return (ptr);
	else
	{
		delete[] ptr;
		return (0);
	}
}

char*	id_buffer::flush()
{
	size_t	i;
	char*	ptr = new char[this->_size];

	i = 0;
	while (i < this->_size)
	{
		ptr[i] = this->buf[i];
		i ++;
	}
	this->pos = 0;
	this->_size = 0;
	return (ptr);
}

void	id_buffer::clear()
{
	this->pos = 0;
	this->_size = 0;
}

id_buffer*	id_buffer::clone()
{
	size_t	i;
	i = 0;

	id_buffer* new_buf = new id_buffer(this->_capacity);
	while (i <= this->pos)
	{
		new_buf->buf[i] = this->buf[i];
		i = i + 1;
	}
	new_buf->pos = this->pos;
	new_buf->_size = this->_size;
	return (new_buf);
}

void	id_buffer::swap(id_buffer* right)
{
	char*	tmpbuf;
	size_t	tmptaille_t;
	size_t	tmptaille_s;
	size_t	tmppos;

	tmpbuf = this->buf;
	tmptaille_t = this->_capacity;
	tmptaille_s = this->_size;
	tmppos = this->pos;
	this->pos = right->pos;
	this->buf = right->buf;
	this->_capacity = right->_capacity;
	this->_size = right->_size;
	right->buf = tmpbuf;
	right->pos = tmppos;
	right->_capacity = tmptaille_t;
	right->_size = tmptaille_s;
}

size_t	id_buffer::getpos() const
{
	return (this->pos);
}
