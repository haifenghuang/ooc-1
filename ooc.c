/**
 * Модуль предоставления возможности работать со структурами как с классами
 * (с некоторыми ограничениями)
 *
 * @author Латышев А.И.
 *
 * @revision $Id:$
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mm.h"
#include "ooc.h"


/**
 * Конструктор объекта
 * @param _self Объект
 * @param app Параметры создания
 */
static void Object_ctor( void* _self, va_list* app )
{
	// ...
}


/**
 * Деструктор объекта
 * @param _self Объект
 */
static void Object_dtor( void* _self )
{
	// ...
}


/**
 * Конструктор класса объекта
 * @param _self Класс объекта
 * @param app Параметры создания
 */
static void Class_ctor( void* _self, va_list* app )
{
	struct Class* self = (struct Class*)_self;

	// Инициализация параметров класса
	self->name = va_arg( *app, char* );
	self->super = va_arg( *app, struct Class* );
	self->size = va_arg( *app, size_t );
	assert( self->super );

	// Копирование указателей методов из родительского класса
	{
		/*size_t offset = 0;
		offset = offsetof( struct Class, ctor );
		memcpy( (char*)self + offset, (char*)self->super + offset, sizeOf( self->super ) - offset );*/
	}

	// Переопределение методов
	{
		typedef void (*f)();
		f selector;
		va_list ap = *app;

		selector = va_arg( ap, f );
		while( selector )
		{
			f method = va_arg( ap, f );
			if( selector == (f)ctor )
			{
				*(f*)&self->ctor = method;
			}
			else if( selector == (f)dtor )
			{
				*(f*)&self->dtor = method;
			}
			selector = va_arg( ap, f );
		}
	}
}


/**
 * Деструктор класса
 * @param _self Уничтожаемый класс
 * @return
 */
static void Class_dtor( void* _self )
{
	struct Class* self = (struct Class*)_self;
	printf( "%s: cannot destroy class\n", self->name );
}


// Инициалиация объекта и класса
static const struct Class object[] =
{
	{
		{ object + 1 },
		"Object", NULL, sizeof( struct Object ),
		Object_ctor, Object_dtor
	},
	{
		{ object + 1 },
		"Class", NULL, sizeof( struct Class ),
		Class_ctor, Class_dtor
	}
};


// Объект и класс
const void* Object = object;
const void* Class = object + 1;
