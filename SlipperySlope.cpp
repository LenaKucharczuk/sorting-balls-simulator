//
// Created by Lena khan on 2016-02-02.
//

#include "SlipperySlope.h"

using namespace std;

SlipperySlope::SlipperySlope()
{
    show_steps = false;
    quality = 0;
    quality2 = 0;
    quality3 = 0;
    t1 = 0;
    t2 = 0;
    t3 = 0;
}

double SlipperySlope::getT(int algorithm)
{
    switch (algorithm)
    {
        case 1:
            return t1;
        case 2:
            return t2;
        case 3:
            return t3;
        default:
            return 0;
    }
}
void SlipperySlope::quality_reset()
{
    quality = 0;
    quality2 = 0;
    quality3 = 0;
}

int SlipperySlope::getQ(int algorithm)
{
    switch (algorithm)
    {
        case 1:
            return quality;
        case 2:
            return quality2;
        case 3:
            return quality3;
        default:
            return 0;
    }
}

int SlipperySlope::slipSize()
{
    return dataOrginal.size();
}

void SlipperySlope::generateData(int counter, int denominator, int number)	// generator danych
{
    data.clear();
    quality_reset();

    vector<int> randomData1;
    vector<int> randomData2;
    vector<int> randomData3;
    int element, index, previous;
    int diff = denominator - counter;
    if (diff < 2 || diff % 2 != 0)	// korekcja danego prawdopodobienstwa
    {
        denominator *= 2;
        counter *= 2;
        diff = denominator - counter;
    }

    for (int i = 0; i < counter; ++i)
    {
        randomData1.push_back(1);
        randomData2.push_back(2);
        randomData3.push_back(3);
    }
    for (int i = 0; i < diff / 2; ++i)
    {
        randomData1.push_back(2);
        randomData2.push_back(1);
        randomData3.push_back(2);

        randomData1.push_back(3);
        randomData2.push_back(3);
        randomData3.push_back(1);
    }

    int randomBall = rand() % 3 + 1;	// pierwszy element na równych szansach
    previous = randomBall;
    data.push_back(randomBall);

    for (int i = 0; i < number - 1; ++i)
    {
        index = rand() % denominator;

        switch (previous)
        {
            case 1:
                randomBall = randomData1[index];
                break;
            case 2:
                randomBall = randomData2[index];
                break;
            case 3:
                randomBall = randomData3[index];
                break;
        }
        data.push_back(randomBall);
        previous = randomBall;
    }
    data2 = data;
    data3 = data;
    dataOrginal = data;
}

void SlipperySlope::addData()
{
    data.clear();
    quality_reset();
    int element;

    string slope;
    cin.ignore(1000, '\n');
    getline(cin, slope);

    for (int i = 0; i < slope.size(); ++i)
    {
        element = (int)slope[i] - 48;
        data.push_back(element);
    }
    data2 = data;
    data3 = data;
    dataOrginal = data;
}

void SlipperySlope::show(int algorithm)	// 0- dataOrginal
{
    vector<int> vec;
    switch (algorithm)
    {
        case 0:
            vec = dataOrginal;
            break;
        case 1:
            vec = data;
            break;
        case 2:
            vec = data2;
            break;
        case 3:
            vec = data3;
            break;
    }

    cout << endl;
    for (int i = 1; i < vec.size() + 1; ++i)
    {
        cout << vec[i - 1] << " ";
        if (i % 30 == 0)
            cout << endl;
    }
    cout << endl;
}


void SlipperySlope::isOk(int algorithm)
{
    vector<int> check;
    switch (algorithm)
    {
        case 1:
            check = data;
            break;
        case 2:
            check = data2;
            break;
        case 3:
            check = data3;
            break;
    }

    int curr = 1;

    for (int i = 0; i < check.size(); ++i)
    {
        if (check[i] != curr)
        {
            if (curr + 1 == check[i])
                curr = check[i];
            else
            {
                cout << "Algorytm " << algorithm << ": ZLE" << endl;
                cout << "i: " << i << ", biezacy: " << curr << ", nastepny " << check[i] << endl;
                cout << "dane pierwnotne: " << endl;
                show(0);
                show(algorithm);
                return;
            }
        }
    }
    return;
}

