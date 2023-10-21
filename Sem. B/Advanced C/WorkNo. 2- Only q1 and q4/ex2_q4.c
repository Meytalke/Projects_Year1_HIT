// Course: Advanced C programming
// exercise 2, question 4
// file name: ex2_q3.c

// --------------------------- //
//
//	Assigned by:
//		Student1_Full_Name #ID
//		Student2_Full_Name #ID
//
// --------------------------- //

// --------------------------------------- //
// Include and definition package section:
// --------------------------------------- //
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define scanf_s scanf
#define PATH1 "c:\\temp\\file1.txt"
#define PATH2 "c:\\temp\\file2.txt"
#define PATH3 "c:\\temp\\file3.txt"

// --------------------------------------- //
// Functions declration section:
// --------------------------------------- //

int memoryReport(char* filename);
int ArrayHandling(char*, int, int[], char* []);
int removeSpaces(char* str);
char* returnNameOfArray(char* str);
char* getDataType(char*,char*,char*);

// --------------------------------------- //
// Main section:
// --------------------------------------- //
int main()
{
    int total1, total2, total3;

    // Start Program:
    printf("Start Program\n");

    // call functions:
    total1 = memoryReport(PATH1);
    total2 = memoryReport(PATH2);
    total3 = memoryReport(PATH3);
    // write output:
    printf("Output:\n");
    printf("First file required %d bytes\n", total1);
    printf("Second file required %d bytes\n", total2);
    printf("Third file required %d bytes\n", total3);

    return 0;
}
// 
// 
// --------------------------- //


