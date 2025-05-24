#include <iostream>
#include <string>
#include <utility>

using namespace std;
int runda = 1;
int zmiana(char l)
{
    int u;
    l = tolower(l);
    switch(l)
    {
        case 'a':
            u = 0;
            break;
        case 'b':
            u = 1;
            break;
        case 'c':
            u = 2;
            break;
        case 'd':
            u = 3;
            break;
        case 'e':
            u = 4;
            break;
        case 'f':
            u = 5;
            break;
        case 'g':
            u = 6;
            break;
        case 'h':
            u = 7;
            break;
        default:
            u = -1;
            break;
    }
    return u;
}

class piece
{
public:
    char colour;
    pair<int,int> position;
    char name;
    bool moved;

    piece(char c,int x,int y,char n) : colour(c), position(make_pair(x,y)), name(n), moved(false) {}
    piece() : colour(' '), position(make_pair(0,0)), name(' ') {}
    ~piece() {}

};

class pawn: public piece
{
public:

    pawn(char c,int x,int y,char n) : piece(c,x,y,n) {}

};
class rook: public piece
{
public:

    rook(char c,int x,int y,char n) : piece(c,x,y,n) {}


};
class knight: public piece
{
public:

    knight(char c,int x,int y,char n) : piece(c,x,y,n) {}
};
class bishop: public piece
{
public:

    bishop(char c,int x,int y,char n) : piece(c,x,y,n) {}
};
class queen: public piece
{
public:

    queen(char c,int x,int y,char n) : piece(c,x,y,n) {}
};
class king: public piece
{
public:

    king(char c,int x,int y,char n) : piece(c,x,y,n) {}
};
class board
{
public:
    piece board_placement[8][8];
    board()
    {
        for(int i = 0; i < 8; ++i)
            {
            for(int j = 0; j < 8; ++j)
            {
                board_placement[i][j] = piece(NULL,0,0,'.');
            }
        }
    }

    void display()
    {
        cout << "   A B C D E F G H" << endl;
        for(int i=0;i<8;i++)
        {
            cout << i+1 << "[ ";
            for(int j=0;j<8;j++)
            {
                cout << board_placement[i][j].name<<" ";
            }
            cout << "]" << endl;
        }
    }

