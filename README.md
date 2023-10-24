# TestTaskFreeRTOS
Test task CTRL+

# Задание

*В рамках данного тестового задания необходимо интегрировать систему управления трёмя светодиодами с использованием микроконтроллера (МК) и RTOS. Требуется создать отдельные потоки (треды) для каждого светодиода, выполняя следующие условия:
1.	Первый светодиод: должен переключать своё состояние (вкл/выкл) через равные временные интервалы.
2.	Второй светодиод: также переключает состояние, но остаётся выключенным во время, когда включен первый светодиод.
3.	Третий светодиод: его яркость должна плавно изменяться с использованием ШИМ — от 0 до заранее установленного уровня (по умолчанию, 50% максимальной яркости) и обратно.

Дополнительно, необходимо реализовать поток (тред) UART, который будет:
1.	Ожидать ввода команд от пользователя.
2.	Обрабатывать следующие команды:
+	«delayAll:500\r»: устанавливает интервал переключения состояния для всех светодиодов.
+	«delay:1:100\r»: задаёт время переключения для конкретного светодиода, где "1" соответствует номеру светодиода, а "100" — времени.
+	«toggleExec:1\r»: включает или выключает поток управления светодиодом, где "1" — номер светодиода.
+	«toggleExecAll\r»: включает или выключает потоки управления всеми светодиодами.
+	«pwm:100:500\r»: устанавливает целевую яркость и время изменения яркости для третьего светодиода, где "100" — уровень яркости, а "500" — время изменения.
+	Отвечать сообщением “Unknown command\r” на любую неопределённую команду.
Выбор RTOS остаётся на усмотрение исполнителя. Однако использование RTOS Zephyr будет считаться дополнительным преимуществом, хотя и не является обязательным условием.
Цель задания — демонстрация навыков работы с многопоточностью, периферией микроконтроллера, а также понимания принципов работы с RTOS.*

# Структура программы.

Программа создана на языке **С** с применением операционной системы реального времени FreeRTOS. Тестовая версия ПО была написана с применением CubeMX и IDE Keil.
Программа отлажена на макетной плате **STM32 Discoveru F411**

**main.c** - основной файл программы, в котором инициализируются все блоки микроконтроллера, задачи, таймеры, очереди и семафоры RTOS.
**freertos.c** - файл в котором описана применяемая RTOS.
**stm32f4xx_it.c** - файл с описанием прерываний.
**stm32f4xx_hal_msp.c** - файл библиотеки HAL.
**SysClk.c** - файл в котором описано тактирование микроконтроллера.
**gpio.c** - файл в котором описана инициализация выводов мкроконтроллеров.
**uart.c** - файл с описанием инициализации блока UART и функцией обработки семафора, взводимого при получении байта по UART.
**timer_pwm.c** - файл с инициализацией таймера в режиме ШИМ.
**rtosTask.c** - файл с описанием задач (потоков) RTOS и хендлеров к ним.
**rtosTimers.c** - файл с описанием программных таймеров RTOS и хендлеров к ним.
**rtosQueues.c** - файл с описанием хендлеров очередей, которые используются в задачах.

**rtosSemaphores.c** - файл с описанием хендлеров семафоров.



Приложен архив отладочного проекта CubeMX со всеми отладочными комментариями.


