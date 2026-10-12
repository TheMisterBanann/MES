#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Node {
    double x = 0.0, y = 0.0;
};

struct Element {
    int ID[4] = {0, 0, 0, 0};
};

struct Grid {
    int nN = 0; 
    int nE = 0; 
    vector<Element> element;   
    vector<Node> node;         
};

struct GlobalData {
    double SimulationTime = 0, SimulationStepTime = 0, Conductivity = 0, Alfa = 0;
    double Tot = 0, InitialTemp = 0, Density = 0, SpecificHeat = 0;
    int nN = 0;  
    int nE = 0;
};

static string trim(const string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

bool readFile(const string& fileName, GlobalData& gd, Grid& grid) {
    ifstream file(fileName);
    if (!file) {
        cerr << "Nie mozna otworzyc pliku: " << fileName << "\n";
        return false;
    }

    enum Section { HEADER, NODES, ELEMENTS, OTHER } section = HEADER;
    string line;

    while (getline(file, line)) {
        line = trim(line);
        if (line.empty()) continue;

        if (line[0] == '*') {
            if (line.rfind("*Node", 0) == 0) {
                section = NODES;
                grid.nN = gd.nN;
                grid.node.resize(gd.nN);
            } else if (line.rfind("*Element", 0) == 0) {
                section = ELEMENTS;
                grid.nE = gd.nE;
                grid.element.resize(gd.nE);
            } else {
                section = OTHER;
            }
            continue;
        }

        if (section == HEADER) {
            istringstream ss(line);
            string key;
            ss >> key;
            if (key == "Nodes")         { string w; ss >> w >> gd.nN; } 
            else if (key == "Elements") { string w; ss >> w >> gd.nE; }
            else if (key == "SimulationTime")     ss >> gd.SimulationTime;
            else if (key == "SimulationStepTime") ss >> gd.SimulationStepTime;
            else if (key == "Conductivity")       ss >> gd.Conductivity;
            else if (key == "Alfa")               ss >> gd.Alfa;
            else if (key == "Tot")                ss >> gd.Tot;
            else if (key == "InitialTemp")        ss >> gd.InitialTemp;
            else if (key == "Density")            ss >> gd.Density;
            else if (key == "SpecificHeat")       ss >> gd.SpecificHeat;
        } else if (section == NODES || section == ELEMENTS) {
            replace(line.begin(), line.end(), ',', ' ');
            istringstream ss(line);
            int id;
            ss >> id;
            if (section == NODES) {
                if (id < 1 || id > grid.nN) continue;
                ss >> grid.node[id - 1].x >> grid.node[id - 1].y;
            } else {
                if (id < 1 || id > grid.nE) continue;
                for (int i = 0; i < 4; ++i) ss >> grid.element[id - 1].ID[i];
            }
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    string fileName = (argc > 1) ? argv[1] : "/home/banan/Desktop/MES/files/Test1_4_4.txt";

    GlobalData gd;
    Grid grid;
    if (!readFile(fileName, gd, grid)) return 1;

    cout << "=== GlobalData ===\n"
              << "SimulationTime     = " << gd.SimulationTime << "\n"
              << "SimulationStepTime = " << gd.SimulationStepTime << "\n"
              << "Conductivity       = " << gd.Conductivity << "\n"
              << "Alfa               = " << gd.Alfa << "\n"
              << "Tot                = " << gd.Tot << "\n"
              << "InitialTemp        = " << gd.InitialTemp << "\n"
              << "Density            = " << gd.Density << "\n"
              << "SpecificHeat       = " << gd.SpecificHeat << "\n"
              << "nN                 = " << gd.nN << "\n"
              << "nE                 = " << gd.nE << "\n\n";

    cout << "=== Wspolrzedne wezlow ===\n";
    cout << fixed << setprecision(10);
    for (int i = 0; i < grid.nN; ++i)
        cout << "Wezel " << setw(3) << i + 1 << ":  x = " << setw(14) << grid.node[i].x << "   y = " << setw(14) << grid.node[i].y << "\n";

    cout << "\n=== Elementy (ID wezlow) ===\n";
    for (int i = 0; i < grid.nE; ++i) {
        cout << "Element " << setw(3) << i + 1 << ":  {";
        for (int j = 0; j < 4; ++j)
            cout << grid.element[i].ID[j] << (j < 3 ? ", " : "}\n");
    }
    return 0;
}