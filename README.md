# QWERTY
    Запуск программы в консоли: ./main dese  #  argv[1] = "dese"
    
1. Открываем предварительно отсортированный список уникальных слов.
2. Создаем массив структур в которой все буквы в алфавитном порядке знают своё окружение.
3. Входим в рекурсивную функцию.
4. В рекурентной функции ищем по буквенно те символы которые подали в аргументах, когда эти буквы закончились функция сама подбирает буквы.
5. Добавляем Index каждого найденного уникального слова в массив индексов.
6. Выводим результат на экран, все слова не попадающие под маску Соседствующих букв уже отброшены.

	./main ra

 ra	
raw
 rawer
raws
ras
rase	
raser	
rases	
rased	
rasa

CountWords 10 