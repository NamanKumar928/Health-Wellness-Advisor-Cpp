#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include <windows.h>
#include <cstdlib>  // For rand()
#include <ctime>    // For time()
#include <limits>
#include <cctype>
// ASCII color codes
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define BLUE "\033[1;34m"


using namespace std;

// Function to change console color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//LOGIN
// Base class for User
class User {
protected:
    string username;
    string password;

public:
    User() {}
    User(const string& user, const string& pass) : username(user), password(pass) {}

    virtual void login() = 0;
    virtual void showWelcomeMessage() {
        cout << "Welcome, " << username << "!" << endl;
    }

    string getUsername() {
        return username;
    }
};

// Derived class for Regular User
class RegularUser : public User {
public:
    RegularUser(const string& user, const string& pass) : User(user, pass) {}

    void login() override {
        ifstream file("users.txt");
        string line;
        bool isAuthenticated = false;
        int attempt = 0;

        while (attempt < 3) {
            file.clear();
            file.seekg(0, ios::beg);

            while (getline(file, line)) {
                stringstream ss(line);
                string fileUsername, filePassword;
                ss >> fileUsername >> filePassword;

                if (fileUsername == username && filePassword == password) {
                    cout << "User Login Successful!" << endl;
                    showWelcomeMessage();
                    isAuthenticated = true;
                    return;
                }
            }

            attempt++;
            if (!isAuthenticated) {
                cout << "Invalid Username or Password. Attempt " << attempt << " of 3." << endl;
                if (attempt < 3) {
                    cout << "Please try again.\nEnter Username: ";
                    cin >> username;
                    cout << "Enter Password: ";
                    cin >> password;
                }
            }
        }

        cout <<RED << "Maximum login attempts reached. Access denied!" << endl;
        exit(0);
    }

    void signUp() {
        ofstream file("users.txt", ios::app);
        if (!file) {
            cerr << "Error opening file for writing!" << endl;
            return;
        }

        file << username << " " << password << endl;
        file.close();
        cout << "Account created successfully!" << endl;
    }
};

//GENERAL HEALTH
class Remedy {
protected:
    int choice;
public:
    Remedy() { choice = 0; }

    void showMenu() {
        cout << "\nNANI DADI KE NUSKHE\n";
        cout << "\nChoose an illness to get home remedies:\n";
        cout << "1. Cold\n";
        cout << "2. Cough\n";
        cout << "3. Fever\n";
        cout << "4. Headache\n";
        cout << "5. Sore Throat\n";
        cout << "Enter your choice (1-5): ";
        cin >> choice;
    }

    int getChoice() {
        return choice;
    }
};

// Derived class
class HomeRemedy : public Remedy {
public:
    void findingRemedy() {
        cout << "\nFinding the perfect nuska";
        for (int i = 0; i < 3; ++i) {
            cout << ".";
            cout.flush();
            Sleep(400);
        }
        cout << "\n\n";
    }

    void displayRemedy() {
        findingRemedy(); // Add little suspense before showing remedy

        switch (choice) {
            case 1:
                cout << "Remedies for Cold:\n";
                cout << "- Drink turmeric milk at night.\n";
                cout << "- Steam with eucalyptus oil.\n";
                cout << "- Honey with warm water.\n";
                break;
            case 2:
                cout << "Remedies for Cough:\n";
                cout << "- Ginger + honey mix.\n";
                cout << "- Gargle with warm salt water.\n";
                cout << "- Tulsi tea twice a day.\n";
                break;
            case 3:
                cout << "Remedies for Fever:\n";
                cout << "- Tulsi kadha 2 times a day.\n";
                cout << "- Lukewarm sponge bath.\n";
                cout << "- Light food and rest.\n";
                break;
            case 4:
                cout << "Remedies for Headache:\n";
                cout << "- Apply peppermint oil.\n";
                cout << "- Drink ginger tea.\n";
                cout << "- Take deep breaths, relax.\n";
                break;
            case 5:
                cout << "Remedies for Sore Throat:\n";
                cout << "- Saltwater gargle.\n";
                cout << "- Honey + ginger juice.\n";
                cout << "- Warm fluids, avoid cold drinks.\n";
                break;
            default:
                setColor(12); // Red
                cout << "Invalid choice! Please restart.\n";
        }
    }
};

class General_health{
public:
    General_health(){
    HomeRemedy r;
    char again;

    do {
        r.showMenu();
        r.displayRemedy();

        cout << "\n\nWould you like to try another remedy? (y/n): ";
        cin >> again;
        cout << endl;
    } while (again == 'y' || again == 'Y');

    setColor(10);
    cout << "Thank you for trusting Nani Dadi ke Nuskhe! Stay healthy! \n";
    setColor(7);}

};

//DIGESTIVE

