#include "CSVEditor.h"
#include <iostream>
/// <summary>
/// Reads and converts CSV-files into a string vector. Hopefully with zero loss.
/// </summary>
/// <param name="filePath">The file path to the csv file.</param>
/// <returns>A vector of strings.</returns>
std::vector<std::string> CSVEditor::ReadFile(const std::string& filePath) //Reads and converts file into a string vector
{
    std::vector<std::string> fileReadings = std::vector<std::string>();

    //Return empty if wrong file type was inserted.
    //std::cout << filePath.substr(filePath.length() - 4, 4) << std::endl;
    if (filePath.substr(filePath.length() - 4, 4) != ".csv")
        return fileReadings;

    std::fstream file = std::fstream(filePath);
    std::string tempString ="";
    std::string tempCellString = "";
    while (std::getline(file, tempString)) //Gets a line in the csv file and then splits it upp into string elements
    {
        //std::cout<<"ts: " << tempString << std::endl;//Debug controll
        while (tempString.find(",") != tempString.npos)
        {
            tempCellString = tempString.substr(0, tempString.find_first_of(","));
            fileReadings.push_back(tempCellString);
            //std::cout << "tcd: " << tempCellString << std::endl;//Debug controll
            tempCellString = "";
            tempString = tempString.substr(tempString.find_first_of(",")+1, tempString.length() - tempString.find_first_of(",")-1);//Remove the cell string from the temp string
        }

        tempCellString = tempString;
        fileReadings.push_back(tempCellString);
        //std::cout << "tcd: " << tempCellString << std::endl;//Debug controll
        tempCellString = "";
    }

    //for (auto & s:fileReadings)//Debug control
    //{
    //    std::cout << s << std::endl;
    //}
    //std::cout << fileReadings.size() << std::endl;
    return fileReadings;
}

std::vector<std::vector<std::string>>& CSVEditor::ReadFileByLine(const std::string& filePath) {
    std::vector<std::vector<std::string>> fileReadings = std::vector<std::vector<std::string>>();

    //Return empty if wrong file type was inserted.
    //std::cout << filePath.substr(filePath.length() - 4, 4) << std::endl;
    if (filePath.substr(filePath.length() - 4, 4) != ".csv")
        return fileReadings;

    std::fstream file = std::fstream(filePath);
    std::string tempString = "";
    std::string tempCellString = "";
    int i = 0;
    while (std::getline(file, tempString)) //Gets a line in the csv file and then splits it upp into string elements
    {
        fileReadings.push_back(std::vector<std::string>());

        //std::cout<<"ts: " << tempString << std::endl;//Debug controll
        while (tempString.find(",") != tempString.npos)
        {
            tempCellString = tempString.substr(0, tempString.find_first_of(","));
            fileReadings[i].push_back(tempCellString);
            //std::cout << "tcd: " << tempCellString << std::endl;//Debug controll
            tempCellString = "";
            tempString = tempString.substr(tempString.find_first_of(",") + 1, tempString.length() - tempString.find_first_of(",") - 1);//Remove the cell string from the temp string
        }

        tempCellString = tempString;
        fileReadings[i].push_back(tempCellString);
        //std::cout << "tcd: " << tempCellString << std::endl;//Debug controll
        tempCellString = "";
        i++;
    }

    //for (auto & s:fileReadings)//Debug control
    //{
    //    std::cout << s << std::endl;
    //}

    return fileReadings;
}

int CSVEditor::StartEdit(std::string& filePath)
{
    //Return error code 1 if not a csv file
    std::cout << filePath.substr(filePath.length() - 4, 4) << std::endl;
    if (filePath.substr(filePath.length() - 4, 4) != ".csv")
        return 1;

    this->filePath = filePath;
    ofstream.open(filePath);
}


