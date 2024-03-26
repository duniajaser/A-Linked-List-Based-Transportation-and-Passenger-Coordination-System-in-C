#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100
#define MAX 1000

// Dunia Jaser 1201345
// Section 1 - Dr. Ahmed Abusnaina

typedef struct node *ptr;
struct node{
    int mode;// if mode = 1 then node is passenger, if mode = 0 then node is bus
    int Id;
    char name[SIZE];
    char travelling_date[SIZE];
    int travelling_time_hour;
    int travelling_time_minute;
    char from[SIZE];
    char to[SIZE];
    float ticket_price_bus;
    int capacity_bus;
    ptr next;
    int match ;// 0 if the passenger is unmatched , 1 is the passenger is matched
    int current_number_of_pass_in_bus ;
    ptr next_passenger_in_specific_bus ;
};
typedef ptr Linked_List;


void display_menu();
void read_bus_info_from_file();
void read_passengers_info_from_file();
void add_to_Linked_list(Linked_List,ptr);
void print_List_Information(Linked_List);
void book_a_bus_from_files(Linked_List,Linked_List);
int valid_Id(Linked_List,ptr);
void print_bus_pass_info(Linked_List);// all buses and their passengers in the system
void add_to_Linked_list1(Linked_List,ptr,ptr);
void print_unmatchedList_Information(Linked_List);
ptr copying_passenger_info(ptr);
void delete_a_node(Linked_List, int);//for passengers list (for pointer next)
ptr find_previous_node(Linked_List, int );// for passengers (for pointer next)
ptr copying_bus_info(ptr );
void print_a_specific_bus_information(Linked_List , int);
void determine_the_current_pass(Linked_List);
void add_a_passenger();
void delete_a_pass(ptr, int);//for system list (for pointer next_passenger_in_specific_bus)
ptr find_previous_pass(ptr, int);//for system list (for pointer next_passenger_in_specific_bus)
void delete_a_passenger();
void print_bus_pass(ptr);//only for one bus and its passengers in the system
void delete_bus_number();
//void unmatched_passengers_number(Linked_List);



static int read_passengers = 0; // to let the user read from file only one time.
static int read_buses = 0;

Linked_List passengers_Linked_List;
Linked_List passengersss;//copied
Linked_List bussesss;//copied
Linked_List buses_Linked_List;
Linked_List busses_passengers; // system


int main()
{
    display_menu();
    return 0;
}

