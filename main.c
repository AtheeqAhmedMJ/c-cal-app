#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EVENTS 10
#define MAX_EVENT_DESC 50

typedef struct {
    int day;
    char description[MAX_EVENT_DESC];
} Event;

Event events[MAX_EVENTS];
int event_count = 0;

int isLeapYear(int year) {
    return (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
}

int getDaysInMonth(int month, int year) {
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) return 29;
    return daysInMonth[month - 1];
}

int getFirstDayOfMonth(int month, int year) {
    int d = 1, m = month, y = year;
    int dayOfWeek = (d += m < 3 ? y-- : y - 2, 23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400) % 7;
    return dayOfWeek;
}

void displayCalendar(int month, int year) {
    printf("\nCalendar for %d/%d\n", month, year);
    printf("Sun Mon Tue Wed Thu Fri Sat\n");

    int daysInMonth = getDaysInMonth(month, year);
    int startDay = getFirstDayOfMonth(month, year);

    for (int i = 0; i < startDay; i++) printf("    ");

    for (int day = 1; day <= daysInMonth; day++) {
        printf("%3d ", day);
        if ((day + startDay) % 7 == 0) printf("\n");
    }
    printf("\n");
}

void addEvent(int day, const char* description) {
    if (event_count < MAX_EVENTS) {
        events[event_count].day = day;
        strncpy(events[event_count].description, description, MAX_EVENT_DESC);
        event_count++;
        printf("Event added on day %d\n", day);
    } else {
        printf("Event limit reached.\n");
    }
}

void viewEvents(int day) {
    printf("Events on day %d:\n", day);
    for (int i = 0; i < event_count; i++) {
        if (events[i].day == day) {
            printf("- %s\n", events[i].description);
        }
    }
}

int main() {
    int month, year, choice, day;
    char desc[MAX_EVENT_DESC];

    printf("Enter month (1-12): ");
    scanf("%d", &month);
    printf("Enter year: ");
    scanf("%d", &year);

    displayCalendar(month, year);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Event\n");
        printf("2. View Events\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter day for event: ");
                scanf("%d", &day);
                printf("Enter event description: ");
                getchar();
                fgets(desc, MAX_EVENT_DESC, stdin);
                desc[strcspn(desc, "\n")] = 0;
                addEvent(day, desc);
                break;
            case 2:
                printf("Enter day to view events: ");
                scanf("%d", &day);
                viewEvents(day);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
    return 0;
}
