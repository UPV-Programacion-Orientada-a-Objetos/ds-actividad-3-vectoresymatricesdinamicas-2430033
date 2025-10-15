#include <iostream>
using namespace std;

int main() {
    const int productos = 5;
    const int materias = 4;

    // Matriz dinámica de planificación (5x4 semanas)
    int semanas = 4;
    float** plan = new float*[productos];
    for (int i = 0; i < productos; i++) {
        plan[i] = new float[semanas];
        for (int j = 0; j < semanas; j++)
            plan[i][j] = 0;
    }

    // Vector dinámico de costos unitarios
    float* costoProd = new float[productos];
    for (int i = 0; i < productos; i++)
        costoProd[i] = 5 + i; // valores ejemplo

    // Vector dinámico de materia prima inicial
    float* matPrima = new float[materias];
    for (int i = 0; i < materias; i++)
        matPrima[i] = 1000; // stock inicial

    // Vector estático de requerimientos (productos x materias)
    int req[5][4] = {
        {2,1,0,1},
        {1,2,1,0},
        {3,0,1,2},
        {2,1,2,1},
        {1,1,1,1}
    };

    int op;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Ver plan\n";
        cout << "2. Agregar semana\n";
        cout << "3. Modificar produccion\n";
        cout << "4. Calcular COGS\n";
        cout << "5. Salir\n";
        cout << "Opcion: ";
        cin >> op;

        if (op == 1) {
            cout << "\nPlan de Produccion (" << productos << "x" << semanas << ")\n";
            for (int i = 0; i < productos; i++) {
                cout << "Producto " << i << ": ";
                for (int j = 0; j < semanas; j++)
                    cout << plan[i][j] << " ";
                cout << endl;
            }
        }

        else if (op == 2) {
            // redimensionar matriz (agregar columna)
            float** nuevo = new float*[productos];
            for (int i = 0; i < productos; i++) {
                nuevo[i] = new float[semanas + 1];
                for (int j = 0; j < semanas; j++)
                    nuevo[i][j] = plan[i][j];
                nuevo[i][semanas] = 0; // nueva semana
            }
            for (int i = 0; i < productos; i++)
                delete[] plan[i];
            delete[] plan;
            plan = nuevo;
            semanas++;
            cout << "Semana agregada. Ahora hay " << semanas << " semanas.\n";
        }

        else if (op == 3) {
            int p, s;
            float cant;
            cout << "Producto (0-" << productos-1 << "): ";
            cin >> p;
            cout << "Semana (0-" << semanas-1 << "): ";
            cin >> s;
            cout << "Cantidad: ";
            cin >> cant;
            if (p>=0 && p<productos && s>=0 && s<semanas)
                plan[p][s] = cant;
            else
                cout << "Fuera de rango.\n";
        }

        else if (op == 4) {
            int s;
            cout << "Semana a calcular (0-" << semanas-1 << "): ";
            cin >> s;
            if (s<0 || s>=semanas) {
                cout << "Semana invalida.\n";
                continue;
            }

            // Calcular consumo de MP
            float consumo[materias] = {0};
            for (int p = 0; p < productos; p++) {
                for (int m = 0; m < materias; m++) {
                    consumo[m] += plan[p][s] * req[p][m];
                }
            }

            // Calcular COGS (simplificado)
            float totalProd = 0;
            float cogs = 0;
            for (int p = 0; p < productos; p++) {
                totalProd += plan[p][s];
                cogs += plan[p][s] * costoProd[p];
            }

            // Inventario final estimado
            float invFinal = 0;
            for (int m = 0; m < materias; m++) {
                float restante = matPrima[m] - consumo[m];
                if (restante < 0) restante = 0;
                invFinal += restante;
            }

            cout << "\n--- Reporte Semana " << s << " ---\n";
            cout << "Produccion total: " << totalProd << " unidades\n";
            cout << "COGS (costo total): $" << cogs << endl;
            cout << "Consumo Materias:\n";
            for (int m = 0; m < materias; m++)
                cout << "MP" << m << ": " << consumo[m] << endl;
            cout << "Inventario Final Estimado: " << invFinal << endl;
        }

    } while (op != 5);

    // Liberar memoria
    for (int i = 0; i < productos; i++)
        delete[] plan[i];
    delete[] plan;
    delete[] costoProd;
    delete[] matPrima;

    cout << "Memoria liberada. Fin del programa.\n";
    return 0;
}