void display_menu(){
    printf("\n------------------------------MENU---------------------------------\n");
    printf("Choose one of these options:\n");
    printf("1) Load the bus information file.\n");
    printf("2) Load the passenger information file.\n");
    printf("3) Assign passengers and print assignment information of all buses.\n");
    printf("4) Print unmatched passengers.\n");
    printf("5) Print a specific bus information along with its passengers information (names and IDs).\n");
    printf("6) Add new passenger.\n");
    printf("7) Delete passenger.\n");
    printf("8) Delete bus number.\n");
    printf("9) Exit the program.\n");
    int choice;
    scanf("%d",&choice);
    if (choice == 1)
    {
        read_bus_info_from_file();
    }
    else if (choice == 2)
    {
        read_passengers_info_from_file();
    }
     else if (choice == 3)
    {
        if(passengersss == NULL || bussesss == NULL){
            printf("You have to load the info before by choosing 1 and 2 from menu.\n");
            display_menu();
        }else
          book_a_bus_from_files(buses_Linked_List,passengers_Linked_List);
    }
     else if (choice == 4)
    {
        if(passengers_Linked_List == NULL){
            printf("You have to load the info before by choosing 1 and 2 from menu.\n");
            display_menu();
        }
        print_unmatchedList_Information(passengers_Linked_List);
        display_menu();
    }
    else if (choice == 5)
    {
    int key ;
    printf("Enter the bus number:\n");
    scanf("%d",&key);
    print_a_specific_bus_information(busses_passengers,key);
    }
     else if (choice == 6)
    {
        add_a_passenger();
    }
    else if (choice == 7)
    {
        delete_a_passenger();
    }
     else if (choice == 8)
    {
        delete_bus_number();
    }
    else if (choice == 9 )//exit from the program.
    {
        printf("Hope you enjoy trying this program ^_^\n");
        exit(0);
    }
    else
    {
        printf("Not a valid choice. \n");
        display_menu();
    }

}
void read_bus_info_from_file(){
    if( read_buses == 0){// this statement to let the user read the file only one time.
        buses_Linked_List = (Linked_List)malloc(sizeof(struct node));
        bussesss = (Linked_List)malloc(sizeof(struct node));
        FILE *in = fopen("busses.txt","r");
        if(in == NULL){
            printf("The buses file not found!\n");
            exit(0);
        }
        int lines_count = 0;
        char c;
        for( c = fgetc(in); c != EOF ; c = fgetc(in) ){
            if( c == '\n')
            lines_count += 1;
    }
    fclose(in);
    FILE *information = fopen("busses.txt","r");
    int times = 0;
    char *token;
    char *token1;
    char tempTokTime[SIZE];
    while(information != NULL){
        ptr temp;
        temp = (ptr)malloc(sizeof(struct node));
        char line[MAX];
        fgets(line,sizeof(line),information) ;
        token = strtok(line,"#");//id
        temp->Id = atoi(token);

        if(token != NULL){
                token = strtok(NULL,"#");//date
                times++;
        }
        strcpy(temp->travelling_date, token);

         if(token != NULL){
                token = strtok(NULL,"#");//time
                strcpy(tempTokTime,token);
        }

         if(token != NULL){
                token = strtok(NULL,"#");//from
        }
        strcpy(temp->from, token);

         if(token != NULL){
                token = strtok(NULL,"#");//to
        }
        strcpy(temp->to, token);


         if(token != NULL){
                token = strtok(NULL,"#");//price
        }
        temp->ticket_price_bus = atof(token);

        if(token != NULL){
                token = strtok(NULL,"#");//capacity
        }
        temp->capacity_bus = atoi(token);
        temp->next_passenger_in_specific_bus =NULL;
        token1 = strtok(tempTokTime,":");
        temp->travelling_time_hour = atoi(token1);
        token1 = strtok(NULL,":");
        temp->travelling_time_minute = atoi(token1) ;
        temp->mode = 0;
        add_to_Linked_list(buses_Linked_List,temp);
        ptr tem = copying_bus_info(temp);
        add_to_Linked_list(bussesss,tem);
        if(times == lines_count)
            break;
    }
    fclose(information);
    }else{
       printf("You had read the buses information before!\n");
       display_menu();
   }
    read_buses++;
   printf("The operation done successfully!\n");
    display_menu();
}

// format: passenger in file ID#NAME#DATE#TIME#FROM#TO
void read_passengers_info_from_file(){
   if(read_passengers ==0){ // this statement to let the user read the file only one time.
    passengers_Linked_List = (Linked_List)malloc(sizeof(struct node));
    passengersss = (Linked_List)malloc(sizeof(struct node));

    FILE *in = fopen("passengers.txt","r");
    if(in == NULL){
            printf("The passengers file not found!\n");
            exit(0);
        }
    int lines_count = 0;
    char c;
    for( c = fgetc(in); c != EOF ; c = fgetc(in) ){
        if( c == '\n')
            lines_count += 1;
    }
    fclose(in);
    FILE *information = fopen("passengers.txt","r");
    int times = 0;
    char *token;
    char *token1;
    char tempTokTime[SIZE];
    while(information != NULL){
        ptr temp;
        temp = (ptr)malloc(sizeof(struct node));
        char line[MAX];
        fgets(line,sizeof(line),information) ;
        token = strtok(line,"#");//id
        temp->Id = atoi(token);

        if(token != NULL){
                token = strtok(NULL,"#");//name
        }

        strcpy(temp->name, token);

        if(token != NULL){
                token = strtok(NULL,"#");//date
                times++;
        }
        strcpy(temp->travelling_date, token);

         if(token != NULL){
                token = strtok(NULL,"#");//time
                strcpy(tempTokTime,token);
        }

         if(token != NULL){
                token = strtok(NULL,"#");//from
        }
        strcpy(temp->from, token);

         if(token != NULL){
                token = strtok(NULL,"#");//to
        }
        int length = strlen(token);
        token[length - 1 ] = '\0';
        strcpy(temp->to, token);

        token1 = strtok(tempTokTime,":");
        temp->travelling_time_hour = atoi(token1);
        token1 = strtok(NULL,":");
        temp->travelling_time_minute = atoi(token1) ;

        temp->mode = 1;
        temp->match = 1;
        add_to_Linked_list(passengers_Linked_List,temp);
        ptr tem1 = copying_passenger_info(temp);
        add_to_Linked_list(passengersss,tem1);
        if(times == lines_count)
            break;
    }
    fclose(information);


   }else{
       printf("You had read the passengers information before!\n");
       display_menu();
   }
    read_passengers++;
 //   print_List_Information(passengers_Linked_List);
    printf("The operation done successfully!\n");

    display_menu();
}


