/**
 * Список объетов
 *
 * @author Латышев А.И.
 *
 * @revision $Id:$
 */


#pragma once
#ifndef LIST_H
#define	LIST_H


#include "ooc.h"


// Предварительное объявление объекта и его класса
extern const void* List;
extern const void* ListClass;


/**
 * Элемент списка
 */
struct Node
{
	/**
	 * Объект
	 */
	void* obj;

	/**
	 * Идентификатор объекта
	 */
	uint32_t id;
};


/**
 * Список объектов
 */
struct List
{
	/**
	 * Родительский объект
	 */
	const struct Object _;

	/**
	 * Массив элементов
	 */
	struct Node* buf;

	/**
	 * Текущий размер буфера (в элементах) :-)
	 */
	uint32_t dim;

	/**
	 * Количество элементов в списке
	 */
	uint32_t count;
};


/**
 * Класс объекта List
 */
struct ListClass
{
	/**
	 * Родительский класс
	 */
	const struct Class _;

	/**
	 * Добавить элемент в начало списка
	 */
	void (*AddFirst)( void* _self, uint32_t id, void* const obj );

	/**
	 * Добавить элемент в конец списка
	 */
	void (*AddLast)( void* _self, uint32_t id, void* const obj );

	/**
	 * Поиск элемента
	 */
	void* (*Search)( void* _self, uint32_t id );

	/**
	 * Поиск номера элемента
	 */
	int32_t (*SearchIndex)( void* _self, uint32_t id );

	/**
	 * Удаление элемента
	 */
	void (*Delete)( void* _self, uint32_t id );

	/**
	 * Сортировка по значению (по возрастанию)
	 */
	void (*Sort)( void* _self );
};


#endif	/* LIST_H */