    void add_piece(piece p)
    {
        board_placement[p.position.first][p.position.second] = p;
    }
    void move_piece_no_check(piece &p, int x, int y)
    {
        char names[8][8];
        for_movements(names);//plansza z samymi nazwami
        bool ruchy[8][8];
        if(ruchy[x][y]==true)
            {
                for(int i=0;i<8;i++)
                {
                    for(int j=0;j<8;j++)
                    {
                        cout << ruchy[i][j];
                    }
                    cout << endl;
                }
                p.moved = true;
                int old_x = p.position.first;
                int old_y = p.position.second;
                p.position = make_pair(x, y);
                board_placement[x][y] = p;
                board_placement[old_x][old_y] = piece(NULL, NULL, NULL, '.');
    }
    }
    bool move_piece(piece &p, int x, int y)
    {
        if(p.name=='.')
        {
            cout << "wybierz figure" << endl;
            runda--;
            return 0;

        }

        char names[8][8];
        for_movements(names);//plansza z samymi nazwami
        bool ruchy[8][8];

        switch(p.name)
        {
            case 'P':
                possible_moves_black_pawn(names,ruchy,p);
                break;
            case 'p':
                possible_moves_white_pawn(names,ruchy,p);
                break;
            case 'r':
                possible_moves_rook(names,ruchy,p);
                break;
            case 'R':
                possible_moves_rook(names,ruchy,p);
                break;
            case 'b':
                possible_moves_bishop(names,ruchy,p);
                break;
            case 'B':
                possible_moves_bishop(names,ruchy,p);
                break;
            case 'h':
                possible_moves_knight(names,ruchy,p);
                break;
            case 'H':
                possible_moves_knight(names,ruchy,p);
                break;
            case 'Q':
                possible_moves_queen(names,ruchy,p);
                    break;
            case 'q':
                possible_moves_queen(names,ruchy,p);
                    break;
            case 'k':
                possible_moves_king(names,ruchy,p);
                    break;
            case 'K':
                possible_moves_king(names,ruchy,p);
                    break;
            default:
                break;
        }

            if(ruchy[x][y]==true)
            {
                p.moved = true;
                int old_x = p.position.first;
                int old_y = p.position.second;
                p.position = make_pair(x, y);
                board_placement[x][y] = p;
                board_placement[old_x][old_y] = piece(NULL, NULL, NULL, '.');

                return 1;
            }
            else
            {
                cout << "niepoprawny ruch" << endl;
                runda--;
                return 0;
            }
    }
    char colour_check(char n)
    {
        if(islower(n))
        {
            n = 'w';
        }
        else
            n ='b';
        return n;
    }
    void for_movements(char names_only[8][8])
    {
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                names_only[i][j] = board_placement[i][j].name;
            }
        }
    }
    void possible_moves_black_pawn(char names[8][8],bool ruchy[8][8], piece &p)
    {
        int a = p.position.first;
        int b = p.position.second;
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                ruchy[i][j] = false;
            }
        }
        if(b>0 && names[a-1][b-1]!='.' && islower(names[a-1][b-1]))//bicie po skosie w lewo
        {
            ruchy[a-1][b-1] = true;
        }
        if(b<8 && names[a-1][b+1]!='.' && islower(names[a-1][b+1]))//bicie po skosie w prawo
        {
            ruchy[a-1][b+1] = true;
        }
        if(names[a-1][b]=='.')//ruch jeden prosto
        {
            ruchy[a-1][b] = true;
        }
        if(names[a-1][b]=='.' && names[a-2][b]=='.' && p.moved==false)//ruch dwa prosto
        {
            ruchy[a-2][b] = true;
        }
    }
    void possible_moves_white_pawn(char names[8][8],bool ruchy[8][8], piece &p)
    {
        int a = p.position.first;
        int b = p.position.second;
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                ruchy[i][j] = false;
            }
        }
        if(b>0 && names[a+1][b-1]!='.' && isupper(names[a+1][b-1]))//bicie po skosie w lewo
        {
            ruchy[a+1][b-1] = true;
        }
        if(b<8 && names[a+1][b+1]!='.' && isupper(names[a+1][b+1]))//bicie po skosie w prawo
        {
            ruchy[a+1][b+1] = true;
        }
        if(names[a+1][b]=='.')//ruch jeden prosto
        {
            ruchy[a+1][b] = true;
        }
        if(names[a+1][b]=='.' && names[a+2][b]=='.' && p.moved==false)//ruch dwa prosto
        {
            ruchy[a+2][b] = true;
        }
    }
    void possible_moves_rook(char names[8][8],bool ruchy[8][8], piece &p)
    {
        int a = p.position.first;
        int b = p.position.second;
        char colour1, colour2;
        colour1 = p.colour;
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                ruchy[i][j] = false;
            }
        }
        for(int i=b-1;i>=0;i--)//ruch w lewo
        {
            colour2 = colour_check(names[a][i]);
            if(names[a][i]=='.')
            {
               ruchy[a][i] = true;
            }
            else if(colour1==colour2)//ten sam kolor
            {
                break;
            }
            else//inne kolory
            {
                ruchy[a][i] = true;
                break;
            }

        }
        for(int i=b+1;i<=8;i++)//ruch w prawo
        {
            colour2 = colour_check(names[a][i]);
            if(names[a][i]=='.')
            {
               ruchy[a][i] = true;
            }
            else if(colour1==colour2)//ten sam kolor
            {
                break;
            }
            else//inne kolory
            {
                ruchy[a][i] = true;
                break;
            }

        }
        for(int i=a-1;i>=0;i--)//ruch w gore
        {
            colour2 = colour_check(names[i][b]);
            if(names[i][b]=='.')
            {
               ruchy[i][b] = true;
            }
            else if(colour1==colour2)//ten sam kolor
            {
                break;
            }
            else//inne kolory
            {
                ruchy[i][b] = true;
                break;
            }

        }
        for(int i=a+1;i<=8;i++)//ruch w dol
        {
            colour2 = colour_check(names[i][b]);
            if(names[i][b]=='.')
            {
               ruchy[i][b] = true;
            }
            else if(colour1==colour2)//ten sam kolor
            {
                break;
            }
            else//inne kolory
            {
                ruchy[i][b] = true;
                break;
            }

        }
    }
    void possible_moves_bishop(char names[8][8], bool ruchy[8][8], piece &p)
    {
    int a = p.position.first;
    int b = p.position.second;
    char colour1, colour2;
    colour1 = p.colour;

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            ruchy[i][j] = false;
        }
    }

    // Ruch góra-lewo
    for(int i = a-1, j = b-1; i >= 0 && j >= 0; i--, j--)
    {
        colour2 = colour_check(names[i][j]);
        if(names[i][j] == '.')
        {
            ruchy[i][j] = true;
        } else if(colour1 == colour2)
        { // ten sam kolor
            break;
        } else
        { // inne kolory
            ruchy[i][j] = true;
            break;
        }
    }

    // Ruch góra-prawo
    for(int i = a-1, j = b+1; i >= 0 && j < 8; i--, j++)
    {
        colour2 = colour_check(names[i][j]);
        if(names[i][j] == '.')
        {
            ruchy[i][j] = true;
        } else if(colour1 == colour2)
        { // ten sam kolor
            break;
        } else
        { // inne kolory
            ruchy[i][j] = true;
            break;
        }
    }

    // Ruch dó³-lewo
    for(int i = a+1, j = b-1; i < 8 && j >= 0; i++, j--)
    {
        colour2 = colour_check(names[i][j]);
        if(names[i][j] == '.')
        {
            ruchy[i][j] = true;
        } else if(colour1 == colour2)
        { // ten sam kolor
            break;
        } else
        { // inne kolory
            ruchy[i][j] = true;
            break;
        }
    }

    // Ruch dó³-prawo
    for(int i = a+1, j = b+1; i < 8 && j < 8; i++, j++)
    {
        colour2 = colour_check(names[i][j]);
        if(names[i][j] == '.')
        {
            ruchy[i][j] = true;
        } else if(colour1 == colour2)
        { // ten sam kolor
            break;
        } else
        { // inne kolory
            ruchy[i][j] = true;
            break;
        }
    }
    }
    void possible_moves_knight(char names[8][8], bool ruchy[8][8], piece &p)
    {
    int a = p.position.first;
    int b = p.position.second;
    char colour1, colour2;
    colour1 = p.colour;

    // Reset ruchy array
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            ruchy[i][j] = false;
        }
    }

    // Define knight moves
    int moves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

    for (int i = 0; i < 8; ++i)
    {
        int x = a + moves[i][0];
        int y = b + moves[i][1];

        if (x >= 0 && x < 8 && y >= 0 && y < 8)
        {
            colour2 = colour_check(names[x][y]);
            if (names[x][y] == '.' || colour2 != colour1)
            {
                ruchy[x][y] = true;
            }
        }
    }
    }
    void possible_moves_queen(char names[8][8], bool ruchy[8][8], piece &p)
    {
        bool ruchy1[8][8];
        bool ruchy2[8][8];
        possible_moves_rook(names,ruchy1,p);
        possible_moves_bishop(names,ruchy2,p);
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                ruchy[i][j] = ruchy1[i][j] || ruchy2[i][j];
            }
        }
    }
    void possible_moves_king(char names[8][8], bool ruchy[8][8], piece &p)
    {
    int a = p.position.first;
    int b = p.position.second;
    char colour1 = p.colour;
    char colour2;

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            ruchy[i][j] = false;
        }
    }

    int moves[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (int i = 0; i < 8; ++i)
    {
        int x = a + moves[i][0];
        int y = b + moves[i][1];

        if (x >= 0 && x < 8 && y >= 0 && y < 8)
        {
            colour2 = colour_check(names[x][y]);
            if (names[x][y] == '.' || colour2 != colour1)
            {
                ruchy[x][y] = true;
            }
        }
    }
    }
    void roszada(piece &krol,piece &wieza)
    {
        if(krol.moved==0 && wieza.moved==0)
        {
            int high,low;
            char kierunek;
            if(krol.position.second>wieza.position.second)
            {
                high = krol.position.second;
                low = wieza.position.second;
                kierunek = 'l';
            }
            else
            {
                low = krol.position.second;
                high = wieza.position.second;
                kierunek = 'p';
            }

            bool check = true;
            for(int i=low+1;i<high;i++)
            {
                if(board_placement[krol.position.first][i].name!='.')
                {
                    check = false;
                }

            }
            if(check == true)
            {
                if(kierunek=='l')
                {
                    move_piece_no_check(krol,krol.position.first,krol.position.second-2);
                    move_piece_no_check(wieza,krol.position.first,krol.position.second-1);
                }
                else
                {
                    move_piece_no_check(krol,krol.position.first,krol.position.second+2);
                    move_piece_no_check(wieza,krol.position.first,krol.position.second+1);
                }

            }
        }
    }
    void promotion(piece &p)
    {
        int x,y;
        int choice;
        x = p.position.first;
        y = p.position.second;
        cout << "Jaka chcesz figure: 1 - rook, 2 - bishop, 3 - knight, 4 - queen: ";
        cin >> choice;
        //piece figura;
        switch(choice)
        {
            case 1:
                board_placement[x][y] = rook(p.colour, x, y, 'r');
                break;
            case 2:
                 board_placement[x][y] = bishop(p.colour, x, y, 'b');
                break;
            case 3:
                board_placement[x][y] = knight(p.colour, x, y, 'h');
                break;
            case 4:
                board_placement[x][y] = queen(p.colour, x, y, 'q');
                break;
        }
    }

};