// Base class
class DRemedy {
public:
    void findingRemedy() {
        cout << "Finding the best Nuskha for you";
        for (int i = 0; i < 3; ++i) {
            cout << ".";
            cout.flush();
            Sleep(500);
        }
        cout << endl << endl;
    }
};

// Derived classes
class Diarrhoea {
public:
    void show() {
        cout << "Sip sip hooray - Stay Hydrated" << RESET << endl;
        cout << "- Drink plenty of water and oral rehydration solutions\n";
        cout << "- Eat light foods like bananas, rice, and toast\n";
    }
};

class UpsetStomach {
public:
    void show() {
        cout << "Calm that tummy storm" << RESET << endl;
        cout << "- Try ginger tea or a warm glass of water\n";
        cout << "- Avoid heavy oily foods for now\n";
    }
};

class Acidity {
public:
    void show() {
        cout << "Feel the burn? No more!" << RESET << endl;
        cout << "- Chew a piece of clove or drink cold milk\n";
        cout << "- Sleeping with your head slightly elevated helps too\n";
    }
};

class Indigestion {
public:
    void show() {
        cout << "Bloating no more" << RESET << endl;
        cout << "- Have a spoon of ajwain with warm water\n";
        cout << "- Peppermint tea can also ease the discomfort\n";
    }
};

class Nausea {
public:
    void show() {
        cout << "Stop that spin before it begins" << RESET << endl;
        cout << "- Suck on a lemon slice or sniff fresh lemon\n";
        cout << "- Ginger candies or tea work wonders too\n";
    }
};

// Main class to run the app
class HealthCare : public DRemedy {
public:
    void showMenu() {
        cout << "Welcome to Nani Dadi ke Nuskhe!" << RESET << endl;
        cout << "Your health is your wealth! Let's fix it naturally.\n\n";
        cout << "Choose your trouble:\n";
        cout << "1. Diarrhoea\n";
        cout << "2. Upset Stomach\n";
        cout << "3. Acidity\n";
        cout << "4. Indigestion\n";
        cout << "5. Nausea\n";
        cout << "0. Exit\n";
    }

    void serve(int choice) {
        if (choice == 1) {
            findingRemedy();
            Diarrhoea d;
            d.show();
        } else if (choice == 2) {
            findingRemedy();
            UpsetStomach u;
            u.show();
        } else if (choice == 3) {
            findingRemedy();
            Acidity a;
            a.show();
        } else if (choice == 4) {
            findingRemedy();
            Indigestion i;
            i.show();
        } else if (choice == 5) {
            findingRemedy();
            Nausea n;
            n.show();
        } else if (choice == 0) {
            cout << GREEN << "Stay healthy and happy! See you soon..." << RESET << endl;
        } else {
            cout << RED << "Oops! Invalid choice. Try again." << RESET << endl;
        }
    }
};
class Digestive
{
    public: Digestive()
    {
    HealthCare app;
    int choice;

    do {
        cout << endl;
        app.showMenu();
        cout << endl << "Enter your choice: ";
        cin >> choice;
        cout << endl;
        app.serve(choice);
    } while (choice != 0);}
};