bool SlipperySlope::shift(int algorithm, int number, int position)
{
    int element;
    string index;
    switch (algorithm)
    {
        case 1:
            if (number * 3 + position >= data.size())
                return false;
            quality += number;
            int element;
            for (int i = 0; i < number * 3; ++i)
            {
                element = data[position];
                data.push_back(element);
                data.erase(data.begin() + position);

                if (show_steps && (i + 1) % 3 == 0)
                {
                    index.clear();
                    for (int j = 0; j < position * 2; ++j)
                    {
                        index += ' ';
                    }
                    index += '^';
                    cout << index;
                    show(1);
                }
            }
            break;

        case 2:
            if (number * 3 + position >= data2.size())
                return false;
            quality2 += number;
            for (int i = 0; i < number * 3; ++i)
            {
                element = data2[position];
                data2.push_back(element);
                data2.erase(data2.begin() + position);

                if (show_steps && (i + 1) % 3 == 0)
                {
                    index.clear();
                    for (int j = 0; j < (position + ready.size()) * 2; ++j)
                    {
                        index += ' ';
                    }
                    index += '^';
                    cout << index << endl;
                    for (int j = 0; j < ready.size(); ++j)
                        cout << ready[j] << " ";
                    for (int j = 0; j < data2.size(); ++j)
                        cout << data2[j] << " ";
                    cout << endl;
                }
            }
            break;

        case 3:
            if (number * 3 + position >= data3.size())
                return false;
            quality3 += number;
            for (int i = 0; i < number * 3; ++i)
            {
                element = data3[position];
                data3.push_back(element);
                data3.erase(data3.begin() + position);

                if (show_steps && (i + 1) % 3 == 0)
                {
                    index.clear();
                    for (int j = 0; j < (position + ready.size()) * 2; ++j)
                    {
                        index += ' ';
                    }
                    index += '^';
                    cout << index << endl;
                    for (int j = 0; j < ready.size(); ++j)
                        cout << ready[j] << " ";
                    for (int j = 0; j < data3.size(); ++j)
                        cout << data3[j] << " ";
                    cout << endl;
                }
            }
            break;
    }
    return true;
}

