#ifndef CONSTANTS_H
#define CONSTANTS_H

class Constant
{
public:
    Constant() {}

    static const int OLED_WIDTH = 64;
    static const int OLED_HEIGHT = 110;
    static const int ARD_P1_WIDTH = 16;
    static const int ARD_P1_HEIGHT = 1;
    static const int ARD_P2_WIDTH = 16;
    static const int ARD_P2_HEIGHT = 1;
    static const int ARD_BALL_RAD = 1;
    static const int ARD_P1_POS_X = OLED_WIDTH/2 - ARD_P1_WIDTH/2;
    static const int ARD_P1_POS_Y = 0;
    static const int ARD_P2_POS_X = OLED_WIDTH/2 - ARD_P2_WIDTH/2;
    static const int ARD_P2_POS_Y = OLED_HEIGHT-1;
    static const int ARD_PENALTY = 1;
    static const int ARD_BLOCK_WIDTH = 50 / 5;
    static const int ARD_BLOCK_HEIGHT = 2;

    //Change This
    static const int SCALE_RATIO_TO_SIM = 4;

    static const int GAME_AREA_WIDTH = OLED_WIDTH * SCALE_RATIO_TO_SIM;
    static const int GAME_AREA_HEIGHT = OLED_HEIGHT * SCALE_RATIO_TO_SIM;

    static const int PLAYER1_WIDTH = ARD_P1_WIDTH * SCALE_RATIO_TO_SIM;
    static const int PLAYER1_HEIGHT = ARD_P1_HEIGHT * SCALE_RATIO_TO_SIM;
    static const int PLAYER2_WIDTH = ARD_P2_WIDTH * SCALE_RATIO_TO_SIM;
    static const int PLAYER2_HEIGHT = ARD_P2_HEIGHT * SCALE_RATIO_TO_SIM;

    static const int BALL_RAD = ARD_BALL_RAD * SCALE_RATIO_TO_SIM;

    static const int PLAYER1_POS_X = ARD_P1_POS_X * SCALE_RATIO_TO_SIM;
    static const int PLAYER1_POS_Y = ARD_P1_POS_Y * SCALE_RATIO_TO_SIM;
    static const int PLAYER2_POS_X = ARD_P2_POS_X * SCALE_RATIO_TO_SIM;
    static const int PLAYER2_POS_Y = ARD_P2_POS_Y * SCALE_RATIO_TO_SIM;
    static const int PENALTY = ARD_PENALTY * SCALE_RATIO_TO_SIM;

    static const int BLOCK_WIDTH = ARD_BLOCK_WIDTH * SCALE_RATIO_TO_SIM;
    static const int BLOCK_HEIGHT= ARD_BLOCK_HEIGHT * SCALE_RATIO_TO_SIM;

};

#endif // CONSTANTS_H