board start()
{
    board plansza;
    //BIALE PIONY
    pawn p1('w',1,0,'p');
    plansza.add_piece(p1);
    pawn p2('w',1,1,'p');
    plansza.add_piece(p2);
    pawn p3('w',1,2,'p');
    plansza.add_piece(p3);
    pawn p4('w',1,3,'p');
    plansza.add_piece(p4);
    pawn p5('w',1,4,'p');
    plansza.add_piece(p5);
    pawn p6('w',1,5,'p');
    plansza.add_piece(p6);
    pawn p7('w',1,6,'p');
    plansza.add_piece(p7);
    pawn p8('w',1,7,'p');
    plansza.add_piece(p8);
    //KONIEC BIALYCH PIONOW
    //BIALE FIGURY
    rook r1('w',0,0,'r');
    plansza.add_piece(r1);
    rook r2('w',0,7,'r');
    plansza.add_piece(r2);

    knight kn1('w',0,1,'h');
    plansza.add_piece(kn1);
    knight kn2('w',0,6,'h');
    plansza.add_piece(kn2);

    bishop b1('w',0,2,'b');
    plansza.add_piece(b1);
    bishop b2('w',0,5,'b');
    plansza.add_piece(b2);

    queen q1('w',0,3,'q');
    plansza.add_piece(q1);
    king k2('w',0,4,'k');
    plansza.add_piece(k2);
    //KONIEC BIALYCH FIGUR
    //CZARNE PIONY
    pawn P1('b',6,0,'P');
    plansza.add_piece(P1);
    pawn P2('b',6,1,'P');
    plansza.add_piece(P2);
    pawn P3('b',6,2,'P');
    plansza.add_piece(P3);
    pawn P4('b',6,3,'P');
    plansza.add_piece(P4);
    pawn P5('b',6,4,'P');
    plansza.add_piece(P5);
    pawn P6('b',6,5,'P');
    plansza.add_piece(P6);
    pawn P7('b',6,6,'P');
    plansza.add_piece(P7);
    pawn P8('b',6,7,'P');
    plansza.add_piece(P8);
    //KONIEC CZARNYCH PIONOW
    //CZARNE FIGURY
    rook R1('b',7,0,'R');
    plansza.add_piece(R1);
    rook R2('b',7,7,'R');
    plansza.add_piece(R2);

    knight KN1('b',7,1,'H');
    plansza.add_piece(KN1);
    knight KN2('b',7,6,'H');
    plansza.add_piece(KN2);

    bishop B1('b',7,2,'B');
    plansza.add_piece(B1);
    bishop B2('b',7,5,'B');
    plansza.add_piece(B2);

    queen Q1('b',7,3,'Q');
    plansza.add_piece(Q1);
    king K2('b',7,4,'K');
    plansza.add_piece(K2);
    //KONIEC CZARNYCH FIGUR



    return plansza;
}
size_t stringLength(const string& str)
{
    return str.length();
}


