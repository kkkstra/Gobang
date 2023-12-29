#include "gobangai.h"

Player GetOppositePlayer(Player player) {
	return (player == BLACK_PLAYER) ? WHITE_PLAYER : BLACK_PLAYER;
}

BoardPiece GetOppositePiece(BoardPiece piece) {
	return (piece == BLACK_PIECE) ? WHITE_PIECE : BLACK_PIECE;
}

BoardPiece PlayerToPiece(Player player) {
    return (player == BLACK_PLAYER) ? BLACK_PIECE : WHITE_PIECE;
}

Player PieceToPlayer(BoardPiece piece) {
    return (piece == BLACK_PIECE) ? BLACK_PLAYER : WHITE_PLAYER;
}

GobangAi::GobangAi() {}

void GobangAi::InitGobangAi() {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			board[i][j] = NO_PIECE;
		}
	}
	round = 0;
    InitTypeTable();
}


void GobangAi::InitTypeTable() {
    memset(typeTable, 0, sizeof(typeTable)); // 全部设为0
    // 白连5,ai赢
    typeTable[2][2][2][2][2][2] = WIN;
    typeTable[2][2][2][2][2][0] = WIN;
    typeTable[0][2][2][2][2][2] = WIN;
    typeTable[2][2][2][2][2][1] = WIN;
    typeTable[1][2][2][2][2][2] = WIN;
    typeTable[3][2][2][2][2][2] = WIN; // 边界考虑
    typeTable[2][2][2][2][2][3] = WIN;
    // 黑连5,ai输
    typeTable[1][1][1][1][1][1] = LOSE;
    typeTable[1][1][1][1][1][0] = LOSE;
    typeTable[0][1][1][1][1][1] = LOSE;
    typeTable[1][1][1][1][1][2] = LOSE;
    typeTable[2][1][1][1][1][1] = LOSE;
    typeTable[3][1][1][1][1][1] = LOSE;
    typeTable[1][1][1][1][1][3] = LOSE;
    // 白活4
    typeTable[0][2][2][2][2][0] = FLEX4;
    // 黑活4
    typeTable[0][1][1][1][1][0] = flex4;
    // 白活3
    typeTable[0][2][2][2][0][0] = FLEX3;
    typeTable[0][0][2][2][2][0] = FLEX3;
    typeTable[0][2][0][2][2][0] = FLEX3;
    typeTable[0][2][2][0][2][0] = FLEX3;
    // 黑活3
    typeTable[0][1][1][1][0][0] = flex3;
    typeTable[0][0][1][1][1][0] = flex3;
    typeTable[0][1][0][1][1][0] = flex3;
    typeTable[0][1][1][0][1][0] = flex3;
    // 白活2
    typeTable[0][2][2][0][0][0] = FLEX2;
    typeTable[0][2][0][2][0][0] = FLEX2;
    typeTable[0][2][0][0][2][0] = FLEX2;
    typeTable[0][0][2][2][0][0] = FLEX2;
    typeTable[0][0][2][0][2][0] = FLEX2;
    typeTable[0][0][0][2][2][0] = FLEX2;
    // 黑活2
    typeTable[0][1][1][0][0][0] = flex2;
    typeTable[0][1][0][1][0][0] = flex2;
    typeTable[0][1][0][0][1][0] = flex2;
    typeTable[0][0][1][1][0][0] = flex2;
    typeTable[0][0][1][0][1][0] = flex2;
    typeTable[0][0][0][1][1][0] = flex2;
    // 白活1
    typeTable[0][2][0][0][0][0] = FLEX1;
    typeTable[0][0][2][0][0][0] = FLEX1;
    typeTable[0][0][0][2][0][0] = FLEX1;
    typeTable[0][0][0][0][2][0] = FLEX1;
    // 黑活1
    typeTable[0][1][0][0][0][0] = flex1;
    typeTable[0][0][1][0][0][0] = flex1;
    typeTable[0][0][0][1][0][0] = flex1;
    typeTable[0][0][0][0][1][0] = flex1;

    int p1, p2, p3, p4, p5, p6, x, y, ix, iy; // x:左5中黑个数,y:左5中白个数,ix:右5中黑个数,iy:右5中白个数
    for (p1 = 0; p1 < 4; ++p1)
    {
        for (p2 = 0; p2 < 3; ++p2)
        {
            for (p3 = 0; p3 < 3; ++p3)
            {
                for (p4 = 0; p4 < 3; ++p4)
                {
                    for (p5 = 0; p5 < 3; ++p5)
                    {
                        for (p6 = 0; p6 < 4; ++p6)
                        {
                            x = y = ix = iy = 0;

                            if (p1 == 1)
                                x++;
                            else if (p1 == 2)
                                y++;

                            if (p2 == 1)
                            {
                                x++;
                                ix++;
                            }
                            else if (p2 == 2)
                            {
                                y++;
                                iy++;
                            }

                            if (p3 == 1)
                            {
                                x++;
                                ix++;
                            }
                            else if (p3 == 2)
                            {
                                y++;
                                iy++;
                            }

                            if (p4 == 1)
                            {
                                x++;
                                ix++;
                            }
                            else if (p4 == 2)
                            {
                                y++;
                                iy++;
                            }

                            if (p5 == 1)
                            {
                                x++;
                                ix++;
                            }
                            else if (p5 == 2)
                            {
                                y++;
                                iy++;
                            }

                            if (p6 == 1)
                                ix++;
                            else if (p6 == 2)
                                iy++;

                            if (p1 == 3 || p6 == 3)
                            { // 有边界
                                if (p1 == 3 && p6 != 3)
                                { // 左边界
                                    // 白冲4
                                    if (ix == 0 && iy == 4)
                                    { // 若右边有空位是活4也没关系，因为活4权重远大于冲4，再加上冲4权重变化可以不计
                                        if (typeTable[p1][p2][p3][p4][p5][p6] == 0)
                                            typeTable[p1][p2][p3][p4][p5][p6] = BLOCK4;
                                    }
                                    // 黑冲4
                                    if (ix == 4 && iy == 0)
                                    {
                                        if (typeTable[p1][p2][p3][p4][p5][p6] == 0)
                                            typeTable[p1][p2][p3][p4][p5][p6] = block4;
                                    }
                                    // 白眠3
                                    if (ix == 0 && iy == 3)
                                    {
                                        if (typeTable[p1][p2][p3][p4][p5][p6] == 0)
                                            typeTable[p1][p2][p3][p4][p5][p6] = BLOCK3;
                                    }
                                    // 黑眠3
                                    if (ix == 3 && iy == 0)
                                    {
                                        if (typeTable[p1][p2][p3][p4][p5][p6] == 0)
                                            typeTable[p1][p2][p3][p4][p5][p6] = block3;
                                    }
                                    // 白眠2
                                    if (ix == 0 && iy == 2)
                                    {
                                        if (typeTable[p1][p2][p3][p4][p5][p6] == 0)
                                            typeTable[p1][p2][p3][p4][p5][p6] = BLOCK2;
                                    }
                                    // 黑眠2
                                    if (ix == 2 && iy == 0)
                                    {
                                        if (typeTable[p1][p2][p3][p4][p5][p6] == 0)
                                            typeTable[p1][p2][p3][p4][p5][p6] = block2;
                                    }
                                }
                                else if (p6 == 3 && p1 != 3)
                                { // 右边界
                                    // 白冲4
                                    if (x == 0 && y == 4)
                                    {
                                        if (typeTable[p1][p2][p3][p4][p5][p6] == 0)
                                            typeTable[p1][p2][p3][p4][p5][p6] = BLOCK4;
                                    }
                                    // 黑冲4
                                    if (x == 4 && y == 0)
                                    {
                                        if (typeTable[p1][p2][p3][p4][p5][p6] == 0)
                                            typeTable[p1][p2][p3][p4][p5][p6] = block4;
                                    }
                                    // 黑眠3
                                    if (x == 3 && y == 0)
                                    {
                                        if (typeTable[p1][p2][p3][p4][p5][p6] == 0)
                                            typeTable[p1][p2][p3][p4][p5][p6] = BLOCK3;
                                    }
                                    // 白眠3
                                    if (x == 0 && y == 3)
                                    {
                                        if (typeTable[p1][p2][p3][p4][p5][p6] == 0)
                                            typeTable[p1][p2][p3][p4][p5][p6] = block3;
                                    }
                                    // 黑眠2
                                    if (x == 2 && y == 0)
                                    {
                                        if (typeTable[p1][p2][p3][p4][p5][p6] == 0)
                                            typeTable[p1][p2][p3][p4][p5][p6] = BLOCK2;
                                    }
                                    // 白眠2
                                    if (x == 0 && y == 2)
                                    {
                                        if (typeTable[p1][p2][p3][p4][p5][p6] == 0)
                                            typeTable[p1][p2][p3][p4][p5][p6] = block2;
                                    }
                                }
                            }
                            else
                            { // 无边界
                                // 白冲4
                                if ((x == 0 && y == 4) || (ix == 0 && iy == 4))
                                {
                                    if (typeTable[p1][p2][p3][p4][p5][p6] == 0)
                                        typeTable[p1][p2][p3][p4][p5][p6] = BLOCK4;
                                }
                                // 黑冲4
                                if ((x == 4 && y == 0) || (ix == 4 && iy == 0))
                                {
                                    if (typeTable[p1][p2][p3][p4][p5][p6] == 0)
                                        typeTable[p1][p2][p3][p4][p5][p6] = block4;
                                }
                                // 白眠3
                                if ((x == 0 && y == 3) || (ix == 0 && iy == 3))
                                {
                                    if (typeTable[p1][p2][p3][p4][p5][p6] == 0)
                                        typeTable[p1][p2][p3][p4][p5][p6] = BLOCK3;
                                }
                                // 黑眠3
                                if ((x == 3 && y == 0) || (ix == 3 && iy == 0))
                                {
                                    if (typeTable[p1][p2][p3][p4][p5][p6] == 0)
                                        typeTable[p1][p2][p3][p4][p5][p6] = block3;
                                }
                                // 白眠2
                                if ((x == 0 && y == 2) || (ix == 0 && iy == 2))
                                {
                                    if (typeTable[p1][p2][p3][p4][p5][p6] == 0)
                                        typeTable[p1][p2][p3][p4][p5][p6] = BLOCK2;
                                }
                                // 黑眠2
                                if ((x == 2 && y == 0) || (ix == 2 && iy == 0))
                                {
                                    if (typeTable[p1][p2][p3][p4][p5][p6] == 0)
                                        typeTable[p1][p2][p3][p4][p5][p6] = block2;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void GobangAi::run() {
	srand(time(NULL));

	if (round == 0) {
        PlayRound1();
	} else {
		MinMaxSearch(aiPlayer, 0, -INF, INF);
	}

	round++;
	qDebug() << "AI drop: " << nextDrop.x() << " " << nextDrop.y();
    emit AiDropPiece(nextDrop.x(), nextDrop.y());
}

void GobangAi::PlayRound1() {
	// 若ai先手，则下在正中心
	if (board[7][7] == NO_PIECE) {
		SetNextDrop(7, 7);
	} else {
		const int dir[2] = { -1, 1 };
		SetNextDrop(7 + dir[rand() % 2], 7 + dir[rand() % 2]);
	}
}

int GobangAi::MinMaxSearch(const Player player, int depth, int alpha, int beta) {
    qDebug() << "depth: " << depth;
    int score = Evaluate();
    if (depth >= BASE_DEPTH) {
        qDebug() << "score: " << score;
        return score;
    }

    QPoint points[POINTS_BUF_SIZE];
    QPoint* p_now = points, * p_end = points + SeekPoints(points, player);

    if (player == aiPlayer) { // max层
        while (p_now != p_end) {
            board[p_now->x()][p_now->y()] = PlayerToPiece(player);
            score = MinMaxSearch(GetOppositePlayer(player), depth + 1, alpha, beta);
            board[p_now->x()][p_now->y()] = NO_PIECE;
            if (score > alpha) {
                alpha = score;
                if (depth == BASE_DEPTH) {
                    SetNextDrop(p_now->x(), p_now->y());
                }
            }
            if (beta <= alpha)
                break; // 剪枝
            p_now++;
        }
        return alpha;
    } else { // min层
        while (p_now != p_end) {
            board[p_now->x()][p_now->y()] = PlayerToPiece(player);
            score = MinMaxSearch(GetOppositePlayer(player), depth + 1, alpha, beta);
            board[p_now->x()][p_now->y()] = NO_PIECE;
            if (score < beta)
                beta = score;
            if (beta <= alpha)
                break; // 剪枝
            p_now++;
        }
        return beta;
    }
}

int GobangAi::SeekPoints(QPoint* points, Player player) {
    player = BLACK_PLAYER;
    int r, c, i, j, cnt;
    bool notFound;
    int nearCnt;

    for (r = cnt = 0; r < 15; r++) {
        for (c = 0; c < 15; c++) {
            if (board[r][c] == NO_PIECE) {
                notFound = true;
                nearCnt = 0;
                for (i = r - 2; i <= r + 2 && notFound; i++) {
                    for (j = c - 2; j <= c + 2; j++) {
                        if (i >= 0 && i < 15 && j >= 0 && j < 15 && board[i][j])
                            ++nearCnt;
                        if (nearCnt == NEAR_CNT) {
                            points[cnt] = QPoint(r, c);
                            ++cnt;
                            notFound = false;
                            break;
                        }
                    }
                }
            }
        }
    }
    return cnt;
}

int GobangAi::Evaluate() {
    // 各棋型权重
    int weight[17] = { 0, 1000000, -10000000, 50000, -100000, 400, -100000, 400, -8000, 20, -50, 20, -50, 1, -3, 1, -3 };

    int i, j, type;
    int record[17]; // 统计4个方向上每种棋型的个数
    memset(record, 0, sizeof(record));

    int A[17][17]; // 包括边界的虚拟大棋盘,board[i][j]=A[i-1][j-1],3表示边界
    for (int i = 0; i < 17; ++i)
        A[i][0] = 3;
    for (int i = 0; i < 17; ++i)
        A[i][16] = 3;
    for (int j = 0; j < 17; ++j)
        A[0][j] = 3;
    for (int j = 0; j < 17; ++j)
        A[16][j] = 3;
    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 15; ++j)
            A[i + 1][j + 1] = board[i][j];

    // 横向棋型
    for (i = 1; i <= 15; ++i) {
        for (j = 0; j < 12; ++j) {
            type = typeTable[A[i][j]][A[i][j + 1]][A[i][j + 2]][A[i][j + 3]][A[i][j + 4]][A[i][j + 5]];
            record[type]++;
        }
    }
    // 竖向棋型
    for (j = 1; j <= 15; ++j) {
        for (i = 0; i < 12; ++i) {
            type = typeTable[A[i][j]][A[i + 1][j]][A[i + 2][j]][A[i + 3][j]][A[i + 4][j]][A[i + 5][j]];
            record[type]++;
        }
    }
    // 左上至右下棋型
    for (i = 0; i < 12; ++i) {
        for (j = 0; j < 12; ++j) {
            type = typeTable[A[i][j]][A[i + 1][j + 1]][A[i + 2][j + 2]][A[i + 3][j + 3]][A[i + 4][j + 4]][A[i + 5][j + 5]];
            record[type]++;
        }
    }
    // 右上至左下棋型
    for (i = 0; i < 12; ++i) {
        for (j = 5; j < 17; ++j) {
            type = typeTable[A[i][j]][A[i + 1][j - 1]][A[i + 2][j - 2]][A[i + 3][j - 3]][A[i + 4][j - 4]][A[i + 5][j - 5]];
            record[type]++;
        }
    }

    int score = 0;
    for (i = 1; i < 17; ++i) {
        score += record[i] * weight[i]; // 计分
    }

    return score;
}

void GobangAi::SetPlayer(Player player) {
	aiPlayer = player;
	humanPlayer = (player == BLACK_PLAYER) ? WHITE_PLAYER : BLACK_PLAYER;
}

void GobangAi::SetNextDrop(int x, int y) {
	nextDrop = QPoint(x, y);
	//emit AiDropPiece(nextDrop);
}

void GobangAi::DropPiece(int x, int y, BoardPiece piece) {
	board[x][y] = piece;
}

void GobangAi::TakePiece(int x, int y) {
    board[x][y] = NO_PIECE;
}

void GobangAi::DecreaseRound() {
    round--;
}