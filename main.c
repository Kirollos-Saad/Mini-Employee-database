#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct
{
    int day;
    int month;
    int year;
} Date;
typedef struct
{
    int ID;
    char First[100];
    char Last[100];
    float Salary ;
    Date DOB;
    char address[100];
    char email[100];
    char phone[100];
} Employee;

char* Serialize_emp(Employee emp)
{
    char *emp_string = malloc(10000);
    sprintf(emp_string,"%d,%s,%s,%.2f,%d-%d-%d,%s,%s,%s\n",emp.ID,emp.Last,emp.First, emp.Salary, emp.DOB.day,emp.DOB.month,emp.DOB.year,emp.address,emp.phone,emp.email);
    return emp_string;
}

Employee DeSerialize_emp(char line[])
{
    Employee emp;
    int x;
    float y;
    char* token = strtok(line,",-");
    x=atoi(token);
    emp.ID=x;
    token = strtok(NULL,",-");
    strcpy(emp.Last,token);
    token = strtok(NULL,",-");
    strcpy(emp.First,token);
    token = strtok(NULL,",-");
    y=atof(token);
    emp.Salary=y;
    token = strtok(NULL,",-");
    x=atoi(token);
    emp.DOB.day=x;
    token = strtok(NULL,",-");
    x=atoi(token);
    emp.DOB.month=x;
    token = strtok(NULL,",-");
    x=atoi(token);
    emp.DOB.year=x;
    token = strtok(NULL,",");
    strcpy(emp.address,token);
    token = strtok(NULL,",-");
    strcpy(emp.phone,token);
    token = strtok(NULL,",\n");
    strcpy(emp.email,token);
    return emp;
}

void Print_employee(Employee e)
{
    printf("\nEmployee Id: %d\n", e.ID);
    printf("Employee First Name: %s\n", e.First);
    printf("Employee Last Name: %s\n",e.Last);
    printf("Employee Salary: %f\n",e.Salary);
    printf("Employee Date of Birth : %d/%d/%d\n",e.DOB.day,e.DOB.month,e.DOB.year);
    printf("Employee Address : %s\n",e.address);
    printf("Employee Phone : %s\n",e.phone);
    printf("Employee Email : %s\n",e.email);
}
int ScanID()
{
    int x,i;
    int flag;
    char ID[10];
    while(1)
    {
        flag=0;
        printf("Enter Employee ID: ");
        scanf("%s",ID);
        for (i=0; ID[i]!='\0'; i++)
        {
            if (!isdigit(ID[i]))
            {
                flag=1;
                break;
            }
        }
        if (flag==0)
        {
            break;
        }
    }
    x=atoi(ID);
    return x;
}
float ScanSalary()
{
    int i;
    float x;
    int flag;
    char salary[20];
    while(1)
    {
        flag=0;
        printf("Enter Employee Salary: ");
        scanf("%s",salary);
        for (i=0; salary[i]!='\0'; i++)
        {
            if ((!isdigit(salary[i]))&&(salary[i]!='.'))
            {
                flag=1;
                break;
            }
        }
        if (flag==0)
        {
            break;
        }
    }
    x=atof(salary);
    return x;
}

char *ScanEmail()
{
    int flag,i,j, at_count;
    char *email =malloc(sizeof(char)*100);
    while (1)
    {
        flag=0;
        at_count=0;
        printf("Enter Employee Email: ");
        scanf("%s",email);
        for (i=0; email[i]!='\0'; i++)
        {
            if (email[i]=='@')
            {
                at_count++;
                for(j=i+1; email[j]!='\0'; j++)
                {
                    if (email[j]=='.'&& j>(i+1))
                    {
                        flag=1;
                    }
                    else if(email[j]=='@')
                    {
                        at_count++;
                    }
                }
                break ;
            }
        }
        if (flag==1&&at_count==1)
        {
            break ;
        }
    }
    return email;
}
void ScanPhone(char *e_phone)
{
    int flag,i;
    char phone[100];
    while (1)
    {
        flag =0;
        printf("Enter Employee phone number: ");
        scanf("%s",phone);
        for (i=0; phone[i]!='\0'; i++)
        {
            flag =0;
            if ((!isdigit(phone[i]))&&(phone[i]!='+'))
            {
                flag=1;
                break ;
            }
        }
        if (flag==0)
        {
            break ;
        }
    }
    strcpy(e_phone,phone);
}

