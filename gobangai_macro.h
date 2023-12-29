#ifndef GOBANGAI_MACRO_H
#define GOBANGAI_MACRO_H

#define INF 0x3f3f3f3f
#define BASE_DEPTH 4 // 搜索深度

#define POINTS_BUF_SIZE 256
#define NEAR_CNT 2

// 棋形分数
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

#endif // GOBANGAI_MACRO_H