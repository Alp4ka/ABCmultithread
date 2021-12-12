# ДЗ#5 по дисциплине "Архитектура вычислительных систем". С++, Multithreading
## Выполнил Горковец Роман Романович, БПИ204 
## 5 Вариант.
 
 
Краткое описание:
Последовательность работы программы следующая: 
По умолчанию есть N каннибалов с определеннным уровнем голода.
Каждый каннибал живет по следующим правилам: пока уровень голода не упадет до нуля - сидит на лавочке и занимается своими каннибальскими делами.
Как только падает до нуля - пытается подойдти к горшку за едой. Но, если видит, что там уже есть кто-то, то он ждет своей очереди. 
Когда подходит очередь каннибала, он проверяет, есть ли еда в горшке. Если  есть - берет кусочек, утоляя голод, и уходит, если нет - зовет повара и терпеливо ждет момента пока повар не приготовит полный чан еды. Как только этот момент наступает, он берет один кусочек и уходит.

Повар же живет по следующему принципу: большую часть времени он спит. Но когда к нему подоходит каннибал, он просыпается и идет кашеварить.
Покашеварил - лег спать.

Повар занимается монотонной работой уже несколько лет, готовя еду для племени каннибалов не щадя себя. 
Это не могло не отразиться на его психическом здоровье, поэтому уже который год его посещают суицидальные мысли.
Поэтому с некоторой вероятностью (1/20) во время очередной готовки ужина он может наложить на себя руки.

Также программа содержит в себе определенную мораль для самых маленьких разработчиков. Кушать человечину - плохо, 
поэтому с некоторой вероятностью каннибал может отравиться во время очерденого приема пищи.
Так как мы исключаем возможность нормальной жизни каннибала с таким питанием, то каждый каннибал в конечном итоге умрет
и программа будет бесконечно наблюдать за спящим поваром. Что ж, очень грустно...
***
### Структура проекта

Наименование | Количество | Вес (байты)
----- | ----- | ------
.cpp | 6 | 9942
.h | 5 | 2245
Итог | 11 | 12187

 * **cmake_build_debug/** _Здесь хранится исполняемый файл_
 * cannibal.h _Описание класса каннибала_
 * cannibal.cpp _Реализация класса каннибала_
 * chef.h _Описание класса повара_
 * chef.cpp _Реализация класса повара_
 * jar.h _Описание класса горшка_
 * jar.cpp _Реализация класса горшка_
 * semaphore.h _Описание семафора_
 * semaphore.cpp _Реализация класса семафора_
 * utils.h _Утилитки_
 * utils.cpp _Утилитки_
 * main.py - _Мэйн_
***
### Запуск:
Стандартный:
```sh
./ABC5 10 4
```
> **Важно:** В данном случае первым аргументом указывается количество каннибалов, вторым - максимальная вместимость горшка.


Рандомная генерация:
```sh
./ABC5
```

### Вывод
Я использовал парадигму "Взаимодействующие равные", т.к. у нас есть два жизненных цикла(повар и дикарь), которые большую часть времени должны взаимодействовать независимо и зависимо только тогда, когда каннибалу захочется кушать. Одновременно доступ к чану должен иметь только один человек (либо готовим иждем, либо кушаем). Для доступа к некоторым полям повара и чана использовались семафоры во избежания неопредленного поведения. (Хотя, на мой взгляд,  в случае чана лучше было использовать один мютекс).
