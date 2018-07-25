struct goals
{
	int awards[3][4];
};

struct hstable
{
    char name[20];
    unsigned long score;
};

int newAwardFile(int levels, struct goals *award);
int loadAwards(int levels, struct goals *award);
int saveAwards(int levels, struct goals *award);
int newHighScoreFile(struct hstable *score);
int loadHighScore(struct hstable *score);
int saveHighScore(struct hstable *score);
int resetAwards(struct goals *award);
int mergeAwards(struct goals *gameAward, struct goals *finalAward, int level, int difficulty);

int levelComplete(struct container *screen, int *pos, int *count, int level, int difficulty, struct goals *complete, int money, int lives, int kills, int startLives, int enemiesTotal, GLuint *textures, int *texW, int *texH, int *texW2, int *texH2, GLuint *fontTexture, int *fontW, int *fontH, int *fontW2, int *fontH2);
