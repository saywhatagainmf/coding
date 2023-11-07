---
title: Задача о рюкзаке
weight: 3
draft: true
---

## 0-1 Рюкзак

В самой простой форме задача о рюкзаке формулируется так:

Даны $n$ предметов с весами $a_1,\\dots, a_n$. Определите, на какой
максимальный вес можно набрать предметов в рюкзак вместимости $W$.

Для решения этой задачи воспользуемся динамическим программированием.
Обозначим за $dp\[i\]\[j\]$ состояние, когда мы рассмотрели первые
$i$ предметов и набрали ими $j$ веса. $dp\[i\]\[j\]=True$, если такая
ситуация возможна, иначе $dp\[i\]\[j\]=False$.

Для каждого состояния $dp\[i\]\[j\]$, которое возможно получить, мы
можем либо взять предмет номер $i$ и попробовать обновить ответ из
состояния $dp\[i - 1\]\[j - a\[i\]\]$, либо не брать его и обновить
ответ из $dp\[i - 1\]\[j\]$. Очевидно, что мы можем получить 0 веса,
рассмотрев 0 предметов.

``` C++ numberLines
for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= W; j++) {
        dp[i][j] = dp[i - 1][j];
        if (a[i] <= j) {
            dp[i][j] = (dp[i][j] | dp[i - 1][j - a[i]]);
        }
    }
}
```

Ответом на задачу будет максимальное $n$, такое что $dp\[n\]\[j\]$ равно
$True$. Такое решение работает за $O(nW)$.

### Уменьшаем затраты памяти

Заметим, что на самом деле нам достаточно одномерно массива $dp\[w\]$, в
котором мы будем хранить, можно ли набрать такой вес. Изначально там
будут храниться нули, после чего мы будем по очереди добавлять
предметы и пересчитывать значения массива, пытаясь набрать вес w,
используя новый предмет, если конечно раньше мы не могли набрать вес w.

Работать такой алгоритм будет всё ещё за $O(nW)$, поскольку мы для
каждого предмета пытаемся перебрать все веса и пробуем этот вес
набрать, используя этот предмет.

### Неасимптотически уменьшаем затраты времени

Заметим, что нам нет необходимости каждый раз просматривать заново те
веса, которые мы уже умеем набирать. Заведём изначально ещё
дополнительный вектор $unreachable$ весов, которые мы не умеем
набирать, изначально там все веса от $1$ до $W$ (нулевой вес мы всегда
умеем набирать). На каждом шаге мы будем добавлять новый предмет и
будем перебирать веса из $unreachable$, если его получилось набрать,
то удаляем его из вектора: свапаем с последним элементом и делаем
pop_back. Поскольку порядок весов в $unreachable$ нам неважен, мы можем
спокойно переставлять элементы внутри него.

## Рюкзак со стоимостями предметов

Теперь у каждого предмета есть стоимость $c_i$. Надо набрать не как
можно больший вес, а как можно бОльшую суммарную стоимость предметов
так, чтобы предметы по весу влезли в рюкзак.

Изменим значение $dp\[i\]\[j\]$. Пусть оно равно максимальной стоимости
предметов, которые можно набрать среди первых $i$ с суммарным весом $j$.
Порядок пересчета динамики остается прежним, но меняется обновление
состояния: если мы не берем текущий предмет, то ответ не хуже, чем
для первых $i-1$ предмета. А если берем, то места на предыдущие
предметы остается $j - a\[i\]$, но мы прибавляем стоимость
нового предмета к ответу.

``` C++ numberLines
dp[i][j] = dp[i - 1][j];
if (a[i] <= j) {
    dp[i][j] = max(dp[i][j], dp[i - 1][j - a[i]] + c[i]);
}
```

Если так получилось, что веса большие, а стоимости маленькие, можно
поменять их местами и считать минимальный вес при данной набранной
стоимости. Поменять местами значение динамики и параметр — довольно
распространенный трюк в динамическом программировании.

## Рюкзак с ограниченным числом предметов

Пусть, теперь предметов каждого типа может быть несколько, то есть даны
не только веса и стоимости, но и максимальные количества каждого из
предметов $k_1,\\ldots,k_n$. Тогда для каждого состояния
$dp\[i\]\[j\]$ переберем, сколько мы взяли предметов такого типа и
сделаем переход из каждого соответствующего состояния. Понятно,
что мы не сможем взять более, чем $\\lfloor\\frac{W}{a_i}\\rfloor$
предметов каждого типа.

``` C++ numberLines
for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= W; j++) {
        dp[i][j] = dp[i - 1][j];
        if (a[i] <= j) {
            for (int cnt = 0; cnt <= k[i]; cnt++) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - a[i] * cnt] + c[i] * cnt);
            }
        }
    }
}
```

