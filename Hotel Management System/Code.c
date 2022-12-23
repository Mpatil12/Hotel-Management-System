#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
   char foodname[50];
   int quantity;
   float price;
   int d;
   struct node *prev;
   struct node *next;
};

struct customer
{
   char Name[50];
   char gender;
   int age;
} C[25];

int Customer_No = 0, Male = 0, Female = 0, SixtyPlus = 0, FourtyPlus = 0, UnderFouty = 0;
char date[10];
float total_sales;
struct node *headc = NULL, *newnode, *tailc = NULL;
struct node *heada = NULL, *taila = NULL;
struct node *head_s;
struct node *createmenu(struct node *head, int d, char foodname[25], float price);
struct node *createorder(struct node *head, int d, int quantity);
void displayMenu(struct node *head);
void displayOrder(struct node *head);
struct node *totalsales(int d, int quantity);
void calculatetotsales();
struct node *delete (int dt, struct node *head, struct node *tail);
struct node *deleteM(int dt, struct node *head, struct node *tail);
int deleteMenu();
int deleteOrder();
void displaybill();
struct node *deleteList(struct node *head);
void Display_Customer_Details();
void Monthly_Details();
void Owner();
void Manager();
void customer();
void Search_By_Date();

int main()
{
   heada = createmenu(heada, 101, "Cheese-Pizza", 330);
   heada = createmenu(heada, 102, "Special-Pav-Bhaji", 210);
   heada = createmenu(heada, 103, "Manchurian-Noodles", 400);
   heada = createmenu(heada, 104, "Cheese-Burger", 250);
   heada = createmenu(heada, 105, "Cherry-Pineapple", 350);
   heada = createmenu(heada, 106, "Chiken-Nawabi", 500);
   heada = createmenu(heada, 107, "Paneer-Bhaji ", 450);
   heada = createmenu(heada, 108, "Veg-Fried-Rice", 300);
   heada = createmenu(heada, 109, "Cherry-Pineapple", 375);
   heada = createmenu(heada, 110, "Cherry-Pineapple", 350);
   heada = createmenu(heada, 111, "Egg-Fried-Rice", 275);

   struct node *temp = heada;
   printf("Enter today's date : ");
   gets(date);
   FILE *f;
   f = fopen("Sales.txt", "a");
   fclose(f);
   FILE *fp;
   fp = fopen("Menu.txt", "w");
   if (fp == NULL)
      printf("\nError");
   else
   {
      while (temp != NULL)
      {
         fprintf(fp, "%d \t%s \t%f\n", temp->d, temp->foodname, temp->price);
         temp = temp->next;
      }
   }
   fclose(fp);
   int choice;
   do
   {
      printf("\n=========================================================\n");
      printf("           WELCOME TO TAJ HOTEL\n");
      printf("==========================================================\n\n\n");
      printf("          1. OWNER DESK   \n");
      printf("          2. MANAGER DESK \n");
      printf("          3. CUSTOMER DESK \n");
      printf("          4. Exit \n\n");
      printf("          Enter Your Choice : ");
      scanf("%d", &choice);
      switch (choice)
      {
      case 1:
         Owner();
         break;

      case 2:
         Manager();
         break;

      case 3:
         customer();
         break;

      case 4:
         printf("\n\nThank You! \nShutting Down ");
         break;

      default:
         printf("          Wrong Input, Choose valid option\n");
         break;
      }
   } while (choice != 4);
}

struct node *createmenu(struct node *head, int d, char foodname[25], float price)
{

   newnode = (struct node *)malloc(sizeof(struct node));
   newnode->d = d;
   newnode->price = price;
   newnode->quantity = 0;
   strcpy(newnode->foodname, foodname);
   newnode->next = NULL;
   newnode->prev = NULL;

   struct node *temp = heada;

   if (temp == NULL)
      heada = taila = newnode;
   else
   {
      while (temp->next != NULL)
      {
         temp = temp->next;
      }
      temp->next = newnode;
      newnode->prev = taila;
      taila = newnode;
   }

   return heada;
}

struct node *createorder(struct node *head, int d, int quantity)
{
   newnode = (struct node *)malloc(sizeof(struct node));