// pomocnicze dla algorytmu 1
int SlipperySlope::howMany(int colour, int position, int end)
{
    if (position >= data.size() || end > data.size())
        return 0;

    int howMany = 0;
    for (int i = position; i < end; ++i)
    {
        if (data[i] == colour)
            ++howMany;
    }
    return howMany;
}
bool SlipperySlope::naive(int currentColor, int position, bool lookForCurr)
{
    // jesli brak podanego koloru lub chcemy sortowac na dalej niż 4 pozycji od konca
    if ((lookForCurr && howMany(currentColor, position, data.size()) == 0) || data.size() - position <= 3)
        return false;

    if (!lookForCurr && data.size() - position - howMany(currentColor, position, data.size()) == 0)
        return false;

    if ((lookForCurr == false && data[position] != currentColor) || (lookForCurr == true && data[position] == currentColor))
        return true;

    bool sorted = true;
    while (sorted)
    {
        // wyławiam co trzeci element
        for (int i = position; i < data.size(); i = i + 3)
        {
            thirds.push_back(data[i]);
        }

        // szukam pierwszej currentColor
        for (int i = 0; i < thirds.size(); ++i)
        {
            if (lookForCurr)
            {
                if (thirds[i] == currentColor)
                {
                    sorted = false;
                    shift(1, i, position);	// zsuwam currentColor w dół
                    break;
                }
            }
            else
            {
                if (thirds[i] != currentColor)
                {
                    sorted = false;
                    shift(1, i, position);	// zsuwam currentColor w dół
                    break;
                }
            }
        }

        // nie ma currentColor na co trzecim - przemieszczam trójkę z currentColor tak, aby currentColor znalazło się na miejscu podzielnym przez 3
        if (sorted)
        {
            int modulo = (data.size() - position) % 3;
            int i;

            switch (modulo)
            {
                case 0:
                    for (i = position; i < data.size(); ++i)
                    {
                        if (lookForCurr)
                        {
                            if (data[i] == currentColor)
                            {
                                break;
                            }
                        }
                        else
                        {
                            if (data[i] != currentColor)
                            {
                                break;
                            }
                        }
                    }
                    if (shift(1, 1, i) == false)
                        shift(1, 1, position);
                    break;

                case 1:
                    for (i = position; i < data.size(); ++i)
                    {
                        if (lookForCurr)
                        {
                            if (data[i] == currentColor && i >= 2)
                            {
                                break;
                            }
                        }
                        else
                        {
                            if (data[i] != currentColor && i >= 2)
                            {
                                break;
                            }
                        }
                    }
                    if (i - 2 < position || shift(1, 1, i - 2) == false)
                    {
                        shift(1, 1, position);
                    }

                    break;

                case 2:
                    for (i = position; i < data.size(); ++i)
                    {
                        if (lookForCurr)
                        {
                            if (data[i] == currentColor && i >= 1)
                            {
                                break;
                            }
                        }
                        else
                        {
                            if (data[i] != currentColor && i >= 1)
                            {
                                break;
                            }
                        }
                    }
                    if (i - 1 < position || shift(1, 1, i - 1) == false)
                    {
                        shift(1, 1, position);
                    }
                    break;
            }
        }
        thirds.clear();
    }
    return sorted;
}
bool SlipperySlope::prepare(int modulo, int currentColor, int position)
{
    int number = howMany(currentColor, position, data.size());
    if (number < 5)
        return false;
    switch (modulo)
    {
        case 1:	// ddxdd
            naive(currentColor, position, true);
            naive(currentColor, position + 1, true);
            naive(currentColor, position + 2, false);
            naive(currentColor, position + 3, true);
            naive(currentColor, position + 4, true);
            break;
        case 2:	// dxxdd
            naive(currentColor, position, true);
            naive(currentColor, position + 1, false);
            naive(currentColor, position + 2, false);
            naive(currentColor, position + 3, true);
            naive(currentColor, position + 4, true);
            break;
    }
    return true;
}

// algorytmy sortujace

void SlipperySlope::algorithm1()
{
    // CZAS
    clock_t s, f;
    double czas = 0;
    s = clock();

    int index;
    int currentColor = 1;
    int begin, end;
    int diffBehindEnd;	// liczba kul o kolorze innym niz currentColor lezacych za end
    int diffThanCurr;	// liczba kulek o innym kolorze niz aktualnie sortowany
    int sortingPosition = 0;

    // dwie iteracje- dla 1 i 2
    for (int i = 0; i < 2; ++i)
    {
        begin = data.size(); // o jeden w prawo od przedzialu
        end = data.size();
        diffBehindEnd = 0;	// liczba kul o kolorze innym niz currentColor lezacych za end
        diffThanCurr = data.size() - sortingPosition - howMany(currentColor, sortingPosition, data.size());	// liczba kulek o innym kolorze niz aktualnie sortowany

        if (howMany(currentColor, sortingPosition, data.size()) < 5)	// jesli kul sortowanego koloru jest mniej niz 5, sortuj naiwnie
        {
            int howManyCurr = howMany(currentColor, sortingPosition, data.size());
            for (int j = 0; j < howManyCurr; ++j)
            {
                naive(currentColor, sortingPosition + j, true);
            }
        }
        else
        {
            if (diffThanCurr % 3 != 0)
            {
                if (diffThanCurr % 3 == 1)
                    prepare(1, currentColor, sortingPosition);	// ddxdd
                else
                    prepare(2, currentColor, sortingPosition);	// dxxdd
            }

            int howLong = 0;
            if (diffThanCurr % 3 != 0)
            {
                howLong = 5;
            }

            do
            {
                begin = begin - 3;
                if (begin < sortingPosition)
                    begin = sortingPosition;
                if (howMany(currentColor, begin, begin + 3) != 0)	// znaleziono currentColour
                {
                    shift(1, 1, begin);
                    end = end - 3;
                    diffBehindEnd = data.size() - end - howMany(currentColor, end, data.size());

                    if (diffBehindEnd >= 3)
                    {
                        naive(currentColor, end, false);
                        naive(currentColor, end + 1, false);
                        naive(currentColor, end + 2, false);
                        end = end + 3;
                    }
                }
            } while (begin > sortingPosition + howLong);

            naive(currentColor, end, false);
            naive(currentColor, end + 1, false);
            naive(currentColor, end + 2, false);

            if (diffThanCurr % 3 != 0)
                shift(1, 1, sortingPosition);

            index = sortingPosition;
            while (data[index] == currentColor)
                ++index;
            while (data[index] != currentColor)
            {
                shift(1, 1, index);
            }
        }

        currentColor = 2;
        sortingPosition = howMany(1, 0, data.size());
    }

    // czas
    f = clock();
    czas = (double)(f - s) / (double)(CLOCKS_PER_SEC);
    t1 = czas;
}