Такое решение работает за $O(nW^2)$, так как $k_i$ могут быть очень
большими, а $a_1=1$.

Можете попробовать решить эту задачу за $O(nW\\log K)$, где $K$ —
максимальное из $k_i$.

## Рюкзак с неограниченным числом предметов

Пусть, теперь каждого предмета будет не $k_i$, а вообще бесконечно.
Оказывается, задача стала только проще. Вернемся к обычному рюкзаку
с весами и стоимостями. Единственное отличие будет в том, что теперь мы
можем делать второй переход не из предыдущей строки, а прямо из текущей.
При этом заметим, что для каждого состояния достаточно рассмотреть
взятие только одного предмета данного типа, поскольку взятие двух
и более будет рассмотрено одновременно.

``` C++ numberLines
for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= W; j++) {
        dp[i][j] = dp[i - 1][j];
        if (a[i] <= j) {
            dp[i][j] = max(dp[i][j], dp[i][j - a[i]] + c[i]);
        }
    }
}
```

Такое решение работает за $O(nW)$.

Если $W$ велико, а $a_i$ достаточно малы, можно построить решение за
$O(n + A^3)$, где $A$ — максимальное из $a_i$. Заметим, что если $W$
достаточно большое, то большая часть рюкзака будет занята предметами
одного и того же типа с максимальной удельной стоимостью. Можно
доказать, что одним и тем же предметом будет занято не менее
$W-A^2$ веса. Таким образом, можно за $O(n)$ выбрать предмет с
максимальным удельным весом, а для оставшихся предметов
запустить предыдущий алгоритм, который сработает за $O(A^3)$, так
как имеет смысл рассматривать не более $A$ предметов, а максимальный вес
$A^2$.

## Восстановление ответа

Во всех рассмотренных задачах восстановление ответа делается стандартным
образом: нужно из ответа пройтись обратно до начала.

  - первый способ - это построить массив prev, где для каждой ячейки
    $dp\[i\]\[j\]$ хранить, берем мы предмет i, или не берем предмет
    $i$.
  - второй способ - это определять это на ходу, смотря, какое из
    значений $dp\[i - 1\]\[j\]$ или $dp\[i - 1\]\[j - a\[i\]\] +
    c\[i\]$ больше.

Если у нас есть $n$ предметов с весами $w_1, w_2, \\ldots, w_n$,
таких что $w_1 + w_2 + \\ldots + w_n = S$, то мы можем решить
задачу о рюкзаке за время $O(Sn)$ стандартной динамикой. Как решать
быстрее? Попытаемся сделать так, чтобы $n$ было $O(\\sqrt{S})$.

Заметим, что количество различных весов среди $w_1, w_2, \\ldots,
w_n$ будет $O(\\sqrt{S})$, потому что если среди них $k$ различных
чисел, то $S = w_1 + w_2 + \\ldots + w_n \\geq 1 + 2 + \\ldots +
k = \\frac{k(k + 1)}{2}$, значит $k \\leq \\sqrt{2S}$.

Рассмотрим некоторый вес $x$, который встречается в наборе весов.
Обозначим за $c$ его количество вхождений. Рассмотрим такое
максимальное натуральное $t$, что $2^t - 1 \\leq c$. Тогда в
наборе весов $c$ вхождений веса $x$ заменим на веса $x, 2x,
\\ldots, 2^{t-1}x, (c+1-2^t)x$. Легко видеть, что все суммы $0, x,
\\ldots, cx$ можно по-прежнему набрать и только их.

Уже сейчас легко видеть, что новое количество весов будет
$O(\\sqrt{S}\\log{S})$, потому что для каждого веса мы оставили $\\leq
\\log{S}$ весов, а различных весов $O(\\sqrt{S})$. Для нужной нам оценки
посмотрим, для каких $x$ мы могли сделать замену на $\\geq p$ весов (при
$p \\geq 2$)? Мы всегда добавляем $t+1$ число, то есть $p-1 \\leq t$, то
есть $2^{p-1} \\leq 2^t \\leq с+1$. Значит количество вхождений каждого
из таких $x$ будет $\\geq 2^{p-1}-1$, значит их сумма $\\leq
\\frac{S}{2^{p-1}-1} \\leq \\frac{4S}{2^p}$, значит количество $\\leq
\\sqrt{8S} \\frac{1}{\\sqrt{2}^p}$ (потому что они все различны, как мы
помним). Значит в сумме мы добавим $\\leq \\sqrt{8S}
(\\sum\\limits_{p=2}^{\\log{S}}{\\frac{1}{\\sqrt{2}^p}})$ чисел, что
является $O(\\sqrt{S})$.

**Bonus:** если далее делать рюкзак с помощью $bitset$, то получаем
решение за $O(\\frac{S\\sqrt{S}}{64})$.