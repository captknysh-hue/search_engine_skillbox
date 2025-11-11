# search_engine_skillbox
**Search Engine** - учебный проект на С++ для Skillbox, реализующий простую модель поисковой системы.
Программа считывает тексты документов, строит **инвертированный индекс** и позволяет выполнять поиск по этим документам с ранжированием результатов по **релевантности**.

---

## Описание проекта
Проект демонстрирует, как работает базовый поисковый движок:

1. Чтение текстов документов.
2. Построение инвертированного индекса ('InvertedIndex'), который хранит, в каких документах встречаются слова и как часто.
3. Обработка поисковых запросов из файла 'request.json'.
4. Расчет **абсолютной** и **относительной релевантности** документов.
5. Формирование итогового файла 'answers.json' с результатами поиска.

---

## Структура проекта

```
search_engine/
│
├── CMakeLists.txt           # Конфигурация сборки проекта
│
├── config                   # Рабочие файлы JSON
│   ├── answers.json
│   ├── config.json
│   └── request.json
│
├── include                  # Заголовочные файлы(.h)
│   ├── ConverterJSON.h
│   ├── InvertedIndex.h
│   └── SeachServer.h
│
├── resources                # Исходные текстовые документы
│   ├── file001.txt
│   ├── file002.txt
│   └── file003.txt
│
├── src
│   ├── CMakeList.txt         # Конфигурация сборки подпроекта
│   ├── main.cpp              # Точка входа программы
│   ├── ConverterJSON.cpp     # Реализация работы с JSON-файлами (config.json, requests.json, answers.json)
│   ├── InvertedIndex.cpp     # Реализация алгоритма инвертированного индекса
│   └── SearchServer.cpp      # Реализация алгоритма поиска и ранжирования результатов
│
├── tests/                    # Тесты Google Test
│   ├── CMakeList.txt             # Конфигурация сборки подпроекта
│   ├── test_inverted_index.cpp   # Тестирование алгоритма инвертированного индекса
│   ├── test_search_server.cpp    # Тестирование алгоритма поиска и ранжирования результатов
│   └── test_main.cpp             # Запуск всех тестов
│
├── cmake-build-debug/ # Директория сборки (создаётся автоматически)
├── .gitignore
└── README.md                # Этот файл
```

---

## Установка и сборка

### Требования
- **CMake** ≥ 3.16  
- **g++ / clang / MSVC** (поддержка C++17)
- **GoogleTest** (автоматически подключается через FetchContent)

### Сборка проекта

```bash
git clone https://github.com/<your-username>/search_engine.git
cd search_engine
mkdir build && cd build
cmake ..
cmake --build .
```

---

## Использование

### 1. Настройте файл `config.json`
```json
{
  "config": {
    "name": "SearchEngine",
    "version": "1.0",
    "max_responses": 5
  },
  "files": [
    "resources/file001.txt",
    "resources/file002.txt",
    "resources/file003.txt"
  ]
}
```

### 2. Добавьте поисковые запросы в `requests.json`
```json
{
  "requests": [
    "milk water",
    "capital of russia"
  ]
}
```

### 3. Запустите программу
```bash
./search_engine
```

### 4. Результаты сохранятся в `answers.json`
```json
{
  "answers": {
    "request001": {
      "result": true,
      "relevance": [
        {"docid": 2, "rank": 1.0},
        {"docid": 0, "rank": 0.7}
      ]
    }
  }
}
```

---

## Тестирование

Тесты реализованы с использованием **Google Test**.

Для запуска всех тестов:
```bash
./search_engine_tests
```

---

## Основные классы

### `InvertedIndex`
Отвечает за построение словаря встречаемости слов по документам.

### `SearchServer`
Обрабатывает поисковые запросы, вычисляет **абсолютную** и **относительную** релевантность и сортирует результаты.

---

## Многопоточность

Обновление базы документов (InvertedIndex::UpdateDocumentBase) реализовано с использованием std::thread, что ускоряет индексацию при большом числе файлов.

## Пример работы

**Документы:**
```
file001.txt: "milk sugar salt"
file002.txt: "milk a milk b milk c milk d"
```

**Индекс:**
```
"milk" → {0,1}, {1,4}
"sugar" → {0,1}
"salt" → {0,1}
```

**Поиск:** `"milk"`  
**Результат:** документ №1 (rank=1.0), документ №0 (rank=0.25)

---

## Используемые технологии

- C++17  
- CMake  
- Google Test  
- nlohmann/json

---

## Автор

**<IGOR_KNYSH>**  
Email: <capt.knysh@gmail.com>  
GitHub: [<captknysh-hue>](https://github.com/<captknysh-hue>)

---

## Лицензия

Проект распространяется под лицензией **MIT License**.
