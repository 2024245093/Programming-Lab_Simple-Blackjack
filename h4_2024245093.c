#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
int picked_cards[10]; //이미 뽑힌 카드들 저장 (중복되는 카드들 피하기 위함)
int picked_cards_count = 0;
int player_sum = 0, dealer_sum = 0; //둘 다 전역변수로 저장
void print_cards_sum(int player, int dealer) { //사용자/딜러에 값 추가하고, 각각의 합계 출력 (합계 출력은 중복되는 코드가 많아서 함수에 넣었습니다)
    player_sum += player;
    dealer_sum += dealer;
    printf("당신의 카드 합계: %d\n", player_sum);
    printf("딜러의 카드 합계: %d\n\n", dealer_sum);
}
int pick_random_card() { //중복되지 않는 랜덤한 값 뽑고 picked_cards(이미 뽑힌 카드들 저장하는 배열)에 추가
    int pick_new_number = 1;
    int random_card;
    while (pick_new_number) {
        pick_new_number = 0;
        random_card = rand() % 10 + 2;
        for (int i = 0; i < picked_cards_count; i++) {
            if (picked_cards[i] == random_card) {
                pick_new_number = 1;
                break;
            }
        }
    }
    picked_cards[picked_cards_count++] = random_card;
    return random_card;
}
void run_program() {
    int i;
    for (i = 0; i < 2; i++) {
        player_sum += pick_random_card();
    }
    for (i = 0; i < 2; i++) {
        dealer_sum += pick_random_card();
    }
    if (player_sum == 21) { //사용자가 딜러보다 먼저 뽑으므로 혹시라도 사용자가 11과 10을 둘다 뽑는 경우
        printf("당신이 21점을 얻었습니다. 당신이 승리했습니다 !");
        return;
    }
    printf("게임 시작! 당신은 두 장의 카드를 받았습니다.\n");
    print_cards_sum(0, 0);
    char get_more_cards;
    printf("카드를 더 받으시겠습니까? (y/n):");
    scanf("%c", &get_more_cards);
    while (get_more_cards == 'y') {
        int random_card = pick_random_card();
        printf("당신은 %d을(를) 받았습니다.\n", random_card);
        print_cards_sum(random_card, 0);
        if (player_sum == 21) {
            printf("당신이 21점을 얻었습니다. 당신이 승리했습니다 !");
            return;
        }
        else if (player_sum > 21) {
            printf("당신이 21점을 초과했습니다. 딜러가 이겼습니다 !");
            return;
        }
        printf("카드를 더 받으시겠습니까? (y/n):");
        scanf(" %c", &get_more_cards);
    }
    while (dealer_sum < player_sum) { //여기서부터 딜러가 사용자보다 작으면 계속 뽑음
        int random_card = pick_random_card();
        printf("딜러는 %d을(를) 받았습니다.\n", random_card);
        print_cards_sum(0, random_card);
        if (dealer_sum > 21) {
            printf("딜러가 21점을 초과했습니다. 당신이 이겼습니다 !");
            return;
        }
    }
    if (dealer_sum == player_sum) {
        printf("카드 총합이 같습니다 ! 비겼습니다 !");
        return;
    }
    else {
        printf("딜러가 당신보다 점수가 많습니다 ! 딜러가 승리했습니다 !");
    }
}
int main() {
    srand(time(NULL));
    run_program();
    return 0;
}