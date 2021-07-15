#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include "header.h"

static unsigned int counter = 0; //Brojač za kontakte

//FUNKCIJA ZA BIRANJE OPCIJA IZBORNIKA
void switchCase() {
	int option = -1;

	while (1) {
		createFile();
		optionsMenu();

		printf("\nChoose an option: ");
		scanf("%d", &option); printf("\n");

		switch (option) {

		case 1:
			//printf("ADD NEW CONTACT\n\n");
			addContact();
			break;

		case 2:
			//printf("LIST ALL CONTACT\n\n");
			listAllContacts();
			break;

		case 3:
			//printf("SEARCH CONTACTS\n\n");
			searchContact();
			break;

		case 4:
			//printf("SORT CONTACTS\n\n");
			sortMenu();
			break;

		case 5:
			//printf("EDIT CONTACT\n\n");
			editContact();
			break;

		case 6:
			//printf("DELETE ALL CONTACTS\n\n");
			deleteContacts();
			break;

		case 0:
			return;

		default:
			printf("Error: Choose your option again\n\n");
		}

	}
}

//FUNKCIJA ZA PRIKAZ OPCIJA IZBORNIKA
void optionsMenu() {
	printf("===============CHOOSE AN OPTION===============\n");
	printf("----------------------------------------------\n");
	printf("[1] ADD NEW CONTACT\n"); 
	printf("----------------------------------------------\n");
	printf("[2] LIST ALL CONTACT\n"); 
	printf("----------------------------------------------\n");
	printf("[3] SEARCH CONTACTS\n"); 
	printf("----------------------------------------------\n");
	printf("[4] SORT CONTACTS\n");
	printf("----------------------------------------------\n");
	printf("[5] EDIT CONTACT\n");
	printf("----------------------------------------------\n");
	printf("[6] DELETE ALL CONTACTS\n"); 
	printf("----------------------------------------------\n");
	printf("[0] EXIT\n"); 
	printf("----------------------------------------------\n");
	printf("==============================================\n");
}

//FUNKCIJA ZA KREIRANJE DATOTEKE
void createFile() {
	FILE* fp = fopen("contacts.bin", "rb"); //Ako postoji, otvori binarnu datoteku u svrhu čitanja

	if (fp == NULL) {
		//printf("Error: Creating contacts.bin file!\n\n");
		fp = fopen("contacts.bin", "wb"); //Ako ne postoji, kreiraj datoteku u svrhu zapisivanja

		if (fp == NULL) { 
			printf("Error: Writing/Creating contacts.bin file!\n\n");
			exit(EXIT_FAILURE);
		}
		else {
			fwrite(&counter, sizeof(int), 1, fp); //Zapiši broj kontakata na početak datoteke
		}
	}
	else {
		//printf("File is created!\n");
	}
	fclose(fp);
}

//FUNCKIJA ZA DODAVANJE KONTAKTA
void addContact() {
	FILE* fp = fopen("contacts.bin", "ab"); //Otvori datoteku u svrhu naknadnog dodavanja sadržaja

	if (fp == NULL) {
		printf("Error: Opening contacts.bin for reading & writing!\n");
		exit(EXIT_FAILURE);
	}
	else {
		counter++; //Counter +1 za dodavanja kontakta

		//printf("\nNumber of contacts: %d\n", counter);

		CONTACT tempContact = { 0 }; //Kreiranje privremenog kontakta koji služi za pohranu novog

		printf("First name: ");
		//scanf("%19s", tempContact.fname);
		getchar();
		fgets(tempContact.fname, 20, stdin);
		deleteEnter(tempContact.fname);

		printf("Last name: ");
		//scanf("%19s", tempContact.lname);
		fgets(tempContact.lname, 20, stdin);
		deleteEnter(tempContact.lname);

		printf("Email: ");
		//scanf("%39s", tempContact.email);
		fgets(tempContact.email, 40, stdin);
		deleteEnter(tempContact.email);

		printf("Phone number: ");
		//scanf("%14s", tempContact.phoneNum);
		fgets(tempContact.phoneNum, 15, stdin);
		deleteEnter(tempContact.phoneNum);

		printf("Address: ");
		//scanf("%79[^\n]", tempContact.address);
		fgets(tempContact.address, 80, stdin);
		deleteEnter(tempContact.address);

		printf("Company: ");		
		//scanf("%99[^\n]", tempContact.company);
		fgets(tempContact.company, 100, stdin);
		deleteEnter(tempContact.company);

		printf("Note: ");
		//scanf("%249[^\n]", tempContact.note);
		fgets(tempContact.note, 200, stdin);
		deleteEnter(tempContact.note);

		printf("\n");

		//fseek(fp, sizeof(int), SEEK_SET);
		fwrite(&tempContact, sizeof(CONTACT), 1, fp); //Zapiši privremenog kontakta u datoteku
	}
	fclose(fp);

	//SPREMANJE BROJA KONTAKATA NA POČETAK DATOTEKE
	FILE* fc = fopen("contacts.bin", "rb+");
	fwrite(&counter, sizeof(int), 1, fc);

	fclose(fc);
}

