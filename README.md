# Roguelike // @hakerhd93

# TODO
- [x] Нанесения урона врагам.
- [x] Создание статов врагам и их scale от сложности.
- [x] Взаимодейтвие с сундуками.
- [ ] Реализация телепорта.
- [x] Сделать лут, вообще какой-то.
- [ ] Переход на следующий этап.
- [x] Scale Сложности.
- [ ] Заполнить меню с Настройками.
- [ ] Заполнить меню с Ачивментами.
- [ ] Создать всё таки туториал, а не начало игры нажимая на туториал))0
- [ ] Придумать боссов.
- [ ] Придумать ачивменты.
- [x] Придумать как риализовать менюшки, такие как магазин, сундуки.
- [x] Система прокачки оружия и игрока.
- [ ] Формула брони, что бы дамаг на поздних стадиях не привращался в наноскопические порезы врагов.
- [x] Реализвать ИИ у врагов (спецефичный) 
# Последнее обновление
### Большое обновление
 **_0.3.5_**

- Переход с версии c++ 14 до версии c++ 20
- Перевод хранения данных врагов, игрока, оружия с массивов на структуры
- Добавил #pragma для подавление ложные предупреждений
- Код наконец-то оптимизирован (_удалено около 800 строчек с мусором, не оптимизированым_)
- ИИ у врагов, оооооочень спецефичний.
- Добавлено переходы на следующий уровень персонажа
- фикс багов с _getch();
- Теперь с сундука не 15 монет, а 5 монет
- Переделаны оружие вовсе, добавлено мног новых
- Сделан тестовый скейл сложности, и скейл от уровня персонажа соответственно
- (BETA) Магазин, пока что не работает

# Архив обновлений
### Большое обновление
**_0.2.9_**
 - Теперь можно взаимодействовать с сундуками
 - Немного по другому перересовается карта при передвижении (т.е теперь карта почти не отрисовывается, только при критических событиях, например переход на следующий этап, намного меньше нагружает комп)
 - Продвижение к нанесению урону врагу
 - Исправление ошибок связанной с выходом из поля

**_0.2.0_**
- Процедурная генерация карты
- Передвижение игрока
- Раскрашенные значки (Типо враг - красный, игрок - зелёный, сундук - жёлтый)
- Наработки на магазин
- Проверка на столкновение со стеной или с концом карты
- Исправление ошибок
- И много малых исправлений, о которых писать дольше чем их исправлять)


**_0.1.0_**
- Добавленно меню слева, геймплей не за горами)))

**_0.0.2_**
- Пункты в меню переменованы
- Изменено окно консоли и шрифт

**_0.0.1a_**
- Было исправлена ошибка C6283 на 107 строке
- На 135, 144, 153, 161 строчке было исправлено предупреждение C6031, _getch() -> cin.ignore();

**_0.0.1_**
- Создание меню

**_0.0.0_**
- Создание репозитория