void loadingDots(string message = "Loading") {
    cout << message;
    for (int i = 0; i < 3; ++i) {
        cout << ".";
        cout.flush();
        Sleep(400);
    }
    cout << endl;
}
class PRemedy {
    public:
        virtual void showPRemedies() = 0; // pure virtual function
    };

    // Wound types
    class Cut : public PRemedy {
    public:
        void showPRemedies() override {
            loadingDots("Fetching first-aid kit");
            cout << "\nRemedies for Cuts:\n";
            cout << "- Clean with clean water\n";
            cout << "- Apply turmeric or honey\n";
            cout << "- Cover it with a clean bandage\n";
        }
    };

    class Burn : public PRemedy {
    public:
        void showPRemedies() override {
            loadingDots("Cooling your burn");
            cout << "\nRemedies for Burns:\n";
            cout << "- Run cool water\n";
            cout << "- Apply Aloe vera gel\n";
            cout << "- Don't pop blisters\n";
        }
    };

    class Sunburn : public PRemedy {
    public:
        void showPRemedies() override {
            loadingDots("Preparing sunburn relief");
            cout << "\nRemedies for Sunburn:\n";
            cout << "- Take a cool bath\n";
            cout << "- Apply yogurt\n";
            cout << "- Stay hydrated\n";
        }
    };

    // Pain types
    class BodyPain : public PRemedy {
    public:
        void showPRemedies() override {
            loadingDots("Getting body pain remedies");
            cout << "\nRemedies for Body Pain:\n";
            cout << "- Rest properly\n";
            cout << "- Warm turmeric milk\n";
            cout << "- Gentle yoga stretches\n";
        }
    };

    class MusclePain : public PRemedy {
    public:
        void showPRemedies() override {
            loadingDots("Stretching muscles");
            cout << "\nRemedies for Muscle Pain:\n";
            cout << "- Warm compress\n";
            cout << "- Oil massage\n";
            cout << "- Stay hydrated\n";
        }
    };

    // Menu class
    class PRemedyMenu {
    public:
        void mainMenu() {
            int choice;
            do {
                loadingDots("Opening Main Menu");
                cout << "1. Wound Remedies\n";
                cout << "2. Pain Remedies\n";
                cout << "3. Exit\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        woundMenu();
                        break;
                    case 2:
                        painMenu();
                        break;
                    case 3:
                        loadingDots("Exiting Program");
                        cout <<BLUE<< "Goodbye! Stay Healthy!\n";
                        break;
                    default:
                        cout <<RED<< "Invalid choice. Please try again.\n"<<RESET<<endl;
                }
            } while (choice != 3);
        }

    private:
        void woundMenu() {
            int choice;
            loadingDots("Opening wound remedies");
            cout << "\n--- WOUND REMEDIES ---\n";
            cout << "1. Cut\n";
            cout << "2. Burn\n";
            cout << "3. Sunburn\n";
            cout << "4. Back to Main Menu\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    Cut c;
                    c.showPRemedies();
                    break;
                }
                case 2: {
                    Burn b;
                    b.showPRemedies();
                    break;
                }
                case 3: {
                    Sunburn s;
                    s.showPRemedies();
                    break;
                }
                case 4:
                    cout << "Returning to Main Menu...\n";
                    break;
                default:
                    cout << RED<<"Invalid option.\n"<<RESET<<endl;
            }
            Sleep(1000);
        }

        void painMenu() {
            int choice;
            loadingDots("Opening pain remedies");
            cout << "\n--- PAIN REMEDIES ---\n";
            cout << "1. Body Pain\n";
            cout << "2. Muscle Pain\n";
            cout << "3. Back to Main Menu\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    BodyPain b;
                    b.showPRemedies();
                    break;
                }
                case 2: {
                    MusclePain m;
                    m.showPRemedies();
                    break;
                }
                case 3:
                    cout << "Returning to Main Menu...\n";
                    break;
                default:
                    cout <<RED<< "Invalid option.\n"<<RESET<<endl;
            }
            Sleep(1000);
        }
    };

class Pain{
    public:
    Pain(){
        PRemedyMenu app;
        app.mainMenu();}
};

//SCALP
class ScalpCare {
public:
    void showNuskhe(string scalpType) {
        cout << "\n=== Recommended Home Remedies for " << scalpType << " ===\n";

        if (scalpType == "Oily Scalp") {
            lemonJuiceAndCurd();
            onionJuiceAndAloeVera();
        } else if (scalpType == "Dry Scalp") {
            coconutOilAndCamphor();
            fenugreekPaste();
        } else if (scalpType == "Dandruff-Prone Scalp") {
            neemAndCoconutOil();
            lemonJuiceAndCurd();
        } else if (scalpType == "Normal Scalp") {
            onionJuiceAndAloeVera();
            fenugreekPaste();
        }

        cout << "\nDiet Tips for Scalp Health:\n";
        if (scalpType == "Oily Scalp") {
            cout << "- Eat more fruits like oranges, apples, and berries.\n";
            cout << "- Avoid greasy, fried, and processed foods.\n";
            cout << "- Stay hydrated: at least 8-10 glasses of water daily.\n";
        } else if (scalpType == "Dry Scalp") {
            cout << "- Increase intake of omega-3 rich foods like flaxseeds, walnuts, and avocados.\n";
            cout << "- Include healthy fats like ghee and olive oil in moderate amounts.\n";
            cout << "- Drink herbal teas to promote hydration.\n";
        } else if (scalpType == "Dandruff-Prone Scalp") {
            cout << "- Reduce sugar and dairy intake.\n";
            cout << "- Include probiotics like curd, fermented foods (idli, dosa).\n";
            cout << "- Add turmeric and ginger to meals for anti-inflammatory effects.\n";
        } else {
            cout << "- Maintain a balanced diet with leafy greens, fruits, and whole grains.\n";
            cout << "- Drink plenty of water and avoid excessive caffeine.\n";
        }
    }

