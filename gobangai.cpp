#include "gobangai.h"

int startTime, costTime;

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
			board[i][j] = NO_CHESS;
		}
	}
	round = 0;
    InitTypeTable();
}


void GobangAi::InitTypeTable() {
    memset(typeTable, 0, sizeof(typeTable));

    typeTable[2][2][2][2][2][2] = WIN;
    typeTable[2][2][2][2][2][0] = WIN;
    typeTable[0][2][2][2][2][2] = WIN;
    typeTable[2][2][2][2][2][1] = WIN;
    typeTable[1][2][2][2][2][2] = WIN;
    typeTable[3][2][2][2][2][2] = WIN;
    typeTable[2][2][2][2][2][3] = WIN;

    typeTable[1][1][1][1][1][1] = LOSE;
    typeTable[1][1][1][1][1][0] = LOSE;
    typeTable[0][1][1][1][1][1] = LOSE;
    typeTable[1][1][1][1][1][2] = LOSE;
    typeTable[2][1][1][1][1][1] = LOSE;
    typeTable[3][1][1][1][1][1] = LOSE;
    typeTable[1][1][1][1][1][3] = LOSE;

    typeTable[0][2][2][2][2][0] = FLEX4;

    typeTable[0][1][1][1][1][0] = flex4;

    typeTable[0][2][2][2][0][0] = FLEX3;
    typeTable[0][0][2][2][2][0] = FLEX3;
    typeTable[0][2][0][2][2][0] = FLEX3;
    typeTable[0][2][2][0][2][0] = FLEX3;

    typeTable[0][1][1][1][0][0] = flex3;
    typeTable[0][0][1][1][1][0] = flex3;
    typeTable[0][1][0][1][1][0] = flex3;
    typeTable[0][1][1][0][1][0] = flex3;

    typeTable[0][2][2][0][0][0] = FLEX2;
    typeTable[0][2][0][2][0][0] = FLEX2;
    typeTable[0][2][0][0][2][0] = FLEX2;
    typeTable[0][0][2][2][0][0] = FLEX2;
    typeTable[0][0][2][0][2][0] = FLEX2;
    typeTable[0][0][0][2][2][0] = FLEX2;

    typeTable[0][1][1][0][0][0] = flex2;
    typeTable[0][1][0][1][0][0] = flex2;
    typeTable[0][1][0][0][1][0] = flex2;
    typeTable[0][0][1][1][0][0] = flex2;
    typeTable[0][0][1][0][1][0] = flex2;
    typeTable[0][0][0][1][1][0] = flex2;

    typeTable[0][2][0][0][0][0] = FLEX1;
    typeTable[0][0][2][0][0][0] = FLEX1;
    typeTable[0][0][0][2][0][0] = FLEX1;
    typeTable[0][0][0][0][2][0] = FLEX1;

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
    startTime = QTime::currentTime().msecsSinceStartOfDay();

	if (round == 0) {
        PlayRound0();
    } else  {
        if (!KillSearch(aiPlayer, 0))
            MinMaxSearch(aiPlayer, 0, -INF, INF);
	}

	round++;
	//qDebug() << "AI drop: " << nextDrop.x() << " " << nextDrop.y();
    emit AiDropPiece(nextDrop.x(), nextDrop.y());
}

void GobangAi::PlayRound0() {
	// 若ai先手，则下在正中心
	if (board[7][7] == NO_CHESS) {
		SetNextDrop(7, 7);
	} else {
		const int dir[2] = { -1, 1 };
		SetNextDrop(7 + dir[rand() % 2], 7 + dir[rand() % 2]);
	}
}

