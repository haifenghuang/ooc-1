/**
 * ������ �������
 *
 * @author ������� �.�.
 *
 * @revision $Id:$
 */


#pragma once
#ifndef LIST_H
#define	LIST_H


#include "ooc.h"


// ��������������� ���������� ������� � ��� ������
extern const void* List;
extern const void* ListClass;


/**
 * ������� ������
 */
struct Node
{
	/**
	 * ������
	 */
	void* obj;

	/**
	 * ������������� �������
	 */
	uint32_t id;
};


/**
 * ������ ��������
 */
struct List
{
	/**
	 * ������������ ������
	 */
	const struct Object _;

	/**
	 * ������ ���������
	 */
	struct Node* buf;

	/**
	 * ������� ������ ������ (� ���������) :-)
	 */
	uint32_t dim;

	/**
	 * ���������� ��������� � ������
	 */
	uint32_t count;
};


/**
 * ����� ������� List
 */
struct ListClass
{
	/**
	 * ������������ �����
	 */
	const struct Class _;

	/**
	 * �������� ������� � ������ ������
	 */
	void (*AddFirst)( void* _self, uint32_t id, void* const obj );

	/**
	 * �������� ������� � ����� ������
	 */
	void (*AddLast)( void* _self, uint32_t id, void* const obj );

	/**
	 * ����� ��������
	 */
	void* (*Search)( void* _self, uint32_t id );

	/**
	 * ����� ������ ��������
	 */
	int32_t (*SearchIndex)( void* _self, uint32_t id );

	/**
	 * �������� ��������
	 */
	void (*Delete)( void* _self, uint32_t id );

	/**
	 * ���������� �� �������� (�� �����������)
	 */
	void (*Sort)( void* _self );
};


#endif	/* LIST_H */