void ScanBirthdate(int* e_day, int* e_month, int* e_year)
{
    char day[10], month[10], year[10];
    int i, flag;
    while(1)
    {
        flag=0;
        printf("Enter Employee Date of birth\n");
        printf("Enter day: ");
        scanf("%s",day);
        printf("Enter month: ");
        scanf("%s",month);
        printf("Enter year: ");
        scanf("%s",year);
        for(i=0; day[i]!='\0'; i++)
        {
            if(!isdigit(day[i]))
                flag =1;
        }
        for(i=0; month[i]!='\0'; i++)
        {
            if(!isdigit(month[i])) flag =1;
        }
        for(i=0; year[i]!='\0'; i++)
        {
            if(!isdigit(year[i]))
                flag =1;
        }
        if(atoi(day)>31 || atoi(month)>12 || atoi(year) > 2022)
            flag=1;
        if(atoi(day)< 1 || atoi(month)< 1 || atoi(year) < 1900)
            flag=1;

        if(flag==0)
            break;
    }
    *e_day = atoi(day);
    *e_month = atoi(month);
    *e_year = atoi(year);
}

Employee Scan_employee()
{
    Employee e;
    e.ID=ScanID();
    printf("Enter Employee First Name: ");
    scanf("%s",&e.First);
    printf("Enter Employee Last Name: ");
    scanf("%s",&e.Last);
    e.Salary=ScanSalary();
    ScanBirthdate(&e.DOB.day,&e.DOB.month,&e.DOB.year);
    printf("Enter Employee Address: ");
    getchar();
    gets(e.address);
    strcpy(e.email,ScanEmail());
    ScanPhone(e.phone);
    printf("\n\n");
    return e;
}

Employee *LOAD(char filename[],int *RC)
{
    FILE *fp=fopen (filename,"r");
    if (fp==NULL)
    {
        printf("ERROR!!!");
        exit(1);
    }
    Employee *empls=malloc(sizeof(Employee)*1000);
    char line[10000];
    int i=0;
    char *x;
    *RC=0;
    while (!feof(fp))
    {
        x=fgets(line,10000,fp);
        if(!x)
            break;
        empls[i]=DeSerialize_emp(line);
        i++;
        (*RC)++;
    }
    fclose(fp);
    return empls;
}
Employee *Add( Employee *emp_array,int *RC )
{
    int i,n;
    printf("Enter number of employees you want to add: ");
    scanf("%d",&n);
    Employee *emp_array2=malloc(sizeof(Employee)*((*RC)+n));
    for (i=0; i<(*RC); i++)
    {
        emp_array2[i]=emp_array[i];
    }
    for (i=(*RC); i<n+(*RC); i++)
    {
        printf("Enter employee %d\n",(i+1-(*RC)));
        emp_array2[i]=Scan_employee();
    }
    *RC=(*RC)+n;
    return emp_array2;
}

void Query(Employee *emp_arr,int n)
{
    int i,found = 0;
    char lastname[100];
    printf("Enter last name you want to search for:\n");
    scanf("%s",lastname);
    for(i = 0; i < n; i++)
    {
        if(strcasecmp(lastname,emp_arr[i].Last) == 0)
        {
            Print_employee(emp_arr[i]);
            found = 1;
        }
    }
    if(found == 0)
        printf("No employees found\n");
}

void Save(char filename[],Employee* emp_array, int RC)
{
    FILE *fp=fopen (filename,"w");
    if (fp==NULL)
    {
        printf("ERROR!!!");
        exit(1);
    }
    int i;
    char* emp_string;
    for(i=0; i<RC; i++)
    {
        emp_string = Serialize_emp(emp_array[i]);
        fprintf(fp,"%s",emp_string);
    }
    printf("File is Saved\n");
    fclose(fp);

}

void Modify( Employee * emp_array,int RC)
{
    int ID,i;
    printf("ID need to be modified:\n");
    ID=ScanID();
    int flag =0;
    for (i=0; i<RC; i++)
    {
        if (ID==emp_array[i].ID)
        {
            flag=1;
            printf("Enter the new information:\n");
            emp_array[i]=Scan_employee();
        }
    }
    if (flag==0)
    {
        printf("No employees with this ID.\n");
    }
}

void Delete(Employee *emp_array,int *RC)
{
    int i = 0,j = 0,RC_flag=0;
    char first[100],last[100];
    printf("Enter first name: ");
    scanf("%s",first);
    printf("Enter last name: ");
    scanf("%s",last);
    for(i = 0; i < (*RC); i++)
    {
        if(strcasecmp(emp_array[i].First,first) == 0 && strcasecmp(emp_array[i].Last,last)== 0)
        {
            *(RC) = *(RC) - 1;
            RC_flag=1;
            for(j = i; j < (*RC); j++)
            {
                emp_array[j] = emp_array[j+1];
            }
            i--;
        }
    }
    if (RC_flag==0)
    {
        printf("No employees with this name.\n");
    }
}

