#include<iostream>
#include<string>
#include<map>
#include<unordered_set>
#include<vector>
#include<algorithm>
using namespace std;

char Vecchar[] = {'P','p','E','e','L','l','Z','z'};
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
    //pi = new piece('S', "white superpawn");
    //Vec.push_back(pi);
    // pi = new piece('s', "black superpawn");
    // Vec.push_back(pi);
    // pi = new piece('G', "white giraffe");
    // Vec.push_back(pi);
    // pi = new piece('g', "black giraffe");
    // Vec.push_back(pi);
    // pi = new piece('M', "white monkey");
    // Vec.push_back(pi);
    // pi = new piece('m', "black monkey");
    //Vec.push_back(pi);
    pi = new piece('E', "white elephant");
    Vec.push_back(pi);
    pi = new piece('e', "black elephant");
    Vec.push_back(pi);
    pi = new piece('L', "white lion");
    Vec.push_back(pi);
    pi = new piece('l', "black lion");
    Vec.push_back(pi);
    // pi = new piece('C', "white crocodile");
    // Vec.push_back(pi);
    // pi = new piece('c', "black crocodile");
    // Vec.push_back(pi);
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
    for(int v = 0; v < FEN.length(); v++)
    {
        if(FEN[v] == ' ')
        {
            if(FEN[v+1] == 'b')
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
    }
    return player;
}

void LionMoves(piece* pic, piece* opp, string turn)
{
    pic->moves.clear();
    for(int k = 0; k<pic->positions.size(); k++)
    {
        string P = pic->positions[k];
        int row = (P[1]-'0')-1;
        int col = getIt(P[0]);
        if(turn == "black"){
            if(((row+1<3) || (row+1>3&&row+1<7)) && (board[(row)+1][col] < 97 || board[(row)+1][col]=='o'))  //down
                pic->moves.push_back(P+pos[col]+to_string((row+1)+1));
                
            if(((row-1<3&&row-1>-1) || (row-1>3&&row-1<7)) && (board[(row-1)][col] < 97 || board[(row-1)][col]=='o'))  //up
                pic->moves.push_back(P+pos[col]+to_string((row+1)-1));

            if(col-1 > 1 && (board[row][col-1] < 97 || board[row][col-1]=='o'))
                pic->moves.push_back(P+pos[col-1]+to_string((row+1)));  //left

            if(col+1 < 5 && (board[row][col+1] < 97 || board[row][col+1]=='o'))
                pic->moves.push_back(P+pos[col+1]+to_string((row+1)));  //right

            if((((row+1<3) || (row+1>3&&row+1<7)) && col-1 > 1) && (board[(row+1)][col-1] < 97 || board[(row+1)][col-1]=='o'))  //up+left
                pic->moves.push_back(P+pos[col-1]+to_string((row+1)+1));

            if((((row+1<3) || (row+1>3&&row+1<7)) && col+1 < 5 ) && (board[(row+1)][col+1] < 97 || board[(row+1)][col+1]=='o'))   //up+right
                pic->moves.push_back(P+pos[col+1]+to_string((row+1)+1));

            if((((row-1<3&&row-1>-1) || (row-1>3&&row-1<7))&& col-1 > 1) && (board[(row-1)][col-1] < 97 || board[(row-1)][col-1]=='o')) //down+left
                pic->moves.push_back(P+pos[col-1]+to_string((row+1)-1));

            if((((row-1<3&&row-1>-1) || (row-1>3&&row-1<7)) && col+1 < 5) && (board[(row-1)][col+1] < 97 || board[(row-1)][col+1]=='o')) //down+right
                 pic->moves.push_back(P+pos[col+1]+to_string((row+1)-1));

            if(getIt((opp->positions[0])[0]) == col)
            {
                for(int k = row-1; k>-1;k--)
                {
                    if(board[k][col] != 'o' && board[k][col] != 'L')
                    {
                        break;
                    }
                    else if(board[k][col] == 'L')
                    {
                        pic->moves.push_back(P+pos[col]+to_string(k+1));
                    }
                    else
                    {
                        continue;
                    }

                }
            }
            else if(board[4][2] == 'l' && board[2][4] == 'L' && board[3][3] == 'o'){
                pic->moves.push_back(P+pos[4]+to_string((3)));
                    }
            else if(board[4][4] == 'l' && board[2][2] == 'L' && board[3][3] == 'o')
            {
                pic->moves.push_back(P+pos[2]+to_string((3)));
            }
        }
        else
        {
            if(((row+1<3) || (row+1>3&&row+1<7)) && board[row+1][col] > 97)  //down
                pic->moves.push_back(P+pos[col]+to_string((row+1)+1));

            if(((row-1<3&&row-1>-1) || (row-1>3&&row-1<7)) && board[row-1][col] > 97)  //up
                pic->moves.push_back(P+pos[col]+to_string((row+1)-1));

            if(col-1 > 1 && board[row][col-1] > 97)
                pic->moves.push_back(P+pos[col-1]+to_string((row+1)));  //left

            if(col+1 < 5 && board[row][col+1] > 97)
                pic->moves.push_back(P+pos[col+1]+to_string((row+1)));  //right

            if((((row+1<3) || (row+1>3&&row+1<7)) && col-1 > 1) && board[(row+1)][col-1] > 97)  //up+left
                pic->moves.push_back(P+pos[col-1]+to_string((row+1)+1));

            if((((row+1<3) || (row+1>3&&row+1<7)) && col+1 < 5 ) && board[(row+1)][col+1] > 97)   //up+right
                pic->moves.push_back(P+pos[col+1]+to_string((row+1)+1));

            if((((row-1<3&&row-1>-1) || (row-1>3&&row-1<7))&& col-1 > 1) && board[(row-1)][col-1] > 97) //down+left
                pic->moves.push_back(P+pos[col-1]+to_string((row+1)-1));

            if((((row-1<3&&row-1>-1) || (row-1>3&&row-1<7)) && col+1 < 5) && board[(row-1)][col+1] > 97 ) //down+right
                pic->moves.push_back(P+pos[col+1]+to_string((row+1)-1));

            if(getIt((opp->positions[0])[0]) == col)
            {
                for(int k = row+1; k<7;k++)
                {
                    if(board[k][col] != 'o' && board[k][col] != 'l')
                    {
                        break;
                    }
                    else if(board[k][col] == 'l')
                    {
                        pic->moves.push_back(P+pos[col]+to_string((k)+1));
                    }
                    else
                    {
                        continue;
                    }
                 }
             }
             else if(board[4][2] == 'l' && board[2][4] == 'L' && board[3][3] == 'o')
             {
                pic->moves.push_back(P+pos[2]+to_string((5)));
             }
             else if(board[4][4] == 'l' && board[2][2] == 'L' && board[3][3] == 'o')
             {
                pic->moves.push_back(P+pos[4]+to_string((5)));
             }
        }
        sort(pic->moves.begin(), pic->moves.end());
    }
}