void add_to_Linked_list(Linked_List List,ptr temp){
    if( valid_Id(List,temp) == 1){
    ptr currentElement = List;
   if(List != NULL && temp != NULL){
        while(currentElement->next != NULL)
            currentElement = currentElement->next;
        currentElement->next = temp;
        temp->next = NULL;
    }
        if(List == NULL)
            printf("The List references to NULL.\n");
         if(temp == NULL)
            printf("The new added element references to NULL.\n");

    } else{
        if(temp->mode == 1)
            printf("You can not add passenger %s ( id = %d ), because the passenger's id is not unique!\n",temp->name,temp->Id);
        else
            printf("You can not add bus ( number = %d ), because the bus' number is not unique!\n",temp->Id);
    }

}

void add_to_Linked_list1(Linked_List List ,ptr temp ,ptr bus ){//for adding unmatched passengers
    int exists = 0 ;

   if(List != NULL && temp != NULL){
      ptr current = List;

      while(current->next != NULL){
        if( current->Id ==  bus->Id){
            exists += 1;
            break;
        }
        current = current->next;
      }
    if(current->next == NULL){// if the bus is in the last node
         if( current->Id ==  bus->Id){
            exists += 1;
        }
      }

      if(exists == 0 ){ // means that the bus is not exists before.
        ptr current1 = List;
        while(current1->next != NULL)
            current1 = current1->next;
        current1->next = bus;
        bus->next = NULL;

        ptr positionbus =  List;
        while(positionbus->next != NULL)
            positionbus = positionbus->next;
        ptr positionpass = positionbus;
        while(positionpass->next_passenger_in_specific_bus != NULL)
           positionpass = positionpass->next_passenger_in_specific_bus;

        positionpass->next_passenger_in_specific_bus = temp;
        temp->next_passenger_in_specific_bus = NULL;

      }
      if(exists > 0 ){// the bus exists before in the list.
       ptr position_bus;
        ptr current2 = List;

      while(current2->next != NULL){
            if( current2->Id ==  bus->Id){
                position_bus = current2;
                break;
        }
        current2 = current2->next;
      }

      if(current2->next == NULL){// if the bus is in the last node
         if( current2->Id ==  bus->Id){
             position_bus = current2;
         }
      }

          ptr pos_passenger = position_bus;
          while(pos_passenger->next_passenger_in_specific_bus != NULL)
            pos_passenger = pos_passenger->next_passenger_in_specific_bus;
          pos_passenger->next_passenger_in_specific_bus = temp;
          temp->next_passenger_in_specific_bus = NULL;

      }

    }
        if(List == NULL)
            printf("The List references to NULL.\n");
         if(temp == NULL)
            printf("The new added element references to NULL.\n");

}