//FUNKCIJA ZA BRISANJE SVIH KONTAKATA
void deleteContacts() {
	int x;

	x = remove("contacts.bin"); //Funkcija za brisanje datoteke

	if (x == 0) {
		printf("Successfully deleted all the contacts!\n\n");
		counter = 0; //Postavljanje broja kontakata na 0
	
	}
	else
		printf("Error: Deleting all the contacts!\n\n");
}

//FUNKCIJA ZA ISPIS SVIH KONTAKATA
void listAllContacts() {
	FILE* fp = NULL;
	fp = fopen("contacts.bin", "rb");

	if (fp == NULL) {
		printf("Error: Reading the file!\n");
		exit(EXIT_FAILURE);
	}
	else {
		CONTACT* allContacts = NULL;

		fread(&counter, sizeof(int), 1, fp); //Pročitaj broj kontakata s početka datoteke
		//printf("Broj kontakata: %d\n", counter);

		if (counter == 0) {
			printf("NO CONTACTS FOUND!\n\n");
			fclose(fp);
			return;
		}
		else {
			allContacts = (CONTACT*)calloc(counter, sizeof(CONTACT)); //Zauzimanje memorije za sve kontakte

			if (allContacts == NULL) {
				printf("Error: Allocating the memory for listing all contacts!\n");
				exit(EXIT_FAILURE);
			}
			else {
				fseek(fp, sizeof(int), SEEK_SET); //Pomakni za sizeof(int) zbog countera
				fread(allContacts, sizeof(CONTACT), counter, fp); //Pročitaj sve kontakte
				fclose(fp);

				for (int i = 0; i < counter; i++) {
					printf("\t\t\n\t--------------------------------------------------------\n\t|\tFirst name: %s\n\t|\tLast Name: %s\n\t|\tEmail: %s\n\t|\tPhone number: %s\n\t|\tAddress: %s\n\t|\tCompany: %s\n\t|\tNote: %s\t\t\n\t--------------------------------------------------------\n\n", (allContacts + i)->fname, (allContacts + i)->lname, (allContacts + i)->email, (allContacts + i)->phoneNum, (allContacts + i)->address, (allContacts + i)->company, (allContacts + i)->note);
				}
				free(allContacts); 
			}
		}
	}
}