piece* SetLion(string player)
{
    piece* lion;
    piece* another;
    for(int q = 0; q < Vec.size(); q++)
    {
        if(player == "black")
        {
            if(Vec[q]->letter == 'l')
            {
                lion = Vec[q];
            }
            else if(Vec[q]->letter == 'L')
                another = Vec[q];
        }
        else
        {
            if(Vec[q]->letter == 'L')
            {
                lion = Vec[q];
            }
            else if(Vec[q]->letter == 'l')
                another = Vec[q];
        }
    }
    LionMoves(lion, another,  player);
    return lion;
}

void ZebraMoves(piece* pic,string turn)
{
    pic->moves.clear();
    for(int k = 0; k<pic->positions.size(); k++)
    {
        string P = pic->positions[k];
        int row = (P[1]-'0')-1;
        int col = getIt(P[0]);
        if(turn == "black"){
            if((row-1>-1 && col+2<7) && (board[row-1][col+2] == 'o' || board[row-1][col+2] < 97)) // right up 
                pic->moves.push_back(P+pos[col+2]+to_string(row));

            if((row+1<7 && col+2<7) && (board[row+1][col+2] == 'o' || board[row+1][col+2] < 97))  //right down
                pic->moves.push_back(P+pos[col+2]+to_string((row+2)));

            if((row+2<7 && col+1<7) && (board[row+2][col+1] == 'o' || board[row+2][col+1] < 97)) //down right
                pic->moves.push_back(P+pos[col+1]+to_string((row+3)));

            if((row+2<7 && col-1>-1) && (board[row+2][col-1] == 'o' || board[row+2][col-1] < 97)) //down left 
                pic->moves.push_back(P+pos[col-1]+to_string((row+3)));

            if((row+1<7 && col-2>-1) && (board[row+1][col-2] == 'o' || board[row+1][col-2] < 97))  //left down
                pic->moves.push_back(P+pos[col-2]+to_string((row+2)));

            if((row-1>-1 && col-2>-1) && (board[row-1][col-2] == 'o' || board[row-1][col-2] < 97)) //left up
                pic->moves.push_back(P+pos[col-2]+to_string((row)));

            if((row-2>-1 && col-1>-1) && (board[row-2][col-1] == 'o' || board[row-2][col-1] < 97))  //up left
                pic->moves.push_back(P+pos[col-1]+to_string((row-1)));

            if((row-2>-1 && col+1<7) && (board[row-2][col+1] == 'o' || board[row-2][col+1] < 97)) //up right
                pic->moves.push_back(P+pos[col+1]+to_string((row-1)));
        }
        else
        {
            if((row-1>-1 && col+2<7) && (board[row-1][col+2] == 'o' || board[row-1][col+2] > 97)) // right up 
                pic->moves.push_back(P+pos[col+2]+to_string(row));

            if((row+1<7 && col+2<7) && (board[row+1][col+2] == 'o' || board[row+1][col+2] > 97))  //right down
                pic->moves.push_back(P+pos[col+2]+to_string((row+2)));

            if((row+2<7 && col+1<7) && (board[row+2][col+1] == 'o' || board[row+2][col+1] > 97)) //down right
                pic->moves.push_back(P+pos[col+1]+to_string((row+3)));

            if((row+2<7 && col-1>-1) && (board[row+2][col-1] == 'o' || board[row+2][col-1] > 97)) //down left 
                pic->moves.push_back(P+pos[col-1]+to_string((row+3)));

            if((row+1<7 && col-2>-1) && (board[row+1][col-2] == 'o' || board[row+1][col-2] > 97))  //left down
                pic->moves.push_back(P+pos[col-2]+to_string((row+2)));

            if((row-1>-1 && col-2>-1) && (board[row-1][col-2] == 'o' || board[row-1][col-2] > 97)) //left up
                pic->moves.push_back(P+pos[col-2]+to_string((row)));

            if((row-2>-1 && col-1>-1) && (board[row-2][col-1] == 'o' || board[row-2][col-1] > 97))  //up left
                pic->moves.push_back(P+pos[col-1]+to_string((row-1)));

            if((row-2>-1 && col+1<7) && (board[row-2][col+1] == 'o' || board[row-2][col+1] > 97)) //up right
                pic->moves.push_back(P+pos[col+1]+to_string((row-1)));
        }
        sort(pic->moves.begin(), pic->moves.end());
    }
}