/// <summary>
/// The function receives a pointer to a string, representing a path to a file.
/// The function output all varibles declerations and their size in byte.
/// </summary>
/// <param>char *filename - valid path to a file</param>
/// <returns>total bytes required</returns>
int memoryReport(char* filename)
{
    FILE* fp = NULL;
    char line[255], c, * ptr = NULL, * token = NULL, * token2 = NULL, * token3 = NULL, * array_name = NULL, * last=NULL, * PointerOrLongLong = NULL;
    int totalMemory = 0,num, dataTypeIndex, numBytes, numVars, i, flag = 0, flagIsPointerOrLongLong, asPointer = 0,f = 0;

    // Define mapping of data types to their sizes in bytes
    int dataTypesSize[] = { sizeof(char), sizeof(short), sizeof(int), sizeof(unsigned int), sizeof(long), sizeof(long long), sizeof(float), sizeof(double) };
    char* dataTypes[] = { "char", "short", "int", "unsigned int", "long", "long long", "float", "double" };

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Failed to open file\n");
        return -1;
    }

    printf("Function print:\n");

    // Read file line by line
    while (fgets(line, sizeof(line), fp))
    {
        flagIsPointerOrLongLong = 0;
        if (strchr(line, ' '))
        {
            flagIsPointerOrLongLong = removeSpaces(line);
        }
        token = strtok(line, " ;\t\n");
        dataTypeIndex = -1;
        numBytes = 0;
        numVars = 0;

        char tttt1[100] = { 0 };
        char tttt2[100] = { 0 };
        char* tttt3 = { 0 };
        if (tttt3 = getDataType(token, tttt1, tttt2))
        {
            asPointer = 1;
            token = tttt3;
        }
        // Find data type in token
        for (i = 0; i < 8; i++)
        {
            if (asPointer == 1)
            {
                if (strcmp(tttt1, dataTypes[i]) == 0)
                {
                    dataTypeIndex = i;
                    break;
                }
            }
            if (strcmp(token, dataTypes[i]) == 0)
            {
                dataTypeIndex = i;
                break;
            }
            if (flagIsPointerOrLongLong == 1 || flagIsPointerOrLongLong == 3)
            {
                dataTypeIndex = 5;
                break;
            }
            if (strcmp(token, "unsigned") == 0)
            {

                token2 = "int";
                strcat(token, " ");
                strcat(token, token2);
                if (strcmp(token, dataTypes[3]) == 0)
                {
                    dataTypeIndex = 3;
                    break;
                }
            }
        }
        char* forNow;
        if (forNow = strchr(token, '$'))
        {
            token = forNow;
            token++;
        }
        ptr = strchr(line, '*');
        if (ptr != NULL)
        {
            *ptr = '\0';
        }

        // If data type was found, count number of variables and calculate memory usage
        if (dataTypeIndex != -1)
        {

            flag = 0;
            
            while (token != NULL)
            {
                
                numVars++;
                if (asPointer == 1)
                {
                    token = strtok(tttt3, " ,;\t\n");
                }
                else
                {
                    token = strtok(NULL, " ,;\t\n$");
                }
                if (token != NULL)
                {
                    PointerOrLongLong = strchr(token, '*');
                    if (PointerOrLongLong)
                    {
                        if (PointerOrLongLong && dataTypeIndex == 5)
                        {
                            flagIsPointerOrLongLong = 3;
                        }
                        else if (PointerOrLongLong && dataTypeIndex != 5)
                        {
                            flagIsPointerOrLongLong = 2;
                        }
                    }
                    else if (asPointer == 1)
                    {
                         PointerOrLongLong = 2;
                    }
                    else
                    {
                        flagIsPointerOrLongLong = 0;
                    }
                    c = token[0];
                }
                else
                {
                    break;
                }

                ptr = strchr(token, '[');
                if (dataTypeIndex == 5 && flag == 0)// long
                {
                    token = token + 4;
                    flag = 1;
                }
                if (ptr != NULL)
                {        
                    num = ArrayHandling(token, dataTypeIndex, dataTypesSize, dataTypes);
                    array_name = returnNameOfArray(token);
                    if (last != NULL && strcmp(last, array_name) == 0  )
                    {
                        break;
                    }
                    else
                    {
                        if (asPointer == 1 || c=='*')
                        {
                            f = 1;
                            token = strtok(tttt3, " ,;\t\n");
                            num = (num / dataTypesSize[dataTypeIndex]) * 4;
                            last = array_name;
                            
                        }
                    }
                    printf("%s requires %d bytes\n", array_name, num);
                    totalMemory += num;
                }
                else
                {
                    if (c == '*' || flagIsPointerOrLongLong == 3 || flagIsPointerOrLongLong == 2)
                    {
                        printf("%s requires %d bytes\n", token + 1, dataTypesSize[dataTypeIndex] * 4);
                        totalMemory += dataTypesSize[dataTypeIndex] * 4;
                    }
                    else
                    {
                        printf("%s requires %d bytes\n", token, dataTypesSize[dataTypeIndex]);
                        totalMemory += dataTypesSize[dataTypeIndex];
                    }
                }
            }
        }
    }
    fclose(fp);
    printf("Function return: %d\n", totalMemory);
    printf("\n\n");
    return totalMemory;
}
int ArrayHandling(char* token, int dataTypeIndex, int dataTypesSize[], char* dataTypes[]) {
    int numBytes = 1;
    char* ptr = strchr(token, '[');
    if (ptr == NULL) {
        numBytes = 1;
    }
    else {
        while (ptr != NULL)
        {
            int num = 0;
            char* c = ptr + 1;
            while (isdigit(*c))
            {
                num = num * 10 + (*c - '0');
                c++;
            }
            numBytes *= num;
            ptr = strchr(c, '[');
        }
        numBytes *= dataTypesSize[dataTypeIndex];
    }
    return numBytes;
}
char* returnNameOfArray(char* str)
{
    int i;
    char NewName[100] = { 0 };
    for (i = 0; str[i] != '[' && str[i] != '\0'; i++)
    {
        NewName[i] = str[i];
    }
    NewName[i] = '\0';
    return strdup(NewName);
}
int removeSpaces(char* str)
{
    int i = 0, j = 0, flag = 0;
    char* temp, newStr[100] = { 0 };
    if (temp = strchr(str, '*'))
    {
        flag = 2;// רק פוינטר
    }
    while (str[i])
    {
        if (str[i] == '[')
        {
            break;
        }
        if (str[i] != ' ')
        {
            str[j++] = str[i];
        }
        else
        {

            str[j++] = str[i];
            break;
        }
        i++;
    }
    if (strstr(str, "long long"))
    {
        flag = 1;
        if (strstr(str, "long long *"))
        {
            flag = 3;
        }
    }
    while (str[i])
    {
        if (str[i] != ' ')
        {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
    return flag;
}
char* getDataType(char* str, char* temp, char* temp2)
{
    int i = 0;
    char* ptr = strchr(str, '*');
    if (ptr != NULL)
    {
        *ptr = '$'; // חוסם על המחרוזת בנקודה שבה מופיע התו '*'
        char* dataType = strtok(str, " "); // מחזיר את המילה הראשונה מהמחרוזת החדשה
        while (dataType[i] != '$')
        {
            temp[i] = dataType[i];
            temp2[i] = dataType[i];
            i++;
        }
        temp2[i++] = ',';
        while (dataType[i])
        {
            if (dataType[i] == '$')
            {
                continue;
            }
            else
            {
                temp2[i] = dataType[i];
            }
            i++;
        }
        *ptr = ',';
        temp[i] = '\0';
        temp2[i] = '\0';
        dataType = strchr(dataType, ',');
        return dataType;
    }
    else
    {
        return NULL;
    }
}


// --------------------------- //