/**
 * Менеджер памяти для объектов
 *
 * @author Латышев А.И.
 */


#pragma once
#ifndef MM_H
#define MM_H


#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>


/**
 * Создание объекта
 * Выделение памяти необходимого размера для объекта и вызов конструктора объекта
 * @param _class Класс объекта
 * @param ... Параметры создания объекта
 * @return Созданный объект
 */
void* New( const void* _class, ... );


/**
 * Уничтожение объекта
 * Вызов деструктора объекта и освобождение выделенной памяти под объект
 * @param _self Объект
 */
void Delete( void* self );


/**
 * Определение размера памяти занимаемой объектом
 * @param _self Объект
 * @return
 */
size_t sizeOf( const void* self );


/**
 * Определение класса объекта
 * @param _self Объект
 * @return
 */
const void* classOf( const void* _self );


/**
 * Приведение объекта к нужному типу
 * @param _class Нужный класс
 * @param _self Объект
 * @return
 */
const void* cast( const void* _class, const void* _self );


/**
 * Конструктор объектов
 * Вызывает по цепочке иерархии объекта конструкторы родительских объектов (сверху вниз)
 * @param _class Класс объекта
 * @param _self Объект
 * @param app Параметры создания объекта
 */
void ctor( const void* _class, void* _self, va_list* app );


/**
 * Деструктор объектов
 * Вызывает по цепочке иерархии объекта деструкторы родительских объектов (снизу вверх)
 * @param _self Объект
 * @param app
 */
void dtor( void* _self );


#endif /* MM_H */
