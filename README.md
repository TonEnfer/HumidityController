# HumidityController
Humidity controller on STM32F030F4

Программное обеспечение для контроллера влажности на STM32F030F4

К контроллеру подключен семисегментный индикатор, энкодер с кнопкой и датчик BME280. Выходной каскад построен на симисторе.

## Структура проекта:

-*./CMSIS* - стандартные библиотеки

-*./inc* - общие header'ы

-*./inc/FSM* - header'ы конечного автомата

-*./inc/HAL* - Hardware Abstraction Level incs;

-*./inc/HAL/Drivers* - Low level driver incs;

-*./src* - исходный код

-*./inc/FSM* - исходники конечного автомата

-*./inc/HAL* - Hardware Abstraction Level src;

-*./inc/HAL/Drivers* - Low level driver src;

-*./startup* - автоматически сгенерированные файлы начальной инициализации контроллера