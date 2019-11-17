#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "interaction.h"

#define OPTION_SEPARATOR "="

/**
 * comportement par défaut, afficher les process de l'user et tty courant (format général)
 * 
 * user = nom utilisateur
 * status = *
 * 
 * format = *
 */

static const char *keys[] = {"user", "status", "topic"};
static const char *statusValues[] = {"running", "sleeping", "waiting", "zombie"};
static const char *topicValues[] = {"paging", "general", "runtime"};

static int array_contains(const char **array, unsigned count, char *value)
{
    for (unsigned i = 0; i < count; i++)
    {
        if (strcmp(array[i], value) == 0)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * Tells if the given key has already been set in the specified array of
 * options.
 */
static int isSet(const awesomeps_option *options, unsigned count,
                 awesomeps_option *option)
{
    for (unsigned i = 0; i < count; i++)
    {
        awesomeps_option currentOption = options[i];
        if (strcmp(currentOption.key, option->key) == 0)
        {
            return 1;
        }
    }
    return 0;
}

/* Tells if the given key is valid. A key is value when it is an available one
 * and is not null.
 */
static int isValidKey(char *key)
{
    return key != NULL && array_contains(keys, 3, key);
}

// Tells if the given value is valuee for the given key.
static int isValidValueForKey(char *key, char *value)
{
    if (isValidKey(key))
    {
        if (strcmp("status", key) == 0)
        {
            return value != NULL && array_contains(statusValues, 4, value);
        }
        else if (strcmp("topic", key) == 0)
        {
            return value != NULL && array_contains(topicValues, 3, value);
        }
    }
    return 0;
}

// Converts the given string to a valid option.
void setOptionFromString(char *str, awesomeps_option *option)
{
    char *key = strtok(str, OPTION_SEPARATOR);
    char *value = strtok(NULL, OPTION_SEPARATOR);
    if (isValidKey(key))
    {
        if (isValidValueForKey(key, value))
        {
            option->key = key;
            option->value = value;
        }
        else
        {
            printf(
                "Option parsing error: %s isn't a valid value for %s.\n",
                value, key);
            exit(-1);
        }
    }
    else
    {
        printf("Option parsing error: %s is not a valid option\n", str);
        exit(-1);
    }
}

void parseCommandlineArguments(int argc, char **argv, awesomeps_option *options)
{
    if (options != NULL)
    {
        for (unsigned count = 0, i = 1; i < argc; i++)
        {
            awesomeps_option option;
            setOptionFromString(argv[i], &option);
            if (!isSet(options, count, &option))
            {
                options[count] = option;
                count++;
            } else {
                printf("Option parsing error: %s has been set twice\n", option.key);
                exit(-1);
            }
        }
    }
}

void readOptions(awesomeps_option *options, unsigned count)
{
    for (unsigned i = 0; i < count; i++)
    {
        printf("<key: %s, value: %s>\n", options[i].key, options[i].value);
    }
}