   struct node *temp1 = heada;
   int flag = 0;
   while (temp1 != NULL)
   {
      if (temp1->d == d)
      {
         flag = 1;
         break;
      }
      temp1 = temp1->next;
   }

   if (flag == 1)
   {
      newnode->d = d;
      newnode->price = quantity * (temp1->price);
      newnode->quantity = quantity;
      strcpy(newnode->foodname, temp1->foodname);
      newnode->next = NULL;
      newnode->prev = NULL;

      struct node *temp = head;

      if (temp == NULL)
         headc = tailc = newnode;
      else
      {
         while (temp->next != NULL)
            temp = temp->next;

         temp->next = newnode;
         newnode->prev = tailc;
         tailc = newnode;
      }
   }
   else
   {
      printf("          This food item is not available in the menu card!\n");
   }

   return headc;
}

void displayMenu(struct node *head)
{
   int da;
   float price;
   char name[100];
   FILE *fp;
   fp = fopen("Menu.txt", "r");
   int n = 0;
   while (!feof(fp))
   {
      fscanf(fp, "%d %s %f", &da, name, &price);
      n++;
   }
   rewind(fp);

   printf("\n");
   printf("        Sr.no.\t    FoodName  \t       Price\n");
   printf("     -----------------------------------------------------\n");
   if (fp == NULL)
      printf("\nError");
   else
      for (int i = 0; i < n - 1; i++)
      {
         fscanf(fp, "%d %s %f", &da, name, &price);
         printf("          %d\t%s     \t%0.2f\n", da, name, price);
      }
   fclose(fp);
}

void displayOrder(struct node *head)
{
   struct node *temp1 = head;

   total_sales = 0;

   if (temp1 == NULL)
   {
      printf("\n          No Order!!\n\n");
   }
   else
   {
      printf("\n");
      printf("        Sr.no.\t    FoodName  \t    Quantity\tPrice\n");
      printf("     -----------------------------------------------------\n");

      while (temp1 != NULL)
      {
         if (temp1->quantity == 0)
            printf("          %d\t%s     \t%0.2f\n", temp1->d, temp1->foodname, temp1->price);
         else
         {
            printf("          %d\t%s     \t%d     \t%0.2f\n", temp1->d, temp1->foodname, temp1->quantity, temp1->price);
         }
         total_sales += temp1->price;
         temp1 = temp1->next;
      }
      printf("-------------------------------------------------------------------------------\n");
      printf(" Today's Sales : %f\n", total_sales);
      printf("-------------------------------------------------------------------------------\n");
      printf("\n");
   }
}

void totalsalesfile(struct node *head)
{
   FILE *fp;
   fp = fopen("Sales.txt", "a");
   struct node *temp2 = head;
   total_sales = 0;
   if (fp == NULL)
      printf("\nError in opening file ");
   else
   {
      fprintf(fp, "\n%s", date);
      fprintf(fp, "\n");
      fprintf(fp, "        Sr.no.\t    FoodName  \t    Quantity\tPrice\n");
      fprintf(fp, "     -----------------------------------------------------\n");

      while (temp2 != NULL)
      {
         if (temp2->quantity == 0)
            fprintf(fp, "          %d\t%s     \t%0.2f\n", temp2->d, temp2->foodname, temp2->price);
         else
         {
            fprintf(fp, "          %d\t%s     \t%d     \t%0.2f\n", temp2->d, temp2->foodname, temp2->quantity, temp2->price);
         }
         total_sales += temp2->price;
         temp2 = temp2->next;
      }
      fprintf(fp, "-------------------------------------------------------------------------------\n");
      fprintf(fp, " Today's Sales : %f\n", total_sales);
      fprintf(fp, "-------------------------------------------------------------------------------\n\n");
      fprintf(fp, "Number of Males                          %d\n", Male);
      fprintf(fp, "Number of Females                        %d\n", Female);
      fprintf(fp, "Number of People below fourty            %d\n", UnderFouty);
      fprintf(fp, "Number of People above fourty            %d\n", FourtyPlus);
      fprintf(fp, "Number of People above sixty             %d\n", SixtyPlus);
      fprintf(fp, "\n");
   }

   fclose(fp);
}