//FUNKCIJA ZA TRAZENJE KONTAKTA
void searchContact() {
	FILE* fp = NULL;
	fp = fopen("contacts.bin", "rb");

	if (fp == NULL) {
		printf("Error: Searching for contact!\n");
		exit(EXIT_FAILURE);
	}
	else {
		CONTACT* allContacts = NULL;
		fread(&counter, sizeof(int), 1, fp); //Procitaj broj kontakata iz datoteke

		if (counter == 0) {
			printf("\nNo contacts found!\n");
			fclose(fp);
			return;
		}
		else {
			allContacts = (CONTACT*)calloc(counter, sizeof(CONTACT)); //Zauzimanje memorije za sve kontakte

			if (allContacts == NULL) {
				printf("Error: Reading all of the contacts");
				exit(EXIT_FAILURE);
			}
			else {
				fseek(fp, sizeof(int), SEEK_SET); //Pomakni za sizeof(int) zbog countera
				fread(allContacts, sizeof(CONTACT), counter, fp); //Čitanje svih kontakata
				fclose(fp);

				unsigned int search;

				printf("Search by: \n[1] FIRST NAME\n[2] LAST NAME\n[3] PHONE NUMBER\n\nChoose an option: ");
				scanf("%u", &search); 
				printf("\n");
				
				char tempFirstName[20] = { '\0' }, tempLastName[20] = { '\0' }, tempPhoneNum[15] = { '\0' }; 
				int result; //Provjera kod strcmp

				switch (search) {
					case 1: 
						printf("Enter contacts first name: ");
						scanf("%19s", tempFirstName);
						
						for (int i = 0; i < counter; i++) {
							result = strcmp((allContacts + i)->fname, tempFirstName); //Kada su 2 stringa jednaka, result = 0
							
							if (result == 0) {
								//printf("Contact found!\n");

								printf("\t\t\n\t--------------------------------------------------------\n\t|\tFirst name: %s\n\t|\tLast Name: %s\n\t|\tEmail: %s\n\t|\tPhone number: %s\n\t|\tAddress: %s\n\t|\tCompany: %s\n\t|\tNote: %s\t\t\n\t--------------------------------------------------------\n\n", (allContacts + i)->fname, (allContacts + i)->lname, (allContacts + i)->email, (allContacts + i)->phoneNum, (allContacts + i)->address, (allContacts + i)->company, (allContacts + i)->note);
							}
						}
						printf("\n");
						break;

					case 2: 
						printf("Enter contacts last name: ");
						scanf("%19s", tempLastName);

						for (int i = 0; i < counter; i++) {
							result = strcmp((allContacts + i)->lname, tempLastName); //Kada su 2 stringa jednaka, result = 0

							if (result == 0) {
								//printf("Contact found!\n");
								
								printf("\t\t\n\t--------------------------------------------------------\n\t|\tFirst name: %s\n\t|\tLast Name: %s\n\t|\tEmail: %s\n\t|\tPhone number: %s\n\t|\tAddress: %s\n\t|\tCompany: %s\n\t|\tNote: %s\t\t\n\t--------------------------------------------------------\n\n", (allContacts + i)->fname, (allContacts + i)->lname, (allContacts + i)->email, (allContacts + i)->phoneNum, (allContacts + i)->address, (allContacts + i)->company, (allContacts + i)->note);
							}
						}
						printf("\n");
						break;
					
					case 3:
						printf("Enter contacts phone number: ");
						scanf("%14s", tempPhoneNum);

						for (int i = 0; i < counter; i++) {
							result = strcmp((allContacts + i)->phoneNum, tempPhoneNum); //Kada su 2 stringa jednaka, result = 0

							if (result == 0) {
								//printf("Contact found!\n");

								printf("\t\t\n\t--------------------------------------------------------\n\t|\tFirst name: %s\n\t|\tLast Name: %s\n\t|\tEmail: %s\n\t|\tPhone number: %s\n\t|\tAddress: %s\n\t|\tCompany: %s\n\t|\tNote: %s\t\t\n\t--------------------------------------------------------\n\n", (allContacts + i)->fname, (allContacts + i)->lname, (allContacts + i)->email, (allContacts + i)->phoneNum, (allContacts + i)->address, (allContacts + i)->company, (allContacts + i)->note);
							}
						}
						printf("\n");
						break;
						
					default:
						printf("Error: Choose your options again!\n");
				}
				free(allContacts);
			}
		}
	}
}

//FUNKCIJA ZA BRISANJE ENTERA
void deleteEnter(char* tempContact) {
	int n = strlen(tempContact);

	if (tempContact[n - 1] == '\n')
		tempContact[n - 1] = '\0';
}

