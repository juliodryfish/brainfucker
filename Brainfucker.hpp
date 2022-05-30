#pragma once
#include <iostream>
#include <iomanip>
#include <stack>

#include <Windows.h>


class Brainfucker {
public:
	using value_type	= char;
	using pointer		= value_type*;
	using cv_pointer		= const value_type*;
public:
	
	static auto run(const char* input) -> void {
		if (not input) return;
		Brainfucker::instance().interpret(input);
	}

private:
	static auto instance() -> Brainfucker& {
		static Brainfucker internal_brainfucker;
		return internal_brainfucker;
	}

	auto interpret(const char* code) -> void
	{
		_instruction_block = code;
		_ip = code;
		while (*_ip != '\0')
		{
			switch (*_ip) {
			case '[': loop_begin();		break;
			case ']': loop_end();		break;
			case '>': increment_ptr();	break;
			case '<': decrement_ptr();	break;
			case '+': increment_pos();	break;
			case '-': decrement_pos();	break;
			case '.': print_pos();		break;
			case ',': read_pos();		break;
			default: _ip++; break;
			}	
		}
	}

	auto init_memory()-> void
	{
		for (pointer x = _memory; x != _memory + _memory_size; ++x)
		{
			*x = 0;
		}
	}

	auto increment_ptr() -> void {
		if (_ptr_memory + 1 > &_memory[_memory_size-1]) throw;
		_ptr_memory++;
		_ip++;
	}
	auto decrement_ptr() -> void {
		if (_ptr_memory - 1 < _memory) throw;
		_ptr_memory--;
		_ip++;
	}
	auto increment_pos() -> void {
		(*_ptr_memory)++;
		_ip++;
	}
	auto decrement_pos() -> void {
		(*_ptr_memory)--;
		_ip++;
	}
	auto print_pos() -> void {
		std::cout << *_ptr_memory;
		_ip++;
	}
	auto read_pos() -> void
	{
		char in;
		std::cin >> in;
		*_ptr_memory = in;
		_ip++;
	}
	auto loop_begin() -> void
	{
		if (*_ptr_memory == 0)
		{
			cv_pointer _aux = _ip;
			auto _stack_size = _stack.size() + 1;

			while (*_aux != '\0')
			{
				switch (*_aux)
				{
				case '[':
					_stack.push(_aux);
					break;
				case ']':
					if (_stack.size() == _stack_size)
					{
						_ip = _aux + 1;
						_stack.pop();
						return;
					}
					else _stack.pop();
					break;
				}
				_aux++;
			}
			throw;
		}
		else
		{
			_stack.push(_ip);
			_ip++;
		}
	}
	auto loop_end() -> void
	{
		if (_stack.empty()) throw;
		
		_ip = _stack.top();
		_stack.pop();
	}

	Brainfucker() {
		_memory = new value_type[_memory_size];
		_ptr_memory = _memory;
		if (not _memory) throw;
		init_memory();
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	~Brainfucker() {
		if (_memory) delete[] _memory;
		if (hConsole) CloseHandle(hConsole);
	}

	size_t	_memory_size = 100;	// edit here if you need more memory
	pointer				_memory			= nullptr;
	pointer				_ptr_memory		= nullptr;
	std::stack<cv_pointer>	_stack;

	cv_pointer				_instruction_block = nullptr;
	cv_pointer				_ip = nullptr;
	HANDLE hConsole;
};