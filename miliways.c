#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// JSON-style candidate data (Problem 5 style)
char *candidate01_arr = "{\"id\":1,\"name\":\"Jiyeon Park\",\"dob\":20060415,\"gender\":\"F\",\"email\":\"jiyeon@outlook.com\",\"nationality\":\"South Korea\",\"bmi\":18.5,\"primary\":\"Dance\",\"secondary\":\"Composition\",\"topik\":0,\"mbti\":\"ENFJ\",\"passed\":1}";
char *candidate02_arr = "{\"id\":2,\"name\":\"Ethan Smith\",\"dob\":20050822,\"gender\":\"M\",\"email\":\"ethan@outlook.com\",\"nationality\":\"USA\",\"bmi\":21.2,\"primary\":\"Vocal\",\"secondary\":\"Lyric Writing\",\"topik\":2,\"mbti\":\"ISTP\",\"passed\":1}";
char *candidate04_arr = "{\"id\":4,\"name\":\"Helena Silva\",\"dob\":20070310,\"gender\":\"F\",\"email\":\"helena@outlook.com\",\"nationality\":\"Brazil\",\"bmi\":20.8,\"primary\":\"Vocal\",\"secondary\":\"Composition & Lyric Writing\",\"topik\":1,\"mbti\":\"ENFP\",\"passed\":1}";
char *candidate06_arr = "{\"id\":6,\"name\":\"Liam Wilson\",\"dob\":20061108,\"gender\":\"M\",\"email\":\"liam@outlook.com\",\"nationality\":\"Australia\",\"bmi\":20.1,\"primary\":\"Dance\",\"secondary\":\"Composition & Lyric Writing\",\"topik\":3,\"mbti\":\"ENTJ\",\"passed\":1}";

// milliways##_arr: extended member profiles
char *milliways01_arr;
char *milliways02_arr;
char *milliways03_arr;
char *milliways04_arr;

void printBMIMessage(float bmi) {
    int category;
    if (bmi < 18.5)
        category = 0;
    else if (bmi < 23)
        category = 1;
    else if (bmi < 25)
        category = 2;
    else
        category = 3;

    switch (category) {
        case 0: printf("BMI 상태: 저체중\n"); break;
        case 1: printf("BMI 상태: 정상\n"); break;
        case 2: printf("BMI 상태: 과체중\n"); break;
        case 3: printf("BMI 상태: 비만\n"); break;
    }
}

void displayMemberInfo(char *json, char *nickname, char *edu, float height, char *blood, char *allergy, char *hobby, char *sns, float bmi) {
    printf("=========================================\n");
    printf("기초 정보 (JSON): %s\n", json);
    printf("닉네임: %s\n", nickname);
    printf("학력: %s\n", edu);
    printf("키: %.2fm\n", height);
    float weight = bmi * height * height;
    printf("몸무게: %.1fkg\n", weight);
    printf("혈액형: %s\n", blood);
    printf("알러지: %s\n", allergy);
    printf("취미: %s\n", hobby);
    printf("SNS: %s\n", sns);
    printBMIMessage(bmi);
}

int main() {
    printf("#########################################\n");
    printf("#     Milliways Final Member Review     #\n");
    printf("#########################################\n");

    // Member 1 - Jiyeon
    milliways01_arr = candidate01_arr;
    displayMemberInfo(
        milliways01_arr, "Ariel", "고1중퇴", 1.68, "A", "유제품",
        "댄스 연습, 작곡", "Instagram - @Ariel_Jiyeon", 18.5
    );

    // Member 2 - Ethan
    milliways02_arr = candidate02_arr;
    displayMemberInfo(
        milliways02_arr, "Simba", "중3중퇴", 1.78, "O", "땅콩",
        "노래 작곡, 헬스 트레이닝", "Twitter - @Simba_Ethan", 21.2
    );

    // Member 3 - Helena
    milliways03_arr = candidate04_arr;
    displayMemberInfo(
        milliways03_arr, "Belle", "중졸", 1.63, "B", "생선",
        "노래 부르기, 그림 그리기", "Instagram - @Belle_Helena", 20.8
    );

    // Member 4 - Liam
    milliways04_arr = candidate06_arr;
    displayMemberInfo(
        milliways04_arr, "Aladdin", "중2중퇴", 1.75, "AB", "갑각류",
        "춤추기, 음악 프로듀싱", "Instagram - @Aladdin_Liam", 20.1
    );

    return 0;
}
