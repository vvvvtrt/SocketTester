# Тестер сети на разном размере пакетов и частоте их отправки

- **ServerTest**: В этом разделе расположен сервер для теста сети:
  - **bin.dbg** расположены файлы:
    -  **config.txt** - конфигурация сервера ip, port, размер пакета.
    -  **ServerTest.exe** - запуск сервера или же запуск через **main.cpp** в каталоге **ServerTest**.
  - **tcp_server** - методы для запуска сервера для приемов пакетов.
  - **config_read** методы для чтения **config.txt**

- **ClientTest**: В этом разделе расположен тестер сети:
  - **bin.dbg** расположены файлы:
    -  **config.txt** - конфигурация тестера, можно задать ip, port, размер пакета и частоту отправки.
    -  **input.txt** - вводные текстовые данные для отправки.
    -  **output.txt** - ввывод программы и замеры скорости.
    -  **ClientTest.exe** - запуск тестера(включать после запуска сервера иначе тест не сработает) или же запуск через **main.cpp** в каталоге **ClientTest**.
  - **socklib** метод для подключение и отправки пакетов на сервер.
  - **config_read** методы для чтения **config.txt**
  - **text_chunker** чтение данных из **input.txt** и разбиение на пакеты.
