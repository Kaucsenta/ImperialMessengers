#include <iostream>
//#define Example

const int MaxNumberOfCities = 100;
const int MinNumberOfCities = 1;
const unsigned int UnreachableReplaceNumber = 0xFFFF;

void ReadInMatrix(unsigned int NumberOfCities, unsigned int ** CityMatrix)
{
    /*prepare the matrix */
    for(int i = 0; i<NumberOfCities; i++)
    {
        CityMatrix[i][i] = UnreachableReplaceNumber;
    }
    /*Require matrix input*/
    for(int i = 1; i<NumberOfCities; i++)
    {
        for (int j = 0; j < i; j++)
        {
            std::string input;
            unsigned int Distance;
            std::cout << i+1 << ". line "<< j+1 << ":" << std::endl;
            std::cin >> input;
            std::size_t found = input.find_first_of("xX");
            if(input.length() >0 && found!=std::string::npos)
            {
                Distance=UnreachableReplaceNumber;
            }
            else
            {
                Distance= std::stoi(input);
            }

            CityMatrix[i][j] = Distance;
            CityMatrix[j][i] = Distance;
        }
    }
}

void FindShortestPaths(unsigned int NumberOfCities, unsigned int **CityMatrix, unsigned int *DistanceList)
{
    unsigned int Previous[NumberOfCities], VisitedCityList[NumberOfCities];

    for (int i = 0; i < NumberOfCities; i++)
    {
        DistanceList[i] = CityMatrix[0][i];
        Previous[i] = 0;
        VisitedCityList[i] = 0;
    }

    DistanceList[0] = 0;
    VisitedCityList[0] = 1;
    unsigned int count = 1;
    unsigned int MinimumDistance, NextNode;
    while (count < NumberOfCities - 1)
    {
        MinimumDistance = UnreachableReplaceNumber;

        for (int i = 0; i < NumberOfCities; i++)
        {
            if (DistanceList[i] < MinimumDistance && !VisitedCityList[i])
            {
                MinimumDistance = DistanceList[i];
                NextNode = i;
            }
        }

        VisitedCityList[NextNode] = 1;
        for (int i = 0; i < NumberOfCities; i++)
        {
            if (!VisitedCityList[i])
            {
                if (MinimumDistance + CityMatrix[NextNode][i] < DistanceList[i])
                {
                    DistanceList[i] = MinimumDistance + CityMatrix[NextNode][i];
                    Previous[i] = NextNode;
                }
            }
        }
        count++;
    }
}


unsigned int FindMaximumOfShortestPaths(unsigned int NumberOfCities, const unsigned int* DistanceList)
{
    unsigned int MaximumTime = 0;
    for (int i=0; i< NumberOfCities; i++)
    {
        if(DistanceList[i] > MaximumTime)
        {
            MaximumTime = DistanceList[i];
        }
    }
    return  MaximumTime;
}

unsigned int ReadInCityNumber()
{
    unsigned int NumberOfCities;
    std::string stdinput;
    std::cout << "How many route there are between the cities?" << std::endl;
    std::cin >> stdinput;
    NumberOfCities = stoi(stdinput);
    if(NumberOfCities<MinNumberOfCities || NumberOfCities>MaxNumberOfCities)
    {
        std::cout << "Invalid number of cities, try between 1 and 100" << std::endl;
        exit(1);
    }
    return NumberOfCities;
}

int main()
{
    unsigned int** CityMatrix; /* Path time between start and target city */
    unsigned int* DistanceList; /* Shortest time path between source and target city */

    unsigned int NumberOfCities; /* number of cities */
    unsigned int MaximumTime; /* result of the task */
#ifdef Example
    /*Example input*/
    NumberOfCities = 5;
    CityMatrix = new unsigned int *[NumberOfCities];
    for (int i = 0; i < NumberOfCities; i++)
    {
        CityMatrix[i] = new unsigned int[NumberOfCities];
    }
    CityMatrix[0][0] = 0;
    CityMatrix[0][1] = 50;
    CityMatrix[0][2] = 30;
    CityMatrix[0][3] = 100;
    CityMatrix[0][4] = 10;

    CityMatrix[1][0] = 50;
    CityMatrix[1][1] = 0;
    CityMatrix[1][2] = 5;
    CityMatrix[1][3] = 20;
    CityMatrix[1][4] = 0xFFFF;

    CityMatrix[2][0] = 30;
    CityMatrix[2][1] = 6;
    CityMatrix[2][2] = 0;
    CityMatrix[2][3] = 50;
    CityMatrix[2][4] = 0xFFFF;

    CityMatrix[3][0] = 100;
    CityMatrix[3][1] = 20;
    CityMatrix[3][2] = 50;
    CityMatrix[3][3] = 0;
    CityMatrix[3][4] = 10;

    CityMatrix[4][0] = 10;
    CityMatrix[4][1] = 0xFFFF;
    CityMatrix[4][2] = 0xFFFF;
    CityMatrix[4][3] = 10;
    CityMatrix[4][4] = 0;
#else
    NumberOfCities=ReadInCityNumber();

    CityMatrix = new unsigned int *[NumberOfCities];
    for (int i = 0; i < NumberOfCities; i++)
    {
        CityMatrix[i] = new unsigned int[NumberOfCities];
    }

    ReadInMatrix(NumberOfCities, CityMatrix);
#endif
    DistanceList = new unsigned int[NumberOfCities];
    FindShortestPaths(NumberOfCities, CityMatrix, DistanceList);
    MaximumTime=FindMaximumOfShortestPaths(NumberOfCities, DistanceList);

    for(int i = 0; i < NumberOfCities; i++)
    {
        delete(CityMatrix[i]);
    }
    delete(CityMatrix);
    delete(DistanceList);
    /*Print out the message and the result*/
    std::cout << std::endl << "Daniel Bozsoki, 2022/12/11" << std::endl;
    std::cout << MaximumTime << std::endl;

    return 0;
}
