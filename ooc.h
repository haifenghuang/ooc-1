/**
 * ������� ������ ��� ���
 *
 * @author ������� �.�.
 */


#pragma once
#ifndef OOC_H
#define OOC_H


#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>


// ��������������� ���������� ������� � ��� ������
extern const void* Object;
extern const void* Class;


/**
 * ����������� ������
 */
struct Object
{
	/**
	 * ����� �������
	 */
	const struct Class* c;
};


/**
 * ����������� �����
 */
struct Class
{
	/**
	 * ����������� ������
	 */
	const struct Object _;

	/**
	 * �������� ������
	 */
	const char* name;

	/**
	 * ������������ �����
	 */
	const struct Class* super;

	/**
	 * ������ �������
	 */
	size_t size;

	/**
	 * ����������� �������
	 */
	void (*ctor)( void* _self, va_list* app );

	/**
	 * ���������� �������
	 */
	void (*dtor)( void* _self );
};


#endif /* OOC_H */