void Profit(struct node *head)
{
   struct node *temp1 = head;

   total_sales = 0;
   while (temp1 != NULL)
   {
      if (temp1->quantity == 0)
         printf("          %d\t%s     \t%0.2f\n", temp1->d, temp1->foodname, temp1->price);
      else
      {
         printf("          %d\t%s     \t%d     \t%0.2f\n", temp1->d, temp1->foodname, temp1->quantity, temp1->price);
      }
      total_sales += temp1->price;
      temp1 = temp1->next;
   }
   float Profit = (55 / 100) * total_sales;
   printf("Profit is : %f", Profit);
}

struct node *totalsales(int d, int quantity)
{
   newnode = (struct node *)malloc(sizeof(struct node));
   int flag = 0;

   struct node *temp1 = heada;
   while (temp1->d != d)
   {
      temp1 = temp1->next;
   }

   newnode->d = d;
   newnode->price = quantity * (temp1->price);
   newnode->quantity = quantity;
   strcpy(newnode->foodname, temp1->foodname);
   newnode->next = NULL;
   newnode->prev = NULL;

   struct node *temp = head_s;

   if (temp == NULL)
      head_s = newnode;
   else
   {
      while (temp->next != NULL)
      {
         if (temp->d == d)
         {
            flag = 1;
            break;
         }
         temp = temp->next;
      }

      if (flag == 1)
      {
         temp->quantity += newnode->quantity;
         temp->price += newnode->price;
      }
      else
      {
         temp->next = newnode;
      }
   }

   return head_s;
}

void calculatetotsales()
{
   struct node *temp = headc;
   while (temp != NULL)
   {
      head_s = totalsales(temp->d, temp->quantity);
      temp = temp->next;
   }
}

struct node *delete (int dt, struct node *head, struct node *tail)
{
   int a;
   if (head == NULL)
   {
      printf("\n          No order available!!\n");
   }
   else
   {
      struct node *temp;
      if (dt == head->d)
      {
         temp = head;
         if (head != NULL && head->quantity == 1)
         {
            head = head->next;
            head->prev = NULL;
            free(temp);
         }
         (head->quantity)--;
      }
      else if (dt == tail->d)
      {
         temp = tail;
         if (tail->quantity == 1)
         {
            tail = tail->prev;
            tail->next = NULL;
            free(temp);
         }
         (tail->quantity)--;
      }
      else
      {
         temp = head;
         while (dt != temp->d)
         {
            temp = temp->next;
         }
         if (temp->quantity == 1)
         {
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            free(temp);
         }

         (temp->quantity)--;
      }
   }
   return head;
}

struct node *deleteM(int dt, struct node *head, struct node *tail)
{
   int a;
   if (head == NULL)
   {
      printf("\n          No Order Available\n");
   }
   else
   {
      struct node *temp;
      if (dt == head->d)
      {
         temp = head;
         head = head->next;
         if (head != NULL)
         {
            head->prev = NULL;
            free(temp);
         }
      }
      else if (dt == tail->d)
      {
         temp = tail;
         tail = tail->prev;
         tail->next = NULL;
         free(temp);
      }
      else
      {
         temp = head;
         while (dt != temp->d)
         {
            temp = temp->next;
         }
         (temp->prev)->next = temp->next;
         (temp->next)->prev = temp->prev;
         free(temp);
      }
   }
   return head;
}
int deleteMenu()
{
   printf("\n          Enter Sr.No. of the food item which you want to delete: ");

   int num;
   int a = 0;
   scanf("%d", &num);
   struct node *temp = heada;
   while (temp != NULL)
   {
      if (temp->d == num)
      {
         heada = deleteM(num, heada, taila);
         a = 1;
         break;
      }
      temp = temp->next;
   }

   char nm[100];
   int t = 0;
   int dat;
   float p;
   FILE *fp, *ft;
   fp = fopen("Menu.txt", "r");
   ft = fopen("data1.txt", "wb+");
   while (!feof(fp))
   {
      fscanf(fp, "%d %s %f", &dat, nm, &p);
      t++;
   }
   rewind(fp);
   for (int i = 0; i < t - 1; i++)
   {
      fscanf(fp, "%d %s %f", &dat, nm, &p);

      if (dat != num)
      {
         fprintf(ft, "%d\t %s\t %f\n", dat, nm, p);
      }
   }

   fclose(fp);
   fclose(ft);
   remove("Menu.txt");
   rename("data1.txt", "Menu.txt");

   if (a == 1)
      return 1;
   return 0;
}

