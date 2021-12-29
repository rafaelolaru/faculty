/*
Create a simple linked list implementing a list of forests, each containing a list of tree species.
 - implement the list of forests as a simple linked list;
   - each forest has an unique ID, name, address;
 - implement the corresponding list of species as an array;
   - each species has an unique ID, popular name, latin name, quantity;
   
Implement the following:
- create, read, update, delete any forests;
- create, read, update, delete any tree species, linked to a forest;
- move any tree species between forests;

Please use a menu to implement the above.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE_OF_STRINGS 30

typedef struct species
{
    int UID;
    char pop_name[MAX_SIZE_OF_STRINGS];
    char latin_name[MAX_SIZE_OF_STRINGS];
    int quantity;
    struct species *prev;
    struct species *next;
} Species;

typedef struct forest_node
{
    int UID;
    char name[MAX_SIZE_OF_STRINGS];
    char address[MAX_SIZE_OF_STRINGS];
    Species *species_head;
    int number_of_species;
    struct forest_node *next;
} Forest;

Forest *head = NULL; /// global list with all the forests

/*
Allocates the memory for a new Forest node, reads the data in new
auxiliary variables, then copies the values from the aux variables
in the fields of the newly made Forest node. After that, it makes
the newly made node the head of the Forests lits.
*/
void create_forest()
{
    Forest *new_forest = (Forest *)malloc(sizeof(Forest));

    int UID_aux;
    printf("\nEnter the forest's UID: ");
    scanf(" %d", &UID_aux);
    char name_aux[MAX_SIZE_OF_STRINGS];
    printf("Please input a name for the forest.\n");
    fscanf(stdin, "%s", name_aux);
    char address_aux[MAX_SIZE_OF_STRINGS];
    printf("Please input an address for the forest.\n");
    fscanf(stdin, "%s", address_aux);

    new_forest->UID = UID_aux;
    strcpy(new_forest->name, name_aux);
    strcpy(new_forest->address, address_aux);
    new_forest->next = head;
    new_forest->species_head = NULL;
    head = new_forest;
}

/*
Searches through the list of forests for a forest whose name
coincides with forest_name and then shows all the data in the 
node
*/
void read_forest(char *forest_name_to_find)
{
    Forest *temp_forest = (Forest *)malloc(sizeof(Forest));
    temp_forest = head;
    while (strcmp(temp_forest->name, forest_name_to_find))
    {
        temp_forest = temp_forest->next;
    }

    printf("\n");
    printf("Forest UID: %d\n", temp_forest->UID);
    printf("Forest name: %s\n", temp_forest->name);
    printf("Forest address:%s\n", temp_forest->address);

    Species *temp_species = (Species *)malloc(sizeof(Species));
    temp_species = temp_forest->species_head;
    while (temp_species != NULL)
    {
        printf("UID: %d\n", temp_species->UID);
        printf("Popular name: %s\n", temp_species->pop_name);
        printf("Latin name: %s\n", temp_species->latin_name);
        printf("Quantity: %d\n", temp_species->quantity);
        temp_species = temp_species->next;
    }
}

/*
Takes a forest name as an argument, then searches in the list for
the forest until it finds it, and then it updates its credentials
*/
void update_forest(char *forest_to_update)
{
    Forest *temp_forest = (Forest *)malloc(sizeof(Forest));
    /*I think this allocation is a problem since i never really free
    this part of the memory and i can't think of a way to safely free
    it right now since it would delete all contents of the list*/
    temp_forest = head;
    while (strcmp(temp_forest->name, forest_to_update))
    {
        temp_forest = temp_forest->next;
    }
    int new_UID;
    char new_name[MAX_SIZE_OF_STRINGS];
    char new_address[MAX_SIZE_OF_STRINGS];

    printf("\nEnter the new forest UID: ");
    scanf(" %d", &new_UID);
    printf("Please input the new name for the forest.\n");
    fscanf(stdin, "%s", new_name);
    printf("Please input the new address for the forest.\n");
    fscanf(stdin, "%s", new_address);

    temp_forest->UID = new_UID;
    strcpy(temp_forest->name, new_name);
    strcpy(temp_forest->address, new_address);
}

/*
PREV -> ACT -> NEXT
We want firstly to find PREV, then change PREV->NEXT to *NEXT,
then we just free the memory allocated to ACT
*/
void delete_forest(char *forest_to_delete)
{
    Forest *forest_temp = (Forest *)malloc(sizeof(Forest));
    forest_temp = head;
    while (strcmp(forest_temp->next->name, forest_to_delete))
    {
        forest_temp = forest_temp->next; //we found PREV
    }

    forest_temp->next = forest_temp->next->next;

    forest_temp = forest_temp->next;
    free(forest_temp);
}