void ElephantMoves(piece* pic,string turn)
{
    pic->moves.clear();
    for(int k = 0; k<pic->positions.size(); k++)
    {
        string P = pic->positions[k];
        int row = (P[1]-'0')-1;
        int col = getIt(P[0]);
        if(turn == "black"){
            if(row-1 > -1 && (board[row-1][col] == 'o' || board[row-1][col] < 97)) // one up 
                pic->moves.push_back(P+pos[col]+to_string(row));

            if(row-2 > -1 && (board[row-2][col] == 'o' || board[row-2][col] < 97)) // two up 
                pic->moves.push_back(P+pos[col]+to_string(row-1));

            if(row+1 < 7 && (board[row+1][col] == 'o' || board[row+1][col] < 97)) // one down
                pic->moves.push_back(P+pos[col]+to_string(row+2));

            if(row+2 < 7 && (board[row+2][col] == 'o' || board[row+2][col] < 97)) // two down
                pic->moves.push_back(P+pos[col]+to_string(row+3));

            if( col-1>-1 && (board[row][col-1] == 'o' || board[row][col-1] < 97))  // one left 
                pic->moves.push_back(P+pos[col-1]+to_string((row+1)));

            if( col-2>-1 && (board[row][col-2] == 'o' || board[row][col-2] < 97))  // two left 
                pic->moves.push_back(P+pos[col-2]+to_string((row+1)));

            if( col+1<7 && (board[row][col+1] == 'o' || board[row][col+1] < 97))  // one right 
                pic->moves.push_back(P+pos[col+1]+to_string((row+1)));

            if( col+2<7 && (board[row][col+2] == 'o' || board[row][col+2] < 97))  // two right 
                pic->moves.push_back(P+pos[col+2]+to_string((row+1)));
        }
        else
        {
            if(row-1 > -1 && (board[row-1][col] == 'o' || board[row-1][col] >97)) // one up 
                pic->moves.push_back(P+pos[col]+to_string(row));

            if(row-2 > -1 && (board[row-2][col] == 'o' || board[row-2][col] > 97)) // two up 
                pic->moves.push_back(P+pos[col]+to_string(row-1));

            if(row+1 < 7 && (board[row+1][col] == 'o' || board[row+1][col] > 97)) // one down
                pic->moves.push_back(P+pos[col]+to_string(row+2));

            if(row+2 < 7 && (board[row+2][col] == 'o' || board[row+2][col] > 97)) // two down
                pic->moves.push_back(P+pos[col]+to_string(row+3));

            if( col-1>-1 && (board[row][col-1] == 'o' || board[row][col-1] > 97))  // one left 
                pic->moves.push_back(P+pos[col-1]+to_string((row+1)));

            if( col-2>-1 && (board[row][col-2] == 'o' || board[row][col-2] > 97))  // two left 
                pic->moves.push_back(P+pos[col-2]+to_string((row+1)));

            if( col+1<7 && (board[row][col+1] == 'o' || board[row][col+1] > 97))  // one right 
                pic->moves.push_back(P+pos[col+1]+to_string((row+1)));

            if( col+2<7 && (board[row][col+2] == 'o' || board[row][col+2] > 97))  // two right 
                pic->moves.push_back(P+pos[col+2]+to_string((row+1)));
        }
            sort(pic->moves.begin(), pic->moves.end());
    }

}