    void generateRoutine(string scalpType) {
        cout << "\n\n=== Personalized Scalp Care Routine ===\n";
        cout << "Based on your " << scalpType << ", here's your ideal routine:\n\n";
        cout << "Weekly Care:\n";
        if (scalpType == "Oily Scalp") {
            cout << "- Wash hair 3-4 times weekly using besan (gram flour) and water paste.\n";
            cout << "- Apply multani mitti (Fuller's earth) mask once a week to soak excess oil.\n";
        } else if (scalpType == "Dry Scalp") {
            cout << "- Wash hair 2-3 times weekly with shikakai and reetha solution.\n";
            cout << "- Hot oil treatment with coconut or mustard oil twice a week.\n";
        } else if (scalpType == "Dandruff-Prone Scalp") {
            cout << "- Wash hair every other day with neem leaf-infused water.\n";
            cout << "- Rinse with diluted lemon juice and curd mixture once weekly.\n";
        } else {
            cout << "- Wash hair 2-3 times weekly using gentle herbal cleansers like hibiscus powder.\n";
            cout << "- Massage scalp with warm oil (coconut or almond) once weekly.\n";
        }

        cout << "\nDaily Care:\n";
        if (scalpType == "Oily Scalp") {
            cout << "- Morning: Rinse scalp with tulsi (basil) water.\n";
            cout << "- Evening: Massage with a few drops of rose water.\n";
        } else if (scalpType == "Dry Scalp") {
            cout << "- Morning: Apply a few drops of aloe vera gel to scalp ends.\n";
            cout << "- Evening: Massage gently with warm sesame oil.\n";
        } else {
            cout << "- Morning: Comb hair gently to stimulate natural oils.\n";
            cout << "- Evening: Scalp massage using fingers dipped in amla oil.\n";
        }

        cout << "\nDadi-Nani Recommended Ingredients:\n";
        if (scalpType == "Oily Scalp") {
            cout << "- Besan (gram flour) for cleansing\n";
            cout << "- Multani mitti to reduce oil\n";
        } else if (scalpType == "Dry Scalp") {
            cout << "- Coconut/Mustard oil for nourishment\n";
            cout << "- Aloe vera gel for hydration\n";
        } else if (scalpType == "Dandruff-Prone Scalp") {
            cout << "- Neem leaves and lemon juice for dandruff\n";
            cout << "- Curd for soothing the scalp\n";
        } else {
            cout << "- Amla oil for strength\n";
            cout << "- Hibiscus powder for shine\n";
        }
    }

private:
    void neemAndCoconutOil() {
        cout << "\n Neem + Coconut Oil:\n1. Boil neem leaves in coconut oil.\n2. Strain and apply to scalp. Leave overnight.\n3. Wash next morning with mild shampoo.\n";
    }
    void coconutOilAndCamphor() {
        cout << "\n Coconut Oil + Camphor:\n1. Mix camphor in coconut oil.\n2. Warm and apply. Leave for 30 mins.\n";
    }
    void onionJuiceAndAloeVera() {
        cout << "\n Onion Juice + Aloe Vera:\n1. Mix onion juice and aloe vera.\n2. Apply for 30 mins. Rinse well.\n";
    }
    void lemonJuiceAndCurd() {
        cout << "\n Lemon Juice + Curd:\n1. Mix lemon juice with curd.\n2. Apply for 30-45 mins. Rinse.\n";
    }
    void fenugreekPaste() {
        cout << "\n Fenugreek Paste:\n1. Soak and grind methi seeds.\n2. Apply for 30 mins. Rinse.\n";
    }
};

class ScalpTypeChecker {
public:
    string assessScalpType() {
        cout << "\n=== Scalp Type Assessment ===\n(Scale: 1 - Never, 2 - Sometimes, 3 - Often)\n";
        int oiliness = getResponse("1. Scalp shiny/greasy by midday?");
        int itching = getResponse("2. Experience itching?");
        int flakes = getResponse("3. See flakes?");
        int tightness = getResponse("4. Scalp feels dry/tight after wash?");
        int redness = getResponse("5. Redness or irritation?");

        if (oiliness >= 3 && flakes <= 2 && tightness <= 1) return "Oily Scalp";
        if (flakes >= 2 && (itching >= 2 || redness >= 2)) return "Dandruff-Prone Scalp";
        if (tightness >= 2 && oiliness <= 1) return "Dry Scalp";
        return "Normal Scalp";
    }

private:
    int getResponse(string question) {
        int response;
        cout << question << " ";
       while (!(cin >> response) || response < 1 || response > 3 ){
            cout << "Please enter between 1-3: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        return response;
    }
};

void saveUserData(const string& username, const string& dataType, const string& value) {
    ofstream outFile(username + "_profile.txt", ios::app);
    if (outFile.is_open()) {
        outFile << dataType << " = " << value << endl;
        outFile.close();
    }
}

void displayPreviousResults(const string& username) {
    ifstream inFile(username + "_profile.txt");
    if (inFile.is_open()) {
        cout << "\n=== Your Previous Assessments ===\n";
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cout << "\nNo previous assessment records found.\n";
    }
}

void scalp(const string& username) {
    ScalpTypeChecker checker;
    ScalpCare care;
    char again;

    do {
        string scalpType = checker.assessScalpType();
        cout << BLUE <<"\n=== Assessment Result ===\nYour scalp type: " << scalpType << "\n"<< RESET<<endl;

        saveUserData(username, "Scalp type", scalpType);
        care.showNuskhe(scalpType);

        cout << "\nWant a complete routine? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            care.generateRoutine(scalpType);
        }

        cout << "\nAssess again? (y/n): ";
        cin >> again;

    } while (again == 'y' || again == 'Y');
    cout <<CYAN << "\nHealthy scalp leads to healthy hair!\n"<<RESET<<endl;
}