/*
Allocates memory for 1 species, fills it, then it becomes the head 
of forest's list of species.
*/
void create_species(char *forest_to_update)
{
    Forest *forest_temp = (Forest *)malloc(sizeof(Forest));
    forest_temp = head;
    while (strcmp(forest_temp->name, forest_to_update))
    {
        forest_temp = forest_temp->next;
    }

    Species *species_temp = (Species *)malloc(sizeof(Species));

    int UID_aux;
    printf("\nEnter the species' UID: ");
    scanf(" %d", &UID_aux);
    char pop_name_aux[MAX_SIZE_OF_STRINGS];
    printf("Please input a popular name for the forest.\n");
    fscanf(stdin, "%s", pop_name_aux);
    char latin_name_aux[MAX_SIZE_OF_STRINGS];
    printf("Please input a latin name for the forest.\n");
    fscanf(stdin, "%s", latin_name_aux);
    int quantity_aux;
    printf("Enter the quantity of trees: ");
    scanf(" %d", &quantity_aux);

    /* Insert the data into the new species node*/
    species_temp->UID = UID_aux;

    strcpy(species_temp->pop_name, pop_name_aux);
    strcpy(species_temp->latin_name, latin_name_aux);
    species_temp->quantity = quantity_aux;
    species_temp->next = forest_temp->species_head;
    species_temp->prev = NULL;

    /*Change the head of the species list in the forest with the newly 
    made node*/
    forest_temp->species_head->prev = species_temp;
    forest_temp->species_head = species_temp;
}
/*
Takes a forest name as an argument, then searches in the list for
the forest until it finds it, gets the head of the doubly linked 
list containing the species, and goes through each species node, 
printing the attributes of the node.
*/
void read_species(char *forest_to_read_species_from)
{
    Forest *forest_temp = (Forest *)malloc(sizeof(Forest));
    forest_temp = head;
    while (strcmp(forest_temp->name, forest_to_read_species_from))
    {
        forest_temp = forest_temp->next;
    }

    Species *temp_species = (Species *)malloc(sizeof(Species));

    temp_species = forest_temp->species_head;

    while (temp_species != NULL)
    {
        printf("UID: %d\n", temp_species->UID);
        printf("Popular name: %s\n", temp_species->pop_name);
        printf("Latin name: %s\n", temp_species->latin_name);
        printf("Quantity: %d\n", temp_species->quantity);
        temp_species = temp_species->next;
    }
}
/*
Goes through the entire list of Forests. In each Forest node,
goes through every species node, looking for a node with the 
desired name. When it finds it, it updates its popular name
(updating latin name is unfeasible, it doesn't change, updating
quantity would be useless since it every quantity is specific
to its own forest). 
*/
void update_species(char *species_to_update, char *new_popular_name)
{
    Forest *forest_temp = (Forest *)malloc(sizeof(Forest));
    forest_temp = head;

    Species *species_temp = (Species *)malloc(sizeof(Species));

    while (forest_temp != NULL)
    {
        species_temp = forest_temp->species_head;
        while (species_temp != NULL)
        {
            if (strcmp(species_temp->pop_name, species_to_update) == 0)
            {
                strcpy(species_temp->pop_name, new_popular_name);
            }
            species_temp = species_temp->next;
        }
        forest_temp = forest_temp->next;
    }
}

/*
Gets as an argument a forest name and a species name, then
goes through the forest's list of species, and when it finds 
the desired species name, it deletes the node from the list,
also freeing the memory. 
*/
void delete_species(char *forest_to_delete_species_from, char *species_to_delete)
{
    Forest *forest_temp = (Forest *)malloc(sizeof(Forest));
    forest_temp = head;

    Species *species_temp = (Species *)malloc(sizeof(Species));

    while (strcmp(forest_temp->name, forest_to_delete_species_from))
    {
        forest_temp = forest_temp->next;
    }

    species_temp = forest_temp->species_head;
    while (strcmp(species_temp->pop_name, species_to_delete))
    {
        species_temp = species_temp->next;
    }

    /*
    Now that we found the species to delete, we just change the pointers
    so that it "forgets" this node.
    */

    species_temp->prev->next = species_temp->next;
    species_temp->next->prev = species_temp->prev;
    free(species_temp);
}

