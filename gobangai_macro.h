#ifndef GOBANGAI_MACRO_H
#define GOBANGAI_MACRO_H

#define INF 0x3f3f3f3f
#define BASE_DEPTH 32 // 搜索深度
#define KILL_DEPTH 16

#define POINTS_BUF_SIZE 256
#define AVA_POINTS_NUM 32
#define KILL_POINTS_NUM 16
#define NEAR_CNT 2

// 方向：右、上、右上、左上
#define RIGHT 0 
#define UP 1
#define UPRIGHT 2
#define UPLEFT 3

#define R_DRAW 0 
#define R_HUM 1
#define R_AI 2

// 棋形下标
#define WIN 1     // 1000000,白赢
#define LOSE 2    //-10000000
#define FLEX4 3   // 50000,白活4
#define flex4 4   //-100000
#define BLOCK4 5  // 400
#define block4 6  //-100000
#define FLEX3 7   // 400
#define flex3 8   //-8000
#define BLOCK3 9  // 20
#define block3 10 //-40
#define FLEX2 11  // 20
#define flex2 12  //-40
#define BLOCK2 13 // 1
#define block2 14 //-2
#define FLEX1 15  // 1
#define flex1 16  //-2

#define NO_CHESS 0
#define HUM_CHESS 1
#define AI_CHESS 2
#define BOUND 3

#endif // GOBANGAI_MACRO_H