void print_unmatchedList_Information(Linked_List List){
           printf("---------------------------------------------------------------\n");

    ptr pointerr = List->next  ;
        printf("The unmatched passengers information :\n");
        printf("Passenger ID:\tName:\t\tDate:\t\tTime:\tFrom:\t\tTo:\n");
        while(pointerr!= NULL){
            printf("%d\t\t%s\t\t%s\t%d:%d\t%s\t\t%s\n",pointerr->Id,pointerr->name,pointerr->travelling_date,pointerr->travelling_time_hour,pointerr->travelling_time_minute,pointerr->from,pointerr->to);
            pointerr = pointerr->next;
        }
}
void print_List_Information(Linked_List List){
    if(List == NULL)
        printf("The list is empty!\n");
    else{
        ptr pointerr;
        pointerr = List->next;
        if(pointerr->mode == 1){
            printf("The passengers information :\n");
            printf("Passenger ID:\tName:\t\tDate:\t\tTime:\tFrom:\t\tTo:\n");
        while(pointerr != NULL){
            printf("%d\t\t%s\t\t%s\t%d:%d\t%s\t\t%s\n",pointerr->Id,pointerr->name,pointerr->travelling_date,pointerr->travelling_time_hour,pointerr->travelling_time_minute,pointerr->from,pointerr->to);
            pointerr = pointerr->next;
        }
           printf("---------------------------------------------------------------\n");
       display_menu();
        }

         if(pointerr->mode == 0){
            printf("The busses information :\n");
        int i = 1;
        while(pointerr != NULL){
            printf("Bus #%d:\n",i);
            printf("ID: %d\nDate:  %s\nTime:  %d:%d\nFrom: %s\nTo: %s\nTicket-Price: %.1f\nCapacity: %d\n",pointerr->Id,pointerr->travelling_date,pointerr->travelling_time_hour,pointerr->travelling_time_minute,pointerr->from,pointerr->to,pointerr->ticket_price_bus,pointerr->capacity_bus);
            pointerr = pointerr->next;
            printf("---------------------------------------------------------------\n");
            i++;
        }

    }

}
}
int valid_Id(Linked_List passengers,ptr temp){
    int valid = 1 ;
    ptr list = passengers->next;
    while(list != NULL){
        if(list->Id == temp->Id){
            valid = 0;
            break;
        }
        list = list->next;
    }
    return valid;

}

void determine_the_current_pass(Linked_List buss_pass){
    ptr bus = buss_pass;
    while(bus->next != NULL){
        int capacity = bus->capacity_bus;
        ptr pass = bus ;
        bus->current_number_of_pass_in_bus = 0;
        while(pass->next_passenger_in_specific_bus != NULL){

                 if( bus->current_number_of_pass_in_bus <= capacity ){
                     bus->current_number_of_pass_in_bus += 1;
                    bus->capacity_bus--;

                }

                if( bus->current_number_of_pass_in_bus > capacity){
                    pass->next_passenger_in_specific_bus = NULL;
                    bus->capacity_bus = 0;
                    bus->current_number_of_pass_in_bus = capacity;
                    break;
                }
                pass = pass->next_passenger_in_specific_bus;

        }

        bus = bus->next;
    }
    if(bus->next == NULL){
        int capacity = bus->capacity_bus;
        ptr pass = bus ;
        bus->current_number_of_pass_in_bus = 0;
        while(pass->next_passenger_in_specific_bus != NULL){

                 if( bus->current_number_of_pass_in_bus <= capacity ){
                     bus->current_number_of_pass_in_bus += 1;
                    bus->capacity_bus--;

                }

                if( bus->current_number_of_pass_in_bus > capacity){
                    pass->next_passenger_in_specific_bus = NULL;
                    break;
                }
                pass = pass->next_passenger_in_specific_bus;
    }
}
}
int timesssss = 0 ;

void book_a_bus_from_files(Linked_List busses, Linked_List passengers){
    if(timesssss == 0){
    if(busses != NULL && passengers != NULL ){
    ptr temp_bus = busses->next;
    busses_passengers = (Linked_List)malloc(sizeof(struct node));
    int time;
    while(temp_bus != NULL){
        ptr pass_in_bus ;
        ptr temp_passenger = passengers->next;
        temp_bus->current_number_of_pass_in_bus = 0;
        time = 0;
        ptr tem = copying_bus_info(temp_bus);
        add_to_Linked_list(busses_passengers,tem);

        int capacity = temp_bus->capacity_bus;
        while(temp_passenger != NULL){
            if((strcmp(temp_bus->from ,temp_passenger->from)==0) && (strcmp(temp_bus->to,temp_passenger->to)==0) && (strcmp(temp_bus->travelling_date,temp_passenger->travelling_date)==0) && (temp_bus->travelling_time_hour == temp_passenger->travelling_time_hour)&& (temp_bus->travelling_time_minute == temp_passenger->travelling_time_minute)){
                if(temp_bus->current_number_of_pass_in_bus <= capacity){
                temp_bus->current_number_of_pass_in_bus ++;
                ptr bus = copying_bus_info(temp_bus);
                if(time == 0)
                    pass_in_bus = temp_bus;
                ptr current = copying_passenger_info(temp_passenger);
                pass_in_bus->next_passenger_in_specific_bus = current;
                add_to_Linked_list1(busses_passengers,current,bus);

                delete_a_node(passengers,temp_passenger->Id);
                pass_in_bus = pass_in_bus->next_passenger_in_specific_bus;
                capacity -= 1 ;
                time++;
                } else{
                temp_passenger->match = 0;
                ptr current = copying_passenger_info(temp_passenger);
                printf("The bus ( number %d ) is full of passengers! We will add (%s) to the waiting list.\n",temp_bus->Id,current->name);
        }
            }else{
                temp_passenger->match = 0;
                }

        temp_passenger = temp_passenger->next;
    }
    temp_bus =temp_bus->next;
}

    determine_the_current_pass(busses_passengers);
    //sizeOfLink(passengers); // the number of unmatched passengers
    print_bus_pass_info(busses_passengers);
    timesssss += 1;

    display_menu();
    }else{
            printf("The lists are Empty! you have to load them from files by choosing 1 and 2 from menu.\n");
            display_menu();
    }
    }
    else{
        printf("You had chosen it before!\n");
        display_menu();
    }
    }