int deleteOrder()
{

   int num, Qty;
   printf("\n          Enter Sr.No. of the food item which you want to delete: ");
   scanf("%d", &num);
   printf("\n          Enter quantity want to delete: ");
   scanf("%d", &Qty);

   struct node *temp = headc;
   while (temp != NULL)
   {
      if (temp->d == num)
      {
         if (temp->quantity == Qty)
         {
            headc = delete (num, headc, tailc);
         }
         else
         {
            temp->quantity = temp->quantity - Qty;
            temp->price = temp->price - (temp->price / Qty);
         }
         return 1;
      }
      temp = temp->next;
   }
   return 0;
}

void displaybill()
{
   displayOrder(headc);
   struct node *temp = headc;
   float total_price = 0;
   while (temp != NULL)
   {
      total_price += temp->price;
      temp = temp->next;
   }

   printf("-----------------------------------------------------------------------\n");
   printf("\n          Price :-\t\t %0.02f       \n", total_price);
   float gst = (((105 * total_price) / 100) - total_price);
   printf("          Additional GST :-\t %.2f\n", gst);
   printf("          -------------------------------\n");
   printf("           Total Price :-\t %.2f\n", gst + total_price);
   printf("          -------------------------------\n");
}

struct node *deleteList(struct node *head)
{
   if (head == NULL)
   {
      return NULL;
   }
   else
   {
      struct node *temp = head;
      while (temp->next != 0)
      {
         temp = temp->next;
         free(temp->prev);
      }
      free(temp);
      head = NULL;
   }

   return head;
}

void Employee_Details()
{
   printf("-----------------------------------------------------------------------------------------------------\n");
   printf("\nSr.No\t\t\tPost\t\t\tName\t\t\tSalary\n");
   printf("  1.\t\t\tManager\t\t\tAjay Suneju\t\t150000\n");
   printf("  2.\t\t\tChef\t\t\tPankaj Patel\t\t70000\n");
   printf("  3.\t\t\tWaiter\t\t\tRam Lale\t\t45000\n");
   printf("  4.\t\t\tWaiter\t\t\tBabu Lal\t\t45000\n");
   printf("  5.\t\t\tWaiter\t\t\tSham Lal\t\t45000\n");
   printf("  6.\t\t\tWaiter\t\t\tRocky Bhaiya\t\t45000\n");
   printf("  7.\t\t\tWaiter\t\t\tBabu Bhaiya\t\t45000\n");
   printf("  8.\t\t\tWaiter\t\t\tRaju Kataria\t\t45000\n");
   printf("  9.\t\t\tWatchman\t\tRaj Suru\t\t45000\n");
   printf("-----------------------------------------------------------------------------------------------------\n");
}

void Owner()
{
   printf("\n----------------------------------------------\n");
   printf("          OWNER DESK\n");
   printf("----------------------------------------------\n");
   while (1)
   {
      printf("\n          1. Employee Details\n");
      printf("          2. Today's Sales and other details\n");
      printf("          3. Customer's Details\n");
      printf("          4. Monthly Details\n");
      printf("          5. Search Data by day\n");
      printf("          6. Back to Main Menu\n");
      printf("          Enter Your Choice : ");
      int opt;
      scanf("%d", &opt);

      switch (opt)
      {
      case 1:
         Employee_Details();
         break;

      case 2:

         printf("\n======================= Total Orders =======================\n");
         totalsalesfile(head_s);
         displayOrder(head_s);
         break;

      case 3:
         Display_Customer_Details();
         break;

      case 4:
         Monthly_Details();
         break;

      case 5:
         Search_By_Date();
      case 6:
         return;

      default:
         printf("\n          Wrong Input !! PLease choose valid option\n");
         break;
      }
   }
}