/*
Gets three arguments, two forest names, one being the address
and one the destination, and a species name. Then it goes through
the species name in the address forest, stores all info in a temp,
uses delete_species to delete the species from that forest, and
then adds the temp to the list of species in the destination forest
species list.
*/
void move_species(char *forest_to_extract_species, char *forest_to_add_extracted_species, char *species_to_be_extracted)
{

    Forest *forest_temp = (Forest *)malloc(sizeof(Forest));
    forest_temp = head;

    Species *species_temp = (Species *)malloc(sizeof(Species));
    Species *species_aux = (Species *)malloc(sizeof(Species));

    while (strcmp(forest_temp->name, forest_to_extract_species))
    {
        forest_temp = forest_temp->next;
    }

    species_temp = forest_temp->species_head;
    while (strcmp(species_temp->pop_name, species_to_be_extracted))
    {
        species_temp = species_temp->next;
    }

    species_aux->UID = species_temp->UID;
    strcpy(species_aux->pop_name, species_temp->pop_name);
    strcpy(species_aux->latin_name, species_temp->latin_name);
    species_aux->quantity = species_temp->quantity;

    forest_temp = head;
    while (strcmp(forest_temp->name, forest_to_add_extracted_species))
    {
        forest_temp = forest_temp->next;
    }

    /*Add the species_aux node as head of the species list of the new forest*/
    species_aux->next = forest_temp->species_head;
    forest_temp->species_head->prev = species_aux;
    species_aux->next = forest_temp->species_head;
    species_aux->prev = NULL;
    forest_temp->species_head = species_aux;
}

void free_forest_list()
{
    Forest *current;
    Forest *next;

    current = head;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}
int main(int argc, char **argv)
{

    char choice;
    int i_want_to_exit;
    i_want_to_exit = 0;

    while (!i_want_to_exit)
    {
        printf("1:Create forest\n");
        printf("2:Read forest\n");
        printf("3:Update forest\n");
        printf("4:Delete forest\n");
        printf("5:Create species\n");
        printf("6:Read species\n");
        printf("7:Update species\n");
        printf("8:Delete species\n");
        printf("9:Move species between forests:\n");
        printf("e:Exit main menu\n");

        scanf(" %c", &choice);

        switch (choice)
        {
        case '1':
            create_forest();
            break;
        case '2':
            printf("Please input the name of the forest you want to read.\n");
            char forest_to_read[MAX_SIZE_OF_STRINGS];
            fscanf(stdin, "%s", forest_to_read);
            read_forest(forest_to_read);
            break;
        case '3':
            printf("Please input the name of the forest you want to update.\n");
            char forest_to_update[MAX_SIZE_OF_STRINGS];
            fscanf(stdin, "%s", forest_to_update);
            update_forest(forest_to_update);
            break;
        case '4':
            printf("Please input the name of the forest you want to delete.\n");
            char forest_to_delete[MAX_SIZE_OF_STRINGS];
            fscanf(stdin, "%s", forest_to_delete);
            delete_forest(forest_to_delete);
            break;
        case '5':
            printf("To which forest would you like to add the species?\n");
            char forest_to_add_species[MAX_SIZE_OF_STRINGS];
            fscanf(stdin, "%s", forest_to_add_species);
            create_species(forest_to_add_species);
            break;
        case '6':
            printf("From which forest would you like to read the species?\n");
            char forest_to_read_species_from[MAX_SIZE_OF_STRINGS];
            fscanf(stdin, "%s", forest_to_read_species_from);
            read_species(forest_to_read_species_from);
            break;
        case '7':
            printf("Which species would you like to update?\n");
            char species_to_update_popular_name[MAX_SIZE_OF_STRINGS];
            fscanf(stdin, "%s", species_to_update_popular_name);
            printf("What is the new popular name?\n");
            char new_popular_name[MAX_SIZE_OF_STRINGS];
            fscanf(stdin, "%s", new_popular_name);
            update_species(species_to_update_popular_name, new_popular_name);
            break;
        case '8':
            printf("What is the name of the species you intend to delete?\n");
            char species_to_delete[MAX_SIZE_OF_STRINGS];
            fscanf(stdin, "%s", species_to_update_popular_name);
            printf("What is the forest you want to delete the species from?\n");
            char forest_to_delete_species_from[MAX_SIZE_OF_STRINGS];
            fscanf(stdin, "%s", new_popular_name);
            delete_species(forest_to_delete_species_from, species_to_delete);
            break;
        case '9':
            printf("What is the name of the forest you want to extract the species from?\n");
            char forest_to_extract_species[MAX_SIZE_OF_STRINGS];
            fscanf(stdin, "%s", forest_to_extract_species);
            printf("What is the forest you want to add the extracted species to?\n");
            char forest_to_add_extracted_species[MAX_SIZE_OF_STRINGS];
            fscanf(stdin, "%s", forest_to_add_extracted_species);
            printf("What is the popular name of the species you want to extract?\n");
            char species_to_be_extracted[MAX_SIZE_OF_STRINGS];
            fscanf(stdin, "%s", species_to_be_extracted);
            move_species(forest_to_extract_species, forest_to_add_extracted_species, species_to_be_extracted);
            break;
        case 'e':
            i_want_to_exit = 1;
            break;
        default:
            printf("Invalid input!\n");
            break;
        }
    }
    free_forest_list();
    return 0;
}