/**
 * �������� ������ ��� ��������
 *
 * @author ������� �.�.
 */


#pragma once
#ifndef MM_H
#define MM_H


#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>


/**
 * �������� �������
 * ��������� ������ ������������ ������� ��� ������� � ����� ������������ �������
 * @param _class ����� �������
 * @param ... ��������� �������� �������
 * @return ��������� ������
 */
void* New( const void* _class, ... );


/**
 * ����������� �������
 * ����� ����������� ������� � ������������ ���������� ������ ��� ������
 * @param _self ������
 */
void Delete( void* self );


/**
 * ����������� ������� ������ ���������� ��������
 * @param _self ������
 * @return
 */
size_t sizeOf( const void* self );


/**
 * ����������� ������ �������
 * @param _self ������
 * @return
 */
const void* classOf( const void* _self );


/**
 * ���������� ������� � ������� ����
 * @param _class ������ �����
 * @param _self ������
 * @return
 */
const void* cast( const void* _class, const void* _self );


/**
 * ����������� ��������
 * �������� �� ������� �������� ������� ������������ ������������ �������� (������ ����)
 * @param _class ����� �������
 * @param _self ������
 * @param app ��������� �������� �������
 */
void ctor( const void* _class, void* _self, va_list* app );


/**
 * ���������� ��������
 * �������� �� ������� �������� ������� ����������� ������������ �������� (����� �����)
 * @param _self ������
 * @param app
 */
void dtor( void* _self );


#endif /* MM_H */