int GobangAi::MinMaxSearch(const Player player, int depth, int alpha, int beta) {
    //qDebug() << "Searching...";
    int res, record[17];
    int score = Evaluate(res, record);

    costTime = QTime::currentTime().msecsSinceStartOfDay() - startTime;
    if (costTime > 15 * 1000) return score;

    if (depth == BASE_DEPTH || res != R_DRAW) {
        if (depth == BASE_DEPTH) {
            QPoint points[POINTS_BUF_SIZE];
            QPoint* p_now = points, * p_end = points + SeekPoints(points, AI_CHESS, 1);
            board[p_now->x()][p_now->y()] = AI_CHESS;
            score = Evaluate(res, record);
            board[p_now->x()][p_now->y()] = NO_CHESS;
            return score;
        } else {
            return score;
        }
    }

    QPoint points[POINTS_BUF_SIZE];

    if (player == aiPlayer) { // max层
        QPoint* p_now = points, * p_end = points + SeekPoints(points, AI_CHESS, AVA_POINTS_NUM);
        while (p_now != p_end) {
            board[p_now->x()][p_now->y()] = AI_CHESS;
            score = MinMaxSearch(GetOppositePlayer(player), depth + 1, alpha, beta);
            board[p_now->x()][p_now->y()] = NO_CHESS;
            if (score > alpha) {
                alpha = score;
                if (!depth) {
                    SetNextDrop(p_now->x(), p_now->y());
                }
            }
            if (beta <= alpha)
                break; // 剪枝
            p_now++;
        }
        return alpha;
    } else { // min层
        QPoint* p_now = points, * p_end = points + SeekPoints(points, HUM_CHESS, AVA_POINTS_NUM);
        while (p_now != p_end) {
            board[p_now->x()][p_now->y()] = HUM_CHESS;
            score = MinMaxSearch(GetOppositePlayer(player), depth + 1, alpha, beta);
            board[p_now->x()][p_now->y()] = NO_CHESS;
            if (score < beta)
                beta = score;
            if (beta <= alpha)
                break; // 剪枝
            p_now++;
        }
        return beta;
    }
}

bool GobangAi::CheckBound(int x, int y) {
    if (x >= 0 && x < 15 && y >= 0 && y < 15) return true;
    else return false;
}

QPoint GobangAi::getXY(int row, int col, int dir, int rel) {
    QPoint p;
    if (dir == RIGHT) {
        p.setX(row);
        p.setY(col + rel);
    } else if (dir == UP) {
        p.setX(row - rel);
        p.setY(col);
    } else if (dir == UPRIGHT) {
        p.setX(row - rel);
        p.setY(col + rel);
    } else if (dir == UPLEFT) {
        p.setX(row - rel);
        p.setY(col - rel);
    }
    return p;
}

int GobangAi::EvaluatePosWorth(int x, int y, int chessid) {
    int sum = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            QPoint start = getXY(x, y, RIGHT + i, j - 4);
            QPoint end = getXY(start.x(), start.y(), RIGHT + i, 4);
            if (CheckBound(start.x(), start.y()) && CheckBound(end.x(), end.y())) {
                int humCount = 0;
                int aiCount = 0;
                for (int k = 0; k < 5; ++k) {
                    QPoint tmp = getXY(start.x(), start.y(), RIGHT + i, k);
                    if (board[tmp.x()][tmp.y()] == HUM_CHESS)
                        humCount++;
                    if (board[tmp.x()][tmp.y()] == AI_CHESS)
                        aiCount++;
                }
                sum += CalculatePosScore(humCount, aiCount, chessid);
            }
        }
    }
    return sum;
}

int GobangAi::CalculatePosScore(int humCount, int aiCount, int chessid) {
    if (chessid == HUM_CHESS && humCount == 5)
        return 9999999;
    if (chessid == AI_CHESS && aiCount == 5)
        return 9999999;
    if (humCount == 0 && aiCount == 0)
        return 7;
    else if (humCount >= 1 && aiCount >= 1)
        return 0;
    else if (chessid == HUM_CHESS) {
        if (humCount == 1 && aiCount == 0)
            return 35;
        else if (humCount == 2 && aiCount == 0)
            return 800;
        else if (humCount == 3 && aiCount == 0)
            return 15000;
        else if (humCount == 4 && aiCount == 0)
            return 800000;
        else if (humCount == 0 && aiCount == 1)
            return 15;
        else if (humCount == 0 && aiCount == 2)
            return 400;
        else if (humCount == 0 && aiCount == 3)
            return 1800;
        else
            return 100000;
    } else {
        if (humCount == 1 && aiCount == 0)
            return 15;
        else if (humCount == 2 && aiCount == 0)
            return 400;
        else if (humCount == 3 && aiCount == 0)
            return 1800;
        else if (humCount == 4 && aiCount == 0)
            return 100000;
        else if (humCount == 0 && aiCount == 1)
            return 35;
        else if (humCount == 0 && aiCount == 2)
            return 800;
        else if (humCount == 0 && aiCount == 3)
            return 15000;
        else
            return 800000;
    }
}

