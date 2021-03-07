/*
** EPITECH PROJECT, 2021
** NANOTEKSPICE
** File description:
** NanoTekSpice header
*/

#ifndef NANOTEKSPICE_H_
#define NANOTEKSPICE_H_

#ifdef BONUS
#define HELP_MSG_HEADER "Usage: ./nanotekspice [-g] FILE.nts [INPUT_NAME=INPUT_VALUE]...\n"              \
                        "\n"                                                                             \
                        "OPTION:\n"                                                                      \
                        "\t-g\trun graphic shell, else run interactive shell in terminal\n\n"            \
                        "GRAPHIC_SHELL:\n"                                                               \
                        "\tLEFT_CLICK\tenable an input and switch it from FALSE to TRUE and vice versa.\n" \
                        "\tRIGHT CLICK\tdisable an input (set it value as UNDEFINED).\n"                    \
                        "\tKEY_ESCAPE\tclose window.\n"
#else
#define HELP_MSG_HEADER "Usage: ./nanotekspice FILE.nts [INPUT_NAME=INPUT_VALUE]...\n"
#endif

#define HELP_MSG_CONTENT                                                                                                                                        \
    "\n"                                                                                                                                                        \
    "SHELL:\n"                                                                                                                                                  \
    "\texit:\t\tcloses the program.\n"                                                                                                                          \
    "\tdisplay/d:\tprints the current tick and the value of all inputs and outputs in the standard output.\n"                                                   \
    "\tinput=value:\tchanges the value of an input. Possible value are 0, 1 and U. This also apply to clocks. Use *=value to change all inputs in same time.\n" \
    "\tsimulate/s:\tsimulate a tick of the circuit.\n"                                                                                                          \
    "\tloop/l:\t\tcontinuously runs the simulation (simulate, display, simulate, ...) without displaying a prompt, until SIGINT is received.\n"                 \
    "\tdump:\t\tcalls the dump method of every component.\n"                                                                                                    \
    "\tsd:\t\tsimulate and display."

#define HELP_MSG HELP_MSG_HEADER HELP_MSG_CONTENT

#endif /* !NANOTEKSPICE_H_ */