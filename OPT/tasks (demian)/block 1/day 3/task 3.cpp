/*
    Близнецам Петру и Павлу родители подарили на день рождения
    настольный футбол, но не простой, а линейный.

    В этом варианте игры все фигурки игроков расположены в одну
    линию на равном расстоянии друг от друга. Всего есть n игроков.
    Для определенности пронумеруем их позиции числами от 1 до n
    слева направо. Ворота находятся в позициях 0 и n + 1. Каждый игрок
    имеет свою силу удара, и может при ударе по мячу перебросить его
    на фиксированное количество позиций другому игроку. Силу удара игрока
    на позиции i обозначим через ai, что означает, что после удара этого
    игрока мяч переместится на ai позиций. Если ai положительное, то мяч
    переместится вправо, в сторону увеличения номеров, а если ai отрицательное,
    то мяч переместится влево, в сторону уменьшения. Если после удара мяч
    попадает в позицию меньшую либо равную 0, то засчитывается гол в левые
    ворота, а если в позицию большую либо равную n + 1, то в правые.
    Если после удара мяч попадает к другому игроку, то тот наносит следующий
    удар со своей силой, и игра продолжается.

    Близнецы решили сыграть n игр, в i-й из которых первый удар нанесёт
    игрок номер i. Для каждой игры выведите, в какие ворота будет забит
    мяч в этой игре (L, если в левые, R, если в правые, U, если гол никто
    не забьёт).
*/

int n;
cin >> n;

vector<int> powers(n + 2);

for (int i{1}; i <= n; i++) {
    int ai;
    cin >> ai;
    powers[i] = ai;
}

for (int player{1}; player <= n; player++) {
    int position = player;
    vector<int> way = {position};

    while (true) {
        position = position + powers[position];
        if (position <= 0) {
            cout << "L";
            break;
        } else if (position > n) {
            cout << "R";
            break;
        } else {
            if (find(way.begin(), way.end(), position) != way.end() ||
                powers[position] == 0) {
                cout << "R";
                break;
            } else {
                way.push_back(position);
            }
        }
    }
}
cout << '\n';