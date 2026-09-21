#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <sys/param.h>
#include <locale.h>

#define X 50
#define Y 25
#define DX 2
#define DY 2
#define CAPACITY 256

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "You must provide file name\n");
        return 1;
    }
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        fprintf(stderr, "You must provide correct file name\n");
        return 1;
    }

    char **lines = NULL;
    char *buffer = NULL;
    size_t n = 0;
    size_t count = 0, capacity = 0;
    ssize_t line_length = 0;
    ssize_t *line_lengths = NULL;
    while ((line_length = getline(&buffer, &n, input_file)) >= 0) {
        if (count == capacity) {
            capacity = (count ? 2 * capacity : CAPACITY);
            lines = realloc(lines, capacity * sizeof(buffer));
            line_lengths = realloc(line_lengths, capacity * sizeof(line_length));
        }
        if (line_length > 0 && buffer[line_length - 1] == '\n') {
            buffer[line_length - 1] = '\0';
            line_length--;
        }
        lines[count] = buffer;
        line_lengths[count] = line_length;
        count++;
        buffer = NULL;
        n = 0;
    }
    fclose(input_file);

    WINDOW *frame, *win;
    int c = 0;

    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    refresh();

    frame = newwin(Y, X, DY, DX);
    box(frame, 0, 0);
    wrefresh(frame);
    mvwaddstr(frame, 0, 1, argv[1]);

    win = newwin(Y - 2, X - 2, DY + 1, DX + 1);
    keypad(win, TRUE);
    scrollok(win, FALSE);
    wmove(win, 0, 0);
    keypad(frame, TRUE);
    int offset_y = 0, offset_x = 0;
    while (1) {
        scrollok(win, TRUE);
        size_t max_len = 0;
        for (int i = offset_y; i < offset_y + Y - 2; i++) {
            wmove(win, i - offset_y, 0);
            wclrtoeol(win);
            if (i < count && offset_x < line_lengths[i]) {
                wprintw(win, "%.*s", X - 2, lines[i] + offset_x);
                max_len = MAX(max_len, line_lengths[i] - offset_x);
            }
        }
        scrollok(win, FALSE);
        wrefresh(win);
        wmove(frame, MIN(count - offset_y, Y - 1), 0);
        wrefresh(frame);
        c = wgetch(frame);
        if (c == 27) {
            break;
        } else if (c == ' ' || c == KEY_NPAGE || c == KEY_DOWN) {
            if (offset_y < count - 1) {
                offset_y++;
            }
        } else if (c == KEY_PPAGE || c == KEY_UP) {
            if (offset_y > 0) {
                offset_y--;
            }
        } else if (c == KEY_RIGHT) {
            if (max_len > 1) {
                offset_x++;
            }
        } else if (c == KEY_LEFT) {
            if (offset_x > 0) {
                offset_x--;
            }
        }
    }
    delwin(win);
    delwin(frame);
    endwin();
    for (size_t i = 0; i < count; i++) {
        free(lines[i]);
    }
    free(lines);
    free(line_lengths);
    return 0;
}
