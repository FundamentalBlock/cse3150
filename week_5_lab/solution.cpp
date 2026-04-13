#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int compute_score(const vector<vector<int>>& board);

vector<int> compress_row(const vector<int>& row) {
    vector<int> compressed;
    compressed.reserve(4);
    copy_if(row.begin(), row.end(), back_inserter(compressed), [](int value) {
        return value != 0;
    });
    compressed.resize(4, 0);
    return compressed;
}

vector<int> merge_row(vector<int> row) {
    for (size_t i = 0; i + 1 < row.size(); ++i) {
        if (row[i] != 0 && row[i] == row[i + 1]) {
            row[i] *= 2;
            row[i + 1] = 0;
            ++i;
        }
    }
    return compress_row(row);
}

void write_board_csv(const vector<vector<int>>& board, bool first, const string& stage) {
    ios_base::openmode mode = ios::app;
    if (first) mode = ios::trunc;
    ofstream fout("game_output.csv", mode);
    if (!fout) return;

    fout << stage << ",";
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            fout << board[r][c];
            if (!(r == 3 && c == 3)) fout << ",";
        }
    }
    fout << "\n";
}

void read_board_csv(vector<vector<int>>& board) {
    ifstream fin("game_input.csv");

    string line;
    int r = 0;
    while (getline(fin, line) && r < 4) {
        stringstream ss(line);
        string cell;
        int c = 0;
        while (getline(ss, cell, ',') && c < 4) {
            try {
                board[r][c] = stoi(cell);
            } catch (...) {
                board[r][c] = 0;
            }
            c++;
        }
        r++;
    }
}

void print_board(const vector<vector<int>>& board) {
    cout << "Score: " << compute_score(board) << "\n";
    for (const auto& row : board) {
        for (int value : row) {
            if (value == 0) {
                cout << ".\t";
            } else {
                cout << value << "\t";
            }
        }
        cout << "\n";
    }
}

void spawn_tile(vector<vector<int>>& board) {
    vector<pair<int, int>> empty;
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (board[r][c] == 0) empty.emplace_back(r, c);
        }
    }

    if (empty.empty()) return;

    static mt19937 gen(42);
    uniform_int_distribution<> pos_dist(0, static_cast<int>(empty.size()) - 1);
    uniform_int_distribution<> val_dist(1, 10);

    auto [r, c] = empty[pos_dist(gen)];
    board[r][c] = (val_dist(gen) == 1 ? 4 : 2);
}

bool move_left(vector<vector<int>>& board) {
    bool moved = false;
    for (auto& row : board) {
        vector<int> updated = merge_row(compress_row(row));
        if (updated != row) {
            row = updated;
            moved = true;
        }
    }
    return moved;
}

bool move_right(vector<vector<int>>& board) {
    bool moved = false;
    for (auto& row : board) {
        vector<int> updated = row;
        reverse(updated.begin(), updated.end());
        updated = merge_row(compress_row(updated));
        reverse(updated.begin(), updated.end());
        if (updated != row) {
            row = updated;
            moved = true;
        }
    }
    return moved;
}

bool move_up(vector<vector<int>>& board) {
    bool moved = false;
    for (int c = 0; c < 4; ++c) {
        vector<int> column(4);
        for (int r = 0; r < 4; ++r) column[r] = board[r][c];

        vector<int> updated = merge_row(compress_row(column));
        if (updated != column) moved = true;

        for (int r = 0; r < 4; ++r) board[r][c] = updated[r];
    }
    return moved;
}

bool move_down(vector<vector<int>>& board) {
    bool moved = false;
    for (int c = 0; c < 4; ++c) {
        vector<int> column(4);
        for (int r = 0; r < 4; ++r) column[r] = board[r][c];

        vector<int> updated = column;
        reverse(updated.begin(), updated.end());
        updated = merge_row(compress_row(updated));
        reverse(updated.begin(), updated.end());
        if (updated != column) moved = true;

        for (int r = 0; r < 4; ++r) board[r][c] = updated[r];
    }
    return moved;
}

int compute_score(const vector<vector<int>>& board) {
    int score = 0;
    for (const auto& row : board) {
        for (int val : row) {
            score += val;
        }
    }
    return score;
}

int main() {
    vector<vector<int>> board(4, vector<int>(4, 0));
    read_board_csv(board);

    stack<vector<vector<int>>> history;
    bool first = true;

    while (true) {
        print_board(board);
        if (first) {
            write_board_csv(board, true, "initial");
            first = false;
        }

        cout << "Move (w=up, a=left, s=down, d=right), u=undo, q=quit: ";
        char cmd;
        if (!(cin >> cmd)) break;
        if (cmd == 'q') break;

        if (cmd == 'u') {
            if (!history.empty()) {
                board = history.top();
                history.pop();
                print_board(board);
                write_board_csv(board, false, "undo");
            }
            continue;
        }

        vector<vector<int>> prev = board;
        bool moved = false;
        if (cmd == 'a') moved = move_left(board);
        else if (cmd == 'd') moved = move_right(board);
        else if (cmd == 'w') moved = move_up(board);
        else if (cmd == 's') moved = move_down(board);

        if (moved) {
            history.push(prev);
            write_board_csv(board, false, "merge");
            spawn_tile(board);
            write_board_csv(board, false, "spawn");
        } else {
            write_board_csv(board, false, "invalid");
        }
    }

    return 0;
}
