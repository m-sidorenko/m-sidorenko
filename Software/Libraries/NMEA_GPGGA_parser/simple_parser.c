/*----------------------------------------------

Simple NMEA parser for embedded systems

----------------------------------------------*/

#define __SIMPLE_PARSER_C__

#include "simple_parser.h"


uint8_t parser(uint8_t* raw_data, T_GPGGA* msg)
{
	static uint8_t s_cnt = 0;				// счетчик заполения массивов полей сообщения
	static uint8_t id = 0;					// флаг id
	static uint8_t id_arr[6] = "XXXXX";		// массив для расшифровки id

	static uint8_t field_number = 0;		// номер поля
	static uint8_t cnt = 0;					// счетчик заполнения массива для расшифровки id
	static uint8_t msg_type = 0;			// код типа сообщения


	// ------------------------------------ НАЧАЛО СООБЩЕНИЯ ------------------------------------
	if (*raw_data == '$')
	{
		id = 1;		// надо заполнить id
		field_number = 0;
		cnt = 0;
		msg_type = 0;
		s_cnt = 0;
		return STATUS_FIND_START;
	}

	// ------------------------------------ ЗАПОЛНЯЕМ ID ------------------------------------
	if (id)
	{
		if (cnt < 5) // если еще НЕ заполнили ID до конца, то продолжаем
		{
			id_arr[cnt] = *raw_data;
			cnt++;
		}
		else		 // если заполнили ID до конца, то переходим в след. шаг
		{
			id = 0; // сбрасываем флаг заполения id
			cnt = 0;
			field_number = 1; // переходим к заполнению первого поля в след. итерации

			if (strcmp("GPGGA", (const char*)id_arr) == 0)
			{
				msg_type = 1;
			}
			else
				msg_type = 0;
		}
		return STATUS_OK;
	}

	// ------------------------------------ если встретили РАЗДЕЛИТЕЛЬ ------------------------------------
	else if (*raw_data == ',')
	{
		s_cnt = 0;
		field_number++;
		return STATUS_OK;
	}

	// ------------------------------------ если встретили КОНЕЦ сообщения ------------------------------------
	else if (*raw_data == '\n')
	{
		field_number = 0;
		s_cnt = 0;
		id = 0;
		if (msg_type == 1)
		{
			msg_type = 0;
			return STATUS_END_OF_MSG;
		}
		else
			return STATUS_ERROR;
	}

	// ------------------------------------ иначе заполняем ПОЛЯ ------------------------------------
	else if (msg_type)
	{
		switch (field_number)
		{
			case utc:
			{
				msg->utc[s_cnt] = *raw_data;
				s_cnt++;
				return STATUS_OK;
			}

			case lat:
			{
				msg->lat[s_cnt] = *raw_data;
				s_cnt++;
				return STATUS_OK;
			}

			case lat_s:
			{
				msg->lat_s = *raw_data;
				return STATUS_OK;
			}

			case lon:
			{
				msg->lon[s_cnt] = *raw_data;
				s_cnt++;
				return STATUS_OK;
			}

			case lon_s:
			{
				msg->lon_s = *raw_data;
				return STATUS_OK;
			}

			case fix_q:
			{
				msg->fix_q = *raw_data;
				return STATUS_OK;
			}

			case num_s:
			{
				msg->num_s[s_cnt] = *raw_data;
				s_cnt++;
				return STATUS_OK;
			}

			case hdop:
			{
				msg->hdop[s_cnt] = *raw_data;
				s_cnt++;
				return STATUS_OK;
			}

			case alt:
			{
				msg->alt[s_cnt] = *raw_data;
				s_cnt++;
				return STATUS_OK;
			}

			case alt_u:
			{
				msg->alt_u = *raw_data;
				return STATUS_OK;
			}

			case height:
			{
				msg->height[s_cnt] = *raw_data;
				s_cnt++;
				return STATUS_OK;
			}

			case height_u:
			{
				msg->height_u = *raw_data;
				return STATUS_OK;
			}

			case tslu:
			{
				msg->tslu[s_cnt] = *raw_data;
				s_cnt++;
				return STATUS_OK;
			}

/*			case st_id:
			{
				msg->st_id[s_cnt] = *raw_data;
				s_cnt++;
				return STATUS_OK;
			} */

			case ch_sum:
			{
				msg->ch_sum[s_cnt] = *raw_data;
				s_cnt++;
				return STATUS_OK;
			}

			default:
			{
				s_cnt = 0;
				return STATUS_ERROR;
			}
		}
	}
}