int GobangAi::SeekPoints(QPoint* points, int chessid, int limit) {
    QList<PointScore> avaPoints;
    for (int r = 0; r < 15; r++) {
        for (int c = 0; c < 15; c++) {
            if (board[r][c] == NO_CHESS) {
                bool notFound = true;
                int nearCnt = 0;
                for (int i = r - 2; i <= r + 2 && notFound; i++) {
                    for (int j = c - 2; j <= c + 2; j++) {
                        if (i >= 0 && i < 15 && j >= 0 && j < 15 && board[i][j] != NO_CHESS)
                            ++nearCnt;
                        if (nearCnt == NEAR_CNT) {
                            avaPoints.append(PointScore(r, c));
                            notFound = false;
                            break;
                        }
                    }
                }
            }
        }
    }

    for (auto& point : avaPoints) {
        int x = point.pos.x();
        int y = point.pos.y();
        point.score = EvaluatePosWorth(x, y, chessid);
    }

    std::sort(avaPoints.begin(), avaPoints.end(), [](PointScore p, PointScore q) {
        return p.score > q.score;
    });

    int cnt = 0;
    for (const auto& point : avaPoints) {
        points[cnt] = point.pos;
        cnt++;
        if (cnt >= AVA_POINTS_NUM) break;
    }
    //qDebug() << "seek points: " << cnt;
    return cnt;
}

bool GobangAi::KillSearch(const Player player, int depth) {
    int res, record[17];
    int score = Evaluate(res, record);
    if (depth == KILL_DEPTH || res != R_DRAW) {
        if (depth == KILL_DEPTH) {
            QPoint points[POINTS_BUF_SIZE];
            QPoint* p_now = points, * p_end = points + SeekPoints(points, AI_CHESS, 1);
            board[p_now->x()][p_now->y()] = AI_CHESS;
            Evaluate(res, record);
            board[p_now->x()][p_now->y()] = NO_CHESS;
            if (res == R_AI) return true;
            else return false;
        } else if (res == R_AI) return true; // 找到ai杀棋
        else return false;
    }
    
    if (player == aiPlayer) {
        if (depth < 4) { // 最开始4层选所有能走的10个点
            QPoint points[POINTS_BUF_SIZE];
            QPoint* p_now = points, * p_end = points + SeekPoints(points, AI_CHESS, KILL_POINTS_NUM);
            while (p_now != p_end) {
                board[p_now->x()][p_now->y()] = AI_CHESS;
                bool res = KillSearch(GetOppositePlayer(player), depth + 1);
                board[p_now->x()][p_now->y()] = NO_CHESS;
                if (res) {
                    if (depth == 0) SetNextDrop(p_now->x(), p_now->y());
                    return true;
                }
                p_now++;
            }
            return false;
        } else { // 只选杀棋点
            QPoint killPoints[POINTS_BUF_SIZE];
            QPoint* p_now = killPoints, * p_end = killPoints + SeekKillPoints(killPoints);

            while (p_now != p_end) {
                board[p_now->x()][p_now->y()] = AI_CHESS;
                bool res = KillSearch(GetOppositePlayer(player), depth + 1);
                board[p_now->x()][p_now->y()] = NO_CHESS;
                if (res) return true;
                p_now++;
            }
            return false;
        }
    } else {
        QPoint points[POINTS_BUF_SIZE];
        QPoint* p_now = points, * p_end = points + SeekPoints(points, HUM_CHESS, 1);

        board[p_now->x()][p_now->y()] = HUM_CHESS;
        bool res = KillSearch(GetOppositePlayer(player), depth + 1);
        board[p_now->x()][p_now->y()] = NO_CHESS;
        return res;
    }
}

int GobangAi::SeekKillPoints(QPoint* killPoints) {
    int cnt, res, record[17];
    QPoint points[POINTS_BUF_SIZE];
    QPoint* p_now = points, * p_end = points + SeekPoints(points, AI_CHESS, AVA_POINTS_NUM);

    cnt = 0;
    while (p_now != p_end) {
        board[p_now->x()][p_now->y()] = AI_CHESS;
        Evaluate(res, record);
        if (record[WIN] + record[FLEX4] + record[BLOCK4] + record[FLEX3] > 0) {
            killPoints[cnt] = QPoint(p_now->x(), p_now->y());
            cnt++;
        }
        board[p_now->x()][p_now->y()] = NO_CHESS;
        p_now++;
    }
    return cnt;
}

int GobangAi::Evaluate(int &res, int record[17]) {
    // 各棋型权重
    int weight[17] = { 0, 1000000, -10000000, 50000, -100000, 400, -100000, 400, -8000, 20, -50, 20, -50, 1, -3, 1, -3 };

    int i, j, type;
    for (int i = 0; i < 17; ++i) record[i] = 0;

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

    if (record[WIN] > 0) res = R_AI;
    else if (record[LOSE] > 0) res = R_HUM;

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
    board[x][y] = PieceToPlayer(piece) == aiPlayer ? AI_CHESS : HUM_CHESS;
}

void GobangAi::TakePiece(int x, int y) {
    board[x][y] = NO_CHESS;
}

void GobangAi::DecreaseRound() {
    round--;
}