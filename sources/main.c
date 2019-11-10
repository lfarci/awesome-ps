#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

#include "status_information_scanner.h"
#include "process_selector.h"
#include "awesomepsio.h"
#include "user_information.h"

/**
 * Parses a string representing a pid and convert it to a long integer. The
 * value of the parsed pid is returned.
 * 
 * The given string should exclusively contain numerical characters. If it not
 * the case, this functions exits the program and prints a appropriate message
 * 
 * If the represented pid is evaluated to be out of range then this
 * function exits the program and prints a appropriate message.
 */
long parsePID(char *str)
{
    char *endptr;
    long pid = strtol(str, &endptr, 10);
    if (errno == ERANGE)
    {
        printf("PID parsing error: the resulting value was out of range.\n");
        exit(-1);
    }
    if (endptr == str || *endptr != '\0')
    {
        printf("PID parsing error: '%s' could not be parsed.\n", str);
        exit(-1);
    }
    return pid;
}

void showProcessStatusInformationFor(const int pid)
{
    status_information information;
    if (scanStatusInformation(pid, &information) == -1)
    {
        printf("PID not found: no /proc/%d/stat virtual file was found.\n", pid);
        exit(-2);
    }
    else
    {
        printStatusInformation(&information);
    }
}

void showAllProcesses(char searchOption) {
    int pids[1000];
    
    switch(searchOption)
    {
        case 's':
            //Implement code to search specific status
            break;
            
        case 'u':
            //Implement code to search specific user
            break;
        
        default:
            searchProcesses(pids, 0, 0);
    }
    
    
    int current = 0;
    printTableHeader();
    while (pids[current] >= 0)
    {
        showProcessStatusInformationFor(pids[current]);
        current++;
    }
    printRowSeparator();
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        showAllProcesses(0);
        return 1;
    }
    else if (argc == 2)
    {
        long pid = parsePID(argv[1]);
        printTableHeader();
        showProcessStatusInformationFor(pid);
        printRowSeparator();
        
        int userId;
        userId = findProcessUserId(pid);
        printf("Voici l'id de l'user qui a lancé le process : %d \n", userId);
        
        char * name;
        name = findUserName(userId);
        printf("Voici le nom de l'user qui a lancé le process : %s \n", name);
    }
    else
    {
        printf("usage: %s [pid]", argv[0]);
    }
    return 0;

}