/*void sizeOfLink(Linked_List L){
 ptr temp = L->next;
    int times = 0 ;
    while(temp != NULL){
        temp = temp->next;
        times++;
    }
    printf("The number of unmatched passengers is %d\n",times);
    }
*/

ptr copying_bus_info(ptr temp){
    ptr current = (ptr)malloc(sizeof(struct node));
    current->Id = temp->Id;
    current->mode = temp->mode;
    strcpy(current->travelling_date,temp->travelling_date);
    strcpy(current->from, temp->from);
    strcpy(current->to, temp->to);
    current->travelling_time_hour = temp->travelling_time_hour;
    current->travelling_time_minute = temp->travelling_time_minute;
    current->capacity_bus = temp->capacity_bus;
    current->current_number_of_pass_in_bus = temp->current_number_of_pass_in_bus;
    current->ticket_price_bus = temp->ticket_price_bus;
    return current;
}
ptr copying_passenger_info(ptr temp_passenger){
    ptr current = (ptr)malloc(sizeof(struct node));
    current->Id = temp_passenger->Id;
    strcpy(current->name,temp_passenger->name);
    current->mode = temp_passenger->mode;
    strcpy(current->travelling_date,temp_passenger->travelling_date);
    strcpy(current->from, temp_passenger->from);
    strcpy(current->to, temp_passenger->to);
    current->travelling_time_hour = temp_passenger->travelling_time_hour;
    current->travelling_time_minute = temp_passenger->travelling_time_minute;
    current->match = temp_passenger->match;
    return current;
}

