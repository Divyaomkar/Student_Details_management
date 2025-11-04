#include <stdio.h>
#include <stdlib.h>

int n;
FILE *fp,*ftmp;

void dataEntering();
void dataReading();
void dataDeleting();

struct student
{
    int rollNum;
    char name[20];
    int m1;
    int m2;
    int total;
    float average;
};

int main()
{
    int choice=0;
    while(1)
    {
        printf("1.Add details\n");
        printf("2.Display data\n");
        printf("3.Delete data\n");
        printf("4.Exit\n");
        printf("Enter the choice to operate : ");
        scanf("%d",&choice);

        switch(choice)
        {

            case 1:dataEntering();break;

            case 2:
                {
                    printf("\nNOTE : \nData displays Roll number, Name, Marks in first Subject, Marks in second Subject, Total marks and Average of marks respectively\n");
                    dataReading();
                };break;

            case 3:dataDeleting();break;

            case 4: printf("Exit successfully\n"); exit(1);break;

            default: printf("You entered wrong choice,please try again\n");
        }
        printf("\n\n");
    }

    return 0;
}

void dataEntering()
{
    struct student s[100];
    printf("\nEnter the number of students to add details\n");
    scanf("%d",&n);

    printf("Enter the details of students\n");
    //data reading from user and write to file
     fp = fopen("StudentFile.txt","a");
    for (int i=0;i<n;i++)
    {
        printf("\nRoll number : ");
        scanf("%d",&s[i].rollNum);
        getchar();
        printf("Name : ");
        scanf("%[^\n]",s[i].name);
        printf("Marks in first subject : ");
        scanf("%d",&s[i].m1);
        printf("Marks in second subject : ");
        scanf("%d",&s[i].m2);

        //calculating total and average of marks
        s[i].total = s[i].m1 + s[i].m2;
        s[i].average = (s[i].total)/2.0;

        fprintf(fp,"%d\t%s\t%d\t%d\t%d\t%f\n",s[i].rollNum,s[i].name,s[i].m1,s[i].m2,s[i].total,s[i].average);
    }
    fclose(fp);
    printf("\nData entered successfully\n");

}

void dataReading()
{
    struct student s[100];
    int i = 0;

    printf("\nStudents Details:\n----------------------\n");

    //read from file
    fp = fopen("StudentFile.txt","r");
    while((fscanf(fp,"%d %s %d %d %d %f",&s[i].rollNum,s[i].name,&s[i].m1,&s[i].m2,&s[i].total,&s[i].average)) == 6)
    {
     printf("%d\t%s\t%d\t%d\t%d\t%f\n",s[i].rollNum,s[i].name,s[i].m1,s[i].m2,s[i].total,s[i].average);
     i++;
    }
    fclose(fp);
}

void dataDeleting()
{
    struct student s[100];
    int dRollNum,found = 0,i=0;
    printf("Enter the roll number of the student to delete details : ");
    scanf("%d",&dRollNum);


    //creating Temporary files
    ftmp = fopen("tempfile.txt","w");
    fp = fopen("StudentFile.txt","r");
    //decision compare and copy to temp file
    while((fscanf(fp,"%d %s %d %d %d %f",&s[i].rollNum,s[i].name,&s[i].m1,&s[i].m2,&s[i].total,&s[i].average)) == 6)
    {
        if(dRollNum == (s[i].rollNum))
            found = 1;
        else
        {
            fprintf(ftmp,"%d\t%s\t%d\t%d\t%d\t%f\n",s[i].rollNum,s[i].name,s[i].m1,s[i].m2,s[i].total,s[i].average);
        }
        i++;
    }
    fclose(ftmp);
    fclose(fp);

    if(found)
    {

        //remove old file and rename the temp file as <old file>
        remove("StudentFile.txt");
        rename("tempfile.txt","StudentFile.txt");
        printf("\nData deleted successfully\n");
        printf("\nAfter deleting the data\n");
        printf("\n---------------------------\n");
        ftmp = fopen("StudentFile.txt","r");
        while((fscanf(ftmp,"%d %s %d %d %d %f",&s[i].rollNum,s[i].name,&s[i].m1,&s[i].m2,&s[i].total,&s[i].average)) == 6)
        {
            printf("%d\t%s\t%d\t%d\t%d\t%f\n",s[i].rollNum,s[i].name,s[i].m1,s[i].m2,s[i].total,s[i].average);
            i++;
        }
        fclose(ftmp);
    }
    else
    {
        printf("\nNo student found with Roll number %d",dRollNum);
    }

}
