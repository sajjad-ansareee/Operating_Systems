/*
    Formula to calculate CGPA
    (Sum of (grade obtained*credit hours of that specific course))/(Sum of total credit hours)
*/ 

#include <stdio.h>
#include <stdlib.h>

float calculate() {
    printf("Number of total courses: ");
    int total_courses; scanf("%d", &total_courses);
    int total_credit_hours=0;
    float total_obtained=0;
    for (int i=0; i<total_courses; ++i) {
        printf("Credit hours of the course_%d: ", i+1);
        int credit_hour; scanf("%d", &credit_hour);
        printf("Grade obtained in course_%d: ", i+1);
        float grade_obtained; scanf("%f", &grade_obtained);
        total_credit_hours+=credit_hour;
        total_obtained+=(credit_hour*grade_obtained);
    }
    return total_obtained/total_credit_hours;
}

int main(int argc, char* argv[]) {
    printf("CGPA: %f\n", calculate());
    return 0;
}