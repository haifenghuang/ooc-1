/**
 * �������� ������ ��� ��������
 *
 * @author ������� �.�.
 *
 * @revision $Id:$
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <windows.h>
#include "../bsp/graph.h"
#include "ooc.h"
#include "mm.h"


#ifdef WIN32
/**
 * ������� ������������� ������
 */
static uint32_t objCount = 0;
static uint32_t memoryUsage = 0;
#endif


/**
 * �������� �������
 * ��������� ������ ������������ ������� ��� ������� � ����� ������������ �������
 * @param _class ����� �������
 * @param ... ��������� �������� �������
 * @return ��������� ������
 */
void* New( const void* _class, ... )
{
	const struct Class* c = (const struct Class*)_class;
	struct Object* object = NULL;
	va_list ap;

	assert( c && c->size );
	object = (struct Object*)calloc( 1, c->size );
	assert( object );
	object->c = c;

	#ifdef WIN32
	// �������� ������������� ������
	objCount++;
	memoryUsage += c->size;
	MoveCursor( 50, 1 );
	printf( "Obj: %03i, Mem: %06i", objCount, memoryUsage );
	#endif

	va_start( ap, _class );
	ctor( c, object, &ap );
	va_end( ap );

	return object;
}


/**
 * ����������� �������
 * ����� ����������� ������� � ������������ ���������� ������ ��� ������
 * @param _self ������
 */
void Delete( void* _self )
{
	if( _self )
	{
		#ifdef WIN32
		// �������� ������������� ������
		const struct Class* c = (const struct Class*)classOf( _self );
		objCount--;
		memoryUsage -= c->size;
		MoveCursor( 50, 1 );
		printf( "Obj: %03i, Mem: %06i", objCount, memoryUsage );
		#endif

		dtor( _self );
		free( _self );
	}
}


/**
 * ����������� ������� ������ ���������� ��������
 * @param _self ������
 * @return
 */
size_t sizeOf( const void* _self )
{
	const struct Class* const* cp = (const struct Class* const*)_self;
	assert( _self && *cp );
	return (*cp)->size;
}


/**
 * ����������� ������ �������
 * @param _self ������
 * @return
 */
const void* classOf( const void* _self )
{
	const struct Object* self = (const struct Object*)_self;
	assert( self && self->c );
	return self->c;
}


/**
 * ���������� ������� � ������� ����
 * @param _class ������ �����
 * @param _self ������
 * @return
 */
const void* cast( const void* _class, const void* _self )
{
	const struct Class* c = (const struct Class*)classOf( _self );
	assert( c && _class );

	while( c )
	{
		if( c == _class )
		{
			return c;
		}
		c = c->super;
	}
	return NULL;
}


/**
 * ����������� ��������
 * �������� �� ������� �������� ������� ������������ ������������ �������� (�� �������� � ���������)
 * @param _class ����� �������
 * @param _self ������
 * @param app ��������� �������� �������
 */
void ctor( const void* _class, void* _self, va_list* app )
{
	const struct Class* c = (const struct Class*)_class;
	const struct Class* s = c->super;
	if( s )
	{
		ctor( s, _self, app );
	}
	if( c->ctor )
	{
		c->ctor( _self, app );
	}
}


/**
 * ���������� ��������
 * �������� �� ������� �������� ������� ����������� ������������ �������� (�� ��������� � ��������)
 * @param _self ������
 * @param app
 */
void dtor( void* _self )
{
	const struct Class* c = (const struct Class*)classOf( _self );
	const struct Class* s = c->super;
	if( c->dtor )
	{
		c->dtor( _self );
	}
	while( s )
	{
		if( s->dtor )
		{
			s->dtor( _self );
		}
		s = s->super;
	}
}