//FUNKCIJA ZA SORTIRANJE KONTAKATA PO IMENIMA
void fnameSort() {
	FILE* fp = NULL;
	fp = fopen("contacts.bin", "rb");

	if (fp == NULL) {
		printf("Error: Creating the file in nameSort function!\n");
		exit(EXIT_FAILURE);
	}
	else {
		CONTACT* allContacts = NULL;
		fread(&counter, sizeof(int), 1, fp); //Pročitaj broj kontakata s početka datoteke

		if (counter == 0) {
			printf("No contacts found!\n");
			fclose(fp);
		}
		else {
			allContacts = (CONTACT*)calloc(counter, sizeof(CONTACT)); //Zauzimanje memorije za sve kontakte
			CONTACT temp;
			char fLetter, hLetter;
			int min;

			if (allContacts == NULL) {
				printf("Error: Reading all the contacts for sorting!\n");
				exit(EXIT_FAILURE);
			}
			else {
				fread(allContacts, sizeof(CONTACT), counter, fp); //Pročitaj sve kontakte iz datoteke

				for (int i = 0; i < counter - 1; i++) {
					min = i;
					fLetter = (allContacts + i)->fname[0] >= 'A' && (allContacts + i)->fname[0] <= 'Z' ? (allContacts + i)->fname[0] : (allContacts + i)->fname[0] - 32;

					for (int j = i + 1; j < counter; j++) {
						hLetter = (allContacts + j)->fname[0] >= 'A' && (allContacts + j)->fname[0] <= 'Z' ? (allContacts + j)->fname[0] : (allContacts + j)->fname[0] - 32;

						if (fLetter < hLetter) {
							min = j;
							fLetter = (allContacts + j)->fname[0] >= 'A' && (allContacts + j)->fname[0] <= 'Z' ? (allContacts + j)->fname[0] : (allContacts + j)->fname[0] - 32;

						}
					}
					strcpy(temp.fname, (allContacts + i)->fname);
					strcpy((allContacts + i)->fname, (allContacts + min)->fname);
					strcpy((allContacts + min)->fname, temp.fname);
					
					strcpy(temp.lname, (allContacts + i)->lname);
					strcpy((allContacts + i)->lname, (allContacts + min)->lname);
					strcpy((allContacts + min)->lname, temp.lname);

					strcpy(temp.email, (allContacts + i)->email);
					strcpy((allContacts + i)->email, (allContacts + min)->email);
					strcpy((allContacts + min)->email, temp.email);

					strcpy(temp.address, (allContacts + i)->address);
					strcpy((allContacts + i)->address, (allContacts + min)->address);
					strcpy((allContacts + min)->address, temp.address);

					strcpy(temp.company, (allContacts + i)->company);
					strcpy((allContacts + i)->company, (allContacts + min)->company);
					strcpy((allContacts + min)->company, temp.company);

					strcpy(temp.phoneNum, (allContacts + i)->phoneNum);
					strcpy((allContacts + i)->phoneNum, (allContacts + min)->phoneNum);
					strcpy((allContacts + min)->phoneNum, temp.phoneNum);
				}

				for (int i = 0; i < counter; i++) {
					printf("\t\t\n\t--------------------------------------------------------\n\t|\tFirst name: %s\n\t|\tLast Name: %s\n\t|\tEmail: %s\n\t|\tPhone number: %s\n\t|\tAddress: %s\n\t|\tCompany: %s\n\t|\tNote: %s\t\t\n\t--------------------------------------------------------\n\n", (allContacts + i)->fname, (allContacts + i)->lname, (allContacts + i)->email, (allContacts + i)->phoneNum, (allContacts + i)->address, (allContacts + i)->company, (allContacts + i)->note);
				}
				free(allContacts);
				fclose(fp);
			}
		}
	}
}

