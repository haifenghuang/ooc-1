/**
 * Динамический список объетов
 *
 * @author Латышев А.И.
 */


#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../ooc/mm.h"
#include "../ooc/ooc.h"
#include "list.h"


/**
 * Быстрая сортировка элементов списка по возрастанию значения
 * @param _self Список
 * @param low Индекс сортировки
 * @param hight Индекс сортировки
 */
static void _QSort( void* _self, uint32_t low, uint32_t high );


/**
 * Добавить элемент в начало списка
 * @param _self Список
 * @param id Идентификатор элемента
 * @param obj Добавляемый элемент
 */
static void _AddFirst( void* _self, uint32_t id, void* const obj )
{
	struct List* self = (struct List*)_self;

	// Увеличение буфера памяти для списка (при необходимости)
	if( self->count >= self->dim )
	{
		self->dim += 4;
		self->buf = (struct Node*)realloc( self->buf, self->dim * sizeof( struct Node ) );
	}

	// Сдвиг элементов списка
	{
		uint8_t i = 0;
		for( i = self->count; i > 0; i++ )
		{
			self->buf[ i ] = self->buf[ i - 1 ];
		}
	}

	// Добавление элемента в начало списка
	self->buf[ 0 ].id = id;
	self->buf[ 0 ].obj = obj;
	self->count++;
}


/**
 * Добавить элемент в конец списка
 * @param _self Список
 * @param id Идентификатор элемента
 * @param obj Добавляемый элемент
 */
static void _AddLast( void* _self, uint32_t id, void* const obj )
{
	struct List* self = (struct List*)_self;

	// Увеличение буфера памяти для списка (при необходимости)
	if( self->count >= self->dim )
	{
		self->dim += 4;
		self->buf = (struct Node*)realloc( self->buf, self->dim * sizeof( struct Node ) );
	}

	// Добавление элемента в конец списка
	self->buf[ self->count ].id = id;
	self->buf[ self->count ].obj = obj;
	self->count++;
}


/**
 * Поиск элемента
 * @param _self Список
 * @param id Идентификатор элемента
 * @return Элемент
 */
static void* _Search( void* _self, uint32_t id )
{
	struct List* self = (struct List*)_self;

	uint8_t i = 0;
	for( i = 0; i < self->count; i++ )
	{
		if( self->buf[ i ].id == id )
		{
			return self->buf[ i ].obj;
		}
	}
	return NULL;
}


/**
 * Поиск элемента
 * @param _self Список
 * @param id Идентификатор элемента
 * @return Номер элемента
 */
static int32_t _SearchIndex( void* _self, uint32_t id )
{
	struct List* self = (struct List*)_self;

	uint8_t i = 0;
	for( i = 0; i < self->count; i++ )
	{
		if( self->buf[ i ].id == id )
		{
			return i;
		}
	}
	return -1;
}


/**
 * Удаление элемента
 * @param _self Список
 * @param id Идентификатор элемента
 */
static void _Delete( void* _self, uint32_t id )
{
	struct List* self = (struct List*)_self;

	// Поиск удаляемого объекта
	uint8_t i = 0;
	for( i = 0; i < self->count; i++ )
	{
		if( self->buf[ i ].id == id )
		{
			// Смещение всех последующих объектов в списке
			for( ; i < self->count - 1; i++ )
			{
				self->buf[ i ] = self->buf[ i + 1 ];
			}
			self->count--;
			memset( &self->buf[ self->count ], 0x00, sizeof( struct Node ) );
		}
	}
}


/**
 * Сортировка по значению (по возрастанию)
 * @param _self Список
 */
static void _Sort( void* _self )
{
	struct List* self = (struct List*)_self;

	if( self->count )
	{
		_QSort( self, 0, self->count - 1 );
	}
}


/**
 * Конструктор класса объекта
 * @param _self Класс объекта
 * @param app Параметры создания
 */
static void ListClass_ctor( void* _self, va_list* app )
{
	struct ListClass* self = (struct ListClass*)_self;
	self->AddFirst = _AddFirst;
	self->AddLast = _AddLast;
	self->Search = _Search;
	self->SearchIndex = _SearchIndex;
	self->Delete = _Delete;
	self->Sort = _Sort;
}


/**
 * Конструктор объекта
 * @param _self Объект
 * @param app Параметры создания
 */
static void List_ctor( void* _self, va_list* app )
{
	struct List* self = (struct List*)_self;
	self->dim = va_arg( *app, uint32_t );
	assert( self->dim );
	self->buf = (struct Node*)calloc( self->dim, sizeof( struct Node ) );
	assert( self->buf );
}


/**
 * Деструктор объекта
 * @param _self Объект
 * @return Очищенный объект
 */
static void List_dtor( void* _self )
{
	struct List* self = (struct List*)_self;
	free( self->buf );
	self->buf = 0;
}


/**
 * Инициалиация класса и объекта
 */
void List_Init( void )
{
	if( !ListClass )
	{
		ListClass = New( Class, "ListClass",
				Class, sizeof( struct ListClass ),
				ctor, ListClass_ctor,
				0 );
	}
	if( !List )
	{
		List = New( ListClass, "List",
				Object, sizeof( struct List ),
				ctor, List_ctor,
				dtor, List_dtor,
				0 );
	}
}


// Класс и объект
const void* ListClass = NULL;
const void* List = NULL;


/**
 * Быстрая сортировка элементов списка по возрастанию значения
 * @param _self Список
 * @param low Индекс сортировки
 * @param hight Индекс сортировки
 */
static void _QSort( void* _self, uint32_t low, uint32_t high )
{
	struct List* self = (struct List*)_self;
	uint32_t i = low;
	uint32_t j = high;
	uint32_t x = self->buf[ ( low + high ) / 2 ].id;

	do
	{
		while( self->buf[ i ].id < x ) i++;
		while( self->buf[ j ].id > x ) j--;
		if( i <= j )
		{
			struct Node tmp = self->buf[ i ];
			self->buf[ i ] = self->buf[ j ];
			self->buf[ j ] = tmp;
			i++;
			j--;
		}
	} while( i <= j );

	if( low < j )
	{
		_QSort( self, low, j );
	}
	if( i < high )
	{
		_QSort( self, i, high );
	}
}
