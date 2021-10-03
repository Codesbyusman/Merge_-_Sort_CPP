#include <iostream>

using namespace std;

//function prototypes
//will allocate memory to the arrays that user will made
int *allocateMemory_foroArray(int *, const int);

//for taking data and allocating the memory to arrays
void populate_allocate_arrays(int **, int *, const int);

//for entering the data
void enterData(int *, const int);

//for displaying the array
void showArray(int *, const int);

//to merge and sort the arrays
int *mergeSort(int **, int *, const int, int &);

//to check for the duplicate
bool duplicateCheck(int *, int, const int);

void sortNew(int *, const int);

int main()
{

    int a = 0, i = 0;

    //to store the N numbrs of array that user says
    int arraysNo = 0;

    //to store number of final size after excluding duplicates
    int finalSize = 0;

    //the main parent pointer that will make the array of pointers to make the respective arrays
    int **nArrays = NULL;

    //to store the size of arrays --- each index will have size of the n arrays
    int *arraySizes = NULL;

    //for the final sorted merged array
    int *mergedSorted_Array = NULL;

    cout << "\n\n\t\t ::::::::::::: Sorting and merging :::::::::::::" << endl
         << endl;

    a = 0;

    do
    {
        if (a == 0)
        {
            cout << "\n\t\t Enter The number Of arrays you want to made : ";
            cin >> arraysNo;
        }
        else //for giving error message
        {

            cout << "\n\t\t\t ::::::::::: Invalid input :::::::::::" << endl;

            cout << "\n\t\t Enter The number Of arrays you want to made : ";
            cin >> arraysNo;
        }

        a++;

    } while (!(arraysNo > 0)); //validating the size to be greater than 0

    //making pointers array that will hold the arrays ---- according to user need
    //will hold arrays of pointer --- to make arrays dynamicallay according to the user
    nArrays = new int *[arraysNo];

    //will make the array of n size to store n sizes of arrays
    arraySizes = new int[arraysNo];

    //now for asking for the size of individual arrays
    //will allocate memory and take the input for the inputs, also will also populate the size arrays
    populate_allocate_arrays(nArrays, arraySizes, arraysNo);

    cout << endl
         << endl;

    cout << "\n\t\t\t :::::::::: Entered Arrays ::::::::::" << endl
         << endl
         << endl;

    //for printing the entered arrays
    for (i = 0; i < arraysNo; i++)
    {
        cout << "Array " << i + 1 << " : ";
        showArray(nArrays[i], arraySizes[i]);
        cout << endl;
    }

    //assiging the memory --- pointer ---- that is returning from the function
    mergedSorted_Array = mergeSort(nArrays, arraySizes, arraysNo, finalSize);

    //showing the array the final size is calculate by the function
    cout << "\n\n\n Sorted & Merged Array : ";
    showArray(mergedSorted_Array, finalSize);
    cout << endl
         << endl
         << endl;

    //deleting the memory
    for(int i = 0 ; i<arraysNo ; i++)
    {
        delete[] nArrays[i];
    }

    delete[] nArrays;

    delete[] arraySizes;
    delete[] mergedSorted_Array;

    nArrays = NULL;
    arraySizes = NULL;
    mergedSorted_Array = NULL; 

    return 0;
}

//for the allocation of the memory
int *allocate_memory_for_array(int *A, const int s)
{

    A = new int[s];
    return A;
}

//for taking data and allocating the memory to arrays
void populate_allocate_arrays(int **baseArray, int *sizes, const int s)
{

    int a = 0;

    //to store the size of each arrays
    int arraySize = 0;

    //iterating for the whole pointer array because user want to have that much arrrays
    for (int i = 0; i < s; i++)
    {

        cout << "\n\n\t\t\t ::::::::::: Array " << i + 1 << " ::::::::::: " << endl
             << endl;
        //now asking for the size of individual arrays
        a = 0;
        do
        {
            if (a == 0)
            {
                cout << "\n\t\t Enter the size of Array " << i + 1 << " : ";
                cin >> arraySize;
            }
            else //for giving error message
            {

                cout << "\n\t\t\t ::::::::::: Invalid size :::::::::::" << endl;

                cout << "\n\t\t Enter again the size of Array " << i + 1 << " : ";
                cin >> arraySize;
            }

            a++;

        } while (!(arraySize > 0)); //validating the size to be greater than 0

        //will allocate memory for the array
        baseArray[i] = allocate_memory_for_array(baseArray[i], arraySize);

        //now calling the function to enter data
        enterData(baseArray[i], arraySize);

        //for every iteration the size will be obtained saving it in the size array ---- parallel
        //for later use
        sizes[i] = arraySize;
    }
}

