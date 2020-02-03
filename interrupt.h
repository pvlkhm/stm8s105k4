// Если прерывание приоритетнее -> то оно идет на обработку (прерывая выполнение слабого)
// Если приоритет ниже или равен -> то оно в очередь
// Если приоритет прерывания == приоритету кода, то код никогда его не пустит

// Приоритеты есть Аппаратные (Таблица приоритетов) и Программные (Выставляются поверх таблицы)
// RESET и TRAP нельзя программно сменить - они самые приоритетные
// В Таблице приоритетов 25(29 мест) вектора прерывания (Источников прерывания)

// Внешние прерывания приходят с портов вместе (Нельзя настроить отдельные пины порта)

// RIM — для разрешения прерываний (Ставит коду низший приоритет 10)
// SIM — для запрета прерываний (Ставит коду самый высокий приоритет 11)

// Макрос для обработки прерывания с номер n (в Таблице приоритетов) функцией code
#define INTERRUPT(n, code) void interrupt_##n(void) __interrupt(n) code

// =================================================================================================
//                                         Векторы прерываний
// =================================================================================================
// Прерывание верхнего уровня
#define I_TLI 0
// Выхода из состояния сна 
#define I_AWU 1
// Контроллер такта
#define I_CLK 2
// Внешнее прерывание Порт А
#define I_EXTI0 3
// Внешнее прерывание Порт B
#define I_EXTI1 4
// Внешнее прерывание Порт C
#define I_EXTI2 5
// Внешнее прерывание Порт D
#define I_EXTI3 6
// Внешнее прерывание Порт E
#define I_EXTI4 7

// Reserver 8
// Reserver 9

// Конец передачи SPI
#define I_SPI 10
// TIM1 обновление/переполнение + триггер-событие/останов
#define I_TIM1_UO 11
// TIM1 захват/сравнение
#define I_TIM1_CC 12
// TIM2 обновление/переполнение
#define I_TIM2_UO 13
// TIM2 захват/сравнение
#define I_TIM2_CC 14
// TIM3 обновление/переполнение
#define I_TIM3_UO 15
// TIM3 захват/сравнение
#define I_TIM3_CC 16

// Reserver 17
// Reserver 18

// Прерывание I2C
#define I_I2C 19
// Завершение отправки Tx
#define I_UART2_TX 20
// Заполнение регистра данных (Конец приема)
#define I_UART2_DFULL 21
// Окончание преобразования АЦП
#define I_ADC1 22
// TIM4 захват/сравнение
#define I_TIM4_UO 23
// Конец записи + Попытка записи в защищенную область
#define I_FLASH 24


// =================================================================================================
//                                              ITC_SPRx
// =================================================================================================

typedef union DATA_ITC_SPR {
    struct {
        // Приоритет вектора 4*n + 0 (01: низкий, 00: Средний, 11: Высокий, 10: —)
        unsigned char VECT0SPR : 2;
        // Приоритет вектора 4*n + 1 (01: низкий, 00: Средний, 11: Высокий, 10: —)
        unsigned char VECT1SPR : 2;
        // Приоритет вектора 4*n + 2 (01: низкий, 00: Средний, 11: Высокий, 10: —)
        unsigned char VECT2SPR : 2;
        // Приоритет вектора 4*n + 3 (01: низкий, 00: Средний, 11: Высокий, 10: —)
        unsigned char VECT3SPR : 2;
    };
    // Значение регистра как есть, чистый байт
    unsigned char RAW;
} DATA_ITC_SPR;

/*
Регистры для установки Программного приоритета прерываниям (Векторам в Таблице приоритетов)
*/
#define ITC_SPR1 ((DATA_ITC_SPR *)0x7F70)
#define ITC_SPR2 ((DATA_ITC_SPR *)0x7F71)
#define ITC_SPR3 ((DATA_ITC_SPR *)0x7F72)
#define ITC_SPR4 ((DATA_ITC_SPR *)0x7F73)
#define ITC_SPR5 ((DATA_ITC_SPR *)0x7F74)
#define ITC_SPR6 ((DATA_ITC_SPR *)0x7F75)
#define ITC_SPR7 ((DATA_ITC_SPR *)0x7F76)
#define ITC_SPR8 ((DATA_ITC_SPR *)0x7F77)

// =================================================================================================
//                                       EXTI_CR1 и EXTI_CR2
// =================================================================================================

// Побитовая структура Регистра управления внешними прерываниями №1 
typedef union DATA_EXTI_CR1 {
    struct {
        // Установка чувствительности порта А
        // 00: Задний фронт + низкий уровень
        // 01: Передний фронт
        // 10: Задний фронт
        // 11: Задний фронт + Передний фронт
        unsigned char PAIS : 2;
        // Установка чувствительности порта B
        // 00: Задний фронт + низкий уровень
        // 01: Передний фронт
        // 10: Задний фронт
        // 11: Задний фронт + Передний фронт
        unsigned char PBIS : 2;
        // Установка чувствительности порта C
        // 00: Задний фронт + низкий уровень
        // 01: Передний фронт
        // 10: Задний фронт
        // 11: Задний фронт + Передний фронт
        unsigned char PCIS : 2;
        // Установка чувствительности порта D
        // 00: Задний фронт + низкий уровень
        // 01: Передний фронт
        // 10: Задний фронт
        // 11: Задний фронт + Передний фронт
        unsigned char PDIS : 2;
    };
    // Значение регистра как есть, чистый байт
    unsigned char RAW;
} DATA_EXTI_CR1; 

// Побитовая структура Регистра управления внешними прерываниями №2
typedef union DATA_EXTI_CR2 {
    struct {
        // Установка чувствительности порта E
        // 00: Задний фронт + низкий уровень
        // 01: Передний фронт
        // 10: Задний фронт
        // 11: Задний фронт + Передний фронт
        unsigned char PEIS : 2;
        // Установка чувствительности Top Level прерывания
        unsigned char TLIS : 1;
        unsigned char : 5;
    };
    // Значение регистра как есть, чистый байт
    unsigned char RAW;
} DATA_EXTI_CR2;

// Регистр управления внешними прерываниям №1 (фронт сигнала)
#define EXTI_CR1 ((DATA_EXTI_CR1 *)0x50A0)
// Регистр управления внешними прерываниям №2 (фронт сигнала)
#define EXTI_CR2 ((DATA_EXTI_CR2 *)0x50A1)
