#include <iostream>
#include <string>
#include <random>
#include <iomanip>
#include <vector>

using namespace std;

// Globale Variablen
double fWahrscheinlichkeit = 2.1;
double iKontostand = 0;
double Wettgeld = 0;
double Gesamt = 0;
int iPin;
double iEingabe;
char cAuswahl;
string str_Kontoinhaber;

vector<string> vec_Benutzer = { "IAmBad", "Firebrigade", "Guest" };
vector<int> vec_Pins = { 321, 123, 0 };

// Login-Funktion
bool Login() {
    for (int i = 0; i < vec_Benutzer.size(); i++) {
        if (str_Kontoinhaber == vec_Benutzer[i]) {
            cout << "\nPin: ";
            cin >> iPin;
            if (iPin == vec_Pins[i]) {
                return true;
            }
            return false;
        }
    }
    return false;
}

// Funktion: nur ein Zeichen einlesen
char einlesenOption() {
    string input;
    while (true) {
        cin >> input;
        if (input.length() == 1)  // nur ein Zeichen erlaubt
            return input[0];
        cout << "Ungueltige Eingabe! Bitte nur einen Buchstaben eingeben: ";
    }
}

int main() {

    system("color a");

    // Hinweistext
    cout << "ACHTUNG: Dieses Spiel verwendet keine echten Waehrungen.\n";
    cout << "Alle Credits sind virtuell und dienen nur zum Lernen und Spass.\n\n";

    cout << "Login\n\n";
    cout << "Kontoinhaber: ";
    cin >> str_Kontoinhaber;

    if (Login() == true) {
        while (true) {
            system("cls");
            cout << "\nWas wollen Sie machen?\n[a]Credits einzahlen\n[b]Credits auszahlen\n[c]Gambling\n[q]Beenden\n";
            cout << "Kontostand: " << fixed << setprecision(2) << iKontostand << endl;

            cAuswahl = einlesenOption();

            switch (cAuswahl) {
            case 'a':
                cout << "Geben Sie die Anzahl der Credits ein, die Sie einzahlen wollen: ";
                cin >> iEingabe;
                if (iEingabe <= 0) {
                    cout << "Ungueltiger Betrag!\n";
                    system("pause");
                    continue;
                }
                iKontostand += iEingabe;
                break;

            case 'b':
                cout << "Credits auszahlen: ";
                cin >> iEingabe;
                if (iEingabe <= 0 || iEingabe > iKontostand) {
                    cout << "Ungueltiger Betrag!\n";
                    system("pause");
                    continue;
                }
                iKontostand -= iEingabe;
                break;

            case 'c': {
                cout << "Wie viele Credits wollen Sie setzen?\n";
                cin >> Wettgeld;
                if (Wettgeld <= 0 || Wettgeld > iKontostand) {
                    cout << "Nicht genug Credits oder ungueltiger Einsatz!\n";
                    system("pause");
                    continue;
                }
                iKontostand -= Wettgeld;

                mt19937 gen(random_device{}()); // Zufallsgenerator
                uniform_real_distribution<float> dist(0, fWahrscheinlichkeit);
                float fZuffalsmultiplikator = dist(gen);

                Gesamt = Wettgeld * fZuffalsmultiplikator + Gesamt - Wettgeld;
                cout << "\nMultiplier: " << fZuffalsmultiplikator << endl;
                cout << "Gewinn: " << Wettgeld * fZuffalsmultiplikator - Wettgeld << endl;
                cout << "Gesamt: " << Gesamt << endl << endl;
                system("pause");

                iKontostand += Wettgeld * fZuffalsmultiplikator;

                if (fWahrscheinlichkeit < 0.1) {
                    fWahrscheinlichkeit = 2.5;
                }
                else {
                    fWahrscheinlichkeit -= 0.1;
                }
                break;
            }

            case 'q':
                return 0;

            default:
                cout << "Ungueltige Auswahl!\n";
                system("pause");
            }
        }
    }

    return 0;
}