void delete_a_node(Linked_List passengerss , int id ){
   if( passengerss != NULL){
        ptr point = find_previous_node(passengerss,id);
        if(point != NULL){
            ptr d = point->next;
            point->next = d->next;
            free(d);
        }
    }else{
    printf("The list is empty!\n");
    }


}
ptr find_previous_node(Linked_List list , int key){
    ptr p = list->next;
    ptr s = list ;
    while( p != NULL && key != p->Id){
        p = p->next;
        s = s->next;
    }

    if(p == NULL)
        return p;
    else
        return s;
}
void print_bus_pass_info(Linked_List busses){
    printf("\n---------------------------------------------------------------\n");
    ptr temp =busses->next;
    ptr temp_pass;
    while(temp != NULL ){
       if(temp->next_passenger_in_specific_bus == NULL){
            printf("The bus ( number %d ),current number of passengers %d, capacity %d, has the passengers:\n",temp->Id,temp->current_number_of_pass_in_bus,temp->capacity_bus);
                printf("The bus is Empty!\n");
                printf("---------------------------------------------------------------\n");

       }
       if( temp->next_passenger_in_specific_bus != NULL){
            temp_pass = temp->next_passenger_in_specific_bus;
        printf("The bus ( number %d ),current number of passengers %d, capacity %d, has the passengers:\n",temp->Id,temp->current_number_of_pass_in_bus,temp->capacity_bus);
        printf("Date %s, time %d:%d, from %s to %s\n",temp->travelling_date,temp->travelling_time_hour,temp->travelling_time_minute,temp->from,temp->to);
        while(temp_pass != NULL){
            printf("ID: %d, name: %s\n",temp_pass->Id,temp_pass->name);
            temp_pass = temp_pass->next_passenger_in_specific_bus;
              }
              printf("---------------------------------------------------------------\n");
       }
    temp = temp->next;

    }
    printf("\n---------------------------------------------------------------\n");
}
void print_a_specific_bus_information(Linked_List busses, int key ){
    if(busses != NULL ){
         int h = 0;
        ptr currnt = busses;
        while(currnt->next != NULL){
            if(currnt->Id == key){
                h += 1;
                break;
            }
            currnt = currnt->next;
        }

         if(currnt->next == NULL){
            if(currnt->Id == key){
                h += 1;
            }
        }
    if(h == 0){//the bus does not exists in the list.
            printf("The bus you are trying to reach is not existed in the list, please try again.\n");
            display_menu();

    }else{
        ptr p = busses;
        while(p->next != NULL){
            if(p->Id == key){
            printf("The bus number %d, date %s, time %d:%d, from %s to %s, the current number passengers %d , the capacity %d, have the passengers:\n",p->Id,p->travelling_date,p->travelling_time_hour,p->travelling_time_minute,p->from,p->to,p->current_number_of_pass_in_bus,p->capacity_bus);

            ptr pass = p->next_passenger_in_specific_bus;
            if(pass == NULL){
                    printf("The bus is Empty!\n");
                                display_menu();

            }
            while(pass->next_passenger_in_specific_bus != NULL){
            printf("%d\t\t%s\t\t%s\t%d:%d\t%s\t\t%s\n",pass->Id,pass->name,pass->travelling_date,pass->travelling_time_hour,pass->travelling_time_minute,pass->from,pass->to);
            pass = pass->next_passenger_in_specific_bus;
            }
           if(pass->next_passenger_in_specific_bus == NULL){
                printf("%d\t\t%s\t\t%s\t%d:%d\t%s\t\t%s\n",pass->Id,pass->name,pass->travelling_date,pass->travelling_time_hour,pass->travelling_time_minute,pass->from,pass->to);
            }

            display_menu();
            }
            p = p ->next;
        }
        if(p->next == NULL){
            if(p->Id == key){
            printf("The bus number %d, date %s, time %d:%d, from %s to %s, the current number passengers %d , the capacity %d, have the passengers:\n",p->Id,p->travelling_date,p->travelling_time_hour,p->travelling_time_minute,p->from,p->to,p->current_number_of_pass_in_bus,p->capacity_bus);

            ptr pass = p->next_passenger_in_specific_bus;
            if(pass == NULL){
                    printf("The bus is Empty!\n");
            }
            while(pass->next_passenger_in_specific_bus != NULL){
            printf("%d\t\t%s\t\t%s\t%d:%d\t%s\t\t%s\n",pass->Id,pass->name,pass->travelling_date,pass->travelling_time_hour,pass->travelling_time_minute,pass->from,pass->to);
            pass = pass->next_passenger_in_specific_bus;
            }
           if(pass->next_passenger_in_specific_bus == NULL){
                printf("%d\t\t%s\t\t%s\t%d:%d\t%s\t\t%s\n",pass->Id,pass->name,pass->travelling_date,pass->travelling_time_hour,pass->travelling_time_minute,pass->from,pass->to);
            }

            display_menu();
            }
        }
    }
    }else{
        printf("The bus list is empty! you have to choose 1, 2 and 4 from menu to load the all information.\n");
        display_menu();
    }
}
void add_a_passenger(){
    printf("--------------------------------------------------\n");
    if(passengersss == NULL || passengers_Linked_List == NULL){
                printf("please choose 1 and 2 from menu!");
                display_menu();
    }
    ptr new1 =(ptr)malloc(sizeof(struct node));
    printf("Enter Id: \n");
    scanf("%d",&new1->Id);
    printf("Enter name: \n");
    scanf("%s",new1->name);
    printf("Enter date: \n");
    scanf("%s",new1->travelling_date);
    printf("Enter time (hour minute): \n");
    scanf("%d %d",&new1->travelling_time_hour,&new1->travelling_time_minute);
    printf("Enter from: \n");
    scanf("%s",new1->from);
    printf("Enter to: \n");
    scanf("%s",new1->to);
    if(passengersss != NULL || passengers_Linked_List != NULL){
    add_to_Linked_list(passengersss,new1);
    ptr temp = (ptr)malloc(sizeof(struct node));
     temp =copying_passenger_info(new1);
    add_to_Linked_list(passengers_Linked_List,temp);
    }
    display_menu();
}
void delete_a_passenger(){
    if(passengers_Linked_List == NULL || buses_Linked_List ==NULL){
        printf("You have to load the info by choosing 1, 2 and 3 from menu.\n");
        display_menu();
    }
    printf("Enter the passenger ID:\n");
    int pass_key ;
    scanf("%d",&pass_key);
    printf("Enter the bus ID:\n");
    int bus_key ;
    scanf("%d",&bus_key);
    printf("------------------------------------------------\n");
    ptr temp_bus = busses_passengers;
    int bus_exists = 0;
    int pass_exists = 0;
    while(temp_bus->next != NULL){
            if(temp_bus->Id == bus_key){
                 bus_exists = 1;
        ptr temp_pass = temp_bus;
        while(temp_pass->next_passenger_in_specific_bus != NULL){
                if(temp_pass->Id == pass_key){
                pass_exists = 1;
                printf("The passenger Id:%d, name:%s, date:%s, time: %d:%d, from %s, to %s is deleted.\n",temp_pass->Id,temp_pass->name,temp_pass->travelling_date,temp_pass->travelling_time_hour,temp_pass->travelling_time_minute,temp_pass->from,temp_pass->to);
                temp_bus->current_number_of_pass_in_bus--;
                temp_bus->capacity_bus++;
                delete_a_pass(temp_bus,pass_key);
                print_bus_pass(temp_bus);
                break;
                }

             temp_pass = temp_pass->next_passenger_in_specific_bus;
        }
 if(temp_pass->next_passenger_in_specific_bus == NULL){
                if(temp_pass->Id == pass_key){
                pass_exists = 1;
                printf("The passenger Id:%d, name:%s, date:%s, time: %d:%d, from %s, to %s is deleted.\n",temp_pass->Id,temp_pass->name,temp_pass->travelling_date,temp_pass->travelling_time_hour,temp_pass->travelling_time_minute,temp_pass->from,temp_pass->to);
                temp_bus->current_number_of_pass_in_bus--;
                temp_bus->capacity_bus++;
                delete_a_pass(temp_bus,pass_key);
                print_bus_pass(temp_bus);
                }
            }

            }
       temp_bus = temp_bus->next;

    }
    if(temp_bus->next == NULL){
          if(temp_bus->Id == bus_key){
            bus_exists = 1;
        ptr temp_pass = temp_bus;
        while(temp_pass->next_passenger_in_specific_bus != NULL){
                if(temp_pass->Id == pass_key){
                pass_exists = 1;
                printf("The passenger Id:%d, name:%s, date:%s, time: %d:%d, from %s, to %s is deleted.\n",temp_pass->Id,temp_pass->name,temp_pass->travelling_date,temp_pass->travelling_time_hour,temp_pass->travelling_time_minute,temp_pass->from,temp_pass->to);
                temp_bus->current_number_of_pass_in_bus--;
                temp_bus->capacity_bus++;
                delete_a_pass(temp_bus,temp_pass->Id);
                print_bus_pass(temp_bus);
                break;
                }

             temp_pass = temp_pass->next_passenger_in_specific_bus;
            }
                if(temp_pass->next_passenger_in_specific_bus == NULL){
                if(temp_pass->Id == pass_key){
                pass_exists = 1;
                printf("The passenger Id:%d, name:%s, date:%s, time: %d:%d, from %s, to %s is deleted.\n",temp_pass->Id,temp_pass->name,temp_pass->travelling_date,temp_pass->travelling_time_hour,temp_pass->travelling_time_minute,temp_pass->from,temp_pass->to);
                temp_bus->current_number_of_pass_in_bus--;
                temp_bus->capacity_bus++;
                delete_a_pass(temp_bus,pass_key);
                print_bus_pass(temp_bus);
                    }
                }
        }
    }

    if(bus_exists == 0){
        printf("The bus %d does not exist!\n",bus_key);
        printf("Please try again\n");
        display_menu();
    }
    if(pass_exists == 0){
        printf("The passenger %d does not exist in bus %d !\n",pass_key,bus_key);
        printf("Please try again\n");
        display_menu();
    }
    display_menu();
}
void print_bus_pass(ptr bus){
    printf("------------------------------------------------\n");
    printf("After deleting a passenger.\n");
    printf("The bus number %d, date %s, time %d:%d, from %s to %s, the current number passengers %d , the capacity %d, have the passengers:\n",bus->Id,bus->travelling_date,bus->travelling_time_hour,bus->travelling_time_minute,bus->from,bus->to,bus->current_number_of_pass_in_bus,bus->capacity_bus);
    ptr temp = bus->next_passenger_in_specific_bus;
    if(temp  == NULL){
            printf("The bus is Empty!\n");
    }
    while(temp->next_passenger_in_specific_bus != NULL){
        printf("%d\t\t%s\t\t%s\t%d:%d\t%s\t\t%s\n",temp->Id,temp->name,temp->travelling_date,temp->travelling_time_hour,temp->travelling_time_minute,temp->from,temp->to);
        temp = temp->next_passenger_in_specific_bus;
    }
    if(temp->next_passenger_in_specific_bus == NULL){
        printf("%d\t\t%s\t\t%s\t%d:%d\t%s\t\t%s\n",temp->Id,temp->name,temp->travelling_date,temp->travelling_time_hour,temp->travelling_time_minute,temp->from,temp->to);
    }
}
void delete_a_pass(ptr bus , int id ){
   if( bus != NULL){
        ptr point = find_previous_pass(bus,id);
        if(point != NULL){
            ptr d = point->next_passenger_in_specific_bus;
            point->next_passenger_in_specific_bus = d->next_passenger_in_specific_bus;
            d->next_passenger_in_specific_bus = NULL;
        }
    }else{
    printf("The list is empty!\n");
    }
}