//SKINCARE
// Linked list node for remedies
class RemedyNode {
public:
    string remedy;
    RemedyNode* next;

    RemedyNode(string r) : remedy(r), next(nullptr) {}
};

// Linked list handler
class RemedyList {
private:
    RemedyNode* head;

public:
    RemedyList() : head(nullptr) {}

    void addRemedy(string r) {
        RemedyNode* newNode = new RemedyNode(r);
        if (!head) {
            head = newNode;
        } else {
            RemedyNode* temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newNode;
        }
    }

    void displayRemedies() {
        RemedyNode* temp = head;
        while (temp) {
            cout << temp->remedy << endl;
            temp = temp->next;
        }
    }

    ~RemedyList() {
        while (head) {
            RemedyNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Abstract base class
class RemedyCategory {
protected:
    RemedyList remedies;
public:
    virtual void display() = 0;
    virtual ~RemedyCategory() {}
};

// Specific categories
class AcneRemedy : public RemedyCategory {
public:
    AcneRemedy() {
        remedies.addRemedy("1. Apply raw honey for 15 mins, then rinse.");
        remedies.addRemedy("2. Use diluted tea tree oil on acne spots.");
        remedies.addRemedy("3. Apply aloe vera gel twice daily.");
        remedies.addRemedy("4. Use green tea toner (cool brewed green tea).");
    }
    void display() {
        cout << "\n Remedies for Acne & Pimples:\n";
        remedies.displayRemedies();
    }
};

class PigmentationRemedy : public RemedyCategory {
public:
    PigmentationRemedy() {
        remedies.addRemedy("1. Apply lemon juice (patch test first) on spots.");
        remedies.addRemedy("2. Use turmeric + honey paste 2x/week.");
        remedies.addRemedy("3. Potato juice helps lighten dark areas.");
        remedies.addRemedy("4. Apply licorice extract (natural brightener).");
    }
    void display() {
        cout << "\n Remedies for Pigmentation & Freckles:\n";
        remedies.displayRemedies();
    }
};

class MolesRemedy : public RemedyCategory {
public:
    MolesRemedy() {
        remedies.addRemedy("1. Apply apple cider vinegar with cotton swab daily.");
        remedies.addRemedy("2. Crushed garlic paste (short time, then wash).");
        remedies.addRemedy("3. Aloe vera can soothe and reduce appearance over time.");
        remedies.addRemedy(" Note: Moles should be checked by a dermatologist if they change shape or color.");
    }
    void display() {
        cout << "\n Remedies for Moles (natural suggestions):\n";
        remedies.displayRemedies();
    }
};

class DrySkinRemedy : public RemedyCategory {
public:
    DrySkinRemedy() {
        remedies.addRemedy("1. Use thick moisturizers with ceramides or shea butter.");
        remedies.addRemedy("2. Apply coconut oil or almond oil at night.");
        remedies.addRemedy("3. Drink at least 8 glasses of water daily.");
        remedies.addRemedy("4. Avoid hot water while washing your face.");
        remedies.addRemedy("5. Use a humidifier in dry climates.");
    }
    void display() {
        cout << "\n Tips for Dry Skin & Dehydration:\n";
        remedies.displayRemedies();
    }
};

class SkinNourishment : public RemedyCategory {
public:
    SkinNourishment() {
        remedies.addRemedy("1. Eat fruits rich in Vitamin C (oranges, strawberries).");
        remedies.addRemedy("2. Include omega-3s (walnuts, flax seeds, salmon).");
        remedies.addRemedy("3. Stay hydrated throughout the day.");
        remedies.addRemedy("4. Avoid processed and oily foods.");
        remedies.addRemedy("5. Include green leafy vegetables in meals.");
    }
    void display() {
        cout << "\n Tips for Nourishing Your Skin with Diet:\n";
        remedies.displayRemedies();
    }
};

class DarkCirclesRemedy : public RemedyCategory {
public:
    DarkCirclesRemedy() {
        remedies.addRemedy("1. Apply cold tea bags on eyes for 10 mins.");
        remedies.addRemedy("2. Use cucumber slices for cooling and hydration.");
        remedies.addRemedy("3. Almond oil massage before sleeping.");
        remedies.addRemedy("4. Get adequate sleep and manage stress.");
    }
    void display() {
        cout << "\n Remedies for Dark Circles:\n";
        remedies.displayRemedies();
    }
};

class DarkSpotsRemedy : public RemedyCategory {
public:
    DarkSpotsRemedy() {
        remedies.addRemedy("1. Apply papaya pulp 2-3 times a week.");
        remedies.addRemedy("2. Lemon and honey mask (test for sensitivity).");
        remedies.addRemedy("3. Use yogurt and turmeric paste.");
        remedies.addRemedy("4. Apply apple cider vinegar toner.");
    }
    void display() {
        cout << "\n Remedies for Dark Spots / Pimple Marks:\n";
        remedies.displayRemedies();
    }
};

class SkinTypeIdentifier {
public:
    string identify() {
        string skinType;
        char answer;
        int oily = 0, dry = 0, sensitive = 0;

        cout << "\nLet's identify your skin type. Answer with Y (yes) or N (no):\n";

        cout << "1. Does your face feel oily/shiny a few hours after washing? ";
        cin >> answer; if (tolower(answer) == 'y') oily++;

        cout << "2. Do you often have clogged pores or acne? ";
        cin >> answer; if (tolower(answer) == 'y') oily++;

        cout << "3. Do you get dry patches or flakiness? ";
        cin >> answer; if (tolower(answer) == 'y') dry++;

        cout << "4. Does your skin feel tight after cleansing? ";
        cin >> answer; if (tolower(answer) == 'y') dry++;

        cout << "5. Do you get red or irritated easily with products or sun? ";
        cin >> answer; if (tolower(answer) == 'y') sensitive++;

        cout << "\nBased on your answers, your likely skin type is: ";

        if (oily >= 2) {
            cout << GREEN <<"OILY SKIN\n"<<RESET<<endl;
            showOilySkinTips();
            skinType = "Oily";
        }
        else if (dry >= 2) {
            cout << GREEN <<"DRY SKIN\n"<<RESET<<endl;
            showDrySkinTips();
            skinType = "Dry";
        }
        else if (sensitive >= 2) {
            cout << GREEN <<"SENSITIVE SKIN\n"<<RESET<<endl;
            showSensitiveSkinTips();
            skinType = "Sensitive";
        }
        else {
            cout << GREEN << "NORMAL SKIN\n"<<RESET<<endl;
            showNormalSkinTips();
            skinType = "Normal";
        }
        return skinType;
    }

private:
    void showOilySkinTips() {
        cout << "\nBasic Tips for Oily Skin:\n";
        cout << "- Use gentle foaming cleansers.\n";
        cout << "- Avoid heavy creams; use gel-based moisturizers.\n";
        cout << "- Use non-comedogenic (won't clog pores) products.\n";
        cout << "- Blot excess oil with oil-absorbing sheets.\n";
        cout << "- Use a clay mask once a week.\n";
    }

    void showDrySkinTips() {
        cout << "\nBasic Tips for Dry Skin:\n";
        cout << "- Use creamy, hydrating cleansers.\n";
        cout << "- Apply moisturizers immediately after washing.\n";
        cout << "- Avoid long, hot showers.\n";
        cout << "- Use hydrating serums with hyaluronic acid.\n";
        cout << "- Use a humidifier in dry environments.\n";
    }

    void showSensitiveSkinTips() {
        cout << "\nBasic Tips for Sensitive Skin:\n";
        cout << "- Use fragrance-free and alcohol-free products.\n";
        cout << "- Always patch test new skincare items.\n";
        cout << "- Avoid physical scrubs; use very mild exfoliants.\n";
        cout << "- Use mineral-based sunscreens.\n";
        cout << "- Keep skincare routine minimal and simple.\n";
    }

    void showNormalSkinTips() {
        cout << "\nBasic Tips for Normal/Combination Skin:\n";
        cout << "- Maintain balance with lightweight products.\n";
        cout << "- Exfoliate 1-2 times a week to avoid clogged pores.\n";
        cout << "- Use a gel moisturizer in T-zone (forehead/nose).\n";
        cout << "- Hydrate dry areas with nourishing creams.\n";
        cout << "- Sunscreen is a must everyday!\n";
    }
};

class SkincareMenu {
public:
    void show() {
        cout << GREEN <<"\nSKINCARE MENU:\n"<<RESET<<endl;
        cout << "1. Identify Your Skin Type\n";
        cout << "2. Remedies for Acne & Pimples\n";
        cout << "3. Remedies for Pigmentation & Freckles\n";
        cout << "4. Remedies for Moles\n";
        cout << "5. Tips for Dry Skin & Dehydration\n";
        cout << "6. Nourishing Skin Through Diet\n";
        cout << "7. Remedies for Dark Circles\n";
        cout << "8. Remedies for Dark Spots\n";
        cout << "9. Exit\n";
    }
};

void skin(const string& username) {
    SkincareMenu menu;
    SkinTypeIdentifier identifier;
    bool running = true;
    int choice;

    while (running) {
        menu.show();
        cout << "\nEnter your choice (1-9): ";
        cin >> choice;

        RemedyCategory* remedy = nullptr;

        switch (choice) {
            case 1: {
                string skinType = identifier.identify();
                saveUserData(username, "Skin type", skinType);
                break;
            }
            case 2:
                remedy = new AcneRemedy();
                break;
            case 3:
                remedy = new PigmentationRemedy();
                break;
            case 4:
                remedy = new MolesRemedy();
                break;
            case 5:
                remedy = new DrySkinRemedy();
                break;
            case 6:
                remedy = new SkinNourishment();
                break;
            case 7:
                remedy = new DarkCirclesRemedy();
                break;
            case 8:
                remedy = new DarkSpotsRemedy();
                break;
            case 9:
                running = false;
                cout << YELLOW <<"\nThanks for using Skincare Helper! Stay glowing!\n"<<RESET<<endl;
                break;
            default:
                cout << RED <<"Invalid choice. Please choose between 1 and 9.\n"<<RESET<<endl;
        }

        if (remedy) {
            remedy->display();
            delete remedy;
        }
    }
}
//PERIOD
class PeriodTracker {
private:
    void wait(int ms) {
        Sleep(ms);
    }

    void printDots(int count, int delay = 500) {
        for (int i = 0; i < count; ++i) {
            cout << "." << flush;
            wait(delay);
        }
    }

public:
    PeriodTracker() {
        cout << CYAN <<" PERIOD TRACKER \n"<<RESET<<endl;
        wait(500);
        cout << "LOADING";
        printDots(5);
        wait(1000);
        cout << YELLOW <<"\n\nWelcome! Here's what I can help you with:"<<RESET<<endl;
        printDots(3);
        wait(500);
    }

    // Function to handle invalid input and ensure only numbers are entered
    template <typename T>
    T getValidInput(const string& prompt) {
        T input;
        while (true) {
            cout << prompt;
            cin >> input;
            if (cin.fail()) {
                cin.clear();  // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the invalid input
                cout <<RED << " Invalid input. Please enter a valid number.\n"<<RESET<<endl;
            } else {
                return input;
            }
        }
    }

   void predictNextPeriod() {
    int day, month, year, cycleLength;
    time_t lastPeriodTime;  // Moved outside the loop to fix scope issue

    while (true) {
        // getValidInput used to avoid input errors
        day = getValidInput<int>("\nEnter the **last period start date** (DD): ");
        month = getValidInput<int>("Enter the **month** (MM): ");
        year = getValidInput<int>("Enter the **year** (YYYY): ");

        // Validate range
        if (month < 1 || month > 12 || day < 1 || day > 31 || year < 1900) {
            cout << RED << "\n Invalid date entered. Please try again.\n"<<RESET<<endl;
            continue;
        }

        tm lastPeriod = {};
        lastPeriod.tm_mday = day;
        lastPeriod.tm_mon = month - 1;
        lastPeriod.tm_year = year - 1900;

        lastPeriodTime = mktime(&lastPeriod);
        if (lastPeriodTime == -1) {
            cout << RED << "\n Invalid date. Try again.\n"<<RESET<<endl;
            continue;
        }

        break;
    }

    cycleLength = getValidInput<int>("Enter your **average cycle length** in days: ");
    time_t nextPeriodTime = lastPeriodTime + cycleLength * 24 * 60 * 60;
    tm* nextPeriod = localtime(&nextPeriodTime);

    cout << "\n Your next period is likely to start on: ";
    cout << nextPeriod->tm_mday << "/" << (nextPeriod->tm_mon + 1) << "/" << (nextPeriod->tm_year + 1900) << "\n";
}

    void displayPCOSSymptoms() {
        cout << "\nCommon Symptoms of PCOS:";
        printDots(5);

        string symptoms[] = {
            "1. Irregular periods",
            "2. Excess facial/body hair (hirsutism)",
            "3. Acne or oily skin",
            "4. Unexplained weight gain",
            "5. Thinning hair or hair loss",
            "6. Dark patches on skin",
            "7. Mood swings or depression",
            "8. Persistent fatigue",
            "9. Difficulty getting pregnant",
            "10. Frequent headaches"
        };

        for (const auto& symptom : symptoms) {
            cout << symptom << endl;
            wait(300);
        }

        cout <<GREEN << "\n These symptoms are general indicators. Always consult a doctor for diagnosis.\n"<<RESET<<endl;
    }

    void calculateFertileWindow() {
        int cycleLength, periodStart;
        periodStart = getValidInput<int>("\nEnter the **day of your last period** (e.g., 2 for 2nd): ");
        cycleLength = getValidInput<int>("Enter your **average menstrual cycle length** (typically 28-35 days): ");

        if (cycleLength < 28 || cycleLength > 35) {
            cout << RED <<" Cycle length should be between 28 and 35 days. Please enter a valid cycle length.\n"<<RESET<<endl;
            return;
        }

        int ovulationDay = periodStart + (cycleLength - 14);
        int fertileStart = ovulationDay - 5;
        int fertileEnd = ovulationDay + 1;

        cout << "\nCalculating your fertile window";
        printDots(3);

        cout << "\n Estimated Fertile Window: Day " << fertileStart << " to Day " << fertileEnd;
        cout << "\n Ovulation is most likely on Day " << ovulationDay << ".\n";
        cout << "Note: These are approximate and depend on your regularity.\n";
    }

    void displayRemedies() {
        cout << "\nHelpful Remedies for Period Cramps:"<<endl;
        wait(500);

        string remedies[] = {
            "1. Use a heating pad on your lower belly/back.",
            "2. Drink warm herbal teas like chamomile or ginger.",
            "3. Try light exercise or yoga (e.g., cobra or child's pose).",
            "4. Stay hydrated and reduce caffeine intake.",
            "5. Eat anti-inflammatory foods (berries, greens, bananas).",
            "6. Massage with lavender or peppermint oil.",
            "7. Eat foods rich in magnesium and calcium (e.g., nuts, dairy)."
        };

        for (const auto& remedy : remedies) {
            cout << remedy << endl;
            wait(500);
        }
    }

    void displayMenu() {
        cout << "\n MENU:\n";
        wait(300);
        cout << "1. Predict Next Period\n";
        cout << "2. Show PCOD/PCOS Symptoms\n";
        cout << "3. Calculate Fertile Window\n";
        cout << "4. Remedies for Cramps\n";
        cout << "5. Exit\n";
    }

    void handleChoice() {
        int choice;
        bool running = true;

        while (running) {
            cout << "\nEnter your choice (1-5): ";
            cin >> choice;

            switch (choice) {
                case 1: predictNextPeriod(); break;
                case 2: displayPCOSSymptoms(); break;
                case 3: calculateFertileWindow(); break;
                case 4: displayRemedies(); break;
                case 5:
                    running = false;
                    cout <<CYAN << "\nThank you for using Period Tracker. Stay healthy!\n"<<RESET<<endl;
                    break;
                default:
                    cout << RED <<"Invalid choice. Please enter a number between 1 and 5.\n"<<RESET<<endl;
            }
        }
    }
};
class Period{
public:
    Period(){
    PeriodTracker tracker;
    tracker.displayMenu();
    tracker.handleChoice();}};
char MainMenu() {
    char ch;
    cout << "\n====== HEALTH & WELLNESS ADVISOR ======\n";
    cout << "1. Health Issues\n2. Scalp Issues\n3. Digestive Issues\n4. Skin Issues\n5. Periods\n6. Wounds and Pain\n7.Exit\n";
    cout << "Enter choice: ";
    cin >> ch;
    return ch;
}

void func_call(const string& username) {
    char ch;
    do {
        ch = MainMenu();
        switch(ch) {
            case '1':
                General_health();
                break;
            case '2':
                scalp(username);
                break;
            case '3':
                Digestive();
                break;
            case '4':
                skin(username);
                break;
            case '5':
                Period();
                break;
            case '6':
                Pain();
                break;
            case '7':
                cout << "Thank you for using our service!\n";
                break;

            default:
                cout <<RED << "Feature coming soon or invalid choice.\n"<<RESET<<endl;
                break;
        }
    } while(ch != '7');
}

int main() {
    int choice;
    string username, password;

    cout <<CYAN << "\n=====Welcome to Dadi-Nani ke Nuskhe=====\n" <<RESET<< endl;
    cout << YELLOW <<"Your trusted guide for natural home remedies and wellness tips.\n"<<RESET<< endl;
    cout <<GREEN << "===== Welcome to the User System =====\n"<<RESET<<endl;
    cout << "1. Login\n2. Sign Up\nChoose an option: ";
    cin >> choice;

    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    RegularUser user(username, password);

    if (choice == 1) {
        user.login();
        displayPreviousResults(username);
    } else if (choice == 2) {
        user.signUp();
    } else {
        cout << RED <<"Invalid option selected." <<RESET<< endl;
        return 0;
    }

    func_call(user.getUsername());
    return 0;
}