void Manager()
{
   printf("\n----------------------------------------------\n");
   printf("          MANAGER DESK\n");
   printf("----------------------------------------------\n");
   while (1)
   {
      printf("\n          1. View total orders\n");
      printf("          2. Add new food items in the menu card\n");
      printf("          3. Delete food items from the menu card\n");
      printf("          4. Display menu card\n");
      printf("          5. Back To Main Menu \n\n");
      printf("          Enter Your Choice : ");

      int opt;
      scanf("%d", &opt);

      if (opt == 5)
         break;

      switch (opt)
      {
      case 1:
         printf("\n======================= Total Orders =======================\n");

         displayOrder(head_s);
         break;
      case 2:

         printf("\n          Enter Sr.No of the food item: ");
         int num, flag = 0;
         char name[50];
         float price;
         scanf("%d", &num);

         struct node *temp = heada;

         while (temp != NULL)
         {
            if (temp->d == num)
            {
               printf("\n         This food item already exists in menu card!!\n\n");
               flag = 1;
               break;
            }
            temp = temp->next;
         }

         if (flag == 1)
            break;

         printf("          Enter name of food item: ");
         scanf("%s", name);
         printf("          Enter price: ");
         scanf("%f", &price);
         heada = createmenu(heada, num, name, price);

         FILE *fp;
         fp = fopen("Menu.txt", "a");
         if (fp == NULL)
            printf("\nError");
         else
            fprintf(fp, "%d \t%s \t%f\n", num, name, price);
         printf("\n          New food item has been added to the menu card!!\n\n");
         fclose(fp);
         break;
      case 3:
         if (deleteMenu())
         {
            printf("\n======================= Updated menu card =======================\n");
            displayMenu(heada);
         }
         else
            printf("\n          Food item with given Sr.No doesn't available!!\n\n");

         break;
      case 4:
         printf("\n======================== Order menu ========================\n");
         displayMenu(heada);
         break;

      default:
         printf("\n          Wrong Input !! PLease choose valid option\n");
         break;
      }
   }
}

void CreateCustomer()
{
   char n[50], g;
   int a;
   printf("\n          Enter your Good Name please....: ");
   scanf("%s", n);
   printf("\n          Male or Female (M/F) ");
   scanf(" %c", &g);
   printf("\n          Enter your age: ");
   scanf("%d", &a);
   if (g == 'M')
      Male++;
   else
      Female++;
   if (a > 60)
      SixtyPlus++;
   else if (a > 40)
      FourtyPlus++;
   else
      UnderFouty++;
   strcpy(C[Customer_No].Name, n);
   C[Customer_No].gender = g;
   C[Customer_No].age = a;
   Customer_No++;
}

void Monthly_Details()
{
   FILE *f_p;
   f_p = fopen("MonthlyDetails.txt", "r");
   float ts = 0.0;
   int cno = 0, m = 0, f = 0, uf = 0, fp = 0, sp = 0;
   char buffer[100];
   int c = getc(f_p);
   if (c == EOF)
   {
      fclose(f_p);
      FILE *ft;
      ft = fopen("MonthlyDetails.txt", "w");
      fprintf(f_p, "Total Sales\tTotal Customer\tMale\tFemale\tUnder 40 age\t40-60 age\t60+ age\n");
      fprintf(ft, "%.1f\t\t%d\t\t%d\t%d\t\t%d\t\t%d\t\t%d\n", (ts + total_sales), (cno + Customer_No), (m + Male), (f + Female), (uf + UnderFouty), (fp + FourtyPlus), (sp + SixtyPlus));

      printf("\n\nTotal Sales\tTotal Customer\tMale\tFemale\tUnder 40 age\t40-60 age\t60+ age\n");
      printf("%.1f\t\t%d\t\t%d\t%d\t%d\t\t%d\t\t%d\n", (ts + total_sales), (cno + Customer_No), (m + Male), (f + Female), (uf + UnderFouty), (fp + FourtyPlus), (sp + SixtyPlus));
      fclose(ft);
      return;
   }
   while (getc(f_p) != '\n')
      ;
   fscanf(f_p, "%f %d %d %d %d %d %d", &ts, &cno, &m, &f, &uf, &fp, &sp);

   fclose(f_p);
   FILE *ft;
   ft = fopen("MonthlyDetails.txt", "w");
   fprintf(f_p, "Total Sales\tTotal Customer\tMale\tFemale\tUnder 40 age\t40-60 age\t60+ age\n");
   fprintf(ft, "%.1f\t\t%d\t\t%d\t%d\t\t%d\t\t%d\t\t%d\n", (ts + total_sales), (cno + Customer_No), (m + Male), (f + Female), (uf + UnderFouty), (fp + FourtyPlus), (sp + SixtyPlus));

   printf("\n\nTotal Sales\tTotal Customer\tMale\tFemale\tUnder 40 age\t40-60 age\t60+ age\n");
   printf("%.1f\t\t%d\t\t%d\t%d\t%d\t\t%d\t\t%d\n", (ts + total_sales), (cno + Customer_No), (m + Male), (f + Female), (uf + UnderFouty), (fp + FourtyPlus), (sp + SixtyPlus));
   fclose(ft);
}

