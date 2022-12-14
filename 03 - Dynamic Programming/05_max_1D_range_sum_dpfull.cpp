#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef struct
{
    float max_sum;
    string max_range;
} Answer;

Answer max_1d_range_sum(float *A, int *Min, int n)
{
    float M[n + 1], S = 0.0;
    string R[n + 1], cad = "";

    M[0] = 0;
    R[0] = "";
    for (int i = 1; i <= n; i++)
    {
        S += A[i - 1];

        if (S > A[i - 1])
            cad += "-" + to_string(Min[i - 1]);
        else
            cad = to_string(Min[i - 1]);
        S = max(S, A[i - 1]);

        if (S > M[i - 1])
            R[i] = cad;
        else
            R[i] = R[i - 1];
        M[i] = max(S, M[i - 1]);
    }

    Answer res;
    res.max_sum = M[n];
    res.max_range = R[n];
    return res;
}

int main(void)
{
    /**Declaracion de variables auxiliares
     * int n: longitud de registros
     * int dato: auxiliar para guardar un dato leido
     */

    int n, registros;

    ifstream file;
    file.open("espatulas.txt");

    // Comprobamos primero que el archivo se pudo leer
    if (!file)
    {
        cout << "Can't open input file.\n";
        return 1;
    }
    
    // Usamos un while loop para recorrer el archivo
    while (file >> registros)
    {
        n = registros;   // Guardamos la cantidad de registros de la tienda
        int Min[n]; // Arreglo para guardar rango de minutos de venta
        float A[n]; // Arreglo para guardar ganancia por venta
        for (int i = 0; i < n; i++)
        {
            file >> Min[i];
            file >> A[i];
        }

        Answer respuesta = max_1d_range_sum(A, Min, n);

        cout << "El resultado máximo es: " << respuesta.max_sum << ", y ocurre en el rango: " << respuesta.max_range << ".\n";
    }

    // Close the file
    file.close();
    return 0;
}