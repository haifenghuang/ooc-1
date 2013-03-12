/**
 * Базовый модуль для ООС
 *
 * @author Латышев А.И.
 */


#pragma once
#ifndef OOC_H
#define OOC_H


#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>


// Предварительное объявление объекта и его класса
extern const void* Object;
extern const void* Class;


/**
 * Абстрактный объект
 */
struct Object
{
	/**
	 * Класс объекта
	 */
	const struct Class* c;
};


/**
 * Абстрактный класс
 */
struct Class
{
	/**
	 * Описываемый объект
	 */
	const struct Object _;

	/**
	 * Название класса
	 */
	const char* name;

	/**
	 * Родительский класс
	 */
	const struct Class* super;

	/**
	 * Размер объекта
	 */
	size_t size;

	/**
	 * Конструктор объекта
	 */
	void (*ctor)( void* _self, va_list* app );

	/**
	 * Деструктор объекта
	 */
	void (*dtor)( void* _self );
};


#endif /* OOC_H */
