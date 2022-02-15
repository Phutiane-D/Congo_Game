#include<iostream>
#include<string>
#include<map>
#include<unordered_set>
#include<vector>
#include<algorithm>
using namespace std;

char Vecchar[] = {'P','p','S','s','G','g','M','m','E','e','L','l','C','c','Z','z'};
vector<vector<char> >board(7, vector<char> (7, 'o'));
char pos[] = {'a','b','c','d','e','f','g'};

class piece
{
    public:
        char letter;
        string name;
        vector<string> positions;
        vector<string> moves;
        
        piece(char let, string nm)
        {
            letter = let;
            name = nm;
        }

        void setPosition(int row, int col)
        {
            positions.push_back(pos[col]+to_string(row+1));
            board[row][col] = letter;
            sort(positions.begin(), positions.end());
        }
};

vector<piece*> Vec;

void board_init()
{
    for(int i = 0; i<7; i++)
    {
        for(int j = 0; j<7; j++)
        {
            board[i][j] = 'o';
        }
    }
}

int getIt(char r)
{
    for(int s = 0; s<7; s++)
    {
        if(pos[s] == r)
            return s;
    }
    return 0;
}

void createPieces()
{
    piece* pi = new piece('P', "white pawn");
    Vec.push_back(pi);
    pi = new piece('p', "black pawn");
    Vec.push_back(pi);
    pi = new piece('S', "white superpawn");
    Vec.push_back(pi);
    pi = new piece('s', "black superpawn");
    Vec.push_back(pi);
    pi = new piece('G', "white giraffe");
    Vec.push_back(pi);
    pi = new piece('g', "black giraffe");
    Vec.push_back(pi);
    pi = new piece('M', "white monkey");
    Vec.push_back(pi);
    pi = new piece('m', "black monkey");
    Vec.push_back(pi);
    pi = new piece('E', "white elephant");
    Vec.push_back(pi);
    pi = new piece('e', "black elephant");
    Vec.push_back(pi);
    pi = new piece('L', "white lion");
    Vec.push_back(pi);
    pi = new piece('l', "black lion");
    Vec.push_back(pi);
    pi = new piece('C', "white crocodile");
    Vec.push_back(pi);
    pi = new piece('c', "black crocodile");
    Vec.push_back(pi);
    pi = new piece('Z', "white zebra");
    Vec.push_back(pi);
    pi = new piece('z', "black zebra");
    Vec.push_back(pi);
}

int getCharPos(char ch)
{
    for(int i = 0; i<16; i++)
    {
        if(Vecchar[i] == ch)
            return i;
        else
            continue;
    }
    return 0;
}

string getPlayer(string FEN)
{
    string player;
    
    for(int v = FEN.length()-1; v > 0; v--)
    {
            if(FEN[v] == 'b')
            {
                player = "black";
                break;
            }
            else 
            {
                player = "white";
                break;
            }
    }
    return player;
}


int getMoVecount(string FEN)
{
    string moves = "";
    int count;
    for(int v = 0; v < FEN.length(); v++)
    {
        if(FEN[v] == ' ')
        {
            for(int k = v+3; k<FEN.length();k++)
                moves += FEN[k];
            break;
        }
    }
    count = stoi(moves);
    return count;
}

void print_Init_pos()
{
    for(int k = 0; k<Vec.size(); k++)
    {
        cout<<Vec[k]->name<<":";
        for(auto pos: Vec[k]->positions)
            cout<<" "<<pos;

        cout<<endl;
    }
}

int main()
{
    int count, movesplayed;
    string player;
    createPieces();
    vector<string> evaluate;

    cin >> count;
    cin.ignore();
    
    for(int i = 0; i < count; i++)
    {
        string str;
        getline(cin, str);
        evaluate.push_back(str);
       
    }

    for(int i = 0 ; i< evaluate.size();i++)
    {
        string eval = evaluate[i];
        //player = getPlayer(eval);
        int row = 6;
        int col = 0;
        for(char str_chr : eval)
        {
            if(str_chr == '/'){
                row--;
            }
            else if(isdigit(str_chr))
            {
                col+= str_chr-'0';
            }
            else if(str_chr == ' '){
                break;
            }
            else{
                int charpos = getCharPos(str_chr);
                piece* Piece = Vec[charpos];
                Piece->setPosition(row, col);
            }
            col = 0;
        }
        print_Init_pos();
    }
    return 0;
}