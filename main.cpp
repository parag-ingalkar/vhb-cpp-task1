#include "university.hpp"

/**
 * Main function - entry point of the program
 * Creates university object and starts the management system
 */
int main()
{
    // Initialize university with name "FAU"
    University university = University("FAU");

    // Display main menu and start program
    university.displayMenu();

    return 0;
}