void Search_By_Date()
{
   char date[11];
   printf("Enter the date (dd/mm/yyyy) : \n");
   scanf("%s",date);
   FILE *fp;
   char line[1000];
   char line2[1000];
   fp = fopen("Sales.txt", "r");
   int flag = 0;

   while (!feof(fp))
   {
      fgets(line, 11, fp);
      // printf("%s",line);
      int find = strcmp(line, date);
      if (find == 0)
      {
         while(!feof(fp))
         {
            fgets(line2, 1000, fp);
            int a = strlen(line2);
            if(a==11){
               flag = 1;
               break;
            }
            printf("%s",line2);
         }
         if(flag == 1)  break;
      }
   }
}
void Display_Customer_Details()
{
   printf("\n======================== Customer's Details ========================\n");
   printf("\nSr.No\tName\t\tGender\tAge");
   for (int i = 0; i < Customer_No; i++)
   {
      printf("\n%d\t%s\t\t%c\t%d", i + 1, C[i].Name, C[i].gender, C[i].age);
   }
   printf("\n\nTotal Customer\t\tMale\t\tFemale\t\tUnder 40 age\t\t40-60 age\t\t60+ age\n");
   printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", Customer_No, Male, Female, UnderFouty, FourtyPlus, SixtyPlus);
}

void customer()
{
   int flag = 0, j = 1;
   char ch, l;
   printf("\n----------------------------------------------\n");
   printf("              CUSTOMER DESK\n");
   printf("----------------------------------------------\n");
   int opt;
   CreateCustomer();
   do
   {
      printf("\n          1. Give order\n");
      printf("          2. View ordered food items\n");
      printf("          3. Cancel a food item from order\n");
      printf("          4. Display final bill\n");
      printf("          5. Back To Main Menu \n\n");
      printf("          Enter Your Choice : ");
      scanf("%d", &opt);

      switch (opt)
      {
      case 1:
         do
         {
            displayMenu(heada);
            printf("\n          Enter Sr.No of food item which you want to order: ");
            int n;
            scanf("%d", &n);
            printf("          Enter quantity: ");
            int quantity;
            scanf("%d", &quantity);
            headc = createorder(headc, n, quantity);
            printf("          Do you want to continue your order (y/n) : ");
            scanf(" %c", &l);
         } while (l != 'n');
         break;
      case 2:
         printf("\n========================== Your Order =========================\n");
         displayOrder(headc);
         break;
      case 3:
         if (deleteOrder())
         {
            printf("\n====================== Your Updated order ========================\n");
            displayOrder(headc);
         }
         else
            printf("\n          Food item with given Sr.No doesn't available!!\n");
         break;
      case 4:
         calculatetotsales();
         printf("\n=========================== Final Bill ================================\n");
         displaybill();
         headc = deleteList(headc);
         printf("\n          Press any key to return to main menu:");
         fflush(stdin);
         ch = fgetc(stdin);
         flag = 1;
         break;
      case 5:
         printf("Thank you for visiting us! ");
         return;
      default:
         printf("\n          Wrong Input !! PLease choose valid option\n");
         break;
      }
      if (flag == 1)
         break;
   } while (opt != 5);
}
