#include "sounds.h"
#include <windows.h>

void CrunchV() {
    PlaySound(TEXT("audio\\NewCrunch.wav"), NULL, SND_FILENAME|SND_ASYNC);
}
void GameOverV() {
    PlaySound(TEXT("audio\\GameOver.wav"), NULL, SND_FILENAME|SND_ASYNC);
}
void BreakV() {
    PlaySound(TEXT("audio\\Break.wav"), NULL, SND_FILENAME|SND_ASYNC);
}