ptr find_previous_pass(ptr list , int key){
    ptr p = list->next_passenger_in_specific_bus;
    ptr s = list ;
    while( p != NULL && key != p->Id){
        p = p->next_passenger_in_specific_bus;
        s = s->next_passenger_in_specific_bus;
    }

    if(p == NULL)
        return p;
    else
        return s;
}
void delete_bus_number(){
    if(passengers_Linked_List == NULL || buses_Linked_List ==NULL){
        printf("You have to load the info by choosing 1, 2 and 3 from menu.\n");
        display_menu();
    }
    int bus_key;
    printf("Enter the bus number:\n");
    scanf("%d",&bus_key);
    int bus_exist = 0;
    ptr bus = busses_passengers;

    while(bus->next != NULL){
        if(bus->Id == bus_key){
            bus_exist = 1;
            ptr pass = bus->next_passenger_in_specific_bus;
            if( pass == NULL){//the bus is empty
                delete_a_node(busses_passengers,bus_key);
                break;
            }
            while(pass->next_passenger_in_specific_bus != NULL){
                ptr copiedd = copying_passenger_info(pass);
                add_to_Linked_list(passengers_Linked_List,copiedd);
                pass = pass->next_passenger_in_specific_bus;
            }
            if(pass->next_passenger_in_specific_bus == NULL){
                 ptr copiedd = copying_passenger_info(pass);
                add_to_Linked_list(passengers_Linked_List,copiedd);
            }
            delete_a_node(busses_passengers,bus_key);
            break;
        }
        bus = bus->next;
    }
    if(bus->next == NULL){
            if(bus->Id == bus_key){
            bus_exist = 1;
            ptr pass = bus->next_passenger_in_specific_bus;
            while(pass->next_passenger_in_specific_bus != NULL){
                ptr copiedd = copying_passenger_info(pass);
                add_to_Linked_list(passengers_Linked_List,copiedd);
                pass = pass->next_passenger_in_specific_bus;
            }
            if(pass->next_passenger_in_specific_bus == NULL){
                 ptr copiedd = copying_passenger_info(pass);
                add_to_Linked_list(passengers_Linked_List,copiedd);
            }
            delete_a_node(busses_passengers,bus_key);
        }
    }
    if(bus_exist == 0 ){
        printf("The bus not found!\n");
        display_menu();
    }else{
        printf("The operation done successfully!\n");
    }

    printf("The list after the bus removed:\n");
    print_bus_pass_info(busses_passengers);
    print_unmatchedList_Information(passengers_Linked_List);

    display_menu();
}