void lnameSort() {
	FILE* fp = NULL;
	fp = fopen("contacts.bin", "rb");

	if (fp == NULL) {
		printf("Error: Creating the file in nameSort function!\n");
		exit(EXIT_FAILURE);
	}
	else {
		CONTACT* allContacts = NULL;
		fread(&counter, sizeof(int), 1, fp); //Pročitaj broj kontakata s početka datoteke

		if (counter == 0) {
			printf("No contacts found!\n");
			fclose(fp);
		}
		else {
			allContacts = (CONTACT*)calloc(counter, sizeof(CONTACT)); //Zauzmi memoriju za sve kontakte
			CONTACT temp;
			char fLetter, hLetter;
			int min;

			if (allContacts == NULL) {
				printf("Error: Reading all the contacts for sorting!\n");
				exit(EXIT_FAILURE);
			}
			else {
				fread(allContacts, sizeof(CONTACT), counter, fp);

				for (int i = 0; i < counter - 1; i++) {
					min = i;
					fLetter = (allContacts + i)->lname[0] >= 'A' && (allContacts + i)->lname[0] <= 'Z' ? (allContacts + i)->lname[0] : (allContacts + i)->lname[0] - 32;

					for (int j = i + 1; j < counter; j++) {
						hLetter = (allContacts + j)->lname[0] >= 'A' && (allContacts + j)->lname[0] <= 'Z' ? (allContacts + j)->lname[0] : (allContacts + j)->lname[0] - 32;

						if (fLetter < hLetter) {
							min = j;
							fLetter = (allContacts + j)->lname[0] >= 'A' && (allContacts + j)->lname[0] <= 'Z' ? (allContacts + j)->lname[0] : (allContacts + j)->lname[0] - 32;

						}
					}
					strcpy(temp.fname, (allContacts + i)->fname);
					strcpy((allContacts + i)->fname, (allContacts + min)->fname);
					strcpy((allContacts + min)->fname, temp.fname);

					strcpy(temp.lname, (allContacts + i)->lname);
					strcpy((allContacts + i)->lname, (allContacts + min)->lname);
					strcpy((allContacts + min)->lname, temp.lname);

					strcpy(temp.email, (allContacts + i)->email);
					strcpy((allContacts + i)->email, (allContacts + min)->email);
					strcpy((allContacts + min)->email, temp.email);

					strcpy(temp.address, (allContacts + i)->address);
					strcpy((allContacts + i)->address, (allContacts + min)->address);
					strcpy((allContacts + min)->address, temp.address);

					strcpy(temp.company, (allContacts + i)->company);
					strcpy((allContacts + i)->company, (allContacts + min)->company);
					strcpy((allContacts + min)->company, temp.company);

					strcpy(temp.phoneNum, (allContacts + i)->phoneNum);
					strcpy((allContacts + i)->phoneNum, (allContacts + min)->phoneNum);
					strcpy((allContacts + min)->phoneNum, temp.phoneNum);
				}

				for (int i = 0; i < counter; i++) {
					printf("\t\t\n\t--------------------------------------------------------\n\t|\tFirst name: %s\n\t|\tLast Name: %s\n\t|\tEmail: %s\n\t|\tPhone number: %s\n\t|\tAddress: %s\n\t|\tCompany: %s\n\t|\tNote: %s\t\t\n\t--------------------------------------------------------\n\n", (allContacts + i)->fname, (allContacts + i)->lname, (allContacts + i)->email, (allContacts + i)->phoneNum, (allContacts + i)->address, (allContacts + i)->company, (allContacts + i)->note);
				}
				free(allContacts);
				fclose(fp);
			}
		}
	}
}

void sortMenu() {
	int num;
	printf("[1] SORT BY FIRST NAME\n[2] SORT BY LAST NAME\n\nEnter a number: ");
	scanf("%d", &num);

	if (num == 1)
		fnameSort();
	else if (num == 2)
		lnameSort();
	else
		printf("\nError: Invalid number entered!\n\n");
}


