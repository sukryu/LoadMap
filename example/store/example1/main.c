#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LENGTH 100
#define MAX_LECTURE_NUM 5

typedef struct course 
{
    int* student_ids;
    char* code;
    char* lecture_name;
    int max_student;
    int count;
} Course;

typedef struct student {
    float gpa;
    int id;
    char* name;
    char* specialty;
    int current_course;
} Student;

Student* g_student_arr;
int g_student_len;

Student* allocate_student(int n) {
    Student* student = (Student *)malloc(sizeof(Student) * n);
    if (student == NULL) {
        perror("Failed to allocate memory for students");
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        student[i].name = (char *)malloc(sizeof(char) * MAX_STR_LENGTH);
        if (student[i].name == NULL) {
            free_student(student, i);
            perror("Failed to allocate memory for student name");
            return NULL;
        }

        student[i].specialty = (char *)malloc(sizeof(char) * MAX_STR_LENGTH);
        if (student[i].specialty == NULL) {
            free_student(student, i);
            perror("Failed to allocate memory for student specialty");
            return NULL;
        }
        student[i].current_course = 0;
    }
    return student;
}

void input_student(Student* student_arr, int n) {
    char buffer[MAX_STR_LENGTH];
    for (int i = 0; i < n; i++) {
        scanf("%d", &student_arr[i].id);
        getchar(); // 버퍼에 남아있는 개행문자 제거
        
        fgets(buffer, MAX_STR_LENGTH, stdin);
        buffer[strcspn(buffer, "\n")] = 0; // 개행문자 제거
        strncpy(student_arr[i].name, buffer, MAX_STR_LENGTH - 1);
        
        fgets(buffer, MAX_STR_LENGTH, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(student_arr[i].specialty, buffer, MAX_STR_LENGTH - 1);
        
        scanf("%f", &student_arr[i].gpa);
        getchar();
    }
}

void free_student(Student* student, int n) {
    if (student == NULL) return;

    for (int i = 0; i < n; i++) {
        if (student[i].name != NULL) {
            free(student[i].name);
        }
        if (student[i].specialty != NULL) {
            free(student[i].specialty);
        }
    }
    free(student);
}

Course* allocate_course(int m) {
    Course* course = (Course *)malloc(sizeof(Course) * m);
    if (course == NULL) {
        perror("Failed to allocate memory for courses");
        return NULL;
    }

    for (int i = 0; i < m; i++) {
        course[i].code = (char *)malloc(sizeof(char) * MAX_STR_LENGTH);
        if (course[i].code == NULL) {
            free_course(course, i);
            perror("Failed to allocate memory for course code");
            return NULL;
        }

        course[i].lecture_name = (char *)malloc(sizeof(char) * MAX_STR_LENGTH);
        if (course[i].lecture_name == NULL) {
            free_course(course, i);
            perror("Failed to allocate memory for lecture name");
            return NULL;
        }

        course[i].count = 0;
        
        // student_ids는 초기에 NULL로 설정
        course[i].student_ids = NULL;
    }
    return course;
}

void input_course(Course* course_arr, int m) {
    char buffer[MAX_STR_LENGTH];
    for (int i = 0; i < m; i++) {
        fgets(buffer, MAX_STR_LENGTH, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(course_arr[i].code, buffer, MAX_STR_LENGTH - 1);

        fgets(buffer, MAX_STR_LENGTH, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(course_arr[i].lecture_name, buffer, MAX_STR_LENGTH - 1);

        scanf("%d", &course_arr[i].max_student);
        getchar();
    }
}

// 처음에는 max_student 수 만큼 할당한 뒤 모든 입력이 끝났을 때 realloc 하면 될 것 같음.
void allocate_course_students_ids(Course* course) {
    if (course->max_student <= 0) {
        return;
    }
    
    course->student_ids = (int *)malloc(sizeof(int) * course->max_student);
    if (course->student_ids == NULL) {
        perror("Failed to allocate memory for students ids");
        return;
    }
}

void free_course(Course* course, int n) {
    if (course == NULL) return;

    for (int i = 0; i < n; i++) {
        if (course[i].code != NULL) {
            free(course[i].code);
        }
        if (course[i].lecture_name != NULL) {
            free(course[i].lecture_name);
        }
        if (course[i].student_ids != NULL) {
            free(course[i].student_ids);
        }
    }
    free(course);
}

void add_student_to_course(Student* student_arr, int student_len, Course* course_arr, int course_len, int r) {
    char buffer[MAX_STR_LENGTH];
    for (int i = 0; i < r; i++) {
        int id = 0;
        scanf("%d", &id);
        getchar();
        
        fgets(buffer, MAX_STR_LENGTH, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        // 1. 강의 코드에 해당하는 구조체 배열의 인덱스 가져오기
        int index = 0;
        for (int j = 0; j < course_len; j++) {
            if (strncmp(buffer, course_arr[j].code, MAX_STR_LENGTH) == 0) {
                index = j;
                break;
            } else { continue; }
        }

        // 2. Course 구조체의 count를 활용해서 max_student에 근접했는지 확인
        if (course_arr[index].count >= course_arr[index].max_student) continue;

        // 3. 학생이 수강 가능한 최대 과목수를 넘겼는지 확인
        int student_index = -1;
        for (int j = 0; j < student_len; j++) {
            if (student_arr[j].id == id) {
                student_index = j;
                break;
            }
        }

        if (student_index != -1 && student_arr[student_index].current_course < MAX_LECTURE_NUM) {
            student_arr[student_index].current_course++;
            course_arr[index].student_ids[course_arr[index].count] = student_arr[student_index].id;
            course_arr[index].count++;
        }
    }

    // 모든 입력이 끝났기 때문에 realloc 실행
    for (int i = 0; i < course_len; i++) {
        if (course_arr[i].count == 0) {
            free(course_arr[i].student_ids);
            course_arr[i].student_ids = NULL;  // free 후 NULL 처리 추가
            continue;
        }

        int* temp = (int *)realloc(course_arr[i].student_ids, course_arr[i].count * sizeof(int));
        if (temp == NULL) {
            // realloc 실패 시 기존 메모리는 그대로 유지
            perror("Failed to reallocate memory");
            continue;
        }
        course_arr[i].student_ids = temp;
    }
}

void print_all(Student* student_arr, int student_len, Course* course_arr, int course_len) {
    for (int i = 0; i < course_len; i++) {
        sort_course_by_gpa(&course_arr[i], student_arr, student_len);
        printf("강의: %s %s\n", course_arr[i].code, course_arr[i].lecture_name);
        printf("등록된 학생:\n");

        if (course_arr[i].count == 0) {
            printf("STUDENT NOT FOUND");
            continue;
        }

        for (int j = 0; j < course_arr[i].count; j++) {
            int student_id = course_arr[i].student_ids[j];
            int student_index = -1;
            for (int k = 0; k < student_len; k++) {
                if (student_arr[k].id == student_id) {
                    student_index = k;
                    break;
                } 
            }

            if (student_index != -1) {
                printf("%d %s %s %.2f\n",
                    student_arr[student_index].id,
                    student_arr[student_index].name,
                    student_arr[student_index].specialty,
                    student_arr[student_index].gpa
                    );
            } else {
                continue;
            }
        }
        float avg_gpa = calculate_avg_gpa(student_arr, course_arr, student_len, i);
        printf("평균 GPA: %.2f\n\n", avg_gpa);
    }
}

float calculate_avg_gpa(Student* student_arr, Course* course_arr, int student_len, int index) {
    if (course_arr[index].count == 0) return 0.0f;
    float result = 0;

    for (int i = 0; i < course_arr[index].count; i++) {
        int student_id = course_arr[index].student_ids[i];
        int student_index = -1;
        for (int j = 0; j < student_len; j++) {
            if (student_arr[j].id == student_id) {
                student_index = j;
                break;
            }
        }
        if (student_index != -1) {
            result += student_arr[student_index].gpa;
        }
    }

    return result / course_arr[index].count;
}

int compare_by_gpa(const void* a, const void* b) {
    int id1 = *(const int*)a;
    int id2 = *(const int*)b;
    
    float gpa1 = 0.0f, gpa2 = 0.0f;
    
    for (int i = 0; i < g_student_len; i++) {
        if (g_student_arr[i].id == id1) {
            gpa1 = g_student_arr[i].gpa;
        }
        if (g_student_arr[i].id == id2) {
            gpa2 = g_student_arr[i].gpa;
        }
    }
    
    if (gpa1 < gpa2) return 1;
    if (gpa1 > gpa2) return -1;
    return 0;
}

void sort_course_by_gpa(Course* course, Student* student_arr, int student_len) {
    if (course->count <= 1) return;
    
    g_student_arr = student_arr;
    g_student_len = student_len;
    
    qsort(course->student_ids, course->count, sizeof(int), compare_by_gpa);
}

int main() {
    int n = 0, m = 0, r = 0;
    scanf("%d", &n);

    Student* student_arr = allocate_student(n);
    input_student(student_arr, n);

    scanf("%d", &m);
    Course* course_arr = allocate_course(m);
    input_course(course_arr, m);
    for (int i = 0; i < m; i++) {
        allocate_course_students_ids(&course_arr[i]);
    }
    scanf("%d", &r);
    add_student_to_course(student_arr, n, course_arr, m, r);

    print_all(student_arr, n, course_arr, m);

    free_student(student_arr, n);
    free_course(course_arr, m);
}