void PawnMoves(piece* pic, string turn)
{
    pic->moves.clear();
    for(int k = 0; k<pic->positions.size(); k++)
    {
        string P = pic->positions[k];
        int row = (P[1]-'0')-1;
        int col = getIt(P[0]);
        if(turn == "black"){
            if(row > 2){
                if(row-1>-1 && (board[row-1][col] == 'o' || board[row-1][col] < 97)) // down 
                    pic->moves.push_back(P+pos[col]+to_string(row));

                if((col+1 < 7 && row-1>-1) && (board[row-1][col+1] == 'o' || board[row-1][col+1] < 97)) // down right
                    pic->moves.push_back(P+pos[col+1]+to_string(row));

                if((col-1 > -1 && row-1>-1) && (board[row-1][col-1] == 'o' || board[row-1][col-1] < 97)) // down left
                    pic->moves.push_back(P+pos[col-1]+to_string(row));
            }
            else
            {
                if(row-1>-1 && (board[row-1][col] == 'o' || board[row-1][col] < 97)) // down 
                    pic->moves.push_back(P+pos[col]+to_string(row));

                if((col+1 < 7 && row-1>-1) && (board[row-1][col+1] == 'o' || board[row-1][col+1] < 97)) // down right
                    pic->moves.push_back(P+pos[col+1]+to_string(row));

                if((col-1 > -1 && row-1>-1) && (board[row-1][col-1] == 'o' || board[row-1][col-1] < 97)) // down left
                    pic->moves.push_back(P+pos[col-1]+to_string(row));

                if(row+1<7 && board[row+1][col] == 'o' ) //one up 
                    pic->moves.push_back(P+pos[col]+to_string(row+2));
                
                if(row+2<7 && board[row+2][col] == 'o' && board[row+1][col] == 'o') //two up 
                    pic->moves.push_back(P+pos[col]+to_string(row+3));
            }

        }
        else
        {
            if(row < 4){
                if(row+1<7 && (board[row+1][col] == 'o' || board[row+1][col] > 97)) // up 
                    pic->moves.push_back(P+pos[col]+to_string(row+2));

                if((col+1 < 7 && row+1<7) && (board[row+1][col+1] == 'o' || board[row+1][col+1] > 97)) // up right
                    pic->moves.push_back(P+pos[col+1]+to_string(row+2));

                if((col-1 > -1 && row+1<7) && (board[row+1][col-1] == 'o' || board[row+1][col-1] > 97)) // up left
                    pic->moves.push_back(P+pos[col-1]+to_string(row+2));
            }
            else
            {
                if(row+1<7 && (board[row+1][col] == 'o' || board[row+1][col] > 97)) // up 
                    pic->moves.push_back(P+pos[col]+to_string(row+2));

                if((col+1 < 7 && row+1<7) && (board[row+1][col+1] == 'o' || board[row+1][col+1] > 97)) // up right
                    pic->moves.push_back(P+pos[col+1]+to_string(row+2));

                if((col-1 > -1 && row+1<7) && (board[row+1][col-1] == 'o' || board[row+1][col-1] > 97)) // up left
                    pic->moves.push_back(P+pos[col-1]+to_string(row+2));

                if(row-1 > -1 && board[row-1][col] == 'o') //one down
                    pic->moves.push_back(P+pos[col]+to_string(row));
                
                if( row-2 > -1 && board[row-2][col] == 'o' && board[row-1][col] == 'o') //two down 
                    pic->moves.push_back(P+pos[col]+to_string(row-1));
            }
        }
            sort(pic->moves.begin(), pic->moves.end());
    }
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

void printBoard()
{
    for(int i = 0; i<7;i++)
    {
        for(int j = 0; j<7; j++)
        {
            cout<<board[6-i][j]<<" ";
        }
        cout<<endl;
    }  cout<<"============================================================="<<endl;
}

void Print_next_move(piece* pie)
{   
    if(!pie->moves.empty())
    cout<<pie->moves[0];
    
    for(int k = 1; k< pie->moves.size(); k++)
    {
            cout<<" "<<pie->moves[k];
    } 
    cout<<endl;
}

piece* findPiece(string player, char piece_play)
{
    piece* congo;
    for(int q = 0; q < Vec.size(); q++)
    {
        if(player == "black")
        {
            if(Vec[q]->letter == piece_play)
            {
                congo = Vec[q];
                break;
            }
        }
        else
        {
            if(Vec[q]->letter == (char)toupper(piece_play))
            {
                congo = Vec[q];
                break;
            }
        }
    }
    return congo;
}

vector<string> generateMoves(string FEN)
{
    unordered_set<char> Piece;
    vector<string> moves;
    string player = getPlayer(FEN);
    piece* congo = nullptr;

    if(player == "black")
    {
        for(char k : FEN){
            if(k == ' ')
                break;
            else if(k == '/' || isdigit(k))
                continue;
            else if(k > 97)
                Piece.insert(k);
        }
    }
    else if(player == "white")
    {
        for(char k : FEN){
            if(k == ' ')
                break;
            else if(k == '/' || isdigit(k))
                continue;
            else if(k < 97)
                Piece.insert(k);
        }
    }

    for(auto elm: Piece)
    {
        if(elm == 'l' || elm == 'L')
        {
            congo = SetLion(player);
        }
        else if(elm == 'z' || elm == 'Z')
        {
            congo = findPiece(player,'z');
            ZebraMoves(congo, player);
        }
        else if(elm == 'e' || elm == 'E')
        {
            congo = findPiece(player,'e');
            ElephantMoves(congo, player);
        }
        else if(elm == 'p' || elm == 'P')
        {
            congo = findPiece(player,'p');
            PawnMoves(congo, player);
        }

        for(auto str: congo->moves)
        {
            moves.push_back(str);
        }
    }

    sort(moves.begin(), moves.end());

    return moves;
}

int MobilityScore(string FEN){
    int score;
    vector<string> black_moves;
    vector<string> white_moves;

    string player = getPlayer(FEN);
    if(player == "black"){
        black_moves = generateMoves(FEN);
        for(int k = FEN.size()-1; k > 0; k--){
            if(FEN[k] == ' '){
                FEN[k-1] = 'w';
                white_moves = generateMoves(FEN);
                break;
            }
        }
    }
    else{
        white_moves = generateMoves(FEN);
        for(int k = FEN.size()-1; k > 0; k--){
            if(FEN[k] == ' '){
                FEN[k-1] = 'b';
                black_moves = generateMoves(FEN);
                break;
            }
        }
    }
    score = white_moves.size()-black_moves.size();
    return score;
}

int AttackScore(string FEN, string player){
    int attackScore = 0, black = 0, white = 0;

    vector<string>moves = generateMoves(FEN);
    if(player == "black"){
        for(auto m: moves){
            int row = (m[3]-'0')-1;
            int col = getIt(m[2]);
            if(board[row][col] < 97 && board[row][col] != 'o'){
                black += 1;
                if(board[row][col] == 'L')
                    black +=10;
            }
        }
        for(int k = FEN.size()-1; k > 0; k--){
            if(FEN[k] == ' '){
                FEN[k-1] = 'w';
                moves = generateMoves(FEN);
                break;
            }
        }
        for(auto m: moves){
            int row = (m[3]-'0')-1;
            int col = getIt(m[2]);
            if(board[row][col] > 97 && board[row][col] != 'o'){
                white += 1;
                if(board[row][col] == 'l')
                    white +=10;
            }
        }
    }
    else{
        for(auto m: moves){
            int row = (m[3]-'0')-1;
            int col = getIt(m[2]);
            if(board[row][col] > 97 && board[row][col] != 'o'){
                white += 1;
                if(board[row][col] == 'l')
                    white +=10;
            }
        }
        for(int k = FEN.size()-1; k > 0; k--){
            if(FEN[k] == ' '){
                FEN[k-1] = 'b';
                moves = generateMoves(FEN);
                break;
            }
        }
        for(auto m: moves){
            int row = (m[3]-'0')-1;
            int col = getIt(m[2]);
            if(board[row][col] < 97 && board[row][col] != 'o'){
                black += 1;
                if(board[row][col] == 'L')
                    black +=10;
            }
        }
    }
    attackScore = white - black;
    return attackScore;
}

int Evaluation(string FEN)
{
    int black = 0, white = 0, row_score;
    bool bl = false, wh = false;
    string turn;

    for(char k: FEN){
        
        turn = getPlayer(FEN);

        if(k == ' ')
            break;
        else if(k == '/' || isdigit(k))
            continue;
        else if(k =='p')
            black+=100;
        else if(k =='P')
            white+=100;
        else if(k =='e')
            black+=200;
        else if(k =='E')
            white+=200;
        else if(k =='z')
            black+=300;
        else if(k =='Z')
            white+=300;
        else if(k =='l')
            bl = true;
        else if(k =='L')
            wh = true;

    }
    if(bl == false){
        row_score = 10000;
    }
    else if(wh == false)
        row_score = -10000;
    else if(black == 0 && white == 0)
        row_score = 0;
    else
        row_score = (white-black) + MobilityScore(FEN) + AttackScore(FEN, turn);
    
    if(turn == "white")
        return row_score ;
    else
        return -row_score;
}

void Reset(string FEN){
    Vec.clear();
    board_init();
    createPieces();
    int j = 6, k = 0;
    for(char v: FEN)
    {
        if(isdigit(v))
            k += v - '0';
        else if(v == '/')
        {
            j--;
            k = 0;
        }
        else if(v == ' ')
        {
            break;
        }
        else
        {
            int m = getCharPos(v);
            Vec[m]->setPosition(j,k);
            k++;   
        }  
    }
}

string ExecuteMove(string Fen, string NextMove){

    string player = getPlayer(Fen); 
    int moVecount = getMoVecount(Fen); 

    int count = 0;
    string state, FEN = "";
    vector<char> river; 

    if(player == "black"){
        for(int i = 0; i<7; i++){
            if(board[3][i] != 'o' && board[3][i] > 97)
                river.push_back(pos[i]);
        }
    }
    else
    {
        for(int i = 0; i<7; i++){
            if(board[3][i] != 'o' && board[3][i] < 97)
                river.push_back(pos[i]);
        }
    }


    int pos_row = (NextMove[1]-'0')-1;
    int pos_col = getIt(NextMove[0]);

    string position = NextMove.substr(0,2);
    string nxtPosition = NextMove.substr(2,3);

    int mov_row = (NextMove[3]-'0')-1;
    int mov_col = getIt(NextMove[2]);

    if(board[mov_row][mov_col] == 'l')
        state = "White wins";
    else if(board[mov_row][mov_col] == 'L')
        state = "Black wins";
    else
        state = "Continue";
        
    char let = board[pos_row][pos_col];
    char rem = board[mov_row][mov_col];
    board[mov_row][mov_col] = let;
    board[pos_row][pos_col] = 'o';

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    piece* curr = findPiece(player,let);
    curr->positions.erase(remove(curr->positions.begin(), curr->positions.end(), position), curr->positions.end()); 
    curr->positions.push_back(nxtPosition);
    if(rem != 'o'){
        string p;
        if(rem > 97)
        p = "black";
        else p = "white";

        piece* remv = findPiece(p,rem);
        remv->positions.erase(remove(remv->positions.begin(), remv->positions.end(), nxtPosition), remv->positions.end()); 
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if(pos_row == 3 && mov_row ==3){
        board[3][mov_col] = 'o';
    }

    if(player == "black")
    {
        for(char k: river)
        {
            pos_col = getIt(k);
            if( board[3][pos_col] != 'o' && board[3][pos_col] > 97){
                board[3][pos_col] = 'o';
            }
            else continue;
        }

    }
    else{
        for(char k: river)
        {
            pos_col = getIt(k);
            if( board[3][pos_col] != 'o' && board[3][pos_col] < 97){
                board[3][pos_col] = 'o';
            }
            else continue;
        }
    }

    for(int i = 0; i<7;i++)
    {   
        count = 0;
        if(FEN != "")
            FEN = FEN + "/";

        for(int j = 0; j<7; j++)
        {
            if(board[6-i][j] == 'o')
            {
                count++;
            }
            else if(count != 0){
                FEN = FEN+to_string(count);
                FEN = FEN+board[6-i][j];
                count = 0;
            }
            else{
                FEN = FEN+board[6-i][j];
            }
        }
        if(count != 0)
        FEN = FEN+to_string(count); 
    }
    

    if(player == "black")
    {
       FEN = FEN+" "+"w"+" "+to_string(moVecount+1)+'\n'+state; 
    }
    else{
        FEN = FEN+" "+"b"+" "+to_string(moVecount)+'\n'+state;
    }
    return FEN;
}

bool isGameOver(string FEN)
{
    int eval = Evaluation(FEN);
    if(eval == 10000 || eval == -10000)
        return true;
    return false;
}

int MinMax(string Currstate, int depth)
{
    string nextState;
    int eval;
    string player = getPlayer(Currstate);
    vector<string>moves;
    if(isGameOver(Currstate) || depth <= 0)
        return Evaluation(Currstate);

    int value = -2000000;
    moves = generateMoves(Currstate);
    for(auto move: moves)
    {
        nextState = ExecuteMove(Currstate, move);
        eval = -MinMax(nextState, depth-1);
        value = max(value, eval);
        if(value == 10000)
            break;
        Reset(Currstate);
    }
    return value;
}

int AlphaBeta(string Currstate, int depth, int alpha, int beta)
{
    if(isGameOver(Currstate) || depth <= 0)
        return Evaluation(Currstate);

    string nextState;
    int eval;
    string player = getPlayer(Currstate);
    vector<string>moves;

    //int value = -2000000;
    moves = generateMoves(Currstate);
    for(auto move: moves)
    {
        nextState = ExecuteMove(Currstate, move);
        eval = -AlphaBeta(nextState, depth-1, -beta, -alpha);
        if(eval >= beta)
            return beta;
        if(eval > alpha)
            alpha = eval;
        Reset(Currstate);
    }
    return alpha;
}

int main()
{
    int count, movesplayed;
    string player, moves = "";
    vector<string> evaluate;
    vector<string> NM;

    cin >> count;
    cin.ignore();
    
    for(int i = 0; i < count; i++)
    {
        string str, next_move;
        getline(cin, str);
        //getline(cin, next_move);
        evaluate.push_back(str);
        //NM.push_back(next_move);
    }

    for(int i = 0 ; i< evaluate.size();i++)
    {
        string eval = evaluate[i];
       //string nexM = NM[i];   
        moves = "";
        Reset(eval);

        //player = getPlayer(eval);
        //movesplayed = getMoVecount(eval);
        //generateMoves(eval);
        //cout<<Evaluation(eval)<<endl;
        cout<<AlphaBeta(eval, 4, INT16_MIN+1, INT16_MAX-1)<<endl;
       // cout<<"before"<<endl;
       // printBoard();
        //string FEN = ExecuteMove(eval,nexM);
        //cout<<MinMax(eval, 2)<<endl;
        //print_Init_pos();
        //cout<<"after"<<endl;
        //cout<<FEN<<endl;
       //printBoard();
        //piece* congo = findPiece(player, 'l');
        //cout<<"Side to play: "<<player<<endl;
        //Print_next_move(congo);
        //cout<<endl;
    }
    return 0;
}