void editContact() {
	FILE* fp = NULL;
	fp = fopen("contacts.bin", "rb");

	if (fp == NULL) {
		printf("Error: Reading the file for editing a contact!\n");
		exit(EXIT_FAILURE);
	}
	else {
		CONTACT* allContacts = NULL;
		fread(&counter, sizeof(int), 1, fp); //Pročitaj broj kontakata s početka datoteke

		if (counter == 0) {
			printf("No contacts found!\n");
			fclose(fp);
			return;
		}
		else {
			allContacts = (CONTACT*)calloc(counter, sizeof(CONTACT)); //Zauzmi memoriju za sve kontakte

			if (allContacts == NULL) {
				printf("Error: Reading all the contacts!\n");
				exit(EXIT_FAILURE);
			}
			else {
				CONTACT tempContact = { 0 };
				fread(allContacts, sizeof(CONTACT), counter, fp); //Pročitaj sve kontakte
				
				char tempfName[50] = { '\0' };
				char templName[50] = { '\0' };

				printf("Enter contacts first name: ");
				scanf(" %50[^\n]", tempfName);
				printf("Enter contacts last name: ");
				scanf(" %50[^\n]", templName);

				unsigned int stat = 0; //Varijabla za provjeru izvršavanja if-a
				unsigned int index = -1; //Varijabla u koju spremamo index traženog kontakta

				for (int i = 0; i < counter; i++) {
					if (!strcmp((allContacts + i)->fname, tempfName) && !strcmp((allContacts + i)->lname, templName)) {
						stat = 1;
						index = i;
					}
				 }

				if (stat == 1) {
					printf("\nContact found!\n");

					printf("\t\t\n\t--------------------------------------------------------\n\t|\tFirst name: %s\n\t|\tLast Name: %s\n\t|\tEmail: %s\n\t|\tPhone number: %s\n\t|\tAddress: %s\n\t|\tCompany: %s\n\t|\tNote: %s\t\t\n\t--------------------------------------------------------\n\n", (allContacts + index)->fname, (allContacts + index)->lname, (allContacts + index)->email, (allContacts + index)->phoneNum, (allContacts + index)->address, (allContacts + index)->company, (allContacts + index)->note);
					fclose(fp);

					fp = fopen("contacts.bin", "rb+");

					printf("First name: ");
					//scanf("%19s", tempContact.fname);
					getchar();
					fgets(tempContact.fname, 20, stdin);
					deleteEnter(tempContact.fname);

					printf("Last name: ");
					//scanf("%19s", tempContact.lname);
					fgets(tempContact.lname, 20, stdin);
					deleteEnter(tempContact.lname);

					printf("Email: ");
					//scanf("%39s", tempContact.email);
					fgets(tempContact.email, 40, stdin);
					deleteEnter(tempContact.email);

					printf("Phone number: ");
					//scanf("%14s", tempContact.phoneNum);
					fgets(tempContact.phoneNum, 15, stdin);
					deleteEnter(tempContact.phoneNum);

					printf("Address: ");
					//scanf("%79[^\n]", tempContact.address);
					fgets(tempContact.address, 80, stdin);
					deleteEnter(tempContact.address);

					printf("Company: ");
					//scanf("%99[^\n]", tempContact.company);
					fgets(tempContact.company, 100, stdin);
					deleteEnter(tempContact.company);

					printf("Note: ");
					//scanf("%249[^\n]", tempContact.note);
					fgets(tempContact.note, 200, stdin);
					deleteEnter(tempContact.note);

					fseek(fp, sizeof(unsigned int) + ((index) * sizeof(CONTACT)), SEEK_SET); //Pozicioniraj se kod traženog kontakta
					fwrite(&tempContact, sizeof(CONTACT), 1, fp); //Zapiši uređenog kontakta
					rewind(fp); //Pozicioniraj se na početak
					//fwrite(counter, sizeof(unsigned int), 1, fp);
					fclose(fp);
				}
				else {
					printf("Non-existant contact!\n");
				}
				free(allContacts);
			}
		}
	}
	fclose(fp);
}
