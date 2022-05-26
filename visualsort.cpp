#include "raylib.h"
#include <vector>

#define ScreenWidth 1200
#define ScreenHeight 800
#define MinSW 500
#define MinSH 800
#define FPS 245

//Pstates
#define NORMAL 0
#define SORTED 1
#define SELECTED 2


//Algoritmi di ordinamento
#define QUICK 0
#define BUBBLE 1
#define INSERTION 2
#define MERGE 3
#define SELECTION 4

//Variabili globali
int ArraySize = 50;
int SortingSpeed = 245;
int SortingAlg = BUBBLE;
bool ShouldRandomizeArray = true;
bool ShouldShowMenuScreen = true;
bool ShouldShowStartOptions = false;
bool ShouldStartSorting = false;
bool ShouldShowEndingScreen = false;
bool TitlePressed = false;


bool addSpeed = false;
bool subSpeed = false;
bool addSize = false;
bool subSize = false;
bool toggleAlgorithm = false;

bool NormalSize = false;
bool NormalSpeed = false;


//Schermate
void ShowMenuScreen();
void ShowStartOptions();
void ShowEndingScreen();


void SortArray(int operation);
void ChangeSpeed(char operation, int &value);
void ChangeSize(char operation, int &value);
void Start_Button(float size, float font, char Start[]);

void Bubble_sort(std::vector<std::pair<int, int>> &a);
void DrawArray(std::vector<std::pair<int, int>> a);
void RandomizeArray(std::vector<std::pair<int, int>> &a);
void Button(float x, float y, char *Text, Color color, bool &state);
void Title_Button(float size, char Title_Text[]);
Color FindColorForPillar(int pState);




std::vector<std::pair<int, int>> a(ArraySize);

