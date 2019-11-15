#ifndef FORMATS_H
#define FORMATS_H

/* Defines the print formats. A format is used to select the data that should
 * be shown to the user.
 */
typedef enum format {

    // Should be used to print general informations about a process.
    GENERAL_FORMAT = 0,

    // Should be used to print informations related to the process runtime.
    RUNTIME_FORMAT = 1,

    // Should be used to print informations related to the process paging.
    PAGING_FORMAT = 2

} awesomeps_format;

#endif /* FORMATS_H */