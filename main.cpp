#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "SlipperySlope.h"

using namespace std;

unsigned int asymptote(int algorithm, int n)
{
    switch (algorithm)
    {
        case 1:
            return n*n;
        case 2:
            return n*n;
        case 3:
            return n*n;
    }
}

int main()
{
    srand(time(NULL));

    SlipperySlope Slip;
    SlipperySlope Mediana;
    vector<SlipperySlope> Slips;

    int choice;
    int min_size, max_size, size=0, jump, algorithm;
    int number;
    string poss;

    int n; // rozmiar problemu
    unsigned int TnMediana, nMediana;
    double Tn, tnMediana, q;

    cout << "Program sluzy do symulacji sortowania kul w 3 kolorach lezacych na rowni" << endl;
    cout << "pochylej. Maszyna sortujaca moze przenosic kule trojkami i umieszczac je" << endl;
    cout << "na szczycie rowni. Kule maja byc zgrupowane wg tych samych kolorow." << endl << endl;

    do
    {
        cout << "Tryby wykonania programu: " << endl;
        cout << "   1 - dane dostarczone ze strumienia wejsciowego" << endl;
        cout << "   2 - dane generowane automatycznie" << endl;
        cout << "   3 - wykonanie z prezentacja wynikow pomiarow" << endl;
        cout << "   0 - wyjdz z programu" << endl;
        cout << endl << "Wybierz tryb wykonania: ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
            case 1:
                cout << "Podaj ciag kul bez odstepow: ";
                Slip.addData();
                Slip.show_steps = true;	// pokaz krok po kroku
                do {
                    cout << endl;
                    cout << "   1 - Algorytm naiwny, ulepszony" << endl;
                    cout << "   2 - Algorytm 'najdluzsza sekwencja'" << endl;
                    cout << "   3 - Algorytm naiwny" << endl;
                    cout << "   4 - Wszystkie po kolei" << endl;
                    cout << "   5 - Wyswietl dane" << endl;
                    cout << "   0 - Zaden, wroc do menu" << endl;
                    cout << endl << "Wybierz testowany algorytm: ";
                    cin >> algorithm;
                    cout << endl;

                    switch (algorithm)
                    {
                        case 1:
                            Slip.show(1);
                            Slip.algorithm1();
                            Slip.isOk(1);
                            cout << "Jakosc algorytmu: " << Slip.getQ(1) << endl;
                            break;
                        case 2:
                            Slip.show(2);
                            Slip.algorithm2();
                            Slip.isOk(2);
                            cout << "Jakosc algorytmu: " << Slip.getQ(2) << endl;
                            break;
                        case 3:
                            Slip.show(3);
                            Slip.algorithm3();
                            Slip.isOk(3);
                            cout << "Jakosc algorytmu: " << Slip.getQ(1) << endl;
                            break;
                        case 4:
                            Slip.algorithm1();
                            Slip.algorithm2();
                            Slip.algorithm3();
                            Slip.isOk(1);
                            Slip.isOk(2);
                            Slip.isOk(3);
                            break;
                        case 5:
                            cout << "Dane wejsciowe: ";
                            Slip.show(0);
                            cout << "Dane algorytmu 1: ";
                            Slip.show(1);
                            cout << "Dane algorytmu 2: ";
                            Slip.show(2);
                            cout << "Dane algorytmu 3: ";
                            Slip.show(3);
                            break;
                        default:
                            break;
                    }
                } while (algorithm);
                break;

            case 2:
                int counter, denominator;
                Slip.show_steps = false;
                cout << "Podaj rozmiar problemu: ";
                cin >> size;
                cout << endl << "Podaj licznik i mianownik prawdopodobienstwa, z jakim maja powtarzac sie te same kolory: "<<endl;
                cin.ignore(1000, '\n');
                getline(cin, poss);
                if (poss.empty())	// enter
                {
                    cout << "domyslne prawdopodobienstwo" << endl;
                    counter = 1;
                    denominator = 3;
                }
                else
                {
                    counter = atoi(poss.c_str());
                    cin >> denominator;
                }
                Slip.generateData(counter, denominator, size);
                do {
                    cout << endl;
                    cout << "   1 - Algorytm naiwny, ulepszony" << endl;
                    cout << "   2 - Algorytm 'najdluzsza sekwencja'" << endl;
                    cout << "   3 - Algorytm naiwny" << endl;
                    cout << "   4 - Wszystkie po kolei" << endl;
                    cout << "   0 - Zaden, wroc do menu" << endl;
                    cout << endl << "Wybierz testowany algorytm: ";
                    cin >> algorithm;
                    cout << endl;

                    switch (algorithm)
                    {
                        case 1:
                            Slip.algorithm1();
                            Slip.isOk(1);
                            break;
                        case 2:
                            Slip.algorithm2();
                            Slip.isOk(2);
                            break;
                        case 3:
                            Slip.algorithm3();
                            Slip.isOk(3);
                            break;
                        case 4:
                            Slip.algorithm1();
                            Slip.algorithm2();
                            Slip.algorithm3();
                            Slip.isOk(1);
                            Slip.isOk(2);
                            Slip.isOk(3);
                            break;
                        default:
                            break;
                    }
                } while (algorithm);
                break;

            case 3:
                Slip.show_steps = false;
                cout << endl << "Podaj licznik i mianownik prawdopodobienstwa, z jakim maja powtarzac sie te same kolory ";
                cout << "lub wcisnij enter dla P= 1/3:" << endl;
                cin.ignore(1000, '\n');
                getline(cin, poss);
                if (poss.empty())	// enter
                {
                    cout << "domyslne prawdopodobienstwo" << endl << endl;;
                    counter = 1;
                    denominator = 3;
                }
                else
                {
                    counter = atoi(poss.c_str());
                    cin >> denominator;
                }
                number = 0;
                cout << "Podaj min rozmiar problemu: ";
                cin >> min_size;
                cout << "Podaj max rozmiar problemu: ";
                cin >> max_size;
                cout << "Podaj skok: ";
                cin >> jump;
                size = min_size;
                while (size <= max_size)
                {
                    SlipperySlope TempSlip;
                    TempSlip.generateData(counter, denominator, size);
                    Slips.push_back(TempSlip);
                    ++number;
                    size += jump;
                }
                nMediana = number%2 ? Slips[number/2].slipSize() : (Slips[(number-1) / 2].slipSize() + Slips[(number-1) / 2 + 1].slipSize()) / 2;

                cout << "Mediana = " << nMediana << endl;
                do {
                    cout << endl;
                    cout << "   1 - Algorytm naiwny, ulepszony" << endl;
                    cout << "   2 - Algorytm 'najdluzsza sekwencja'" << endl;
                    cout << "   3 - Algorytm naiwny" << endl;
                    cout << "   0 - Zaden, wroc do menu" << endl;
                    cout << endl << "Wybierz testowany algorytm: ";
                    cin >> algorithm;
                    cout << endl;

                    switch (algorithm)
                    {
                        case 0:
                            Slips.clear();
                            break;
                        case 1:
                        case 2:
                        case 3:
                            switch (algorithm)
                            {
                                case 1:
                                    for (int j = 0; j < number; ++j)
                                    {
                                        Slips[j].algorithm1();
                                    }
                                    break;
                                case 2:
                                    for (int j = 0; j < number; ++j)
                                    {
                                        Slips[j].algorithm2();
                                    }
                                    break;
                                case 3:
                                    for (int j = 0; j < number; ++j)
                                    {
                                        Slips[j].algorithm3();
                                    }
                                    break;
                            }

                            if (number % 2 == 0)
                            {
                                Mediana.generateData(counter, denominator, nMediana);

                                switch (algorithm)
                                {
                                    case 1:
                                        Mediana.algorithm1(); break;
                                    case 2:
                                        Mediana.algorithm2(); break;
                                    case 3:
                                        Mediana.algorithm3(); break;
                                }
                                tnMediana = Mediana.getT(algorithm);
                                TnMediana = asymptote(algorithm, nMediana);
                            }
                            else// mediana na n/2
                            {
                                tnMediana = Slips[number / 2].getT(algorithm);
                                TnMediana = asymptote(algorithm, Slips[number / 2].slipSize());
                            }
                            cout << "tnMediana: " << tnMediana << " TnMediana: " << TnMediana << endl;

                            cout << "n " << "\tt(n)" << "\tq(n)" << endl;
                            cout << "-----------------------" << endl;
                            for (int j = 0; j < number; ++j)
                            {
                                double Tn = (double)asymptote(algorithm, Slips[j].slipSize());
                                q = (Slips[j].getT(algorithm)*TnMediana) / (Tn *tnMediana);
                                cout << Slips[j].slipSize() << "  \t";
                                cout << Slips[j].getT(algorithm) << " \t";
                                cout << q << endl;
                                if (number % 2 == 0 && j == number / 2 - 1)
                                {
                                    cout << Mediana.slipSize() << "  \t";
                                    cout << Mediana.getT(algorithm) << "  \t";
                                    cout << 1 << endl;
                                }
                            }

                            cout << endl;
                            for (int j = 0; j < number; ++j)
                            {
                                Slips[j].isOk(algorithm);
                            }
                            break;

                        default:
                            break;
                    }
                } while (algorithm);

                break;

            case 0:
                cout << "Zamykam program" << endl;
                break;

            default:
                cout << "Operacja jest niemozliwa do wykonania!" << endl;
                break;
        }
        cout << endl << endl;
    } while (choice);


    system("pause");
    return 0;
}

