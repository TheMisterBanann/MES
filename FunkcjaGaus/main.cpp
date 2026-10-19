#include <iostream>


float JedenPunkt();
float DwaPunkty();
float TrzyPunkty();
float WielePunktow();
float CalkowanieProstokaty(int liczbaP, float start, float end);

int main(){

    std::cout << CalkowanieProstokaty(10,-2,6);

    std::cout << "\n u gory";

    return 0;
}

float funkcja(float x){
    float wynik = 5 * x * x + 3*x + 6;
    return wynik;
}


float CalkowanieProstokaty(int liczbaP, float start, float end){
    float calka=0;
    float wymiar = (end - start)/ (liczbaP);
    float punkt = wymiar/2;
    int j = 0;
    for(float i = start; i<end; i+= wymiar){
        calka+= wymiar * funkcja(start + punkt+wymiar*j);
        j+=1;
    }
    return calka;
}



float JedenPunkt(){


    return 0;
}


float DwaPunkty(){


    return 0;
}



float TrzyPunkty(){


    return 0;
}



float WielePunktow(){


    return 0;
}