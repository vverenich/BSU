# Лабораторная работа №11

1) Функция представлена в виде своего ряда Тейлора. Используя встроенный ассемблер и
команды математического сопроцессора разработайте тестовое консольное приложение и
процедуру/функцию на ассемблере для вычисления приближённого значения суммы этого
бесконечного ряда. При вычислении следующего слагаемого использовать значение,
полученное на предыдущей итерации.
2) Вычисления заканчивать, когда очередное слагаемое окажется по модулю меньше заданного
числа e. e удовлетворяет условию: 0 < e < 10-k
, k – натуральное число, k > 1, k задает
количество верных знаков в вычисленной сумме ряда.
3) Параметры x и k передавать через командную строку.
4) Сравнить значение суммы ряда со значением, непосредственно вычисленным используя
трансцендентные и арифметические команды сопроцессора.
5) Вывести на экран вычисленные значения используя библиотечные методы С/С++. Два
выведенных значения должны совпадать с заданной точностью (без округления), т.е. k знаков
после десятичной точки. При выводе чисел использовать форматирование, выводить только k
знаков после десятичной точки.

![image](https://user-images.githubusercontent.com/74289746/148575399-742af613-e83c-456c-94fd-fb6d1b90ea29.png)