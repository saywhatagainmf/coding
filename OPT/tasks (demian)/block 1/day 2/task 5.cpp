/*
    В кинотеатре места часто расставляют со сдвигом соседних
    рядов для удобства зрителей. Пусть в таком кинотеатре N мест
    в 1-м, 3-м, 5-м и всех нечётных рядах и N + 1 место во 2-м,
    4-м и всех чётных рядах.

    Места в рядах нумеруются от 1 до N в нечётных рядах и
    от 1 до N + 1 в чётных рядах.

    Касса продаёт билеты подряд: сначала в 1-й ряд на места
    с 1-го по N-е, потом — во 2-й ряд на места с 1-го по N +1-е,
    затем в 3-й ряд с 1-го места и т.д.

    Определите номер ряда и номер места для K-го проданного билета

    Ввод:               Ввод:
        10 25               5 14
    Вывод:              Вывод:
        3 4                 3 3
*/

int n, k;
cin >> n >> k;

k = k - 1;

int par = k / (2 * n + 1);
k = k % (2 * n + 1);

if (k < n)
    cout << 2 * par + 1 << " " << k + 1 << '\n';
else {
    cout << 2 * par + 2 << " " << k + 1 - n << '\n';
}