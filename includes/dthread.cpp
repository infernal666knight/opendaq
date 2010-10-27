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

#include "dthread.h"

DThread::DThread()
{ //конструктор
	device = new UHandler();	// создаём переменную управления устройством
	config = new DConfig;
	connect (device, SIGNAL (data_ready(DPack *)), this, SLOT (deliver_data (DPack *)) ); // связываем устройство с потоком

	stopped = false;
	cur_measure = 0; //счётчик, значение которого указывает на текущий период измерений. 
	cur_cycle = 0;
	fprintf (stderr, "DThread: constructor did all successful.\n");
}

void DThread::stop_thread() 
{
	stopped = true;
	fprintf (stderr, "DThread: stopped.\n");
}

void DThread::start_thread()
{
	stopped = false;
	fprintf (stderr, "DThread: started.\n");
	start();
}

void DThread::deliver_data (DPack *pack) 
{	// слот, принимающий информацию от сигнала device->dataStringRcvd (QString)
	if ( (cur_measure%config->chart_mod) == 0 ) 
	{
		emit chart_data(pack);
		fprintf (stderr, "DThread: chart_data() emitted. cur_measure = %d.\n", cur_measure);
	}
	if ( (cur_measure%config->table_mod) == 0 )
	{
		emit text_data(pack);
		fprintf (stderr, "DThread: text_data() emitted.\n");
	}
	fprintf (stderr, "DThread: Data delivered.\n");
	emit save_data(pack);

}

/*	Управление конфигурацией	*/

void DThread::set_config (DConfig *cfg)
{
	config = cfg;
	fprintf (stderr, "DThread: Config accepted.\n");
	fprintf (stderr, "DThread: measure_num : %d\n", config->measure_num);
}

// Главная функция потока
/*	обработка конфигурации и формирование запросов		*/

void DThread::run ()
{
	int pause = (config->measure_interval - 4.1)*1000;
	fprintf (stderr, "DThread: pause value is %d.\n", pause);
	if (!stopped)
	{
		emit started();
		cur_measure = 0;
		cur_cycle = 0;
		switch (config->mode)
		{
			case SINGLE_MODE:
				emit series_start();
				while (cur_measure < config->measure_num)
				{
					if (stopped)
						break;
					device->conversion_request();
					cur_measure++;
					usleep (pause);
				}
				break;

			case CYCLED_MODE:
				switch (config->cycle_mode)
				{
					case CYCLE_INFINITE:
						while (!stopped)
						{
							emit series_start();
							while (cur_measure < config->measure_num)
							{
								if (stopped)
									break;
								device->conversion_request();
								cur_measure++;
								usleep (pause);		
							}
							emit series_end();
						}
						break;

					case CYCLE_NON_INFINITE:
						while (cur_cycle < config->cycle_num)
						{
							emit series_start();
							while (cur_measure < config->measure_num)
                                                        {
                                                                if (stopped)
                                                                        break;
                                                                device->conversion_request();
                                                                cur_measure++;
                                                                usleep (pause);
                                                        }
                                                        emit series_end();
							cur_cycle++;
						}		
						break;
				}
				break;

			case SCHEDULED_MODE:
				break;
		}
		emit done();
	}
}

