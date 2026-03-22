# SpeedFetch - System Information Fetcher

Минималистичная и быстрая программа на C++ для вывода информации о вашей Linux системе с красивым ASCII артом дистрибутива.

## 📋 Возможности

- Быстрый вывод информации о системе  
- Поддержка основных Linux дистрибутивов (Ubuntu, Fedora, Debian, Arch, Manjaro, openSUSE и др.)  
- Красивый ASCII арт для каждого дистрибутива  
- Пользователе и hostname
- Операционной системе
- Версии ядра
- Процессоре
- Оперативной памяти
- Свободном месте на диске
- Времени работы системы
- Shell и терминале

## 🛠️ Сборка

### Требования:
- GCC/Clang компилятор с поддержкой C++17
- CMake 3.10 или выше
- Linux система
- make (опционально, но рекомендуется)

### Быстрая сборка (с Makefile):

```bash
cd speedfetch
make build      # Компилирует программу
make run        # Компилирует и запускает
make install    # Устанавливает в систему (требует sudo)
make clean      # Удаляет build директорию
```

### Ручная сборка (через CMake):

```bash
cd speedfetch
mkdir build
cd build
cmake ..
make
./speedfetch
```

### Использование скриптов:

```bash
# Дать права на выполнение
chmod +x build.sh install.sh

# Собрать
./build.sh

# Установить (требует sudo)
sudo ./install.sh
```

## 🚀 Использование

### Запуск из папки build:
```bash
./build/speedfetch
```

### После установки в систему:
```bash
speedfetch
```

Просто запустите программу в любой папке!

## 📁 Структура проекта

```
speedfetch/
├── CMakeLists.txt          # Конфигурация CMake
├── src/
│   ├── main.cpp            # Главная программа
│   ├── system_info.h       # Заголовок для сбора информации
│   ├── system_info.cpp     # Реализация сбора информации
│   ├── ascii_art.h         # Заголовок для ASCII артов
│   └── ascii_art.cpp       # Реализация ASCII артов
└── README.md               # Этот файл
```

## 🎨 Поддерживаемые дистрибутивы

- Ubuntu
- Fedora
- Debian
- Arch Linux
- Manjaro
- openSUSE
- CentOS
- Pop!_OS
- И другие Linux системы

## 💡 О программе

SpeedFetch написана на чистом C++ с минимальными зависимостями. Программа использует системные файлы `/proc` и стандартные Linux команды для получения информации о системе.

## 📝 Лицензия

GNU GPLv3

---

**Автор:** MyNameIsV