int main(){
    //Configuring the window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(ScreenWidth, ScreenHeight, "Visual Sort");
    SetWindowMinSize(MinSW, MinSH);
    SetTargetFPS(FPS);


    

    while(!WindowShouldClose()){
        
        if(ShouldShowMenuScreen) ShowMenuScreen();

        ShouldShowStartOptions = false;
        if(TitlePressed) ShouldShowStartOptions = true;
        
        //Da implementare, Cambia l'algoritmo
        //if(AlgorithmPressed) ChangeAlgorithm();

        if(ShouldShowStartOptions) ShowStartOptions();

        if(ShouldRandomizeArray) RandomizeArray(a);
        
        if(ShouldStartSorting) {
            ShouldShowMenuScreen = false;
            ShouldShowStartOptions = false;

            SortArray(SortingAlg);

            ShouldStartSorting = false;
            ShouldShowEndingScreen = true;
        }

        if (ShouldShowEndingScreen){ShowEndingScreen();}
        
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void DrawArray(std::vector<std::pair<int, int>> a){
    float BarWidth = (float) GetScreenWidth() / ArraySize;

    for (int i = 0; i < ArraySize; i++){
        Color color = FindColorForPillar(a[i].second);
        DrawRectangleV(Vector2{(float) i*BarWidth, (float) GetScreenHeight() - a[i].first}, 
                       Vector2{BarWidth, (float) a[i].first}, 
                       color);
    }
}

Color FindColorForPillar(int pState){
    switch (pState){

    case SELECTED: return RED; break;

    case SORTED: return GREEN; break;

    default: return WHITE; break;
    }
}

void RandomizeArray(std::vector<std::pair<int, int>> &a){
    for (int i = 0; i < ArraySize; i++) 
        {a[i] = {GetRandomValue(40, MinSW + 100), NORMAL};}
    
    ShouldRandomizeArray = false;
}

void ShowMenuScreen(){
    float font = (2.5 * GetScreenWidth()) / 100;
    char Title_Text[] = "Visual Sort";
    float tmp = MeasureText(Title_Text, font) / 2;
    Title_Button(tmp, Title_Text);

    DrawArray(a);
}
//TBI
void ShowToggleButton(){

}

void ShowStartOptions() {
    float font = (2.5 * GetScreenWidth() / 100);


    char StartText[] = "Start Sorting!";
    float tmp = (27*GetScreenWidth()) / 100;
    Start_Button(tmp, font, StartText);

    tmp += MeasureText(StartText, font) + 75;
    char RandomizeArrayText[] = "Randomize Array!";
    Button(tmp, GetScreenHeight()/20 + font*2, RandomizeArrayText, DARKPURPLE, ShouldRandomizeArray);


    addSpeed = false;
    subSpeed = false;
    addSize = false;
    subSize = false;

    toggleAlgorithm = false;

    NormalSize = false;
    NormalSpeed = false;

    tmp = (84.2 * GetScreenWidth()) / 100;
    char TimeButtonText[] = "Speed";

    Button(tmp, GetScreenHeight()/20 + font*2, TimeButtonText, DARKPURPLE, NormalSpeed);

    if (NormalSpeed){
        ChangeSpeed('/', SortingSpeed);
        return;
    }

    tmp += MeasureText(TimeButtonText, font) +20;
    char SpeedPlusButtonText[] = "+";
    Button(tmp, GetScreenHeight()/20 + font*2, SpeedPlusButtonText, YELLOW, addSpeed);

    if (addSpeed){
        ChangeSpeed('+', SortingSpeed);
        return;
    }

    tmp += MeasureText(SpeedPlusButtonText, font) + 20;
    char SpeedMinusButtonText[] = "-";
    Button(tmp, GetScreenHeight()/20 + font*2, SpeedMinusButtonText, YELLOW, subSpeed);

    if (subSpeed){
        ChangeSpeed('-', SortingSpeed);
        return;
    }

    tmp = (5* GetScreenWidth()) / 100;
    char SizeButtonText[] = "Size";
    Button(tmp, GetScreenHeight()/20 + font*2, SizeButtonText, DARKPURPLE, NormalSize);

    if (NormalSize){
        ChangeSize('/', ArraySize);
        return;
    }

    tmp += MeasureText(SizeButtonText, font) + 20;
    char SizePlusButton[] = "+";
    Button(tmp, GetScreenHeight()/20 + font*2, SizePlusButton, YELLOW, addSize);

    if (addSize){
        ChangeSize('+', ArraySize);
        return;
    }

    tmp += MeasureText(SizePlusButton, font) + 20;
    char SizeMinusButton[] = "-";
    Button(tmp, GetScreenHeight()/20 + font*2, SizeMinusButton, YELLOW, subSize);


    if (subSize){
        ChangeSize('-', ArraySize);
        return;
    }

 

}

void ShowEndingScreen(){
    DrawArray(a);
    ShouldShowMenuScreen = true;
    ShouldShowStartOptions = false;
}

void ChangeSpeed(char operation, int &value){
    switch (operation)
    {
        case '-':
        value = value-10 > 0 ? value-10 : value; 
        break;
        
        case '+':
        value += 10;
        break;

        default:
        value = 245;
        break;
    }

    SetTargetFPS(SortingSpeed);
}

void ChangeSize(char operation, int &value){
    switch (operation)
    {
        case '-':
        if (value > 5){
            value -= 5;
            for (int i = 0; i < 5; i++){a.pop_back();}
        }break;
            
        case '+':
        value += 5;
        for(int i = 0; i < 5; i++){a.push_back({GetRandomValue(40, MinSW + 100), NORMAL});}
        break;

        default:
        while(ArraySize > 50){ArraySize--; a.pop_back();}
        while(ArraySize < 50){ArraySize++; a.push_back({GetRandomValue(40, MinSW + 100), NORMAL});}
        break;
    }

    for (int i = 0; i < ArraySize; i++){a[i].second = NORMAL;}
    DrawArray(a);
}



void Start_Button(float size, float font, char Start[]){
    Button(size, GetScreenHeight()/20 + font*2, Start, DARKPURPLE, ShouldStartSorting);
}

void Title_Button(float size, char Title_Text[]){
    Color color;
    if (TitlePressed) color = GREEN;
    else color = YELLOW;

    Button(GetScreenWidth()/2 - size, GetScreenHeight()/20, Title_Text, color, TitlePressed);

}
//TBI
void Toggle_Button(float size, char Toggle_Text[]){
}

void Button(float x, float y, char *Text, Color color, bool &state){
    float font = (2.5 * GetScreenWidth() / 100);
    Rectangle r1 = {
        .x = x, 
        .y = y, 
        .width = (float) MeasureText(Text, font),
        .height = (float) font
    };

    if (CheckCollisionPointRec(GetMousePosition(), r1)){
        DrawText(Text, x, y, font, RED);

        if(IsMouseButtonPressed(0)){
            
            if (state) state = false;
            else state = true;
        }
    }                
    else{DrawText(Text, x, y, font, color);}          
}

void SortArray(int operation){


    switch(operation)
    {

        case QUICK:
        //Quick_Sort(a);
        break;

        case BUBBLE:
        Bubble_sort(a);
        break;
        
        case INSERTION:
        //Insertion_Sort(a);
        break;

        case MERGE:
        //Merge_Sort(a);
        break;

        case SELECTION:
        //Selection_sort(a);
        break;
    }

    DrawArray(a); 
}

void Bubble_sort(std::vector<std::pair<int, int>> &a) {
    
    int endingPoint = ArraySize;
    bool swapped;
    do{
        swapped = false;



        for (int i = 0; i < endingPoint-1; i++){
            
            a[i].second = SELECTED;
            
            if(a[i] > a[i+1]){
                std::swap(a[i], a[i+1]);
                swapped = true;
            }
        
            BeginDrawing();
            ClearBackground(BLACK);

            for (int k = ArraySize - 1; k >= endingPoint; k--){a[k].second = SORTED;}
            DrawArray(a);
            for (int k = i; k >= 0; k--){a[k].second = NORMAL;}
            EndDrawing();
        }    
        endingPoint--;
    }while(swapped);

    for (int i = ArraySize - 1; i >= 0; i--){a[i].second = SORTED;}

}
