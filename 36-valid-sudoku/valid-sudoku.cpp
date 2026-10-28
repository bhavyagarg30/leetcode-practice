class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        bool row[9][9] = {}, col[9][9] = {}, box[9][9] = {};

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') continue;

                int n = board[i][j] - '1';
                int b = (i / 3) * 3 + j / 3;

                if (row[i][n] || col[j][n] || box[b][n])
                    return false;

                row[i][n] = col[j][n] = box[b][n] = true;
            }
        }
        return true;
    }
};