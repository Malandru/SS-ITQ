#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#define MAXCNDTS 2
using namespace std;

int F, C, N, T;
bool finished;
typedef vector< vector<int> > matriz;

class Ficha
{
    int x, y;
    bool free;
public:
    void set_freedom(bool free)
    { this->free = free; }

    bool is_free()
    { return free; }

    void imprimir()
    { cout << "[" << x << "|" << y << "]\n"; }

    void add_ficha(int x, int y)
    { x > y ? set_xy(y, x) : set_xy(x, y); }

    int get_position() //Posicion del cand en el array de fichas
    { return y * (y + 1) / 2 + x; }
    //METODOS DE COORDENADAS
    void set_xy(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    int fila()
    { return x; }

    int columna()
    { return y; }

    bool out_range()
    { return x < 0 || x >= F || y < 0 || y >= C; }
};

typedef vector<Ficha> array;
array fichas;
/*
-- k: profundidad
-- cand: vector de candidatos
-- coord: vector de coordenadas
-- c: total de candidatos
-- input: matriz de entrada
-- i, j: posicion en la matriz input
*/

//---------BACKTRACKING----------
bool es_solucion(int); //(k)
void procesar_solucion();
//(k, cand, coord, c, input, i, j)
void crt_cndts(int, array&, array&, int&, matriz, int&, int&);
//(k, input, i, j)
void backtrack(int, matriz, int, int);

//---------METODOS DE AYUDA----------
void modificar(matriz&, int&, int&); //(input, i, j)
void init(matriz&);
void crear_fichas();

int main()
{
    matriz input;
    int casos;
    cin >> casos;
    for(int i = 0; i < casos; i++)
    {
        init(input);
        backtrack(0, input, 0, 0);
        cout << (finished ? "SI" : "NO") << endl;
    }
    return 0;
}

//---------BACKTRACKING----------
bool es_solucion(int k)
{ return k == F * C / 2; }

void procesar_solucion()
{
    finished = true;
}

void crt_cndts(int k, array &cand, array &coord, int &c, matriz input, int& i, int& j)
{
    c = 0;
    Ficha aux;
    array puntos(MAXCNDTS);
    while(input[i][j] == -1)
        modificar(input, i, j);
    int x = input[i][j];
    puntos[0].set_xy(i, j + 1);
    puntos[1].set_xy(i + 1, j);
    for(int m = 0; m < MAXCNDTS; m++)
        if(!puntos[m].out_range())
        {
            aux.add_ficha(x, input[puntos[m].fila()][puntos[m].columna()]);
            int p = aux.get_position();
            //cout << "Posicion a buscar: " << p << endl;
            if(fichas[p].is_free())
            {
                c++;
                cand.push_back(fichas[p]);
                coord.push_back(puntos[m]);
                continue;
            }
        }
    /*
    cout << "Total de candidatos: " << cand.size() << endl;
    for(int m = 0; m < cand.size(); m++)
        cand[m].imprimir();
    cin.get();
    getchar();*/
}

void backtrack(int k, matriz input, int i, int j)
{
    array cand, coord;
    int c, p; //candidatos, posicion
    if(es_solucion(k))
        procesar_solucion();
    else if(i < F)
    {
        int *a, temp;
        crt_cndts(k++, cand, coord, c, input, i, j);
        modificar(input, i, j);
        for(int x = 0; x < c; x++)
        {
            a = &input[coord[x].fila()][coord[x].columna()];
            temp = *a;
            *a = -1;
            p = cand[x].get_position();
            fichas[p].set_freedom(false);
            backtrack(k, input, i, j);
            fichas[p].set_freedom(true);
            *a = temp;
        }
    }
}

//---------METODOS DE AYUDA----------
void modificar(matriz& input, int& i, int& j)
{
    input[i][j] = -1;
    if(++j == C)
    {
        j = 0;
        i++;
    }
}

void init(matriz &input)
{
    cin >> N;
    T = (N + 1) * (N + 2) / 2;
    crear_fichas();
    cin >> F;
    input.resize(F);
    cin >> C;
    for(int i = 0; i < F; i++)
    {
        input[i].resize(C);
        for(int j = 0; j < C; j++)
            cin >> input[i][j];
    }
    finished = false;
}

void crear_fichas()
{
    Ficha ficha;
    for(int i = 0; i <= N; i++)
        for(int j = 0; j <= i; j++)
        {
            ficha.add_ficha(j, i);
            ficha.set_freedom(true);
            fichas.push_back(ficha);
        }
}