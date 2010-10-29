/*
    This file is part of OpenDAQ.   
    Copyright (C) Shapar Andrei (email: nkerah_w@mail.ru)

    OpenDAQ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DTHREAD_H
#define DTHREAD_H
#include <unistd.h> // usleep ();
#include <QThread> // отсюда наследуем весь основной класс потока
#include <QString> // для использования в слотах/сигналах
#include <QTimer>
#include <stdio.h>
#include <stdlib.h>
#include "uhandler.h" // базовый объект создается из класса UHandler
#include "dconfig.h" // структура конфигурации
#include "dpack.h"

class DThread : public QThread 
{
	Q_OBJECT  // макрос, позволяющий нам использовать механизм сигналов и слотов

public:
	DThread(); 
	DConfig *config;			// настройки
	UHandler *device;
	unsigned int cur_measure;	// measurements counter

public slots:
	//void deliver_data ();	// приём резльутата от device
	void deliver_data (DPack *pack);
	void set_config (DConfig *cfg);	// установка конфигурации 	
	void stop_thread();		// остановка выполнения потока
	void start_thread();

protected:
	void run();	// перегружаем стандартную функцию работы потока, вносим туда весь полезный код.

signals:
	void chart_data (DPack *pack); // передача результата диаграмме
	void text_data (DPack *pack);  // передача результата в таблицу
	void save_data (DPack *pack);	// передача результата для сохранения в файл
//	void started();   // начало одного цикла заполнения буфера	
	void done();	  // конец заполнения буфера	
	void get_config (DConfig *cfg); // передача конфигурации структуры DConfig
	void series_start(); // для индикации начала серии измерений
	void series_end();	// соотв. для конца

private:
	volatile bool stopped;	// Переменная-флаг, служит для управления потоком.
	unsigned int cur_cycle;	// cycle counter
};
#endif
