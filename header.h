#ifndef HEADER_H
#define HEADER_H

typedef struct contact {
	char fname[20];
	char lname[20];
	char email[40];
	char phoneNum[15];
	char address[80];
	char company[100];
	char note[200];
}CONTACT;

void switchCase();
void optionsMenu();
void createFile();
void addContact();
void deleteContacts();
void listAllContacts();
void searchContact();
void deleteEnter(char* tempContact);
void fnameSort();
void lnameSort();
void sortMenu();
void editContact();

#endif // HEADER_H