int main()
{
    string x,y;
    board plansza = start();
    //int runda = 1;
    int player;
    while (1)
    {
        player = runda%2;
        for(int i=0;i<8;i++)//czarne promocja
        {
            if(plansza.board_placement[0][i].name=='P')
            {
                cout << "PROMOCJA";
                plansza.promotion(plansza.board_placement[0][i]);
            }
        }
        for(int i=0;i<8;i++)//biale promocja
        {
            if(plansza.board_placement[7][i].name=='p')
            {
                cout << "PROMOCJA";
                plansza.promotion(plansza.board_placement[7][i]);
            }
        }
        cout << "Runda:" << runda << endl;
        plansza.display();
        cout << "POLE Z KTOREGO SIE RUSZASZ:";
        cin >> x;
        cout << "POLE NA KTORE SIE RUSZASZ:";
        cin >> y;
        int x1, x2, y1, y2;
        x1 = zmiana(x[0]);
        y1 = (x[1] - '0') - 1;
        x2 = zmiana(y[0]);
        y2 = (y[1] - '0') - 1;
        if ((player == 1 && plansza.board_placement[y1][x1].colour == 'b') || (player == 0 && plansza.board_placement[y1][x1].colour == 'w'))
        {
            cout << "nie twoja tura" << endl;
            continue;
        }
        if(x=="roszada")
        {
            int krol,wieza;
            piece krolD, wiezaD;
            cout << "podaj krola: bialy - 1,czarny - 2: ";
            cin >> krol;
            cout << "podaj wieze: czarna-lewa - 1, czarna prawa - 2, biala-lewa - 3, biala-prawa -4: ";
            cin >> wieza;
            switch(krol)
            {
            case 1:
                krolD = plansza.board_placement[0][4];
                break;
            case 2:
                krolD = plansza.board_placement[7][4];
                break;

            }
            switch(wieza)
            {
            case 1:
                wiezaD = plansza.board_placement[7][0];
                break;
            case 2:
                wiezaD = plansza.board_placement[7][7];
                break;
            case 3:
                wiezaD = plansza.board_placement[0][0];
                break;
            case 4:
                wiezaD = plansza.board_placement[0][7];
                break;
            }
            plansza.roszada(krolD,wiezaD);
        }
        else
        {
            while ((stringLength(x)>2 || stringLength(y)>2 || x1 < 0 || x1 > 7 || x2 < 0 || x2 > 7 || y1 < 0 || y1 > 7 || y2 < 0 || y2 > 7))
            {

                cout << "bledne dane podaj jeszcze raz" << endl;
                //plansza.display();
                cout << "POLE Z KTOREGO SIE RUSZASZ:";
                cin >> x;
                cout << "POLE NA KTORE SIE RUSZASZ:";
                cin >> y;
                x1 = zmiana(x[0]);
                x2 = (x[1] - '0') - 1;
                y1 = zmiana(y[0]);
                y2 = (y[1] - '0') - 1;

            }

        plansza.move_piece(plansza.board_placement[y1][x1],y2 ,x2 );
        }

        runda++;


        cout << endl;
    }


    return 0;
}

