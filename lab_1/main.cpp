/*
 ntask = (nvar - 1) mod 11 + 1      ntask = (3 - 1) mod 11 + 1 = 3
 Канцелярские принадлежности
 1) Карандаш (плотность грифеля - целое, цвет - перечислимый тип)
 2) Ручка (тип {шариковая, гелевая}, диаметр стержня - дробное)
 3) Бумага (плотность - целое, ширина и высота листа - целые).
 Цена - дробное
 Номер телефона владельца
 
 ncont = ((nvar - 1) div 12) mod 3 + 1      ncont = ((3 - 1) div 12) mod 3 + 1 = 1
 Однонаправленный кольцевой список
 */
//  Created by Андрей Давыдов on 29.09.2023.
//

#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <vector>

using namespace std;

struct Base {
    string Name;
    double PRICE = 0.0; // цена
    string PHONE;       // телефон владельца
    
    Base(string& Name_, double& PRICE_, string& PHONE_) : Name(Name_), PRICE(PRICE_), PHONE(PHONE_) {}
    
    virtual void print() = 0;
};

enum colour {black, white, red, orange, yellow, green, blue, purple}; // перечислимый тип для цвета
enum pen_type {ballpoint, gel}; // перечислимый тип типа ручки (шариковая/гелевая соответственно)

auto chek_colour(string& Colour){
    colour Colour_;
    if (Colour == "black") Colour_ = black;
    else if (Colour == "white") Colour_ = white;
    else if (Colour == "red") Colour_ = red;
    else if (Colour == "orange") Colour_ = orange;
    else if (Colour == "yellow") Colour_ = yellow;
    else if (Colour == "green") Colour_ = green;
    else if (Colour == "blue") Colour_ = blue;
    else if (Colour == "purple") Colour_ = purple;
    else { cout << "Цвет карандаша " << Colour << " не соответсвует допустимому\n"; exit(0);}
    return Colour_;
}
auto chek_type(string& Type){
    pen_type Type_;
    if (Type == "ballpoint") Type_ = ballpoint;
    else if (Type == "gel") Type_ = gel;
    else { cout << "Тип ручки " << Type << " не соответсвует допустимому\n"; exit(0);}
    return Type_;
}

struct pencil : public Base{           // класс объекта "Карандаш"
    int Plotnost;              // плотность грифеля
    colour COLOUR;         // цвет карандаша
    
    pencil(string& Name_, int Plotnost_, colour COLOUR_, double& PRICE_, string& PHONE_)
    : Plotnost(Plotnost_), COLOUR(COLOUR_), Base(Name_, PRICE_, PHONE_) {}
    //delete
    void print() // функция вывода объекта на экран
    {
        cout << Name << ": Плотность " << Plotnost << "   Цвет ";
        switch (COLOUR) {
            case 0: cout << "черный"; break;
            case 1: cout << "белый"; break;
            case 2: cout << "красный"; break;
            case 3: cout << "оранжевый"; break;
            case 4: cout << "желтый"; break;
            case 5: cout << "зеленый"; break;
            case 6: cout << "синий"; break;
            default: cout << "фиолетовый"; break;
        }
        cout << "   Цена " << PRICE << "   Мобила " << PHONE << "\n\n";
    }
};

struct pen : public Base{           // класс объекта "Ручка"
    pen_type TYP;       // тип ручки (шар/гел)
    double DIAM;  // диаметр стержня
    
    pen(string& Name_, pen_type TYP_, double DIAM_, double& PRICE_, string& PHONE_)
    : TYP(TYP_), DIAM(DIAM_), Base(Name_, PRICE_, PHONE_) {}
    
    void print() // функция вывода объекта на экран
    {
        cout << Name << ": Тип ";
        switch (TYP) {
            case 0: cout << "шариковая"; break;
            default: cout << "гелевая"; break;
        }
        cout << "   Диаметр " << DIAM << "   Цена " << PRICE << "   Мобила " << PHONE << "\n\n";
    }
};

struct paper : public Base{           // класс объекта "Ручка"
    int Plotnost, Width, Height;        // плотность, ширина, высота
    
    paper(string& Name_, int Plotnost_, int Width_, int Height_, double& PRICE_, string& PHONE_)
    : Plotnost(Plotnost_), Width(Width_), Height(Height_), Base(Name_, PRICE_, PHONE_) {}
    
    void print() // функция вывода объекта на экран
    {
        cout << Name << ": Плотность " << Plotnost << "   Ширина " << Width << "   Высота " << Height << "   Цена " << PRICE << "   Мобила " << PHONE << "\n\n";
    }
};

