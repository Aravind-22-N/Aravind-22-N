#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>

int main() {
    struct dirent *entry;
    DIR *proc_dir = opendir("/proc");
    if (!proc_dir) {
        perror("opendir");
        return 1;
    }
    
    while ((entry = readdir(proc_dir)) != NULL) {
        if (isdigit(entry->d_name[0])) {
            char path[256];
            snprintf(path, sizeof(path), "/proc/%s/comm", entry->d_name);
            FILE *file = fopen(path, "r");
            if (file) {
                char comm[256];
                if (fgets(comm, sizeof(comm), file)) {
                    comm[strcspn(comm, "\n")] = 0;  // Remove newline character
                    printf("PID: %s, Name: %s\n", entry->d_name, comm);
                }
                fclose(file);
            }
        }
    }
    closedir(proc_dir);
    return 0;
}