void SortByLName(Employee *emp_array,int RC)
{
    int i,j;
    Employee temp;
    for (i=0; i<RC-1; i++)
    {
        for (j=0; j<RC-1-i; j++)
        {
            if (strcasecmp(emp_array[j].Last,emp_array[j+1].Last)>0)
            {
                temp=emp_array[j];
                emp_array[j]=emp_array[j+1];
                emp_array[j+1]=temp;
            }
        }
    }
}

void SortByDOB(Employee *emp_array,int RC)
{
    int i,j;
    Employee temp;
    for (i=0; i<RC-1; i++)
    {
        for (j=0; j<RC-1-i; j++)
        {
            if (emp_array[j].DOB.year<emp_array[j+1].DOB.year)
            {
                temp=emp_array[j];
                emp_array[j]=emp_array[j+1];
                emp_array[j+1]=temp;
            }
            else if (emp_array[j].DOB.year==emp_array[j+1].DOB.year)
            {
                if(emp_array[j].DOB.month<emp_array[j+1].DOB.month)
                {
                    temp=emp_array[j];
                    emp_array[j]=emp_array[j+1];
                    emp_array[j+1]=temp;
                }
                else if(emp_array[j].DOB.month==emp_array[j+1].DOB.month)
                {
                    if (emp_array[j].DOB.day<emp_array[j+1].DOB.day)
                    {
                        temp=emp_array[j];
                        emp_array[j]=emp_array[j+1];
                        emp_array[j+1]=temp;
                    }
                }
            }

        }
    }
}

void SortBySalary(Employee *emp_array,int RC)
{
    int i,j;
    Employee temp;
    for (i=0; i<RC-1; i++)
    {
        for (j=0; j<RC-1-i; j++)
        {
            if (emp_array[j].Salary>emp_array[j+1].Salary)
            {
                temp=emp_array[j];
                emp_array[j]=emp_array[j+1];
                emp_array[j+1]=temp;
            }
        }
    }
}

void Sort(Employee *emp_array,int RC)
{
    int x,i;
    while(1)
    {
        printf("Enter sort way:\n");
        printf("1.Sort by last name.\n");
        printf("2.Sort by date of birth.\n");
        printf("3.Sort by salary.\n");
        printf("Type here: ");
        scanf("%d",&x);
        if(x==1)
        {
            SortByLName(emp_array,RC);
        }
        else if (x==2)
        {
            SortByDOB(emp_array,RC);
        }
        else if (x==3)
        {
            SortBySalary(emp_array,RC);
        }
        else
        {
            printf("Wrong number\nPlease enter again:\n");
            continue;
        }
        for (i=0; i<RC; i++)
        {
            Print_employee(emp_array[i]);
        }
        break;
    }

}

void Quit(char filename[],Employee* emp_array, int RC,int change)
{
    int i,x;
    if (change ==0)
    {
        exit(0);
    }
    while (1)
    {
        printf("Enter quit way:\n");
        printf("1.Save.\n");
        printf("2.Don't Save.\n");
        printf("3.Cancel.\n");
        printf("Type here: ");
        scanf("%d",&x);
        if (x==1)
        {
            Save("Company.txt",emp_array,RC);
            exit(0);
        }
        else if (x==2)
        {
            exit(0);
        }
        else if (x==3)
        {
            break;
        }
        else
        {
            printf("Wrong number\nPlease enter again:\n");
        }
    }
}

int main()
{
    int i,RC,x,change=0;
    Employee *emp_array;
    emp_array=LOAD("Company.txt",&RC);
    printf("Hello to Company System.");
    while (1)
    {
        printf("\nEnter what you need:\n");
        printf("1.Query.\n");
        printf("2.Add.\n");
        printf("3.Delete.\n");
        printf("4.Modify.\n");
        printf("5.Print(Sort).\n");
        printf("6.Save.\n");
        printf("7.Exit.\n");
        printf("Type here: ");
        scanf("%d",&x);
        if(x==1)
            Query(emp_array,RC);
        else if(x==2)
        {
            emp_array=Add(emp_array,&RC);
            change=1;
        }
        else if(x==3)
        {
            Delete(emp_array,&RC);
            change=1;
        }
        else if (x==4)
        {
            Modify(emp_array,RC);
            change=1;
        }
        else if (x==5)
        {
            Sort(emp_array,RC);
            change=1;
        }
        else if (x==6)
        {
            Save("Company.txt",emp_array,RC);
            change=0;
        }
        else if(x==7)
            Quit("Company.txt",emp_array,RC,change);
        else
            printf("Wrong number\nPlease enter again:\n");
    }
    return 0;
}