//for taking the data from the user
void enterData(int *A, const int s)
{

    int i = 0, a = 0;

    //the temporary variable to store the value for temporary to check whether the entery is valid or not
    int temp = 0;

    cout << "\n\t\t\t :::::::::: Enter the values in ascending order ::::::::::" << endl
         << endl
         << endl;

    cout << "\t\t Enter Value of Element " << i + 1 << " at index " << i << " : ";
    cin >> A[0];

    //first will have no validation sp taking that as a direct input outside loop
    for (i = 1; i < s; i++)
    {
        a = 0;

        do
        {

            if (a == 0)
            {
                cout << "\t\t Enter Value of Element " << i + 1 << " at index " << i << " : ";
                cin >> temp;
            }
            else //for error display
            {

                cout << "\n\t\t\t\t ::::::::: Invalid Input :::::::::" << endl
                     << endl;

                cout << "\n\t\t\t ------- Enter the elements in ascending order ------- " << endl
                     << endl;
                ;
                cout << "\t\t Enter Value of Element " << i + 1 << " at index again " << i << " : ";
                cin >> temp;
            }

            a++;

        } while (!(A[i - 1] <= temp)); //validating the ascending order -- same will be accepted

        //saving temp on the desired value after ensuring is in ascending order
        A[i] = temp;
    }
}

//for displaying the array
void showArray(int *A, const int s)
{
    int i = 0;

    cout << " {  ";
    for (i = 0; i < s; i++)
    {
        cout << A[i] << "  ";
    }

    cout << "} " << endl;
}

//to merge and sort the arrays
//and will return an array the final that will be sorted in decending as in example
int *mergeSort(int **nArrays, int *sizes, const int s, int &finalS)
{

    int i = 0, j = 0, k = 0;

    //to store the number of elements --- the summ of all
    int elements = 0;

    //to store temporarily
    int temp = 0;

    //to find the duplicates
    int duplicate = 0;

    //the intermediate array that will be the second last step to the final one
    int *interMidate_Array = NULL;

    //the final array to store the desired array
    int *finalArray = NULL;

    //for calculating the whole elements of all arrays
    for (i = 0; i < s; i++)
    {
        elements += sizes[i];
    }

    //making the intermediate array of total elment size
    interMidate_Array = new int[elements];

    k = 0;

    //for accessing the all arrays
    for (i = 0; i < s; i++)
    {

        //for acceessing arrays all elements
        for (j = 0; j < sizes[i]; j++)
        {

            //function returns if find duplicate thus don't store the value
            if (!duplicateCheck(interMidate_Array, nArrays[i][j], k))
            {
                interMidate_Array[k] = nArrays[i][j];
                k++; //increase the k value for next
            }
            else
            {
                duplicate++; //there is duplicate so incriment
            }

            //will sort the new array having a new element that is added to it
            sortNew(interMidate_Array, k);
        }
    }

    //the final size excluding the duplicates
    finalS = elements - duplicate;

    //now assigning the intermediate to the final array of size excluding duplicates
    finalArray = new int[finalS];

    //copying the intermediate to the final array
    for (i = 0; i < finalS; i++)
    {
        finalArray[i] = interMidate_Array[i];
    }

    //deleting the memory of intermediate
    delete[] interMidate_Array;

    //returning the final array
    return finalArray;
}

bool duplicateCheck(int *A, int check, const int s)
{
    int i = 0;

    //will go through whole array to check the duplicate
    //for having no element the s will be 0 so loop will not execute
    for (i = 0; i < s; i++)
    {
        //duplicate found
        if (check == A[i])
        {
            return 1; //there is duplicate
        }
    }

    return 0; //there was no duplicte
}

//will sort the array that is created by the addition of new one
void sortNew(int *nA, const int s)
{
    int i = 0, j = 0;

    //for swaping
    int swap = 0;

    //to check wther the swaping in iteration was done
    bool swapCheck = false;

    //will go through the arrays n-1 times because at last will be sorted
    for (i = 0; i < s - 1; i++)
    {
        //making 0 in each iteration
        swapCheck = false;

        //will be checking and swaping the elements for n-1-i because in each iteration the ---i--- that much
        //elemnts will be swaped.
        for (j = 0; j < s - 1 - i; j++)
        {
            //if the previous is less than the the next swap
            if (nA[j] < nA[j + 1])
            {
                //swaping the elements
                swap = nA[j];
                nA[j] = nA[j + 1];
                nA[j + 1] = swap;

                //swping is done
                swapCheck = true;
            }
        }

        //if no swaping was done mean the arrray was stored thus break ... don't check further
        if (swapCheck == false)
        {
            break;
        }
    }
}