void SlipperySlope::algorithm2()
{
    bool sorted = false;
    int currentColor = 1;

    // CZAS
    clock_t s, f;
    double czas = 0;
    s = clock();

    if (howMany(3, 0, data2.size()) <3)
    {
        cout << "sortowanie sie nie powiedzie" << endl;
        return;
    }

    while (!sorted && data2.size() > 3)
    {
        // przerzucam posortowaną część do vectora ready
        while (data2[0] == currentColor)
        {
            ready.push_back(data2[0]);
            data2.erase(data2.begin());
        }

        // wyławiam co trzeci element
        for (int i = 0; i < data2.size(); i = i + 3)
        {
            thirds.push_back(data2[i]);
        }

        sorted = true;

        // szukam optymalnego wystapienia currentColor (najdluzszej sekwencji currentColor)
        int bestNumber = 0;	// najoptymalniejsza liczba poczynionych przesuniec trojek kulek (czyli znajdujacych sie przed najdluzsza
        // sekwencja currentColor)
        int bestHowMany = 0;	// najdluzsza sekwencja currentColor
        for (int i = 0; i < thirds.size(); ++i)
        {
            // gdy znajde currentColor w thirds, sprawdzam
            if (thirds[i] == currentColor)	// zliczam ile currentColor w howMany
            {
                int howMany = 0;	// zliczanie sekwencji currentColor
                int j = i * 3;
                sorted = false;

                while (j < data2.size() && data2[j] == currentColor)	// zliczam dlugosc sekwencji currentColor
                {
                    ++howMany;
                    ++j;
                }
                cout << "howMany: "<<howMany << endl;
                if (bestHowMany < howMany)	// sprawdzam czy lepsza od dotychczas najlepszej znalezionej
                {
                    bestHowMany = howMany;
                    bestNumber = i;
                }
            }
        }

        if (!sorted)
            shift(2, bestNumber, 0);	// zsuwam currentColor w dół
        else // nie ma currentColor na co trzecim
        {
            int modulo = data2.size() % 3;
            int i;

            switch (modulo)
            {
                case 0:
                    for (i = 0; i < data2.size(); ++i)
                    {
                        if (data2[i] == currentColor)
                        {
                            break;
                        }
                    }
                    if (shift(2, 1, i) == false)
                        shift(2, 1, 0);
                    break;

                case 1:
                    for (i = 0; i < data2.size(); ++i)
                    {
                        if (data2[i] == currentColor && i >= 2)
                        {
                            break;
                        }
                    }
                    if (shift(2, 1, i - 2) == false)
                        shift(2, 1, 0);
                    break;

                case 2:
                    for (i = 0; i < data2.size(); ++i)
                    {
                        if (data2[i] == currentColor && i >= 1)
                        {
                            break;
                        }
                    }
                    if (shift(2, 1, i - 1) == false)
                        shift(2, 1, 0);
                    break;
            }
        }

        if (find(data2.begin(), data2.end(), currentColor) != data2.end())	// znaleziono sortowany kolor w data2
        {
            sorted = false;
        }
        else   // nie znaleziono sortowanego koloru
        {
            if (currentColor < 2)
            {
                ++currentColor;
                sorted = false;
            }
            else
                break;
        }
        thirds.clear();
    }

    for (int i = 0; i < data2.size(); ++i)
        ready.push_back(data2[i]);

    data2 = ready;

    f = clock();
    czas = (double)(f - s) / (double)(CLOCKS_PER_SEC);
    t2 = czas;

    ready.clear();
    thirds.clear();
}