void for_pencil(list<Base*>& values, stringstream& word){
    int Plotnost;
    string Colour, PHONE, Name="Карандаш"; // буферы для цвета и телефона
    double PRICE;
    colour Colour_;
    word >> Plotnost >> Colour >> PRICE >> PHONE; // чтение: плотность, цвет, цена, телефон
    Colour_ = chek_colour(Colour);
    values.push_back(new pencil(Name, PRICE, Colour_, PRICE, PHONE)); // новое звено списка с содержимым объекта Карандаш
}

void for_pen(list<Base*>& values, stringstream& word){
    pen_type Type_; // буфер для типа ручки
    string Type, PHONE, Name="Ручка"; // буферы для цвета и телефона
    double DIAM, PRICE;
    word >> Type >> DIAM >> PRICE >> PHONE; // чтение: тип, диаметр, цена, телефон
    Type_ = chek_type(Type);
    values.push_back(new pen(Name, Type_, DIAM, PRICE, PHONE));// новое звено списка с содержимым объекта Ручка
}

void for_paper(list<Base*>& values, stringstream& word){
    int Plotnost, Width, Height; // буферы для плотности, ширины и высоты
    string PHONE, Name="Бумага"; // буферы для цвета и телефона
    double PRICE;
    word >> Plotnost >> Width >> Height >> PRICE >> PHONE; // чтение: плотность, ширина, высота, цена, телефон
    values.push_back(new paper(Name, Plotnost, Width, Height, PRICE, PHONE)); // новое звено списка с содержимым объекта Бумага
}

void ADD_instruct(list<Base*>& values, stringstream& word){
    string instruct;
    word >> instruct;
    if (instruct == "pencil") for_pencil(values, word);
    else if (instruct == "pen") for_pen(values, word);
    else if (instruct == "paper") for_paper(values, word);
    else {cout << "Объект " << instruct << " недопустим!\n"; exit(0);};
}

std::vector<std::string> split(std::string str, char del){
    std::vector<std::string> temp;
    std::string currentString;
    
    for(int i=0; i<(int)str.size(); i++){
        if(str[i] != del){
            currentString += str[i];
        } else {
            if (!currentString.empty()) {
                temp.push_back(currentString);
                currentString.clear();
            }
        }
    }
    
    if (!currentString.empty()) {
        temp.push_back(currentString);
    }
    return temp;
}

void REM_instruct(list<Base*>& values, string& line){
    
    vector<string> splitStr = split(line, ' ');
    
    if(splitStr.size() > 2) {
        
    } else {
        // Если в векторе 2 обьекта
        string name = splitStr.at(1);
        for (auto it = values.begin(); it != values.end(); ) {
            if(name == "pencil" && (*it)->Name == "Карандаш") {
                it = values.erase(it); // удалить и перейти к следующему элементу
            } else if (name == "pen" && (*it)->Name == "Ручка") {
                it = values.erase(it); // удалить и перейти к следующему элементу
            } else if (name == "paper" && (*it)->Name == "Бумага") {
                it = values.erase(it); // удалить и перейти к следующему элементу
            } else {
                ++it; // если элемент не подходит под условия, перейти к следующему элементу
            }
        }
    }
    cout << " Происходит удаление...\n\n";
}

void Print_instruct(list<Base*>& values){
    cout << "\n___________________ Вывод... ___________________\n";
    for (auto* value : values) value->print();
}

void chek_instruct(list<Base*>& values, stringstream& word, string& line){
    string name, instruct;
    word >> instruct;
    if (instruct == "ADD") ADD_instruct(values, word);
    else if (instruct == "REM") REM_instruct(values, line);
    else if (instruct == "Print") Print_instruct(values);
    else {cout << "Команда " << instruct << " некорректна или не существует!\n"; exit(0);};
}

void reed_txt(list<Base*>& values, ifstream& IN){
    string line, instruct;
    while (getline(IN, line)){
        stringstream word(line);    // извлекаем по одному слову из строчки
        chek_instruct(values, word, line);
    }
}

int main() {
    
    ifstream IN("/Users/andrejdavydov/Desktop/СФУ/ОПППО/lab_1/Input.txt");
    if (!IN.is_open()) {                            // если файл не открыт
        cout << "Файл IN не может быть открыт!\n";  // сообщить об этом
        return -1;
    }
    
    list<Base*> values;
    string line, instruct; // буфер для строчки и слова
    
    reed_txt(values, IN);
    
    IN.close();
}