void SlipperySlope::algorithm3()
{
    // CZAS
    clock_t s, f;
    double czas = 0;
    s = clock();

    if (howMany(3, 0, data3.size()) <3)
    {
        cout << "sortowanie sie nie powiedzie" << endl;
        return;
    }

    bool sorted = false;
    int currentColor = 1;
    while (!sorted && data3.size() > 3)
    {
        // przerzucam posortowaną część do vectora ready
        while (data3[0] == currentColor)
        {
            ready.push_back(data3[0]);
            data3.erase(data3.begin());
        }

        // wyławiam co trzeci element
        for (int i = 0; i < data3.size(); i = i + 3)
        {
            thirds.push_back(data3[i]);
        }

        sorted = true;
        // szukam pierwszego currentColor
        for (int i = 0; i < thirds.size(); ++i)
        {
            if (thirds[i] == currentColor)
            {
                sorted = false;
                shift(3, i, 0);	// zsuwam currentColor w dół
                break;
            }
        }

        // nie ma currentColor na co trzecim - przemieszczam trójkę z currentColor tak, aby currentColor znalazło się na miejscu podzielnym przez 3
        if (sorted)
        {
            int modulo = data3.size() % 3;
            int i;

            switch (modulo)	// w zależoności od reszty z dzielenia liczby elementów przez 3
            {
                case 0:		// biorę trójkę, w której currentColor występuje na 1 miejscu
                    for (i = 0; i < data3.size(); ++i)
                    {
                        if (data3[i] == currentColor)
                        {
                            break;
                        }
                    }
                    if (shift(3, 1, i) == false)
                        shift(3, 1, 0);
                    break;

                case 1:		// biorę trójkę, w której currentColor występuje na 3 miejscu
                    for (i = 0; i < data3.size(); ++i)
                    {
                        if (data3[i] == currentColor && i >= 2)
                        {
                            break;
                        }
                    }
                    if (shift(3, 1, i - 2) == false)
                        shift(3, 1, 0);
                    break;

                case 2:		// biorę trójkę, w której currentColor występuje na 2 miejscu
                    for (i = 0; i < data3.size(); ++i)
                    {
                        if (data3[i] == currentColor && i >= 1)
                        {
                            break;
                        }
                    }
                    if (shift(3, 1, i - 1) == false)
                        shift(3, 1, 0);
                    break;
            }
        }

        if (find(data3.begin(), data3.end(), currentColor) != data3.end())	// znaleziono sortowany kolor w data3
        {
            sorted = false;	// wciaz sortuje currentColor
        }
        else   // nie znaleziono sortowanego elementu
        {
            if (currentColor < 2)	// jesli wlasnie sortowano jedynki
            {
                ++currentColor;		// teraz sortuje dwojki
                sorted = false;
            }
            else		// posortowano juz dwojki, wiec koniec sortowania
                break;
        }
        thirds.clear();
    }

    for (int i = 0; i < data3.size(); ++i)
        ready.push_back(data3[i]);

    data3 = ready;

    f = clock();
    czas = (double)(f - s) / (double)(CLOCKS_PER_SEC);
    t3 = czas;

    ready.clear();
    thirds.clear();
}